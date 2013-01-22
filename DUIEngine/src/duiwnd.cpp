//////////////////////////////////////////////////////////////////////////
//   File Name: DuiWnd.h
// Description: DuiWindow Definition
//     Creator: Zhang Xiaoxuan
//     Version: 2009.04.28 - 1.0 - Create
//				2011.09.01 - 2.0 huang jianxiong
//////////////////////////////////////////////////////////////////////////

#include "duistd.h"
#include "duiwnd.h"
#include "duiwndfactorymanager.h"
#include "DuiSystem.h"

namespace DuiEngine
{

//////////////////////////////////////////////////////////////////////////
// CDuiWindow Implement
//////////////////////////////////////////////////////////////////////////

CDuiWindow::CDuiWindow()
    : m_hDuiWnd(DuiWindowManager::NewWindow(this))
    , m_pContainer(NULL)
    , m_pParent(NULL),m_pFirstChild(NULL),m_pLastChild(NULL),m_pNextSibling(NULL),m_pPrevSibling(NULL)
    , m_nChildrenCount(0)
    , m_bMsgHandled(FALSE)
    , m_uCmdID(NULL)
    , m_uPositionType(0)
    , m_lSpecifyWidth(0)
    , m_lSpecifyHeight(0)
    , m_dwState(DuiWndState_Normal)
    , m_uVAlign(0)
    , m_bMsgTransparent(FALSE)
    , m_bVisible(TRUE)
    , m_nSepSpace(2)
    , m_nMaxWidth(-1)
    , m_bUpdateLocked(FALSE)
    , m_bClipClient(FALSE)
#ifdef _DEBUG
    , m_nMainThreadId( ::GetCurrentThreadId() ) // 初始化对象的线程不一定是主线程
#endif
    , m_uData(0)
    , m_pOwner(NULL)
    , m_pCurMsg(NULL)
    , m_pBgSkin(NULL)
    , m_pNcSkin(NULL)
    , m_nSaveDC(0)
    , m_gdcFlags(-1)
{
}

CDuiWindow::~CDuiWindow()
{
    DuiWindowManager::DestroyWindow(m_hDuiWnd);
}

void CDuiWindow::OnFinalRelease()
{
    delete this;
}


//////////////////////////////////////////////////////////////////////////
// Method Define

// Get align
UINT CDuiWindow::GetAlign()
{
    return m_uVAlign ;
}

// Get position type
DWORD CDuiWindow::GetPositionType()
{
    return m_uPositionType;
}

// Set position type
void CDuiWindow::SetPositionType(DWORD dwPosType, DWORD dwMask /*= 0xFFFFFFFF*/)
{
    m_uPositionType = (m_uPositionType & ~dwMask) | (dwPosType & dwMask);
}

void CDuiWindow::SetFixSize(int nWid,int nHei)
{
    m_uPositionType = (m_uPositionType & ~SizeX_Mask) | SizeX_Specify|SizeY_Specify;
    m_lSpecifyWidth = nWid;
    m_lSpecifyHeight = nHei;
}

void CDuiWindow::SetBkColor(COLORREF cr)
{
    m_style.m_crBg=cr;
}

// Get DuiWindow rect(position in container)
void CDuiWindow::GetRect(LPRECT prect)
{
    DUIASSERT(prect);
    prect->left     = m_rcWindow.left;
    prect->right    = m_rcWindow.right;
    prect->top      = m_rcWindow.top;
    prect->bottom   = m_rcWindow.bottom;
}

void CDuiWindow::GetClient(LPRECT pRect)
{
    DUIASSERT(pRect);
    *pRect=m_rcWindow;
    pRect->left+=m_style.m_nMarginX;
    pRect->right-=m_style.m_nMarginX;
    pRect->top+=m_style.m_nMarginY;
    pRect->bottom-=m_style.m_nMarginY;
}

void CDuiWindow::GetDlgPosition(DUIDLG_POSITION *pPos)
{
    if (pPos)
        memcpy(pPos, &m_dlgpos, sizeof(DUIDLG_POSITION));
}

// Get inner text
LPCTSTR CDuiWindow::GetInnerText()
{
    return m_strInnerText;
}

// Get tooltip text
BOOL CDuiWindow::OnUpdateToolTip(HDUIWND hCurTipHost,HDUIWND &hNewTipHost,CRect &rcTip,CString &strTip)
{
    if(m_hDuiWnd==hCurTipHost) return FALSE;
    hNewTipHost=m_hDuiWnd;
    GetRect(&rcTip);
    strTip=m_strToolTipText;
    return TRUE;
}

// Set inner text
HRESULT CDuiWindow::SetInnerText(LPCTSTR lpszText)
{
    m_strInnerText = lpszText;

    if ((m_uPositionType & SizeX_FitContent | SizeY_FitContent) || CLR_INVALID == m_style.m_crBg)
    {
        if ((m_uPositionType & (SizeX_FitContent | SizeY_FitContent)) && (4 != m_dlgpos.nCount))
        {
            SIZE sizeRet = {0, 0};

            DuiSendMessage(WM_CALCSIZE, FALSE, (LPARAM)&sizeRet);

            if (m_uPositionType & SizeX_FitContent)
                m_rcWindow.right = m_rcWindow.left + sizeRet.cx;
            if (m_uPositionType & SizeY_FitContent)
                m_rcWindow.bottom = m_rcWindow.top + sizeRet.cy;
        }

        return S_OK;
    }
    else
        return S_FALSE;
}

VOID CDuiWindow::TestMainThread()
{
#ifdef DEBUG
    // 当你看到这个东西的时候，我不幸的告诉你，你的其他线程在刷界面
    // 这是一件很危险的事情
    DWORD dwCurThreadID = GetCurrentThreadId();

    BOOL bOK = (m_nMainThreadId == dwCurThreadID); // 当前线程和构造对象时的线程一致

    DUIASSERT(bOK);
#endif
}


// Send a message to DuiWindow
LRESULT CDuiWindow::DuiSendMessage(UINT Msg, WPARAM wParam /*= 0*/, LPARAM lParam /*= 0*/,BOOL *pbMsgHandled/*=NULL*/)
{
    LRESULT lResult = 0;

    if ( Msg < WM_USER
            && Msg != WM_DESTROY
            && Msg != WM_CLOSE
       )
    {
        TestMainThread();
    }
    AddRef();
    DUIMSG msgCur= {Msg,wParam,lParam};
    DUIMSG *pOldMsg=m_pCurMsg;
    m_pCurMsg=&msgCur;

    BOOL bOldMsgHandle=IsMsgHandled();//备分上一个消息的处理状态

    SetMsgHandled(FALSE);

    ProcessDuiWndMessage(Msg, wParam, lParam, lResult);

    if(pbMsgHandled) *pbMsgHandled=IsMsgHandled();

    SetMsgHandled(bOldMsgHandle);//恢复上一个消息的处理状态

    m_pCurMsg=pOldMsg;
    Release();
    return lResult;
}

// Move DuiWindow to new place
//
void CDuiWindow::Move(LPRECT prect)
{
    DUIASSERT(prect);
    TestMainThread();

    if(m_rcWindow.EqualRect(prect)) return;

    m_rcWindow = prect;

    DuiSendMessage(WM_NCCALCSIZE);
    CRect rcClient;
    GetClient(&rcClient);
    DuiSendMessage(WM_SIZE,0,MAKELPARAM(rcClient.Width(),rcClient.Height()));

    CDuiWindow *pChild=m_pFirstChild;
    while(pChild)
    {
        DuiSendMessage(WM_CALCWNDPOS,0,(LPARAM)pChild);
        pChild= pChild->m_pNextSibling;
    }
}

void CDuiWindow::Move(int x,int y, int cx/*=-1*/,int cy/*=-1*/)
{
    if(cx==-1) cx=m_rcWindow.Width();
    if(cy==-1) cy=m_rcWindow.Height();
    CRect rcNew(x,y,x+cx,y+cy);
    Move(&rcNew);
}

void CDuiWindow::ReCalcWndPos()
{
    CDuiWindow *pChild=m_pFirstChild;
    while(pChild)
    {
        DuiSendMessage(WM_CALCWNDPOS,0,(LPARAM)pChild);
        pChild= pChild->m_pNextSibling;
    }
}

// Set current cursor, when hover
BOOL CDuiWindow::OnDuiSetCursor(const CPoint &pt)
{
    HCURSOR hCur = ::LoadCursor(NULL, m_style.m_lpCursorName);
    ::SetCursor(hCur);
    return TRUE;
}

// Get DuiWindow state
DWORD CDuiWindow::GetState(void)
{
    return m_dwState;
}

// Modify DuiWindow state
DWORD CDuiWindow::ModifyState(DWORD dwStateAdd, DWORD dwStateRemove,BOOL bUpdate/*=FALSE*/)
{
    DWORD dwOldState = m_dwState;

    TestMainThread();

    m_dwState |= dwStateAdd;
    m_dwState &= ~dwStateRemove;

    OnStateChanged(dwOldState,m_dwState);
    if(bUpdate && NeedRedrawWhenStateChange()) NotifyInvalidate();
    return dwOldState;
}

// Get Command ID
UINT CDuiWindow::GetCmdID()
{
    return m_uCmdID;
}

void CDuiWindow::SetCmdID(UINT uNewID)
{
    m_uCmdID=uNewID;
}

ULONG_PTR CDuiWindow::GetCmdData()
{
    return m_uData;
}

ULONG_PTR CDuiWindow::SetCmdData(ULONG_PTR uData)
{
    ULONG_PTR uOld=m_uData;
    m_uData=uData;
    return uOld;
}

BOOL CDuiWindow::SetDuiTimer(char id,UINT uElapse)
{
    CDuiTimerID timerID(m_hDuiWnd,id);
    return ::SetTimer(GetContainer()->GetHostHwnd(),DWORD(timerID),uElapse,NULL);
}

void CDuiWindow::KillDuiTimer(char id)
{
    CDuiTimerID timerID(m_hDuiWnd,id);
    ::KillTimer(GetContainer()->GetHostHwnd(),DWORD(timerID));
}


BOOL CDuiWindow::SetDuiTimerEx( UINT_PTR id,UINT uElapse )
{
    return CDuiTimerEx::SetTimer(m_hDuiWnd,id,uElapse);
}

void CDuiWindow::KillDuiTimerEx( UINT_PTR id )
{
    CDuiTimerEx::KillTimer(m_hDuiWnd,id);
}

HDUIWND CDuiWindow::GetDuiHwnd()
{
    return m_hDuiWnd;
}


CDuiWindow *CDuiWindow::GetParent()
{
    return m_pParent;
}


CDuiWindow * CDuiWindow::GetTopLevelParent()
{
    CDuiWindow *pParent=this;
    while(pParent->GetParent()) pParent=pParent->GetParent();
    return pParent;
}

void CDuiWindow::SetParent(CDuiWindow *pParent)
{
    if(m_pParent)
    {
        m_pParent->RemoveChild(this);
        m_pParent=NULL;
    }
    m_pParent=pParent;
    //根据Parent的状态来初始化自己的状态
    if(!m_pParent) return;
    m_pParent->InsertChild(this);
    if(m_pParent->IsVisible(TRUE) && m_bVisible)
        ModifyState(0,DuiWndState_Invisible);
    else
        ModifyState(DuiWndState_Invisible,0);
}

BOOL CDuiWindow::DestroyChild(CDuiWindow *pChild)
{
    if(this != pChild->GetParent()) return FALSE;
    pChild->DuiSendMessage(WM_DESTROY);
    RemoveChild(pChild);
    pChild->Release();
    return TRUE;
}

int CDuiWindow::GetChildrenCount()
{
    return m_nChildrenCount;
}

CDuiWindow * CDuiWindow::GetChild(UINT uCmdID)
{
    CDuiWindow *pChild=m_pFirstChild;
    while(pChild)
    {
        if(pChild->GetCmdID()==uCmdID) return pChild;
        pChild=pChild->m_pNextSibling;
    }
    return NULL;
}

void CDuiWindow::SetChildContainer(CDuiWindow *pChild)
{
    pChild->SetContainer(GetContainer());
}

void CDuiWindow::InsertChild(CDuiWindow *pNewChild,CDuiWindow *pInsertAfter/*=ICWND_LAST*/)
{
    pNewChild->m_pParent=this;
    pNewChild->m_pPrevSibling=pNewChild->m_pNextSibling=NULL;
    SetChildContainer(pNewChild);

    if(pInsertAfter==m_pLastChild) pInsertAfter=ICWND_LAST;

    if(pInsertAfter==ICWND_LAST)
    {
        //insert window at head
        pNewChild->m_pPrevSibling=m_pLastChild;
        if(m_pLastChild) m_pLastChild->m_pNextSibling=pNewChild;
        else m_pFirstChild=pNewChild;
        m_pLastChild=pNewChild;
    }
    else if(pInsertAfter==ICWND_FIRST)
    {
        //insert window at tail
        pNewChild->m_pNextSibling=m_pFirstChild;
        if(m_pFirstChild) m_pFirstChild->m_pPrevSibling=pNewChild;
        else m_pLastChild=pNewChild;
        m_pFirstChild=pNewChild;
    }
    else
    {
        //insert window at middle
        DUIASSERT(pInsertAfter->m_pParent == this);
        DUIASSERT(m_pFirstChild && m_pLastChild);
        CDuiWindow *pNext=pInsertAfter->m_pNextSibling;
        DUIASSERT(pNext);
        pInsertAfter->m_pNextSibling=pNewChild;
        pNewChild->m_pPrevSibling=pInsertAfter;
        pNewChild->m_pNextSibling=pNext;
        pNext->m_pPrevSibling=pNewChild;
    }
    m_nChildrenCount++;
}

BOOL CDuiWindow::RemoveChild(CDuiWindow *pChild)
{
    if(this != pChild->GetParent()) return FALSE;
    CDuiWindow *pPrevSib=pChild->m_pPrevSibling;
    CDuiWindow *pNextSib=pChild->m_pNextSibling;
    if(pPrevSib) pPrevSib->m_pNextSibling=pNextSib;
    else m_pFirstChild=pNextSib;
    if(pNextSib) pNextSib->m_pPrevSibling=pPrevSib;
    else m_pLastChild=pPrevSib;
    m_nChildrenCount--;
    return TRUE;
}

BOOL CDuiWindow::IsChecked()
{
    return DuiWndState_Check == (m_dwState & DuiWndState_Check);
}

BOOL CDuiWindow::IsDisabled(BOOL bCheckParent /*= FALSE*/)
{
    BOOL bDisable = (DuiWndState_Disable == (m_dwState & DuiWndState_Disable));

    if (bCheckParent && !bDisable)
    {
        CDuiWindow *pWndParent = this;

        while (pWndParent = pWndParent->GetParent())
        {
            if (pWndParent->IsDisabled())
                return TRUE;
        }
    }

    return bDisable;
}

BOOL CDuiWindow::IsVisible(BOOL bCheckParent /*= FALSE*/)
{
    if(bCheckParent) return (0 == (m_dwState & DuiWndState_Invisible));
    else return m_bVisible;
}

void CDuiWindow::SetVisible(BOOL bVisible,BOOL bUpdate/*=FALSE*/)
{
    DuiSendMessage(WM_SHOWWINDOW,bVisible);
    if(bUpdate) NotifyInvalidate();
}

void CDuiWindow::EnableWindow( BOOL bEnable)
{
    if (bEnable)
        ModifyState(0, DuiWndState_Disable,TRUE);
    else
        ModifyState(DuiWndState_Disable, DuiWndState_Hover,TRUE);
}

void CDuiWindow::SetCheck(BOOL bCheck)
{
    if (bCheck)
        ModifyState(DuiWndState_Check, 0,TRUE);
    else
        ModifyState(0, DuiWndState_Check,TRUE);
}

BOOL CDuiWindow::NeedRedrawParent()
{
    return (GetContainer()->IsTranslucent() || !m_pBgSkin || (m_style.m_crBg == CLR_INVALID));
}


LPCTSTR CDuiWindow::GetLinkUrl()
{
    return m_strLinkUrl;
}

CDuiContainer *CDuiWindow::GetContainer()
{
    return m_pContainer;
}

void CDuiWindow::SetContainer(CDuiContainer *pContainer)
{
    m_pContainer=pContainer;
    CDuiWindow *pChild=m_pFirstChild;
    while(pChild)
    {
        pChild->SetContainer(pContainer);
        pChild=pChild->m_pNextSibling;
    }
}

void CDuiWindow::SetOwner(CDuiWindow *pOwner)
{
    m_pOwner=pOwner;
}

CDuiWindow *CDuiWindow::GetOwner()
{
    return m_pOwner;
}

BOOL CDuiWindow::IsMsgTransparent()
{
    return m_bMsgTransparent;
}

// add by dummyz@126.com
DuiStyle& CDuiWindow::GetStyle()
{
    return m_style;
}


CDuiWindow* CDuiWindow::FindChildByCmdID(UINT uCmdID)
{
    CDuiWindow *pChild = m_pFirstChild;
    while(pChild)
    {
        if (pChild->GetCmdID() == uCmdID)
            return pChild;
        CDuiWindow *pChildFind=pChild->FindChildByCmdID(uCmdID);
        if(pChildFind) return pChildFind;
        pChild=pChild->m_pNextSibling;
    }
    return NULL;
}

BOOL CDuiWindow::LoadChildren(TiXmlElement* pTiXmlChildElem)
{
    for (TiXmlElement* pXmlChild = pTiXmlChildElem; NULL != pXmlChild; pXmlChild = pXmlChild->NextSiblingElement())
    {
        CDuiWindow *pChild = DuiWindowFactoryManager::getSingleton().CreateWindowByName(pXmlChild->Value());
		if(!pChild)
		{
// 			DUIASSERT(FALSE);
			continue;
		}

		InsertChild(pChild);
        pChild->Load(pXmlChild);
    }
    return TRUE;
}

// Create DuiWindow from xml element
BOOL CDuiWindow::Load(TiXmlElement* pTiXmlElem)
{
    DUIASSERT(m_pContainer);
    if (!pTiXmlElem)
    {
        if(m_pParent)	m_pParent->DestroyChild(this);
        return FALSE;
    }

    {
        m_strInnerText = CA2T(pTiXmlElem->GetText(), CP_UTF8);
        if (!m_strInnerText.IsEmpty()) DuiStringPool::getSingleton().BuildString(m_strInnerText);
    }

    m_uPositionType = 0;
    m_dlgpos.nCount = 0;
    __super::Load(pTiXmlElem);

    //加载style中指定的皮肤属性，由于皮肤有owner属性，而style没有owner属性，因此需要在属性加载完成后查询皮肤名称并加载 hjx:2012.1.15
    if(m_pBgSkin==NULL && !m_style.m_strSkinName.IsEmpty())
        m_pBgSkin=DuiSkinPool::getSingleton().GetSkin(m_style.m_strSkinName);
    if(m_pNcSkin==NULL && !m_style.m_strNcSkinName.IsEmpty())
        m_pNcSkin=DuiSkinPool::getSingleton().GetSkin(m_style.m_strNcSkinName);

    if(!m_bVisible || (m_pParent && !m_pParent->IsVisible(TRUE)))
        ModifyState(DuiWndState_Invisible, 0);

    if (2 != m_dlgpos.nCount && 4 != m_dlgpos.nCount)
    {
        int nValue = 0;
        CStringA strValue;
        strValue = pTiXmlElem->Attribute("width", &nValue);
        if (0 == nValue && "full" == strValue)
        {
            m_rcWindow.right = 0;
            m_uPositionType = (m_uPositionType & ~SizeX_Mask) | SizeX_FitParent;
        }
        else
        {
            if (nValue > 0)
            {
                m_rcWindow.right = nValue;
                m_lSpecifyWidth = nValue;
                m_uPositionType = (m_uPositionType & ~SizeX_Mask) | SizeX_Specify;
            }
            else
            {
                m_rcWindow.right = 0;
                m_uPositionType = (m_uPositionType & ~SizeX_Mask) | SizeX_FitContent;
            }
        }

        strValue = pTiXmlElem->Attribute("height", &nValue);
        if (0 == nValue && "full" == strValue)
        {
            m_rcWindow.bottom = 0;
            m_uPositionType = (m_uPositionType & ~SizeY_Mask) | SizeY_FitParent;
        }
        else
        {
            if (nValue > 0)
            {
                m_rcWindow.bottom = nValue;
                m_lSpecifyHeight = nValue;
                m_uPositionType = (m_uPositionType & ~SizeY_Mask) | SizeY_Specify;
            }
            else
            {
                m_rcWindow.bottom = 0;
                m_uPositionType = (m_uPositionType & ~SizeY_Mask) | SizeY_FitContent;
            }
        }

        if (m_uPositionType & (SizeX_FitContent | SizeY_FitContent))
        {
            SIZE sizeRet = {0, 0};

            DuiSendMessage(WM_CALCSIZE, FALSE, (LPARAM)&sizeRet);

            if (m_uPositionType & SizeX_FitContent)
                m_rcWindow.right = sizeRet.cx;
            if (m_uPositionType & SizeY_FitContent)
                m_rcWindow.bottom = sizeRet.cy;
        }
    }

    if(0!=DuiSendMessage(WM_CREATE))
    {
        if(m_pParent)	m_pParent->DestroyChild(this);
        return FALSE;
    }
    LoadChildren(pTiXmlElem->FirstChildElement());
    return TRUE;
}

CDuiWindow * CDuiWindow::LoadXmlChildren(LPCSTR utf8Xml)
{
    TiXmlDocument doc;
    doc.Parse( utf8Xml,NULL, TIXML_ENCODING_UTF8);
    if(doc.Error()) return NULL;
    CDuiWindow *pCurLast=m_pLastChild;
    BOOL bLoaded=LoadChildren(doc.RootElement());
    if(!bLoaded) return NULL;
    if(!m_rcWindow.IsRectEmpty())
    {
        for(CDuiWindow *p=m_pLastChild; p && p!=pCurLast; p=p->m_pPrevSibling)
        {
            DuiSendMessage(WM_CALCWNDPOS,0,(LPARAM)p);
            p->NotifyInvalidate();
        }
    }
    return m_pLastChild;
}

// Hittest children
HDUIWND CDuiWindow::DuiGetHWNDFromPoint(CPoint ptHitTest, BOOL bOnlyText)
{
    if (!m_rcWindow.PtInRect(ptHitTest)) return NULL;


    HDUIWND hDuiWndChild = NULL;

    CDuiWindow *pChild=m_pLastChild;
    while(pChild)
    {
        if (pChild->IsVisible(TRUE) && !pChild->IsMsgTransparent())
        {
            hDuiWndChild = pChild->DuiGetHWNDFromPoint(ptHitTest, bOnlyText);

            if (hDuiWndChild) return hDuiWndChild;
        }

        pChild=pChild->m_pPrevSibling;
    }

    return m_hDuiWnd;
}

BOOL CDuiWindow::NeedRedrawWhenStateChange()
{
    if (m_pBgSkin && !m_pBgSkin->IgnoreState())
    {
        return TRUE;
    }

    return (CLR_INVALID != m_style.m_crHoverText) || (NULL != m_style.m_ftHover) || (CLR_INVALID != m_style.m_crBgHover);
}

BOOL CDuiWindow::RedrawRegion(CDCHandle& dc, CRgn& rgn)
{
    if (rgn.IsNull() || rgn.RectInRegion(m_rcWindow))
    {

        CRect rcClient;
        GetClient(&rcClient);
        if(rgn.IsNull() || rgn.RectInRegion(rcClient))
        {
            CRgn rgnOldClip;
            if(IsClipClient())
            {
                dc.GetClipRgn(rgnOldClip);
                CRgn rgn;
                rgn.CreateRectRgnIndirect(&rcClient);
                dc.SelectClipRgn(rgn,RGN_AND);
            }
            DuiSendMessage(WM_ERASEBKGND, (WPARAM)(HDC)dc);
            DuiSendMessage(WM_PAINT, (WPARAM)(HDC)dc);

            DuiDCPaint DuiDC;

            BeforePaint(dc, DuiDC);	//让子窗口继承父窗口的属性

            CDuiWindow *pChild=GetDuiWindow(GDUI_FIRSTCHILD);
            while(pChild)
            {
                if (pChild->IsVisible(TRUE))
                {
                    pChild->RedrawRegion(dc, rgn);
                }
                pChild=pChild->GetDuiWindow(GDUI_NEXTSIBLING);
            }

            AfterPaint(dc, DuiDC);
            if(IsClipClient())
            {
                dc.SelectClipRgn(rgnOldClip);
            }
        }
        DuiSendMessage(WM_NCPAINT, (WPARAM)(HDC)dc);//ncpaint should be placed in tail of paint link
        return TRUE;
    }

    return FALSE;
}

void CDuiWindow::OnAttributeChanged( const CStringA & strAttrName,BOOL bLoading,HRESULT hRet )
{
    if(!bLoading && hRet==S_OK)
    {
        if(strAttrName=="pos")
        {
            //位置改变时需要重新计算位置，并更新
            NotifyInvalidate();
            if(GetParent())
            {
                GetParent()->DuiSendMessage(WM_CALCWNDPOS,0,(LPARAM)this);
                NotifyInvalidate();
            }
        }
        else
        {
            NotifyInvalidate();
        }
    }
}

void CDuiWindow::NotifyInvalidate()
{
    NotifyInvalidateRect(m_rcWindow);
}

void CDuiWindow::NotifyInvalidateRect(LPRECT lprect)
{
    if (lprect)
    {
        CRect rect = *lprect;
        NotifyInvalidateRect(rect);
    }
}

void CDuiWindow::NotifyInvalidateRect(const CRect& rect)
{
    if (!m_bUpdateLocked)
    {
        GetContainer()->OnRedraw(rect);
    }
}

void CDuiWindow::LockUpdate()
{
    m_bUpdateLocked=TRUE;
}

void CDuiWindow::UnlockUpdate()
{
    m_bUpdateLocked=FALSE;
}

BOOL CDuiWindow::IsUpdateLocked()
{
    return m_bUpdateLocked;
}

void CDuiWindow::BringWindowToTop()
{
    if(!m_pParent) return;
    m_pParent->RemoveChild(this);
    m_pParent->InsertChild(this);
}

LRESULT CDuiWindow::DuiNotify(LPNMHDR pnms)
{
    if(GetOwner()) return GetOwner()->DuiNotify(pnms);
    return GetContainer()->OnDuiNotify(pnms);
}


void CDuiWindow::OnWindowPosChanged(LPDUIWNDPOS lpWndPos)
{
    m_rcWindow.MoveToXY(lpWndPos->x, lpWndPos->y);
    SIZE sizeRet = {lpWndPos->cx, lpWndPos->cy};

    DuiSendMessage(WM_CALCSIZE, TRUE, (LPARAM)&sizeRet);

    m_rcWindow.SetRect(lpWndPos->x, lpWndPos->y, lpWndPos->x + sizeRet.cx, lpWndPos->y + sizeRet.cy);

    if (GetPositionType() & SizeX_FitParent)
        m_rcWindow.right = max(lpWndPos->x + lpWndPos->cx, m_rcWindow.right);
    else if (GetPositionType() & SizeX_Specify)
        m_rcWindow.right = m_rcWindow.left + m_lSpecifyWidth;

    if (GetPositionType() & SizeY_FitParent)
        m_rcWindow.bottom = max(lpWndPos->y + lpWndPos->cy, m_rcWindow.bottom);
    else if (GetPositionType() & SizeY_Specify)
        m_rcWindow.bottom = m_rcWindow.top + m_lSpecifyHeight;

    DuiSendMessage(WM_NCCALCSIZE);
    CRect rcClient;
    GetClient(&rcClient);
    DuiSendMessage(WM_SIZE,0,MAKELPARAM(rcClient.Width(),rcClient.Height()));

    CDuiWindow *pChild=m_pFirstChild;
    while(pChild)
    {
        DuiSendMessage(WM_CALCWNDPOS,0,(LPARAM)pChild);
        pChild=pChild->m_pNextSibling;
    }

}

int CDuiWindow::OnCreate( LPVOID )
{
    return 0;
}

void CDuiWindow::OnDestroy()
{
    //destroy children dui windows
    CDuiWindow *pChild=m_pFirstChild;
    while (pChild)
    {
        CDuiWindow *pNextChild=pChild->m_pNextSibling;
        pChild->DuiSendMessage(WM_DESTROY);
        pChild->Release();

        pChild=pNextChild;
    }
    m_pFirstChild=m_pLastChild=NULL;
    m_nChildrenCount=0;
}

// Draw background default
BOOL CDuiWindow::OnEraseBkgnd(CDCHandle dc)
{
    CRect rcClient;
    GetClient(&rcClient);
    if (!m_pBgSkin)
    {
        COLORREF crBg = m_style.m_crBg;

        if (DuiWndState_Hover == (GetState() & DuiWndState_Hover) && CLR_INVALID != m_style.m_crBgHover)
        {
            crBg = m_style.m_crBgHover;
        }

        if (CLR_INVALID != crBg)
            CGdiAlpha::FillSolidRect(dc,&rcClient, crBg);
    }
    else
    {
        m_pBgSkin->Draw(dc, rcClient, NeedRedrawWhenStateChange()?(IIF_STATE4(GetState(), 0, 1, 2, 3)):0);
    }
    return TRUE;
}

void CDuiWindow::BeforePaint(CDCHandle &dc, DuiDCPaint &DuiDC)
{
    HFONT hftDraw = NULL;
    COLORREF crDraw = CLR_INVALID;

    GetClient(DuiDC.rcClient);

    if (m_pBgSkin)
    {
        DuiDC.bDuiModeChanged = TRUE;
        DuiDC.nOldDuiMode = dc.SetBkMode(TRANSPARENT);
    }
    if (CLR_INVALID != m_style.m_crBg)
    {
        DuiDC.bBgColorChanged = TRUE;
        DuiDC.crOldBg = dc.SetBkColor(m_style.m_crBg);
    }

    if (m_style.m_ftText)
        hftDraw = m_style.m_ftText;

    if (m_style.m_crText != CLR_INVALID)
        crDraw = m_style.m_crText;

    if (IsDisabled(TRUE))
    {
        if (m_style.m_crDisabledText != CLR_INVALID)
            crDraw = m_style.m_crDisabledText;
    }
    else if (DuiWndState_Hover == (GetState() & DuiWndState_Hover))
    {
        if (m_style.m_ftHover)
            hftDraw = m_style.m_ftHover;

        if (m_style.m_crHoverText != CLR_INVALID)
            crDraw = m_style.m_crHoverText;
    }

    if (hftDraw)
    {
        DuiDC.bFontChanged = TRUE;
        DuiDC.hftOld = dc.SelectFont(hftDraw);
    }

    if (crDraw != CLR_INVALID)
    {
        DuiDC.bTextColorChanged = TRUE;
        DuiDC.crOld = dc.SetTextColor(crDraw);
    }
}

void CDuiWindow::BeforePaintEx( CDCHandle &dc)
{
    CDuiWindow *pParent=GetParent();
    if(pParent) pParent->BeforePaintEx(dc);
    DuiDCPaint DuiDC;
    BeforePaint(dc,DuiDC);
}

void CDuiWindow::AfterPaint(CDCHandle &dc, DuiDCPaint &DuiDC)
{
    if (DuiDC.bFontChanged)
        dc.SelectFont(DuiDC.hftOld);

    if (DuiDC.bTextColorChanged)
        dc.SetTextColor(DuiDC.crOld);

    if (DuiDC.bDuiModeChanged)
        dc.SetBkMode(DuiDC.nOldDuiMode);

    if (DuiDC.bBgColorChanged)
        dc.SetBkColor(DuiDC.crOldBg);
}

// Draw inner text default and focus rect
void CDuiWindow::OnPaint(CDCHandle dc)
{
    DuiDCPaint DuiDC;

    BeforePaint(dc, DuiDC);

    DuiDrawText(dc,m_strInnerText, m_strInnerText.GetLength(), DuiDC.rcClient, m_style.m_nTextAlign|(m_style.m_bDotted?DT_END_ELLIPSIS:0));

    AfterPaint(dc, DuiDC);

    //draw focus rect
    if(GetContainer()->GetDuiFocus()==m_hDuiWnd)
    {
        DuiDrawFocus(dc);
    }
}

void CDuiWindow::OnNcPaint(CDCHandle dc)
{
    if(m_style.m_nMarginX!=0 || m_style.m_nMarginY!=0)
    {
        BOOL bGetDC = dc==0;
        if(bGetDC) dc=GetDuiDC(&m_rcWindow,OLEDC_OFFSCREEN);//不自动画背景
        int nSavedDC=dc.SaveDC();

        CRect rcClient;
        CDuiWindow::GetClient(&rcClient);
        dc.ExcludeClipRect(&rcClient);
        if(bGetDC) PaintBackground(dc,&m_rcWindow);

        DWORD nState=0;
        if(DuiWndState_Hover & m_dwState) nState=1;
        if(m_pNcSkin) m_pNcSkin->Draw(dc,m_rcWindow,nState);
        else
        {
            COLORREF crBg = m_style.m_crBg;
            if (DuiWndState_Hover == (GetState() & DuiWndState_Hover) && CLR_INVALID != m_style.m_crBgHover)
            {
                crBg = m_style.m_crBgHover;
            }
            if (CLR_INVALID != crBg) CGdiAlpha::FillSolidRect(dc,&rcClient, crBg);
        }
        if(bGetDC) PaintForeground(dc,&m_rcWindow);
        dc.RestoreDC(nSavedDC);
        if(bGetDC) ReleaseDuiDC(dc);
    }
}

CRect CDuiWindow::GetViewRect()
{
    return m_rcWindow;
}

void CDuiWindow::OnCalcChildPos(CDuiWindow *pDuiWndChild)
{
    DUIDLG_POSITION dlgPos;
    DUIWNDPOS WndPos = {0};
    CRect rcDlg = GetViewRect();
    if(rcDlg.IsRectEmpty()) return;

    rcDlg.DeflateRect(m_style.m_nMarginX, m_style.m_nMarginY);

    pDuiWndChild->GetDlgPosition(&dlgPos);

    if(dlgPos.nCount==2 || dlgPos.nCount==4)
    {
        if (dlgPos.Left.bCenter)
            WndPos.x = rcDlg.left + rcDlg.Width() / 2 + (dlgPos.Left.bMinus ? -1 : 1) *  dlgPos.Left.nPos;
        else if (dlgPos.Left.bMinus)
            WndPos.x = rcDlg.left + rcDlg.Width() - dlgPos.Left.nPos;
        else
            WndPos.x = rcDlg.left + dlgPos.Left.nPos;

        if (dlgPos.Top.bCenter)
            WndPos.y = rcDlg.top + rcDlg.Height() / 2 + (dlgPos.Top.bMinus ? -1 : 1) *  dlgPos.Top.nPos;
        else if (dlgPos.Top.bMinus)
            WndPos.y = rcDlg.top + rcDlg.Height() - dlgPos.Top.nPos;
        else
            WndPos.y = rcDlg.top + dlgPos.Top.nPos;
    }
    else
    {
        //没有指定合格的pos属性时，使用它的前一个兄弟的右上角坐标，方便自动排版
        WndPos.x=WndPos.y=0;
        CDuiWindow *pPrevSibling=pDuiWndChild->m_pPrevSibling;
        SIZE sz= {0,0};
        pDuiWndChild->DuiSendMessage(WM_CALCSIZE,1,(LPARAM)&sz);
        if(pPrevSibling)
        {
            CRect rcSibling;
            pPrevSibling->GetRect(&rcSibling);
            WndPos.x=rcSibling.right+m_nSepSpace;
            WndPos.y=rcSibling.top;
            if(pDuiWndChild->GetAlign() & VAlign_Middle)
                WndPos.y+=(rcSibling.Height()-sz.cy)/2;
            else if(pDuiWndChild->GetAlign() & VAlign_Bottom)
                WndPos.y+=rcSibling.Height()-sz.cy;
        }
    }

    WndPos.cx=rcDlg.Width();
    WndPos.cy=rcDlg.Height();
    pDuiWndChild->DuiSendMessage(WM_WINDOWPOSCHANGED, NULL, (LPARAM)&WndPos);
}


// Calc DuiWindow size
LRESULT CDuiWindow::OnCalcSize(BOOL bCalcValidRects, LPSIZE pSize)
{
    if (4 == m_dlgpos.nCount)
    {
        CRect rect;

        if (m_dlgpos.Left.bCenter)
            rect.left = pSize->cx / 2 + (m_dlgpos.Left.bMinus ? -1 : 1) *  m_dlgpos.Left.nPos;
        else if (m_dlgpos.Left.bMinus)
            rect.left = pSize->cx - m_dlgpos.Left.nPos;
        else
            rect.left = m_dlgpos.Left.nPos;

        if (m_dlgpos.Right.bCenter)
            rect.right = pSize->cx / 2 + (m_dlgpos.Right.bMinus ? -1 : 1) *  m_dlgpos.Right.nPos;
        else if (m_dlgpos.Right.bMinus)
            rect.right = pSize->cx - m_dlgpos.Right.nPos;
        else
            rect.right = m_dlgpos.Right.nPos;

        if (m_dlgpos.Top.bCenter)
            rect.top = pSize->cy / 2 + (m_dlgpos.Top.bMinus ? -1 : 1) *  m_dlgpos.Top.nPos;
        else if (m_dlgpos.Top.bMinus)
            rect.top = pSize->cy - m_dlgpos.Top.nPos;
        else
            rect.top = m_dlgpos.Top.nPos;

        if (m_dlgpos.Bottom.bCenter)
            rect.bottom = pSize->cy / 2 + (m_dlgpos.Bottom.bMinus ? -1 : 1) *  m_dlgpos.Bottom.nPos;
        else if (m_dlgpos.Bottom.bMinus)
            rect.bottom = pSize->cy - m_dlgpos.Bottom.nPos;
        else
            rect.bottom = m_dlgpos.Bottom.nPos;

        *pSize = rect.Size();
    }
    else
    {
        CDCHandle dcDesktop = ::GetDC(::GetDesktopWindow());
        CDC dcTest;
        HFONT hftOld = NULL, hftTest = NULL;
        CRect rcTest = m_rcWindow;

        dcTest.CreateCompatibleDC(dcDesktop);

        if (bCalcValidRects)
        {
            rcTest.right = rcTest.left + pSize->cx;
            rcTest.bottom = rcTest.top + pSize->cy;
        }

        if (m_style.m_ftText)
            hftTest = m_style.m_ftText;
        else
        {
            CDuiWindow* pWnd = this;

            while (pWnd = pWnd->GetParent())
            {
                if (pWnd->m_style.m_ftText)
                {
                    hftTest = pWnd->m_style.m_ftText;
                    break;
                }
            }

        }

        if (DuiWndState_Hover == (GetState() & DuiWndState_Hover))
        {
            if (m_style.m_ftHover)
                hftTest = m_style.m_ftHover;
            else
            {
                CDuiWindow* pWnd = this;

                while (pWnd = pWnd->GetParent())
                {
                    if (pWnd->m_style.m_ftHover)
                    {
                        hftTest = pWnd->m_style.m_ftHover;
                        break;
                    }
                }
            }
        }

        if (NULL == hftTest)
            hftTest = DuiFontPool::getSingleton().GetFont(DUIF_DEFAULTFONT);

        hftOld = dcTest.SelectFont(hftTest);

        rcTest.DeflateRect(m_style.m_nMarginX, m_style.m_nMarginY);

        int nTestDrawMode = m_style.m_nTextAlign & ~(DT_CENTER | DT_RIGHT | DT_VCENTER | DT_BOTTOM);

        if (nTestDrawMode & DT_WORDBREAK)
            rcTest.bottom = 0x7FFF;

        DuiDrawText(dcTest,m_strInnerText, m_strInnerText.GetLength(), rcTest, nTestDrawMode | DT_CALCRECT);

        pSize->cx = rcTest.Width() + 2 * m_style.m_nMarginX;
        pSize->cy = rcTest.Height() + 2 * m_style.m_nMarginY;

        dcTest.SelectFont(hftOld);

        ::ReleaseDC(::GetDesktopWindow(), dcDesktop);

        if(m_uPositionType & SizeX_Specify)
            pSize->cx=m_lSpecifyWidth;
        if(m_nMaxWidth!=-1 && pSize->cx>m_nMaxWidth)
            pSize->cx=m_nMaxWidth;
        if(m_uPositionType & SizeY_Specify)
            pSize->cy=m_lSpecifyHeight;
    }

    return 0;
}

void CDuiWindow::DuiDrawText(HDC hdc,LPCTSTR pszBuf,int cchText,LPRECT pRect,UINT uFormat)
{
    CGdiAlpha::DrawText(hdc,pszBuf,cchText,pRect,uFormat);
}

void CDuiWindow::DuiDrawFocus(HDC hdc)
{
    CRect rcFocus;
    GetClient(&rcFocus);
    rcFocus.DeflateRect(2,2);

    HBRUSH hbr=(HBRUSH)::GetStockObject(NULL_BRUSH);
    CPen pen;
    pen.CreatePen(PS_DOT,1,RGB(88,88,88));
    CDCHandle dc(hdc);
    HBRUSH hOldBr=dc.SelectBrush(hbr);
    HPEN hOldPen=dc.SelectPen(pen);
    ALPHAINFO ai;
    if(GetContainer()->IsTranslucent()) CGdiAlpha::AlphaBackup(hdc,&rcFocus,ai);
    dc.Rectangle(&rcFocus);
    if(GetContainer()->IsTranslucent()) CGdiAlpha::AlphaRestore(hdc,ai);
    dc.SelectPen(hOldPen);
    dc.SelectBrush(hOldBr);
}

UINT CDuiWindow::OnGetDuiCode()
{
    return 0;
}

BOOL CDuiWindow::IsTabStop()
{
    return FALSE;
}

BOOL CDuiWindow::OnDefKeyDown(UINT nChar, UINT nFlags)
{
    CDuiWindow *pChild=m_pFirstChild;
    while(pChild)
    {
        if(pChild->OnDefKeyDown(nChar,nFlags)) return TRUE;
        pChild=pChild->m_pNextSibling;
    }
    return FALSE;
}

void CDuiWindow::OnShowWindow(BOOL bShow, UINT nStatus)
{
    if(nStatus == ParentShow)
    {
        if(bShow && !IsVisible(FALSE)) bShow=FALSE;
    }
    else
    {
        m_bVisible=bShow;
    }
    if(bShow && m_pParent)
    {
        bShow=m_pParent->IsVisible(TRUE);
    }

    if (bShow)
        ModifyState(0, DuiWndState_Invisible);
    else
        ModifyState(DuiWndState_Invisible, 0);

    CDuiWindow *pChild=m_pFirstChild;
    while(pChild)
    {
        pChild->DuiSendMessage(WM_SHOWWINDOW,bShow,ParentShow);
        pChild=pChild->m_pNextSibling;
    }
    if(!IsVisible(TRUE) && m_hDuiWnd == GetContainer()->GetDuiFocus())
    {
        GetContainer()->OnSetDuiFocus(NULL);
    }
}

void CDuiWindow::OnLButtonDown(UINT nFlags,CPoint pt)
{
    SetDuiCapture();
    ModifyState(DuiWndState_PushDown, 0,TRUE);
}

void CDuiWindow::OnLButtonUp(UINT nFlags,CPoint pt)
{
    ReleaseDuiCapture();
    if(!m_rcWindow.PtInRect(pt)) return;

    ModifyState(0, DuiWndState_PushDown,TRUE);

    LPCTSTR lpszUrl = GetLinkUrl();
    if (lpszUrl && lpszUrl[0])
    {
        HINSTANCE hRet = ::ShellExecute(NULL, L"open", lpszUrl, NULL, NULL, SW_SHOWNORMAL);
    }
    else if (GetCmdID())
    {
        DUINMCOMMAND nms;
        nms.hdr.code = DUINM_COMMAND;
        nms.hdr.hwndFrom = NULL;
        nms.hdr.idFrom = GetCmdID();
        nms.uItemID = GetCmdID();
        nms.szItemClass = GetObjectClass();
        nms.uItemData = GetCmdData();
        DuiNotify((LPNMHDR)&nms);
    }
}

void CDuiWindow::OnMouseHover(WPARAM wParam, CPoint ptPos)
{
    if(GetDuiCapture()==m_hDuiWnd)
        ModifyState(DuiWndState_PushDown,0,FALSE);
    ModifyState(DuiWndState_Hover, 0,TRUE);
    OnNcPaint(0);
}

void CDuiWindow::OnMouseLeave()
{
    if(GetDuiCapture()==m_hDuiWnd)
        ModifyState(0,DuiWndState_PushDown,FALSE);
    ModifyState(0,DuiWndState_Hover,TRUE);
    OnNcPaint(0);
}

BOOL CDuiWindow::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
    BOOL bRet=FALSE;
    if(m_pParent) bRet=(BOOL)m_pParent->DuiSendMessage(WM_MOUSEWHEEL,MAKEWPARAM(nFlags,zDelta),MAKELPARAM(pt.x,pt.y));
    return bRet;
}

HRESULT CDuiWindow::OnAttributeName(const CStringA& strValue, BOOL bLoading)
{
    if(m_uCmdID==0)
    {
        m_uCmdID=DuiSystem::getSingleton().Name2ID(strValue);
    }
    return S_FALSE;
}

HRESULT CDuiWindow::OnAttributePosition(const CStringA& strValue, BOOL bLoading)
{
    if (strValue.IsEmpty()) return E_FAIL;

    LPCSTR lpszValue = strValue;
    int nPos = 0, nPosPrev = 0;

    for (m_dlgpos.nCount = 0; m_dlgpos.nCount < 4; m_dlgpos.nCount ++)
    {
        nPosPrev = nPos;
        nPos = strValue.Find(',', nPosPrev) + 1;

        m_dlgpos.Item[m_dlgpos.nCount].bCenter = ('|' == lpszValue[nPosPrev]);
        if (m_dlgpos.Item[m_dlgpos.nCount].bCenter)
            nPosPrev ++;
        m_dlgpos.Item[m_dlgpos.nCount].bMinus = ('-' == lpszValue[nPosPrev]);
        if (m_dlgpos.Item[m_dlgpos.nCount].bMinus)
            nPosPrev ++;

        if (0 == nPos)
        {
            m_dlgpos.Item[m_dlgpos.nCount].nPos = ::StrToIntA(strValue.Mid(nPosPrev));
            m_dlgpos.nCount ++;
            break;
        }

        m_dlgpos.Item[m_dlgpos.nCount].nPos = ::StrToIntA(strValue.Mid(nPosPrev, nPos - nPosPrev));
    }

    if (2 == m_dlgpos.nCount || 4 == m_dlgpos.nCount)
    {
        m_uPositionType = (m_uPositionType & ~SizeX_Mask) | SizeX_FitContent;
        m_uPositionType = (m_uPositionType & ~SizeY_Mask) | SizeY_FitContent;
    }
    else
        m_dlgpos.nCount = 0;

    return bLoading?S_FALSE:S_OK;
}

void CDuiWindow::OnSetDuiFocus()
{
    NotifyInvalidate();
}

void CDuiWindow::OnKillDuiFocus()
{
    NotifyInvalidate();
}

HDC CDuiWindow::GetDuiDC(const LPRECT pRc/*=NULL*/,DWORD gdcFlags/*=0*/)
{
    DUIASSERT(m_gdcFlags==-1);
    m_rcGetDC=m_rcWindow;
    m_gdcFlags=gdcFlags;
    BOOL bClip=FALSE;
    if(pRc)
    {
        m_rcGetDC.IntersectRect(pRc,&m_rcWindow);
        bClip=!m_rcGetDC.EqualRect(pRc);
    }
    HDC hdc=GetContainer()->OnGetDuiDC(m_rcGetDC,gdcFlags);
    if(bClip)
    {
        m_nSaveDC=SaveDC(hdc);
        CRgn rgn;
        rgn.CreateRectRgnIndirect(&m_rcGetDC);
        SelectClipRgn(hdc,rgn);
    }
    else
    {
        m_nSaveDC=0;
    }
    if(gdcFlags&OLEDC_PAINTBKGND)
        PaintBackground(hdc,&m_rcGetDC);

    return hdc;
}

void CDuiWindow::ReleaseDuiDC(HDC hdc)
{
    if(m_gdcFlags & OLEDC_PAINTBKGND) //画了背景，自动画前景
        PaintForeground(hdc,&m_rcGetDC);
    if(m_nSaveDC!=0) RestoreDC(hdc,m_nSaveDC);
    GetContainer()->OnReleaseDuiDC(hdc,m_rcGetDC,m_gdcFlags);
    m_nSaveDC=0;
    m_gdcFlags=-1;
}

HDUIWND CDuiWindow::GetDuiCapture()
{
    return GetContainer()->GetDuiCapture();
}

HDUIWND CDuiWindow::SetDuiCapture()
{
    return GetContainer()->OnSetDuiCapture(m_hDuiWnd);
}

BOOL CDuiWindow::ReleaseDuiCapture()
{
    return GetContainer()->OnReleaseDuiCapture();
}

void CDuiWindow::SetDuiFocus()
{
    GetContainer()->OnSetDuiFocus(m_hDuiWnd);
}

CDuiWindow *CDuiWindow::GetCheckedRadioButton()
{
    CDuiWindow *pChild=m_pFirstChild;
    while(pChild)
    {
        if(pChild->IsClass("radio") && pChild->IsChecked())
        {
            return pChild;
        }
        pChild=pChild->m_pNextSibling;
    }
    return NULL;
}

void CDuiWindow::CheckRadioButton(CDuiWindow * pRadioBox)
{
    CDuiWindow *pChecked=GetCheckedRadioButton();
    if(pChecked == pRadioBox) return;
    if(pChecked)
    {
        pChecked->ModifyState(0,DuiWndState_Check,TRUE);
    }
    pRadioBox->ModifyState(DuiWndState_Check,0,TRUE);
}


BOOL CDuiWindow::SetItemVisible(UINT uItemID, BOOL bVisible)
{
    CDuiWindow *pWnd = FindChildByCmdID(uItemID);

    if (pWnd)
    {
        pWnd->DuiSendMessage(WM_SHOWWINDOW, (WPARAM)bVisible);
        pWnd->NotifyInvalidate();
        return TRUE;
    }

    return FALSE;
}

BOOL CDuiWindow::IsItemVisible(UINT uItemID, BOOL bCheckParent /*= FALSE*/)
{
    CDuiWindow *pWnd = FindChildByCmdID(uItemID);

    if (pWnd)
        return pWnd->IsVisible(bCheckParent);

    return FALSE;
}

BOOL CDuiWindow::GetItemCheck(UINT uItemID)
{
    CDuiWindow *pWnd = FindChildByCmdID(uItemID);

    if (pWnd)
        return pWnd->IsChecked();

    return FALSE;
}

BOOL CDuiWindow::SetItemCheck(UINT uItemID, BOOL bCheck)
{
    CDuiWindow *pWnd = FindChildByCmdID(uItemID);

    if (pWnd)
    {
        if (bCheck)
            pWnd->ModifyState(DuiWndState_Check, 0);
        else
            pWnd->ModifyState(0, DuiWndState_Check);

        pWnd->NotifyInvalidate();

        return TRUE;
    }

    return FALSE;
}

BOOL CDuiWindow::EnableItem(UINT uItemID, BOOL bEnable)
{
    CDuiWindow *pWnd = FindChildByCmdID(uItemID);

    if (pWnd)
    {
        if (bEnable)
            pWnd->ModifyState(0, DuiWndState_Disable);
        else
            pWnd->ModifyState(DuiWndState_Disable, DuiWndState_Hover);

        pWnd->NotifyInvalidate();
        return TRUE;
    }

    return FALSE;
}

BOOL CDuiWindow::IsItemEnable(UINT uItemID, BOOL bCheckParent /*= FALSE*/)
{
    CDuiWindow *pWnd = FindChildByCmdID(uItemID);

    if (pWnd)
        return !pWnd->IsDisabled(bCheckParent);

    return FALSE;
}

BOOL CDuiWindow::OnDuiNcHitTest(CPoint pt)
{
    return FALSE;
}

BOOL CDuiWindow::IsMsgHandled() const
{
    return m_bMsgHandled;
}

void CDuiWindow::SetMsgHandled(BOOL bHandled)
{
    m_bMsgHandled = bHandled;
}


CDuiWindow * CDuiWindow::GetDuiWindow(int uCode)
{
    CDuiWindow *pRet=NULL;
    switch(uCode)
    {
    case GDUI_FIRSTCHILD:
        pRet=m_pFirstChild;
        break;
    case GDUI_LASTCHILD:
        pRet=m_pLastChild;
        break;
    case GDUI_PREVSIBLING:
        pRet=m_pPrevSibling;
        break;
    case GDUI_NEXTSIBLING:
        pRet=m_pNextSibling;
        break;
    case GDUI_OWNER:
        pRet=m_pOwner;
        break;
    case GDUI_PARENT:
        pRet=m_pParent;
        break;
    }
    return pRet;
}


void CDuiWindow::PaintBackground( HDC hdc,LPRECT pRc )
{
    CRect rcDraw=m_rcWindow;
    if(pRc) rcDraw.IntersectRect(rcDraw,pRc);

    CDuiWindow *pTopWnd=GetTopLevelParent();
    int nSavedDC=::SaveDC(hdc);
    CRgn rgn;
    rgn.CreateRectRgnIndirect(&rcDraw);
    ::ExtSelectClipRgn(hdc,rgn,RGN_AND);
	CDCHandle dc(hdc);
	dc.FillSolidRect(pRc,0);//清除残留的alpha值

    CDuiWindow *pEnd=this;
    while(pEnd && !pEnd->IsVisible(TRUE))
    {
        pEnd=pEnd->GetParent();
    }

    if(pEnd)
    {
        if(pEnd!=this) // 将pEnd的第一个子窗口作为结束绘制标志
            pEnd=pEnd->GetDuiWindow(GDUI_FIRSTCHILD);
        _PaintBackground(hdc,&rcDraw,pTopWnd,pEnd);
    }

    ::RestoreDC(hdc,nSavedDC);
}

BOOL CDuiWindow::_PaintBackground(HDC hdc,CRect *pRc,CDuiWindow *pCurWnd,CDuiWindow *pEnd)
{
    if(pCurWnd==pEnd )	return TRUE; //不管pEnd是否可见都退出

    if(!pCurWnd->IsVisible(TRUE) || ((*pRc)&pCurWnd->m_rcWindow).IsRectEmpty())
        return FALSE;

    BOOL bRet=FALSE;

    pCurWnd->DuiSendMessage(WM_ERASEBKGND, (WPARAM)hdc);
    pCurWnd->DuiSendMessage(WM_PAINT, (WPARAM)hdc);

    DuiDCPaint DuiDC;
    CDCHandle dc(hdc);
    pCurWnd->BeforePaint(dc, DuiDC);	//让子窗口继承父窗口的属性

    CDuiWindow *pChild=pCurWnd->GetDuiWindow(GDUI_FIRSTCHILD);
    while(pChild)
    {
        bRet=_PaintBackground(hdc,pRc,pChild,pEnd);
        if(bRet) break;
        pChild=pChild->GetDuiWindow(GDUI_NEXTSIBLING);
    }
    pCurWnd->AfterPaint(dc, DuiDC);

    pCurWnd->DuiSendMessage(WM_NCPAINT, (WPARAM)(HDC)dc);//ncpaint should be placed in tail of paint link

    return bRet;
}



void CDuiWindow::PaintForeground( HDC hdc,LPRECT pRc )
{
    CRect rcDraw=m_rcWindow;
    if(pRc) rcDraw.IntersectRect(rcDraw,pRc);

    CDuiWindow *pTopWnd=GetTopLevelParent();
    int nSavedDC=::SaveDC(hdc);
    CRgn rgn;
    rgn.CreateRectRgnIndirect(&rcDraw);
    ::ExtSelectClipRgn(hdc,rgn,RGN_AND);

    CDuiWindow *pStart=this;
    while(pStart && !pStart->IsVisible(TRUE))
    {
        pStart=pStart->GetParent();
    }

    if(pStart)
    {
        BOOL bInRange=FALSE;
        _PaintForeground(hdc,&rcDraw,pTopWnd,pStart,bInRange);
    }

    ::RestoreDC(hdc,nSavedDC);
}

void CDuiWindow::_PaintForeground(HDC hdc,CRect *pRc,CDuiWindow *pCurWnd,CDuiWindow *pStart,BOOL &bInRange)
{
    DUIASSERT(pStart->IsVisible(TRUE));

    if(!pCurWnd->IsVisible(TRUE) || ((*pRc)&pCurWnd->m_rcWindow).IsRectEmpty())
        return ;

    if(bInRange)
    {
        pCurWnd->DuiSendMessage(WM_ERASEBKGND, (WPARAM)hdc);
        pCurWnd->DuiSendMessage(WM_PAINT, (WPARAM)hdc);
    }

    DuiDCPaint DuiDC;
    CDCHandle dc(hdc);
    pCurWnd->BeforePaint(dc, DuiDC);	//让子窗口继承父窗口的属性

    CDuiWindow *pChild=pCurWnd->GetDuiWindow(GDUI_FIRSTCHILD);
    while(pChild)
    {
        _PaintForeground(hdc,pRc,pChild,pStart,bInRange);
        pChild=pChild->GetDuiWindow(GDUI_NEXTSIBLING);
    }

    pCurWnd->AfterPaint(dc, DuiDC);

    if(bInRange)
    {
        pCurWnd->DuiSendMessage(WM_NCPAINT, (WPARAM)(HDC)dc);//ncpaint should be placed in tail of paint link
    }

    if(pCurWnd==pStart) bInRange=TRUE;//画前景时，pStart指定的窗口不绘制
}

BOOL CDuiWindow::AnimateWindow(DWORD dwTime,DWORD dwFlags )
{
    return FALSE;
}

}//namespace DuiEngine
