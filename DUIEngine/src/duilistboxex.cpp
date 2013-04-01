//////////////////////////////////////////////////////////////////////////
//  Class Name: CDuiListBoxEx
// Description: A DuiWindow Based ListBox Control. Can contain control as an item
//     Creator: Huang Jianxiong
//     Version: 2011.8.27 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma  once
#include "duistd.h"
#include "duilistboxex.h"
#include "DuiSystem.h"
#include "mybuffer.h"

#pragma warning(disable:4018)
#pragma warning(disable:4267)

namespace DuiEngine
{


CDuiListBoxEx::CDuiListBoxEx()
    : m_nItemHei(20)
    , m_iScrollSpeed(-1)
    , m_iSelItem(-1)
    , m_iHoverItem(-1)
    , m_pCapturedFrame(NULL)
    , m_pTemplPanel(NULL)
	, m_nItems(0)
    , m_pItemSkin(NULL)
	, m_pXmlTempl(NULL)
	, m_bVirtual(FALSE)
{
	addEvent(DUINM_LBITEMNOTIFY);
	addEvent(DUINM_ITEMMOUSEEVENT);
	addEvent(DUINM_GETLBDISPINFO);
	addEvent(DUINM_LBSELCHANGING);
	addEvent(DUINM_LBSELCHANGED);
}

CDuiListBoxEx::~CDuiListBoxEx()
{
    if(m_pXmlTempl) delete m_pXmlTempl;
}


void CDuiListBoxEx::DeleteAllItems(BOOL bUpdate/*=TRUE*/)
{
	if(m_pTemplPanel)
	{
		m_nItems=0;
	}
	else
	{
		for(int i=0; i<GetItemCount(); i++)
		{
			m_arrItems[i]->Release();
		}
		m_arrItems.RemoveAll();
	}
    m_iSelItem=-1;
    m_iHoverItem=-1;
    m_pCapturedFrame=NULL;
    ReleaseDuiCapture();

    SetViewSize(CSize(0,0));
    if(bUpdate) NotifyInvalidate();
}

void CDuiListBoxEx::DeleteItem(int iItem)
{
	if(m_pTemplPanel) return;

    if(iItem<0 || iItem>=GetItemCount()) return;
    if(m_pCapturedFrame == m_arrItems[iItem])
    {
        m_pCapturedFrame=NULL;
        ReleaseDuiCapture();
    }

    m_arrItems[iItem]->Release();
    m_arrItems.RemoveAt(iItem);

    if(m_iSelItem==iItem) m_iSelItem=-1;
    else if(m_iSelItem>iItem) m_iSelItem--;
    if(m_iHoverItem==iItem) m_iHoverItem=-1;
    else if(m_iHoverItem>iItem) m_iHoverItem--;

	UpdatePanelsIndex(iItem,-1);

    CRect rcClient;
    CDuiWindow::GetClient(&rcClient);
    CSize szView(rcClient.Width(),GetItemCount()*m_nItemHei);
    if(szView.cy>rcClient.Height()) szView.cx-=m_nSbWid;
    SetViewSize(szView);
}

int CDuiListBoxEx::InsertItem(int iItem,TiXmlElement *pXmlItem,DWORD dwData/*=0*/)
{
	if(m_pTemplPanel) return -1;

	CDuiItemPanel *pItemObj=new CDuiItemPanel(this,pXmlItem,this);

    if(iItem==-1 || iItem>=GetItemCount())
    {
        iItem=GetItemCount();
    }
    pItemObj->SetItemData(dwData);
    pItemObj->Move(CRect(0,0,m_rcClient.Width(),m_nItemHei));
    if(m_pItemSkin) pItemObj->SetSkin(m_pItemSkin);

    m_arrItems.InsertAt(iItem,pItemObj);

    if(m_iSelItem>=iItem) m_iSelItem++;
    if(m_iHoverItem>=iItem) m_iHoverItem++;

	UpdatePanelsIndex(iItem,-1);

    CRect rcClient;
    CDuiWindow::GetClient(&rcClient);
    CSize szView(rcClient.Width(),GetItemCount()*m_nItemHei);
    if(szView.cy>rcClient.Height()) szView.cx-=m_nSbWid;
    SetViewSize(szView);

    return iItem;
}

int CDuiListBoxEx::InsertItem(int iItem,LPCWSTR pszXml,DWORD dwData/*=0*/)
{
	if(m_pTemplPanel) return -1;

    CDuiStringA strUtf8=DUI_CW2A(pszXml,CP_UTF8);
    TiXmlDocument xmlDoc;
    xmlDoc.Parse(strUtf8);
    if(xmlDoc.Error()) return NULL;
    return InsertItem(iItem,xmlDoc.RootElement(),dwData);
}

void CDuiListBoxEx::SetCurSel(int iItem)
{
	if(iItem<0 || iItem>=GetItemCount()) return;

    if(m_iSelItem==iItem) return;
	if(m_pTemplPanel)
	{
		int nOldSel=m_iSelItem;
		m_iSelItem=iItem;
		if(IsVisible(TRUE))
		{
			if(nOldSel!=-1) RedrawItem(nOldSel);
			RedrawItem(m_iSelItem);
		}
	}else
	{
		int nOldSel=m_iSelItem;
		m_iSelItem=iItem;
		if(nOldSel!=-1)
		{
			m_arrItems[nOldSel]->ModifyItemState(0,DuiWndState_Check);
			if(IsVisible(TRUE)) RedrawItem(nOldSel);
		}
		m_arrItems[m_iSelItem]->ModifyItemState(DuiWndState_Check,0);
		if(IsVisible(TRUE)) RedrawItem(m_iSelItem);
	}
}

void CDuiListBoxEx::EnsureVisible( int iItem )
{
    if(iItem<0 || iItem>=GetItemCount()) return;
    int iFirstVisible=(m_ptOrgin.y + m_nItemHei -1) / m_nItemHei;
    CRect rcClient;
    GetClient(&rcClient);
    int nVisibleItems=rcClient.Height()/m_nItemHei;
    if(iItem<iFirstVisible || iItem> iFirstVisible+nVisibleItems-1)
    {
        int nOffset=GetScrollPos(TRUE);
        if(iItem<iFirstVisible) nOffset=(iItem-iFirstVisible)*m_nItemHei;
        else nOffset=(iItem - iFirstVisible-nVisibleItems +1)*m_nItemHei;
        nOffset-=nOffset%m_nItemHei;//让当前行刚好显示
        OnScroll(TRUE,SB_THUMBPOSITION,nOffset + GetScrollPos(TRUE));
    }
}

int CDuiListBoxEx::GetCurSel()
{
    return m_iSelItem;
}

int CDuiListBoxEx::GetItemObjIndex(CDuiPanel *pItemObj)
{
	CDuiItemPanel * pItemPanel= dynamic_cast<CDuiItemPanel *>(pItemObj);
	if (NULL == pItemPanel) return -1;
	return (int)pItemPanel->GetItemIndex();
}


CDuiPanel * CDuiListBoxEx::GetItemPanel(int iItem)
{
    if(iItem<0 || iItem>= GetItemCount()) return NULL;
	if(m_pTemplPanel) return m_pTemplPanel;
    else return m_arrItems[iItem];
}


LPARAM CDuiListBoxEx::GetItemData(int iItem)
{
    DUIASSERT(iItem>=0 || iItem< GetItemCount());
	if(m_pTemplPanel) return 0;
    return m_arrItems[iItem]->GetItemData();
}


BOOL CDuiListBoxEx::SetItemCount(int nItems,LPCTSTR pszXmlTemplate)
{
	if(m_arrItems.GetCount()!=0) return FALSE;
	if(pszXmlTemplate)
	{
		TiXmlDocument xmlDoc;
		CDuiStringA strXml=DUI_CT2A(pszXmlTemplate,CP_UTF8);
		xmlDoc.Parse(strXml);
		if(xmlDoc.Error()) return FALSE;
		if(m_bVirtual)
		{
			if(m_pTemplPanel)
			{
				m_pTemplPanel->DuiSendMessage(WM_DESTROY);
				m_pTemplPanel->Release();
			}
			m_pTemplPanel=new CDuiItemPanel(this,xmlDoc.RootElement(),this);
			if(m_pItemSkin) m_pTemplPanel->SetSkin(m_pItemSkin);
		}else
		{
			if(m_pTemplPanel) delete m_pTemplPanel;
			m_pXmlTempl=xmlDoc.RootElement()->Clone()->ToElement();
		}

	}
    if(m_bVirtual)
	{
		DUIASSERT(m_pTemplPanel);
		m_nItems=nItems;
		CRect rcClient;
		CDuiWindow::GetClient(&rcClient);
		CSize szView(rcClient.Width(),GetItemCount()*m_nItemHei);
		if(szView.cy>rcClient.Height()) szView.cx-=m_nSbWid;
		SetViewSize(szView);
		GetClient(&rcClient);
		m_pTemplPanel->Move(0,0,rcClient.Width(),m_nItemHei);
		NotifyInvalidate();
		return TRUE;
	}else if(m_pXmlTempl)
	{
		for(int i=0;i<nItems;i++)
		{
			InsertItem(i,m_pXmlTempl);
		}
		return TRUE;
	}else
	{
		return FALSE;
	}

}

int CDuiListBoxEx::GetItemCount()
{
	if(m_bVirtual) 
		return m_nItems;
    else
		return m_arrItems.GetCount();
}

void CDuiListBoxEx::RedrawItem(int iItem)
{
    if(!IsVisible(TRUE)) return;
    CRect rcClient;
    GetClient(&rcClient);
	CRect rcItem=GetItemRect(iItem);
	CRect rcInter;
	rcInter.IntersectRect(&rcClient,&rcItem);
	if(rcInter.IsRectEmpty()) return;

	CDCHandle dc=GetDuiDC(&rcItem,OLEDC_PAINTBKGND);
	DuiDCPaint duiDC;
	BeforePaint(dc,duiDC);

	DuiSendMessage(WM_ERASEBKGND,(WPARAM)(HDC)dc);
	OnDrawItem(dc,rcItem,iItem);

	AfterPaint(dc,duiDC);
	ReleaseDuiDC(dc);
}

//自动修改pt的位置为相对当前项的偏移量
int CDuiListBoxEx::HitTest(CPoint &pt)
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

int CDuiListBoxEx::GetScrollLineSize(BOOL bVertical)
{
    return m_iScrollSpeed >0 ? m_iScrollSpeed : m_nItemHei;
}

void CDuiListBoxEx::OnPaint(CDCHandle dc)
{
    DuiDCPaint duiDC;
    BeforePaint(dc,duiDC);

    int iFirstVisible=m_ptOrgin.y/m_nItemHei;
    int nPageItems=(m_rcClient.Height()+m_nItemHei-1)/m_nItemHei+1;

	CRect rcClip,rcInter;
	int nClip=dc.GetClipBox(&rcClip);

    for(int iItem = iFirstVisible; iItem<GetItemCount() && iItem <iFirstVisible+nPageItems; iItem++)
    {
        CRect rcItem(0,0,m_rcClient.Width(),m_nItemHei);
        rcItem.OffsetRect(0,m_nItemHei*iItem-m_ptOrgin.y);
        rcItem.OffsetRect(m_rcClient.TopLeft());
		rcInter.IntersectRect(&rcClip,&rcItem);
		if(nClip==NULLREGION || !rcInter.IsRectEmpty())
			OnDrawItem(dc,rcItem,iItem);
    }

    AfterPaint(dc,duiDC);
}


void CDuiListBoxEx::OnSize( UINT nType, CSize size )
{
	__super::OnSize(nType,size);
	if(m_bVirtual)
	{
		DUIASSERT(m_pTemplPanel);
		m_pTemplPanel->Move(CRect(0,0,m_rcClient.Width(),m_nItemHei));
	}
	else
	{
		for(int i=0; i<GetItemCount(); i++)
			m_arrItems[i]->Move(CRect(0,0,m_rcClient.Width(),m_nItemHei));
	}

}

void CDuiListBoxEx::OnDrawItem(CDCHandle & dc, CRect & rc, int iItem)
{
	if(m_bVirtual)
	{//虚拟列表，由APP控制显示
		DUIASSERT(m_pTemplPanel);
		DUINMGETLBDISPINFO nms;
		nms.hdr.code    = DUINM_GETLBDISPINFO;
		nms.hdr.hwndFrom = NULL;
		nms.hdr.idFrom  = GetCmdID();
		nms.bHover      = iItem == m_iHoverItem;
		nms.bSelect     = iItem == m_iSelItem;
		nms.nListItemID = iItem;
		nms.pItem = m_pTemplPanel;
		nms.pHostDuiWin   = this;

		m_pTemplPanel->SetItemIndex(iItem);

		DWORD dwState=0;
		if(nms.bHover) dwState|=DuiWndState_Hover;
		if(nms.bSelect) dwState|=DuiWndState_PushDown;
		m_pTemplPanel->ModifyItemState(dwState,-1);

		LockUpdate();
		GetContainer()->OnDuiNotify((LPNMHDR)&nms);
		UnlockUpdate();
		m_pTemplPanel->Draw(dc,rc);
	}else
	{
		m_arrItems[iItem]->Draw(dc,rc);
	}
}

BOOL CDuiListBoxEx::Load(TiXmlElement* pTiXmlElem)
{
    if (!__super::Load(pTiXmlElem))
        return FALSE;

    int			nChildSrc=-1;
    pTiXmlElem->Attribute("itemsrc",&nChildSrc);

    if (nChildSrc == -1)
        return TRUE;

	TiXmlDocument xmlDoc;
	if(!DuiSystem::getSingleton().LoadXmlDocment(&xmlDoc,nChildSrc,DUIRES_XML_TYPE))
		return FALSE;

	TiXmlElement *pSubTiElement = xmlDoc.RootElement();
    return LoadChildren(pSubTiElement);
}

BOOL CDuiListBoxEx::LoadChildren(TiXmlElement* pTiXmlChildElem)
{
    if(!pTiXmlChildElem) return TRUE;
    TiXmlElement* pParent=(TiXmlElement*)pTiXmlChildElem->Parent();
    TiXmlElement* pTemplate=(TiXmlElement*)pParent->FirstChildElement("template");
	TiXmlElement* pItems=(TiXmlElement*)pParent->FirstChildElement("items");

	if(!m_bVirtual)
	{//普通列表
		if(pTemplate) m_pXmlTempl=pTemplate->Clone()->ToElement();

		if(pItems)
		{
			TiXmlElement *pChild=pItems->FirstChildElement();
			while(pChild)
			{
				int dwData=0;
				pChild->Attribute("itemdata",&dwData);
				if(strcmp(pChild->Value(),"dlg")==0 || strcmp(pChild->Value(),"item")==0)
				{
					InsertItem(-1,pChild,dwData);
				}
				pChild=pChild->NextSiblingElement();
			}
			int nSelItem=-1;
			pItems->Attribute("cursel",&nSelItem);
			SetCurSel(nSelItem);
		}

		return TRUE;
	}else
    {//虚拟列表
		DUIASSERT(pTemplate);
		m_pTemplPanel=new CDuiItemPanel(this,pTemplate,this);
		if(m_pItemSkin) m_pTemplPanel->SetSkin(m_pItemSkin);
		return TRUE;
    }
}


void CDuiListBoxEx::NotifySelChange( int nOldSel,int nNewSel ,UINT uMsg)
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
		if(m_bVirtual)
		{
			DUIASSERT(m_pTemplPanel);
			CDuiWindow *pHover=DuiWindowManager::GetWindow(m_pTemplPanel->GetDuiHover());
			if(pHover) nms.uHoverID=pHover->GetCmdID();
		}else
		{
			CDuiWindow *pHover=DuiWindowManager::GetWindow(m_arrItems[nNewSel]->GetDuiHover());
			if(pHover) nms.uHoverID=pHover->GetCmdID();
		}
    }

    nms.hdr.code=DUINM_LBSELCHANGING;
    if(S_OK!=DuiNotify((LPNMHDR)&nms)) return ;
	m_iSelItem=nNewSel;
    if(nOldSel!=-1)
    {
        if(!m_pTemplPanel) m_arrItems[nOldSel]->ModifyItemState(0,DuiWndState_Check);
        RedrawItem(nOldSel);
    }
    if(m_iSelItem!=-1)
    {
        if(!m_pTemplPanel) m_arrItems[m_iSelItem]->ModifyItemState(DuiWndState_Check,0);
        RedrawItem(m_iSelItem);
    }

    nms.hdr.idFrom=GetCmdID();
    nms.hdr.code=DUINM_LBSELCHANGED;
    DuiNotify((LPNMHDR)&nms);
}

void CDuiListBoxEx::OnMouseLeave()
{
	__super::OnMouseLeave();
    if(m_iHoverItem!=-1)
    {
		int nOldHover=m_iHoverItem;
		m_iHoverItem=-1;
		if(m_bVirtual)
		{
			DUIASSERT(m_pTemplPanel);
			RedrawItem(nOldHover);
			m_pTemplPanel->DoFrameEvent(WM_MOUSELEAVE,0,0);
		}
		else
			m_arrItems[nOldHover]->DoFrameEvent(WM_MOUSELEAVE,0,0);
    }
}

BOOL CDuiListBoxEx::OnDuiSetCursor(const CPoint &pt)
{
    BOOL bRet=FALSE;
    if(m_pCapturedFrame)
    {
        CRect rcItem=m_pCapturedFrame->GetItemRect();
        bRet=m_pCapturedFrame->DoFrameEvent(WM_SETCURSOR,0,MAKELPARAM(pt.x-rcItem.left,pt.y-rcItem.top))!=0;
    }
    else if(m_iHoverItem!=-1)
    {
		CRect rcItem=GetItemRect(m_iHoverItem);
		if(m_bVirtual)
		{
			DUIASSERT(m_pTemplPanel);
			bRet=m_pTemplPanel->DoFrameEvent(WM_SETCURSOR,0,MAKELPARAM(pt.x-rcItem.left,pt.y-rcItem.top))!=0;
		}else
		{
			bRet=m_arrItems[m_iHoverItem]->DoFrameEvent(WM_SETCURSOR,0,MAKELPARAM(pt.x-rcItem.left,pt.y-rcItem.top))!=0;
		}
    }
    if(!bRet)
    {
        bRet=__super::OnDuiSetCursor(pt);
    }
    return bRet;
}

void CDuiListBoxEx::OnKeyDown( TCHAR nChar, UINT nRepCnt, UINT nFlags )
{
    int  nNewSelItem = -1;
    CDuiWindow *pOwner = GetOwner();
    if (pOwner && (nChar == VK_ESCAPE))
    {
        pOwner->DuiSendMessage(WM_KEYDOWN, nChar, MAKELONG(nFlags, nRepCnt));
        return;
    }

    if (nChar == VK_DOWN && m_iSelItem < GetItemCount() - 1)
        nNewSelItem = m_iSelItem+1;
    else if (nChar == VK_UP && m_iSelItem > 0)
        nNewSelItem = m_iSelItem-1;
    else if (pOwner && nChar == VK_RETURN)
        nNewSelItem = m_iSelItem;

    if(nNewSelItem!=-1)
    {
        EnsureVisible(nNewSelItem);
        NotifySelChange(m_iSelItem,nNewSelItem,nChar!=VK_RETURN ? WM_MOUSEMOVE : WM_LBUTTONUP);
    }
}

void CDuiListBoxEx::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    CDuiWindow *pOwner = GetOwner();
    if (pOwner)
        pOwner->DuiSendMessage(WM_CHAR, nChar, MAKELONG(nFlags, nRepCnt));
}

UINT CDuiListBoxEx::OnGetDuiCode()
{
    return DUIC_WANTALLKEYS;
}

void CDuiListBoxEx::OnDestroy()
{
    DeleteAllItems(FALSE);
	if(m_bVirtual)
	{
		DUIASSERT(m_pTemplPanel);
		m_pTemplPanel->DuiSendMessage(WM_DESTROY);
		m_pTemplPanel->Release();
		m_pTemplPanel=NULL;
	}
    __super::OnDestroy();
}

BOOL CDuiListBoxEx::OnUpdateToolTip(HDUIWND hCurTipHost,HDUIWND &hNewTipHost,CRect &rcTip,CDuiStringT &strTip)
{
    if(m_iHoverItem==-1)
        return __super::OnUpdateToolTip(hCurTipHost,hNewTipHost,rcTip,strTip);
    else if(m_bVirtual)
		return m_pTemplPanel->OnUpdateToolTip(hCurTipHost,hNewTipHost,rcTip,strTip);
	else
		return m_arrItems[m_iHoverItem]->OnUpdateToolTip(hCurTipHost,hNewTipHost,rcTip,strTip);
}

void CDuiListBoxEx::OnItemSetCapture(CDuiItemPanel *pItem,BOOL bCapture )
{
    if(bCapture)
    {
        SetDuiCapture();
        m_pCapturedFrame=pItem;
    }
    else if(pItem==m_pCapturedFrame)
    {
        ReleaseDuiCapture();
        m_pCapturedFrame=NULL;
    }
}


CRect CDuiListBoxEx::GetItemRect( int iItem )
{
	CRect rcClient;
	GetClient(&rcClient);
	CRect rcRet(CPoint(0,iItem*m_nItemHei),CSize(rcClient.Width(),m_nItemHei));
	rcRet.OffsetRect(rcClient.TopLeft()-m_ptOrgin);
	return rcRet;
}

BOOL CDuiListBoxEx::OnItemGetRect(CDuiItemPanel *pItem,CRect &rcItem )
{
	int iItem=pItem->GetItemIndex();
	rcItem=GetItemRect(iItem);
	return TRUE;
}

LRESULT CDuiListBoxEx::OnMouseEvent( UINT uMsg,WPARAM wParam,LPARAM lParam )
{
	CPoint pt(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	if(m_pCapturedFrame)
	{
		CRect rcItem=m_pCapturedFrame->GetItemRect();
		pt.Offset(-rcItem.TopLeft());
		return m_pCapturedFrame->DoFrameEvent(uMsg,wParam,MAKELPARAM(pt.x,pt.y));
	}
	else
	{
		int iHover=HitTest(pt);
		if(iHover!=m_iHoverItem)
		{
			int nOldHover=m_iHoverItem;
			m_iHoverItem=iHover;
			if(nOldHover!=-1)
			{
				RedrawItem(nOldHover);
				if(!m_bVirtual)
				{
					m_arrItems[nOldHover]->DoFrameEvent(WM_MOUSELEAVE,0,0);
				}else
				{
					DUIASSERT(m_pTemplPanel);
					m_pTemplPanel->DoFrameEvent(WM_MOUSELEAVE,0,0);
				}
			}
			if(m_iHoverItem!=-1)
			{
				RedrawItem(m_iHoverItem);
				if(!m_bVirtual)
				{
					m_arrItems[m_iHoverItem]->DoFrameEvent(WM_MOUSEHOVER,wParam,MAKELPARAM(pt.x,pt.y));
				}else
				{
					DUIASSERT(m_pTemplPanel);
					m_pTemplPanel->DoFrameEvent(WM_MOUSEHOVER,wParam,MAKELPARAM(pt.x,pt.y));
				}
			}
		}
		if(m_iHoverItem!=-1)
		{
			if(!m_bVirtual)
			{
				m_arrItems[m_iHoverItem]->DoFrameEvent(uMsg,wParam,MAKELPARAM(pt.x,pt.y));
			}else
			{
				DUIASSERT(m_pTemplPanel);
				m_pTemplPanel->DoFrameEvent(uMsg,wParam,MAKELPARAM(pt.x,pt.y));
			}
			if(uMsg==WM_LBUTTONDOWN && m_iHoverItem!=m_iSelItem)
				NotifySelChange(m_iSelItem,m_iHoverItem,WM_LBUTTONDOWN);
		}
		return 0;
	}
}

//同步在CDuiItemPanel中的index属性，在执行了插入，删除等操作后使用
void CDuiListBoxEx::UpdatePanelsIndex(UINT nFirst,UINT nLast)
{
	if(m_pTemplPanel) return;
	for(UINT i=nFirst;i<m_arrItems.GetCount() && i<nLast;i++)
	{
		m_arrItems[i]->SetItemIndex(i);
	}
}

}//namespace DuiEngine