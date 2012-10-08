#pragma once

#include "duiwnd.h"

namespace DuiEngine{

//////////////////////////////////////////////////////////////////////////
// Rich Text Control
//
class DUI_EXP CDuiRichText : public CDuiWindow
{
    DUIOBJ_DECLARE_CLASS_NAME(CDuiRichText, "richtext")

public:
    CDuiRichText();

    virtual ~CDuiRichText();

    virtual BOOL Load(TiXmlElement* pTiXmlElem);

    BOOL LoadChildren(TiXmlElement* pTiXmlElem);

    virtual BOOL OnDuiSetCursor(const CPoint &pt);
protected:

    void OnWindowPosChanged(LPDUIWNDPOS lpWndPos);

    void OnPaint(CDCHandle dc);

    void OnMouseMove(UINT nFlags, CPoint point);

    void OnMouseLeave();

    void OnLButtonDown(UINT nFlags, CPoint point);
    void OnLButtonUp(UINT nFlags, CPoint point);

    void _AddLink(CDCHandle &dc, TiXmlElement *pElemChild, POINT &pt);

    void _DrawElement(CDCHandle &dc, TiXmlElement *pElemChild, WORD wFont, POINT &pt);

    void _DrawLinks(CDCHandle &dc);

    void _DrawNode(CDCHandle &dc, TiXmlNode *pNodeChild, WORD wFont, POINT &pt, BOOL bOnlyCalcPoint = FALSE);

protected:

    TiXmlElement m_XmlElemChildren;
    DWORD m_dwFont;
    DuiStyle m_styleLink;
    BOOL m_bLinkLoaded;
    POSITION m_posHover;
    POSITION m_posPushDown;

    class _LinkInfo 
    {
    public:
        CString strText;
        UINT    uCmdID;
        CRect   rcLink;
    };

    CAtlList<_LinkInfo> m_lstLink;

    DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
        DUIWIN_HEX_ATTRIBUTE("defaultfont", m_dwFont, FALSE)
        DUIWIN_STYLE_ATTRIBUTE("linkclass", m_styleLink, FALSE)
    DUIWIN_DECLARE_ATTRIBUTES_END()

    DUIWIN_BEGIN_MSG_MAP()
        MSG_WM_PAINT(OnPaint)
        MSG_WM_DUIWINPOSCHANGED(OnWindowPosChanged)
        MSG_WM_MOUSEMOVE(OnMouseMove)
        MSG_WM_MOUSELEAVE(OnMouseLeave)
        MSG_WM_LBUTTONDOWN(OnLButtonDown)
        MSG_WM_LBUTTONUP(OnLButtonUp)
    DUIWIN_END_MSG_MAP()
};

}//namespace DuiEngine