#pragma once

class CIECtrlDlg :
	public CDuiHostWnd
{
public:
	CIECtrlDlg(void);
	~CIECtrlDlg(void);

protected:
	BEGIN_MSG_MAP_EX(CIECtrlDlg)
		CHAIN_MSG_MAP(CDuiHostWnd)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()
};
