//////////////////////////////////////////////////////////////////////////
//  Class Name: CDuiDropDownListOwner / CDuiDropDownListBase /
//              CDuiDropDownList / CDuiDropDownListEx
// Description: The common dropdown list
//     Creator: JinHui
//     Version: 2012.12.20 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#include "duistd.h"
#include "DuiDropDownList.h"

namespace DuiEngine
{

CDuiDropDownListBase::CDuiDropDownListBase(CDuiDropDownListOwner* pOwner,int nDropHeight)
    :m_pOwner(pOwner)
    ,m_nDropHeight(nDropHeight)
{
    MsgFilterRegister(pOwner->GetHostHwnd());
}

BOOL CDuiDropDownListBase::FixPosition(const CRect * prcOwner, int nDropHeight)
{
    BOOL bShowTop=FALSE;
    MONITORINFO oMonitor = {0};
    oMonitor.cbSize = sizeof(oMonitor);
    ::GetMonitorInfo(::MonitorFromWindow(GetContainer()->GetHostHwnd(), MONITOR_DEFAULTTOPRIMARY), &oMonitor);

    if(prcOwner->bottom+nDropHeight>oMonitor.rcWork.bottom)
    {
        bShowTop=TRUE;
        MoveWindow(prcOwner->left,prcOwner->top-nDropHeight,prcOwner->Width(),nDropHeight,FALSE);
    }
    else
    {
        MoveWindow(prcOwner->left,prcOwner->bottom,prcOwner->Width(),nDropHeight,FALSE);
    }

    return bShowTop;
}

int CDuiDropDownListBase::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
    int nRet=__super::OnCreate(lpCreateStruct);
    if(nRet!=0) return nRet;

	pugi::xml_document * pXmlDocTempl=(pugi::xml_document*)lpCreateStruct->lpCreateParams;
    DUIASSERT(pXmlDocTempl);
    CreateListBox(pXmlDocTempl);

    CRect rcClient;
    GetClientRect(&rcClient);
    Move(&rcClient);

    return 0;
}

void CDuiDropDownListBase::OnFinalMessage(HWND)
{
    __super::OnFinalMessage(0);
    MsgFilterUnregister(m_pOwner->GetHostHwnd());
    delete this;
}

void CDuiDropDownListBase::OnKillFocus( HWND wndFocus )
{
    PostMessage(WM_CLOSE);
}

void CDuiDropDownListBase::OnClose()
{
    DefWindowProc();
    m_pOwner->OnDropDownListClose();
}

BOOL CDuiDropDownListBase::PreTranslateMessage( MSG* pMsg )
{
    return _PreTranslateMessage(pMsg);
}

///////////////////////////////////////////////////////////////////////////////////////////

CDuiDropDownList::CDuiDropDownList(CDuiDropDownListOwner* pOwner,int nDropHeight)
    : CDuiDropDownListBase(pOwner, nDropHeight)
    , m_pListBox(NULL)
{
}

void CDuiDropDownList::CreateListBox(pugi::xml_document *pXmlDocTmpl)
{
    m_pListBox=new CDuiListBox;
    InsertChild(m_pListBox);
    m_pListBox->SetCmdID(IDC_DROPDOWN_LIST);

    m_pListBox->Load(pXmlDocTmpl->first_child());
    m_pListBox->SetAttribute("pos", "0,0,-0,-0", TRUE);
    m_pListBox->SetAttribute("hottrack","1",TRUE);

    m_pListBox->SetOwner(m_pOwner->GetWindow());	//chain notify message to combobox
    m_pListBox->SetDuiFocus();
}


void CDuiDropDownList::DeleteItem(int iItem)
{
    m_pListBox->DeleteString(iItem);
}

void CDuiDropDownList::UpdateItems(const CRect * prcOwner)
{
    int nItems=m_pOwner->GetListItemCount();
    BOOL bShowTop=FALSE;
    if(prcOwner)
    {
        int nDropHeight=m_nDropHeight;
        if(nItems!=0 && nItems*m_pListBox->GetItemHeight()+m_pListBox->GetStyle().m_nMarginY*2<m_nDropHeight)
        {
            nDropHeight=nItems*m_pListBox->GetItemHeight()+m_pListBox->GetStyle().m_nMarginY*2;
        }

        bShowTop = FixPosition(prcOwner, nDropHeight);
    }

    for(int i=0; i<nItems; i++)
    {
        m_pListBox->AddString(m_pOwner->GetListItemText(i),
                              m_pOwner->GetListItemIcon(i), m_pOwner->GetListItemData(i));
    }

    m_pListBox->SetCurSel(m_pOwner->GetListCurSel());
    m_pListBox->EnsureVisible(m_pOwner->GetListCurSel());
    if(prcOwner)
    {
        ::AnimateWindow(m_hWnd,m_pOwner->GetAnimateTime(),
                        AW_SLIDE|AW_ACTIVATE|(bShowTop?AW_VER_NEGATIVE:AW_VER_POSITIVE));
    }
}

///////////////////////////////////////////////////////////////////////////////////////////

CDuiDropDownListEx::CDuiDropDownListEx(CDuiDropDownListOwner* pOwner,int nDropHeight)
    : CDuiDropDownListBase(pOwner, nDropHeight)
    , m_pListBox(NULL)
    ,m_nTextID(-1)
    ,m_nIconID(-1)
{
}

void CDuiDropDownListEx::CreateListBox(pugi::xml_document *pXmlDocTmpl)
{
    m_pListBox=new CDuiListBoxEx;
    InsertChild(m_pListBox);
    m_pListBox->SetCmdID(IDC_DROPDOWN_LIST);

	pugi::xml_node xmlTemplate=pXmlDocTmpl->first_child();
	m_nTextID=xmlTemplate.attribute("id_text").as_int(0);
	m_nIconID=xmlTemplate.attribute("id_icon").as_int(0);

    m_pListBox->Load(xmlTemplate);
    m_pListBox->SetAttribute("pos", "0,0,-0,-0", TRUE);
    m_pListBox->SetAttribute("hottrack","1",TRUE);

    m_pListBox->SetOwner(m_pOwner->GetWindow());	//chain notify message to combobox
    m_pListBox->SetDuiFocus();
}


void CDuiDropDownListEx::DeleteItem(int iItem)
{
    m_pListBox->DeleteItem(iItem);
}

void CDuiDropDownListEx::UpdateItems(const CRect * prcOwner)
{
    int nItems=m_pOwner->GetListItemCount();
    BOOL bShowTop=FALSE;
    if(prcOwner)
    {
        int nDropHeight=m_nDropHeight;
        if(nItems!=0 && nItems*m_pListBox->GetItemHeight()+m_pListBox->GetStyle().m_nMarginY*2<m_nDropHeight)
        {
            nDropHeight=nItems*m_pListBox->GetItemHeight()+m_pListBox->GetStyle().m_nMarginY*2;
        }

        bShowTop = FixPosition(prcOwner, nDropHeight);
    }
    m_pListBox->SetItemCount(nItems);
    for(int i=0; i<nItems; i++)
    {
        CDuiPanel *pPanel=m_pListBox->GetItemPanel(i);
        if(m_nTextID!=-1)
        {
            CDuiWindow *pText=pPanel->FindChildByCmdID(m_nTextID);
            if(pText) pText->SetInnerText(m_pOwner->GetListItemText(i));
        }
        if(m_nIconID!=-1)
        {
            CDuiImageWnd *pIcon=(CDuiImageWnd*)pPanel->FindChildByCmdID(m_nIconID);
            if(pIcon && pIcon->IsClass(CDuiImageWnd::GetClassName()))
                pIcon->SetIcon(m_pOwner->GetListItemIcon(i));
        }
    }
    m_pListBox->SetCurSel(m_pOwner->GetListCurSel());
    m_pListBox->EnsureVisible(m_pOwner->GetListCurSel());
    if(prcOwner)
    {
        ::AnimateWindow(m_hWnd,m_pOwner->GetAnimateTime(),
                        AW_SLIDE|AW_ACTIVATE|(bShowTop?AW_VER_NEGATIVE:AW_VER_POSITIVE));
    }
}

}