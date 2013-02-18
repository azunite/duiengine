#include "duistd.h"
#include "DuiMessageBox.h"
#include "DuiSystem.h"
#include "duihostwnd.h"
#include "duiwndcmnctrl.h"

namespace DuiEngine
{

	class CDuiMessageBox:public CDuiHostWnd
	{
	public:
		void OnBtnClick(UINT uID)
		{
			EndDialog(uID);
		}

	DUI_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		DUI_NOTIFY_ID_COMMAND_EX(IDOK,IDNO, OnBtnClick)
	DUI_NOTIFY_MAP_END()	

	BEGIN_MSG_MAP_EX(CDuiMessageBox)
		MSG_DUI_NOTIFY(IDC_RICHVIEW_WIN)
		CHAIN_MSG_MAP(CDuiHostWnd)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()
	};

	int DuiMessageBox( HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType )
{
	TiXmlElement *pXmlTempl=DuiSystem::getSingleton().GetMsgBoxTemplate();
	if(!pXmlTempl) return -1;
	TiXmlElement * pXmlBody=pXmlTempl->FirstChildElement("body");
	DUIASSERT(pXmlBody);
	
	CDuiMessageBox duiHost;
	duiHost.Create(NULL,NULL,WS_POPUPWINDOW,0,0,0,10,10,NULL);
	duiHost.SetXml(pXmlTempl);
	
	
	switch(uType&0x0F)
	{
	case MB_ABORTRETRYIGNORE:
		{
			duiHost.FindChildByCmdID(IDC_MSGBOX_BTN1PANEL)->SetVisible(FALSE);
			duiHost.FindChildByCmdID(IDC_MSGBOX_BTN2PANEL)->SetVisible(FALSE);
			CDuiWindow *pBtnPanel=duiHost.FindChildByCmdID(IDC_MSGBOX_BTN3PANEL);
			pBtnPanel->SetVisible(TRUE);
			CDuiWindow *pBtn=pBtnPanel->FindChildByCmdID(IDC_MSGBOX_BTN1);
			pBtn->SetInnerText(_T("中止"));pBtn->SetCmdID(IDABORT);
			pBtn=pBtnPanel->FindChildByCmdID(IDC_MSGBOX_BTN2);
			pBtn->SetInnerText(_T("重试"));pBtn->SetCmdID(IDRETRY);
			pBtn=pBtnPanel->FindChildByCmdID(IDC_MSGBOX_BTN3);
			pBtn->SetInnerText(_T("忽略"));pBtn->SetCmdID(IDIGNORE);
		}
		break;
	case MB_YESNOCANCEL:
		{
			duiHost.FindChildByCmdID(IDC_MSGBOX_BTN1PANEL)->SetVisible(FALSE);
			duiHost.FindChildByCmdID(IDC_MSGBOX_BTN2PANEL)->SetVisible(FALSE);
			CDuiWindow *pBtnPanel=duiHost.FindChildByCmdID(IDC_MSGBOX_BTN3PANEL);
			pBtnPanel->SetVisible(TRUE);
			CDuiWindow *pBtn=pBtnPanel->FindChildByCmdID(IDC_MSGBOX_BTN1);
			pBtn->SetInnerText(_T("是"));pBtn->SetCmdID(IDYES);
			pBtn=pBtnPanel->FindChildByCmdID(IDC_MSGBOX_BTN2);
			pBtn->SetInnerText(_T("否"));pBtn->SetCmdID(IDNO);
			pBtn=pBtnPanel->FindChildByCmdID(IDC_MSGBOX_BTN3);
			pBtn->SetInnerText(_T("取消"));pBtn->SetCmdID(IDCANCEL);
		}
		break;
	case MB_OKCANCEL:
		{
			duiHost.FindChildByCmdID(IDC_MSGBOX_BTN1PANEL)->SetVisible(FALSE);
			duiHost.FindChildByCmdID(IDC_MSGBOX_BTN3PANEL)->SetVisible(FALSE);

			CDuiWindow *pBtnPanel=duiHost.FindChildByCmdID(IDC_MSGBOX_BTN2PANEL);
			pBtnPanel->SetVisible(TRUE);

			CDuiWindow *pBtn=pBtnPanel->FindChildByCmdID(IDC_MSGBOX_BTN1);
			pBtn->SetInnerText(_T("确定"));	pBtn->SetCmdID(IDOK);
			pBtn=pBtnPanel->FindChildByCmdID(IDC_MSGBOX_BTN2);
			pBtn->SetInnerText(_T("取消"));	pBtn->SetCmdID(IDCANCEL);
		}
		break;
	case MB_YESNO:
		{
			duiHost.FindChildByCmdID(IDC_MSGBOX_BTN1PANEL)->SetVisible(FALSE);
			duiHost.FindChildByCmdID(IDC_MSGBOX_BTN3PANEL)->SetVisible(FALSE);

			CDuiWindow *pBtnPanel=duiHost.FindChildByCmdID(IDC_MSGBOX_BTN2PANEL);
			pBtnPanel->SetVisible(TRUE);

			CDuiWindow *pBtn=pBtnPanel->FindChildByCmdID(IDC_MSGBOX_BTN1);
			pBtn->SetInnerText(_T("是"));	pBtn->SetCmdID(IDYES);
			pBtn=pBtnPanel->FindChildByCmdID(IDC_MSGBOX_BTN2);
			pBtn->SetInnerText(_T("否"));	pBtn->SetCmdID(IDNO);
		}
		break;
	case MB_RETRYCANCEL:
		{
			duiHost.FindChildByCmdID(IDC_MSGBOX_BTN1PANEL)->SetVisible(FALSE);
			duiHost.FindChildByCmdID(IDC_MSGBOX_BTN3PANEL)->SetVisible(FALSE);

			CDuiWindow *pBtnPanel=duiHost.FindChildByCmdID(IDC_MSGBOX_BTN2PANEL);
			pBtnPanel->SetVisible(TRUE);

			CDuiWindow *pBtn=pBtnPanel->FindChildByCmdID(IDC_MSGBOX_BTN1);
			pBtn->SetInnerText(_T("重试"));	pBtn->SetCmdID(IDRETRY);
			pBtn=pBtnPanel->FindChildByCmdID(IDC_MSGBOX_BTN2);
			pBtn->SetInnerText(_T("取消"));	pBtn->SetCmdID(IDCANCEL);
		}
		break;
	case MB_OK:
		{
			duiHost.FindChildByCmdID(IDC_MSGBOX_BTN2PANEL)->SetVisible(FALSE);
			duiHost.FindChildByCmdID(IDC_MSGBOX_BTN3PANEL)->SetVisible(FALSE);

			CDuiWindow *pBtnPanel=duiHost.FindChildByCmdID(IDC_MSGBOX_BTN1PANEL);
			pBtnPanel->SetVisible(TRUE);
			CDuiWindow *pBtn=pBtnPanel->FindChildByCmdID(IDC_MSGBOX_BTN1);
			pBtn->SetInnerText(_T("确定"));	pBtn->SetCmdID(IDOK);
		}
		break;
	default:
		DUIASSERT(FALSE);
		break;
	}
	const char *pszFrameAttr=pXmlBody->Attribute("frame_size");
	CRect rcFrame;
	sscanf(pszFrameAttr,"%d,%d,%d,%d",&rcFrame.left,&rcFrame.top,&rcFrame.right,&rcFrame.bottom);
	CSize szMin;
	const char *pszMinAttr=pXmlBody->Attribute("min_size");
	sscanf(pszMinAttr,"%d,%d",&szMin.cx,&szMin.cy);
	
	CDuiWindow * pTitle= duiHost.FindChildByCmdID(IDC_MSGBOX_TITLE);
	DUIASSERT(pTitle);
	pTitle->SetInnerText(lpCaption?lpCaption:_T("提示"));

	CDuiWindow * pMsg= duiHost.FindChildByCmdID(IDC_MSGBOX_TEXT);
	DUIASSERT(pMsg);
	pMsg->SetInnerText(lpText);
	
	CRect rcText;
	pMsg->GetRect(&rcText);

	CSize szWnd;
	szWnd.cx=max(szMin.cx,rcText.Width()+rcFrame.left+rcFrame.right);
	szWnd.cy=max(szMin.cy,rcText.Height()+rcFrame.top+rcFrame.bottom);
	
	duiHost.SetWindowPos(0,0,0,szWnd.cx,szWnd.cy,SWP_NOZORDER|SWP_NOMOVE|SWP_NOSENDCHANGING|SWP_NOACTIVATE);

	CDuiIconWnd *pIcon=(CDuiIconWnd *)duiHost.FindChildByCmdID(IDC_MSGBOX_ICON);
	DUIASSERT(pIcon);
	switch(uType&0xF0)
	{
	case MB_ICONEXCLAMATION:
		pIcon->AttachIcon(LoadIcon(NULL,IDI_EXCLAMATION));
// 		pIcon->AttachIcon((HICON)LoadImage(NULL,IDI_EXCLAMATION,IMAGE_ICON,0,0,0 ));
		break;
	case MB_ICONINFORMATION:
		pIcon->AttachIcon(LoadIcon(NULL,IDI_INFORMATION));
// 		pIcon->AttachIcon((HICON)LoadImage(NULL,IDI_INFORMATION,IMAGE_ICON,32,32,LR_DEFAULTCOLOR ));
		break;
	case MB_ICONQUESTION:
		pIcon->AttachIcon(LoadIcon(NULL,IDI_QUESTION));
// 		pIcon->AttachIcon((HICON)LoadImage(NULL,IDI_QUESTION,IMAGE_ICON,32,32,LR_DEFAULTCOLOR ));
		break;
	case MB_ICONHAND:
		pIcon->AttachIcon(LoadIcon(NULL,IDI_HAND));
// 		pIcon->AttachIcon((HICON)LoadImage(NULL,MB_ICONHAND,IMAGE_ICON,32,32,LR_DEFAULTCOLOR ));
		break;
	}
	
	return duiHost.DoModal(hWnd);
}

}//endof namespace 
