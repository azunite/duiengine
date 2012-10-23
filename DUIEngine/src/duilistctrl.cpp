//////////////////////////////////////////////////////////////////////////
//  Class Name: CDuiListBox
// Description: A DuiWindow Based ListBox Control. Can contain control as an item
//     Creator: Huang Jianxiong
//     Version: 2011.8.27 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma  once
#include "duistd.h"
#include "duilistctrl.h"
#include "DuiSystem.h"
#include "mybuffer.h"

#pragma warning(disable:4018)
#pragma warning(disable:4267)

namespace DuiEngine{


CDuiListBox::CDuiListBox()
: m_nItemHei(20)
, m_iScrollSpeed(-1)
, m_iSelItem(-1)
, m_iHoverItem(-1)
, m_pCapturedFrame(NULL)
, m_pItemTemplate(NULL)
, m_crItemBg(CLR_INVALID)
, m_crItemBg2(CLR_INVALID)
, m_crItemSelBg(CLR_INVALID)
, m_pItemSkin(NULL)
, m_bHotTrack(FALSE)
{
}

CDuiListBox::~CDuiListBox()
{
	if(m_pItemTemplate) delete m_pItemTemplate;
}


void CDuiListBox::DeleteAllItems(BOOL bUpdate/*=TRUE*/)
{
	for(int i=0;i<GetItemCount();i++)
	{
		m_arrItems[i]->Release();
	}
	m_arrItems.clear();
	m_iSelItem=-1;
	m_iHoverItem=-1;
	m_pCapturedFrame=NULL;
	ReleaseDuiCapture();

	SetViewSize(CSize(0,0));
	NotifyInvalidate();
}

void CDuiListBox::DeleteItem(int iItem)
{
	if(iItem<0 || iItem>=GetItemCount()) return;
	if(m_pCapturedFrame == m_arrItems[iItem])
	{
		m_pCapturedFrame=NULL;
		ReleaseDuiCapture();
	}

	m_arrItems[iItem]->Release();
	m_arrItems.erase(m_arrItems.begin()+iItem);

	if(m_iSelItem==iItem) m_iSelItem=-1;
	else if(m_iSelItem>iItem) m_iSelItem--;
	if(m_iHoverItem==iItem) m_iHoverItem=-1;
	else if(m_iHoverItem>iItem) m_iHoverItem--;

	CRect rcClient;
	CDuiWindow::GetClient(&rcClient);
	CSize szView(rcClient.Width(),GetItemCount()*m_nItemHei);
	if(szView.cy>rcClient.Height()) szView.cx-=m_nSbWid;
	SetViewSize(szView);
}

int CDuiListBox::InsertItem(int iItem,CDuiItemPanel *pItemObj,DWORD dwData/*=0*/)
{
	if(iItem==-1 || iItem>=GetItemCount())
	{
		iItem=GetItemCount();
	}
	if (m_crItemBg2 == CLR_INVALID || iItem % 2 == 0)
	{
		pItemObj->SetColor(m_crItemBg,m_crItemSelBg);
	}
	else
	{
		pItemObj->SetColor(m_crItemBg2, m_crItemSelBg);
	}
	pItemObj->SetItemData(dwData);		
	pItemObj->Move(CRect(0,0,m_rcClient.Width(),m_nItemHei));
	pItemObj->SetSkin(m_pItemSkin);

	m_arrItems.insert(m_arrItems.begin()+iItem,pItemObj);

	if(m_iSelItem>=iItem) m_iSelItem++;
	if(m_iHoverItem>=iItem) m_iHoverItem++;

	CRect rcClient;
	CDuiWindow::GetClient(&rcClient);
	CSize szView(rcClient.Width(),GetItemCount()*m_nItemHei);
	if(szView.cy>rcClient.Height()) szView.cx-=m_nSbWid;
	SetViewSize(szView);

	return iItem;
}

int CDuiListBox::InsertItem(int iItem,LPCWSTR pszXml,DWORD dwData/*=0*/)
{
	CStringA strUtf8=CW2A(pszXml,CP_UTF8);
	TiXmlDocument xmlDoc;
	xmlDoc.Parse(strUtf8);
	if(xmlDoc.Error()) return NULL;
	CDuiItemPanel *pItem=new CDuiItemPanel(this,xmlDoc.RootElement());
	return InsertItem(iItem,pItem,dwData);
}


CDuiPanel * CDuiListBox::InsertPanelItem(int iItem,LPCWSTR pszXml,DWORD dwData/*=0*/)
{
	CStringA strUtf8=CW2A(pszXml,CP_UTF8);
	TiXmlDocument xmlDoc;
	xmlDoc.Parse(strUtf8);
	if(xmlDoc.Error()) return NULL;
	CDuiItemPanel *pRet=new CDuiItemPanel(this,xmlDoc.RootElement());
	InsertItem(iItem,pRet,dwData);
	return pRet;
}

void CDuiListBox::SetCurSel(int iItem)
{
	if(m_iSelItem==iItem) return;
	if(m_iSelItem!=-1)
	{
		m_arrItems[m_iSelItem]->ModifyItemState(0,DuiWndState_Check); 
	}
	if(iItem>=0 && iItem<GetItemCount())
	{
		m_arrItems[iItem]->ModifyItemState(DuiWndState_Check,0);
		m_iSelItem=iItem;
		if(IsVisible(TRUE)) RedrawItem(iItem);
	}
}

void CDuiListBox::EnsureVisible( int iItem )
{
	if(iItem<0 || iItem>=GetItemCount()) return;
	int iFirstVisible=m_ptOrgin.y/m_nItemHei;
	CRect rcClient;
	GetClient(&rcClient);
	int nVisibleItems=rcClient.Height()/m_nItemHei;
	if(iItem<iFirstVisible || iItem> iFirstVisible+nVisibleItems-1)
	{
		int nOffset=GetScrollPos(TRUE);
		if(iItem<iFirstVisible) nOffset=(iItem-iFirstVisible)*m_nItemHei;
		else nOffset=(iItem - iFirstVisible-nVisibleItems +1)*m_nItemHei;
		nOffset-=nOffset%m_nItemHei;//让当前行刚好显示
		OnScroll(TRUE,SB_THUMBPOSITION,nOffset);
	}
}

int CDuiListBox::GetCurSel()
{
	return m_iSelItem;
}

LRESULT CDuiListBox::OnGetItemRect(UINT,WPARAM wParam,LPARAM lParam)
{
	CDuiItemPanel *pItemObj=(CDuiItemPanel*)wParam;
	LPRECT pRcItem=(LPRECT)lParam;

	CRect rcClient;
	GetClient(&rcClient);

	int iFirstVisible=m_ptOrgin.y/m_nItemHei;
	int nPageItems=(rcClient.Height()+m_nItemHei-1)/m_nItemHei+1;

	for(int iItem = iFirstVisible; iItem<GetItemCount() && iItem <iFirstVisible+nPageItems; iItem++)
	{
		if(m_arrItems[iItem] == pItemObj)
		{
			CRect rcRet(0,0,rcClient.Width(),m_nItemHei);
			rcRet.OffsetRect(rcClient.left,rcClient.top-m_ptOrgin.y+iItem*m_nItemHei);
			*pRcItem=rcRet;
			break;
		}
	}
	return 1;
}

LRESULT CDuiListBox::OnSetItemCapture(UINT uMsg,WPARAM wParam, LPARAM lParam)
{
	m_pCapturedFrame= (CDuiItemPanel*)wParam;
	if(m_pCapturedFrame) SetDuiCapture();
	else ReleaseDuiCapture();
	return 0;
}

int CDuiListBox::GetItemObjIndex(CDuiPanel *pItemObj)
{
	if(m_iSelItem!=-1 && m_arrItems[m_iSelItem]==pItemObj) return m_iSelItem;

	int iFirstVisible=m_ptOrgin.y/m_nItemHei;
	int nPageItems=(m_rcWindow.Height()+m_nItemHei-1)/m_nItemHei+1;

	int iItem;
	for(iItem=iFirstVisible ; iItem<GetItemCount() && iItem <iFirstVisible+nPageItems; iItem++)
	{
		if(m_arrItems[iItem] == pItemObj) return iItem;
	}
	for(iItem=0;iItem<iFirstVisible;iItem++)
	{
		if(m_arrItems[iItem] == pItemObj) return iItem;
	}
	for(iItem=iFirstVisible+nPageItems;iItem<GetItemCount();iItem++)
	{
		if(m_arrItems[iItem] == pItemObj) return iItem;
	}
	return -1;
}


CDuiPanel * CDuiListBox::GetDuiItem(int iItem)
{
	if(iItem<0 || iItem>= GetItemCount()) return NULL;
	return GetDuiItem(m_arrItems[iItem]);
}
CDuiPanel * CDuiListBox::GetDuiItem(CDuiPanel *pItem)
{
	return pItem;
}

DWORD CDuiListBox::GetItemData(int iItem)
{
	DUIASSERT(iItem>=0 || iItem< GetItemCount());
	return m_arrItems[iItem]->GetItemData();
}


BOOL CDuiListBox::SetItemCount(DWORD *pData,int nItems)
{
	if(!m_pItemTemplate) return FALSE;
	DeleteAllItems();
	for(int i=0;i<nItems;i++)
	{
		InsertItem(-1,new CDuiItemPanel(this,m_pItemTemplate),pData?pData[i]:0);
	}
	NotifyInvalidate();
	return TRUE;
}

int CDuiListBox::GetItemCount() {return m_arrItems.size();}

void CDuiListBox::RedrawItem(int iItem)
{
	if(!IsVisible(TRUE)) return;
	CRect rcClient;
	GetClient(&rcClient);
	int iFirstVisible=m_ptOrgin.y/m_nItemHei;
	int nPageItems=(rcClient.Height()+m_nItemHei-1)/m_nItemHei+1;

	if(iItem>=iFirstVisible && iItem<GetItemCount() && iItem<iFirstVisible+nPageItems)
	{
		CRect rcItem(0,0,rcClient.Width(),m_nItemHei);
		rcItem.OffsetRect(0,m_nItemHei*iItem-m_ptOrgin.y);
		rcItem.OffsetRect(rcClient.TopLeft());
		rcItem.IntersectRect(rcItem,rcClient);
		CDCHandle dc=GetDuiDC(&rcItem,OLEDC_PAINTBKGND);
		DuiDCPaint duiDC;
		BeforePaint(dc,duiDC);

		DuiSendMessage(WM_ERASEBKGND,(WPARAM)(HDC)dc);
		DrawItem(dc,rcItem,iItem);

		AfterPaint(dc,duiDC);
		ReleaseDuiDC(dc);
	}
}

//自动修改pt的位置为相对当前项的偏移量
int CDuiListBox::HitTest(CPoint &pt)
{
	CRect rcClient;
	GetClient(&rcClient);
	CPoint pt2=pt;
	pt2.y -= rcClient.top - m_ptOrgin.y;
	int nRet=pt2.y/m_nItemHei;
	if(nRet >= GetItemCount()) nRet=-1;
	else
	{
		pt.x-=rcClient.left;
		pt.y=pt2.y%m_nItemHei;
	}

	return nRet;
}

int CDuiListBox::GetScrollLineSize(BOOL bVertical) 
{
	return m_iScrollSpeed >0 ? m_iScrollSpeed : m_nItemHei;
}

void CDuiListBox::OnPaint(CDCHandle dc)
{
	if(IsUpdateLocked()) return;

	DuiDCPaint duiDC;
	BeforePaint(dc,duiDC);

	int iFirstVisible=m_ptOrgin.y/m_nItemHei;
	int nPageItems=(m_rcClient.Height()+m_nItemHei-1)/m_nItemHei+1;

	for(int iItem = iFirstVisible; iItem<GetItemCount() && iItem <iFirstVisible+nPageItems; iItem++)
	{
		CRect rcItem(0,0,m_rcClient.Width(),m_nItemHei);
		rcItem.OffsetRect(0,m_nItemHei*iItem-m_ptOrgin.y);
		rcItem.OffsetRect(m_rcClient.TopLeft());
		DrawItem(dc,rcItem,iItem);
	}

	AfterPaint(dc,duiDC);
}

LRESULT CDuiListBox::OnNcCalcSize(BOOL bCalcValidRects, LPARAM lParam)
{
	__super::OnNcCalcSize(bCalcValidRects,lParam);
	CRect rcClient;
	GetClient(&rcClient);
	for(int i=0;i<GetItemCount();i++)
		m_arrItems[i]->Move(CRect(0,0,rcClient.Width(),m_nItemHei));
	NotifyInvalidate();
	return 0;
}

void CDuiListBox::DrawItem(CDCHandle & dc, CRect & rc, int iItem)
{
	CDuiItemPanel *pItem=m_arrItems[iItem];
	DUINMGETLBDISPINFO nms;
	nms.hdr.code    = DUINM_GETLBDISPINFO;
	nms.hdr.hwndFrom = NULL;
	nms.hdr.idFrom  = GetCmdID();
	nms.bHover      = iItem == m_iHoverItem;
	nms.bSelect     = iItem == m_iSelItem;
	nms.nListItemID = iItem;
	nms.pItem = pItem;
	nms.pHostDuiWin   = this;
	LockUpdate();
	GetContainer()->OnDuiNotify((LPNMHDR)&nms);
	UnlockUpdate();
	pItem->Draw(dc,rc);
}

BOOL CDuiListBox::Load(TiXmlElement* pTiXmlElem)
{
	if (!__super::Load(pTiXmlElem))
		return FALSE;

	int			nChildSrc=-1;
	pTiXmlElem->Attribute("itemsrc",&nChildSrc);

	if (nChildSrc == -1)
		return TRUE;

	DuiResProviderBase *pRes=DuiSystem::getSingleton().GetResProvider();
	if(!pRes) return FALSE;

	DWORD dwSize=pRes->GetRawBufferSize(DUIRES_XML_TYPE,nChildSrc);
	if(dwSize==0) return FALSE;

	CMyBuffer<char> strXml;
	strXml.Allocate(dwSize);
	pRes->GetRawBuffer(DUIRES_XML_TYPE,nChildSrc,strXml,dwSize);

	TiXmlDocument xmlDoc;
	{
		xmlDoc.Parse(strXml, NULL, TIXML_ENCODING_UTF8);
	}
	if (xmlDoc.Error())
	{
		DUIASSERT(FALSE);
		return FALSE;
	}

	TiXmlElement *pSubTiElement = xmlDoc.RootElement();
	return LoadChildren(pSubTiElement);
}

BOOL CDuiListBox::LoadChildren(TiXmlElement* pTiXmlChildElem)
{
	if(!pTiXmlChildElem) return TRUE;
	TiXmlElement* pParent=(TiXmlElement*)pTiXmlChildElem->Parent();
	TiXmlElement* pTemplate=(TiXmlElement*)pParent->FirstChildElement("template");
	if(pTemplate)
	{
		m_pItemTemplate=(TiXmlElement*)pTemplate->Clone();
	}
	TiXmlElement* pItems=(TiXmlElement*)pParent->FirstChildElement("items");
	if(pItems)
	{
		TiXmlElement *pChild=pItems->FirstChildElement();
		while(pChild)
		{
			int dwData=0;
			pChild->Attribute("itemdata",&dwData);
			if(strcmp(pChild->Value(),"dlg")==0 || strcmp(pChild->Value(),"item")==0)
			{
				InsertItem(-1,new CDuiItemPanel(this,pChild),dwData);
			}
			pChild=pChild->NextSiblingElement();
		}
		int nSelItem=-1;
		pItems->Attribute("cursel",&nSelItem);
		SetCurSel(nSelItem);
	}

	return TRUE;
}


void CDuiListBox::NotifySelChange( int nOldSel,int nNewSel ,UINT uMsg)
{
	DUINMLBSELCHANGE nms;
	nms.hdr.hwndFrom=NULL;
	nms.hdr.idFrom=GetCmdID();
	nms.nOldSel=nOldSel;
	nms.nNewSel=nNewSel;
	nms.uMsg=uMsg;
	nms.uHoverID=0;
	if(nNewSel!=-1)
	{
		CDuiWindow *pHover=DuiWindowManager::GetWindow(m_arrItems[nNewSel]->GetDuiHover());
		if(pHover) nms.uHoverID=pHover->GetCmdID();
	}

	nms.hdr.code=DUINM_LBSELCHANGING;
	if(S_OK!=DuiNotify((LPNMHDR)&nms)) return ;

	if(nOldSel!=-1)
	{
		m_arrItems[nOldSel]->ModifyItemState(0,DuiWndState_Check);
		RedrawItem(nOldSel);
	}
	m_iSelItem=nNewSel;
	if(m_iSelItem!=-1)
	{
		m_arrItems[m_iSelItem]->ModifyItemState(DuiWndState_Check,0);
		RedrawItem(m_iSelItem);
	}

	nms.hdr.idFrom=GetCmdID();
	nms.hdr.code=DUINM_LBSELCHANGED;
	DuiNotify((LPNMHDR)&nms);			
}

void CDuiListBox::OnLButtonDown(UINT nFlags,CPoint pt)
{
	if(m_pCapturedFrame)
	{
		CRect rcItem=m_pCapturedFrame->GetItemRect();
		if(!rcItem.IsRectEmpty())
		{
			pt.Offset(-rcItem.left,-rcItem.top);
			m_pCapturedFrame->DoFrameEvent(WM_LBUTTONDOWN,nFlags,MAKELPARAM(pt.x,pt.y));;
			return;
		}
	}
	m_iHoverItem=HitTest(pt);

	if(m_iHoverItem!=-1)
	{//pt 已经在HitTest中被修改过
		m_arrItems[m_iHoverItem]->DoFrameEvent(WM_LBUTTONDOWN,nFlags,MAKELPARAM(pt.x,pt.y));
	}
}

void CDuiListBox::OnLButtonUp(UINT nFlags,CPoint pt)
{
	if(m_pCapturedFrame)
	{
		CRect rcItem=m_pCapturedFrame->GetItemRect();
		if(!rcItem.IsRectEmpty())
		{
			pt.Offset(-rcItem.left,-rcItem.top);
			m_pCapturedFrame->DoFrameEvent(WM_LBUTTONUP,nFlags,MAKELPARAM(pt.x,pt.y));
			return;
		}
	}
	m_iHoverItem=HitTest(pt);
	if(m_iHoverItem!=-1)
	{
		m_arrItems[m_iHoverItem]->DoFrameEvent(WM_LBUTTONUP,nFlags,MAKELPARAM(pt.x,pt.y));
	}

	if(m_iHoverItem!=m_iSelItem || m_bHotTrack)
		NotifySelChange(m_iSelItem,m_iHoverItem,WM_LBUTTONUP);

}

void CDuiListBox::OnLButtonDbClick(UINT nFlags,CPoint pt)
{
	if(m_pCapturedFrame)
	{
		CRect rcItem=m_pCapturedFrame->GetItemRect();
		if(!rcItem.IsRectEmpty())
		{
			pt.Offset(-rcItem.left,-rcItem.top);
			m_pCapturedFrame->DoFrameEvent(WM_LBUTTONDBLCLK,nFlags,MAKELPARAM(pt.x,pt.y));
			return;
		}
	}
	m_iHoverItem=HitTest(pt);
	if(m_iHoverItem!=-1)
	{
		m_arrItems[m_iHoverItem]->DoFrameEvent(WM_LBUTTONDBLCLK,nFlags,MAKELPARAM(pt.x,pt.y));
	}else
	{
		DUINMITEMMOUSEEVENT nms;
		nms.hdr.code=DUINM_ITEMMOUSEEVENT;
		nms.hdr.hwndFrom=NULL;
		nms.hdr.idFrom=GetCmdID();
		nms.pItem=NULL;
		nms.uMsg=WM_LBUTTONDBLCLK;
		nms.wParam=nFlags;
		nms.lParam=MAKELPARAM(pt.x,pt.y);
		DuiNotify((LPNMHDR)&nms);
	}

}

void CDuiListBox::OnMouseMove(UINT nFlags,CPoint pt)
{
	if(m_pCapturedFrame)
	{
		CRect rcItem=m_pCapturedFrame->GetItemRect();
		if(!rcItem.IsRectEmpty())
		{
			pt.Offset(-rcItem.left,-rcItem.top);
			m_pCapturedFrame->DoFrameEvent(WM_MOUSEMOVE,nFlags,MAKELPARAM(pt.x,pt.y));
			return;
		}
	}
	int nHitTest=HitTest(pt);
	if(nHitTest!=m_iHoverItem)
	{
		if(m_iHoverItem!=-1)
			m_arrItems[m_iHoverItem]->DoFrameEvent(WM_MOUSELEAVE,0,0);
		m_iHoverItem=nHitTest;
		if(m_iHoverItem!=-1)
			m_arrItems[m_iHoverItem]->DoFrameEvent(WM_MOUSEHOVER,0,0);
	}
	if(m_iHoverItem!=-1)
	{
		m_arrItems[m_iHoverItem]->DoFrameEvent(WM_MOUSEMOVE,nFlags,MAKELPARAM(pt.x,pt.y));
	}
	if(m_bHotTrack && m_iHoverItem!=m_iSelItem)
		NotifySelChange(m_iSelItem,m_iHoverItem,WM_MOUSEMOVE);
}

void CDuiListBox::OnMouseLeave()
{
	if(m_pCapturedFrame)
	{
		m_pCapturedFrame->DoFrameEvent(WM_MOUSELEAVE,0,0);
	}
	if(m_iHoverItem!=-1)
	{
		m_arrItems[m_iHoverItem]->DoFrameEvent(WM_MOUSELEAVE,0,0);
		m_iHoverItem=-1;
	}
}

BOOL CDuiListBox::OnDuiSetCursor(const CPoint &pt)
{
	BOOL bRet=FALSE;
	if(m_pCapturedFrame)
	{
		CRect rcItem=m_pCapturedFrame->GetItemRect();
		bRet=m_pCapturedFrame->DoFrameEvent(WM_SETCURSOR,0,MAKELPARAM(pt.x-rcItem.left,pt.y-rcItem.top))!=0;
	}else if(m_iHoverItem!=-1)
	{
		CRect rcItem=m_arrItems[m_iHoverItem]->GetItemRect();
		bRet=m_arrItems[m_iHoverItem]->DoFrameEvent(WM_SETCURSOR,0,MAKELPARAM(pt.x-rcItem.left,pt.y-rcItem.top))!=0;
	}
	if(!bRet)
	{
		bRet=__super::OnDuiSetCursor(pt);
	}
	return bRet;
}

void CDuiListBox::OnDestroy()
{
	DeleteAllItems(FALSE);
	__super::OnDestroy();
}

BOOL CDuiListBox::OnUpdateToolTip(HDUIWND hCurTipHost,HDUIWND &hNewTipHost,CRect &rcTip,CString &strTip)
{
	if(m_iHoverItem==-1)
		return __super::OnUpdateToolTip(hCurTipHost,hNewTipHost,rcTip,strTip);
	return m_arrItems[m_iHoverItem]->OnUpdateToolTip(hCurTipHost,hNewTipHost,rcTip,strTip);
}

}//namespace DuiEngine