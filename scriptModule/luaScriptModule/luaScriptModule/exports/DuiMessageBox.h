#include <DuiMessageBox.h>

BOOL ExpLua_DuiMessageBox(lua_State *L)
{
	try{
		lua_tinker::def(L,"DuiMessageBox",DuiMessageBox);
		return TRUE;
	}catch(...)
	{
		return FALSE;
	}
}