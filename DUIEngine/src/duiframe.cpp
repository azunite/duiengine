//////////////////////////////////////////////////////////////////////////
//  Class Name: CDuiFrame
// Description: A DuiWindow Frame.
//     Creator: Huang Jianxiong
//     Version: 2011.9.1 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////
#include "duistd.h"
#include "duiframe.h"


namespace DuiEngine
{

#define WM_NCMOUSEFIRST WM_NCMOUSEMOVE
#define WM_NCMOUSELAST  WM_NCMBUTTONDBLCLK


CDuiFrame::CDuiFrame()
	:m_hCapture(NULL)
	,m_hHover(NULL)
	,m_bNcHover(FALSE)
	,m_dropTarget(this)
	,m_focusMgr(this)
{
}

LRESULT CDuiFrame::DoFrameEvent(UINT uMsg,WPARAM wParam,LPARAM lParam)
{
    LRESULT lRet=0;
    AddRef();
    SetMsgHandled(TRUE);

    switch(uMsg)
    {
    case WM_MOUSEMOVE:
        OnFrameMouseMove((UINT)wParam,CPoint(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)));
        break;
    case WM_MOUSEHOVER:
        OnFrameMouseEvent(uMsg,wParam,lParam);
        break;
    case WM_MOUSELEAVE:
        OnFrameMouseLeave();
        break;
    case WM_SETCURSOR:
    {
        lRet=OnFrameSetCursor(CPoint(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)));
        if(!lRet)
        {
            SetCursor(LoadCursor(NULL,IDC_ARROW));
        }
    }
    break;
    case WM_KEYDOWN:
        OnFrameKeyDown((UINT)wParam,(UINT)lParam & 0xFFFF, (UINT)((lParam & 0xFFFF0000) >> 16));
        break;
	case WM_ACTIVATE:
		OnActivate(LOWORD(wParam));
		break;
    default:
        if(uMsg>=WM_KEYFIRST && uMsg<=WM_KEYLAST)
            OnFrameKeyEvent(uMsg,wParam,lParam);
        else if(uMsg>=WM_MOUSEFIRST && uMsg <= WM_MOUSELAST)
            OnFrameMouseEvent(uMsg,wParam,lParam);
        else
            SetMsgHandled(FALSE);
        break;
    }

    Release();
    return lRet;
}


BOOL CDuiFrame::OnReleaseDuiCapture()
{
    m_hCapture=NULL;
    return TRUE;
}

HDUIWND CDuiFrame::OnSetDuiCapture(HDUIWND hDuiWnd)
{
	CDuiWindow *pWnd=DuiWindowManager::GetWindow(hDuiWnd);
	DUIASSERT(pWnd);
	if(pWnd->IsDisabled(TRUE)) return 0;

    HDUIWND hRet=m_hCapture;
    m_hCapture=hDuiWnd;
    return hRet;
}

void CDuiFrame::OnSetDuiFocus(HDUIWND hDuiWnd)
{
	m_focusMgr.SetFocusedHwnd(hDuiWnd);
}

HDUIWND CDuiFrame::GetDuiCapture()
{
    return m_hCapture;
}

HDUIWND CDuiFrame::GetDuiFocus()
{
    return m_focusMgr.GetFocusedHwnd();
}

HDUIWND CDuiFrame::GetDuiHover()
{
    return m_hHover;
}

void CDuiFrame::OnFrameMouseMove(UINT uFlag,CPoint pt)
{
    CDuiWindow *pCapture=DuiWindowManager::GetWindow(m_hCapture);
    if(pCapture)
    {
        CRect rc;
        pCapture->GetRect(&rc);
        CDuiWindow * pHover=rc.PtInRect(pt)?pCapture:NULL;
        HDUIWND hHover=pHover?pHover->GetDuiHwnd():NULL;
        if(hHover!=m_hHover)
        {
            CDuiWindow *pOldHover=DuiWindowManager::GetWindow(m_hHover);
            m_hHover=hHover;
            if(pOldHover) pOldHover->DuiSendMessage(m_bNcHover?WM_NCMOUSELEAVE:WM_MOUSELEAVE);
            if(pHover)	pHover->DuiSendMessage(m_bNcHover?WM_NCMOUSEHOVER:WM_MOUSEHOVER,uFlag,MAKELPARAM(pt.x,pt.y));
        }
        pCapture->DuiSendMessage(m_bNcHover?WM_NCMOUSEMOVE:WM_MOUSEMOVE,uFlag,MAKELPARAM(pt.x,pt.y));
    }
    else
    {
        HDUIWND hHover=DuiGetHWNDFromPoint(pt,FALSE);
        CDuiWindow * pHover=DuiWindowManager::GetWindow(hHover);
        if(m_hHover!=hHover)
        {
            CDuiWindow *pOldHover=DuiWindowManager::GetWindow(m_hHover);
            m_hHover=hHover;
            if(pOldHover)
            {
                if(m_bNcHover) pOldHover->DuiSendMessage(WM_NCMOUSELEAVE);
                pOldHover->DuiSendMessage(WM_MOUSELEAVE);
            }
            if(pHover && !pHover->IsDisabled(TRUE))
            {
                m_bNcHover=pHover->OnDuiNcHitTest(pt);
                if(m_bNcHover) pHover->DuiSendMessage(WM_NCMOUSEHOVER,uFlag,MAKELPARAM(pt.x,pt.y));
                pHover->DuiSendMessage(WM_MOUSEHOVER,uFlag,MAKELPARAM(pt.x,pt.y));
            }
        }
        else if(pHover && !pHover->IsDisabled(TRUE))
        {
            BOOL bNcHover=pHover->OnDuiNcHitTest(pt);
            if(bNcHover!=m_bNcHover)
            {
                m_bNcHover=bNcHover;
                if(m_bNcHover)
                {
                    pHover->DuiSendMessage(WM_NCMOUSEHOVER,uFlag,MAKELPARAM(pt.x,pt.y));
                }
                else
                {
                    pHover->DuiSendMessage(WM_NCMOUSELEAVE);
                }
            }
        }
        if(pHover && !pHover->IsDisabled(TRUE))
			pHover->DuiSendMessage(m_bNcHover?WM_NCMOUSEMOVE:WM_MOUSEMOVE,uFlag,MAKELPARAM(pt.x,pt.y));
    }
}

void CDuiFrame::OnFrameMouseLeave()
{
    CDuiWindow *pCapture=DuiWindowManager::GetWindow(m_hCapture);
    if(pCapture)
    {
        pCapture->DuiSendMessage(WM_MOUSELEAVE);
    }
    else if(m_hHover)
    {
        CDuiWindow *pHover=DuiWindowManager::GetWindow(m_hHover);
        if(pHover && !pHover->IsDisabled(TRUE))
			pHover->DuiSendMessage(m_bNcHover?WM_NCMOUSELEAVE:WM_MOUSELEAVE);
    }
    m_hHover=NULL;
}


BOOL CDuiFrame::OnFrameSetCursor(const CPoint &pt)
{
    CDuiWindow *pCapture=DuiWindowManager::GetWindow(m_hCapture);
    if(pCapture) return pCapture->OnDuiSetCursor(pt);
    else
    {
        CDuiWindow *pHover=DuiWindowManager::GetWindow(m_hHover);
        if(pHover && !pHover->IsDisabled(TRUE)) return pHover->OnDuiSetCursor(pt);
    }
    return FALSE;
}

void CDuiFrame::OnFrameMouseEvent(UINT uMsg,WPARAM wParam,LPARAM lParam)
{
    CDuiWindow *pCapture=DuiWindowManager::GetWindow(m_hCapture);
    if(pCapture)
    {
        if(m_bNcHover && uMsg!=WM_MOUSEWHEEL) uMsg += WM_NCMOUSEFIRST - WM_MOUSEFIRST;//转换成NC对应的消息
        pCapture->DuiSendMessage(uMsg,wParam,lParam);
    }
    else
    {
        m_hHover=DuiGetHWNDFromPoint(CPoint(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)),FALSE);
        CDuiWindow *pHover=DuiWindowManager::GetWindow(m_hHover);
        if(pHover  && !pHover->IsDisabled(TRUE))
        {
            if(m_bNcHover && uMsg!=WM_MOUSEWHEEL) uMsg += WM_NCMOUSEFIRST - WM_MOUSEFIRST;//转换成NC对应的消息
            pHover->DuiSendMessage(uMsg,wParam,lParam);
        }
    }
}

void CDuiFrame::OnFrameKeyEvent(UINT uMsg,WPARAM wParam,LPARAM lParam)
{
    CDuiWindow *pFocus=DuiWindowManager::GetWindow(m_focusMgr.GetFocusedHwnd());
    if(pFocus)
    {
        pFocus->DuiSendMessage(uMsg,wParam,lParam);
    }
}

void CDuiFrame::OnFrameKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(m_focusMgr.OnKeyDown(nChar)) return; //首先处理焦点切换

    CDuiWindow *pFocus=DuiWindowManager::GetWindow(m_focusMgr.GetFocusedHwnd());
    if(pFocus)
    {
        pFocus->DuiSendMessage(WM_KEYDOWN,nChar,MAKELPARAM(nRepCnt,nFlags));
    }
}

BOOL CDuiFrame::RegisterDragDrop( HDUIWND hDuiWnd,IDropTarget *pDropTarget )
{
	return m_dropTarget.RegisterDragDrop(hDuiWnd,pDropTarget);
}

BOOL CDuiFrame::RevokeDragDrop( HDUIWND hDuiWnd )
{
	return m_dropTarget.RevokeDragDrop(hDuiWnd);
}

void CDuiFrame::OnActivate( UINT nState )
{
	if(nState==WA_INACTIVE)
	{
		m_focusMgr.StoreFocusedView();
	}else if(nState==WA_ACTIVE)
	{
		m_focusMgr.RestoreFocusedView();
	}
}

}//namespace DuiEngine
