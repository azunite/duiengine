#pragma once

#include "duiwnd.h"

namespace DuiEngine
{

//////////////////////////////////////////////////////////////////////////
//  CDuiSliderBar
class DUI_EXP CDuiSliderBar : public CDuiWindow
{
    DUIOBJ_DECLARE_CLASS_NAME(CDuiSliderBar, "sliderbar")

public:
    CDuiSliderBar();
    ~CDuiSliderBar();

    enum
    {
        SC_CHANNEL,
        SC_SELECT,
        SC_THUMB,
        SC_POSITION_DRAG,
        SC_POSITION_CLICK,
        SC_MOUSEDOWN,
        SC_MOUSEUP
    };

public:
    BOOL            IsVertical();
    int             HitTest(CPoint pt);

    void            SetMaxValue(int nValue);

    void            SetValue(int nValue);
    int             GetValue();

public:
    CRect           GetPartRect(UINT uSBCode);

    void            OnPaint(CDCHandle dc);
    void            OnLButtonUp(UINT nFlags, CPoint point);
    void            OnLButtonDown(UINT nFlags, CPoint point);
    void            OnMouseMove(UINT nFlags, CPoint point);
    void            OnMouseLeave();

    LRESULT         OnSetScrollInfo(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT         OnGetScrollInfo(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT         NotifySbCode(UINT uCode, int nPos);

protected:
    int             m_nMaxVal;
    int             m_nValue;
    int             m_nCurPos;
    int             m_nInterHeight;
    BOOL            m_bDrag;
    CPoint          m_ptDrag;
    int             m_nDragPos;
    UINT            m_uClicked;
    BOOL            m_bNotify;
    int             m_uHtPrev;
    COLORREF        m_crBg;
    COLORREF        m_crSelect;

    BOOL            m_bVertical;

	CDuiSkinBase *  m_pSkinThumb;
protected:
    DUIWIN_BEGIN_MSG_MAP()
        MSG_WM_LBUTTONDOWN(OnLButtonDown)
        MSG_WM_LBUTTONUP(OnLButtonUp)
        MSG_WM_MOUSEMOVE(OnMouseMove)
        MSG_WM_MOUSELEAVE(OnMouseLeave)
        MSG_WM_PAINT(OnPaint)
    DUIWIN_END_MSG_MAP()

    DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
        DUIWIN_COLOR_ATTRIBUTE("crbg", m_crBg, FALSE)
        DUIWIN_COLOR_ATTRIBUTE("crsel", m_crSelect, FALSE)
		DUIWIN_SKIN_ATTRIBUTE("thumbskin", m_pSkinThumb, FALSE)
        DUIWIN_DWORD_ATTRIBUTE("interheight", m_nInterHeight, FALSE)
    DUIWIN_DECLARE_ATTRIBUTES_END()
};

}
