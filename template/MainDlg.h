// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include "UIHander.h"

class CMainDlg : public CDuiHostWnd
{
public:
	CMainDlg();
	~CMainDlg();

	void OnClose()
	{
		EndDialog(IDCANCEL);
	}

protected:

	DUI_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		DUI_NOTIFY_ID_COMMAND(1, OnClose)
	DUI_NOTIFY_MAP_END()	

	BEGIN_MSG_MAP_EX(CMainDlg)
		MSG_WM_CLOSE(OnClose)
		MSG_DUI_NOTIFY(IDC_RICHVIEW_WIN)
		CHAIN_MSG_MAP_MEMBER((*m_pUiHandler))
		CHAIN_MSG_MAP(CDuiHostWnd)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

private:
	CUIHander *    m_pUiHandler; 
};
