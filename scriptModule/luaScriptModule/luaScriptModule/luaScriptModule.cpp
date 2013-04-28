// luaScriptModule.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <DuiEventSubscriber.h>
#include "luaScriptModule.h"
#include "lua_tinker.h"

using namespace DuiEngine;

extern BOOL DuiEngine_Export_Lua(lua_State *L);

wchar_t * cast_a2w(char * str)
{
	return (wchar_t *)str;
}

int Utf8ToW(lua_State* L)
{
	size_t n = 0;
	char* str = (char*)luaL_checklstring(L, -1, &n);
	if(!str)   return 0;
	int nSize=MultiByteToWideChar(CP_UTF8,0,str,n,NULL,0);
	wchar_t *wstr=new wchar_t[nSize+1];
	MultiByteToWideChar(CP_UTF8,0,str,n,wstr,nSize+1);
	wstr[nSize]=0;
	lua_pushlstring(L, (char*)wstr, 2*nSize+2);
	delete []wstr;
	return 1;
}

class LuaFunctionSlot : public SlotFunctorBase
{
public:
	//! Slot function type.
	LuaFunctionSlot(lua_State *pLuaState,LPCSTR pszLuaFun) 
		: m_pLuaState(pLuaState)
		, m_luaFun(pszLuaFun)
	  {}

	  virtual bool operator()(CDuiWindow * pSender,LPNMHDR pNmhdr)
	  {
		  return lua_tinker::call<bool>(m_pLuaState,m_luaFun,pSender,pNmhdr);
	  }

	  virtual SlotFunctorBase* Clone() const 
	  {
		  return new LuaFunctionSlot(m_pLuaState,m_luaFun);
	  }

	  virtual bool Equal(const SlotFunctorBase & sour)const 
	  {
		  if(sour.GetSlotType()!=GetSlotType()) return false;
		  const LuaFunctionSlot *psour=static_cast<const LuaFunctionSlot*>(&sour);
		  DUIASSERT(psour);
		  return psour->m_luaFun==m_luaFun && psour->m_pLuaState==m_pLuaState;
	  }

	  virtual UINT GetSlotType() const {return SLOT_USER+1;}

private:
	CDuiStringA m_luaFun;
	lua_State *m_pLuaState;
};


CLuaScriptModule::CLuaScriptModule()
{
	d_state = lua_open();
	if(d_state)
	{
		luaL_openlibs(d_state);
		DuiEngine_Export_Lua(d_state);
		lua_register(d_state, "A2W", Utf8ToW);
		lua_tinker::def(d_state, "cast_a2w", cast_a2w);
		luaL_dostring(d_state,"function L (str)\n return cast_a2w(A2W(str));\nend");//注册一个全局的"L"函数，用来将utf8编码的字符串转换为宽字符
	}
}


CLuaScriptModule::~CLuaScriptModule()
{
	if (d_state)
	{
		lua_close( d_state );
	}
}


int CLuaScriptModule::loadScriptFile( LPCSTR pszScriptFile )
{
	return luaL_loadfile(d_state,pszScriptFile);
}


int CLuaScriptModule::loadScriptString( LPCSTR pszScriptStr )
{
	return luaL_loadstring(d_state,pszScriptStr);
}

LPCSTR CLuaScriptModule::getIdentifierString() const
{
	return "DuiEngine.Script.Lua5.1";
}

void CLuaScriptModule::executeScriptFile( LPCSTR pszScriptFile )
{
 	luaL_dofile(d_state,pszScriptFile);
}

bool CLuaScriptModule::executeScriptedEventHandler( LPCSTR handler_name, DuiEngine::CDuiWindow *pSender, LPNMHDR pNmhdr)
{
	LuaFunctionSlot luaFunSlot(d_state,handler_name);
	return luaFunSlot(pSender,pNmhdr);
}

void CLuaScriptModule::executeString( LPCSTR str )
{
	luaL_dostring(d_state,str);
}

bool CLuaScriptModule::subscribeEvent(DuiEngine::CDuiWindow* target, UINT uEvent, LPCSTR subscriber_name )
{
	return target->subscribeEvent(uEvent,LuaFunctionSlot(d_state,subscriber_name));
}
