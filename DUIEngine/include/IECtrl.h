// IECtrl.h : interface of the CIECtrl class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <exdispid.h>

#include "duiobject.h"
#include "duimsgfilter.h"
#include <vector>

namespace DuiEngine{

const int _nDispatchID = 1;

class CBrowserHostUIHandlerImpl : public IDispatchImpl<IDocHostUIHandlerDispatch, &IID_IDocHostUIHandlerDispatch, &LIBID_ATLLib>
{
public:
	CBrowserHostUIHandlerImpl(HWND hWnd) : m_hWnd(hWnd)
	{
		m_dwRef = 0;
	}

	~CBrowserHostUIHandlerImpl()
	{
	}

	STDMETHOD_(ULONG, AddRef)()
	{ 
		return InterlockedIncrement(&m_dwRef); 
	}
	STDMETHOD_(ULONG, Release)()
	{
		unsigned long l = InterlockedDecrement(&m_dwRef);
		if(l == 0)
			delete this;
		return l;
	}
	STDMETHOD(QueryInterface)(REFIID iid, LPVOID far* ppvObject)
	{
		HRESULT hrRet = S_OK;
		*ppvObject = NULL;
		if (IsEqualIID(iid, IID_IUnknown))
			*ppvObject = (IUnknown*)this;
		else if(IsEqualIID(iid, IID_IDispatch))
			*ppvObject = (IDispatch*)this;
		else if (IsEqualIID(iid, __uuidof(IDocHostUIHandler)))
			*ppvObject = (IDocHostUIHandler*)this;
		else
			hrRet = E_NOINTERFACE;
		if (S_OK == hrRet)
			((IUnknown*)*ppvObject)->AddRef();
		return hrRet;
	}
	STDMETHOD(ShowContextMenu)(/* [in] */ DWORD dwID,
		/* [in] */ DWORD x,
		/* [in] */ DWORD y,
		/* [in] */ IUnknown *pcmdtReserved,
		/* [in] */ IDispatch *pdispReserved,
		/* [retval][out] */ HRESULT *dwRetVal)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(GetHostInfo)(/* [out][in] */ DWORD *pdwFlags,	/* [out][in] */ DWORD *pdwDoubleClick)
	{
		CComPtr<IAxWinAmbientDispatch> spHost; 

		CComPtr<IUnknown> spUnk;
		HRESULT hr = AtlAxGetHost(m_hWnd, &spUnk);
		if (SUCCEEDED(hr))
			hr = spUnk->QueryInterface(IID_IAxWinAmbientDispatch, (void**)&spHost);

		if(SUCCEEDED(hr))
		{
			spHost->get_DocHostFlags(pdwFlags); 
			spHost->get_DocHostDoubleClickFlags(pdwDoubleClick); 
			return S_OK;
		}
		return E_NOTIMPL;
	}

	STDMETHOD(ShowUI)(/* [in] */ DWORD dwID,
		/* [in] */ IUnknown *pActiveObject,
		/* [in] */ IUnknown *pCommandTarget,
		/* [in] */ IUnknown *pFrame,
		/* [in] */ IUnknown *pDoc,
		/* [retval][out] */ HRESULT *dwRetVal)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(HideUI)(){ return E_NOTIMPL; }
	STDMETHOD(UpdateUI)(){ return E_NOTIMPL; }
	STDMETHOD(EnableModeless)(/* [in] */ VARIANT_BOOL fEnable){ return E_NOTIMPL; }
	STDMETHOD(OnDocWindowActivate)(/* [in] */ VARIANT_BOOL fActivate){ return E_NOTIMPL; }
	STDMETHOD(OnFrameWindowActivate)(/* [in] */ VARIANT_BOOL fActivate){ return E_NOTIMPL; }
	STDMETHOD(ResizeBorder)(/* [in] */ long left,
		/* [in] */ long top,
		/* [in] */ long right,
		/* [in] */ long bottom,
		/* [in] */ IUnknown *pUIWindow,
		/* [in] */ VARIANT_BOOL fFrameWindow)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(TranslateAccelerator)(/* [in] */ DWORD_PTR hWnd,
		/* [in] */ DWORD nMessage,
		/* [in] */ DWORD_PTR wParam,
		/* [in] */ DWORD_PTR lParam,
		/* [in] */ BSTR bstrGuidCmdGroup,
		/* [in] */ DWORD nCmdID,
		/* [retval][out] */ HRESULT *dwRetVal)
	{
		return E_NOTIMPL; 
	}

	STDMETHOD(GetOptionKeyPath)(/* [out] */ BSTR *pbstrKey,	/* [in] */ DWORD dw){ return E_NOTIMPL;}
	STDMETHOD(GetDropTarget)(/* [in] */ IUnknown *pDropTarget,/* [out] */ IUnknown **ppDropTarget){ return E_NOTIMPL; }

	STDMETHOD(GetExternal)(/* [out] */ IDispatch **ppDispatch)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(TranslateUrl)(/* [in] */ DWORD dwTranslate, /* [in] */ BSTR bstrURLIn, /* [out] */ BSTR *pbstrURLOut){ return E_NOTIMPL; }
	STDMETHOD(FilterDataObject)(/* [in] */ IUnknown *pDO, /* [out] */ IUnknown **ppDORet){ return E_NOTIMPL; }

private:
	long			m_dwRef; 
	HWND            m_hWnd; 
};

typedef struct tagIENAVIGATE
{
	NMHDR nmhdr;
	LPCWSTR pszUrl;
	CComPtr<IWebBrowser2> spIWebBrowser;
	BOOL	bCancel;
}IENAVIGATE, *LPIENAVIGATE;

typedef tagIENAVIGATE IENEWWINDOW, * LPIENEWWINDOW; 

typedef struct tagIELOADCOMPLETE
{
	NMHDR nmhdr;
	LPCWSTR pszUrl;
	CComPtr<IWebBrowser2> spIWebBrowser; 
} IELOADCOMPLETE, * LPIELOADCOMPLETE;

typedef struct tagIETITLECHANGED
{
	NMHDR nmhdr;
	LPCWSTR pszTitle;
}IETITLECHANGED, *LPIETITLECHANGED;

typedef struct tagNAVCOMPETE2
{
	NMHDR nmhdr;
	LPCWSTR pszUrl;
	CComPtr<IWebBrowser2> spIWebBrowser; 
}IENAVCOMPLETE, LPIENAVCOMPLETE;

typedef tagIELOADCOMPLETE IEDESTROY, * LPIEDESTROY; 

typedef tagIELOADCOMPLETE IECREATE, * LPIECREATE; 

#define NC_BROWSER					(100)
#define NC_NEWWINDOW			(101)
#define NC_LOADCOMPLETE		(102)
#define NC_DESTROY					(103)
#define NC_CREATE						(104)
#define NC_TITLECHANGED			(105)
#define NC_NAVCOMPLETE			(106)

class DUI_EXP CIECtrlPropertySet : public CDuiObject
{
	DUIOBJ_DECLARE_CLASS_NAME(CIECtrlPropertySet, "IECtrlPropertySet")
public:
	CIECtrlPropertySet():m_bNoScrollBar(FALSE),m_bNoContextMenu(TRUE)
	{

	}
protected:
	BOOL	m_bNoScrollBar;
	BOOL	m_bNoContextMenu;
	DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
		DUIWIN_INT_ATTRIBUTE("NoScrollBar", m_bNoScrollBar, FALSE)
		DUIWIN_INT_ATTRIBUTE("NoContextMenu", m_bNoContextMenu, FALSE)
	DUIWIN_DECLARE_ATTRIBUTES_END()
};

class DUI_EXP CIECtrl : public CWindowImpl<CIECtrl, CAxWindow>
		,public IDispEventSimpleImpl<_nDispatchID, CIECtrl, &DIID_DWebBrowserEvents2>
		,public CIECtrlPropertySet
		,public CDuiMessageFilter
{
public:
	DECLARE_WND_SUPERCLASS(_T("WTL_IECTRL"), CAxWindow::GetWndClassName())

	// IDispatch events function info
	static _ATL_FUNC_INFO NavigateComplete2_Info;
	static _ATL_FUNC_INFO DocumentComplete2_Info;
	static _ATL_FUNC_INFO TitleChange_Info;
	static _ATL_FUNC_INFO StatusTextChange_Info;
	static _ATL_FUNC_INFO CommandStateChange_Info;
	static _ATL_FUNC_INFO BeforeNavigate2_Info;
	static _ATL_FUNC_INFO NewWindow3_Info;

	bool m_bCanGoBack;
	bool m_bCanGoForward;


	CIECtrl() : m_bCanGoBack(false), m_bCanGoForward(false)
	{
	}

	BOOL __stdcall Navigate(BSTR Url);
	//Ö´ÐÐ½Å±¾
	VARIANT ExecuteScript( std::wstring const& fun,std::vector< std::wstring >const& params );

	//CDuiMessageFilter
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void SetFocusToHTML();

	CComPtr<IWebBrowser2> GetIWebBrowser(void);	

// Event map and handlers
#ifdef _VC80X
  #pragma warning(disable:4867)
#endif
	BEGIN_SINK_MAP(CIECtrl)
		SINK_ENTRY_INFO(_nDispatchID, DIID_DWebBrowserEvents2, DISPID_BEFORENAVIGATE2,OnBeforeNavigate2, &BeforeNavigate2_Info)
		SINK_ENTRY_INFO(_nDispatchID, DIID_DWebBrowserEvents2, DISPID_NAVIGATECOMPLETE2, OnNavigateComplete2, &NavigateComplete2_Info)
		SINK_ENTRY_INFO(_nDispatchID, DIID_DWebBrowserEvents2, DISPID_DOCUMENTCOMPLETE, OnEventDocumentComplete, &DocumentComplete2_Info)
		SINK_ENTRY_INFO(_nDispatchID, DIID_DWebBrowserEvents2, DISPID_TITLECHANGE, OnEventTitleChange, &TitleChange_Info)
		SINK_ENTRY_INFO(_nDispatchID, DIID_DWebBrowserEvents2, DISPID_STATUSTEXTCHANGE, OnEventStatusTextChange, &StatusTextChange_Info)
		SINK_ENTRY_INFO(_nDispatchID, DIID_DWebBrowserEvents2, DISPID_COMMANDSTATECHANGE, OnEventCommandStateChange, &CommandStateChange_Info)
		SINK_ENTRY_INFO(_nDispatchID, DIID_DWebBrowserEvents2, DISPID_NEWWINDOW3, OnNewWindow3, &NewWindow3_Info)
	END_SINK_MAP()
#ifdef _VC80X
  #pragma warning(default:4867)
#endif

	void __stdcall OnEventDocumentComplete(IDispatch* pDisp, VARIANT* URL);
	void __stdcall OnNavigateComplete2(IDispatch* pDisp, VARIANT* pvURL);
	void __stdcall OnEventTitleChange(BSTR Text);

	void __stdcall OnEventStatusTextChange(BSTR Text);
	void __stdcall OnEventCommandStateChange(long Command, VARIANT_BOOL Enable);
	void __stdcall OnBeforeNavigate2 ( 
		IDispatch* pDisp, VARIANT* URL, VARIANT* Flags,
		VARIANT* TargetFrameName, VARIANT* PostData,
		VARIANT* Headers, VARIANT_BOOL* Cancel );
	void __stdcall OnNewWindow3 (
		IDispatch **ppDisp,
		VARIANT_BOOL *Cancel,
		DWORD dwFlags,
		BSTR bstrUrlContext,
		BSTR bstrUrl );

// Message map and handlers
	BEGIN_MSG_MAP(CIECtrl)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);	
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);	
};

}//namespace DuiEngine