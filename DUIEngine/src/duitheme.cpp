#include "duistd.h"
#include "duitheme.h"

namespace DuiEngine
{

DuiWinThemeFunc* DuiWinThemeFunc::ms_pInstance = NULL;

DuiWinThemeFunc::DuiWinThemeFunc()
    : m_bThemeValid(FALSE)
    , m_pfnOpenThemeData(NULL)
    , m_pfnCloseThemeData(NULL)
    , m_pfnDrawThemeBackground(NULL)
    , m_pfnSetWindowTheme(NULL)
{
    HMODULE hModTheme = ::GetModuleHandle(_T("uxtheme.dll"));

    if (!hModTheme)
        return;

    m_bThemeValid = TRUE;
    m_pfnOpenThemeData          = (FnOpenThemeData)::GetProcAddress(hModTheme, "OpenThemeData");
    m_pfnCloseThemeData         = (FnCloseThemeData)::GetProcAddress(hModTheme, "CloseThemeData");
    m_pfnDrawThemeBackground    = (FnDrawThemeBackground)::GetProcAddress(hModTheme, "DrawThemeBackground");
    m_pfnSetWindowTheme         = (FnSetWindowTheme)::GetProcAddress(hModTheme, "SetWindowTheme");
}

BOOL DuiWinThemeFunc::IsValid()
{
    return _Instance()->m_bThemeValid;
}

HTHEME DuiWinThemeFunc::OpenThemeData(HWND hwnd, LPCWSTR pszClassList)
{
    if (_Instance()->m_pfnOpenThemeData)
    {
        return _Instance()->m_pfnOpenThemeData(hwnd, pszClassList);
    }
    else
        return NULL;
}

HRESULT DuiWinThemeFunc::CloseThemeData(HTHEME hTheme)
{
    if (_Instance()->m_pfnCloseThemeData)
    {
        return _Instance()->m_pfnCloseThemeData(hTheme);
    }
    else
        return E_NOTIMPL;
}

HRESULT DuiWinThemeFunc::DrawThemeBackground(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pRect, OPTIONAL const RECT *pClipRect)
{
    if (_Instance()->m_pfnDrawThemeBackground)
    {
        return _Instance()->m_pfnDrawThemeBackground(hTheme, hdc, iPartId, iStateId, pRect, pClipRect);
    }
    else
        return E_NOTIMPL;
}

HRESULT DuiWinThemeFunc::SetWindowTheme(HWND hwnd, LPCWSTR pszSubAppName, LPCWSTR pszSubIdList)
{
    if (_Instance()->m_pfnSetWindowTheme)
    {
        return _Instance()->m_pfnSetWindowTheme(hwnd, pszSubAppName, pszSubIdList);
    }
    else
        return E_NOTIMPL;
}

LPCWSTR DuiWinThemeFunc::ThemeName(int nID)
{
    static const LPCWSTR Names[] =
    {
        L"BUTTON",
        L"",
    };

    static int NamesCount = sizeof(Names) / sizeof(LPCWSTR) - 1;

    if (nID >= 0 && nID < NamesCount)
        return Names[DuiThemeNameButton];
    else
        return NULL;
}

DuiWinThemeFunc* DuiWinThemeFunc::_Instance()
{
    if (!ms_pInstance)
        ms_pInstance = new DuiWinThemeFunc;
    return ms_pInstance;
}


}//namespace DuiEngine