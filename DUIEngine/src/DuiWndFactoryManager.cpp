#include "duistd.h"
#include "DuiWndFactoryManager.h"

#include "duictrls.h"

namespace DuiEngine
{


template<> DuiWindowFactoryManager * Singleton<DuiWindowFactoryManager>::ms_Singleton=0;

DuiWindowFactoryManager::DuiWindowFactoryManager(void)
{
    m_pFunOnKeyRemoved=OnWndFactoryRemoved;
    AddStandardWindowFactory();
}

void DuiWindowFactoryManager::AddStandardWindowFactory()
{
    AddKeyObject(CDuiPanel::GetClassName(),new TplDuiWindowFactory<CDuiPanel>(TRUE));
    AddKeyObject(CDuiPanelEx::GetClassName(),new TplDuiWindowFactory<CDuiPanelEx>(TRUE));
    AddKeyObject(CDuiScrollView::GetClassName(),new TplDuiWindowFactory<CDuiScrollView>(TRUE));
    AddKeyObject(CDuiDialog::GetClassName(),new TplDuiWindowFactory<CDuiDialog>(TRUE));
    AddKeyObject(CDuiDialogFile::GetClassName(),new TplDuiWindowFactory<CDuiDialogFile>(TRUE));
    AddKeyObject(CDuiStatic::GetClassName(),new TplDuiWindowFactory<CDuiStatic>(TRUE));
    AddKeyObject(CDuiButton::GetClassName(),new TplDuiWindowFactory<CDuiButton>(TRUE));
    AddKeyObject(CDuiSpacing::GetClassName(),new TplDuiWindowFactory<CDuiSpacing>(TRUE));
    AddKeyObject(CDuiImageWnd::GetClassName(),new TplDuiWindowFactory<CDuiImageWnd>(TRUE));
    AddKeyObject(CDuiProgress::GetClassName(),new TplDuiWindowFactory<CDuiProgress>(TRUE));
    AddKeyObject(CDuiImageBtnWnd::GetClassName(),new TplDuiWindowFactory<CDuiImageBtnWnd>(TRUE));
    AddKeyObject(CDuiRealWnd::GetClassName(),new TplDuiWindowFactory<CDuiRealWnd>(TRUE));
    AddKeyObject(CDuiLine::GetClassName(),new TplDuiWindowFactory<CDuiLine>(TRUE));
    AddKeyObject(CDuiCheckBox::GetClassName(),new TplDuiWindowFactory<CDuiCheckBox>(TRUE));
    AddKeyObject(CDuiIconWnd::GetClassName(),new TplDuiWindowFactory<CDuiIconWnd>(TRUE));
    AddKeyObject(CDuiTabCtrl::GetClassName(),new TplDuiWindowFactory<CDuiTabCtrl>(TRUE));
    AddKeyObject(CDuiRadioBox::GetClassName(),new TplDuiWindowFactory<CDuiRadioBox>(TRUE));
    AddKeyObject(CDuiLink::GetClassName(),new TplDuiWindowFactory<CDuiLink>(TRUE));
    AddKeyObject(CDuiGroup::GetClassName(),new TplDuiWindowFactory<CDuiGroup>(TRUE));
    AddKeyObject(CDuiAnimateImgWnd::GetClassName(),new TplDuiWindowFactory<CDuiAnimateImgWnd>(TRUE));
    AddKeyObject(CDuiScrollBar::GetClassName(),new TplDuiWindowFactory<CDuiScrollBar>(TRUE));
    AddKeyObject(CDuiListBox::GetClassName(),new TplDuiWindowFactory<CDuiListBox>(TRUE));
    AddKeyObject(CDuiListBoxEx::GetClassName(),new TplDuiWindowFactory<CDuiListBoxEx>(TRUE));
    AddKeyObject(CDuiItemBox::GetClassName(),new TplDuiWindowFactory<CDuiItemBox>(TRUE));
    AddKeyObject(CDuiToggle::GetClassName(),new TplDuiWindowFactory<CDuiToggle>(TRUE));
    AddKeyObject(CDuiTreeBox::GetClassName(),new TplDuiWindowFactory<CDuiTreeBox>(TRUE));
    AddKeyObject(CDuiTreeCtrl::GetClassName(),new TplDuiWindowFactory<CDuiTreeCtrl>(TRUE));
    AddKeyObject(CDuiRichEdit::GetClassName(),new TplDuiWindowFactory<CDuiRichEdit>(TRUE));
    AddKeyObject(CDuiEdit::GetClassName(),new TplDuiWindowFactory<CDuiEdit>(TRUE));
    AddKeyObject(CDuiSplitWnd::GetClassName(),new TplDuiWindowFactory<CDuiSplitWnd>(TRUE));
    AddKeyObject(CDuiSplitWnd_Col::GetClassName(),new TplDuiWindowFactory<CDuiSplitWnd_Col>(TRUE));
    AddKeyObject(CDuiSplitWnd_Row::GetClassName(),new TplDuiWindowFactory<CDuiSplitWnd_Row>(TRUE));
    AddKeyObject(CDuiComboBox::GetClassName(),new TplDuiWindowFactory<CDuiComboBox>(TRUE));
    AddKeyObject(CDuiHotKeyCtrl::GetClassName(),new TplDuiWindowFactory<CDuiHotKeyCtrl>(TRUE));
    AddKeyObject(CDuiCaption::GetClassName(),new TplDuiWindowFactory<CDuiCaption>(TRUE));

}

void DuiWindowFactoryManager::OnWndFactoryRemoved( const CDuiWindowFactoryPtr & obj )
{
	if(obj->IsSysWindow()) delete obj;
}

CDuiWindow * DuiWindowFactoryManager::CreateWindowByName( LPCSTR pszClassName )
{
	if(!HasKey(pszClassName)) return NULL;
	return GetKeyObject(pszClassName)->NewWindow();
}

}//namesspace DuiEngine