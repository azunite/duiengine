// sample3.cpp : LuaTinker 의 클래스 기능을 알아본다.
//
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>

extern "C" 
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
};

#include "lua_tinker.h"

namespace NS{
struct A
{
	A(int v) : value(v) {}
	int value;
};

struct base
{
	base() {}

	const char* is_base(){ return "this is base"; }
};

class test : public base
{
public:
	test(int val) : _test(val) {}
	~test() {}

	const char* is_test(){ return "this is test"; }

	void ret_void() {}
	int ret_int()				{ return _test;			}
	int ret_mul(int m) const	{ return _test * m;		}
	A get()						{ return A(_test);		}
	void set(A a)				{ _test = a.value;		}

	HWND GetWnd(){
		HWND hRet=GetActiveWindow();
		return (HWND)0x12345678;
	}

	void SetWnd(HWND hWnd)
	{
		HWND hNewWnd=hWnd;
	}
	int _test;
};

test g_test(11);
}

int main()
{
	// Lua 를 초기화 한다.
	lua_State* L = lua_open();

	// Lua 기본 함수들을 로드한다.- print() 사용
	luaopen_base(L);
	// Lua 문자열 함수들을 로드한다.- string 사용
	luaopen_string(L);

	// base 클래스를 Lua 에 추가한다.
	lua_tinker::class_add<NS::base>(L, "base");
	// base 의 함수를 등록한다.
	lua_tinker::class_def<NS::base>(L, "is_base", &NS::base::is_base);

	// test 클래스를 Lua 에 추가한다.
	lua_tinker::class_add<NS::test>(L, "test");
	// test 가 base 에 상속 받았음을 알려준다.
	lua_tinker::class_inh<NS::test, NS::base>(L);
	// test 클래스 생성자를 등록한다.
	lua_tinker::class_con<NS::test>(L, lua_tinker::constructor<NS::test,int>);
	// test 의 함수들을 등록한다.
	lua_tinker::class_def<NS::test>(L, "is_test", &NS::test::is_test);
	lua_tinker::class_def<NS::test>(L, "ret_void", &NS::test::ret_void);
	lua_tinker::class_def<NS::test>(L, "ret_int", &NS::test::ret_int);
	lua_tinker::class_def<NS::test>(L, "ret_mul", &NS::test::ret_mul);
	lua_tinker::class_def<NS::test>(L, "get", &NS::test::get);
	lua_tinker::class_def<NS::test>(L, "set", &NS::test::set);
	lua_tinker::class_mem<NS::test>(L, "_test", &NS::test::_test);
	lua_tinker::class_def<NS::test>(L, "getwnd", &NS::test::GetWnd);
	lua_tinker::class_def<NS::test>(L, "setwnd", &NS::test::SetWnd);

	// Lua 전역 변수호 g_test 의 포인터를 등록한다.
	lua_tinker::set(L, "g_test", &NS::g_test);

	// sample3.lua 파일을 로드/실행한다.
	lua_tinker::dofile(L, "sample3.lua");

	HWND hWnd=lua_tinker::call<HWND>(L,"lua_getwnd");

	// 프로그램 종료
	lua_close(L);

	return 0;
}

