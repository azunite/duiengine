//////////////////////////////////////////////////////////////////////////
//   File Name: duiwndpanel.h
// Description: CDuiPanel Definition,  Container of DuiWindows
//     Creator: Zhang Xiaoxuan
//     Version: 2009.04.28 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "duistd.h"
#include "duiwndpanel.h"

namespace DuiEngine{

// Hittest children
HDUIWND CDuiPanel::DuiGetHWNDFromPoint(POINT ptHitTest, BOOL bOnlyText)
{
	if (!m_rcWindow.PtInRect(ptHitTest)) return NULL;

	if (m_bOnlyDrawChild)
		return m_hDuiWnd;

	return __super::DuiGetHWNDFromPoint(ptHitTest,bOnlyText);
}

CDuiPanelEx::CDuiPanelEx()
:m_pSkinSb(DuiSkinPool::getSingleton().GetSkin("sb_common"))
,m_nSbArrowSize(-1) 
,m_nSbWid(-1)
,m_bDragSb(FALSE)
,m_wBarVisible(0)
,m_wBarEnable(DUISB_BOTH)
{
	memset(&m_siHoz,0,sizeof(SCROLLINFO));
	memset(&m_siVer,0,sizeof(SCROLLINFO));
 	m_HitInfo.uSbCode=-1;
	m_siHoz.nTrackPos=-1;
	m_siVer.nTrackPos=-1;
}

BOOL CDuiPanelEx::ShowScrollBar( int wBar, BOOL bShow )
{
	if(bShow) m_wBarVisible|=wBar;
	else m_wBarVisible&=~wBar;
	DuiSendMessage(WM_NCCALCSIZE);
	NotifyInvalidate();
	return TRUE;
}


BOOL CDuiPanelEx::EnableScrollBar( int wBar,BOOL bEnable )
{
	if(bEnable) m_wBarEnable|=wBar;
	else m_wBarEnable&=~wBar;
	if(wBar & DUISB_VERT)
	{
		CRect rcSb=GetScrollBarRect(TRUE);
		NotifyInvalidateRect(rcSb);
	}
	if(wBar & DUISB_HORZ)
	{
		CRect rcSb=GetScrollBarRect(FALSE);
		NotifyInvalidateRect(rcSb);
	}
	return TRUE;
}


BOOL CDuiPanelEx::IsScrollBarEnable( BOOL bVertical )
{
	return m_wBarEnable&(bVertical?DUISB_VERT:DUISB_HORZ);
}

void CDuiPanelEx::SetScrollInfo(SCROLLINFO si,BOOL bVertical)
{
	SCROLLINFO *psi=bVertical?(&m_siVer):(&m_siHoz);
	if(si.fMask & SIF_RANGE)
	{
		psi->nMin=si.nMin;
		psi->nMax=si.nMax;
	}
	if(si.fMask & SIF_PAGE) psi->nPage=si.nPage;
	if (si.fMask & SIF_POS) psi->nPos=si.nPos;
	if(si.fMask & SIF_TRACKPOS) psi->nTrackPos=si.nTrackPos;
	if(si.nPage==0) psi->nPos=0;
	else
	{
		if(psi->nPos>(psi->nMax-(int)psi->nPage+1)) psi->nPos=(psi->nMax-psi->nPage+1);
		if(psi->nPos<psi->nMin) psi->nPos=psi->nMin;
	}
}

BOOL CDuiPanelEx::SetScrollPos(BOOL bVertical, int nNewPos,BOOL bRedraw)
{
	SCROLLINFO *psi=bVertical?(&m_siVer):(&m_siHoz);

	//make sure nNewPos is valid.
	if(nNewPos<psi->nMin) nNewPos=psi->nMin;
	if(nNewPos>psi->nMax - (int)psi->nPage+1) nNewPos=psi->nMax-psi->nPage+1;

	psi->nPos=nNewPos;

	if(bRedraw)
	{
		CRect rcSb=GetScrollBarRect(bVertical);
		NotifyInvalidateRect(rcSb);
	}
	OnScroll(bVertical,SB_THUMBPOSITION,nNewPos);
	return TRUE;
}

int CDuiPanelEx::GetScrollPos(BOOL bVertical)
{
	return bVertical?m_siVer.nPos:m_siHoz.nPos;
}


BOOL CDuiPanelEx::SetScrollRange( BOOL bVertical,int nMinPos,int nMaxPos,BOOL bRedraw )
{
	SCROLLINFO *psi=bVertical?(&m_siVer):(&m_siHoz);
	psi->nMin=nMinPos;
	psi->nMax=nMaxPos;

	if(psi->nPos<psi->nMin) psi->nPos=psi->nMin;
	if(psi->nPos>psi->nMax - (int)psi->nPage+1) psi->nPos=psi->nMax-psi->nPage+1;

	if(bRedraw)
	{
		CRect rcSb=GetScrollBarRect(bVertical);
		NotifyInvalidateRect(rcSb);
	}
	return TRUE;
}

BOOL CDuiPanelEx::GetScrollRange( BOOL bVertical, LPINT lpMinPos, LPINT lpMaxPos )
{
	SCROLLINFO *psi=bVertical?(&m_siVer):(&m_siHoz);
	if(lpMaxPos) *lpMaxPos=psi->nMax;
	if(lpMinPos) *lpMinPos=psi->nMin;
	return TRUE;
}

BOOL CDuiPanelEx::HasScrollBar(BOOL bVertical)
{
	return m_wBarVisible&(bVertical?DUISB_VERT:DUISB_HORZ);
}


CRect CDuiPanelEx::GetSbPartRect(BOOL bVertical,UINT uSBCode)
{
	DUIASSERT(m_pSkinSb);
	CRect rcSb=GetScrollBarRect(bVertical);
	if(rcSb.IsRectEmpty()) return rcSb;

	SCROLLINFO *psi=bVertical?(&m_siVer):(&m_siHoz);
	int nTrackPos=psi->nTrackPos;
	int nMax=psi->nMax;
	if(nMax<psi->nMin+(int)psi->nPage-1) nMax=psi->nMin+psi->nPage-1;

	if(nTrackPos==-1) 
		nTrackPos=psi->nPos;
	int nLength=(bVertical?rcSb.Height():rcSb.Width());
	int nInterHei=nLength-2*m_nSbArrowSize;
	if(nInterHei<0) 
		nInterHei=0;
	int	nSlideHei=psi->nPage*nInterHei/(nMax-psi->nMin+1);
	if(nMax==psi->nMin+psi->nPage-1) 
		nSlideHei=nInterHei;
	if(nSlideHei<THUMB_MINSIZE) 
		nSlideHei=THUMB_MINSIZE;
	if(nInterHei<THUMB_MINSIZE) 
		nSlideHei=0;
	int nEmptyHei=nInterHei-nSlideHei;
	int nArrowHei=m_nSbArrowSize;
	if(nInterHei==0) 
		nArrowHei=nLength/2;

	CRect rcRet(0,0,rcSb.Width(),nArrowHei);
	if(uSBCode==SB_LINEUP) goto end;
	rcRet.top=rcRet.bottom;
	if((psi->nMax-psi->nMin-psi->nPage+1)==0)
		rcRet.bottom+=nEmptyHei/2;
	else
		rcRet.bottom+=nEmptyHei*nTrackPos/(psi->nMax-psi->nMin-psi->nPage+1);
	if(uSBCode==SB_PAGEUP) goto end;
	rcRet.top=rcRet.bottom;
	rcRet.bottom+=nSlideHei;
	if(uSBCode==SB_THUMBTRACK) goto end;
	rcRet.top=rcRet.bottom;
	rcRet.bottom=nLength-nArrowHei;
	if(uSBCode==SB_PAGEDOWN) goto end;
	rcRet.top=rcRet.bottom;
	rcRet.bottom=nLength;
	if(uSBCode==SB_LINEDOWN) goto end;
end:
	if(!bVertical)
	{
		rcRet.left=rcRet.top;
		rcRet.right=rcRet.bottom;
		rcRet.top=0;
		rcRet.bottom=rcSb.Height();
	}
	rcRet.OffsetRect(rcSb.TopLeft());
	return rcRet;
}

CRect CDuiPanelEx::GetScrollBarRect(BOOL bVertical)
{
	CRect rcSb;
	if(!HasScrollBar(bVertical)) return rcSb;

	__super::GetClient(&rcSb);

	if(bVertical)
	{
		rcSb.left=rcSb.right-m_nSbWid;
	}else
	{
		rcSb.top=rcSb.bottom-m_nSbWid;
	}
	if(HasScrollBar(!bVertical))
	{
		if(bVertical)
		{
			rcSb.bottom-=m_nSbWid;
		}else
		{
			rcSb.right-=m_nSbWid;
		}
	}
	return rcSb;
}

CDuiPanelEx::SBHITINFO CDuiPanelEx::HitTest(CPoint pt)
{
	SBHITINFO hi={-1,0,0};
	CRect rcSbVer=GetScrollBarRect(TRUE);
	CRect rcSbHoz=GetScrollBarRect(FALSE);
	if(rcSbHoz.PtInRect(pt)) hi.bVertical=FALSE;
	else if(rcSbVer.PtInRect(pt)) hi.bVertical=TRUE;
	else return hi;

	if(GetSbPartRect(hi.bVertical,SB_LINEUP).PtInRect(pt)) hi.uSbCode=SB_LINEUP;
	else if(GetSbPartRect(hi.bVertical,SB_LINEDOWN).PtInRect(pt)) hi.uSbCode= SB_LINEDOWN;
	else if(GetSbPartRect(hi.bVertical,SB_THUMBTRACK).PtInRect(pt)) hi.uSbCode= SB_THUMBTRACK;
	else if(GetSbPartRect(hi.bVertical,SB_PAGEUP).PtInRect(pt)) hi.uSbCode= SB_PAGEUP;
	else if(GetSbPartRect(hi.bVertical,SB_PAGEDOWN).PtInRect(pt)) hi.uSbCode= SB_PAGEDOWN;

	return hi;

}

int CDuiPanelEx::OnCreate(LPVOID)
{
	int nRet=__super::OnCreate(NULL);

	if(nRet!=0) return nRet;
	DUIASSERT(m_pSkinSb);
	SIZE szSbSkin=m_pSkinSb->GetSkinSize();
	if(m_nSbWid==-1) m_nSbWid=szSbSkin.cx/9;
	if(m_nSbArrowSize==-1) m_nSbArrowSize=szSbSkin.cx/9;

	return 0;
}

void CDuiPanelEx::OnNcPaint(CDCHandle dc)
{
	__super::OnNcPaint(dc);
	CRect rcDest;
	//绘制滚动条
	if(HasScrollBar(TRUE))
	{
		int nState=(IsDisabled(TRUE) || !IsScrollBarEnable(TRUE))?3:0;
		rcDest=GetSbPartRect(TRUE,SB_LINEUP);
		m_pSkinSb->Draw(dc,rcDest,MAKESBSTATE(SB_LINEUP,nState,TRUE));
		rcDest=GetSbPartRect(TRUE,SB_PAGEUP);
		m_pSkinSb->Draw(dc,rcDest,MAKESBSTATE(SB_PAGEUP,nState,TRUE));
		rcDest=GetSbPartRect(TRUE,SB_THUMBTRACK);
		m_pSkinSb->Draw(dc,rcDest,MAKESBSTATE(SB_THUMBTRACK,nState,TRUE));
		rcDest=GetSbPartRect(TRUE,SB_PAGEDOWN);
		m_pSkinSb->Draw(dc,rcDest,MAKESBSTATE(SB_PAGEDOWN,nState,TRUE));
		rcDest=GetSbPartRect(TRUE,SB_LINEDOWN);
		m_pSkinSb->Draw(dc,rcDest,MAKESBSTATE(SB_LINEDOWN,nState,TRUE));
	}
	if(HasScrollBar(FALSE))
	{
		int nState=(IsDisabled(TRUE) || !IsScrollBarEnable(FALSE))?3:0;
		rcDest=GetSbPartRect(FALSE,SB_LINEUP);
		m_pSkinSb->Draw(dc,rcDest,MAKESBSTATE(SB_LINEUP,nState,FALSE));
		rcDest=GetSbPartRect(FALSE,SB_PAGEUP);
		m_pSkinSb->Draw(dc,rcDest,MAKESBSTATE(SB_PAGEUP,nState,FALSE));
		rcDest=GetSbPartRect(FALSE,SB_THUMBTRACK);
		m_pSkinSb->Draw(dc,rcDest,MAKESBSTATE(SB_THUMBTRACK,nState,FALSE));
		rcDest=GetSbPartRect(FALSE,SB_PAGEDOWN);
		m_pSkinSb->Draw(dc,rcDest,MAKESBSTATE(SB_PAGEDOWN,nState,FALSE));
		rcDest=GetSbPartRect(FALSE,SB_LINEDOWN);
		m_pSkinSb->Draw(dc,rcDest,MAKESBSTATE(SB_LINEDOWN,nState,FALSE));
	}

	if(HasScrollBar(TRUE) && HasScrollBar(FALSE))
	{
		CRect rcDest;
		__super::GetClient(&rcDest);
		rcDest.left=rcDest.right-m_nSbWid;
		rcDest.top=rcDest.bottom-m_nSbWid;
		m_pSkinSb->Draw(dc,rcDest,SB_CORNOR);
	}
}

void CDuiPanelEx::GetClient(LPRECT pRect)
{
	pRect->left=m_rcClient.left;
	pRect->right=m_rcClient.right;
	pRect->top=m_rcClient.top;
	pRect->bottom=m_rcClient.bottom;
}

BOOL CDuiPanelEx::OnDuiNcHitTest(CPoint pt)
{
	if(m_bDragSb) return TRUE;
	return !m_rcClient.PtInRect(pt);
}

void CDuiPanelEx::OnNcLButtonDown(UINT nFlags, CPoint point)
{
	m_HitInfo=HitTest(point);
	if(m_HitInfo.uSbCode!=WORD(-1) && IsScrollBarEnable(m_HitInfo.bVertical))
	{
		if(m_HitInfo.uSbCode!=SB_THUMBTRACK)
		{
			if(m_HitInfo.uSbCode==SB_LINEUP || m_HitInfo.uSbCode== SB_LINEDOWN)
			{
				CRect rc=GetSbPartRect(m_HitInfo.bVertical,m_HitInfo.uSbCode);
				HDC hdc=GetDuiDC(&rc,OLEDC_PAINTBKGND);
				m_pSkinSb->Draw(hdc,rc,MAKESBSTATE(m_HitInfo.uSbCode,DuiWndState_PushDown,m_HitInfo.bVertical));
				ReleaseDuiDC(hdc);
			}
			OnScroll(m_HitInfo.bVertical,m_HitInfo.uSbCode,m_HitInfo.bVertical?m_siVer.nPos:m_siHoz.nPos);
			SetDuiTimer(TIMER_SBWAIT,500);
		}else
		{
			SetDuiCapture();
			m_bDragSb=TRUE;
			m_ptDragSb=point;
			m_nDragPos=m_HitInfo.bVertical?m_siVer.nPos:m_siHoz.nPos;
		}
	}
}

void CDuiPanelEx::OnNcLButtonUp(UINT nFlags,CPoint pt)
{
	if(m_bDragSb)
	{
		ReleaseDuiCapture();
		m_bDragSb=FALSE;
		SCROLLINFO *psi=m_HitInfo.bVertical?(&m_siVer):(&m_siHoz);
		OnScroll(m_HitInfo.bVertical,SB_THUMBPOSITION,psi->nTrackPos);

		CRect rcRail=GetScrollBarRect(m_HitInfo.bVertical);
		if(m_HitInfo.bVertical) rcRail.DeflateRect(0,m_nSbArrowSize);
		else rcRail.DeflateRect(m_nSbArrowSize,0);
		HDC hdc=GetDuiDC(&rcRail,OLEDC_PAINTBKGND);
		m_pSkinSb->Draw(hdc,rcRail,MAKESBSTATE(SB_PAGEDOWN,DuiWndState_Normal,m_HitInfo.bVertical));
		psi->nTrackPos=-1;
		CRect rcSlide=GetSbPartRect(m_HitInfo.bVertical,SB_THUMBTRACK);
		m_pSkinSb->Draw(hdc,rcSlide,MAKESBSTATE(SB_THUMBTRACK,DuiWndState_Normal,m_HitInfo.bVertical));
		ReleaseDuiDC(hdc);
	}else if(m_HitInfo.uSbCode!=WORD(-1) && IsScrollBarEnable(m_HitInfo.bVertical))
	{
		if(m_HitInfo.uSbCode==SB_LINEUP||m_HitInfo.uSbCode==SB_LINEDOWN) 
		{
			CRect rc=GetSbPartRect(m_HitInfo.bVertical,m_HitInfo.uSbCode);
			HDC hdc=GetDuiDC(&rc,OLEDC_PAINTBKGND);
			m_pSkinSb->Draw(hdc,rc,MAKESBSTATE(m_HitInfo.uSbCode,DuiWndState_Normal,m_HitInfo.bVertical));
			ReleaseDuiDC(hdc);
		}
		KillDuiTimer(TIMER_SBWAIT);
		KillDuiTimer(TIMER_SBGO);
	}
	m_HitInfo.uSbCode=-1;
	OnNcMouseMove(nFlags,pt);
}

void CDuiPanelEx::OnNcMouseMove(UINT nFlags, CPoint point) 
{
	if(m_bDragSb)
	{
		if(m_HitInfo.uSbCode!=SB_THUMBTRACK) return;
		CRect rcSb=GetScrollBarRect(m_HitInfo.bVertical);
		CRect rcRail=rcSb;
		if(m_HitInfo.bVertical) rcRail.DeflateRect(0,m_nSbArrowSize);
		else rcRail.DeflateRect(m_nSbArrowSize,0);

		int nInterHei=m_HitInfo.bVertical?rcRail.Height():rcRail.Width();
		SCROLLINFO *psi=m_HitInfo.bVertical?(&m_siVer):(&m_siHoz);

		int	nSlideLen=GetSbSlideLength(m_HitInfo.bVertical);
		int nEmptyHei=nInterHei-nSlideLen;

		int nDragLen=m_HitInfo.bVertical?(point.y-m_ptDragSb.y):(point.x-m_ptDragSb.x);
	
		int nSlide=(nEmptyHei==0)?0:(nDragLen*(int)(psi->nMax-psi->nMin-psi->nPage+1)/nEmptyHei);
		int nNewTrackPos=m_nDragPos+nSlide;
		if(nNewTrackPos<psi->nMin)
		{
			nNewTrackPos=psi->nMin;
		}else if(nNewTrackPos>(int)(psi->nMax-psi->nMin-psi->nPage+1))
		{
			nNewTrackPos=psi->nMax-psi->nMin-psi->nPage+1;
		}

		CRect rcSlide=GetSbSlideRectByPos(m_HitInfo.bVertical,m_nDragPos);
		if(m_HitInfo.bVertical)
		{
			if(nDragLen>0 && nDragLen>rcRail.bottom-rcSlide.bottom)
				nDragLen=rcRail.bottom-rcSlide.bottom;
			if(nDragLen<0 && nDragLen<rcRail.top-rcSlide.top)
				nDragLen=rcRail.top-rcSlide.top;
			rcSlide.OffsetRect(0,nDragLen);
		}else
		{
			if(nDragLen>0 && nDragLen>rcRail.right-rcSlide.right)
				nDragLen=rcRail.right-rcSlide.right;
			if(nDragLen<0 && nDragLen<rcRail.left-rcSlide.left)
				nDragLen=rcRail.left-rcSlide.left;
			rcSlide.OffsetRect(nDragLen,0);
		}

		HDC hdc=GetDuiDC(&rcRail,OLEDC_PAINTBKGND);
		m_pSkinSb->Draw(hdc,rcRail,MAKESBSTATE(SB_PAGEUP,DuiWndState_Normal,m_HitInfo.bVertical));
		m_pSkinSb->Draw(hdc,rcSlide,MAKESBSTATE(SB_THUMBTRACK,DuiWndState_Hover,m_HitInfo.bVertical));
		ReleaseDuiDC(hdc);

		if(nNewTrackPos!=psi->nTrackPos)
		{
			psi->nTrackPos=nNewTrackPos;
			OnScroll(m_HitInfo.bVertical,SB_THUMBTRACK,psi->nTrackPos);
		}
	}else
	{
		SBHITINFO uHit=HitTest(point);
		if(memcmp(&uHit,&m_HitInfo,sizeof(SBHITINFO))!=0)
		{
			if(m_HitInfo.uSbCode!=WORD(-1) && IsScrollBarEnable(m_HitInfo.bVertical))
			{
				CRect rc=GetSbPartRect(m_HitInfo.bVertical,m_HitInfo.uSbCode);
				HDC hdc=GetDuiDC(&rc,OLEDC_PAINTBKGND);
				m_pSkinSb->Draw(hdc,rc,MAKESBSTATE(m_HitInfo.uSbCode,DuiWndState_Normal,m_HitInfo.bVertical));
				ReleaseDuiDC(hdc);
			}
			if(uHit.uSbCode!=WORD(-1) && IsScrollBarEnable(uHit.bVertical))
			{
				CRect rc=GetSbPartRect(uHit.bVertical,uHit.uSbCode);
				CDCHandle dc=GetDuiDC(&rc,OLEDC_PAINTBKGND);
				m_pSkinSb->Draw(dc,rc,MAKESBSTATE(uHit.uSbCode,DuiWndState_Hover,uHit.bVertical));
				ReleaseDuiDC(dc);
			}
			m_HitInfo=uHit;
		}
	}
}

void CDuiPanelEx::OnNcMouseLeave()
{
	if(!m_bDragSb) OnNcMouseMove(0,CPoint(-1,-1));
}

//滚动条显示或者隐藏时发送该消息
LRESULT CDuiPanelEx::OnNcCalcSize(BOOL bCalcValidRects, LPARAM lParam)
{
	__super::GetClient(&m_rcClient);

	if(HasScrollBar(TRUE)) m_rcClient.right-=m_nSbWid;
	if(HasScrollBar(FALSE)) m_rcClient.bottom-=m_nSbWid;

	return 0;
}

BOOL CDuiPanelEx::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	zDelta/=WHEEL_DELTA;
	if(zDelta>0)
	{
		for(short i=0;i<zDelta;i++) OnScroll(TRUE,SB_LINEUP,0);
	}else
	{
		for(short i=0;i>zDelta;i--) OnScroll(TRUE,SB_LINEDOWN,0);
	}

	HWND hHost=GetContainer()->GetHostHwnd();
	::SendMessage(hHost,WM_MOUSEMOVE,nFlags,MAKELPARAM(pt.x,pt.y));
	::SendMessage(hHost,WM_SETCURSOR,WPARAM(hHost),MAKELPARAM(HTCLIENT,WM_MOUSEMOVE));
	return FALSE;
}


BOOL CDuiPanelEx::OnScroll(BOOL bVertical,UINT uCode,int nPos)
{
	SCROLLINFO *psi=bVertical?(&m_siVer):(&m_siHoz);
	int nNewPos=psi->nPos;
	int nPage=bVertical?m_siVer.nPage:m_siHoz.nPage;
	switch(uCode)
	{
	case SB_LINEUP:nNewPos-=GetScrollLineSize(bVertical);break;
	case SB_LINEDOWN:nNewPos+=GetScrollLineSize(bVertical);break;
	case SB_PAGEUP:nNewPos-=psi->nPage;break;
	case SB_PAGEDOWN:nNewPos+=psi->nPage;break;
	case SB_THUMBTRACK:nNewPos=nPos;break;
	case SB_THUMBPOSITION:nNewPos=nPos;break;
	}

	if(nNewPos<psi->nMin) nNewPos=psi->nMin;
	if(nNewPos>psi->nMax - (int)psi->nPage+1) nNewPos=psi->nMax-psi->nPage+1;
	if(psi->nPage==0) nNewPos=0;

	if(nNewPos!=psi->nPos)
	{
		psi->nPos=nNewPos;
		if(uCode!=SB_THUMBTRACK)
		{
			CRect rcRail=GetScrollBarRect(bVertical);
			if(bVertical) rcRail.DeflateRect(0,m_nSbArrowSize);
			else rcRail.DeflateRect(m_nSbArrowSize,0);
			HDC hdc=GetDuiDC(&rcRail,OLEDC_PAINTBKGND);
			m_pSkinSb->Draw(hdc,rcRail,MAKESBSTATE(SB_PAGEDOWN,DuiWndState_Normal,bVertical));
			psi->nTrackPos=-1;
			CRect rcSlide=GetSbPartRect(bVertical,SB_THUMBTRACK);
			m_pSkinSb->Draw(hdc,rcSlide,MAKESBSTATE(SB_THUMBTRACK,DuiWndState_Normal,bVertical));
			ReleaseDuiDC(hdc);
		}
	}
	return TRUE;
}

int CDuiPanelEx::GetSbSlideLength(BOOL bVertical)
{
	SCROLLINFO *psi=bVertical?(&m_siVer):(&m_siHoz);
	CRect rcSb=GetScrollBarRect(bVertical);
	int nInterHei=(bVertical?rcSb.Height():rcSb.Width())- 2*m_nSbArrowSize;

	int	nSlideHei=psi->nPage*nInterHei/(psi->nMax-psi->nMin+1);
	if(nSlideHei<THUMB_MINSIZE) nSlideHei=THUMB_MINSIZE;
	if(nInterHei<THUMB_MINSIZE) nSlideHei=0;

	return nSlideHei;
}

CRect CDuiPanelEx::GetSbSlideRectByPos(BOOL bVertical,int nPos)
{
	SCROLLINFO *psi=bVertical?(&m_siVer):(&m_siHoz);
	int nOldPos=psi->nTrackPos;
	psi->nTrackPos=nPos;
	CRect rcRet=GetSbPartRect(bVertical,SB_THUMBTRACK);
	psi->nTrackPos=nOldPos;
	return rcRet;
}

void CDuiPanelEx::OnDuiTimer( char cTimerID )
{
	if(cTimerID==TIMER_SBWAIT)
	{
		KillDuiTimer(cTimerID);
		SetDuiTimer(TIMER_SBGO,50);
		OnDuiTimer(TIMER_SBGO);
	}else if(cTimerID==TIMER_SBGO)
	{
		if(m_HitInfo.uSbCode>=SB_LINEUP && m_HitInfo.uSbCode<=SB_PAGEDOWN)
		{
			OnScroll(m_HitInfo.bVertical,m_HitInfo.uSbCode,0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//	CDuiScrollView

CDuiScrollView::CDuiScrollView()
:m_szView(-1,-1)
,m_ptOrgin(0,0)
{
	m_bClipClient=TRUE;
}

int CDuiScrollView::OnCreate( LPVOID )
{
	int nRet=__super::OnCreate(NULL);
	if(nRet!=0) return nRet;
	if(m_szView.cx==-1) m_szView.cx=m_rcClient.Width();
	if(m_szView.cy==-1) m_szView.cy=m_rcClient.Height();
	SetViewOrigin(m_ptOrgin);
	return 0;
}

void CDuiScrollView::OnSize(UINT nType,CSize size)
{
	SetViewSize(m_szView);
}

CRect CDuiScrollView::GetViewRect()
{
	CRect rcView;
	CDuiWindow::GetClient(&rcView);
	rcView.OffsetRect(-m_ptOrgin);
	rcView.right=rcView.left+m_szView.cx;
	rcView.bottom=rcView.top+m_szView.cy;
	return rcView;
}


void CDuiScrollView::SetViewOrigin(CPoint pt)
{
	if(m_ptOrgin==pt) return;
	OnViewOriginChanged(m_ptOrgin,pt);
	m_ptOrgin=pt;
	CDuiWindow *pChild=m_pFirstChild;
	while(pChild)
	{
		DuiSendMessage(WM_CALCWNDPOS,0,(LPARAM)pChild);
		pChild=pChild->GetDuiWindow(GDUI_NEXTSIBLING);
	}

	CRect rcClient;
	GetClient(&rcClient);
	NotifyInvalidateRect(rcClient);
}

CPoint CDuiScrollView::GetViewOrigin(){return m_ptOrgin;}


void CDuiScrollView::SetViewSize(CSize szView)
{
	m_szView=szView;
	CRect rcClient;
	CDuiPanel::GetClient(&rcClient);

	CSize size=rcClient.Size();
	m_wBarVisible=DUISB_NULL;	//关闭滚动条

	if(size.cy<m_szView.cy || (size.cy<m_szView.cy+m_nSbWid && size.cx<m_szView.cx))
	{//需要纵向滚动条
		m_wBarVisible|=DUISB_VERT;
		m_siVer.nMin=0;
		m_siVer.nMax=m_szView.cy-1;

		if(size.cx<m_szView.cx+m_nSbWid)
		{//需要横向滚动条
			m_wBarVisible |= DUISB_HORZ;
			m_siVer.nPage=size.cy-m_nSbWid;

			m_siHoz.nMin=0;
			m_siHoz.nMax=m_szView.cx-1;
			m_siHoz.nPage=size.cx-m_nSbWid;
		}else
		{//不需要横向滚动条
			m_siHoz.nPage=size.cx;
			m_siHoz.nMin=0;
			m_siHoz.nMax=m_siHoz.nPage-1;
			m_siHoz.nPos=0;
			m_ptOrgin.x=0;
		}
	}else
	{//不需要纵向滚动条
		m_siVer.nPage=size.cy;
		m_siVer.nMin=0;
		m_siVer.nMax=size.cy-1;
		m_siVer.nPos=0;
		m_ptOrgin.y=0;

		if(size.cx<m_szView.cx)
		{//需要横向滚动条
			m_wBarVisible|=DUISB_HORZ;
			m_siHoz.nMin=0;
			m_siHoz.nMax=m_szView.cx-1;
			m_siHoz.nPage=size.cx;
		}
		//不需要横向滚动条
		else
		{
			m_siHoz.nPage=size.cx;
			m_siHoz.nMin=0;
			m_siHoz.nMax=m_siHoz.nPage-1;
			m_siHoz.nPos=0;
			m_ptOrgin.x=0;
		}
	}

	SetScrollPos(TRUE,m_siVer.nPos,TRUE);
	SetScrollPos(FALSE,m_siHoz.nPos,TRUE);

	DuiSendMessage(WM_NCCALCSIZE);

	NotifyInvalidate();
}

CSize CDuiScrollView::GetViewSize(){return m_szView;}

BOOL CDuiScrollView::OnScroll(BOOL bVertical,UINT uCode,int nPos)
{
	BOOL bRet=__super::OnScroll(bVertical,uCode,nPos);
	if(bRet)
	{
		int nPos=GetScrollPos(bVertical);
		CPoint ptOrigin=m_ptOrgin;

		if(bVertical) ptOrigin.y=nPos;
		else ptOrigin.x=nPos;

		if(ptOrigin!=m_ptOrgin)
			SetViewOrigin(ptOrigin);
	}
	return bRet;
}

}//namespace DuiEngine