
#ifndef __DUICOMPTR_H__
#define __DUICOMPTR_H__

#pragma once

#include <unknwn.h>

// COMPILE_ASSERT宏用来在编译时断言表达式. 例如可以这样保证静态数组大小:
//     COMPILE_ASSERT(ARRAYSIZE_UNSAFE(content_type_names)==CONTENT_NUM_TYPES,
//         content_type_names_incorrect_size);
//
// 或者确保结构体小于一定大小:
//     COMPILE_ASSERT(sizeof(foo)<128, foo_too_large);
// 第二个宏参数是变量名, 如果表达式为false, 编译器会产生一条包含变量名的错误/警告.
template<bool>
struct CompileAssert {};

// COMPILE_ASSERT实现细节:
//
// - COMPILE_ASSERT通过定义一个长度为-1的数组(非法)来实现的, 此时表达式false.
//
// - 下面简化的定义
//       #define COMPILE_ASSERT(expr, msg) typedef char msg[(expr)?1:-1]
//   是非法的. 由于gcc支持运行时确定长度的变长数组(gcc扩展, 不属于C++标准),
//   导致下面这段简单的代码定义不报错:
//       int foo;
//       COMPILE_ASSERT(foo, msg); // not supposed to compile as foo is
//                                 // not a compile-time constant.
//
// - 要使用类型CompileAssert<(bool(expr))>, 必须确保expr是编译时常量.
//   (模板参数在编译时确定.)
//
// - CompileAssert<(bool(expr))>最外层的圆括号用于解决gcc 3.4.4和4.0.1的
//   一个bug. 如果写成
//       CompileAssert<bool(expr)>
//   编译器将无法编译
//       COMPILE_ASSERT(5>0, some_message);
//   ("5>0"中的">"被误认为是模板参数列表结尾的">".)
//
// - 数组大小是(bool(expr)?1:-1)而不是((expr)?1:-1), 可以解决MS VC 7.1
//   中把((0.0)?1:-1)错误计算为1的bug.
#undef COMPILE_ASSERT
#define COMPILE_ASSERT(expr, msg) \
	typedef CompileAssert<(bool(expr))> msg[bool(expr)?1:-1]

namespace DuiEngine
{
	template<class T>
	class CDuiRefPtr
	{
	public:
		CDuiRefPtr() : ptr_(NULL) {}

		CDuiRefPtr(T* p) : ptr_(p)
		{
			if(ptr_)
			{
				ptr_->AddRef();
			}
		}

		CDuiRefPtr(const CDuiRefPtr<T>& r) : ptr_(r.ptr_)
		{
			if(ptr_)
			{
				ptr_->AddRef();
			}
		}

		template<typename U>
		CDuiRefPtr(const CDuiRefPtr<U>& r) : ptr_(r.get())
		{
			if(ptr_)
			{
				ptr_->AddRef();
			}
		}

		~CDuiRefPtr()
		{
			if(ptr_)
			{
				ptr_->Release();
			}
		}

		T* get() const { return ptr_; }
		operator T*() const { return ptr_; }
		T* operator->() const { return ptr_; }

		// 释放指针.
		// 返回对象当前拥有的指针. 如果指针为NULL, 返回NULL.
		// 操作完成后, 对象拥有一个NULL指针, 不再拥有任何对象.
		T* release()
		{
			T* retVal = ptr_;
			ptr_ = NULL;
			return retVal;
		}

		CDuiRefPtr<T>& operator=(T* p)
		{
			// 先调用AddRef, 这样自我赋值也能工作.
			if(p)
			{
				p->AddRef();
			}
			if(ptr_ )
			{
				ptr_ ->Release();
			}
			ptr_ = p;
			return *this;
		}

		CDuiRefPtr<T>& operator=(const CDuiRefPtr<T>& r)
		{
			return *this = r.ptr_;
		}

		template<typename U>
		CDuiRefPtr<T>& operator=(const CDuiRefPtr<U>& r)
		{
			return *this = r.get();
		}

		void swap(T** pp)
		{
			T* p = ptr_;
			ptr_ = *pp;
			*pp = p;
		}

		void swap(CDuiRefPtr<T>& r)
		{
			swap(&r.ptr_);
		}

	protected:
		T* ptr_;
	};

	template<typename T>
	CDuiRefPtr<T> MakeRefPtr(T* t)
	{
		return CDuiRefPtr<T>(t);
	}

	// 模拟COM接口的智能指针. 使用scoped_refptr作为积累提供引用计数功能,
	// 添加了IUnknown的一些特定服务.
	template<class Interface, const IID* interface_id=&__uuidof(Interface)>
	class CDuiComPtr : public CDuiRefPtr<Interface>
	{
	public:
		// 工具模板, 阻止使用者透过ScopedComPtr类调用接口指针的AddRef和(或)
		// Release.
		class BlockIUnknownMethods : public Interface
		{
		private:
			STDMETHOD(QueryInterface)(REFIID iid, void** object) = 0;
			STDMETHOD_(ULONG, AddRef)() = 0;
			STDMETHOD_(ULONG, Release)() = 0;
		};

		typedef CDuiRefPtr<Interface> ParentClass;

		CDuiComPtr() {}

		explicit CDuiComPtr(Interface* p) : ParentClass(p) {}

		CDuiComPtr(const CDuiComPtr<Interface, interface_id>& p)
			: ParentClass(p) {}

		~CDuiComPtr()
		{
			// 智能指针类的大小跟裸指针保持一致.
			COMPILE_ASSERT(sizeof(CDuiComPtr<Interface, interface_id>) ==
				sizeof(Interface*), ScopedComPtrSize);
		}

		// 显式调用内部对象的Release()方法. 为ScopedComPtr实例提供重用功能.
		// 函数与IUnknown::Release等价, 不要与scoped_ptr::release()混淆.
		void Release()
		{
			if(ptr_ != NULL)
			{
				ptr_->Release();
				ptr_ = NULL;
			}
		}

		// 使内部对象与本对象分离并返回其指针.
		Interface* Detach()
		{
			Interface* p = ptr_;
			ptr_ = NULL;
			return p;
		}

		// 接受一个已经被addref的接口指针.
		void Attach(Interface* p)
		{
			DUIASSERT(ptr_ == NULL);
			ptr_ = p;
		}

		// 返回接口指针的地址.
		// 用于接受输出参数(接管所有权). 函数使用DUIASSERTs验证当前值是否为NULL.
		// 用法: Foo(p.Receive());
		Interface** Receive()
		{
			DUIASSERT(ptr_==NULL);
			return &ptr_;
		}

		// 返回void**类型的接口指针的地址.
		void** ReceiveVoid()
		{
			return reinterpret_cast<void**>(Receive());
		}

		template<class Query>
		HRESULT QueryInterface(Query** p)
		{
			DUIASSERT(p != NULL);
			DUIASSERT(ptr_ != NULL);
			// IUnknown已经有一个模板版本的QueryInterface, 所以iid参数在
			// 这里是隐式的. 这里只是添加了DUIASSERTs.
			return ptr_->QueryInterface(p);
		}

		// 在IID没与类型关联时QI.
		HRESULT QueryInterface(const IID& iid, void** obj)
		{
			DUIASSERT(obj != NULL);
			DUIASSERT(ptr_ != NULL);
			return ptr_->QueryInterface(iid, obj);
		}

		// 从|other|查询内部对象接口, 并返回other->QueryInterface操作的错误码.
		HRESULT QueryFrom(IUnknown* object)
		{
			DUIASSERT(object != NULL);
			return object->QueryInterface(Receive());
		}

		// CoCreateInstance封装.
		HRESULT CreateInstance(const CLSID& clsid, IUnknown* outer=NULL,
			DWORD context=CLSCTX_ALL)
		{
			DUIASSERT(ptr_ == NULL);
			HRESULT hr = ::CoCreateInstance(clsid, outer, context,
				*interface_id, reinterpret_cast<void**>(&ptr_));
			return hr;
		}

		// 检查本对象与|other|是否相同.
		bool IsSameObject(IUnknown* other)
		{
			if(!other && !ptr_)
			{
				return true;
			}

			if(!other || !ptr_)
			{
				return false;
			}

			CDuiComPtr<IUnknown> my_identity;
			QueryInterface(my_identity.Receive());

			CDuiComPtr<IUnknown> other_identity;
			other->QueryInterface(other_identity.Receive());

			return static_cast<IUnknown*>(my_identity) ==
				static_cast<IUnknown*>(other_identity);
		}

		// 提供接口的直接访问. 这里使用了一个常用的技巧限制访问IUknown的
		// 方法, 以免发生类似下面的错误做法:
		//     ScopedComPtr<IUnknown> p(Foo());
		//     p->Release();
		//     ... 后面析构函数执行时, 会再次调用Release().
		// 还能得益于QueryInterface添加的DUIASSERTs. 假如你静态的强转ScopedComPtr到
		// 被封装的接口, 你还是可以通过接口指针访问这些方法, 但是一般不要那样做.
		BlockIUnknownMethods* operator->() const
		{
			DUIASSERT(ptr_ != NULL);
			return reinterpret_cast<BlockIUnknownMethods*>(ptr_);
		}

		// 使用父类的operator=().
		using CDuiRefPtr<Interface>::operator=;

		static const IID& iid()
		{
			return *interface_id;
		}
	};

} //namespace base

#endif //__DUICOMPTR_H__