#include <DuiThreadActiveWndManager.h>

BOOL ExpLua_DuiThreadActiveWndMgr(lua_State *L)
{
	try{
		lua_tinker::def(L,"DuiThreadActiveWndManager_SetActive",&DuiThreadActiveWndManager::SetActive);
		lua_tinker::def(L,"DuiThreadActiveWndManager_GetActive",&DuiThreadActiveWndManager::GetActive);

		return TRUE;
	}catch(...)
	{
		return FALSE;
	}
}