#pragma once

class CMainDlg;

class CUIHander
{
public:
	CUIHander(CMainDlg *pMainDlg);
	~CUIHander(void);

protected:
	LRESULT OnInitDialog(HWND hWnd, LPARAM lParam);

	void OnMsgBtnClick();
	
	BEGIN_MSG_MAP_EX(CUIHander)
		MSG_DUI_NOTIFY(IDC_RICHVIEW_WIN)
		MSG_WM_INITDIALOG(OnInitDialog)
	END_MSG_MAP()

	DUI_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		DUI_NOTIFY_ID_COMMAND(btn_msgbox, OnMsgBtnClick)
	DUI_NOTIFY_MAP_END()	
private:
	CMainDlg * m_pMainDlg; 
};
