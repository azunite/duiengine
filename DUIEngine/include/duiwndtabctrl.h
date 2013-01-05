//////////////////////////////////////////////////////////////////////////
//   File Name: bkwndtabctrl.h
// Description: Tab Control
//     Creator: Huang Jianxiong
//     Version: 2011.12.2 - 1.1 - Create
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "duiwndnotify.h"
#include "duiwndcmnctrl.h"

namespace DuiEngine{

class DUI_EXP CDuiTab : public CDuiPanel
{
    DUIOBJ_DECLARE_CLASS_NAME(CDuiTab, "tab")

public:
	CDuiTab()
    {
		m_bVisible = FALSE;
		m_dwState = DuiWndState_Invisible;
		m_uPositionType = SizeX_FitParent|SizeY_FitParent;
    }

	~CDuiTab()
	{
	}

    LPCTSTR GetTitle()
    {
        return m_strTitle;
    }

    void SetTitle(LPCTSTR lpszTitle)
    {
        m_strTitle = lpszTitle;
    }

protected:

    CString m_strTitle;
    DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
        DUIWIN_TSTRING_ATTRIBUTE("title", m_strTitle, FALSE)
    DUIWIN_DECLARE_ATTRIBUTES_END()
};

typedef enum tagSLIDEDIR
{
	SD_LEFTRIGHT=0,
	SD_RIGHTLEFT,
	SD_TOPBOTTOM,
	SD_BOTTOMTOP,
}SLIDEDIR;

class DUI_EXP CDuiTabSlide : public CDuiWindow
{
	DUIOBJ_DECLARE_CLASS_NAME(CDuiTabSlide, "tabslide")

public:
	CDuiTabSlide():m_hMemDC(NULL),m_hBmp(NULL)
	{
	}
	
	void SetPage1(CDuiWindow *pPage1);

	void SetPage2(CDuiWindow *pPage2);

	void Slide(SLIDEDIR sd,int nSteps=20);

	void OnPaint(CDCHandle dc)
	{
	}

protected:
	HDC m_hMemDC;
	HBITMAP m_hBmp;
	DUIWIN_BEGIN_MSG_MAP()
		MSG_WM_PAINT(OnPaint)
	DUIWIN_END_MSG_MAP()
};

class DUI_EXP CDuiTabCtrl : public CDuiPanel
{
    DUIOBJ_DECLARE_CLASS_NAME(CDuiTabCtrl, "tabctrl")

protected:
    int m_nHoverTabItem;
    int m_nCurrentPage;
    int m_nTabSpacing;
    int m_nTabWidth;
    int m_nTabHeight;
    int m_nTabPos;
    int m_nFramePos;
    CDuiSkinBase *m_pSkinTab;
    CDuiSkinBase *m_pSkinIcon;
    CDuiSkinBase *m_pSkinSplitter;
    CDuiSkinBase *m_pSkinFrame;
    CPoint m_ptIcon;
    CPoint m_ptText;
    int m_nTabAlign;

    STL_NS::vector<CDuiTab*> m_lstPages;

    CDuiTabSlide	m_tabSlide;

    enum {
        AlignTop,
        AlignLeft,
    };

	int	m_nAnimateSteps;
public:

    CDuiTabCtrl();

    int GetCurSel()
    {
        return m_nCurrentPage;
    }

    BOOL SetCurSel(int nIndex);

    BOOL SetItemTitle(int nIndex, LPCTSTR lpszTitle);

    BOOL LoadChildren(TiXmlElement* pTiXmlChildElem);

	BOOL InsertItem(LPCWSTR lpContent,int iInsert=-1);

	int InsertItem(TiXmlElement *pXmlElement,int iInsert=-1,BOOL bLoading=FALSE);

	int GetItemCount()
	{ 
		return m_lstPages.size();
	}

    CDuiTab* GetItem(int nIndex);


	BOOL RemoveItem(int nIndex);

	void RemoveAllItems(void);

protected:
	virtual BOOL GetItemRect(int nIndex, CRect &rcItem);
	virtual void DrawItem(CDCHandle dc,const CRect &rcItem,int iItem,DWORD dwState);

protected:
	void OnPaint(CDCHandle dc);

	void OnCalcChildPos(CDuiWindow *pDuiWndChild);

	void OnLButtonDown(UINT nFlags, CPoint point);

	void OnMouseMove(UINT nFlags, CPoint point);

	void OnMouseLeave()
	{
		OnMouseMove(0,CPoint(-1,-1));
	}

	void OnDestroy();

	LRESULT OnCreate(LPVOID);

    DUIWIN_BEGIN_MSG_MAP()
		MSG_WM_CREATE(OnCreate)
        MSG_WM_PAINT(OnPaint)
		MSG_WM_DESTROY(OnDestroy)
        MSG_WM_LBUTTONDOWN(OnLButtonDown)
        MSG_WM_MOUSEMOVE(OnMouseMove)
        MSG_WM_MOUSELEAVE(OnMouseLeave)
		MSG_WM_CALCWNDPOS(OnCalcChildPos)
    DUIWIN_END_MSG_MAP()

    DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
        DUIWIN_INT_ATTRIBUTE("cursel", m_nCurrentPage, FALSE)
        DUIWIN_INT_ATTRIBUTE("tabwidth", m_nTabWidth, FALSE)
        DUIWIN_INT_ATTRIBUTE("tabheight", m_nTabHeight, FALSE)
        DUIWIN_INT_ATTRIBUTE("tabpos", m_nTabPos, FALSE)
        DUIWIN_INT_ATTRIBUTE("framepos", m_nFramePos, FALSE)
        DUIWIN_INT_ATTRIBUTE("tabspacing", m_nTabSpacing, FALSE)
        DUIWIN_SKIN_ATTRIBUTE("tabskin", m_pSkinTab, FALSE)
        DUIWIN_SKIN_ATTRIBUTE("iconskin", m_pSkinIcon, FALSE)
        DUIWIN_SKIN_ATTRIBUTE("splitterskin", m_pSkinSplitter, FALSE)
        DUIWIN_SKIN_ATTRIBUTE("frameskin", m_pSkinFrame, FALSE)
        DUIWIN_INT_ATTRIBUTE("icon-x", m_ptIcon.x, FALSE)
        DUIWIN_INT_ATTRIBUTE("icon-y", m_ptIcon.y, FALSE)
        DUIWIN_INT_ATTRIBUTE("text-x", m_ptText.x, FALSE)
        DUIWIN_INT_ATTRIBUTE("text-y", m_ptText.y, FALSE)
        DUIWIN_ENUM_ATTRIBUTE("tabalign", int, TRUE)
            DUIWIN_ENUM_VALUE("top", AlignTop)
            DUIWIN_ENUM_VALUE("left", AlignLeft)
        DUIWIN_ENUM_END(m_nTabAlign)
		DUIWIN_INT_ATTRIBUTE("animatesteps",m_nAnimateSteps,FALSE)
    DUIWIN_DECLARE_ATTRIBUTES_END()
};

}//namespace DuiEngine