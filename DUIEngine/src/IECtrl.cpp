// IECtrl.h : interface of the CIECtrl class
//
/////////////////////////////////////////////////////////////////////////////

#include "duistd.h"
#include "IECtrl.h"

#include <comutil.h>
#pragma comment(lib,"comsuppw.lib")

namespace DuiEngine{

BOOL __stdcall CIECtrl::Navigate(BSTR Url)
{
	CComPtr<IWebBrowser2> spWebBrowser;
	HRESULT hr = QueryControl(IID_IWebBrowser2, (void**)&spWebBrowser);
	if(!SUCCEEDED(hr) || !spWebBrowser) return FALSE;

	CComVariant v;
	hr = spWebBrowser->Navigate(Url,&v,&v,&v,&v);
	return SUCCEEDED(hr);
}

//CDuiMessageFilter
BOOL CIECtrl::PreTranslateMessage(MSG* pMsg)
{
	if((pMsg->message < WM_KEYFIRST || pMsg->message > WM_KEYLAST) &&
		(pMsg->message < WM_MOUSEFIRST || pMsg->message > WM_MOUSELAST))
		return FALSE;
	if(pMsg->message == WM_RBUTTONDOWN && m_bNoContextMenu)
		return TRUE;

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		GetParent().SendMessage(WM_KEYDOWN, pMsg->wParam, pMsg->lParam);
	}

	BOOL bRet = FALSE;
	// give HTML page a chance to translate this message
	if(pMsg->hwnd == m_hWnd || IsChild(pMsg->hwnd))
	{
		bRet = (BOOL)SendMessage(WM_FORWARDMSG, 0, (LPARAM)pMsg);

		HWND hFocus = GetFocus(); 
		if (hFocus != m_hWnd && !IsChild(hFocus))
		{
			CRect rcWindow; 
			GetWindowRect(rcWindow); 
			if (rcWindow.PtInRect(pMsg->pt)) { SetFocus(); }
		}
	}

	return bRet;
}

void CIECtrl::SetFocusToHTML()
{
	CComPtr<IWebBrowser2> spWebBrowser;
	HRESULT hRet = QueryControl(IID_IWebBrowser2, (void**)&spWebBrowser);
	if(SUCCEEDED(hRet) && spWebBrowser != NULL)
	{
		CComPtr<IDispatch> spDocument;
		hRet = spWebBrowser->get_Document(&spDocument);
		if(SUCCEEDED(hRet) && spDocument != NULL)
		{
			CComQIPtr<IHTMLDocument2> spHtmlDoc = spDocument;
			if(spHtmlDoc != NULL)
			{
				CComPtr<IHTMLWindow2> spParentWindow;
				hRet = spHtmlDoc->get_parentWindow(&spParentWindow);
				if(spParentWindow != NULL)
					spParentWindow->focus();
			}
		}
	}
}

CComPtr<IWebBrowser2> CIECtrl::GetIWebBrowser(void)
{
	CComPtr<IWebBrowser2> spIWebBrowser;
	QueryControl(IID_IWebBrowser2, (void**)&spIWebBrowser); 
	return spIWebBrowser; 
}

VARIANT CIECtrl::ExecuteScript( std::wstring const& fun,std::vector< std::wstring >const& params )
{
	VARIANT varErr;
	VariantInit( &varErr );

	//get document dispatch interface
	IDispatch* pDisp = NULL;

	CComPtr<IWebBrowser2> spIWebBrowser;
	QueryControl(IID_IWebBrowser2, (void**)&spIWebBrowser); 
	HRESULT hr = spIWebBrowser->get_Document( &pDisp );

	if ( FAILED( hr ) || pDisp == NULL )
	{
		return varErr;
	}

	IHTMLDocument2* pDoc = NULL;
	pDisp->QueryInterface( IID_IHTMLDocument2,(void**)&pDoc );
	pDisp->Release();

	IDispatch* pScript = NULL;
	hr = pDoc->get_Script( &pScript );
	pDoc->Release();

	if ( FAILED( hr ) || pScript == NULL )
	{
		return varErr;
	}

	CComBSTR bstrMember((int)fun.size(),fun.c_str() );
	DISPID dispid = 0;
	BSTR bstr = (BSTR)bstrMember;
	hr = pScript->GetIDsOfNames( IID_NULL,&(bstr),1,LOCALE_SYSTEM_DEFAULT,&dispid );

	if ( FAILED( hr ) )
	{
		return varErr;
	}

	DISPPARAMS dispparams;
	::ZeroMemory( &dispparams,sizeof( DISPPARAMS ) );
	dispparams.cArgs = (UINT)params.size();
	dispparams.rgvarg = new VARIANT[dispparams.cArgs];
	dispparams.cNamedArgs = 0;

	for ( size_t i = 0;i < params.size();i++ )
	{
		size_t indx = params.size() - i - 1;
		CComBSTR bstrParam((int)params[indx].size(),params[indx].c_str() );
		bstrParam.CopyTo( &dispparams.rgvarg[i].bstrVal );
		dispparams.rgvarg[i].vt = VT_BSTR;
	}

	EXCEPINFO excepinfo;
	::ZeroMemory( &excepinfo,sizeof( EXCEPINFO ) );
	VARIANT varRet;
	UINT nArgErr = (UINT)-1;	//initialize to invalid arg

	hr = pScript->Invoke( dispid,IID_NULL,0,DISPATCH_METHOD,&dispparams,&varRet,&excepinfo,&nArgErr );

	delete []dispparams.rgvarg;
	pScript->Release();

	if ( FAILED( hr ) )
	{
		return varErr;
	}

	return varRet;
}

void __stdcall CIECtrl::OnEventDocumentComplete(IDispatch* pDisp, VARIANT* URL)
{
	// Send message to the main frame
	ATLASSERT(V_VT(URL) == VT_BSTR);
	USES_CONVERSION;

	CComQIPtr <IUnknown, &IID_IUnknown> pUnkDisp; 
	pUnkDisp = pDisp; 

	CComPtr<IWebBrowser2> spIWebBrowser;
	QueryControl(IID_IWebBrowser2, (void**)&spIWebBrowser);
	CComQIPtr <IUnknown, &IID_IUnknown> pUnkBrowser = spIWebBrowser;

	if(pUnkBrowser == pUnkDisp) 
	{
		IELOADCOMPLETE stNav;
		stNav.nmhdr.hwndFrom=m_hWnd;
		stNav.nmhdr.idFrom=GetDlgCtrlID();
		stNav.nmhdr.code=NC_LOADCOMPLETE;
		_bstr_t bstrUrl(*URL);
		stNav.pszUrl=bstrUrl;
		stNav.spIWebBrowser = pUnkBrowser; 

		GetParent().SendMessage(WM_NOTIFY,stNav.nmhdr.idFrom,(LPARAM)&stNav);
	}

	SetFocusToHTML();
}

void __stdcall CIECtrl::OnNavigateComplete2( IDispatch* pDisp, VARIANT* pvURL )
{
	// Send message to the main frame
	ATLASSERT(V_VT(pvURL) == VT_BSTR);
	USES_CONVERSION;

	CComQIPtr <IUnknown, &IID_IUnknown> pUnkDisp; 
	pUnkDisp = pDisp; 

	CComPtr<IWebBrowser2> spIWebBrowser;
	QueryControl(IID_IWebBrowser2, (void**)&spIWebBrowser);
	CComQIPtr <IUnknown, &IID_IUnknown> pUnkBrowser = spIWebBrowser;

	if(pUnkBrowser == pUnkDisp) 
	{
		IENAVCOMPLETE stNav;
		stNav.nmhdr.hwndFrom=m_hWnd;
		stNav.nmhdr.idFrom=GetDlgCtrlID();
		stNav.nmhdr.code=NC_NAVCOMPLETE;
		_bstr_t bstrUrl(*pvURL);
		stNav.pszUrl=bstrUrl;
		stNav.spIWebBrowser = pUnkBrowser; 

		GetParent().SendMessage(WM_NOTIFY,stNav.nmhdr.idFrom,(LPARAM)&stNav);
	}

	SetFocusToHTML();
}

void __stdcall CIECtrl::OnEventTitleChange(BSTR Text)
{
	IETITLECHANGED stNav;
	stNav.nmhdr.hwndFrom = m_hWnd;
	stNav.nmhdr.idFrom = GetDlgCtrlID();
	stNav.nmhdr.code = NC_TITLECHANGED;
	stNav.pszTitle = OLE2T(Text);

	GetParent().SendMessage(WM_NOTIFY, stNav.nmhdr.idFrom, (LPARAM)&stNav);
}

void __stdcall CIECtrl::OnEventStatusTextChange(BSTR Text)
{
	USES_CONVERSION;
}

void __stdcall CIECtrl::OnEventCommandStateChange(long Command, VARIANT_BOOL Enable)
{
	if(Command == CSC_NAVIGATEBACK)
		m_bCanGoBack = (Enable != VARIANT_FALSE);
	else if(Command == CSC_NAVIGATEFORWARD)
		m_bCanGoForward = (Enable != VARIANT_FALSE);
}

void __stdcall CIECtrl::OnBeforeNavigate2 ( 
	IDispatch* pDisp, VARIANT* URL, VARIANT* Flags,
	VARIANT* TargetFrameName, VARIANT* PostData,
	VARIANT* Headers, VARIANT_BOOL* Cancel )
{
	IENAVIGATE stNav;
	stNav.nmhdr.hwndFrom=m_hWnd;
	stNav.nmhdr.idFrom=GetDlgCtrlID();
	stNav.nmhdr.code=NC_BROWSER;
	_bstr_t bstrUrl(*URL);
	stNav.pszUrl=bstrUrl;
	stNav.bCancel=FALSE;

	QueryControl(IID_IWebBrowser2, (void**)&stNav.spIWebBrowser);

	GetParent().SendMessage(WM_NOTIFY,stNav.nmhdr.idFrom,(LPARAM)&stNav);
	*Cancel=stNav.bCancel;
}

void __stdcall CIECtrl::OnNewWindow3 (
									  IDispatch **ppDisp,
									  VARIANT_BOOL *Cancel,
									  DWORD dwFlags,
									  BSTR bstrUrlContext,
									  BSTR bstrUrl )
{
	IENEWWINDOW stNav;
	stNav.nmhdr.hwndFrom=m_hWnd;
	stNav.nmhdr.idFrom=GetDlgCtrlID();
	stNav.nmhdr.code=NC_NEWWINDOW;
	stNav.pszUrl=bstrUrl;
	QueryControl(IID_IWebBrowser2, (void**)&stNav.spIWebBrowser);
	stNav.bCancel=FALSE;

	GetParent().SendMessage(WM_NOTIFY,stNav.nmhdr.idFrom,(LPARAM)&stNav);
	*Cancel=stNav.bCancel;
}

LRESULT CIECtrl::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);

	// Connect events
	CComPtr<IWebBrowser2> spWebBrowser2;
	HRESULT hRet = QueryControl(IID_IWebBrowser2, (void**)&spWebBrowser2);
	if(SUCCEEDED(hRet))
	{
		if(FAILED(DispEventAdvise(spWebBrowser2, &DIID_DWebBrowserEvents2)))
			ATLASSERT(FALSE);
	}

	// Set host flag to indicate that we handle themes
	CComPtr<IAxWinAmbientDispatch> spHost;
	hRet = QueryHost(IID_IAxWinAmbientDispatch, (void**)&spHost);
	if(SUCCEEDED(hRet))
	{
		const DWORD _DOCHOSTUIFLAG_THEME = 0x40000;
		hRet = spHost->put_DocHostFlags(DOCHOSTUIFLAG_NO3DBORDER | _DOCHOSTUIFLAG_THEME|(m_bNoScrollBar?DOCHOSTUIFLAG_SCROLL_NO:0));
		ATLASSERT(SUCCEEDED(hRet));
	}

	SetExternalUIHandler(new CBrowserHostUIHandlerImpl(m_hWnd)); 

	MsgFilterRegister(GetParent());
	spWebBrowser2->put_Silent(VARIANT_TRUE);

	if(spWebBrowser2)
	{
		IECREATE stNav;
		stNav.nmhdr.hwndFrom = m_hWnd;
		stNav.nmhdr.idFrom = GetDlgCtrlID();
		stNav.nmhdr.code = NC_CREATE;
		stNav.pszUrl=NULL;
		QueryControl(IID_IWebBrowser2, (void**)&stNav.spIWebBrowser);

		GetParent().SendMessage(WM_NOTIFY,stNav.nmhdr.idFrom,(LPARAM)&stNav);
	}
	return lRet;
}

LRESULT CIECtrl::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	SetExternalUIHandler(NULL);
	MsgFilterUnregister(GetParent());

	// Disconnect events
	CComPtr<IWebBrowser2> spWebBrowser2;
	HRESULT hRet = QueryControl(IID_IWebBrowser2, (void**)&spWebBrowser2);
	if(SUCCEEDED(hRet))
	{
		IEDESTROY stNav;
		stNav.nmhdr.hwndFrom = m_hWnd;
		stNav.nmhdr.idFrom = GetDlgCtrlID();
		stNav.nmhdr.code = NC_DESTROY;
		stNav.pszUrl=NULL;
		stNav.spIWebBrowser = spWebBrowser2; 
		GetParent().SendMessage(WM_NOTIFY,stNav.nmhdr.idFrom,(LPARAM)&stNav);

		DispEventUnadvise(spWebBrowser2, &DIID_DWebBrowserEvents2);
	}

	bHandled=FALSE;
	return 1;
}

LRESULT CIECtrl::OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	LRESULT lRet = DefWindowProc(uMsg, wParam, lParam);
	SetFocusToHTML();

	return lRet;
}

_ATL_FUNC_INFO CIECtrl::DocumentComplete2_Info = { CC_STDCALL, VT_EMPTY, 2, { VT_DISPATCH, VT_BYREF | VT_VARIANT } };
_ATL_FUNC_INFO CIECtrl::TitleChange_Info = { CC_STDCALL, VT_EMPTY, 1, { VT_BSTR } };
_ATL_FUNC_INFO CIECtrl::StatusTextChange_Info = { CC_STDCALL, VT_EMPTY, 1, { VT_BSTR } };
_ATL_FUNC_INFO CIECtrl::CommandStateChange_Info = { CC_STDCALL, VT_EMPTY, 2, { VT_I4, VT_BOOL } };
_ATL_FUNC_INFO CIECtrl::BeforeNavigate2_Info =
{ CC_STDCALL, VT_EMPTY, 7,
{ VT_DISPATCH, VT_VARIANT|VT_BYREF, VT_VARIANT|VT_BYREF,
VT_VARIANT|VT_BYREF, VT_VARIANT|VT_BYREF, VT_VARIANT|VT_BYREF,
VT_BOOL|VT_BYREF }
};
_ATL_FUNC_INFO CIECtrl::NewWindow3_Info =
{ CC_STDCALL, VT_EMPTY, 5,
{ VT_DISPATCH, VT_BOOL|VT_BYREF, VT_UINT, VT_BSTR, VT_BSTR }
};
_ATL_FUNC_INFO CIECtrl::NavigateComplete2_Info = {CC_STDCALL, VT_EMPTY, 2, {VT_DISPATCH, VT_BYREF|VT_VARIANT}};

}//namespace DuiEngine