#ifndef __DXMINICALENDAR_H__
#define __DXMINICALENDAR_H__

#include <atltime.h>
#include <atlcomtime.h>

#include "DuiWnd.h"

namespace DuiEngine
{

class CDuiMonthPicker;
//---------------------------------------------------------------------------
const UINT XTP_NC_DATEPICKER_BUTTON_CLICK      = (NM_FIRST - 50);  // Notify ID to parent window.
const UINT XTP_NC_DATEPICKER_SELECTION_CHANGED = (NM_FIRST - 51);  // Notify ID to parent window.

class CDuiDatePickerMonth;
// ----------------------------------------------------------------------
class CDuiDatePickerButton
{
    friend class CDuiMonthPicker;

public:
    CDuiDatePickerButton();
    virtual ~CDuiDatePickerButton()
    {
    }

    virtual CDuiStringT     GetCaption() const;
    virtual void        SetCaption(LPCTSTR pcszCaption);

public:
    //  This member variable is used to specify the identifier of the button. Also it used as resource ID for a caption string.
    int                 m_nID;
    //  This member variable is used to specify the bounding rectangle coordinates of a button.
    CRect               m_rcButton;

    BOOL                m_bVisible;        // This member variable is used to indicate if a button is visible.

    BOOL                m_bPressed;        // This member variable is used to indicate if a button is pressed.

    BOOL                m_bHighlight;      // This member variable is used to indicate if a button is highlighted.

protected:
    //  This member variable is used to specify the caption of the button.
    CDuiStringT             m_strCaption;
};

//===========================================================================
class CDuiDatePickerDay
{
public:
    CDuiDatePickerDay(CDuiMonthPicker* pControl, CDuiDatePickerMonth* pMonth, COleDateTime dtDay);
    virtual ~CDuiDatePickerDay();

    virtual void        Draw(CDCHandle dc);
    BOOL                DrawDay(CDCHandle dc);
    void                SetRect(const CRect& rcDay);
    CRect               GetRect() const;
    COleDateTime        GetDate() const;
    BOOL                IsVisible() const;
    BOOL                IsToday(COleDateTime &dt) const;

    CDuiDatePickerMonth* GetMonth() const;
    CDuiMonthPicker*      GetDatePicker() const;

protected:
    CDuiMonthPicker*      m_pControl;
    CDuiDatePickerMonth* m_pMonth;
    COleDateTime        m_dtDay;
    CRect               m_rcDay;
    BOOL                m_bVisible;

protected:
    friend class CDuiMonthPicker;
};

//===========================================================================
class CDuiDatePickerMonth
{
    friend class CDuiMonthPicker;

public:
    CDuiDatePickerMonth(CDuiMonthPicker* pControl, COleDateTime dtMonth);
    virtual ~CDuiDatePickerMonth();

    void                AdjustLayout(CRect rcClient);
    virtual void        Draw(CDCHandle dc);
    COleDateTime        GetMonth() const;
    BOOL                GetShowDaysBefore() const;

    BOOL                GetShowDaysAfter() const;
    void                SetShowDaysBefore(BOOL bShow);
    void                SetShowDaysAfter(BOOL bShow);
    BOOL                GetShowLeftScroll() const;
    BOOL                GetShowRightScroll() const;
    void                SetShowScrolling(BOOL bLeftScroll, BOOL bRightScroll);
    CDuiDatePickerDay*   GetDay(int nIndex) const;
    int                 GetDayCount() const;
    void                DrawMonthHeader(CDCHandle dc);
    void                DrawDaysOfWeek(CDCHandle dc);
    CDuiDatePickerDay*   HitTest(CPoint point, BOOL bCheckVisible = TRUE) const;

protected:
    void                DrawScrollTriangle(CDCHandle dc, CRect rcSpot, BOOL bLeftDirection, COLORREF clrColor = 0, BOOL bYears = FALSE);
    void                Triangle(CDCHandle dc, CPoint pt0, CPoint pt1, CPoint pt2, COLORREF clrColor);

    void                ClearDays();
    void                PopulateDays();
    void                OnLButtonDown(UINT nFlags, CPoint point);
    void                OnLButtonUp(UINT nFlags, CPoint point);
    void                AutoAdjustLayout(CRect rcClient);

protected:
    typedef CDuiArray<CDuiDatePickerDay*> ArrayDays;

    CDuiMonthPicker*      m_pControl;

    COLORREF            m_clrStaticBorder;
    COLORREF            m_clrDaysOfWeekBack;
    COLORREF            m_clrDaysOfWeekText;
    COLORREF            m_clrMonthBorder;
    COLORREF            m_clrWeekNumbersBack;
    COLORREF            m_clrWeekNumbersText;
    COLORREF            m_clrMonthHeaderBack;
    COLORREF            m_clrMonthHeaderText;
    COLORREF            m_clrMonthHeaderButton;

    COleDateTime        m_dtMonth;
    BOOL                m_bShowDaysBefore;
    BOOL                m_bShowDaysAfter;
    BOOL                m_bShowLeftScroll;
    BOOL                m_bShowRightScroll;
    CRect               m_rcMonth;
    CRect               m_rcHeader;
    CRect               m_rcDaysOfWeek;
    CRect               m_rcWeekNumbers;
    CRect               m_rcDaysArea;
    CRect               m_rcLeftScroll;
    CRect               m_rcRightScroll;
    ArrayDays           m_arrDays;

private:
    static void         Swap(COleDateTime& dtFirst, COleDateTime& dtSecond);
};

/////////////////////////////////////////////////////////////////////////////
//  CDxMonthPicker window
class DUI_EXP CDuiMonthPicker : public CDuiWindow
{
    DUIOBJ_DECLARE_CLASS_NAME(CDuiMonthPicker, "monthpicker")

    friend class CDuiDatePickerMonth;

public:
    enum DatePickerMouseMode
    {
        mouseNothing,            // No mouse activity by the user.
        mouseScrollingLeft,      // User pressed left scroll triangle and is holding the button.
        mouseScrollingRight,     // User pressed right scroll triangle and is holding the button.
        mouseSelecting,          // User pressed left mouse down on unselected day item and is now selecting a range of day items.
        mouseDeselecting,        // User pressed left mouse down on selected day item and is now de-selecting a range of day items.
        mouseTrackingHeaderList  // User is tracking pop-up month list window.
    };

public:
    CDuiMonthPicker();
    virtual ~CDuiMonthPicker();

    void                SetFirstDayOfWeek(int nDay);
    int                 GetFirstDayOfWeek() const;
    void                SetFirstWeekOfYearDays(int nDays);
    int                 GetFirstWeekOfYearDays() const;

    virtual void        ScrollLeft(int nMonthCount = 1);
    virtual void        ScrollRight(int nMonthCount = 1);

    virtual BOOL        IsSelected(const COleDateTime& dtDay) const;
    virtual void        Select(const COleDateTime& dtDay);
    virtual void        EnsureVisible(const COleDateTime& dtDate);

    CDuiStringT             GetMonthName(int nMonth) const;
    CDuiStringT             GetDayOfWeekName(int nDayOfWeek) const;

    int                 GetMonthDelta() const;
    virtual BOOL        GetCurSel(COleDateTime& refDateTime) const;
    virtual BOOL        SetCurSel(const COleDateTime& refDateTime);
    virtual BOOL        GetToday(COleDateTime& refDateTime) const;
    virtual void        SetToday(const COleDateTime& refDateTime);
    virtual void        AddButton();
    virtual void        AdjustLayout();

protected:
    virtual void        InitNames();
    virtual void        Populate();
    virtual void        CreateMonth();
    virtual void        DrawButtons(CDCHandle dc);
    virtual void        AdjustLayout(CRect rcClient);
    virtual CSize       CalcButtonSize() const;
    virtual void        SetButtonRect();
    virtual void        CalcButtonBandRect();
    virtual void        ProcessButtons(CPoint point);
    static BOOL         ShiftDate(COleDateTime &refDate, int nMonthCount);
    virtual void        OnButtonClick(UINT nID);

protected:
    void                OnLButtonDown(UINT nFlags, CPoint point);
    void                OnLButtonUp(UINT nFlags, CPoint point);
    void                OnPaint(CDCHandle dc);
    int                 OnCreate(LPVOID);
    void                OnSize(UINT nType, CSize);

public:
    COLORREF            m_clrControlBack;
    //  This member variable is used to specify the current Mouse operating mode.
    DatePickerMouseMode m_mouseMode;

    int                 m_nTimerID;                 // This member variable is used to specify the control timer ID.

    CRect               m_rcControl;  // This data member is used to store the control drawing coordinates.

    COleDateTime        m_dtMinRange;      // This member variable specifies the minimum allowable date for a date picker control.
    COleDateTime        m_dtMaxRange;      // This member variable specifies the maximum allowable date for a date picker control.
    COleDateTime        m_dtToday;         // This member variable is used to specify the "Today" date for a date picker control.
    COleDateTime        m_dtFirstMonth;    // This member variable is used to specify the first month in the grid.
    int                 m_nFirstDayOfWeek;          // This member variable is used to specify the first day of the week to display (1-Sunday, 2-Monday ... etc).
    int                 m_nFirstWeekOfYearDays;     // This member variable is used to specify the number of days of the new year in the first week of this year.

    int                 m_nMonthDelta;          // This member variable is used to specify the number of months set

    // before starting the mouse selection.
    BOOL                m_bSelectWeek;         // TRUE when user is started selecting the whole week.

    CDuiDatePickerMonth* m_monthPicker;

    COleDateTime        m_dtFSelBase;  // This member variable is used to specify start day of the continuous selection. Used only for keyboard navigation and selecting.

    CDuiStringT*            m_arMonthNames;    // This member variable contains the localized month names values.
    CDuiStringT*            m_arDayOfWeekNames;// This member variable contains the day abbreviation for drawing in the month header.

    CRect               m_rcGrid;             // Months grid rect.

    CDuiDatePickerButton* m_btnToday;  // Pointer to a date picker button
    CDuiDatePickerButton* m_btnCaptured;  // Pointer to a date picker button

    BOOL                m_bYearsTriangle;          //use extra button for 1 year jump
    CDuiStringT             m_strYearMonthFormat;   //The year month format.

protected:
	DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
// 		DUIWIN_INT_ATTRIBUTE("scrollspeed", m_iScrollSpeed, FALSE)
// 		DUIWIN_INT_ATTRIBUTE("itemheight", m_nItemHei, FALSE)
// 		DUIWIN_SKIN_ATTRIBUTE("itemskin", m_pItemSkin, TRUE)
// 		DUIWIN_SKIN_ATTRIBUTE("iconskin", m_pIconSkin, TRUE)
// 		DUIWIN_COLOR_ATTRIBUTE("critembg",m_crItemBg,FALSE)
// 		DUIWIN_COLOR_ATTRIBUTE("critembg2", m_crItemBg2, FALSE)
// 		DUIWIN_COLOR_ATTRIBUTE("critemselbg",m_crItemSelBg,FALSE)
// 		DUIWIN_COLOR_ATTRIBUTE("crtext",m_crText,FALSE)
// 		DUIWIN_COLOR_ATTRIBUTE("crseltext",m_crSelText,FALSE)
// 		DUIWIN_INT_ATTRIBUTE("icon-x", m_ptIcon.x, FALSE)
// 		DUIWIN_INT_ATTRIBUTE("icon-y", m_ptIcon.y, FALSE)
// 		DUIWIN_INT_ATTRIBUTE("text-x", m_ptText.x, FALSE)
// 		DUIWIN_INT_ATTRIBUTE("text-y", m_ptText.y, FALSE)
// 		DUIWIN_INT_ATTRIBUTE("hottrack",m_bHotTrack,FALSE)
	DUIWIN_DECLARE_ATTRIBUTES_END()

    DUIWIN_BEGIN_MSG_MAP()
        MSG_WM_CREATE(OnCreate)
        MSG_WM_PAINT(OnPaint)
        MSG_WM_LBUTTONDOWN(OnLButtonDown)
        MSG_WM_LBUTTONUP(OnLButtonUp)
        MSG_WM_SIZE(OnSize)
    DUIWIN_END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////
inline void CDuiMonthPicker::SetFirstDayOfWeek(int nDay)
{
    ATLASSERT(nDay >= 1 && nDay <= 7);
    if (nDay >= 1 && nDay <= 7 && nDay != m_nFirstDayOfWeek)
    {
        m_nFirstDayOfWeek = nDay;
        Populate();
    }
}

inline int CDuiMonthPicker::GetFirstDayOfWeek() const
{
    return m_nFirstDayOfWeek;
}

inline void CDuiMonthPicker::SetFirstWeekOfYearDays(int nDays)
{
    ATLASSERT(nDays >= 1 && nDays <= 7);
    if (nDays >= 1 && nDays <= 7 && nDays != m_nFirstWeekOfYearDays)
    {
        m_nFirstWeekOfYearDays = nDays;
        NotifyInvalidate();
    }
}

inline int CDuiMonthPicker::GetFirstWeekOfYearDays() const
{
    return m_nFirstWeekOfYearDays;
}

inline CDuiStringT CDuiMonthPicker::GetMonthName(int nMonth) const
{
    return nMonth >= 1 && nMonth <= 12 ? m_arMonthNames[nMonth - 1] : _T("");
}

inline CDuiStringT CDuiMonthPicker::GetDayOfWeekName(int nDayOfWeek) const
{
    return nDayOfWeek >= 1 && nDayOfWeek <= 7 ? m_arDayOfWeekNames[nDayOfWeek - 1] : _T("");
}

inline int CDuiMonthPicker::GetMonthDelta() const
{
    return 1;
}

inline BOOL CDuiMonthPicker::GetToday(COleDateTime& refDateTime) const
{
    refDateTime = m_dtToday;
    return TRUE;
}

inline void CDuiMonthPicker::AdjustLayout()
{
    InitNames();
    AdjustLayout(m_rcControl);
}

inline COleDateTime CDuiDatePickerMonth::GetMonth() const
{
    return m_dtMonth;
}

inline BOOL CDuiDatePickerMonth::GetShowDaysBefore() const
{
    return m_bShowDaysBefore;
}

inline BOOL CDuiDatePickerMonth::GetShowDaysAfter() const
{
    return m_bShowDaysAfter;
}

inline void CDuiDatePickerMonth::SetShowDaysBefore(BOOL bShow)
{
    m_bShowDaysBefore = bShow;
}

inline void CDuiDatePickerMonth::SetShowDaysAfter(BOOL bShow)
{
    m_bShowDaysAfter = bShow;
}

inline BOOL CDuiDatePickerMonth::GetShowLeftScroll() const
{
    return m_bShowLeftScroll;
}

inline BOOL CDuiDatePickerMonth::GetShowRightScroll() const
{
    return m_bShowRightScroll;
}

inline void CDuiDatePickerMonth::SetShowScrolling(BOOL bLeftScroll, BOOL bRightScroll)
{
    m_bShowLeftScroll = bLeftScroll;
    m_bShowRightScroll = bRightScroll;
}

inline void CDuiDatePickerMonth::Swap(COleDateTime& dtFirst, COleDateTime& dtSecond)
{
    COleDateTime dtTemp = dtFirst;
    dtFirst = dtSecond;
    dtSecond = dtTemp;
}

inline void CDuiDatePickerDay::SetRect(const CRect& rcDay)
{
    m_rcDay = rcDay;
}

inline CRect CDuiDatePickerDay::GetRect() const
{
    return m_rcDay;
}

inline COleDateTime CDuiDatePickerDay::GetDate() const
{
    return m_dtDay;
}

inline BOOL CDuiDatePickerDay::IsVisible() const
{
    return m_bVisible;
}

inline CDuiDatePickerMonth* CDuiDatePickerDay::GetMonth() const
{
    return m_pMonth;
}

inline CDuiMonthPicker* CDuiDatePickerDay::GetDatePicker() const
{
    return m_pControl;
}


}//end of namespace DuiEngine

#endif  //  __DXMINICALENDAR_H__

