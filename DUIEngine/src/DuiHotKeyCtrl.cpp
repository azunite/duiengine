#include "duistd.h"
#include "DuiHotKeyCtrl.h"
#include <CommCtrl.h>

namespace DuiEngine
{

#define EDIT_INSET 2

CDuiHotKeyCtrl::CDuiHotKeyCtrl(void)
{
    m_wVK=0;
    m_wModifier=0;
    m_hTxtFont=0;
    m_wInvalidModifier=HOTKEYF_CONTROL;
    m_wInvalidComb=HKCOMB_NONE;
    m_bInSetting=FALSE;
}

CDuiHotKeyCtrl::~CDuiHotKeyCtrl(void)
{
    if(m_hTxtFont) DeleteObject(m_hTxtFont);
}



int CDuiHotKeyCtrl::OnCreate( LPVOID )
{
    int nRet=__super::OnCreate(NULL);
    if(nRet!=0) return nRet;
    CDCHandle dc=GetDuiDC(NULL,OLEDC_NODRAW);
    DUIASSERT(dc);
    DuiDCPaint duidc;
    BeforePaint(dc,duidc);

    LOGFONT lf;
    HFONT hFont=(HFONT)GetCurrentObject(dc,OBJ_FONT);
    ::GetObject(hFont, sizeof(LOGFONT), &lf);
    m_hTxtFont=CreateFontIndirect(&lf);

    AfterPaint(dc,duidc);
    ReleaseDuiDC(dc);
    return 0;
}

void CDuiHotKeyCtrl::OnLButtonDown( UINT nFlags,CPoint pt )
{
    __super::OnLButtonDown(nFlags,pt);
    GetContainer()->OnSetDuiFocus(m_hDuiWnd);
}

void CDuiHotKeyCtrl::OnPaint( CDCHandle dc )
{
    DuiDCPaint duiDC;
    BeforePaint(dc,duiDC);
    CRect rcClient;
    GetClient(&rcClient);
    rcClient.OffsetRect(EDIT_INSET,0);
    ALPHAINFO alphaBack;
    if(GetContainer()->IsTranslucent())
        CGdiAlpha::AlphaBackup(dc,&rcClient,alphaBack);
    CDuiStringT str=FormatHotkey();
    DrawText(dc,str,str.GetLength(),&rcClient,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
    if(GetContainer()->IsTranslucent())
        CGdiAlpha::AlphaRestore(dc,alphaBack);
    AfterPaint(dc,duiDC);
}

void CDuiHotKeyCtrl::UpdateCaret()
{
    CDuiStringT str=FormatHotkey();
    CDCHandle dc=GetDC(GetContainer()->GetHostHwnd());
    HFONT hOldFond=dc.SelectFont(m_hTxtFont);
    SIZE szTxt;
    GetTextExtentPoint(dc,str,str.GetLength(),&szTxt);
    dc.SelectFont(hOldFond);
    ReleaseDC(GetContainer()->GetHostHwnd(),dc);

    CRect rcClient;
    GetClient(&rcClient);
    GetContainer()->DuiSetCaretPos(rcClient.left+EDIT_INSET+szTxt.cx,rcClient.top+(rcClient.Height()-szTxt.cy)/2);
}

void CDuiHotKeyCtrl::OnSetDuiFocus()
{
    CDCHandle dc=GetDC(GetContainer()->GetHostHwnd());
    HFONT hOldFond=dc.SelectFont(m_hTxtFont);
    SIZE szTxt;
    dc.GetTextExtent(_T("A"),1,&szTxt);
    GetContainer()->DuiCreateCaret(NULL,1,szTxt.cy);
    dc.SelectFont(hOldFond);
    ReleaseDC(GetContainer()->GetHostHwnd(),dc);

    UpdateCaret();
    GetContainer()->DuiShowCaret(TRUE);
}

void CDuiHotKeyCtrl::OnKillDuiFocus()
{
    GetContainer()->DuiShowCaret(FALSE);

}

CDuiStringT CDuiHotKeyCtrl::GetKeyName(WORD vk)
{
    CDuiStringT str;
    switch(vk)
    {
    case VK_ESCAPE:
        str=_T("ESC");
        break;
    case VK_RETURN:
        str=_T("Enter");
        break;
    case VK_UP:
        str=_T("Up");
        break;
    case VK_DOWN:
        str=_T("Down");
        break;
    case VK_LEFT:
        str=_T("Left");
        break;
    case VK_RIGHT:
        str=_T("Right");
        break;
    case VK_HOME:
        str=_T("Home");
        break;
    case VK_END:
        str=_T("End");
        break;
    case VK_PRIOR:
        str=_T("PageUp");
        break;
    case VK_NEXT:
        str=_T("PageDown");
        break;
    case VK_INSERT:
        str=_T("Insert");
        break;
    default:
        if((vk>='0' && m_wVK<='9')||(vk>='A' && vk<='Z'))
            str=(TCHAR)vk;
        else if(vk>=VK_F1 && vk<=VK_F9)
            str=CDuiStringT(_T('F'))+TCHAR(m_wVK-VK_F1+'1');
        else if(vk==VK_F10)
            str+=_T("F10");
        else if(vk==VK_F11)
            str+=_T("F11");
        else if(vk==VK_F12)
            str+=_T("F12");
        else
        {
            char c=MapVirtualKeyA(vk,2);
            switch(c)
            {
            case '-':
            case '=':
            case '[':
            case ']':
            case '\\':
            case ';':
            case '\'':
            case ',':
            case '.':
            case '/':
            case '`':
                str+=TCHAR(c);
                break;
            }
        }
        break;
    }
    return str;
}

CDuiStringT CDuiHotKeyCtrl::FormatHotkey()
{
    if(m_wModifier==0 && m_wVK==0) return _T("нч");
    CDuiStringT str;
    if(m_wModifier == HOTKEYF_ALT) str=_T("Alt+");
    if(m_wModifier == HOTKEYF_CONTROL) str=_T("Ctrl+");
    if(m_wModifier == HOTKEYF_SHIFT) str=_T("Shift+");
    if(m_wModifier == (HOTKEYF_ALT|HOTKEYF_SHIFT)) str=_T("Shift+Alt+");
    if(m_wModifier == (HOTKEYF_ALT|HOTKEYF_CONTROL)) str=_T("Ctrl+Alt+");
    if(m_wModifier == (HOTKEYF_CONTROL|HOTKEYF_SHIFT)) str=_T("Ctrl+Shift+");
    if(m_wModifier == (HOTKEYF_ALT|HOTKEYF_CONTROL|HOTKEYF_SHIFT)) str=_T("Ctrl+Shift+Alt+");
    str+=GetKeyName(m_wVK);
    return str;
}

void CDuiHotKeyCtrl::UpdateModifier()
{
    BOOL bAlt=GetKeyState(VK_MENU)&0x8000;
    BOOL bCtrl=GetKeyState(VK_CONTROL)&0x8000;
    BOOL bShift=GetKeyState(VK_SHIFT)&0x8000;

    WORD wCombKey=0;
    if(!bAlt && !bCtrl && !bShift) wCombKey=HKCOMB_NONE,m_wModifier=0;
    else if(bAlt && !bCtrl && !bShift) wCombKey=HKCOMB_A,m_wModifier=HOTKEYF_ALT;
    else if(!bAlt && bCtrl && !bShift) wCombKey=HKCOMB_C,m_wModifier=HOTKEYF_CONTROL;
    else if(!bAlt && !bCtrl && bShift) wCombKey=HKCOMB_S,m_wModifier=HOTKEYF_SHIFT;
    else if(bAlt && bCtrl && !bShift) wCombKey=HKCOMB_CA,m_wModifier=HOTKEYF_ALT|HOTKEYF_CONTROL;
    else if(bAlt && !bCtrl && bShift) wCombKey=HKCOMB_SA,m_wModifier=HOTKEYF_SHIFT|HOTKEYF_ALT;
    else if(!bAlt && bCtrl && bShift) wCombKey=HKCOMB_SC,m_wModifier=HOTKEYF_SHIFT|HOTKEYF_CONTROL;
    else wCombKey=HKCOMB_SCA,m_wModifier=HOTKEYF_ALT|HOTKEYF_SHIFT|HOTKEYF_CONTROL;
    if(wCombKey&m_wInvalidComb)
        m_wModifier=m_wInvalidModifier;
}

void CDuiHotKeyCtrl::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
    if(!m_bInSetting)
    {
        m_bInSetting=TRUE;
        m_wVK=0;
        m_wModifier=m_wInvalidModifier;
    }
    CDuiStringT strKey=GetKeyName(nChar);
    if(!strKey.IsEmpty())
    {
        //
        m_wVK=nChar;
    }
    UpdateModifier();
    UpdateCaret();
    NotifyInvalidate();
}

void CDuiHotKeyCtrl::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
    if(!m_bInSetting) return;

    if(nChar == m_wVK)
    {
        m_bInSetting=FALSE;
    }
    else if(m_wVK==0 && (GetKeyState(VK_SHIFT)&0x8000)==0 && (GetKeyState(VK_MENU)&0x8000)==0 && (GetKeyState(VK_CONTROL)&0x8000)==0)
    {
        m_bInSetting=FALSE;
        UpdateModifier();
        UpdateCaret();
        NotifyInvalidate();
    }
    else if(nChar==VK_SHIFT || nChar==VK_MENU || nChar== VK_CONTROL)
    {
        UpdateModifier();
        UpdateCaret();
        NotifyInvalidate();
    }
}

void CDuiHotKeyCtrl::OnSysKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
    if(GetKeyState(VK_MENU)&0x8000) OnKeyDown(nChar,nRepCnt,nFlags);
    else SetMsgHandled(FALSE);
}

void CDuiHotKeyCtrl::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if(nChar==VK_MENU || GetKeyState(VK_MENU)&0x8000) OnKeyUp(nChar,nRepCnt,nFlags);
    else SetMsgHandled(FALSE);
}

void CDuiHotKeyCtrl::SetRule( WORD wInvalidComp,WORD wModifier )
{
    m_wInvalidComb=wInvalidComp;
    m_wInvalidModifier=wModifier;
}

void CDuiHotKeyCtrl::SetHotKey( WORD vKey,WORD wModifiers )
{
    m_wVK=vKey;
    m_wModifier=wModifiers;
    UpdateModifier();
    UpdateCaret();
    NotifyInvalidate();
}

void CDuiHotKeyCtrl::GetHotKey( WORD & vKey,WORD wModifers )
{
    vKey=m_wVK;
    wModifers=m_wModifier;
}

}//namespace DuiEngine
