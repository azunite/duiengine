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


CDuiFrame::CDuiFrame():m_hCapture(NULL),m_hHover(NULL),m_hFocus(NULL),m_bNcHover(FALSE)
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


BOOL CDuiFrame::OnReleaseDuiCapture(){
	m_hCapture=NULL;
	return TRUE;
}

HDUIWND CDuiFrame::OnSetDuiCapture(HDUIWND hDuiWnd)
{
	HDUIWND hRet=m_hCapture;
	m_hCapture=hDuiWnd;
	return hRet;
}

void CDuiFrame::OnSetDuiFocus(HDUIWND hDuiWnd)
{
	CDuiWindow *pFocus=DuiWindowManager::GetWindow(m_hFocus);
	if(pFocus) pFocus->DuiSendMessage(WM_KILLFOCUS);
	m_hFocus=hDuiWnd;
	pFocus=DuiWindowManager::GetWindow(m_hFocus);
	if(pFocus) pFocus->DuiSendMessage(WM_SETFOCUS);
}

HDUIWND CDuiFrame::GetDuiCapture(){return m_hCapture;}

HDUIWND CDuiFrame::GetDuiFocus(){return m_hFocus;}

HDUIWND CDuiFrame::GetDuiHover(){return m_hHover;}

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
			if(pHover)
			{
				m_bNcHover=pHover->OnDuiNcHitTest(pt);
				if(m_bNcHover) pHover->DuiSendMessage(WM_NCMOUSEHOVER,uFlag,MAKELPARAM(pt.x,pt.y));
				pHover->DuiSendMessage(WM_MOUSEHOVER,uFlag,MAKELPARAM(pt.x,pt.y));
			}
		}else if(pHover)
		{
			BOOL bNcHover=pHover->OnDuiNcHitTest(pt);
			if(bNcHover!=m_bNcHover) 
			{
				m_bNcHover=bNcHover;
				if(m_bNcHover)
				{
					pHover->DuiSendMessage(WM_NCMOUSEHOVER,uFlag,MAKELPARAM(pt.x,pt.y));
				}else
				{
					pHover->DuiSendMessage(WM_NCMOUSELEAVE);
				}
			}
		}
		if(pHover) pHover->DuiSendMessage(m_bNcHover?WM_NCMOUSEMOVE:WM_MOUSEMOVE,uFlag,MAKELPARAM(pt.x,pt.y));
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
		if(pHover) pHover->DuiSendMessage(m_bNcHover?WM_NCMOUSELEAVE:WM_MOUSELEAVE);
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
	CDuiWindow *pFocus=DuiWindowManager::GetWindow(m_hFocus);
	if(pFocus)
	{
		pFocus->DuiSendMessage(uMsg,wParam,lParam);
	}
}

void CDuiFrame::OnFrameKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CDuiWindow *pFocus=DuiWindowManager::GetWindow(m_hFocus);
	UINT uCode=pFocus?pFocus->OnGetDuiCode():0;

	WORD wCtrl=::GetKeyState(VK_CONTROL);
	if(!(wCtrl&0x8000)  && nChar==VK_RETURN && !(uCode & DUIC_WANTRETURN))
	{//处理RETURN
		if(!OnDefKeyDown(nChar,nFlags))
			::SendMessage(GetContainer()->GetHostHwnd(),WM_COMMAND,IDOK,0);
		return;
	}
	if(!(wCtrl&0x8000) && nChar == VK_ESCAPE && uCode != DUIC_WANTALLKEYS)
	{//处理ESCAPE
		::SendMessage(GetContainer()->GetHostHwnd(),WM_COMMAND,IDCANCEL,0);
		return;
	}

	if(nChar==VK_TAB)
	{//首先处理tab按键
		if(pFocus)
		{
			if(uCode & DUIC_WANTTAB)
			{
				pFocus->DuiSendMessage(WM_KEYDOWN,nChar,MAKELPARAM(nRepCnt,nFlags));
				return;
			}
		}else
		{
			if(this->IsTabStop()!=0)
			{
				this->SetDuiFocus();
				return;
			}
			pFocus=this;
		}
		CDuiWindow *pNextFocus=GetNextKeyHostWnd(pFocus,pFocus);
		if(pNextFocus)
		{
			pNextFocus->SetDuiFocus();
			return;
		}
	}
	if(pFocus)
	{
		pFocus->DuiSendMessage(WM_KEYDOWN,nChar,MAKELPARAM(nRepCnt,nFlags));
	}
}

CDuiWindow * CDuiFrame::GetNextKeyHostWnd(CDuiWindow *pCurWnd,CDuiWindow *pFirst)
{
	CDuiWindow *pChild=pCurWnd->GetDuiWindow(GDUI_FIRSTCHILD);
	if(pChild)
	{
		if(pChild->IsTabStop()&& pChild->IsVisible(TRUE) && !pChild->IsDisabled(TRUE))
			{ if(pChild==pFirst) return NULL; else return pChild;}
		else 
			return GetNextKeyHostWnd(pChild,pFirst);
	}

	CDuiWindow *pParent=NULL;
	while(pCurWnd)
	{
		CDuiWindow *pNextSibling=pCurWnd->GetDuiWindow(GDUI_NEXTSIBLING);
		while(pNextSibling)
		{//没有子节点的兄弟结点不递归调用，以提高效率。
			if(pNextSibling->IsTabStop() && pNextSibling->IsVisible(TRUE) && !pNextSibling->IsDisabled(TRUE))
			{
				if(pNextSibling==pFirst) 
					return NULL;
				else 
					return pNextSibling;
			}
			else
			{
				if(pNextSibling->GetDuiWindow(GDUI_FIRSTCHILD))
					return GetNextKeyHostWnd(pNextSibling,pFirst);
				else 
					pNextSibling=pNextSibling->GetDuiWindow(GDUI_NEXTSIBLING);
			}
		}
		pParent=pCurWnd;//save current duiwindow level 
		pCurWnd=pCurWnd->GetDuiWindow(GDUI_PARENT);
	}
	//search next char host win from the very top win
	if(pParent!=pFirst)
		return GetNextKeyHostWnd(pParent,pFirst);
	else
		return NULL;
}

}//namespace DuiEngine
