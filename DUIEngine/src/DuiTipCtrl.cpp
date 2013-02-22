#include "duistd.h"
#include "DuiTipCtrl.h"

namespace DuiEngine
{

#define TIMERID_DELAY	1
#define TIMERID_SPAN	2

#define MARGIN_TIP		5

CDuiTipCtrl::CDuiTipCtrl(void):m_nDelay(500),m_nShowSpan(5000),m_dwHostID(0),m_bSetDelayTimer(FALSE)
{
}

CDuiTipCtrl::~CDuiTipCtrl(void)
{
    if(m_font) m_font.DeleteObject();
}

BOOL CDuiTipCtrl::Create( HWND hOwner )
{
    HWND hWnd=__super::Create(NULL,WS_POPUP,WS_EX_TOOLWINDOW|WS_EX_TOPMOST|WS_EX_NOACTIVATE,0,0,0,0,hOwner,NULL);
    if(!hWnd) return FALSE;

    LOGFONTW lf;
    GetObjectW(GetStockObject(DEFAULT_GUI_FONT),sizeof(lf),&lf);
    lf.lfHeight=-12;
    wcscpy(lf.lfFaceName,L"ËÎÌו");
    m_font.CreateFontIndirect(&lf);

    return TRUE;
}

void CDuiTipCtrl::RelayEvent( const MSG *pMsg )
{
    switch(pMsg->message)
    {
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
    case WM_MBUTTONDOWN:
        OnTimer(TIMERID_SPAN);//hide tip
        break;
    case WM_MOUSEMOVE:
    {
        CPoint pt(GET_X_LPARAM(pMsg->lParam),GET_Y_LPARAM(pMsg->lParam));
        if(!m_rcTarget.PtInRect(pt))
        {
            OnTimer(TIMERID_SPAN);//hide tip
        }
        else if(!IsWindowVisible() && !m_strTip.IsEmpty()&&!m_bSetDelayTimer)
        {
            KillTimer(TIMERID_DELAY);
            SetTimer(TIMERID_DELAY,m_nDelay);
            m_bSetDelayTimer = TRUE;
            ::ClientToScreen(pMsg->hwnd,&pt);
            SetWindowPos(0,pt.x,pt.y+24,0,0,SWP_NOSIZE|SWP_NOZORDER|SWP_NOSENDCHANGING|SWP_NOACTIVATE);
        }
    }
    break;
    }
}

void CDuiTipCtrl::UpdateTip(CRect rc, LPCTSTR pszTip,BOOL bText/*=TRUE*/ )
{
    m_rcTarget=rc;
    m_bTextTip=bText;
    m_strTip=pszTip;
    if(IsWindowVisible())
    {
        ShowTip(TRUE);
    }
}

void CDuiTipCtrl::SetDelayTime( DWORD dwType,UINT iTime )
{

}

void CDuiTipCtrl::ShowTip(BOOL bShow)
{
    if(!bShow)
    {
        //m_dwHostID=0;
        ShowWindow(SW_HIDE);
        m_rcTarget.SetRect(0,0,0,0);
        m_strTip=_T("");
    }
    else if(!m_strTip.IsEmpty())
    {
        HDC hdc=::GetDC(NULL);
        CRect rcText(0,0,500,1000);
        HFONT oldFont=(HFONT)SelectObject(hdc,m_font);
        DrawText(hdc,m_strTip,-1,&rcText,DT_CALCRECT|DT_LEFT|DT_WORDBREAK);
        SelectObject(hdc,oldFont);
        ::ReleaseDC(NULL,hdc);
        SetWindowPos(HWND_TOPMOST,0,0,rcText.right+2*MARGIN_TIP,rcText.bottom+2*MARGIN_TIP,SWP_NOMOVE|SWP_NOSENDCHANGING|SWP_SHOWWINDOW|SWP_NOACTIVATE);
    }
}

void CDuiTipCtrl::OnTimer( UINT_PTR idEvent )
{
    switch(idEvent)
    {
    case TIMERID_DELAY:
        KillTimer(TIMERID_DELAY);
        m_bSetDelayTimer = FALSE;
        ShowTip(TRUE);
        SetTimer(TIMERID_SPAN,m_nShowSpan);
        break;
    case TIMERID_SPAN:
        ShowTip(FALSE);
        KillTimer(TIMERID_SPAN);
        break;
    }
}

void CDuiTipCtrl::OnPaint( CDCHandle dc )
{
    CPaintDC dcPaint(m_hWnd);
    CRect rc;
    GetClientRect(&rc);
    CBrush br;
    br.CreateSolidBrush(GetSysColor(COLOR_INFOBK));
    HBRUSH hOld=dcPaint.SelectBrush(br);
    dcPaint.Rectangle(&rc);
    dcPaint.SelectBrush(hOld);
    rc.DeflateRect(MARGIN_TIP,MARGIN_TIP);
    dcPaint.SetBkMode(TRANSPARENT);
    HFONT hOldFont=(HFONT)dcPaint.SelectFont(m_font);
    ::DrawText(dcPaint,m_strTip,-1,&rc,DT_WORDBREAK);
    dcPaint.SelectFont(hOldFont);
}

}//namespace DuiEngine