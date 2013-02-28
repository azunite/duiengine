#include "duistd.h"
#include "activex/DuiActiveX.h"
#include "activex/DuiBStr.h"

namespace DuiEngine
{

	CDuiActiveX::CDuiActiveX() 
		: ax_host_(new CDuiAxHost(this))
		,m_clsid(CLSID_NULL)
		,m_bDelayInit(FALSE)
	{
	}

	CDuiActiveX::~CDuiActiveX() {
		delete ax_host_;
	}


	BOOL CDuiActiveX::InitActiveX()
	{
		ax_host_->CreateControl(m_clsid);
		if(m_bDelayInit)
		{
			if(ax_host_->activex_control())
			{
				ax_host_->SetRect(m_rcWindow);
				SetActiveXVisible(IsVisible(TRUE));
			}
			m_bDelayInit=FALSE;//防止重入
		}
		OnInitActiveXFinished();
		return ax_host_!=NULL;
	}

	void CDuiActiveX::OnPaint(CDCHandle dc)
	{
		ax_host_->Draw(dc, m_rcWindow);
	}

	// Overridden from CDuiAxHostDelegate:
	HWND CDuiActiveX::GetAxHostWindow() const
	{
		return m_pContainer->GetHostHwnd();
	}

	void CDuiActiveX::OnAxCreate(CDuiAxHost* host)
	{
	}

	void CDuiActiveX::OnAxInvalidate(CRect& rect)
	{
		NotifyInvalidateRect(rect);
	}


	void CDuiActiveX::OnAxSetCapture( BOOL fCapture )
	{
		if(fCapture) SetDuiCapture();
		else ReleaseDuiCapture();
	}

	int CDuiActiveX::OnCreate( LPVOID )
	{
		if(IsEqualCLSID(m_clsid,CLSID_NULL)) return 0;

		if(!m_bDelayInit) InitActiveX();
		return 0;
	}

	void CDuiActiveX::OnSize( UINT nType, CSize size )
	{
		if(ax_host_->activex_control()) ax_host_->SetRect(m_rcWindow);		
	}

	void CDuiActiveX::OnShowWindow( BOOL bShow, UINT nStatus )
	{
		__super::OnShowWindow(bShow, nStatus);

		if(bShow && m_bDelayInit) InitActiveX();//窗口显示时才初始化

		SetActiveXVisible(bShow);
	}

	LRESULT CDuiActiveX::OnMouseEvent( UINT uMsg,WPARAM wp,LPARAM lp )
	{
		if(!ax_host_->activex_control()) return 0;
		if(uMsg==WM_LBUTTONDOWN) SetDuiFocus();
		return ax_host_->OnWindowMessage(uMsg, wp, lp);
	}

	LRESULT CDuiActiveX::OnKeyEvent( UINT uMsg,WPARAM wp,LPARAM lp )
	{
		if(!ax_host_->activex_control()) return 0;
		return ax_host_->OnWindowMessage(uMsg, wp, lp);
	}

	HRESULT CDuiActiveX::OnAttrClsid(const CDuiStringA & strValue,BOOL bLoading)
	{
		CDuiStringW strValueW=DUI_CA2W(strValue,CP_UTF8);

		OLECHAR szCLSID[100] = { 0 };
		wcscpy(szCLSID,strValueW);

		HRESULT hr=E_FAIL;
		if( szCLSID[0] == L'{' ) hr=::CLSIDFromString(szCLSID, &m_clsid);
		else hr=::CLSIDFromProgID(szCLSID, &m_clsid);
		
		if(!SUCCEEDED(hr)) return S_FALSE;
		return S_OK;
	}

	void CDuiActiveX::SetActiveXVisible( BOOL bVisible )
	{
		if(ax_host_->activex_control() && !ax_host_->IsWindowless())
		{
			CDuiComPtr<IOleWindow> ole_window;
			ole_window.QueryFrom(ax_host_->activex_control());
			if(!ole_window)
			{
				return ;
			}

			HWND window = NULL;
			ole_window->GetWindow(&window);
			if(!window)
			{
				return ;
			}

			ShowWindow(window, bVisible ? SW_SHOW : SW_HIDE);
		}
	}


//////////////////////////////////////////////////////////////////////////
	CDuiFlashCtrl::CDuiFlashCtrl()
	{
		m_clsid=__uuidof(ShockwaveFlashObjects::ShockwaveFlash);
	}

	void CDuiFlashCtrl::OnAxCreate( CDuiAxHost* host )
	{
		HRESULT hr = flash_.QueryFrom(ax_host_->activex_control());
		if(flash_)
		{
			hr = flash_->put_WMode(L"Transparent");
		}
	}

	bool CDuiFlashCtrl::Play( LPCWSTR pszUrl )
	{
		if(!flash_)
		{
			return false;
		}

		flash_->Stop();
		flash_->put_Movie(CDuiBStr(pszUrl));
		flash_->Play();
		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	CDuiMediaPlayer::CDuiMediaPlayer()
	{
		m_clsid=__uuidof(WMPLib::WindowsMediaPlayer);
	}

	void CDuiMediaPlayer::OnAxCreate( CDuiAxHost* host )
	{
		HRESULT hr = wmp_.QueryFrom(ax_host_->activex_control());
		if(wmp_)
		{
			hr = wmp_->put_windowlessVideo(VARIANT_TRUE);
		}
	}

	bool CDuiMediaPlayer::Play( LPCWSTR pszUrl )
	{
		if(!wmp_)
		{
			return false;
		}

		wmp_->close();
		wmp_->put_URL(CDuiBStr(pszUrl));
		return true;
	}

}//end of namespace DuiEngine


