#pragma once

namespace DuiEngine{

typedef CWinTraits<WS_POPUP | WS_CLIPCHILDREN , WS_EX_TOOLWINDOW|WS_EX_NOACTIVATE> CDuiTipCtrlTraits;

class CDuiTipCtrl 
	: public ATL::CWindowImpl<CDuiTipCtrl, ATL::CWindow, CDuiTipCtrlTraits>
{
public:
	DECLARE_WND_CLASS_EX(_T("CDuiTipCtrl"), CS_HREDRAW | CS_VREDRAW, COLOR_WINDOW)
	
	CDuiTipCtrl(void);
	~CDuiTipCtrl(void);

	BOOL Create(HWND hOwner);

	void RelayEvent(const MSG *pMsg);
	void UpdateTip(CRect rc,LPCSTR pszTip,BOOL bText=TRUE);
	void SetDelayTime(DWORD dwType,UINT iTime);

	void ShowTip(BOOL bShow);

	DWORD	m_dwHostID;
protected:
	void OnTimer(UINT_PTR idEvent);
	void OnPaint(CDCHandle dc);

	BEGIN_MSG_MAP_EX(CDuiTipCtrl)
		MSG_WM_PAINT(OnPaint)
		MSG_WM_TIMER(OnTimer)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()

protected:
	int			m_nDelay;
	int			m_nShowSpan;
	CStringA	m_strTip;
	BOOL		m_bTextTip;
	CRect		m_rcTarget;
	CFont		m_font;
};

}//namespace DuiEngine