#pragma once
#include "duiwndpanel.h"

namespace DuiEngine
{

enum SPLITMODE {SM_COL=0,SM_ROW};


class DUI_EXP CDuiSplitPane : public CDuiPanel
{
    friend class CDuiSplitWnd;
    DUIOBJ_DECLARE_CLASS_NAME(CDuiSplitPane, "splitpane")
public:
    CDuiSplitPane();
    virtual ~CDuiSplitPane() {}

protected:
    DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
    DUIWIN_INT_ATTRIBUTE("idealsize", m_nSizeIdeal, TRUE)
    DUIWIN_INT_ATTRIBUTE("minsize", m_nSizeMin, TRUE)
    DUIWIN_INT_ATTRIBUTE("priority", m_nPriority, TRUE)
    DUIWIN_DECLARE_ATTRIBUTES_END()
protected:
    int m_nSizeIdeal;
    int m_nSizeMin;
    int m_nPriority;
};

class DUI_EXP CDuiSplitWnd :
    public CDuiWindow
{
    DUIOBJ_DECLARE_CLASS_NAME(CDuiSplitWnd, "splitwnd")

    struct PANEORDER
    {
        int idx;
        CDuiSplitPane *pPane;
    };
public:
    CDuiSplitWnd(void);
    virtual ~CDuiSplitWnd(void);

    BOOL SetPaneInfo(int iPane,int nIdealSize,int nMinSize,int nPriority);

    BOOL GetPaneInfo(int iPane,int *pnIdealSize,int *pnMinSize,int *pnPriority);

    BOOL ShowPanel(int iPane);

    BOOL HidePanel(int iPane);

protected:
	virtual void UpdateChildrenPosition(){}//empty

    int GetVisiblePanelCount();

    int GetNextVisiblePanel(int iPanel);

    virtual BOOL LoadChildren(TiXmlElement* pTiXmlChildElem);

    virtual BOOL OnDuiSetCursor(const CPoint &pt);

    void OnDestroy();

    void OnPaint(CDCHandle dc);

    void OnWindowPosChanged(LPRECT lpWndPos);

    void OnLButtonDown(UINT nFlags,CPoint pt);

    void OnLButtonUp(UINT nFlags,CPoint pt);

    void OnMouseMove(UINT nFlags,CPoint pt);

    static int FunComp(const void * p1,const void * p2);

    void Relayout();

    DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
    DUIWIN_INT_ATTRIBUTE("sepsize", m_nSepSize, TRUE)
    DUIWIN_INT_ATTRIBUTE("adjustable", m_bAdjustable, TRUE)
    DUIWIN_INT_ATTRIBUTE("colmode", m_bColMode, TRUE)
    DUIWIN_SKIN_ATTRIBUTE("skinsep",m_pSkinSep,TRUE)
    DUIWIN_DECLARE_ATTRIBUTES_END()

    DUIWIN_BEGIN_MSG_MAP()
    MSG_WM_PAINT(OnPaint)
    MSG_WM_DESTROY(OnDestroy)
    MSG_WM_DUIWINPOSCHANGED(OnWindowPosChanged)
    MSG_WM_LBUTTONDOWN(OnLButtonDown)
    MSG_WM_LBUTTONUP(OnLButtonUp)
    MSG_WM_MOUSEMOVE(OnMouseMove)
    DUIWIN_END_MSG_MAP()

protected:
    CDuiArray<CDuiSplitPane *> m_arrPane;
    CDuiSkinBase *m_pSkinSep;
    int m_nSepSize;
    BOOL m_bAdjustable;
    BOOL m_bColMode;

    int m_iDragBeam;
    CPoint m_ptClick;
};

class DUI_EXP CDuiSplitWnd_Col : public CDuiSplitWnd
{
    DUIOBJ_DECLARE_CLASS_NAME(CDuiSplitWnd_Col, "splitcol")
public:
    CDuiSplitWnd_Col()
    {
        m_bColMode=TRUE;
    }
};

class DUI_EXP CDuiSplitWnd_Row : public CDuiSplitWnd
{
    DUIOBJ_DECLARE_CLASS_NAME(CDuiSplitWnd_Row, "splitrow")
public:
    CDuiSplitWnd_Row()
    {
        m_bColMode=FALSE;
    }
};

}//namespace DuiEngine