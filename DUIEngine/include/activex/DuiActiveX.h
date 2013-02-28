#pragma once
#include "duiwnd.h"
#include "DuiAxHost.h"

#include "flash10t.tlh"
#include "wmp.tlh"

namespace DuiEngine
{
	class DUI_EXP CDuiActiveX : public CDuiWindow, public CDuiAxHostDelegate
	{
	public:
		DUIOBJ_DECLARE_CLASS_NAME(CDuiActiveX, "activex")
		explicit CDuiActiveX();
		virtual ~CDuiActiveX();

	protected:
		int OnCreate(LPVOID);
		void OnSize(UINT nType, CSize size);
		void OnPaint(CDCHandle dc);
		LRESULT OnMouseEvent(UINT uMsg,WPARAM wp,LPARAM lp);
		LRESULT OnKeyEvent(UINT uMsg,WPARAM wp,LPARAM lp);
		void OnShowWindow(BOOL bShow, UINT nStatus);

		virtual UINT OnGetDuiCode(){return DUIC_WANTALLKEYS;}

		virtual BOOL IsTabStop(){return TRUE;}
		// Overridden from CDuiAxHostDelegate:
		virtual HWND GetAxHostWindow() const;
		virtual void OnAxCreate(CDuiAxHost* host);
		virtual void OnAxInvalidate(CRect& rect);
		virtual void OnAxSetCapture(BOOL fCapture);

		HRESULT OnAttrClsid(const CDuiStringA & strValue,BOOL bLoading);
		DUIWIN_BEGIN_MSG_MAP()
			MSG_WM_PAINT(OnPaint)
			MESSAGE_RANGE_HANDLER_EX(WM_MOUSEFIRST,WM_MOUSELAST,OnMouseEvent)
			MESSAGE_RANGE_HANDLER_EX(WM_KEYFIRST,WM_KEYLAST,OnKeyEvent)
			MSG_WM_CREATE(OnCreate)
			MSG_WM_SIZE(OnSize)
			MSG_WM_SHOWWINDOW(OnShowWindow)
		DUIWIN_END_MSG_MAP()

		DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
			DUIWIN_CUSTOM_ATTRIBUTE("clsid",OnAttrClsid)
			DUIWIN_UINT_ATTRIBUTE("delayinit",m_bDelayInit,FALSE)
		DUIWIN_DECLARE_ATTRIBUTES_END()

		virtual void OnInitActiveXFinished(){}

		BOOL InitActiveX();
		void SetActiveXVisible(BOOL bVisible);
	protected:
		CDuiAxHost * ax_host_;
		CLSID	m_clsid;
		BOOL		m_bDelayInit;
	};

	class DUI_EXP CDuiFlashCtrl : public CDuiActiveX
	{
	public:
		DUIOBJ_DECLARE_CLASS_NAME(CDuiFlashCtrl, "flash")
		CDuiFlashCtrl();

		ShockwaveFlashObjects::IShockwaveFlash* GetFlashInterface()  const
		{
			return flash_;
		}
		bool Play(LPCWSTR pszUrl);

	protected:
		virtual void OnAxCreate(CDuiAxHost* host);
		virtual void OnInitActiveXFinished(){
			if(!m_strUrl.IsEmpty() && flash_)
			{
				Play(m_strUrl);
			}
		}

		DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
			DUIWIN_WSTRING_ATTRIBUTE("url",m_strUrl,FALSE)
		DUIWIN_DECLARE_ATTRIBUTES_END()

		CDuiStringW m_strUrl;

		CDuiComPtr<ShockwaveFlashObjects::IShockwaveFlash> flash_;
	};

	class DUI_EXP CDuiMediaPlayer :public CDuiActiveX
	{
	public:
		DUIOBJ_DECLARE_CLASS_NAME(CDuiMediaPlayer, "mediaplayer")
		CDuiMediaPlayer();

		WMPLib::IWMPPlayer4* GetMediaPlayerInterface()  const
		{
			return wmp_;
		}
		bool Play(LPCWSTR pszUrl);

	protected:
		virtual void OnInitActiveXFinished(){
			if(!m_strUrl.IsEmpty() && wmp_)
			{
				Play(m_strUrl);
			}
		}

		virtual void OnAxCreate(CDuiAxHost* host);

		DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
			DUIWIN_WSTRING_ATTRIBUTE("url",m_strUrl,FALSE)
		DUIWIN_DECLARE_ATTRIBUTES_END()

		CDuiStringW m_strUrl;
		CDuiComPtr<WMPLib::IWMPPlayer4> wmp_;
	};

}//end of namespace DuiEngine
