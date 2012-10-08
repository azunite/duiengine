//////////////////////////////////////////////////////////////////////////
//  Class Name: CDuiItemPanel
// Description: A Framework wrapping frame to be used in a duiwindow.
//     Creator: Huang Jianxiong
//     Version: 2011.10.20 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma  once
#include "duistd.h"
#include "duiItempanel.h"

#include "duiwndnotify.h"

#pragma warning(disable:4018)

namespace DuiEngine{


CDuiItemPanel::CDuiItemPanel(CDuiWindow *pFrameHost,TiXmlElement *pXml):m_pFrmHost(pFrameHost),m_dwData(0),m_crBk(CLR_INVALID),m_crSelBk(RGB(0,0,128))
{
	ATLASSERT(m_pFrmHost);
	SetContainer(this);
	Load(pXml);
}

void CDuiItemPanel::OnFinalRelease()
{
	AddRef();//防止重复进入该函数
	DuiSendMessage(WM_DESTROY);
	__super::OnFinalRelease();
}

LRESULT CDuiItemPanel::DoFrameEvent(UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	AddRef();
	LRESULT lRet=__super::DoFrameEvent(uMsg,wParam,lParam);
	if(IsMsgHandled())
	{
		DUINMITEMMOUSEEVENT nms;
		nms.hdr.code=DUINM_ITEMMOUSEEVENT;
		nms.hdr.hwndFrom=NULL;
		nms.hdr.idFrom=m_pFrmHost->GetCmdID();
		nms.pItem=this;
		nms.uMsg=uMsg;
		nms.wParam=wParam;
		nms.lParam=lParam;
		m_pFrmHost->DuiNotify((LPNMHDR)&nms);
	}
	Release();
	return lRet;
}

LRESULT CDuiItemPanel::OnDuiNotify(LPNMHDR pHdr)
{
	DUINMITEMNOTIFY nmsItem;
	nmsItem.hdr.code=DUINM_LBITEMNOTIFY;
	nmsItem.hdr.hwndFrom=NULL;
	nmsItem.hdr.idFrom=m_pFrmHost->GetCmdID();
	nmsItem.pItem=this;
	nmsItem.pHostDuiWin=(CDuiWindow*)m_pFrmHost;
	nmsItem.pOriginHdr=pHdr;
	return m_pFrmHost->DuiNotify((LPNMHDR)&nmsItem);
}

CRect CDuiItemPanel::GetContainerRect(){return m_rcWindow;}

HDC CDuiItemPanel::OnGetDuiDC(CRect & rc,DWORD gdcFlags)
{
	CRect rcItem=GetItemRect();
	CRect rcInvalid=rc;
	rcInvalid.OffsetRect(rcItem.TopLeft());
	CDCHandle dc=m_pFrmHost->GetContainer()->OnGetDuiDC(rcInvalid,gdcFlags);
	dc.OffsetViewportOrg(rcItem.left,rcItem.top);
	return dc;
}

void CDuiItemPanel::OnReleaseDuiDC(HDC hdc,CRect &rc,DWORD gdcFlags)
{
	CRect rcItem=GetItemRect();
	CDCHandle dc(hdc);
	dc.OffsetViewportOrg(-rcItem.left,-rcItem.top);
	CRect rcNew=rc;
	rcNew.OffsetRect(rcItem.TopLeft());
	m_pFrmHost->GetContainer()->OnReleaseDuiDC(hdc,rcNew,gdcFlags);
}

void CDuiItemPanel::OnRedraw(const CRect &rc)
{
	if(m_pFrmHost->IsUpdateLocked()) return;

	CRect rcItem=GetItemRect();
	if(!rcItem.IsRectNull() && m_pFrmHost->IsVisible(TRUE))
	{
		CRect rcInvalid=rc;
		rcInvalid.OffsetRect(rcItem.TopLeft());
		HDC hdc=m_pFrmHost->GetDuiDC(&rcInvalid);
		m_pFrmHost->DuiSendMessage(WM_ERASEBKGND,(WPARAM)hdc);
		CDCHandle dc(hdc);
		dc.OffsetViewportOrg(rcItem.left,rcItem.top);
		CRgn rgn;
		rgn.CreateRectRgnIndirect(&rc);
		RedrawRegion(dc,rgn);
		rgn.DeleteObject();
		dc.OffsetViewportOrg(-rcItem.left,-rcItem.top);
		m_pFrmHost->ReleaseDuiDC(hdc);
	}
}

BOOL CDuiItemPanel::OnReleaseDuiCapture()
{
	if(!__super::OnReleaseDuiCapture()) return FALSE;
	m_pFrmHost->DuiSendMessage(UM_ONITEMSETCAPTURE,0);
	return TRUE;
}

HDUIWND CDuiItemPanel::OnSetDuiCapture(HDUIWND hDuiWNd)
{
	m_pFrmHost->DuiSendMessage(UM_ONITEMSETCAPTURE,(WPARAM)this);
	return __super::OnSetDuiCapture(hDuiWNd);
}

HWND CDuiItemPanel::GetHostHwnd()
{
	return m_pFrmHost->GetContainer()->GetHostHwnd();
}

BOOL CDuiItemPanel::IsTranslucent()
{
	return m_pFrmHost->GetContainer()->IsTranslucent();
}

BOOL CDuiItemPanel::DuiCreateCaret( HBITMAP hBmp,int nWidth,int nHeight )
{
	return m_pFrmHost->GetContainer()->DuiCreateCaret(hBmp,nWidth,nHeight);
}

BOOL CDuiItemPanel::DuiShowCaret( BOOL bShow )
{
	return m_pFrmHost->GetContainer()->DuiShowCaret(bShow);
}

BOOL CDuiItemPanel::DuiSetCaretPos( int x,int y )
{
	return m_pFrmHost->GetContainer()->DuiSetCaretPos(x,y);
}

void CDuiItemPanel::ModifyItemState(DWORD dwStateAdd, DWORD dwStateRemove)
{
	ModifyState(dwStateAdd,dwStateRemove,FALSE);
}

HDUIWND CDuiItemPanel::DuiGetHWNDFromPoint(POINT ptHitTest, BOOL bOnlyText)
{
	HDUIWND hRet=__super::DuiGetHWNDFromPoint(ptHitTest,bOnlyText);
	if(hRet==m_hDuiWnd) hRet=NULL;
	return hRet;
}

void CDuiItemPanel::Draw(CDCHandle dc,const CRect & rc)
{
	CRgn rgnNull;
		if((m_dwState & DuiWndState_Check) && m_crSelBk != CLR_INVALID) SetBkColor(m_crSelBk);
	else SetBkColor(m_crBk);

	dc.OffsetViewportOrg(rc.left,rc.top);
	RedrawRegion(dc,rgnNull);
	dc.OffsetViewportOrg(-rc.left,-rc.top);
}

void CDuiItemPanel::SetSkin(CDuiSkinBase *pSkin)
{
	m_pBgSkin=pSkin;
}

void CDuiItemPanel::SetColor(COLORREF crBk,COLORREF crSelBk)
{
	m_crBk=crBk;
	m_crSelBk=crSelBk;
}

BOOL CDuiItemPanel::NeedRedrawWhenStateChange(){return TRUE;}

CRect CDuiItemPanel::GetItemRect()
{
	CRect rcRet;
	m_pFrmHost->DuiSendMessage(UM_ONITEMGETRECT,(WPARAM)this,(LPARAM)&rcRet);
	return rcRet;
}
void CDuiItemPanel::SetItemCapture(BOOL bCapture)
{
	m_pFrmHost->DuiSendMessage(UM_ONITEMSETCAPTURE,0,(LPARAM)(bCapture?this:NULL));
}
void CDuiItemPanel::SetItemData(DWORD dwData){m_dwData=dwData;}
DWORD CDuiItemPanel::GetItemData(){return m_dwData;}

BOOL CDuiItemPanel::OnUpdateToolTip( HDUIWND hCurTipHost,HDUIWND &hNewTipHost,CRect &rcTip,CString &strTip )
{
	if(hCurTipHost==m_hHover) return FALSE;

	CDuiWindow *pHover=DuiWindowManager::GetWindow(m_hHover);
	if(!pHover || pHover->IsDisabled(TRUE))
	{
		hNewTipHost=NULL;
		return TRUE;
	}
	BOOL bRet=pHover->OnUpdateToolTip(hCurTipHost,hNewTipHost,rcTip,strTip);
	if(bRet)
	{
		CRect rcItem=GetItemRect();
		rcTip.OffsetRect(rcItem.TopLeft());
	}
	return bRet;
}

}//namespace DuiEngine