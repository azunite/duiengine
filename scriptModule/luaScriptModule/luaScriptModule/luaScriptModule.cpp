// luaScriptModule.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <DuiEventSubscriber.h>
#include "luaScriptModule.h"
#include <wtl.mini/duistr.h>

#include "tolua++.h"
// prototype for bindings initialisation function
extern int tolua_duiengine_open(lua_State* tolua_S);

#include "..\\..\\lua_call.hpp"

using namespace DuiEngine;

template<>
void lua_function_base::push_value(CDuiWindow * pDuiWnd)
{
	tolua_pushusertype(m_vm,pDuiWnd,"DuiEngine::CDuiWindow");
}

template <>
DuiEngine::CDuiWindow * lua_function_base::value_extractor()
{
	CDuiWindow * val = (DuiEngine::CDuiWindow *)tolua_tousertype(m_vm, -1,0);
	lua_pop(m_vm, 1);
	return val;
}

template<>
void lua_function_base::push_value(LPNMHDR  pNmhdr)
{
	tolua_pushusertype(m_vm,pNmhdr,"NMHDR");
}

template <>
LPNMHDR lua_function_base::value_extractor()
{
	LPNMHDR val = (LPNMHDR)tolua_tousertype(m_vm, -1,0);
	lua_pop(m_vm, 1);
	return val;
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
		  lua_function<bool> luaEvtHandler(m_pLuaState,m_luaFun);
		  return luaEvtHandler(pSender,pNmhdr);
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

int CvtUTF8ToT(lua_State *L)
{

	CDuiStringT str;
	size_t n = 0; 
	char* pszSour = (char*)luaL_checklstring(L, -1, &n); 
	if(!pszSour) return 0;
	CDuiStringA strA(pszSour,n);
	str=DUI_CA2T(strA,CP_UTF8);
	lua_pushlstring(L, (char*)str.GetData(), (str.GetLength()+1)*sizeof(TCHAR)); 
	return 1;
}

int CvtAnsiToT(lua_State *L)
{

	CDuiStringT str;
	size_t n = 0; 
	char* pszSour = (char*)luaL_checklstring(L, -1, &n); 
	if(!pszSour) return 0;
	CDuiStringA strA(pszSour,n);
	str=DUI_CA2T(strA,CP_ACP);
	lua_pushlstring(L, (char*)str.GetData(), (str.GetLength()+1)*sizeof(TCHAR)); 
	return 1;
}

CLuaScriptModule::CLuaScriptModule()
{
	d_state = luaL_newstate();
	if(d_state)
	{
		luaL_openlibs(d_state);
		tolua_duiengine_open(d_state);
		lua_register(d_state, "L", CvtUTF8ToT); 
		lua_register(d_state, "W", CvtAnsiToT); 
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
