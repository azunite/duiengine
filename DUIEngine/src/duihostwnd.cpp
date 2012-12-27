#include "duistd.h"

#include "duihostwnd.h"
#include "DuiTipCtrl.h"
#include "duiwndcmnctrl.h"
#include "DuiSystem.h"
#include "mybuffer.h"


namespace DuiEngine{

#define TIMER_CARET	1
#define TIMER_TRANSLUCENT	2


//////////////////////////////////////////////////////////////////////////
// CDuiHostWnd
//////////////////////////////////////////////////////////////////////////
CDuiHostWnd::CDuiHostWnd(UINT uResID/* =0*/)
: m_uResID(uResID)
, m_uRetCode(0)
, m_nIdleCount(0)
, m_bExitModalLoop(FALSE)
, m_bTrackFlag(FALSE)
, m_dwDlgStyle(0)
, m_dwDlgExStyle(0)
, m_bTranslucent(FALSE)
, m_bCaretShowing(FALSE)
, m_hBmpCaret(NULL)
, m_bCaretActive(FALSE)
, m_bNeedRepaint(FALSE)
, m_bNeedAllRepaint(TRUE)
, m_bResizable(FALSE)
, m_szMin(200, 200)
, m_pTipCtrl(NULL)
{
	SetContainer(this);
}


HWND CDuiHostWnd::Create(HWND hWndParent,LPCTSTR lpWindowName, DWORD dwStyle,DWORD dwExStyle, int x, int y, int nWidth, int nHeight,LPVOID lpParam)
{
	if (NULL != m_hWnd)
		return m_hWnd;

	HWND hWnd = CSimpleWnd::Create(lpWindowName,dwStyle,dwExStyle, x,y,nWidth,nHeight,hWndParent,lpParam);
	if(!hWnd) return NULL;

	//tooltip
	m_pTipCtrl=new CDuiTipCtrl;
	m_pTipCtrl->Create(m_hWnd);

	SetContainer(this);

	if(m_uResID)
	{
		Load(m_uResID);

		if(m_bTranslucent) 
		{
			SetWindowLong(GWL_EXSTYLE, GetWindowLong(GWL_EXSTYLE) | WS_EX_LAYERED);
		}
	}

	SendMessage(WM_INITDIALOG, (WPARAM)hWnd);
	return hWnd;
}

HWND CDuiHostWnd::Create(HWND hWndParent,int x,int y,int nWidth,int nHeight)
{
	return Create(hWndParent, NULL,WS_POPUP,0,x,y,nWidth,nHeight,0);
}

BOOL CDuiHostWnd::Load(UINT uResID)
{
	DuiResProviderBase *pRes=DuiSystem::getSingleton().GetResProvider();
	if(!pRes) return FALSE;

	DWORD dwSize=pRes->GetRawBufferSize(DUIRES_XML_TYPE,uResID);
	if(dwSize==0) return FALSE;

	CMyBuffer<char> strXml;
	strXml.Allocate(dwSize);
	pRes->GetRawBuffer(DUIRES_XML_TYPE,uResID,strXml,dwSize);

	return SetXml(strXml);
}

BOOL CDuiHostWnd::SetXml(LPCSTR lpszXml)
{

	TiXmlDocument xmlDoc;
	{ // Free stack
		xmlDoc.Parse(lpszXml, NULL, TIXML_ENCODING_UTF8);
	}

	if (xmlDoc.Error())
	{
		return FALSE;
	}

	CStringA strValue;

	m_dwDlgStyle    = WS_POPUP | WS_CLIPCHILDREN | WS_TABSTOP;
	m_dwDlgExStyle  = 0;

	DuiSendMessage(WM_DESTROY);


	TiXmlElement *pXmlRootElem = xmlDoc.RootElement();

	strValue = pXmlRootElem->Value();
	if (strValue != "layer")
	{
		return FALSE;
	}

	{
		m_strWindowCaption = pXmlRootElem->Attribute("title");
		m_sizeDefault.cx = 0;
		m_sizeDefault.cy = 0;
		pXmlRootElem->Attribute("width", (int *)&m_sizeDefault.cx);
		pXmlRootElem->Attribute("height", (int *)&m_sizeDefault.cy);
		CStringA strNC=pXmlRootElem->Attribute("ncRect");
		sscanf(strNC,"%d,%d,%d,%d",&m_rcNC.left,&m_rcNC.top,&m_rcNC.right,&m_rcNC.bottom);
		CStringA strMin = pXmlRootElem->Attribute("minsize");
		sscanf(strMin,"%d,%d",&m_szMin.cx, &m_szMin.cy);

		m_bTranslucent=FALSE;
		pXmlRootElem->Attribute("translucent",&m_bTranslucent);

		if(m_bTranslucent)
		{
			m_dwDlgExStyle |= WS_EX_LAYERED;
		}

		BOOL bValue = FALSE;

		pXmlRootElem->Attribute("appwin", &bValue);
		if (bValue)
		{
			m_dwDlgExStyle |= WS_EX_APPWINDOW;
 			m_dwDlgStyle |= WS_SYSMENU;
		}


		m_bResizable = FALSE;

		pXmlRootElem->Attribute("resize", &m_bResizable);

		if (m_bResizable)
		{
			m_dwDlgStyle |= WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME;
		}

	}
	ModifyStyle(0,m_dwDlgStyle);
	ModifyStyleEx(0,m_dwDlgExStyle);
	SetWindowText(CA2T(m_strWindowCaption,CP_UTF8));
	if(!m_strWindowCaption.IsEmpty()) 
	{
		DuiSkinPool::getSingleton().LoadSkins(m_strWindowCaption);	//load skin only used in the host window
	}

	CDuiPanel::Load(pXmlRootElem->FirstChildElement("body"));
	SetAttribute("pos", "0,0,-0,-0", TRUE);


	SetWindowPos(NULL,0,0,m_sizeDefault.cx,m_sizeDefault.cy,SWP_NOZORDER|SWP_NOMOVE);	

	DuiSendMessage(WM_SHOWWINDOW,1);

	_Redraw();

	RedrawRegion(CDCHandle(m_memDC),CRgn());

	if(m_bTranslucent) SetDuiTimer(TIMER_TRANSLUCENT,10);
	else KillDuiTimer(TIMER_TRANSLUCENT);
	return TRUE;
}

UINT_PTR CDuiHostWnd::DoModal(HWND hWndParent/* = NULL*/, LPRECT rect /*= NULL*/)
{
	BOOL bEnableParent = FALSE;

	if (NULL == hWndParent)
	{
		hWndParent = DuiThreadActiveWndManager::GetActive();
		if (NULL == hWndParent)
			hWndParent = ::GetActiveWindow();
	}

	if (hWndParent && hWndParent != ::GetDesktopWindow() && ::IsWindowEnabled(hWndParent))
	{
		::EnableWindow(hWndParent, FALSE);
		bEnableParent = TRUE;
	}

	m_bExitModalLoop = FALSE;
	
	CRect rc;
	if(rect) rc=*rect;
	HWND hWnd = Create(hWndParent, rc.left,rc.top,rc.Width(),rc.Height());
	if (!hWnd)
	{
		::EnableWindow(hWndParent, TRUE);
		return 0;
	}

	HWND hWndLastActive = DuiThreadActiveWndManager::SetActive(hWnd);

	if (!rect)
		CenterWindow();

	::SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_SHOWWINDOW);

	_ModalMessageLoop();

	m_bExitModalLoop = FALSE;

	// From MFC
	// hide the window before enabling the parent, etc.

	if ( IsWindow() )
	{
		SetWindowPos(
			NULL, 0, 0, 0, 0, 
			SWP_HIDEWINDOW | SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	}

	if (bEnableParent)
	{
		::EnableWindow(hWndParent, TRUE);
	}

	if (hWndParent != NULL && ::GetActiveWindow() == m_hWnd)
		::SetActiveWindow(hWndParent);

	DuiThreadActiveWndManager::SetActive(hWndLastActive);

	if ( IsWindow() )
		DestroyWindow();

	return m_uRetCode;
}


void CDuiHostWnd::EndDialog(UINT uRetCode)
{
	m_uRetCode = uRetCode;

	m_bExitModalLoop = TRUE;

	// DestroyWindow里面直接Send了WM_DESTROY，所以不会跑到DoModal的消息循环里，所以有了下面那行代码
	// DestroyWindow();

	// 这句非常重要，可以让DoModal消息循环再跑一次，防止卡死在GetMessage，泪奔~~~~~~~
	::PostThreadMessage(::GetCurrentThreadId(), WM_NULL, 0, 0);
}


BOOL CDuiHostWnd::OnIdle(int nCount)
{
	return FALSE;
}

void CDuiHostWnd::_ModalMessageLoop()
{
	BOOL bRet;
	MSG msg;

	for(;;)
	{
		if (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (WM_QUIT == msg.message)
				break;
		}else
		{
			OnIdle(m_nIdleCount++);
		}

		if (m_bExitModalLoop || NULL == m_hWnd || !::IsWindow(m_hWnd))
			break;

		bRet = ::GetMessage(&msg, NULL, 0, 0);

		if (bRet == -1)
		{
			continue;   // error, don't process
		}
		else if (!bRet)
		{
			break;   // WM_QUIT, exit message loop
		}
		if (!_PreTranslateMessage(&msg))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}
}


void CDuiHostWnd::_Redraw()
{
	m_bNeedAllRepaint = TRUE;
	m_bNeedRepaint = TRUE;
	if (!m_rgnInvalidate.IsNull())
		m_rgnInvalidate.DeleteObject();

	if(!m_bTranslucent)
		Invalidate(FALSE);
}

BOOL CDuiHostWnd::_PreTranslateMessage(MSG* pMsg)
{
	if(m_pTipCtrl  && m_pTipCtrl->IsWindow()) m_pTipCtrl->RelayEvent(pMsg);

	// loop backwards
	for(int i = m_aMsgFilter.size() - 1; i >= 0; i--)
	{
		CDuiMessageFilter* pMessageFilter = m_aMsgFilter[i];
		if(pMessageFilter != NULL && pMessageFilter->PreTranslateMessage(pMsg))
			return TRUE;
	}
	return FALSE;   // not translated
}


void CDuiHostWnd::OnPrint(CDCHandle dc, UINT uFlags)
{
	if(m_bTranslucent && !uFlags && (!m_bNeedAllRepaint && !m_bNeedRepaint)) return;
 	if (m_bNeedAllRepaint)
	{
		if (!m_rgnInvalidate.IsNull())
			m_rgnInvalidate.DeleteObject();

		m_bNeedAllRepaint = FALSE;
		m_bNeedRepaint=TRUE;
	}


	if (m_bNeedRepaint)
	{
		DuiThreadActiveWndManager::EnterPaintLock();

		HFONT hftOld = m_memDC.SelectFont(DuiFontPool::getSingleton().GetFont(DUIF_DEFAULTFONT));
		
		m_memDC.SetBkMode(TRANSPARENT);
		m_memDC.SetTextColor(0);

		CRect rcInvalid=m_rcWindow;
		if (!m_rgnInvalidate.IsNull())
		{
			m_memDC.SelectClipRgn(m_rgnInvalidate);
			m_rgnInvalidate.GetRgnBox(&rcInvalid);
		}else
		{
			m_memDC.SelectClipRgn(NULL);
		}

		m_memDC.FillSolidRect(&rcInvalid,0);//清除残留的alpha值

		//m_rgnInvalidate有可能在RedrawRegion时被修改，必须生成一个临时的区域对象
		CRgn rgnUpdate;
		if(m_rgnInvalidate)
		{
			rgnUpdate.Attach(m_rgnInvalidate.Detach());
		}
 		RedrawRegion(CDCHandle(m_memDC), rgnUpdate);	
		
		m_memDC.SelectClipRgn(NULL);

		m_memDC.SelectFont(hftOld);

		m_bNeedRepaint = FALSE;
		DuiThreadActiveWndManager::LeavePaintLock();
	}

	CRect rc;
	GetClientRect(&rc);
	UpdateHost(dc,rc);
}

void CDuiHostWnd::OnPaint(CDCHandle dc)
{
	OnPrint(m_bTranslucent?NULL:CPaintDC(m_hWnd).m_hDC, 0);
}

BOOL CDuiHostWnd::OnEraseBkgnd(CDCHandle dc)
{
	return TRUE;
}


int CDuiHostWnd::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	CDCHandle dc=::GetDC(NULL);
	m_memDC.CreateCompatibleDC(dc);
	::ReleaseDC(NULL,dc);
	return 0;
}

void CDuiHostWnd::OnDestroy()
{	
	if(m_pTipCtrl)
	{
		delete m_pTipCtrl;
	}

	DuiSendMessage(WM_DESTROY);

	if(::GetCurrentObject(m_memDC,OBJ_BITMAP))
	{
		HBITMAP hBmp=m_memDC.SelectBitmap(NULL);
		DeleteObject(hBmp);
	}
	m_memDC.DeleteDC();

	if(!m_strWindowCaption.IsEmpty()) 
	{
		DuiSkinPool::getSingleton().FreeSkins(m_strWindowCaption);
	}
}

void CDuiHostWnd::OnSize(UINT nType, CSize size)
{
	if(IsIconic()) return;

	if (size.cx==0 || size.cy==0)
		return;

	if(m_memDC.HasBitmap())
	{
		HBITMAP hBmp=m_memDC.SelectBitmap(NULL);
		DeleteObject(hBmp);
	}


	CDCHandle dcDesk=::GetDC(NULL);
	m_memDC.SelectBitmap(CGdiAlpha::CreateBitmap32(dcDesk,size.cx,size.cy));
	::ReleaseDC(NULL,dcDesk);

	CRect rcClient;
	GetClientRect(rcClient);

	Move(rcClient);

	_Redraw();

	SetMsgHandled(FALSE);//交给其它处理器继续处理
}

void CDuiHostWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bTrackFlag)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE;
		tme.dwHoverTime = 0;
		m_bTrackFlag = TrackMouseEvent(&tme);
	}

	OnMouseEvent(WM_MOUSEMOVE,nFlags,MAKELPARAM(point.x,point.y));
}

void CDuiHostWnd::OnMouseLeave()
{
	m_bTrackFlag = FALSE;
	DoFrameEvent(WM_MOUSELEAVE,0,0);
}

void CDuiHostWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();
	DoFrameEvent(WM_LBUTTONDOWN,nFlags,MAKELPARAM(point.x,point.y));
}

void CDuiHostWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	DoFrameEvent(WM_LBUTTONDBLCLK,nFlags,MAKELPARAM(point.x,point.y));
}

BOOL CDuiHostWnd::OnSetCursor(HWND hwnd, UINT nHitTest, UINT message)
{
	if(hwnd!=m_hWnd) return FALSE;
	if(nHitTest==HTCLIENT)
	{
		CPoint pt;
		GetCursorPos(&pt);
		ScreenToClient(&pt);
		return DoFrameEvent(WM_SETCURSOR,0,MAKELPARAM(pt.x,pt.y))!=0;
	}
	return DefWindowProc()!=0;
}

void CDuiHostWnd::OnTimer(UINT_PTR idEvent)
{
	CDuiTimerID duiTimerID((DWORD)idEvent);
	if(duiTimerID.bDuiTimer)
	{
		CDuiWindow *pDuiWnd=DuiWindowManager::GetWindow((HDUIWND)duiTimerID.hDuiWnd);
		if(pDuiWnd) 
		{
			if(pDuiWnd==this) OnDuiTimer(duiTimerID.uTimerID);//由于DUIWIN采用了ATL一致的消息映射表模式，因此在HOST中不能有DUI的消息映射表（重复会导致SetMsgHandled混乱)
			else pDuiWnd->DuiSendMessage(WM_TIMER,duiTimerID.uTimerID,0);
		}else
		{//窗口已经删除，自动清除该窗口的定时器
			KillTimer(idEvent);
		}
	}else
	{
		SetMsgHandled(FALSE);
	}
}

void CDuiHostWnd::OnDuiTimer( char cTimerID )
{
	if(cTimerID==TIMER_TRANSLUCENT)
	{
		OnPrint(NULL,0);
	}else if(cTimerID==TIMER_CARET)
	{
		if(DrawCaret(m_ptCaret,TRUE))	m_bCaretActive=!m_bCaretActive;
	}
}

BOOL CDuiHostWnd::DrawCaret(CPoint pt,BOOL bUpdate/*=FALSE*/)
{
	DUIASSERT(m_bTranslucent);
	BITMAP bm;
	GetObject(m_hBmpCaret,sizeof(bm),&bm);

	CMemDC dcCaret(m_memDC,m_hBmpCaret);

	ALPHAINFO ai;
	CGdiAlpha::AlphaBackup(m_memDC,CRect(pt,CSize(bm.bmWidth,bm.bmHeight)),ai);
	m_memDC.BitBlt(pt.x,pt.y,bm.bmWidth,bm.bmHeight,dcCaret,0,0,DSTINVERT);
	CGdiAlpha::AlphaRestore(m_memDC,ai);
	dcCaret.DeleteDC();
	if(bUpdate)
	{
		CRect rc;
		GetWindowRect(&rc);
		BLENDFUNCTION bf={AC_SRC_OVER,0,0xFF,AC_SRC_ALPHA};
		CDCHandle dc=GetDC();
		UpdateLayeredWindow(m_hWnd,dc,&rc.TopLeft(),&rc.Size(),m_memDC,&CPoint(0,0),0,&bf,ULW_ALPHA);	
		ReleaseDC(dc);
	}
	return TRUE;
}

LRESULT CDuiHostWnd::OnMouseEvent(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	DoFrameEvent(uMsg,wParam,lParam);	//将鼠标消息转发到DuiWindow处理
	
	if(m_pTipCtrl && m_pTipCtrl->IsWindow())
	{
		CDuiWindow *pHover=DuiWindowManager::GetWindow(m_hHover);
		if(!pHover || pHover->IsDisabled(TRUE)) 
		{
			m_pTipCtrl->ShowTip(FALSE);
		}else
		{
			HDUIWND hNewTipHost=0;
			CRect rcTip;
			CString strTip;
			BOOL bUpdate=pHover->OnUpdateToolTip(m_pTipCtrl->m_dwHostID,hNewTipHost,rcTip,strTip);
			if(bUpdate)
			{
				m_pTipCtrl->m_dwHostID=hNewTipHost;
				m_pTipCtrl->UpdateTip(rcTip,CT2A(strTip));
			}
		}
	}

	return 0;
}

LRESULT CDuiHostWnd::OnKeyEvent(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(uMsg==WM_KEYDOWN && (wParam==VK_RETURN || wParam==VK_ESCAPE))
	{//处理默认按钮，默认按钮的ID必须是IDOK或者IDCANCEL
		CDuiWindow *pFocus=DuiWindowManager::GetWindow(m_hFocus);
		if(!pFocus || (wParam==VK_RETURN && !(pFocus->OnGetDuiCode()&DUIC_WANTRETURN)) || !(pFocus->OnGetDuiCode()&DUIC_WANTALLKEYS))
		{
			UINT uCmdID = (wParam==VK_RETURN)?IDOK:IDCANCEL;
			CDuiWindow *pWnd=FindChildByCmdID(uCmdID);
			if(pWnd && (pWnd->IsClass(CDuiButton::GetClassName())||pWnd->IsClass(CDuiImageBtnWnd::GetClassName())))
			{
				DUINMCOMMAND nms;
				nms.hdr.code = DUINM_COMMAND;
				nms.hdr.hwndFrom = NULL;
				nms.hdr.idFrom = uCmdID;
				nms.uItemID = uCmdID;
				nms.szItemClass = pWnd->GetClassName();

				return OnDuiNotify((LPNMHDR)&nms);
			}
		}
	}else if(uMsg==WM_SYSKEYDOWN || uMsg==WM_SYSKEYUP)
	{
		CDuiWindow *pFocus=DuiWindowManager::GetWindow(m_hFocus);
		if(!pFocus  || !(pFocus->OnGetDuiCode()&DUIC_WANTSYSKEY))
		{
			SetMsgHandled(FALSE);
			return 0;
		}		
	}
	return DoFrameEvent(uMsg,wParam,lParam);
}

BOOL CDuiHostWnd::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	ScreenToClient(&pt);
	return DoFrameEvent(WM_MOUSEWHEEL,MAKEWPARAM(nFlags,zDelta),MAKELPARAM(pt.x,pt.y))!=0;
}

LRESULT CDuiHostWnd::OnDuiNotify(LPNMHDR pHdr)
{
	if(pHdr->code==DUINM_REALWND_CREATE) return (LRESULT)OnRealWndCreate(((LPDUINMREALWNDCMN)pHdr)->pRealWnd);
	else if(pHdr->code==DUINM_REALWND_INIT) return OnRealWndInit(((LPDUINMREALWNDCMN)pHdr)->pRealWnd);
	else if(pHdr->code==DUINM_REALWND_DESTROY) {OnRealWndDestroy(((LPDUINMREALWNDCMN)pHdr)->pRealWnd);return 0;}
	else if(pHdr->code==DUINM_REALWND_SIZE) {OnRealWndSize(((LPDUINMREALWNDCMN)pHdr)->pRealWnd);return 0;}

	return SendMessage(WM_NOTIFY,IDC_RICHVIEW_WIN,(LPARAM)pHdr);
}

CRect CDuiHostWnd::GetContainerRect(){return m_rcWindow;}

HWND CDuiHostWnd::GetHostHwnd(){return m_hWnd;}

HDC CDuiHostWnd::OnGetDuiDC(CRect & rc,DWORD gdcFlags)
{
	if(!(gdcFlags & OLEDC_NODRAW))
	{
		m_memDC.SelectFont(DuiFontPool::getSingleton().GetFont(DUIF_DEFAULTFONT));
		m_memDC.SetBkMode(TRANSPARENT);
		m_memDC.SetTextColor(0);

		CRgn rgnRc;
		rgnRc.CreateRectRgnIndirect(&rc);
		m_memDC.SelectClipRgn(rgnRc);
	}
	return m_memDC;
}

void CDuiHostWnd::UpdateHost(CDCHandle dc, CRect &rcInvalid )
{
	if(m_bTranslucent)
	{
		BITMAP bm;
		GetObject(m_hBmpCaret,sizeof(bm),&bm);
		CRect rcCaret(m_ptCaret,CSize(bm.bmWidth,bm.bmHeight));

		if(m_bCaretActive)
		{
			CMemDC dcCaret(m_memDC,m_hBmpCaret);
			m_memDC.BitBlt(rcCaret.left,rcCaret.top,rcCaret.Width(),rcCaret.Height(),dcCaret,0,0,DSTINVERT);
		}

		CRect rc;
		GetWindowRect(&rc);
		BLENDFUNCTION bf={AC_SRC_OVER,0,0xFF,AC_SRC_ALPHA};
		CDCHandle hdcSrc=::GetDC(NULL);
		UpdateLayeredWindow(m_hWnd,hdcSrc,&rc.TopLeft(),&rc.Size(),m_memDC,&CPoint(0,0),0,&bf,ULW_ALPHA);	
		::ReleaseDC(NULL,hdcSrc);

	}else
	{
		dc.BitBlt(rcInvalid.left,rcInvalid.top,rcInvalid.Width(),rcInvalid.Height(),m_memDC,rcInvalid.left,rcInvalid.top,SRCCOPY);
	}
}

void CDuiHostWnd::OnReleaseDuiDC(HDC hdcSour,CRect &rc,DWORD gdcFlags)
{
	if(gdcFlags & OLEDC_NODRAW) return;
	CDCHandle dc=GetDC();
	UpdateHost(dc,rc);
	ReleaseDC(dc);
}

void CDuiHostWnd::OnRedraw(const CRect &rc)
{
	if(!IsWindow()) return;

	if (m_rgnInvalidate.IsNull())
	{
		m_rgnInvalidate.CreateRectRgnIndirect(rc);
	}
	else
	{
		CRgn rgnInvalidate;

		rgnInvalidate.CreateRectRgnIndirect(rc);

		m_rgnInvalidate.CombineRgn(rgnInvalidate, RGN_OR);
	}
	m_bNeedRepaint = TRUE;

	if(!m_bTranslucent)//半透明状态下由Timer去刷新
	{
		InvalidateRect(rc, FALSE);
	}
}

BOOL CDuiHostWnd::OnReleaseDuiCapture()
{
	if(!__super::OnReleaseDuiCapture()) return FALSE;
	ReleaseCapture();
	CPoint pt;
	GetCursorPos(&pt);
	ScreenToClient(&pt);
	PostMessage(WM_MOUSEMOVE,0,MAKELPARAM(pt.x,pt.y));
	return TRUE;
}

HDUIWND CDuiHostWnd::OnSetDuiCapture(HDUIWND hDuiWnd)
{
	SetCapture();
	return __super::OnSetDuiCapture(hDuiWnd);
}

HDUIWND CDuiHostWnd::GetDuiCapture()
{
	if(GetCapture()!=m_hWnd) return NULL;
	return __super::GetDuiCapture();
}

BOOL CDuiHostWnd::IsTranslucent()
{
	return m_bTranslucent;
}


BOOL CDuiHostWnd::DuiCreateCaret( HBITMAP hBmp,int nWidth,int nHeight )
{
	BOOL bRet=::CreateCaret(m_hWnd,hBmp,nWidth,nHeight);
	if(bRet && m_bTranslucent)
	{
		CDCHandle dc=GetDC();
		if(m_hBmpCaret){ DeleteObject(m_hBmpCaret);m_hBmpCaret=NULL;}
		m_hBmpCaret=CreateCompatibleBitmap(dc,nWidth,nHeight);
		CDCHandle memdc1,memdc2;
		memdc1.CreateCompatibleDC(dc);
		memdc1.SelectBitmap(m_hBmpCaret);
		if(hBmp)
		{//以拉伸方式创建一个插入符位图
			memdc2.CreateCompatibleDC(dc);
			memdc2.SelectBitmap(hBmp);
			BITMAP bm;
			GetObject(hBmp,sizeof(bm),&bm);
			StretchBlt(memdc1,0,0,nWidth,nHeight,memdc2,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
			memdc2.DeleteDC();
		}else
		{//创建一个黑色插入符的位图
			memdc1.FillSolidRect(0,0,nWidth,nHeight,0);	
		}
		memdc1.DeleteDC();
		ReleaseDC(dc);
	}
	return bRet;
}

BOOL CDuiHostWnd::DuiShowCaret( BOOL bShow )
{
	BOOL bRet=FALSE;
	m_bCaretShowing=bShow;
	if(!m_bTranslucent)
	{
		if(bShow) bRet=ShowCaret();
		else bRet=HideCaret();
		if(bRet) m_bCaretShowing=bShow;
	}else
	{
		if(bShow)
		{
			SetDuiTimer(TIMER_CARET,GetCaretBlinkTime());
			m_bCaretShowing=TRUE;
			m_bCaretActive=DrawCaret(m_ptCaret,TRUE);
		}else
		{
			KillDuiTimer(TIMER_CARET);
			if(m_bCaretActive)
			{
				m_bCaretActive=!DrawCaret(m_ptCaret,TRUE);
			}
		}
	}
	return bRet;
}

BOOL CDuiHostWnd::DuiSetCaretPos( int x,int y )
{
	if(!SetCaretPos(x,y)) return FALSE;
	if(m_bTranslucent)
	{
		if(m_bCaretShowing && m_bCaretActive)
		{//clear old caret
			DrawCaret(m_ptCaret);
		}
		m_ptCaret=CPoint(x,y);
		if(m_bCaretShowing && m_bCaretActive)
		{//draw new caret
			DrawCaret(m_ptCaret);
		}
	}
	return TRUE;
}

LRESULT CDuiHostWnd::OnNcCalcSize(BOOL bCalcValidRects, LPARAM lParam)
{
	if (bCalcValidRects)
	{
		CRect rcWindow;

		GetWindowRect(rcWindow);

		LPNCCALCSIZE_PARAMS pParam = (LPNCCALCSIZE_PARAMS)lParam;

		if (SWP_NOSIZE == (SWP_NOSIZE & pParam->lppos->flags))
			return 0;

		if (0 == (SWP_NOMOVE & pParam->lppos->flags))
		{
			rcWindow.left = pParam->lppos->x;
			rcWindow.top = pParam->lppos->y;
		}

		rcWindow.right = rcWindow.left + pParam->lppos->cx;
		rcWindow.bottom = rcWindow.top + pParam->lppos->cy;
		pParam->rgrc[0] = rcWindow;
	}

	return 0;
}

void CDuiHostWnd::OnGetMinMaxInfo(LPMINMAXINFO lpMMI)
{
	HMONITOR hMonitor = ::MonitorFromWindow(m_hWnd, MONITOR_DEFAULTTONULL);

	if (hMonitor)
	{
		MONITORINFO mi = {sizeof(MONITORINFO)};
		::GetMonitorInfo(hMonitor, &mi);

		CRect rcWork = mi.rcWork, rcMonitor = mi.rcMonitor;
		lpMMI->ptMaxPosition.x = abs(rcWork.left - rcMonitor.left) - 1;
		lpMMI->ptMaxPosition.y = abs(rcWork.top - rcMonitor.top) - 1;
		lpMMI->ptMaxSize.x = abs(rcWork.Width()) + 2;
		lpMMI->ptMaxSize.y = abs(rcWork.Height()) + 2;
		lpMMI->ptMaxTrackSize.x = abs(rcWork.Width()) + 2;
		lpMMI->ptMaxTrackSize.y = abs(rcWork.Height()) + 2;
		lpMMI->ptMinTrackSize = CPoint(m_szMin.cx, m_szMin.cy); 
	}
}

BOOL CDuiHostWnd::OnNcActivate(BOOL bActive)
{
	return TRUE;
}

UINT CDuiHostWnd::OnWndNcHitTest(CPoint point)
{
	if (m_bResizable)
	{
		ScreenToClient(&point);
		if (point.x > m_rcWindow.right - m_rcNC.right)
		{
			if (point.y > m_rcWindow.bottom - m_rcNC.bottom)
			{
				return HTBOTTOMRIGHT; 
			}
			else if (point.y < m_rcNC.top)
			{
				return HTTOPRIGHT; 
			}
			return HTRIGHT; 
		}
		else if (point.x < m_rcNC.left)
		{
			if (point.y > m_rcWindow.bottom - m_rcNC.bottom)
			{
				return HTBOTTOMLEFT; 
			}
			else if (point.y < m_rcNC.top)
			{
				return HTTOPLEFT; 
			}
			return HTLEFT; 
		}
		else if (point.y > m_rcWindow.bottom - m_rcNC.bottom)
		{
			return HTBOTTOM; 
		}
		else if (point.y < m_rcNC.top)
		{
			return HTTOP; 
		}
	}
	return HTCLIENT;
}

void CDuiHostWnd::OnClose()
{
	EndDialog(IDCANCEL);
}

LRESULT CDuiHostWnd::OnOK()
{
	EndDialog(IDOK);
	return 0;
}

LRESULT CDuiHostWnd::OnCancel()
{
	EndDialog(IDCANCEL);
	return 0;
}

LRESULT CDuiHostWnd::OnMsgFilter(UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	CDuiMessageFilter *pMsgFilter=(CDuiMessageFilter*)lParam;
	if(wParam)
	{
		m_aMsgFilter.push_back(pMsgFilter);
	}else
	{
		std::vector<CDuiMessageFilter*>::iterator it= m_aMsgFilter.begin();
		while(it!=m_aMsgFilter.end())
		{
			if(*it == pMsgFilter)
			{
				m_aMsgFilter.erase(it);
				break;
			}
			it++;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
// IDuiRealWnd
HWND CDuiHostWnd::OnRealWndCreate(CDuiRealWnd *pRealWnd)
{
	CRect rcWindow;
	UINT uCmdID=pRealWnd->GetCmdID();
	pRealWnd->GetRect(&rcWindow);

	const CDuiRealWndParam & paramRealWnd=pRealWnd->GetRealWndParam();
	return CreateWindowEx(paramRealWnd.m_dwExStyle,paramRealWnd.m_strClassName,paramRealWnd.m_strWindowName,paramRealWnd.m_dwStyle,
			rcWindow.left,rcWindow.top,rcWindow.Width(),rcWindow.Height(),
			m_hWnd,(HMENU)(ULONG_PTR)uCmdID,0,NULL);
}

BOOL CDuiHostWnd::OnRealWndInit( CDuiRealWnd *pRealWnd )
{
	return FALSE;
}

void CDuiHostWnd::OnRealWndDestroy(CDuiRealWnd *pRealWnd)
{
	if(::IsWindow(pRealWnd->GetRealHwnd(FALSE)))
	{
		::DestroyWindow(pRealWnd->GetRealHwnd(FALSE));
	}
	if(pRealWnd->GetData())
	{
		delete pRealWnd->GetData();
		pRealWnd->SetData(0);
	}
}


void CDuiHostWnd::OnRealWndSize( CDuiRealWnd *pRealWnd )
{
	if(::IsWindow(pRealWnd->GetRealHwnd(FALSE)))
	{
		CRect rcClient;
		pRealWnd->GetClient(&rcClient);
		::SetWindowPos(pRealWnd->GetRealHwnd(FALSE),0, rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), SWP_NOZORDER);
	}
}

}//namespace DuiEngine
