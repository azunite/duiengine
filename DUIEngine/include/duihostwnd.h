//////////////////////////////////////////////////////////////////////////
//  Class Name: CDuiHostWnd
//	Description: Real Container of DuiWindow
//     Creator: ZhangXiaoxuan
//     Version: 2010.3.12 - 1.0 - Create
//				2011.6.18	1.1   huangjianxiong
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "MemDC.h"
#include "duimsgfilter.h"
#include "DuiThreadActiveWndManager.h"

#include "duiwndpanel.h"
#include "duiframe.h"
#include "duirealwnd.h"

#include "SimpleWnd.h"

#pragma warning(disable: 4996)
///////////////////////////////////////////////////////////////////////////////
// Classes in this file:
//
// CDuiHostWnd
//////////////////////////////////////////////////////////////////////////


namespace DuiEngine
{

class CDuiTipCtrl;

class DUI_EXP CDuiHostWnd
    : public CSimpleWnd
    , public CDuiFrame
    , IDuiRealWndHandler
{
public:
    CDuiHostWnd(UINT uResID = 0);
    virtual ~CDuiHostWnd() {}

public:

    HWND Create(HWND hWndParent,int x,int y,int nWidth,int nHeight);
    HWND Create(HWND hWndParent,LPCTSTR lpWindowName, DWORD dwStyle,DWORD dwExStyle, int x, int y, int nWidth, int nHeight, LPVOID lpParam);
    BOOL Load(UINT uResID);

    BOOL SetXml(LPCSTR lpszXml);

	BOOL IsLayoutInited();

    UINT_PTR DoModal(HWND hWndParent = NULL, LPRECT rect = NULL);

    void EndDialog(UINT uRetCode);
protected:
    UINT m_uRetCode;
    BOOL m_bExitModalLoop;
    UINT m_uResID;
    int m_nIdleCount;

    // Tracking flag
    BOOL m_bTrackFlag;

    CStringA m_strWindowCaption;
    SIZE m_sizeDefault;
    CRect m_rcNC;

    DWORD m_dwDlgStyle;
    DWORD m_dwDlgExStyle;
    BOOL m_bResizable;
    CSize m_szMin;

    BOOL m_bTranslucent;	//窗口的半透明属性
    BOOL m_bCaretShowing;	//当前有插入符正在显示
    HBITMAP m_hBmpCaret;	//半透明窗口中的模拟插入符
    BOOL m_bCaretActive;	//模拟插入符正在显示标志
    CPoint m_ptCaret;		//插入符位置
    BOOL m_bNeedRepaint;
    BOOL m_bNeedAllRepaint;
	BOOL m_bLayoutInited;

    CDuiTipCtrl	* m_pTipCtrl;

    CRgn m_rgnInvalidate;

    CMemDC	m_memDC;
protected:
    virtual BOOL OnIdle(int nCount);

    void _ModalMessageLoop();

    void _Redraw();

    virtual BOOL _PreTranslateMessage(MSG* pMsg);

    CDuiArray<CDuiMessageFilter*> m_aMsgFilter;
protected:
    //////////////////////////////////////////////////////////////////////////
    // Message handler

    void OnPrint(CDCHandle dc, UINT uFlags);

    void OnPaint(CDCHandle dc);

    BOOL OnEraseBkgnd(CDCHandle dc);

    int OnCreate(LPCREATESTRUCT lpCreateStruct);

    void OnDestroy();

    void OnSize(UINT nType, CSize size);

    void OnMouseMove(UINT nFlags, CPoint point);

    void OnMouseLeave();

    void OnLButtonDown(UINT nFlags, CPoint point);
    void OnLButtonDblClk(UINT nFlags, CPoint point);

    BOOL OnSetCursor(HWND hWnd, UINT nHitTest, UINT message);

    void OnTimer(UINT_PTR idEvent);

    void OnDuiTimer(char cTimerID);

    BOOL DrawCaret(CPoint pt,BOOL bUpdate=FALSE);

    LRESULT OnMouseEvent(UINT uMsg, WPARAM wParam, LPARAM lParam);

    LRESULT OnKeyEvent(UINT uMsg, WPARAM wParam, LPARAM lParam);

    BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

    //////////////////////////////////////////////////////////////////////////
    // CDuiContainer

    /*virtual */
    LRESULT OnDuiNotify(LPNMHDR pHdr);

    /*virtual */
    CRect GetContainerRect();

    /*virtual */
    HWND GetHostHwnd();

    /*virtual */
    HDC OnGetDuiDC(CRect & rc,DWORD gdcFlags);

    /*virtual */
    void OnReleaseDuiDC(HDC hdcSour,CRect &rc,DWORD gdcFlags);

    /*virtual */
    void OnRedraw(const CRect &rc);

    /*virtual */
    BOOL OnReleaseDuiCapture();

    /*virtual */
    HDUIWND OnSetDuiCapture(HDUIWND hDuiWnd);

    /*virtual */
    HDUIWND GetDuiCapture();

    /*virtual */
    BOOL IsTranslucent();

    /*virtual */
    BOOL DuiCreateCaret(HBITMAP hBmp,int nWidth,int nHeight);

    /*virtual */
    BOOL DuiShowCaret(BOOL bShow);

    /*virtual */
    BOOL DuiSetCaretPos(int x,int y);

    //////////////////////////////////////////////////////////////////////////
    // IDuiRealWndHandler
    virtual HWND OnRealWndCreate(CDuiRealWnd *pRealWnd);
    virtual BOOL OnRealWndInit(CDuiRealWnd *pRealWnd);
    virtual void OnRealWndDestroy(CDuiRealWnd *pRealWnd);
    virtual void OnRealWndSize(CDuiRealWnd *pRealWnd);

    LRESULT OnNcCalcSize(BOOL bCalcValidRects, LPARAM lParam);

    void OnGetMinMaxInfo(LPMINMAXINFO lpMMI);

    BOOL OnNcActivate(BOOL bActive);

    UINT OnWndNcHitTest(CPoint point);

    void OnClose();

    LRESULT OnOK();

    LRESULT OnCancel();

    LRESULT OnMsgFilter(UINT uMsg,WPARAM wParam,LPARAM lParam);

    void UpdateHost(CDCHandle dc,CRect &rc);
protected:
    DUI_NOTIFY_MAP(IDC_RICHVIEW_WIN)
    DUI_NOTIFY_ID_COMMAND(IDCANCEL, OnCancel)
    DUI_NOTIFY_ID_COMMAND(IDOK, OnOK)
    DUI_NOTIFY_MAP_END()

    BEGIN_MSG_MAP_EX(CDuiHostWnd)
    MSG_WM_SIZE(OnSize)
    MSG_WM_PRINT(OnPrint)
    MSG_WM_PAINT(OnPaint)
    MSG_WM_CREATE(OnCreate)
    MSG_WM_DESTROY(OnDestroy)
    MSG_WM_ERASEBKGND(OnEraseBkgnd)
    MSG_WM_MOUSELEAVE(OnMouseLeave)
    MSG_WM_MOUSEMOVE(OnMouseMove)
    MSG_WM_LBUTTONDBLCLK(OnLButtonDblClk)
    MSG_WM_LBUTTONDOWN(OnLButtonDown)
    MSG_WM_MOUSEWHEEL(OnMouseWheel)
    MESSAGE_RANGE_HANDLER_EX(WM_MOUSEFIRST, WM_MOUSELAST, OnMouseEvent)
    MESSAGE_RANGE_HANDLER_EX(WM_KEYFIRST, WM_KEYLAST, OnKeyEvent)

    MSG_WM_SETCURSOR(OnSetCursor)
    MSG_WM_TIMER(OnTimer)
    MSG_WM_NCACTIVATE(OnNcActivate)
    MSG_WM_NCCALCSIZE(OnNcCalcSize)
    MSG_WM_NCHITTEST(OnWndNcHitTest)
    MSG_WM_GETMINMAXINFO(OnGetMinMaxInfo)
    MESSAGE_HANDLER_EX(UM_MSGFILTER,OnMsgFilter)
    MSG_WM_CLOSE(OnClose)

    MSG_DUI_NOTIFY(IDC_RICHVIEW_WIN)
    REFLECT_NOTIFY_CODE(NM_CUSTOMDRAW)
    END_MSG_MAP()
};

}//namespace DuiEngine
