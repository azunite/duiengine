//////////////////////////////////////////////////////////////////////////
//  Class Name: CDuiListBoxEx
// Description: A DuiWindow Based ListBox Control. Can contain control as an item
//     Creator: Huang Jianxiong
//     Version: 2011.8.27 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma  once

#include "duiitempanel.h"

namespace DuiEngine
{

class DUI_EXP CDuiListBoxEx :public CDuiScrollView
    ,public CDuiItemContainer
{
public:

    DUIOBJ_DECLARE_CLASS_NAME(CDuiListBoxEx, "listboxex")

    CDuiListBoxEx();

    virtual ~CDuiListBoxEx();


    void DeleteAllItems(BOOL bUpdate=TRUE);

    void DeleteItem(int iItem);
    int InsertItem(int iItem,CDuiItemPanel *pItemObj,DWORD dwData=0);

    int InsertItem(int iItem,LPCWSTR pszXml,DWORD dwData=0);


    CDuiPanel * InsertPanelItem(int iItem,LPCWSTR pszXml,DWORD dwData=0);

    void SetCurSel(int iItem);

    void EnsureVisible(int iItem);

    int GetCurSel();

    int GetItemObjIndex(CDuiPanel *pItemObj);

    CDuiPanel * GetDuiItem(int iItem);
    CDuiPanel * GetDuiItem(CDuiPanel *pItem);

    DWORD GetItemData(int iItem);


    BOOL SetItemCount(DWORD *pData,int nItems);

    int GetItemCount() ;

    int GetItemHeight()
    {
        return m_nItemHei;
    }

    void RedrawItem(int iItem);

    //自动修改pt的位置为相对当前项的偏移量
    int HitTest(CPoint &pt);

    virtual BOOL Load(TiXmlElement* pTiXmlElem);
protected:
    virtual void OnItemSetCapture(CDuiItemPanel *pItem,BOOL bCapture);
    virtual BOOL OnItemGetRect(CDuiItemPanel *pItem,CRect &rcItem);

    virtual int GetScrollLineSize(BOOL bVertical);

    void OnPaint(CDCHandle dc);

    LRESULT OnNcCalcSize(BOOL bCalcValidRects, LPARAM lParam);

    void DrawItem(CDCHandle & dc, CRect & rc, int iItem);

    virtual BOOL LoadChildren(TiXmlElement* pTiXmlChildElem);
    // Get tooltip Info
    virtual BOOL OnUpdateToolTip(HDUIWND hCurTipHost,HDUIWND &hNewTipHost,CRect &rcTip,CDuiStringT &strTip);

    void NotifySelChange(int nOldSel,int nNewSel,UINT uMsg);

    void OnLButtonDown(UINT nFlags,CPoint pt);

    void OnLButtonUp(UINT nFlags,CPoint pt);

    void OnLButtonDbClick(UINT nFlags,CPoint pt);

    void OnMouseMove(UINT nFlags,CPoint pt);

    void OnMouseLeave();

    void OnKeyDown( TCHAR nChar, UINT nRepCnt, UINT nFlags );

    void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

    UINT OnGetDuiCode();

    virtual BOOL OnDuiSetCursor(const CPoint &pt);

    void OnDestroy();
protected:
    CDuiArray<CDuiItemPanel *> m_arrItems;

    int		m_nItemHei;
    int		m_iSelItem;
    int		m_iHoverItem;
    int		m_iScrollSpeed;
    BOOL	m_bHotTrack;

    TiXmlElement *m_pItemTemplate;	//模板项
    CDuiItemPanel	*	m_pCapturedFrame;
    COLORREF m_crItemBg, m_crItemBg2, m_crItemSelBg;
    CDuiSkinBase * m_pItemSkin;
public:
    DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
    DUIWIN_INT_ATTRIBUTE("scrollspeed", m_iScrollSpeed, FALSE)
    DUIWIN_INT_ATTRIBUTE("itemheight", m_nItemHei, FALSE)
    DUIWIN_SKIN_ATTRIBUTE("itemskin", m_pItemSkin, TRUE)
    DUIWIN_COLOR_ATTRIBUTE("critembg",m_crItemBg,FALSE)
    DUIWIN_COLOR_ATTRIBUTE("critembg2", m_crItemBg2, FALSE)
    DUIWIN_COLOR_ATTRIBUTE("critemselbg",m_crItemSelBg,FALSE)
    DUIWIN_INT_ATTRIBUTE("hottrack",m_bHotTrack,FALSE)
    DUIWIN_DECLARE_ATTRIBUTES_END()

    DUIWIN_BEGIN_MSG_MAP()
    MSG_WM_DESTROY(OnDestroy)
    MSG_WM_PAINT(OnPaint)
    MSG_WM_NCCALCSIZE(OnNcCalcSize)
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