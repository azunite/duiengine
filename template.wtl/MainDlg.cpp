// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"
#include "UIHander.h"

#include "IECtrl.h"

CMainDlg::CMainDlg() : CDuiHostWnd(IDR_DUI_MAIN_DIALOG)
{
	m_pUiHandler = new CUIHander(this);
} 

CMainDlg::~CMainDlg()
{
	delete m_pUiHandler; 
}

HWND CMainDlg::OnRealWndCreate( CDuiRealWnd *pRealWnd )
{
	HWND hWndContainer=m_hWnd;
	CRect rcWindow;
	UINT uCmdID=pRealWnd->GetCmdID();
	pRealWnd->GetRect(&rcWindow);

	const CDuiRealWndParam & paramRealWnd=pRealWnd->GetRealWndParam();
	if(_tcscmp(paramRealWnd.m_strClassName,_T("IECTRL"))==0)
	{
		CIECtrl *pView=new CIECtrl;
		pView->Load(paramRealWnd.m_pXmlParams);
		pView->Create(hWndContainer,rcWindow,paramRealWnd.m_strWindowName,paramRealWnd.m_dwStyle | WS_CLIPCHILDREN,paramRealWnd.m_dwExStyle,uCmdID);
		pRealWnd->SetData(pView);
		return pView->m_hWnd;
	}else
	return __super::OnRealWndCreate(pRealWnd);
}

void CMainDlg::OnRealWndDestroy( CDuiRealWnd *pRealWnd )
{
	const CDuiRealWndParam & paramRealWnd=pRealWnd->GetRealWndParam();
	if(_tcscmp(paramRealWnd.m_strClassName,_T("IECTRL"))==0)
	{
		if(::IsWindow(pRealWnd->GetRealHwnd(FALSE)))
		{
			::DestroyWindow(pRealWnd->GetRealHwnd(FALSE));
		}
		if(pRealWnd->GetData())
		{
			delete (CIECtrl*)pRealWnd->GetData();
			pRealWnd->SetData(0);
		}
	}else
	__super::OnRealWndDestroy(pRealWnd);

}
