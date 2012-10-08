#include "duistd.h"
#include "DuiWndFactoryManager.h"

#include "duictrls.h"

namespace DuiEngine{


template<> DuiWindowFactoryManager * Singleton<DuiWindowFactoryManager>::ms_Singleton=0;

DuiWindowFactoryManager::DuiWindowFactoryManager(void)
{
	m_pFunOnKeyRemoved=OnKeyRemoved;
	AddStandardWindowFactory();
}

void DuiWindowFactoryManager::AddStandardWindowFactory()
{
	AddKeyObject(CDuiPanel::GetClassName(),new TplDuiWindowFactory<CDuiPanel>);
	AddKeyObject(CDuiPanelEx::GetClassName(),new TplDuiWindowFactory<CDuiPanelEx>);
	AddKeyObject(CDuiScrollView::GetClassName(),new TplDuiWindowFactory<CDuiScrollView>);
	AddKeyObject(CDuiDialog::GetClassName(),new TplDuiWindowFactory<CDuiDialog>);
	AddKeyObject(CDuiDialogFile::GetClassName(),new TplDuiWindowFactory<CDuiDialogFile>);
	AddKeyObject(CDuiStatic::GetClassName(),new TplDuiWindowFactory<CDuiStatic>);
	AddKeyObject(CDuiButton::GetClassName(),new TplDuiWindowFactory<CDuiButton>);
	AddKeyObject(CDuiSpacing::GetClassName(),new TplDuiWindowFactory<CDuiSpacing>);
	AddKeyObject(CDuiImageWnd::GetClassName(),new TplDuiWindowFactory<CDuiImageWnd>);
	AddKeyObject(CDuiProgress::GetClassName(),new TplDuiWindowFactory<CDuiProgress>);
	AddKeyObject(CDuiImageBtnWnd::GetClassName(),new TplDuiWindowFactory<CDuiImageBtnWnd>);
	AddKeyObject(CDuiRealWnd::GetClassName(),new TplDuiWindowFactory<CDuiRealWnd>);
	AddKeyObject(CDuiLine::GetClassName(),new TplDuiWindowFactory<CDuiLine>);
	AddKeyObject(CDuiCheckBox::GetClassName(),new TplDuiWindowFactory<CDuiCheckBox>);
	AddKeyObject(CDuiIconWnd::GetClassName(),new TplDuiWindowFactory<CDuiIconWnd>);
	AddKeyObject(CDuiTabCtrl::GetClassName(),new TplDuiWindowFactory<CDuiTabCtrl>);
	AddKeyObject(CDuiRadioBox::GetClassName(),new TplDuiWindowFactory<CDuiRadioBox>);
	AddKeyObject(CDuiRichText::GetClassName(),new TplDuiWindowFactory<CDuiRichText>);
	AddKeyObject(CDuiLink::GetClassName(),new TplDuiWindowFactory<CDuiLink>);
	AddKeyObject(CDuiDrawFileIcon::GetClassName(),new TplDuiWindowFactory<CDuiDrawFileIcon>);
	AddKeyObject(CDuiGroup::GetClassName(),new TplDuiWindowFactory<CDuiGroup>);
	AddKeyObject(CDuiAnimateImgWnd::GetClassName(),new TplDuiWindowFactory<CDuiAnimateImgWnd>);
	AddKeyObject(CDuiScrollBar::GetClassName(),new TplDuiWindowFactory<CDuiScrollBar>);
	AddKeyObject(CDuiListBox::GetClassName(),new TplDuiWindowFactory<CDuiListBox>);
	AddKeyObject(CDuiItemBox::GetClassName(),new TplDuiWindowFactory<CDuiItemBox>);
	AddKeyObject(CDuiToggle::GetClassName(),new TplDuiWindowFactory<CDuiToggle>);
	AddKeyObject(CDuiTreeCtrl::GetClassName(),new TplDuiWindowFactory<CDuiTreeCtrl>);
	AddKeyObject(CDuiRichEdit::GetClassName(),new TplDuiWindowFactory<CDuiRichEdit>);
	AddKeyObject(CDuiSplitWnd::GetClassName(),new TplDuiWindowFactory<CDuiSplitWnd>);
	AddKeyObject(CDuiSplitWnd_Col::GetClassName(),new TplDuiWindowFactory<CDuiSplitWnd_Col>);
	AddKeyObject(CDuiSplitWnd_Row::GetClassName(),new TplDuiWindowFactory<CDuiSplitWnd_Row>);
	AddKeyObject(CDuiComboBox::GetClassName(),new TplDuiWindowFactory<CDuiComboBox>);
	AddKeyObject(CDuiHotKeyCtrl::GetClassName(),new TplDuiWindowFactory<CDuiHotKeyCtrl>);
	AddKeyObject(CDuiCaption::GetClassName(),new TplDuiWindowFactory<CDuiCaption>);

}

}//namesspace DuiEngine