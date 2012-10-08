#pragma once
#include "duistd.h"
#include "duirealwnd.h"

namespace DuiEngine{


CDuiRealWndParam::CDuiRealWndParam()
:m_dwStyle(WS_CHILD)
,m_dwExStyle(0)
,m_pXmlParams(NULL)
{

}

CDuiRealWndParam::~CDuiRealWndParam()
{
	if(m_pXmlParams) delete m_pXmlParams;
}


CDuiRealWnd::CDuiRealWnd()
:m_bInit(FALSE)
,m_lpData(0)
,m_hRealWnd(0)
{
}

CDuiRealWnd::~CDuiRealWnd()
{
}

BOOL CDuiRealWnd::NeedRedrawWhenStateChange()
{
	return FALSE;
}

void CDuiRealWnd::ShowRealWindow()
{
	if(IsVisible(TRUE) && !IsWindow(m_hRealWnd))
	{
		InitRealWnd();
	}
	if(IsWindow(m_hRealWnd))
	{
		ShowWindow(m_hRealWnd,IsVisible(TRUE) ? SW_SHOW : SW_HIDE);
	}
}

void CDuiRealWnd::OnWindowPosChanged(LPDUIWNDPOS lpWndPos)
{
	CRect rcOldWnd = m_rcWindow;

	__super::OnWindowPosChanged(lpWndPos);

	if (rcOldWnd != m_rcWindow)
	{
		DUINMREALWNDCMN nms;
		nms.hdr.code = DUINM_REALWND_SIZE;
		nms.hdr.hwndFrom = NULL;
		nms.hdr.idFrom = GetCmdID();
		nms.uItemID = GetCmdID();
		nms.pRealWnd=this;
		DuiNotify((LPNMHDR)&nms);
	}
}

void CDuiRealWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	__super::OnShowWindow(bShow, nStatus);
	ShowRealWindow();
}

void CDuiRealWnd::OnDestroy()
{
	if (IsWindow(m_hRealWnd))
	{
		DUINMREALWNDCMN nms;
		nms.hdr.code = DUINM_REALWND_DESTROY;
		nms.hdr.hwndFrom = NULL;
		nms.hdr.idFrom = GetCmdID();
		nms.uItemID = GetCmdID();
		nms.pRealWnd=this;
		DuiNotify((LPNMHDR)&nms);
	}
}

BOOL CDuiRealWnd::Load(TiXmlElement* pXmlElem)
{
	BOOL bRet=__super::Load(pXmlElem);
	if(bRet)
	{
		TiXmlElement *pParams=pXmlElem->FirstChildElement("params");
		if(pParams) m_realwndParam.m_pXmlParams=pParams->Clone()->ToElement();
		if(m_bInit) InitRealWnd();
	}
	return bRet;
}

const HWND CDuiRealWnd::GetRealHwnd(BOOL bAutoCreate/*=TRUE*/)
{
	if(!bAutoCreate) return m_hRealWnd;

	if(!m_bInit && !IsWindow(m_hRealWnd)) 
	{
		InitRealWnd();
	}

	return m_hRealWnd;
}

BOOL CDuiRealWnd::InitRealWnd()
{
	m_realwndParam.m_dwStyle|= WS_CHILD;

	DUINMREALWNDCMN nms;
	nms.hdr.code = DUINM_REALWND_CREATE;
	nms.hdr.hwndFrom = NULL;
	nms.hdr.idFrom = GetCmdID();
	nms.uItemID = GetCmdID();
	nms.pRealWnd=this;
	HWND hWnd =(HWND) DuiNotify((LPNMHDR)&nms);

	if(::IsWindow(hWnd))
	{
		m_hRealWnd=hWnd;
		if(!m_bInit)
		{//如果不是在加载的时候创建窗口，则需要自动调整窗口位置
			CRect rcClient;
			GetClient(&rcClient);
			SetWindowPos(m_hRealWnd,0,rcClient.left,rcClient.top,rcClient.Width(),rcClient.Height(),SWP_NOZORDER);
		}
	
		DUINMREALWNDCMN nms;
		nms.hdr.code = DUINM_REALWND_INIT;
		nms.hdr.hwndFrom = NULL;
		nms.hdr.idFrom = GetCmdID();
		nms.uItemID = GetCmdID();
		nms.pRealWnd=this;
		
		BOOL bFocus=(BOOL)DuiNotify((LPNMHDR)&nms);
		if(bFocus)
		{
			SetFocus(m_hRealWnd);
		}
		return TRUE;
	}
	return FALSE;
}


}//namespace DuiEngine