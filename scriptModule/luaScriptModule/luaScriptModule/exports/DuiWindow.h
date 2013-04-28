#include <duiwnd.h>

BOOL ExpLua_DuiWindow(lua_State *L)
{
	try{
		lua_tinker::class_add<CDuiWindow>(L,"CDuiWindow");
		lua_tinker::class_con<CDuiWindow>(L,lua_tinker::constructor<CDuiWindow>);
		lua_tinker::class_def<CDuiWindow>(L,"GetParent",&CDuiWindow::GetParent);
		lua_tinker::class_def<CDuiWindow>(L,"SetParent",&CDuiWindow::SetParent);
		lua_tinker::class_def<CDuiWindow>(L,"GetTopLevelParent",&CDuiWindow::GetTopLevelParent);
		lua_tinker::class_def<CDuiWindow>(L,"DestroyChild",&CDuiWindow::DestroyChild);
		lua_tinker::class_def<CDuiWindow>(L,"GetChildrenCount",&CDuiWindow::GetChildrenCount);
		lua_tinker::class_def<CDuiWindow>(L,"GetChild",&CDuiWindow::GetChild);
		lua_tinker::class_def<CDuiWindow>(L,"FindChildByCmdID",&CDuiWindow::FindChildByCmdID);
		lua_tinker::class_def<CDuiWindow>(L,"FindChildByName",&CDuiWindow::FindChildByName);
		lua_tinker::class_def<CDuiWindow>(L,"LoadXmlChildren",&CDuiWindow::LoadXmlChildren);
		lua_tinker::class_def<CDuiWindow>(L,"SetVisible",&CDuiWindow::SetVisible);

		return TRUE;
	}catch(...)
	{
		return FALSE;
	}
}