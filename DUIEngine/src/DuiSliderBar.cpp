#include "duistd.h"
#include "DuiSliderBar.h"

namespace DuiEngine
{

#define TIMERID_NOTIFY1     1
#define TIMERID_DELAY1      2

//////////////////////////////////////////////////////////////////////////
//  CDuiSliderBar
CDuiSliderBar::CDuiSliderBar()
    : m_bDrag(FALSE)
    , m_uClicked(-1)
    , m_bNotify(FALSE)
    , m_uHtPrev(-1)
    , m_bVertical(FALSE)
    , m_nMaxVal(100)
    , m_nCurPos(0)
    , m_nInterHeight(6)
	, m_pSkinThumb(NULL)
{
    m_nDragPos = 0;
}

CDuiSliderBar::~CDuiSliderBar()
{
}

BOOL CDuiSliderBar::IsVertical()
{
    return m_bVertical;
}

int CDuiSliderBar::HitTest(CPoint pt)
{
    CRect rc;

    rc = GetPartRect(SC_THUMB);
    if (rc.PtInRect(pt))
        return SC_THUMB;

    rc = GetPartRect(SC_SELECT);
    if (rc.PtInRect(pt))
        return SC_SELECT;

    rc = GetPartRect(SC_CHANNEL);
    if (rc.PtInRect(pt))
        return SC_CHANNEL;

    return -1;
}

void CDuiSliderBar::SetMaxValue(int nValue)
{
    m_nMaxVal = nValue;
}

void CDuiSliderBar::SetValue(int nValue)
{
    if (nValue > m_nMaxVal)
        nValue = m_nMaxVal;

    if (nValue < 0)
        nValue = 0;

    if (nValue != m_nValue)
    {
        m_nValue = nValue;

        CRect rcChannel = GetPartRect(SC_CHANNEL);

        //  更新位置
        m_nDragPos = ((double)nValue / (double)m_nMaxVal) * rcChannel.Width();
        m_nCurPos  = m_nDragPos;

        NotifyInvalidate();
    }
}

int CDuiSliderBar::GetValue()
{
    return m_nValue;
}

CRect CDuiSliderBar::GetPartRect(UINT uSBCode)
{
    DUIASSERT(m_pSkinThumb);

    CRect rcRet(0,0,0,0);

    SIZE szThumb = m_pSkinThumb->GetSkinSize();

    switch (uSBCode)
    {
    case SC_CHANNEL:
        {
            //  左边要偏移滑块的一半(+1)
            rcRet.left   = m_rcWindow.left + szThumb.cx/2 + 1;
            //  右边要偏移滑块的一半(-1)
            rcRet.right  = m_rcWindow.right - szThumb.cx/2 - 1;
            //  垂直居中
            rcRet.top    = m_rcWindow.top + (m_rcWindow.Height()-m_nInterHeight)/2;
            rcRet.bottom = rcRet.top + m_nInterHeight;
        }
        break;

    case SC_SELECT:
        {
            //  计算出实际的长度
            //int nPos = (m_rcWindow.Width()-szThumb.cx-2) * ((double)m_nCurPos/(double)m_nMaxVal);
            //  左边要偏移滑块的一半(+1)
            rcRet.left   = m_rcWindow.left + szThumb.cx/2 + 1;
            //  右边加上真实长度
            rcRet.right  = rcRet.left + m_nDragPos;
            //  垂直居中
            rcRet.top    = m_rcWindow.top + (m_rcWindow.Height()-m_nInterHeight)/2;
            rcRet.bottom = rcRet.top + m_nInterHeight;
        }
        break;

    case SC_THUMB:
        {
            //  获取选择区域的大小
            CRect rcSelect = GetPartRect(SC_SELECT);
            //  滑块左边
            rcRet.left   = rcSelect.right - szThumb.cx/2;
            //  滑块右边
            rcRet.right  = rcRet.left + szThumb.cx;
            //  垂直居中
            if (rcSelect.Height() > szThumb.cy)
            {
                //  滑块在区域内
                rcRet.top = rcSelect.top + (rcSelect.Height()-szThumb.cy)/2;
            }
            else
            {
                //  滑块在区域外
                rcRet.top = rcSelect.top - (szThumb.cy-rcSelect.Height())/2;
            }
            rcRet.bottom = rcRet.top + szThumb.cy;
        }
        break;
    }

    return rcRet;
}

void CDuiSliderBar::OnPaint(CDCHandle dc)
{
    if (!m_pSkinThumb)
        return;

    int nState = IsDisabled(TRUE) ? 3 : 0;
    CRect rcDest;

    DuiDCPaint dxDC;
    CPen penFrame;

    BeforePaint(dc, dxDC);

    penFrame.CreatePen(PS_SOLID, 1, RGB(0x70, 0x70, 0x70));

    HPEN hPenOld = dc.SelectPen(penFrame);

    //  画背景区域
    CRect rcChannel = GetPartRect(SC_CHANNEL);
    rcChannel.InflateRect(1,1,1,1);
    CGdiAlpha::RoundRect(dc, rcChannel, CPoint(1, 1));
    rcChannel.DeflateRect(1,1,1,1);
    CGdiAlpha::FillSolidRect(dc, rcChannel, m_crBg);

    //  画选择区域
    CRect rcSelect = GetPartRect(SC_SELECT);
    CGdiAlpha::FillSolidRect(dc, rcSelect, m_crSelect);

	dc.SelectPen(hPenOld);
    //  画滑块
    CRect rcThumb = GetPartRect(SC_THUMB);
    m_pSkinThumb->Draw(dc, rcThumb, IIF_STATE4(GetState(), 0, 1, 2, 3), 0xFF);

    AfterPaint(dc, dxDC);
}

void CDuiSliderBar::OnLButtonUp(UINT nFlags, CPoint point)
{
    ReleaseDuiCapture();

    if (m_bDrag)
    {
        m_bDrag   = FALSE;
        m_nCurPos = m_nDragPos;
        OnMouseMove(nFlags, point);

        //  计算出新的值
        CRect rcChannel = GetPartRect(SC_CHANNEL);
        m_nValue = m_nMaxVal * ((double)m_nCurPos/(double)rcChannel.Width());

        NotifySbCode(SC_MOUSEUP, m_nValue);
    }
    else if (m_uClicked != -1)
    {
        if (m_uClicked==SC_SELECT || m_uClicked==SC_CHANNEL) 
        {
            //  更新位置
            CRect rcChannel = GetPartRect(SC_CHANNEL);

            m_nCurPos  = IsVertical() ? (point.y-rcChannel.top) : (point.x-rcChannel.left);
            m_nDragPos = m_nCurPos;

            m_nValue = m_nMaxVal * ((double)m_nCurPos/(double)rcChannel.Width());
            NotifyInvalidate();

            NotifySbCode(SC_POSITION_CLICK, m_nValue);
        }
        m_uClicked = -1;
    }
}

void CDuiSliderBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
    SetDuiCapture();

    UINT uHit = HitTest(point);
    if (uHit == SC_THUMB)
    {
        m_bDrag    = TRUE;
        m_ptDrag   = point;
        m_nDragPos = m_nCurPos;

        NotifySbCode(SC_MOUSEDOWN, m_nValue);
    }
    else
    {
        m_uClicked = uHit;

        if (uHit == SC_SELECT || uHit == SC_CHANNEL)
        {
            NotifySbCode(uHit, m_nValue);
        }
    }
}

void CDuiSliderBar::OnMouseMove(UINT nFlags, CPoint point) 
{
    if (m_bDrag)
    {
        CRect rcChannel = GetPartRect(SC_CHANNEL);

        int nDragLen = IsVertical() ? (point.y-m_ptDrag.y) : (point.x-m_ptDrag.x);
        m_nDragPos = m_nCurPos + nDragLen;
        if (m_nDragPos < 0)
        {
            m_nDragPos = 0;
        }
        else if (m_nDragPos > rcChannel.Width())
        {
            m_nDragPos = rcChannel.Width();
        }

        if (m_nDragPos != m_nCurPos)
        {
            //CRect rcOldThumb = GetPartRect(SC_THUMB);

            //CRect rcThumb = GetPartRect(SC_THUMB);
            //CRect rcUnion;
            //rcUnion.UnionRect(rcOldThumb, rcThumb);

            //HDC hdc = GetDuiDC(&rcUnion, OLEDC_PAINTBKGND);
            ////m_pSkinThumb->Draw(hdc, rcUnion, MAKESBSTATE(SB_PAGEUP, DuiWndState_Normal, m_bVertical));
            //m_pSkinThumb->Draw(hdc, rcThumb, IIF_STATE4(DuiWndState_Hover, 0, 1, 2, 3), 0xFF);

            //ReleaseDuiDC(hdc);
            //NotifySbCode(SB_THUMBTRACK, m_nTrackPos);
            NotifyInvalidate();

            //  计算出新的值
            CRect rcChannel = GetPartRect(SC_CHANNEL);
            m_nValue = m_nMaxVal * ((double)m_nDragPos/(double)rcChannel.Width());

            NotifySbCode(SC_POSITION_DRAG, m_nValue);
        }
    }
    else
    {
        int uHit = HitTest(point);
        if (uHit != m_uHtPrev)
        {
            if (m_uHtPrev == SC_THUMB)
            {
                CRect rcThumb = GetPartRect(m_uHtPrev);
                HDC   hdc     = GetDuiDC(&rcThumb, OLEDC_PAINTBKGND);
                m_pSkinThumb->Draw(hdc, rcThumb, IIF_STATE4(DuiWndState_Normal, 0, 1, 2, 3), 0xFF);
                ReleaseDuiDC(hdc);
            }

            if (uHit == SC_THUMB)
            {
                CRect rcThumb = GetPartRect(uHit);
                HDC   hdc     = GetDuiDC(&rcThumb, OLEDC_PAINTBKGND);
                m_pSkinThumb->Draw(hdc, rcThumb, IIF_STATE4(DuiWndState_Hover, 0, 1, 2, 3), 0xFF);
                ReleaseDuiDC(hdc);
            }

            m_uHtPrev = uHit;
        }
    }
}

void CDuiSliderBar::OnMouseLeave()
{
    if (!m_bDrag)
    {
        if (m_uHtPrev != -1)
        {
            OnMouseMove(0, CPoint(-1,-1));
        }
    }
}

LRESULT CDuiSliderBar::NotifySbCode(UINT uCode, int nPos)
{
    DUINMSLIDER nms;
    nms.hdr.code     = DUINM_SLIDER;
    nms.hdr.idFrom   = GetCmdID();
    nms.hdr.hwndFrom = NULL;
    nms.uSbCode      = uCode;
    nms.pSliderBar   = this;
    nms.nPos         = nPos;
    nms.bVertical    = IsVertical();

    return DuiNotify((LPNMHDR)&nms);
}


}//end of namespace