#include "StdAfx.h"
#include "UIHander.h"

#include "MainDlg.h"
#include "skinole/ImageOle.h"

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

void CUIHander::OnAttrReposition()
{
	m_pMainDlg->FindChildByCmdID(测试)->SetAttribute("pos","|-100,|-15,|100,|15");
}


// #define  PATH_GIF _T("E:\\dui.work\\RichEditDemo\\RichEditDemo\\Face\\1.gif")

void CUIHander::OnRepEditSel()
{
	CDuiRichEdit *pEdit=(CDuiRichEdit *)m_pMainDlg->FindChildByCmdID(1140);
	if(pEdit)
	{
		for(int i=0;i<5;i++)
		{
			CDuiSkinBase *pSkinGif=DuiSkinPool::getSingleton().GetSkin("face0");
// 			RichEdit_InsertImage(pEdit,PATH_GIF);//从文件加载 
			RichEdit_InsertSkin(pEdit,pSkinGif);
			CDuiSkinBase *pSkin=DuiSkinPool::getSingleton().GetSkin("bmpmask");
			RichEdit_InsertSkin(pEdit,pSkin);
// 			RichEdit_InsertSkin(pEdit,pSkin);
// 			RichEdit_InsertSkin(pEdit,pSkin);
		}
	}
//	pEdit->SetDefaultTextColor(RGB(0,128,128));
// 	pEdit->SetAttribute("crtext","00CCCC");
// 	pEdit->SetSel(MAKELONG(5,5));
// 	pEdit->ReplaceSel(L"repsel");
// 	TCHAR szBuf[100]={0};
// 	pEdit->GetWindowText(szBuf,100);


}

LRESULT CUIHander::OnEditNotify( LPNMHDR pNHdr )
{
	LPDUIRICHEDITNOTIFY pEditNotify=(LPDUIRICHEDITNOTIFY)pNHdr;
	if(pEditNotify->iNotify==EN_CHANGE)
	{
	}
	return S_OK;
}

//演示阻止combobox继续发送selchanged消息。
LRESULT CUIHander::OnComboListSelChanging( LPNMHDR pNHdr )
{
	LPDUINMLBSELCHANGE pLbSelChange=(LPDUINMLBSELCHANGE)pNHdr;
	return pLbSelChange->uHoverID==3?S_FALSE:S_OK;//点击删除按钮时下拉窗口不关闭
}
  
//演示combobox选择改变的事件响应
LRESULT CUIHander::OnComboListSelChanged( LPNMHDR pNHdr )
{
	LPDUINMLBSELCHANGE pLbSelChange=(LPDUINMLBSELCHANGE)pNHdr;
	CDuiComboBox *pCombobox=(CDuiComboBox*)m_pMainDlg->FindChildByCmdID(1310);
	return S_OK;
}

//演示响应combobox选项中按钮事件的响应
LRESULT CUIHander::OnComboListItemNotify( LPNMHDR pNHdr )
{
	LPDUINMITEMNOTIFY pItemNHdr=(LPDUINMITEMNOTIFY)pNHdr;
	if(pItemNHdr->pOriginHdr->idFrom==3) 
	{//delete button 
		CDuiComboBox *pCombobox=(CDuiComboBox*)m_pMainDlg->FindChildByCmdID(1310);
		CDuiListBoxEx *pListBox=(CDuiListBoxEx*)pItemNHdr->pHostDuiWin;
		int iItem=pListBox->GetItemObjIndex(pItemNHdr->pItem);
		pCombobox->DeleteItem(iItem); 
	}
	return S_OK;
}


void CUIHander::OnIECtrl()
{
	CDuiImageWnd *pImgWnd=(CDuiImageWnd*)m_pMainDlg->FindChildByCmdID(1139);
	if(pImgWnd)
	{
// 		CDuiImgX *pImg=new CDuiImgX;
// 		pImg->LoadImg(L"e:\\test.png");
// 		CDuiImageList *pSkin=new CDuiImageList;
// 		pSkin->SetImage(pImg);
// 		pImgWnd->SetSkin(pSkin);
// 		pSkin->Release();
	}
}


void CUIHander::OnDuiMenu()
{
	CPoint pt; 
	GetCursorPos(&pt);
	CDuiMenu menu;  
	menu.LoadMenu(IDR_MENU_TEST); //load menu
	CDuiMenu subMenu=menu.GetSubMenu(5);
	CheckMenuRadioItem(subMenu.m_hMenu,51,53,52,MF_BYCOMMAND);
// 	CDuiMenu subMenu2; 
// 	subMenu2.CreatePopupMenu();
// 	subMenu2.InsertMenu(1,MF_STRING|MF_BYPOSITION,59,_T("代码插入1"),3);
// 	subMenu2.InsertMenu(2,MF_STRING|MF_BYPOSITION|MF_GRAYED,58,_T("代码插入2"),3);
// 	subMenu.InsertMenu(1,MF_POPUP|MF_BYPOSITION,(UINT_PTR)&subMenu2,_T("插入子菜单"),5);
	UINT uRet=menu.TrackPopupMenu(0,pt.x,pt.y,m_pMainDlg->m_hWnd);
// 	ATLTRACE(L"\nmenu ret=%d",uRet); 
}

void CUIHander::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
{
// 	ATLTRACE(L"\nOnCommand nID=%d",nID);  

}


void CUIHander::OnWebkit_GoBack()
{
// 	CDuiWebkit *pWebkitCtrl=static_cast<CDuiWebkit*>(m_pMainDlg->FindChildByCmdID(1205));
// 	pWebkitCtrl->GoBack();
}

void CUIHander::OnWebkit_GoForward()
{
// 	CDuiWebkit *pWebkitCtrl=static_cast<CDuiWebkit*>(m_pMainDlg->FindChildByCmdID(1205));
// 	pWebkitCtrl->GoForward();
}

void CUIHander::OnWebkit_Refresh()
{
// 	CDuiWebkit *pWebkitCtrl=static_cast<CDuiWebkit*>(m_pMainDlg->FindChildByCmdID(1205));
// 	pWebkitCtrl->Refresh();
}

void CUIHander::OnWebkit_Go()
{
// 	CDuiWebkit *pWebkitCtrl=static_cast<CDuiWebkit*>(m_pMainDlg->FindChildByCmdID(1205));
// 	CDuiRichEdit *pEdit=static_cast<CDuiRichEdit*>(m_pMainDlg->FindChildByCmdID(1203));
// 	WCHAR szURI[200];
// 	pEdit->GetWindowText(szURI,200);
// 	CDuiStringA strURI=CW2A(szURI,CP_UTF8);
// 	pWebkitCtrl->SetURI(strURI);
}

//演示列表中的按钮控件的响应
LRESULT CUIHander::OnListBtnClick( LPNMHDR pNHdr )
{
	DUINMITEMNOTIFY *pNHdrEx=(DUINMITEMNOTIFY*)pNHdr;

	return S_OK;
}