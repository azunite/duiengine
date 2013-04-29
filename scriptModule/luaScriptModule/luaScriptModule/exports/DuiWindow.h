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
		lua_tinker::class_def<CDuiWindow>(L,"GetTextAlign",&CDuiWindow::GetTextAlign);
		lua_tinker::class_def<CDuiWindow>(L,"SetFixSize",&CDuiWindow::SetFixSize);
		lua_tinker::class_def<CDuiWindow>(L,"SetBkColor",&CDuiWindow::SetBkColor);
		lua_tinker::class_def<CDuiWindow>(L,"GetRect",&CDuiWindow::GetRect);
		lua_tinker::class_def<CDuiWindow>(L,"GetClient",&CDuiWindow::GetClient);
		lua_tinker::class_def<CDuiWindow>(L,"GetInnerText",&CDuiWindow::GetInnerText);
		lua_tinker::class_def<CDuiWindow>(L,"SetInnerText",&CDuiWindow::SetInnerText);
		lua_tinker::class_def<CDuiWindow>(L,"DuiSendMessage",&CDuiWindow::DuiSendMessage);
		lua_tinker::class_def<CDuiWindow>(L,"GetCmdID",&CDuiWindow::GetCmdID);
		lua_tinker::class_def<CDuiWindow>(L,"SetCmdID",&CDuiWindow::SetCmdID);
		lua_tinker::class_def<CDuiWindow>(L,"GetUserData",&CDuiWindow::GetUserData);
		lua_tinker::class_def<CDuiWindow>(L,"SetUserData",&CDuiWindow::SetUserData);
		lua_tinker::class_def<CDuiWindow>(L,"GetName",&CDuiWindow::GetName);
		lua_tinker::class_def<CDuiWindow>(L,"GetDuiHwnd",&CDuiWindow::GetDuiHwnd);
		lua_tinker::class_def<CDuiWindow>(L,"InsertChild",&CDuiWindow::InsertChild);
		lua_tinker::class_def<CDuiWindow>(L,"RemoveChild",&CDuiWindow::RemoveChild);
		lua_tinker::class_def<CDuiWindow>(L,"IsChecked",&CDuiWindow::IsChecked);
		lua_tinker::class_def<CDuiWindow>(L,"IsDisabled",&CDuiWindow::IsDisabled);
		lua_tinker::class_def<CDuiWindow>(L,"IsVisible",&CDuiWindow::IsVisible);
		lua_tinker::class_def<CDuiWindow>(L,"SetVisible",&CDuiWindow::SetVisible);
		lua_tinker::class_def<CDuiWindow>(L,"EnableWindow",&CDuiWindow::EnableWindow);
		lua_tinker::class_def<CDuiWindow>(L,"SetCheck",&CDuiWindow::SetCheck);
		lua_tinker::class_def<CDuiWindow>(L,"GetLinkUrl",&CDuiWindow::GetLinkUrl);
		lua_tinker::class_def<CDuiWindow>(L,"SetOwner",&CDuiWindow::SetOwner);
		lua_tinker::class_def<CDuiWindow>(L,"GetOwner",&CDuiWindow::GetOwner);
		lua_tinker::class_def<CDuiWindow>(L,"NotifyInvalidate",&CDuiWindow::NotifyInvalidate);
//		lua_tinker::class_def<CDuiWindow>(L,"NotifyInvalidateRect",(void (*)(LPRECT))&CDuiWindow::NotifyInvalidateRect);

		return TRUE;
	}catch(...)
	{
		return FALSE;
	}
}