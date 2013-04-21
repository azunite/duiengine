#pragma once
#include <string>
#include <exception>

#pragma warning(disable:4800)

// the base function wrapper class
class lua_function_base
{
public:
    lua_function_base(lua_State *vm, LPCSTR func)
        : m_vm(vm)
    {
        // get the function
        lua_getfield(m_vm, LUA_GLOBALSINDEX, func);
        // ensure it's a function
        if (!lua_isfunction(m_vm, -1)) {
            // throw an exception; you'd use your own exception class here
            // of course, but for sake of simplicity i use runtime_error
            lua_pop(m_vm, 1);
			std::string err=std::string(func)+" is not a valid function";
            throw std::exception(err.c_str());
        }
        // store it in registry for later use
        m_func = luaL_ref(m_vm, LUA_REGISTRYINDEX);
    }

    lua_function_base(const lua_function_base& func)
        : m_vm(func.m_vm)
    {
        // copy the registry reference
        lua_rawgeti(m_vm, LUA_REGISTRYINDEX, func.m_func);
        m_func = luaL_ref(m_vm, LUA_REGISTRYINDEX);
    }

    ~lua_function_base()
    {
        // delete the reference from registry
        luaL_unref(m_vm, LUA_REGISTRYINDEX, m_func);
    }

    lua_function_base& operator=(const lua_function_base& func)
    {
        if (this != &func) {
            m_vm = func.m_vm;
            lua_rawgeti(m_vm, LUA_REGISTRYINDEX, func.m_func);
            m_func = luaL_ref(m_vm, LUA_REGISTRYINDEX);
        }
        return *this;
    }
	
	template<typename T>
	void push_value(T n)
	{
		lua_pushlightuserdata(m_vm, &n);
	}


	template<typename T>
	T value_extractor()
	{
		T ret= *(T *)lua_touserdata(m_vm,-1);
		lua_pop(m_vm, 1);
		return ret;
	}

protected:
    // the virtual machine and the registry reference to the function
    lua_State *m_vm;
    int m_func;

    // call the function, throws an exception on error
    void call(int args, int results=1)
    {
        // call it with no return values
        int status = lua_pcall(m_vm, args, results, 0);
        if (status != 0) {
            // call failed; throw an exception
            std::string error = lua_tostring(m_vm, -1);
            lua_pop(m_vm, 1);
            // in reality you'd want to use your own exception class here
            throw std::exception(error.c_str());
        }
    }
};

template<>
void lua_function_base::push_value(lua_Integer n)
{
	lua_pushinteger(m_vm, n);
}

template <>
lua_Integer lua_function_base::value_extractor()
{
	lua_Integer val = lua_tointeger(m_vm, -1);
	lua_pop(m_vm, 1);
	return val;
}

template<>
void lua_function_base::push_value(lua_Number n)
{
	lua_pushnumber(m_vm, n);
}

template <>
lua_Number lua_function_base::value_extractor()
{
	lua_Number val = lua_tonumber(m_vm, -1);
	lua_pop(m_vm, 1);
	return val;
}

template<>
void lua_function_base::push_value(bool b)
{
	lua_pushboolean(m_vm, b);
}

template <>
bool lua_function_base::value_extractor()
{
	bool val = lua_toboolean(m_vm, -1);
	lua_pop(m_vm, 1);
	return val;
}

template<>
void lua_function_base::push_value(std::string s)
{
	lua_pushstring(m_vm, s.c_str());
}

template <>
std::string lua_function_base::value_extractor()
{
	std::string val = lua_tostring(m_vm, -1);
	lua_pop(m_vm, 1);
	return val;
}

template<>
void lua_function_base::push_value(void * s)
{
	lua_pushlightuserdata(m_vm, s);
}

template <>
void * lua_function_base::value_extractor()
{
	void * val = lua_touserdata(m_vm, -1);
	lua_pop(m_vm, 1);
	return val;
}

template<>
void lua_function_base::push_value(const char * pstr)
{
	lua_pushstring(m_vm, pstr);
}

template <>
const char * lua_function_base::value_extractor()
{
	const char * val = lua_tostring(m_vm, -1);
	lua_pop(m_vm, 1);
	return val;
}

// the function wrapper class
template <typename Ret>
class lua_function : public lua_function_base
{
public:
    lua_function(lua_State *vm, LPCSTR func)
        : lua_function_base(vm, func)
    {
    }

    Ret operator()()
    {
        // push the function from the registry
        lua_rawgeti(m_vm, LUA_REGISTRYINDEX, m_func);
        // call the function on top of the stack (throws exception on error)
        call(0);
        // return the value
        return  value_extractor<Ret>::get(m_vm);
    }

    template <typename T1>
    Ret operator()(const T1& p1)
    {
        lua_rawgeti(m_vm, LUA_REGISTRYINDEX, m_func);
        // push the argument and call with 1 arg
         push_value(p1);
        call(1);
        return  value_extractor<Ret>();
    }

    template <typename T1, typename T2>
    Ret operator()(const T1& p1, const T2& p2)
    {
        lua_rawgeti(m_vm, LUA_REGISTRYINDEX, m_func);
        // push the arguments and call with 2 args
         push_value( p1);
         push_value( p2);
        call(2);
		return  value_extractor<Ret>();
    }

    template <typename T1, typename T2, typename T3>
    Ret operator()(const T1& p1, const T2& p2, const T3& p3)
    {
        lua_rawgeti(m_vm, LUA_REGISTRYINDEX, m_func);
         push_value( p1);
         push_value( p2);
         push_value( p3);
        call(3);
		return  value_extractor<Ret>();
    }

	template <typename T1, typename T2, typename T3,typename T4>
	Ret operator()(const T1& p1, const T2& p2, const T3& p3, const T4& p4)
	{
		lua_rawgeti(m_vm, LUA_REGISTRYINDEX, m_func);
		push_value( p1);
		push_value( p2);
		push_value( p3);
		push_value( p4);
		call(4);
		return  value_extractor<Ret>();
	}

	template <typename T1, typename T2, typename T3,typename T4,typename T5>
	Ret operator()(const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5  p5)
	{
		lua_rawgeti(m_vm, LUA_REGISTRYINDEX, m_func);
		push_value( p1);
		push_value( p2);
		push_value( p3);
		push_value( p4);
		push_value( p5);
		call(5);
		return  value_extractor<Ret>();
	}
    // et cetera, provide as many overloads as you need
};

// we need to specialize the function for void return type
// as the other class would fail to compile with void as return type
template <>
class lua_function<void> : public lua_function_base
{
public:
    lua_function(lua_State *vm, LPCSTR func)
        : lua_function_base(vm, func)
    {
    }

    void operator()()
    {
        lua_rawgeti(m_vm, LUA_REGISTRYINDEX, m_func);
        call(0);
    }

    template <typename T1>
    void operator()(const T1& p1)
    {
        lua_rawgeti(m_vm, LUA_REGISTRYINDEX, m_func);
         push_value(p1);
        call(1);
    }

    template <typename T1, typename T2>
    void operator()(const T1& p1, const T2& p2)
    {
        lua_rawgeti(m_vm, LUA_REGISTRYINDEX, m_func);
         push_value( p1);
         push_value( p2);
        call(2);
    }

    template <typename T1, typename T2, typename T3>
    void operator()(const T1& p1, const T2& p2, const T3& p3)
    {
        lua_rawgeti(m_vm, LUA_REGISTRYINDEX, m_func);
         push_value( p1);
         push_value( p2);
         push_value( p3);
        call(3);
    }

    // et cetera, provide as many overloads as you need
};