#pragma once

namespace DuiEngine
{

#define IDC_MSGBOX_BTN1PANEL	65400
#define IDC_MSGBOX_BTN2PANEL	65401
#define IDC_MSGBOX_BTN3PANEL	65402
#define IDC_MSGBOX_TEXT			65403
#define IDC_MSGBOX_TITLE		65404
#define IDC_MSGBOX_ICON			65405
#define IDC_MSGBOX_BTN1			65410
#define IDC_MSGBOX_BTN2			65411
#define IDC_MSGBOX_BTN3			65412

int DUI_EXP DuiMessageBox(HWND hWnd, 
						   LPCTSTR lpText, 
						   LPCTSTR lpCaption, 
						   UINT uType
);

}//endof namespace 

