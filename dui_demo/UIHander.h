#pragma once

#include "DuiMenu.h" 

class CMainDlg;

class CUIHander
{
public:
	struct student{
		TCHAR szName[100];
		TCHAR szSex[10];
		int age;
		int score;
	};

	CUIHander(CMainDlg *pMainDlg);
	~CUIHander(void);
	
	bool Evt_Test(CDuiWindow * pSender, LPNMHDR pNmhdr);

protected:
	LRESULT OnInitDialog(HWND hWnd, LPARAM lParam);

	void OnDestory();

	void OnAttrReposition();
	void OnRepEditSel();
	void OnIECtrl();
	void OnDuiMenu();
	void OnBtnAniList();

	LRESULT OnEditNotify(LPNMHDR pNHdr);

	LRESULT OnComboListSelChanging( LPNMHDR pNHdr );

	LRESULT OnComboListSelChanged(LPNMHDR pNHdr);

	LRESULT OnComboListItemNotify(LPNMHDR pNHdr);

	LRESULT OnListPredraw(LPNMHDR pNHdr);

	void OnCommand(UINT uNotifyCode, int nID, HWND wndCtl);

	LRESULT OnListBtnClick(LPNMHDR pNHdr);

	void OnBtnInitListClick();

	bool OnListHeaderClick(CDuiWindow * pSender, LPNMHDR pNmhdr);

	BEGIN_MSG_MAP_EX(CUIHander)
		MSG_DUI_NOTIFY(IDC_RICHVIEW_WIN)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_DESTROY(OnDestory)
		MSG_WM_COMMAND(OnCommand)
	END_MSG_MAP()

	DUI_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		DUI_NOTIFY_ID_COMMAND(≤‚ ‘, OnAttrReposition)
		DUI_NOTIFY_ID_COMMAND(IDC_REPSEL, OnRepEditSel)
		DUI_NOTIFY_ID_COMMAND(1307, OnIECtrl)
		DUI_NOTIFY_ID_COMMAND(1360, OnDuiMenu)
		DUI_NOTIFY_HANDLER(1140,DUINM_RICHEDIT_NOTIFY,OnEditNotify)
		DUI_NOTIFY_HANDLER(1310,DUINM_LBSELCHANGED,OnComboListSelChanged)
		DUI_NOTIFY_HANDLER(1310,DUINM_LBSELCHANGING,OnComboListSelChanging)
		DUI_NOTIFY_HANDLER(1310,DUINM_LBITEMNOTIFY,OnComboListItemNotify)
		DUI_NOTIFY_HANDLER(mylist,DUINM_LBITEMNOTIFY,OnListBtnClick)
		DUI_NOTIFY_HANDLER(mylist2,DUINM_GETLBDISPINFO,OnListPredraw)

		DUI_NOTIFY_ID_COMMAND(btn_ani,OnBtnAniList)
	DUI_NOTIFY_MAP_END()	
private:
	CMainDlg * m_pMainDlg; 
};
