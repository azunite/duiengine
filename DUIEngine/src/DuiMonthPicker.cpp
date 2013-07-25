#include "duistd.h"

#include "DuiMonthPicker.h"
#include <math.h>

#define XTP_HALF_SECOND  (1.0/172800.0)
const UINT XTP_MAX_WEEKS = (UINT)6;

const UINT XTP_WEEK_DAYS = (UINT)7;

#define XTP_IDS_DATEPICKER_TODAY                9000

//////////////////////////////////////////////////////////////////////////
BOOL DateIsEqual(const COleDateTime& dt1, const COleDateTime& dt2, BOOL bOneSecTimeDiff = FALSE)
{
    if (dt1.GetStatus() == COleDateTime::null ||
        dt2.GetStatus() == COleDateTime::null)
        return FALSE;

    double dTimeDiff = bOneSecTimeDiff ? XTP_HALF_SECOND * 2 : XTP_HALF_SECOND;
    return dTimeDiff >= fabs(dt1 - dt2);
}

BOOL GetAsSystemTime(const COleDateTime& dtTime, SYSTEMTIME& sysTime)
{
    ::ZeroMemory(&sysTime, sizeof(sysTime));
    return dtTime.GetAsSystemTime(sysTime);
}

int GetDiff_Months(const COleDateTime& dt1, const COleDateTime& dt2)
{
    int nYear1 = dt1.GetYear();
    int nMonth1 = dt1.GetMonth();

    int nYear2 = dt2.GetYear();
    int nMonth2 = dt2.GetMonth();

    int nYearDiff = nYear1 - nYear2;
    int nMonthDiff = nYearDiff * 12;

    nMonthDiff += nMonth1 - nMonth2;

    return nMonthDiff;
}

CDuiStringT GetLocaleString(LCTYPE LCType, int nMaxLength)
{
	TCHAR *pszBuf=new TCHAR[nMaxLength+1];
    int nResult = ::GetLocaleInfo(LOCALE_USER_DEFAULT, LCType ,pszBuf, nMaxLength);
	pszBuf[nResult]=0;
	CDuiStringT strResult(pszBuf);
	delete pszBuf;
    return strResult;
}

BOOL ShiftDate_Month(COleDateTime &refDate, int nMonthCount)
{
    SYSTEMTIME sysDate;
    if (!GetAsSystemTime(refDate, sysDate))
        return FALSE;

    int nYearNew = sysDate.wYear + nMonthCount / 12;
    int nMonthNew = sysDate.wMonth + nMonthCount % 12;

    if (nMonthNew > 12)
    {
        nMonthNew -= 12 * (nMonthCount / abs(nMonthCount));
        nYearNew++;
    }
    else if (nMonthNew <= 0)
    {
        nYearNew--;
        nMonthNew += 12;

        DUIASSERT(nMonthNew >= 1 && nMonthNew <= 12);
    }

    return COleDateTime::valid == refDate.SetDate(nYearNew, nMonthNew, 1);
}

int GetMaxMonthDay(COleDateTime dtDate)
{
    SYSTEMTIME sysDate;
    if (!GetAsSystemTime(dtDate, sysDate))
        return 0;

    // days per month  -     _  jan feb mar apr may jun   jul aug sep oct nov dec
    static int arDays[13] = {0, 31, 28, 31, 30, 31, 30,   31, 31, 30, 31, 30, 31};
    if (sysDate.wMonth == 2 && sysDate.wYear % 4 == 0)
    {
        if (sysDate.wYear % 100 != 0 || sysDate.wYear % 400 == 0)
            return 29;
        else
            return 28;
    }
    else
    {
        return arDays[sysDate.wMonth];
    }
}

BOOL UpdateMonthDay(COleDateTime &refDate, int nMonthDay)
{
    if (nMonthDay > 28)
    {
        int nMaxDay = GetMaxMonthDay(refDate);
        if (!nMaxDay)
        {
            return FALSE;
        }
        nMonthDay = min(nMonthDay, nMaxDay);
    }

    SYSTEMTIME sysDate;
    if (!GetAsSystemTime(refDate, sysDate))
        return FALSE;

    int nRes = refDate.SetDate(sysDate.wYear, sysDate.wMonth, nMonthDay);
    return nRes == 0;
}

BOOL ShiftDate_Month(COleDateTime &refDate, int nMonthCount, int nMonthDay)
{
    if (ShiftDate_Month(refDate, nMonthCount))
    {
        BOOL bRes = UpdateMonthDay(refDate, nMonthDay);
        return bRes;
    }
    return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
double _RoundDateTime_dbl(double dblDT)
{
    return (dblDT >= 0 ? dblDT + XTP_HALF_SECOND : dblDT - XTP_HALF_SECOND);
}

double _ResetTime_dbl(double dblDT)
{
    return (double)((LONGLONG)_RoundDateTime_dbl(dblDT));
}

double _ResetDate_dbl(double dblDT)
{
    double dblDate = _ResetTime_dbl(dblDT);
    double dblResult = dblDT > dblDate ? (dblDT - dblDate) : (dblDate - dblDT);

    double dblDate_raw = (double)((LONGLONG)dblDT);

    if (dblDate_raw != dblDate)
    {
        dblResult = _RoundDateTime_dbl(dblResult);
    }
    return dblResult;
}

const COleDateTime ResetTime(const COleDateTime& dtDateTime)
{
    return (DATE)_ResetTime_dbl((double)dtDateTime);
}


void XTPGetAsSystemTime(const COleDateTime& dateTime, SYSTEMTIME& st)
{
#if _MSC_VER < 1200
	UNREFERENCED_PARAMETER(dateTime);
	UNREFERENCED_PARAMETER(st);
	DUIASSERT(FALSE);
#else
	dateTime.GetAsSystemTime(st);
#endif
}

//////////////////////////////////////////////////////////////////////////
//	Namespace DuiEngine
//////////////////////////////////////////////////////////////////////////

namespace DuiEngine
{

//////////////////////////////////////////////////////////////////////////
//  CDxDatePickerButton
CDuiDatePickerButton::CDuiDatePickerButton()
{
    m_rcButton.SetRectEmpty();
    m_bVisible = TRUE;
    m_bPressed = FALSE;
    m_bHighlight = FALSE;
    m_nID = 0;
}

CDuiStringT CDuiDatePickerButton::GetCaption() const
{
    return m_strCaption;
}

void CDuiDatePickerButton::SetCaption(LPCTSTR pcszCaption)
{
    m_strCaption = pcszCaption;
}

//////////////////////////////////////////////////////////////////////////
//  CDxDatePickerDay
CDuiDatePickerDay::CDuiDatePickerDay(CDuiMonthPicker* pControl, CDuiDatePickerMonth* pMonth, COleDateTime dtDay)
: m_dtDay(dtDay), m_pControl(pControl), m_pMonth(pMonth)
{
    m_rcDay.SetRectEmpty();
    m_bVisible = FALSE;
}

CDuiDatePickerDay::~CDuiDatePickerDay()
{
}

void CDuiDatePickerDay::Draw(CDCHandle dc)
{
    m_bVisible = FALSE;

    if (m_rcDay.IsRectEmpty())
        return;

    m_bVisible = DrawDay(dc);
}

BOOL CDuiDatePickerDay::DrawDay(CDCHandle dc)
{
    // check this day item
    BOOL bThisMonthItem = FALSE;
    BOOL bNextMonthItem = FALSE;
    BOOL bPreviousMonthItem = FALSE;

    CDuiMonthPicker* pControl = GetDatePicker();
    CDuiDatePickerMonth* pMonth = GetMonth();

    COleDateTime dtDay = GetDate();
    CRect rcDay = GetRect();

    if (dtDay.GetYear() > pMonth->GetMonth().GetYear())
    {
        bNextMonthItem = TRUE;
    }
    else if (dtDay.GetYear() < pMonth->GetMonth().GetYear())
    {
        bPreviousMonthItem = TRUE;
    }
    else
    {
        // years the same
        if (dtDay.GetMonth() > pMonth->GetMonth().GetMonth())
            bNextMonthItem = TRUE;
        else if (dtDay.GetMonth() < pMonth->GetMonth().GetMonth())
            bPreviousMonthItem = TRUE;
        else // months the same
            bThisMonthItem = TRUE;
    }

    if (bPreviousMonthItem && !pMonth->GetShowDaysBefore())
        return FALSE;

    if (bNextMonthItem && !pMonth->GetShowDaysAfter())
        return FALSE;


    // apply settings to the DC
    dc.SetBkMode(TRANSPARENT);
    dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
    dc.FillSolidRect(rcDay, GetSysColor(COLOR_WINDOW));

    // change default drawing metrics if day is selected
    if (pControl->IsSelected(dtDay))
    {
        dc.SetTextColor(GetSysColor(COLOR_WINDOW));
        dc.FillSolidRect(rcDay, GetSysColor(COLOR_WINDOWTEXT));
    }

    // make a text for drawing
    CDuiStringT strText;
    strText.Format(_T("%i"), dtDay.GetDay());

    // draw item content
    {
        // draw item text
        HFONT hFontOld = (HFONT)dc.SelectFont(DuiFontPool::getSingleton().GetFont(DUIF_DEFAULTFONT));
        dc.DrawText(strText, strText.GetLength(), &rcDay, DT_SINGLELINE | DT_VCENTER | DT_CENTER | DT_NOCLIP);
    }

    CRect rcFocus = rcDay;
    BOOL bToday = FALSE;

    // highlight today item
    if (IsToday(dtDay))
    {
        dc.Draw3dRect(rcDay, GetSysColor(COLOR_HIGHLIGHT), GetSysColor(COLOR_HIGHLIGHT));
        bToday = TRUE;
    }

    if (pControl->IsSelected(dtDay))
    {
        if (!bToday)
        {
            dc.SetTextColor(0);
            dc.SetBkColor(RGB(255, 255, 255));
            dc.DrawFocusRect(&rcFocus);
        }
        else
        {
            COLORREF clrFocus = GetSysColor(COLOR_HIGHLIGHT);
            clrFocus = clrFocus ^ RGB(255, 128, 128);

            rcFocus.DeflateRect(0, 0, 1, 1);

            CPen pen1;
            pen1.CreatePen(PS_DOT, 1, clrFocus);

            HPEN hOldPen = dc.SelectPen(pen1);

            dc.MoveTo(rcFocus.TopLeft());
            dc.LineTo(rcFocus.right, rcFocus.top);
            dc.LineTo(rcFocus.right, rcFocus.bottom);
            dc.LineTo(rcFocus.left, rcFocus.bottom);
            dc.LineTo(rcFocus.left, rcFocus.top);

            dc.SelectPen(hOldPen);
        }
    }

    return TRUE;
}

BOOL CDuiDatePickerDay::IsToday(COleDateTime &dt) const
{
    BOOL bReturn = FALSE;
    COleDateTime dtToday;
    if (m_pControl->GetToday(dtToday))
    {
        if (dt.GetMonth() == dtToday.GetMonth() && dt.GetYear() == dtToday.GetYear() && dt.GetDay() == dtToday.GetDay())
            bReturn = TRUE;
    }

    return bReturn;
}

/////////////////////////////////////////////////////////////////////////////
// CDxDatePickerMonth

CDuiDatePickerMonth::CDuiDatePickerMonth(CDuiMonthPicker* pControl, COleDateTime dtMonth)
    : m_pControl(pControl), m_dtMonth(dtMonth)
{
    m_rcHeader.SetRectEmpty();
    m_rcDaysOfWeek.SetRectEmpty();
    m_rcWeekNumbers.SetRectEmpty();
    m_rcDaysArea.SetRectEmpty();
    m_rcLeftScroll.SetRectEmpty();
    m_rcRightScroll.SetRectEmpty();

    m_bShowDaysBefore = FALSE;
    m_bShowDaysAfter = FALSE;
    m_bShowLeftScroll = TRUE;
    m_bShowRightScroll = TRUE;

    m_clrDaysOfWeekBack = GetSysColor(COLOR_WINDOW);
    m_clrDaysOfWeekText = GetSysColor(COLOR_WINDOWTEXT);

    PopulateDays();
}

CDuiDatePickerMonth::~CDuiDatePickerMonth()
{
    ClearDays();
}

void CDuiDatePickerMonth::PopulateDays()
{
    if (m_dtMonth.GetYear() <= 100 && m_dtMonth.GetMonth() <= 2)
        m_dtMonth = COleDateTime(100,2,1,0,0,0);

    if (m_dtMonth.GetStatus() != COleDateTime::valid)
    {
        ATLASSERT(FALSE);
        m_dtMonth = ResetTime(COleDateTime::GetCurrentTime());
    }
    //if (m_dtMonth < COleDateTime(1601,4,1,0,0,0))
    //  m_dtMonth = COleDateTime(1601,4,1,0,0,0);

    // init days from 1st to last
    COleDateTime dtDay(m_dtMonth.GetYear(), m_dtMonth.GetMonth(), 1, 0, 0, 0);
    COleDateTimeSpan spDay(1, 0, 0, 0);

    // adjust first day of the week
    int nOleFirstDayOfWeek = m_pControl->GetFirstDayOfWeek();

    int iDayOfWeek = dtDay.GetDayOfWeek();
    if (iDayOfWeek != -1)
    {
        while (dtDay.GetDayOfWeek() != nOleFirstDayOfWeek && dtDay.GetDayOfWeek() != -1)
        {
            dtDay -= spDay;
        }
    }
    else
    {
        COleDateTime dtFutureDay(dtDay);
        dtFutureDay.SetDate(dtFutureDay.GetYear() + 2000, dtFutureDay.GetMonth(), dtFutureDay.GetDay());
        iDayOfWeek = dtFutureDay.GetDayOfWeek();

        while (dtFutureDay.GetDayOfWeek() != nOleFirstDayOfWeek && dtFutureDay.GetDayOfWeek() != -1)
        {
            dtFutureDay -= spDay;
            dtDay -= spDay;
        }
    }

    //while (dtDay.GetDayOfWeek() != nOleFirstDayOfWeek && dtDay.GetDayOfWeek() != -1)
    //{
    //  dtDay -= spDay;
    //}

    // populate all grid days
    for (int nWeek = 0; nWeek < XTP_MAX_WEEKS; nWeek++)
    {
        for (int nDay = 0; nDay < XTP_WEEK_DAYS; nDay++)
        {
            // create and add new day item
            CDuiDatePickerDay* pDay = new CDuiDatePickerDay(m_pControl, this, dtDay);
            m_arrDays.Add(pDay);
            // move next day
            dtDay += spDay;
        }
    }
}

void CDuiDatePickerMonth::AutoAdjustLayout(CRect rcClient)
{
    m_rcMonth = rcClient;
    // calc header rect
    m_rcHeader = m_rcMonth;
    m_rcHeader.left  += 2;
    m_rcHeader.right -= 2;
    m_rcHeader.bottom = m_rcHeader.top + 18; // TODO: change to font height

    // calc days of week rect
    m_rcDaysOfWeek = m_rcMonth;
    m_rcDaysOfWeek.top = m_rcHeader.bottom;
    m_rcDaysOfWeek.bottom = m_rcDaysOfWeek.top + 18; // TODO: change to font height

    // draw week numbers
    m_rcWeekNumbers = m_rcMonth;
    m_rcWeekNumbers.top = m_rcDaysOfWeek.bottom;
    m_rcWeekNumbers.right = m_rcWeekNumbers.left + 18; // TODO: change to font width

    // calc triangles rect
    m_rcLeftScroll = m_rcHeader;
    m_rcRightScroll = m_rcHeader;
    int nScrollWidth = min(m_rcWeekNumbers.Width(), m_rcHeader.Width() / 8);
    m_rcHeader.left += nScrollWidth;
    m_rcHeader.right -= nScrollWidth;
    m_rcLeftScroll.right = m_rcHeader.left;
    m_rcRightScroll.left = m_rcHeader.right;

    // calc days display params
    m_rcDaysArea = m_rcMonth;
    m_rcDaysArea.top = m_rcDaysOfWeek.bottom;
    m_rcDaysArea.left = m_rcWeekNumbers.right;
    m_rcDaysArea.right -= m_rcWeekNumbers.Width();

    // calc simple day rect sizes
    CSize szDay(m_rcDaysArea.Width() / XTP_WEEK_DAYS, m_rcDaysArea.Height() / XTP_MAX_WEEKS);

    // calc rects for all days
    CRect rcDay;
    int nIndex = 0;
    for (int nWeek = 0; nWeek < XTP_MAX_WEEKS; nWeek++)
    {
        for (int nDay = 0; nDay < XTP_WEEK_DAYS; nDay++)
        {
            CDuiDatePickerDay* pDay = GetDay(nIndex);
            nIndex++;

            rcDay.left = m_rcDaysArea.left + nDay * szDay.cx + 1;
            rcDay.top = m_rcDaysArea.top + nWeek * szDay.cy;
            rcDay.right = rcDay.left + szDay.cx;
            rcDay.bottom = rcDay.top + szDay.cy;
            pDay->SetRect(rcDay);
        }
    }
}

void CDuiDatePickerMonth::AdjustLayout(CRect rcClient)
{
    AutoAdjustLayout(rcClient);
}

CDuiDatePickerDay* CDuiDatePickerMonth::GetDay(int nIndex) const
{
    if (nIndex < GetDayCount())
        return m_arrDays[nIndex];
    return NULL;
}

int CDuiDatePickerMonth::GetDayCount() const
{
    return (int)m_arrDays.GetCount();
}

void CDuiDatePickerMonth::Triangle(CDCHandle dc, CPoint pt0, CPoint pt1, CPoint pt2, COLORREF clrColor)
{
    //CPen pen;
    //pen.CreatePen(PS_DOT, 1, clrColor);

    //CBrush brush;
    //brush.CreateSolidBrush(clrColor);

    //HPEN hOldPen = dc.SelectPen(pen);
    //HBRUSH oldBrush = dc.SelectBrush(brush);

    CPoint pts[3];
    pts[0] = pt0;
    pts[1] = pt1;
    pts[2] = pt2;
    dc.Polygon(pts, 3);

    //dc.SelectPen(hOldPen);
    //dc.SelectBrush(oldBrush);
}

void CDuiDatePickerMonth::DrawScrollTriangle(CDCHandle dc, CRect rcSpot, BOOL bLeftDirection, COLORREF clrColor, BOOL bYears)
{
    CPoint ptCenter(rcSpot.CenterPoint());

    if (bLeftDirection)
    {
        Triangle(dc, ptCenter, CPoint(ptCenter.x + 4, ptCenter.y - 4), CPoint(ptCenter.x + 4, ptCenter.y + 4), clrColor);

        if (bYears)
        {
            Triangle(dc, CPoint(ptCenter.x - 8, ptCenter.y), CPoint(ptCenter.x - 4, ptCenter.y - 4), CPoint(ptCenter.x - 4, ptCenter.y + 4), clrColor);
            Triangle(dc, CPoint(ptCenter.x + 4, ptCenter.y), CPoint(ptCenter.x + 8, ptCenter.y - 4), CPoint(ptCenter.x + 8, ptCenter.y + 4), clrColor);

            //Triangle(pDC,
            //  CPoint(ptCenter.x + 2, ptCenter.y),
            //  CPoint(ptCenter.x + 3, ptCenter.y - 2),
            //  CPoint(ptCenter.x + 3, ptCenter.y + 2),
            //  RGB(255,255,255));
        }
    }
    else
    {
        Triangle(dc, ptCenter, CPoint(ptCenter.x - 4, ptCenter.y - 4), CPoint(ptCenter.x - 4, ptCenter.y + 4), clrColor);

        if (bYears)
        {
            Triangle(dc, CPoint(ptCenter.x + 8, ptCenter.y), CPoint(ptCenter.x + 4, ptCenter.y - 4), CPoint(ptCenter.x + 4, ptCenter.y + 4), clrColor);
            Triangle(dc, CPoint(ptCenter.x - 4, ptCenter.y), CPoint(ptCenter.x - 8, ptCenter.y - 4), CPoint(ptCenter.x - 8, ptCenter.y + 4), clrColor);

            //Triangle(pDC,
            //  CPoint(ptCenter.x - 2, ptCenter.y),
            //  CPoint(ptCenter.x - 3, ptCenter.y - 2),
            //  CPoint(ptCenter.x - 3, ptCenter.y + 2),
            //  RGB(255,255,255));
        }
    }
}

void CDuiDatePickerMonth::DrawMonthHeader(CDCHandle dc)
{
    if (m_rcHeader.IsRectEmpty())
        return;

    COleDateTime dtMonth = GetMonth();
    CRect rcHeader = m_rcHeader;
    CRect rcLeftScroll = m_rcLeftScroll;
    CRect rcRightScroll = m_rcRightScroll;

    CRect rcClient(m_pControl->m_rcControl);
    //dc.Draw3dRect(0, 0, rcClient.Width(), rcClient.Height(), m_clrStaticBorder, m_clrStaticBorder);

    CRect rcHeaderBk = m_rcMonth;
    rcHeaderBk.bottom = rcHeader.bottom;

    // fill background
    dc.FillSolidRect(rcHeaderBk, RGB(191, 219, 255));

    // draw header text
    dc.SetBkColor(GetSysColor(COLOR_BTNFACE));
    dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));

    HFONT hFontOld = (HFONT)dc.SelectFont(DuiFontPool::getSingleton().GetFont(DUIF_DEFAULTFONT));

    CDuiStringT strText;

    if (!m_pControl->m_strYearMonthFormat.IsEmpty())
    {
        //strText = GetDateFormat(dtMonth, pControl->m_strYearMonthFormat);
    }
    else
    {
        strText.Format(_T("%s %d"), (LPCTSTR)m_pControl->GetMonthName( dtMonth.GetMonth()), dtMonth.GetYear());
    }

    dc.DrawText(strText, strText.GetLength(), &rcHeader, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

    // draw left scroll triangle
    if (!rcLeftScroll.IsRectEmpty())
    {
        // draw left triangle itself
        if (GetShowLeftScroll())
            DrawScrollTriangle(dc, rcLeftScroll, TRUE, m_clrMonthHeaderButton, m_pControl->m_bYearsTriangle);
    }

    // draw right scroll triangle
    if (!rcRightScroll.IsRectEmpty())
    {
        // draw right triangle itself
        if (GetShowRightScroll())
            DrawScrollTriangle(dc, rcRightScroll, FALSE, m_clrMonthHeaderButton, m_pControl->m_bYearsTriangle);
    }

    dc.SelectFont(hFontOld);
}

void CDuiDatePickerMonth::DrawDaysOfWeek(CDCHandle dc)
{
    if (m_rcDaysOfWeek.IsRectEmpty())
        return;

    // fill background
    dc.FillSolidRect(m_rcDaysOfWeek, m_clrDaysOfWeekBack);

    // draw days of week text
    dc.SetBkColor(m_clrDaysOfWeekBack);
    dc.SetTextColor(m_clrDaysOfWeekText);

    HFONT hFontOld = (HFONT)dc.SelectFont(DuiFontPool::getSingleton().GetFont(DUIF_DEFAULTFONT));

    int nMaxX = 0;
    SIZE szText;

    dc.GetTextExtent(_T("XX"), 2, &szText);

    int nTwoLetterWidth = szText.cx;
    int nWholeLetterWidth = 0;

    for (int i = 0; i < XTP_WEEK_DAYS; i++)
    {
        CDuiStringT strText(m_pControl->GetDayOfWeekName(i));

        dc.GetTextExtent(strText, strText.GetLength(), &szText);
        nWholeLetterWidth = max(nWholeLetterWidth, szText.cx);
    }

    for (int nDayDelta = 0; nDayDelta < XTP_WEEK_DAYS; nDayDelta++)
    {
        // calc item rect
        CDuiDatePickerDay* pDay = GetDay(nDayDelta);
        CRect rcItem(pDay->GetRect());
        rcItem.top = m_rcDaysOfWeek.top;
        rcItem.bottom = m_rcDaysOfWeek.bottom - 2;
        nMaxX = rcItem.right;

        // get item text
        CDuiStringT strText(m_pControl->GetDayOfWeekName(pDay->GetDate().GetDayOfWeek()));

        // Check if we can draw whole text
        if (nWholeLetterWidth + 4 <= rcItem.Width())
        {
            dc.DrawText(strText, strText.GetLength(), &rcItem, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
        }
        else if (nTwoLetterWidth + 4 <= rcItem.Width()) // Draw 2 letters
        {
            int nChrLen = (int)_tcsnbcnt(strText, 2);
            dc.DrawText(strText, nChrLen, &rcItem, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
        }
        else // Draw only first letter
        {
            int nChrLen = (int)_tcsnbcnt(strText, 1);
            dc.DrawText(strText, nChrLen, &rcItem, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
        }
    }

    // draw bottom line on days of the week
    CRect rcBottomLine(m_rcDaysOfWeek);
    rcBottomLine.bottom--;
    rcBottomLine.top = rcBottomLine.bottom - 1;
    rcBottomLine.left = m_rcWeekNumbers.right - 1;
    rcBottomLine.right = nMaxX;
    dc.FillSolidRect(rcBottomLine, m_clrMonthBorder);

    dc.SelectFont(hFontOld);
}

void CDuiDatePickerMonth::Draw(CDCHandle dc)
{
    // draw header
    DrawMonthHeader(dc);

    // draw days of week
    DrawDaysOfWeek(dc);

    //  draw all days
    int nDaysCount = GetDayCount();
    for (int nIndex = 0; nIndex < nDaysCount; nIndex++)
    {
        CDuiDatePickerDay* pDay = GetDay(nIndex);
        pDay->Draw(dc);
    }
}

void CDuiDatePickerMonth::ClearDays()
{
    // cleanup old month array
    int nOldDayCount = GetDayCount();
    for (int nDay = 0; nDay < nOldDayCount; nDay++)
    {
        CDuiDatePickerDay* pDay = GetDay(nDay);
        delete pDay;
    }
    m_arrDays.RemoveAll();
}

void CDuiDatePickerMonth::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (!m_pControl)
        return;

    // check left scroll item
    if (m_bShowLeftScroll && !m_rcLeftScroll.IsRectEmpty() && m_rcLeftScroll.PtInRect(point))
    {
        m_pControl->m_mouseMode = CDuiMonthPicker::mouseScrollingLeft;
        if (m_pControl->m_bYearsTriangle)
        {
            if (point.x < m_rcLeftScroll.left + 9)
            {
                if (m_dtMonth.GetYear() >= 100 || (m_dtMonth.GetYear() == 100 && m_dtMonth.GetMonth() >= 3))
                    m_pControl->ScrollLeft(m_pControl->GetMonthDelta());
            }
            else if (point.x > m_rcLeftScroll.right - 9)
            {
                if (m_dtMonth.GetYear() >= 101 || (m_dtMonth.GetYear() == 101 && m_dtMonth.GetMonth() >= 3))
                    m_pControl->ScrollLeft(12 * m_pControl->GetMonthDelta());
            }
        }
        else
        {
            m_pControl->ScrollLeft(m_pControl->GetMonthDelta());
        }
        return;
    }

    // check right scroll item
    if (m_bShowRightScroll && !m_rcRightScroll.IsRectEmpty() && m_rcRightScroll.PtInRect(point))
    {
        m_pControl->m_mouseMode = CDuiMonthPicker::mouseScrollingRight;

        if (m_pControl->m_bYearsTriangle)
        {
            if (point.x < m_rcRightScroll.left + 9)
                m_pControl->ScrollRight(12 * m_pControl->GetMonthDelta());
            else if (point.x > m_rcLeftScroll.right - 9)
                m_pControl->ScrollRight(m_pControl->GetMonthDelta());
        }
        else
        {
            m_pControl->ScrollRight(m_pControl->GetMonthDelta());
        }
        return;
    }

    //  check header click
    if (!m_rcHeader.IsRectEmpty() && CRect(m_rcHeader.left + 20, m_rcHeader.top, m_rcHeader.right - 20, m_rcHeader.bottom).PtInRect(point))
    {
        // call month popup list
        //m_pControl->ShowListHeader(m_rcHeader, m_dtMonth);
        return;
    }

    // check week numbers click
    m_pControl->m_bSelectWeek = !m_rcWeekNumbers.IsRectEmpty() && m_rcWeekNumbers.PtInRect(point);

    CPoint ptFirstWeekDay(point);
    ptFirstWeekDay.x = m_rcWeekNumbers.right + 3;

    //  check day item
    CDuiDatePickerDay* pDay = HitTest(m_pControl->m_bSelectWeek ? ptFirstWeekDay : point, FALSE);
    if (pDay)
    {
        COleDateTime dtDay(pDay->GetDate());
        BOOL bSelected = m_pControl->IsSelected(dtDay);
        if (m_pControl->m_bSelectWeek)
        {
            //  week is selected only when all week days are selected
            for (int i = 0; i < 7; i++)
            {
                COleDateTime dtDay_i = dtDay + COleDateTimeSpan(i, 0, 0, 0);
                bSelected &= m_pControl->IsSelected(dtDay_i);
            }
        }

        m_pControl->m_mouseMode = CDuiMonthPicker::mouseSelecting;

        m_pControl->m_dtFSelBase = dtDay;

        m_pControl->NotifyInvalidate();
    }
}

void CDuiDatePickerMonth::OnLButtonUp(UINT /*nFlags*/, CPoint /*point*/)
{
}

CDuiDatePickerDay* CDuiDatePickerMonth::HitTest(CPoint point, BOOL bCheckVisible) const
{
    // enumerate month array
    int nDayCount = GetDayCount();
    for (int nDay = 0; nDay < nDayCount; nDay++)
    {
        CDuiDatePickerDay* pDay = GetDay(nDay);
        if (pDay && pDay->GetRect().PtInRect(point) && (pDay->IsVisible() || !bCheckVisible))
        {
            return pDay;
        }
    }
    return NULL;
}

//////////////////////////////////////////////////////////////////////////////
// CDxMonthPicker

CDuiMonthPicker::CDuiMonthPicker()
{
    m_monthPicker = NULL;

    m_mouseMode = mouseNothing;
    m_nTimerID = 0;
    m_bSelectWeek = FALSE;

    m_clrControlBack = RGB(255,255,255);

    m_nFirstDayOfWeek = 2;
    m_nFirstWeekOfYearDays = 1;
    m_dtToday = COleDateTime::GetCurrentTime();
    m_dtFirstMonth.SetDate(m_dtToday.GetYear(), m_dtToday.GetMonth(), 1);
    m_dtMinRange.SetStatus(COleDateTime::null);
    m_dtMaxRange.SetStatus(COleDateTime::null);

    m_rcControl.SetRectEmpty();
    m_rcGrid.SetRectEmpty();

    m_btnToday = NULL;
    m_bYearsTriangle = TRUE;
    m_btnCaptured = NULL;

    AddButton();

    m_arMonthNames     = new CDuiStringT[12];
    m_arDayOfWeekNames = new CDuiStringT[7];

    InitNames();
}

CDuiMonthPicker::~CDuiMonthPicker()
{
    if (m_monthPicker != NULL)
    {
        delete m_monthPicker;
    }

    if (m_nTimerID != 0)
        KillDuiTimer(m_nTimerID);

    delete m_btnToday;

    delete[] m_arDayOfWeekNames;
    delete[] m_arMonthNames;
}

/////////////////////////////////////////////////////////////////////////////
// CDxMonthPicker message handlers

int CDuiMonthPicker::OnCreate(LPVOID)
{
    int nRet = __super::OnCreate(NULL);
    if (nRet == -1)
        return nRet;

	Populate();

    CRect rcClient;
    GetRect(rcClient);
    AdjustLayout(rcClient);

    //  默认选择当天
    Select(m_dtToday);

    return nRet;
}

void CDuiMonthPicker::AddButton()
{
    m_btnToday = new CDuiDatePickerButton();

    m_btnToday->m_nID = XTP_IDS_DATEPICKER_TODAY;
    m_btnToday->m_strCaption = _T("Today");
}

void CDuiMonthPicker::AdjustLayout(CRect rcClient)
{
    m_dtToday = COleDateTime::GetCurrentTime();

    m_rcControl = rcClient;

    CSize szMonth(0, 0);
    CRect rcMonth(0, 0, 0, 0);

    //get button size
    CSize szButton(CalcButtonSize());

    m_rcGrid.CopyRect(&m_rcControl);

    //COLORREF m_clrStaticBorder = RGB(255,255,0);
    //dc.Draw3dRect(0, 0, m_rcGrid.Width(), m_rcGrid.Height(), m_clrStaticBorder, m_clrStaticBorder);

    m_rcGrid.bottom -= (szButton.cy + 2);

    szMonth.cx = m_rcGrid.Width();
    szMonth.cy = m_rcGrid.Height();

    CalcButtonBandRect();

    int nIndex = 0;
    rcMonth = CRect(CPoint(m_rcGrid.left, m_rcGrid.top), szMonth);
    rcMonth.DeflateRect(1, 1);
    // adjust internal month layout
    m_monthPicker->AdjustLayout(rcMonth);
}

void CDuiMonthPicker::OnPaint(CDCHandle dc)
{
    CRect rcClient;
    GetRect(rcClient);

    // draw background
    dc.FillSolidRect(rcClient, m_clrControlBack);

    // draw all month items in the collection
    m_monthPicker->Draw(dc);

    // draw today/none buttons
    DrawButtons(dc);

}

void CDuiMonthPicker::OnLButtonDown(UINT nFlags, CPoint point)
{
    SetDuiCapture();
    SetDuiFocus();

    if (m_monthPicker != NULL)
    {
        m_monthPicker->OnLButtonDown(nFlags, point);
    }

    if (m_btnToday->m_rcButton.PtInRect(point))
        m_btnCaptured = m_btnToday;

    ProcessButtons(point);
}

void CDuiMonthPicker::OnLButtonUp(UINT nFlags, CPoint point)
{
    // kill timer
    if (m_nTimerID != 0)
    {
        KillDuiTimer(m_nTimerID);
        m_nTimerID = 0;
    }

    // logic message processing
    if (m_mouseMode == mouseTrackingHeaderList)
    {
        // reset mouse mode
        m_mouseMode = mouseNothing;

        //if (m_pListControl)
        //{
        //    int nDelta = m_pListControl->GetMonthInterval();
        //    // destroy list control
        //    m_pListControl->DestroyWindow();
        //    delete m_pListControl;
        //    m_pListControl = NULL;
        //    // scroll on selected months count
        //    if (nDelta < 0)
        //        ScrollLeft(-nDelta);
        //    else if (nDelta > 0)
        //        ScrollRight(nDelta);
        //}
    }
    else
    {
        // forward message to appropriate month
        if (m_monthPicker != NULL)
        {
            m_monthPicker->OnLButtonUp(nFlags, point);
        }

        // Update selection
        BOOL bSelecting = m_mouseMode == mouseSelecting;
        BOOL bDeselecting = m_mouseMode == mouseDeselecting;
        if (bSelecting || bDeselecting)
        {
            //int nDay = (m_dtLastClicked - m_dtFirstClicked).GetDays();
            //for (; abs(nDay) >= 0; nDay += nDay > 0 ? -1 : 1)
            //{
            //    COleDateTime dtSelect(m_dtFirstClicked);
            //    dtSelect += nDay;
            //    //if (bDeselecting)
            //    //{
            //    //    m_pSelectedDays->Remove(dtSelect);
            //    //}
            //    //else if (bSelecting && IsSelected(dtSelect))
            //    //{
            //    //    m_pSelectedDays->Add(dtSelect);
            //    //}

            //    if (nDay == 0)
            //        break;
            //}

            // reset mouse mode
            m_mouseMode = mouseNothing;
        }
    }

    //release resources
    ReleaseDuiCapture();

    // process buttons
    m_btnCaptured = NULL;
    ProcessButtons(point);

    // reset mouse mode
    m_mouseMode = mouseNothing;
}

void CDuiMonthPicker::OnSize(UINT nType, CSize)
{
    CRect rcClient;
    GetRect(rcClient);
    AdjustLayout(rcClient);
}

void CDuiMonthPicker::CreateMonth()
{
    CDuiStringT s = m_dtFirstMonth.Format();
    COleDateTime dtNextMonth(m_dtFirstMonth);

    m_monthPicker = new CDuiDatePickerMonth(this, dtNextMonth);

    // by default set show previous days for first month and show following days for last month
    m_monthPicker->SetShowDaysBefore(TRUE);
    m_monthPicker->SetShowDaysAfter(TRUE);

    //  set triangles showing
    BOOL bScrollLeft = TRUE;
    if (m_dtMinRange.GetStatus() == COleDateTime::valid && m_monthPicker->GetMonth() <= m_dtMinRange)
    {
        bScrollLeft = FALSE;
    }

    m_monthPicker->SetShowScrolling(bScrollLeft, m_monthPicker->GetShowRightScroll());

    BOOL bScrollRight = TRUE;
    if (m_dtMaxRange.GetStatus() == COleDateTime::valid && (DATE)m_monthPicker->GetMonth() + 30.0 >= (DATE)m_dtMaxRange)
    {
        bScrollRight = FALSE;
    }

    m_monthPicker->SetShowScrolling(m_monthPicker->GetShowLeftScroll(), bScrollRight);
}

void CDuiMonthPicker::Populate()
{
    // add all month items in the grid to the array
    // and set first month and last month defaults
    if (m_monthPicker != NULL)
    {
        delete m_monthPicker;
    }

    CreateMonth();

    // redraw control image
    if (!m_rcControl.IsRectEmpty())
        AdjustLayout(m_rcControl);

    NotifyInvalidate();
}

CSize CDuiMonthPicker::CalcButtonSize() const
{
    // get button size
    CWindowDC dc(GetDesktopWindow());

    HFONT hFontOld = (HFONT)dc.SelectFont(DuiFontPool::getSingleton().GetFont(DUIF_DEFAULTFONT));

    CSize szButton(0, 0);

    if (m_btnToday != NULL)
    {
        CSize sz;
        CDuiStringT strText = m_btnToday->GetCaption();

        dc.GetTextExtent(strText, strText.GetLength(), &sz);

        szButton.cx = max(szButton.cx, sz.cx + 12);
        szButton.cy = max(szButton.cy, sz.cy + 6);
    }

    dc.SelectFont(hFontOld);

    return szButton;
}

void CDuiMonthPicker::SetButtonRect()
{
    CSize szButton(CalcButtonSize());

    int nGap = 10;

    int nButtonLen = szButton.cx + nGap;
    int nVisibleCount = 1;

    int nLeft = m_rcGrid.CenterPoint().x - (nButtonLen * nVisibleCount - nGap)/2;

    m_btnToday->m_rcButton = CRect(CPoint(nLeft, m_rcGrid.bottom + 1), szButton);
    nLeft += nButtonLen;
}

void CDuiMonthPicker::CalcButtonBandRect()
{
    SetButtonRect();
}

void CDuiMonthPicker::DrawButtons(CDCHandle dc)
{
    if (m_btnToday->m_bVisible)
    {
        dc.FillSolidRect(m_btnToday->m_rcButton, GetSysColor(COLOR_BTNFACE));

        CRect rcButtonX = m_btnToday->m_rcButton;
        rcButtonX.DeflateRect(1, 1, 1, 1);

        if (m_btnToday->m_bPressed)
        {
            dc.Draw3dRect(m_btnToday->m_rcButton, GetSysColor(COLOR_BTNTEXT), GetSysColor(COLOR_BTNFACE));
            dc.Draw3dRect(rcButtonX, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
        }
        else
        {
            dc.Draw3dRect(m_btnToday->m_rcButton, GetSysColor(COLOR_BTNFACE), GetSysColor(COLOR_BTNTEXT));
            dc.Draw3dRect(rcButtonX, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));
        }

        HFONT hFontOld = (HFONT)dc.SelectFont(DuiFontPool::getSingleton().GetFont(DUIF_DEFAULTFONT));
        CDuiStringT strCaption = _T("Today");

        dc.SetTextColor(RGB(0,0,0));
        dc.DrawText(strCaption, strCaption.GetLength(), rcButtonX, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
    }
}

void CDuiMonthPicker::ScrollLeft(int nMonthCount)
{
    int nYear = m_dtFirstMonth.GetYear();
    int nMonth = m_dtFirstMonth.GetMonth();
    if (nYear < 100 || (nYear == 100 && nMonth <= 2))
        return;
    int nYearNew = nYear - nMonthCount / 12;
    int nMonthNew = nMonth - nMonthCount % 12;
    if (nMonthNew < 1)
    {
        nMonthNew += 12;
        nYearNew--;
    }
    DUIASSERT(nMonthNew >= 1 && nMonthNew <= 12);

    if (m_dtMinRange.GetStatus() == COleDateTime::valid)
    {
        if (nYearNew < m_dtMinRange.GetYear())
        {
            nYearNew = m_dtMinRange.GetYear();
            nMonthNew = m_dtMinRange.GetMonth();
        }

        if (m_dtMinRange.GetYear() == nYearNew)
        {
            if (nMonthNew < m_dtMinRange.GetMonth())
                nMonthNew = m_dtMinRange.GetMonth();
        }
    }

    m_dtFirstMonth.SetDate(nYearNew, nMonthNew, 1);

    Populate();
}

void CDuiMonthPicker::ScrollRight(int nMonthCount)
{
    int nYear = m_dtFirstMonth.GetYear();
    int nMonth = m_dtFirstMonth.GetMonth();

    int nYearNew = nYear + nMonthCount / 12;
    int nMonthNew = nMonth + nMonthCount % 12;
    if (nMonthNew > 12)
    {
        nMonthNew -= 12;
        nYearNew++;
    }

    if (m_dtMaxRange.GetStatus() == COleDateTime::valid)
    {
        int nLeftYear = m_dtMaxRange.GetYear();
        int nMaxMonth = m_dtMaxRange.GetMonth();
        int nLeftMonth = nMaxMonth;
        if (nLeftMonth < 1)
        {
            nLeftYear -= (-nLeftMonth) / 12 + 1;
            nLeftMonth = -(((-nLeftMonth) % 12) - 12);
        }

        if (nYearNew > nLeftYear)
        {
            nYearNew = nLeftYear;
            nMonthNew = nLeftMonth;
        }

        if (nLeftYear == nYearNew)
        {
            if (nMonthNew > nLeftMonth)
                nMonthNew = nLeftMonth;
        }
    }

    m_dtFirstMonth.SetDate(nYearNew, nMonthNew, 1);

    ScrollLeft(0); // adjust also scrolling left before calling Populate();
}

void CDuiMonthPicker::Select(const COleDateTime& dtDay)
{
    m_dtFSelBase = dtDay;

    NotifyInvalidate();
}

BOOL CDuiMonthPicker::IsSelected(const COleDateTime& dtDay) const
{
    if (m_dtFSelBase.GetStatus() != COleDateTime::valid)
    {
        return FALSE;
    }

    return DateIsEqual(ResetTime(m_dtFSelBase), ResetTime(dtDay));
}

void CDuiMonthPicker::OnButtonClick(UINT nID)
{
    if (nID == XTP_IDS_DATEPICKER_TODAY)
    {
        COleDateTime dt;
        GetToday(dt);
        EnsureVisible(dt);
        Select(dt);
    }
}

void CDuiMonthPicker::ProcessButtons(CPoint point)
{
    BOOL bHighlight = m_btnToday->m_rcButton.PtInRect(point);
    if (m_btnCaptured == m_btnToday)
    {
        if (bHighlight != m_btnToday->m_bPressed)
        {
            m_btnToday->m_bPressed = bHighlight;
            NotifyInvalidate();
        }
    }
    else if (m_btnToday->m_bPressed)
    {
        m_btnToday->m_bPressed = FALSE;
        if (bHighlight)
            OnButtonClick(m_btnToday->m_nID);
        NotifyInvalidate();
    }

    bHighlight = m_btnToday->m_bHighlight;

    m_btnToday->m_bHighlight = ((m_btnCaptured == m_btnToday) || (!m_btnCaptured && m_btnToday->m_rcButton.PtInRect(point)));
    if (m_btnToday->m_bHighlight != bHighlight)
    {
        NotifyInvalidate();
    }
}

void CDuiMonthPicker::EnsureVisible(const COleDateTime& dtDate)
{
    int nYear = dtDate.GetYear();
    int nMonth = dtDate.GetMonth();

    if (m_monthPicker != NULL)
    {
        COleDateTime dtm = m_monthPicker->GetMonth();
        int iM = dtm.GetMonth();
        int iY = dtm.GetYear();
        if (iM == nMonth &&  iY == nYear)
            return;
    }

    m_dtFirstMonth.SetDate(nYear, nMonth, 1);
    Populate();
}

int GetEqualLeftSymbols(const CDuiStringT& str1, const CDuiStringT& str2)
{
    int nCount = min(str1.GetLength(), str2.GetLength());

    for (int i = 0; i < nCount; i++)
    {
        if (str1.GetAt(i) != str2.GetAt(i))
            return i;
    }
    return nCount;
}

#ifndef LOCALE_SYEARMONTH
#define LOCALE_SYEARMONTH 0x00001006
#endif

void CDuiMonthPicker::InitNames()
{
    // initialize month names
    for (int nMonth = 0; nMonth < 12; nMonth++)
    {
        CDuiStringT strMonth = GetLocaleString(LOCALE_SMONTHNAME1 + nMonth, 255) ;

        m_arMonthNames[nMonth] = strMonth;
    }

    int nEqualLeftSymbols = 255, nDay;

    // initialize day names
    for (nDay = 0; nDay < 7; nDay++)
    {
        CDuiStringT strDayName = GetLocaleString(LOCALE_SABBREVDAYNAME1 + nDay, 255);

        int nOleDayOfWeek = (nDay + 1) % 7;
        m_arDayOfWeekNames[nOleDayOfWeek] = strDayName;

        if (nDay > 0 && nEqualLeftSymbols > 0)
        {
            nEqualLeftSymbols = min(nEqualLeftSymbols, GetEqualLeftSymbols(strDayName, m_arDayOfWeekNames[1]));
        }
    }

    // If first symbols equal, remove them.
    if (nEqualLeftSymbols > 0)
    {
        for (nDay = 0; nDay < 7; nDay++)
            m_arDayOfWeekNames[nDay].Delete(0, nEqualLeftSymbols);
    }

    //m_strYearMonthFormat.Empty();
}

BOOL CDuiMonthPicker::GetCurSel(COleDateTime& refDateTime) const
{
    refDateTime = m_dtFSelBase;
    return TRUE;
}

BOOL CDuiMonthPicker::SetCurSel(const COleDateTime& refDateTime)
{
    m_dtFSelBase = refDateTime;
    NotifyInvalidate();

    return TRUE;
}

void CDuiMonthPicker::SetToday(const COleDateTime& refDateTime)
{
    m_dtToday = refDateTime;
    NotifyInvalidate();
}

BOOL CDuiMonthPicker::ShiftDate(COleDateTime &refDate, int nMonthCount)
{
    int nYearNew = refDate.GetYear();
    int nMonthNew = refDate.GetMonth();
    int nInc = abs(nMonthCount) / nMonthCount;
    for (int nItem = 0; nItem < abs(nMonthCount); nItem++)
    {
        nMonthNew += nInc;
        if (nMonthNew < 1)
        {
            nMonthNew = 12;
            nYearNew--;
        }
        if (nMonthNew > 12)
        {
            nMonthNew = 1;
            nYearNew++;
        }
    }
    return 0 == refDate.SetDate(nYearNew, nMonthNew, 1);
}


}//end of namespace DuiEngine
