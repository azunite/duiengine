//////////////////////////////////////////////////////////////////////////
//  Class Name: CDuiListBox
// Description: A DuiWindow Based ListBox Control.
//     Creator: JinHui
//     Version: 2012.12.18 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma  once

#include "duiwndpanel.h"

namespace DuiEngine
{

typedef struct tagLBITEM
{
    CString		strText;
    int			nImage;
    DWORD		dwData;
    LPARAM      lParam;

    tagLBITEM()
    {
        nImage = -1;
        dwData = 0;
        lParam = NULL;
    }

} LBITEM, *LPLBITEM;

class DUI_EXP CDuiListBox :public CDuiScrollView
{
public:

    DUIOBJ_DECLARE_CLASS_NAME(CDuiListBox, "listbox")

    CDuiListBox();

    virtual ~CDuiListBox();

    virtual BOOL Load(TiXmlElement* pTiXmlElem);

    inline int GetCount() const;

    BOOL SetCount(DWORD *pData,int nItems);

    inline int GetCurSel() const;

    BOOL SetCurSel(int nIndex);

    inline int GetTopIndex() const;

    BOOL SetTopIndex(int nIndex);

    inline int GetItemHeight() const
    {
        return m_nItemHei;
    }

    DWORD GetItemData(int nIndex) const;

    BOOL SetItemData(int nIndex, DWORD dwItemData);

    int GetText(int nIndex, LPTSTR lpszBuffer) const;

    int GetText(int nIndex, CString& strText) const;

    int GetTextLen(int nIndex) const;

    int GetItemHeight(int nIndex) const;

    BOOL SetItemHeight(int nIndex, int cyItemHeight);

    void DeleteAll();

    BOOL DeleteString(int nIndex);

    int AddString(LPCTSTR lpszItem, int nImage = -1, DWORD dwData = 0, LPARAM lParam = NULL);

    int InsertString(int nIndex, LPCTSTR lpszItem, int nImage = -1, DWORD dwData = 0, LPARAM lParam = NULL);

    void EnsureVisible(int nIndex);

    void RedrawItem(int iItem);

    //自动修改pt的位置为相对当前项的偏移量
    int HitTest(CPoint &pt);

protected:

    virtual BOOL LoadChildren(TiXmlElement* pTiXmlChildElem);
    void LoadItemAttribute(TiXmlElement *pTiXmlItem, LPLBITEM pItem);

    int InsertItem(int nIndex, LPLBITEM pItem);

    virtual int GetScrollLineSize(BOOL bVertical);

    void DrawItem(CDCHandle &dc, CRect &rc, int iItem);

    void NotifySelChange(int nOldSel,int nNewSel,UINT uMsg);

    UINT OnGetDuiCode();

protected:

    void OnSize(UINT nType,CSize size);

    void OnPaint(CDCHandle dc);

    void OnLButtonDown(UINT nFlags,CPoint pt);

    void OnLButtonDbClick(UINT nFlags,CPoint pt);

    void OnLButtonUp(UINT nFlags,CPoint pt);

    void OnMouseMove(UINT nFlags,CPoint pt);

    void OnMouseLeave();

    void OnKeyDown( TCHAR nChar, UINT nRepCnt, UINT nFlags );

    void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

    void OnDestroy();

    LRESULT OnNcCalcSize(BOOL bCalcValidRects, LPARAM lParam);

protected:

    CDuiArray<LPLBITEM>	m_arrItems;

    int		m_nItemHei;
    int		m_iSelItem;
    int		m_iHoverItem;
    int		m_iScrollSpeed;
    BOOL	m_bHotTrack;

    CPoint m_ptIcon;
    CPoint m_ptText;

    COLORREF m_crItemBg, m_crItemBg2, m_crItemSelBg;
    COLORREF m_crText, m_crSelText;
    CDuiSkinBase *m_pItemSkin, *m_pIconSkin;

public:

    DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
    DUIWIN_INT_ATTRIBUTE("scrollspeed", m_iScrollSpeed, FALSE)
    DUIWIN_INT_ATTRIBUTE("itemheight", m_nItemHei, FALSE)
    DUIWIN_SKIN_ATTRIBUTE("itemskin", m_pItemSkin, TRUE)
    DUIWIN_SKIN_ATTRIBUTE("iconskin", m_pIconSkin, TRUE)
    DUIWIN_COLOR_ATTRIBUTE("critembg",m_crItemBg,FALSE)
    DUIWIN_COLOR_ATTRIBUTE("critembg2", m_crItemBg2, FALSE)
    DUIWIN_COLOR_ATTRIBUTE("critemselbg",m_crItemSelBg,FALSE)
    DUIWIN_COLOR_ATTRIBUTE("crtext",m_crText,FALSE)
    DUIWIN_COLOR_ATTRIBUTE("crseltext",m_crSelText,FALSE)
    DUIWIN_INT_ATTRIBUTE("icon-x", m_ptIcon.x, FALSE)
    DUIWIN_INT_ATTRIBUTE("icon-y", m_ptIcon.y, FALSE)
    DUIWIN_INT_ATTRIBUTE("text-x", m_ptText.x, FALSE)
    DUIWIN_INT_ATTRIBUTE("text-y", m_ptText.y, FALSE)
    DUIWIN_INT_ATTRIBUTE("hottrack",m_bHotTrack,FALSE)
    DUIWIN_DECLARE_ATTRIBUTES_END()

    DUIWIN_BEGIN_MSG_MAP()
    MSG_WM_DESTROY(OnDestroy)
    MSG_WM_SIZE(OnSize)
    MSG_WM_PAINT(OnPaint)
    MSG_WM_LBUTTONDOWN(OnLButtonDown)
    MSG_WM_LBUTTONDBLCLK(OnLButtonDbClick)
    MSG_WM_LBUTTONUP(OnLButtonUp)
    MSG_WM_MOUSEMOVE(OnMouseMove)
    MSG_WM_MOUSELEAVE(OnMouseLeave)
    MSG_WM_KEYDOWN(OnKeyDown)
    MSG_WM_CHAR(OnChar)
    DUIWIN_END_MSG_MAP()
};

}//namespace DuiEngine