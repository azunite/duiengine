//////////////////////////////////////////////////////////////////////////
//  Class Name: DuiTheme
// Description: Windows Theme(XP later)
//     Creator: ZhangXiaoxuan
//     Version: 2009.5.12 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma once

#include <Uxtheme.h>
#include <tmschema.h>

namespace DuiEngine
{

class DUI_EXP DuiWinThemeFunc
{
    typedef HTHEME (WINAPI *FnOpenThemeData)(HWND hwnd, LPCWSTR pszClassList);
    typedef HRESULT (WINAPI *FnCloseThemeData)(HTHEME hTheme);
    typedef HRESULT (WINAPI *FnDrawThemeBackground)(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pRect, OPTIONAL const RECT *pClipRect);
    typedef HRESULT (WINAPI *FnSetWindowTheme)(HWND hwnd, LPCWSTR pszSubAppName, LPCWSTR pszSubIdList);

public:
    DuiWinThemeFunc();

    static BOOL IsValid();

    static HTHEME OpenThemeData(HWND hwnd, LPCWSTR pszClassList);

    static HRESULT CloseThemeData(HTHEME hTheme);

    static HRESULT DrawThemeBackground(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pRect, OPTIONAL const RECT *pClipRect);

    static HRESULT SetWindowTheme(HWND hwnd, LPCWSTR pszSubAppName, LPCWSTR pszSubIdList);

    enum
    {
        DuiThemeNameButton = 0,
        DuiThemeNameEnd,
    };

    static LPCWSTR ThemeName(int nID);

private:

    BOOL m_bThemeValid;

    FnOpenThemeData         m_pfnOpenThemeData;
    FnCloseThemeData        m_pfnCloseThemeData;
    FnDrawThemeBackground   m_pfnDrawThemeBackground;
    FnSetWindowTheme        m_pfnSetWindowTheme;

    static DuiWinThemeFunc* ms_pInstance;

    static DuiWinThemeFunc* _Instance();

};



template<int t_nThemeId, int t_partid>
class DUI_EXP CDuiWinTheme
{
public:
    CDuiWinTheme(HWND hWnd = NULL)
        : m_hTheme(NULL)
    {
        if (hWnd)
            OpenTheme(hWnd);
    }

    ~CDuiWinTheme()
    {
        DuiWinThemeFunc::CloseThemeData(m_hTheme);
    }

    BOOL IsValid()
    {
        return (NULL != m_hTheme);
    }

    BOOL OpenTheme(HWND hWnd)
    {
        if (m_hTheme)
            return FALSE;

        m_hTheme = DuiWinThemeFunc::OpenThemeData(NULL, DuiWinThemeFunc::ThemeName(t_nThemeId));

        if (m_hTheme)
            return TRUE;

        return FALSE;
    }

    void DrawBackground(HDC hdc, int iStateId, const RECT *pRect)
    {
        DuiWinThemeFunc::DrawThemeBackground(m_hTheme, hdc, t_partid, iStateId, pRect, NULL);
    }

protected:

    HTHEME m_hTheme;
};

typedef CDuiWinTheme<DuiWinThemeFunc::DuiThemeNameButton, BP_CHECKBOX> CDuiCheckBoxTheme;
typedef CDuiWinTheme<DuiWinThemeFunc::DuiThemeNameButton, BP_RADIOBUTTON> CDuiRadioBoxTheme;

}//namespace DuiEngine