#pragma once

#include "duiskin.h"
#include <atlctrls.h>

typedef CWinTraits<WS_CHILD|WS_VISIBLE,WS_EX_CLIENTEDGE> CDuiCustomFrameTraits;

template <class T, class TBase, class TWinTraits = CDuiCustomFrameTraits>
class DUI_EXP CDuiCustomFrameImpl
	: public ATL::CWindowImpl<T, TBase, TWinTraits>
{
public:
	CDuiCustomFrameImpl():m_bTracking(FALSE),m_pSkinFrame(NULL),m_hFont(0)
	{

	}

	void SetXmlParam(TiXmlElement *pParam)
	{
		if(!pParam) return;
		CStringA strSkin=pParam->Attribute("frmskin");
		if(!strSkin.IsEmpty())
		{
			m_pSkinFrame=DuiSkinPool::getSingleton().GetSkin(strSkin);
		}
	}

	void SetFrameSkin(CDuiSkinBase *pSkin) {m_pSkinFrame=pSkin;}
protected:
	BOOL m_bTracking;
	CDuiSkinBase *m_pSkinFrame;
	HFONT m_hFont;

	void OnMouseMove(UINT uFlag,CPoint pt)
	{
		if(!m_bTracking)
		{
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(tme);
			tme.hwndTrack = m_hWnd;
			tme.dwFlags = TME_LEAVE;
			tme.dwHoverTime = 0;
			m_bTracking = _TrackMouseEvent(&tme);
			OnNcPaint(0);
		}
		DefWindowProc();
	}
	
	void OnMouseLeave()
	{
		m_bTracking=FALSE;
		OnNcPaint(0);
	}

	void OnNcPaint(CRgn rgn)
	{
		if (!m_hFont)
		{
			m_hFont = DuiFontPool::getSingleton().GetFont(DUIF_DEFAULTFONT);
			SetFont(m_hFont);

			CRect rect ;			
			::GetClientRect(m_hWnd, &rect);
			rect.DeflateRect(2, 2, 2, 2);
			::SendMessage(m_hWnd, EM_SETRECT,0,(LPARAM)&rect);
		}
		if(!m_pSkinFrame)
		{
			DefWindowProc();
			return ;
		}
		CRect rc,rcClient;
		CDCHandle hdc;
		GetWindowRect(&rc);
		hdc = GetWindowDC();
		GetClientRect(&rcClient);
		ClientToScreen(&rcClient);
		rcClient.OffsetRect(-rc.left,-rc.top);
		rc.MoveToXY(0,0);
		ExcludeClipRect(hdc,rcClient.left,rcClient.top,rcClient.right,rcClient.bottom);
		m_pSkinFrame->Draw(hdc,rc,m_bTracking?1:0);
		ReleaseDC(hdc);
	}

	BEGIN_MSG_MAP(CDuiCustomFrameImpl)
		MSG_WM_MOUSEMOVE(OnMouseMove)
		MSG_WM_MOUSELEAVE(OnMouseLeave)
		MSG_WM_NCPAINT(OnNcPaint)
	END_MSG_MAP()
};

class DUI_EXP CDuiEdit 
	: public CDuiCustomFrameImpl<CDuiEdit,CEdit>
{
public:
	DECLARE_WND_CLASS(_T("duiedit"))
};