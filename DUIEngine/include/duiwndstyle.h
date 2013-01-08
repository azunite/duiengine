//////////////////////////////////////////////////////////////////////////
//   File Name: DuiWndStyle.h
// Description: DuiWindow Styles Definition
//     Creator: Zhang Xiaoxuan
//     Version: 2009.04.28 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "duiskin.h"

namespace DuiEngine
{

class DUI_EXP DuiStyle : public CDuiObject
{
    DUIOBJ_DECLARE_CLASS_NAME(DuiStyle, "style")

    enum
    {
        // Specify by "cursor" attribute
        Cursor_Mask     = 0xF00UL,
        Cursor_Arrow    = 0x000UL,   // cursor = "arrow"
        Cursor_Hand     = 0x100UL,   // cursor = "hand"
    };
public:
    DuiStyle();

    CStringA m_strClassName;

    COLORREF m_crBg;
    COLORREF m_crBgHover;
    COLORREF m_crText;
    COLORREF m_crHoverText;
    COLORREF m_crDisabledText;
    COLORREF m_crPushText;
    UINT m_uAlign;
    int m_nTextAlign;
    HFONT m_ftText;
    HFONT m_ftHover;
    HFONT m_ftPush;
    int m_nMarginX;
    int m_nMarginY;
    int m_nSpacing;
    int m_nLineSpacing;
    BOOL m_bDotted;

    LPCTSTR m_lpCursorName;
    CStringA m_strSkinName,m_strNcSkinName;

    // Get class name
    LPCSTR GetName();

protected:

    // Load style-pool from xml tree
    static void _LoadStylePool(TiXmlElement *pXmlStyleRootElem);

    DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
    DUIWIN_STRING_ATTRIBUTE("name", m_strClassName, TRUE)
    DUIWIN_STRING_ATTRIBUTE("skin", m_strSkinName, TRUE)
    DUIWIN_STRING_ATTRIBUTE("ncskin", m_strNcSkinName, TRUE)
    DUIWIN_HEX_ATTRIBUTE("textmode", m_nTextAlign, TRUE)
    DUIWIN_COLOR_ATTRIBUTE("crbg", m_crBg, TRUE)
    DUIWIN_COLOR_ATTRIBUTE("crbghover", m_crBgHover, TRUE)
    DUIWIN_COLOR_ATTRIBUTE("crtext", m_crText, TRUE)
    DUIWIN_COLOR_ATTRIBUTE("crhover", m_crHoverText, TRUE)
    DUIWIN_COLOR_ATTRIBUTE("crpush", m_crPushText, TRUE)
    DUIWIN_COLOR_ATTRIBUTE("crdisabled", m_crDisabledText, TRUE)
    DUIWIN_FONT_ATTRIBUTE("font", m_ftText, TRUE)
    DUIWIN_FONT_ATTRIBUTE("hoverfont", m_ftHover, TRUE)
    DUIWIN_FONT_ATTRIBUTE("pushfont", m_ftPush, TRUE)
    DUIWIN_INT_ATTRIBUTE("x-margin", m_nMarginX, TRUE)
    DUIWIN_INT_ATTRIBUTE("y-margin", m_nMarginY, TRUE)
    DUIWIN_INT_ATTRIBUTE("margin", m_nMarginX = m_nMarginY, TRUE) // 这样比较bt，不过.....凑合用吧
    DUIWIN_INT_ATTRIBUTE("spacing", m_nSpacing, TRUE)
    DUIWIN_INT_ATTRIBUTE("linespacing", m_nLineSpacing, TRUE)
    DUIWIN_ENUM_ATTRIBUTE("cursor", LPCTSTR, FALSE)
    DUIWIN_ENUM_VALUE("hand", IDC_HAND)
    DUIWIN_ENUM_VALUE("arrow", IDC_ARROW)
    DUIWIN_ENUM_END(m_lpCursorName)
    DUIWIN_INT_ATTRIBUTE("dotted",m_bDotted,FALSE)
    DUIWIN_DECLARE_ATTRIBUTES_END()
};

#include "DuiSingletonMap.h"

class DUI_EXP DuiStylePool :public DuiSingletonMap<DuiStylePool,DuiStyle,CStringA>
{
public:
    // Get style object from pool by class name
    static BOOL GetStyle(LPCSTR lpszName,DuiStyle& style);

    static BOOL Init(UINT uResID);

    static BOOL Init(LPCSTR lpszXml);
protected:
    void _LoadStylePool(TiXmlElement *pXmlStyleRootElem);
};

}//namespace DuiEngine