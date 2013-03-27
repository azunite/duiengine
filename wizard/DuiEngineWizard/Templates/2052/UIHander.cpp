#include "StdAfx.h"
#include "UIHander.h"

#include "MainDlg.h"

CUIHander::CUIHander(CMainDlg * pMainDlg) : m_pMainDlg(pMainDlg)
{
}

CUIHander::~CUIHander(void)
{
}

LRESULT CUIHander::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	SetMsgHandled(FALSE); 
	//演示在程序初始化的时候通过如用户配置文件设置PANE的大小.
// 	CDuiSplitWnd *pSplit=(CDuiSplitWnd*)m_pMainDlg->FindChildByCmdID(1180);
// 	pSplit->SetPaneInfo(0,100,-1,-1);
// 	CDuiRichEdit *pEdit=(CDuiRichEdit*)m_pMainDlg->FindChildByCmdID(1140);
// 	pEdit->DuiSendMessage(EM_SETEVENTMASK,0,ENM_CHANGE);

    return 0; 
}

void CUIHander::OnMsgBtnClick()
{
	DuiMessageBox(NULL,_T("messagebox test"),_T("tip"),MB_YESNOCANCEL|MB_ICONWARNING);
}
