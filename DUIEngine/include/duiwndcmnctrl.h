//////////////////////////////////////////////////////////////////////////
//   File Name: bkwndcmnctrl.h
// Description: DuiWindow Definition
//     Creator: Zhang Xiaoxuan
//     Version: 2009.04.28 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "duiwnd.h"
#include "duitheme.h"
#include "duiwndpanel.h"
#include "duiwndnotify.h"

namespace DuiEngine{


//////////////////////////////////////////////////////////////////////////
// Spacing Control
// Only leave a space
//
// Usage: <spacing width=xx />
//
class DUI_EXP CDuiSpacing : public CDuiWindow
{
	DUIOBJ_DECLARE_CLASS_NAME(CDuiSpacing, "spacing")

public:

	// Do nothing
	void OnPaint(CDCHandle dc)
	{
	}

protected:
	DUIWIN_BEGIN_MSG_MAP()
		MSG_WM_PAINT(OnPaint)
	DUIWIN_END_MSG_MAP()
};


//////////////////////////////////////////////////////////////////////////
// Static Control
// 
// Usage: <text>inner text example</text>
// 有多行属性时，\n可以强制换行
//
class DUI_EXP CDuiStatic : public CDuiWindow
{
	DUIOBJ_DECLARE_CLASS_NAME(CDuiStatic, "text")
public:
	CDuiStatic():m_nMultiLines(0),m_nLineInter(5)
	{
		m_bMsgTransparent=TRUE;
	}
	virtual void DuiDrawText(HDC hdc,LPCTSTR pszBuf,int cchText,LPRECT pRect,UINT uFormat);

protected:
	int m_nMultiLines;
	int m_nLineInter;

	DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
		DUIWIN_INT_ATTRIBUTE("multilines", m_nMultiLines, FALSE)
		DUIWIN_INT_ATTRIBUTE("interhei", m_nLineInter, FALSE)
	DUIWIN_DECLARE_ATTRIBUTES_END()
};

//////////////////////////////////////////////////////////////////////////
// Link Control
// Only For Header Drag Test
// Usage: <link>inner text example</link>
//
class DUI_EXP CDuiLink : public CDuiWindow
{
	DUIOBJ_DECLARE_CLASS_NAME(CDuiLink, "link")

public:

protected:
	virtual void OnAttributeFinish(TiXmlElement* pXmlElem);
	virtual void DuiDrawText(HDC hdc,LPCTSTR pszBuf,int cchText,LPRECT pRect,UINT uFormat);
	virtual BOOL OnDuiSetCursor(const CPoint &pt);

	void OnLButtonDown(UINT nFlags,CPoint pt);
	void OnLButtonUp(UINT nFlags,CPoint pt);
	void OnMouseMove(UINT nFlags,CPoint pt);
	void OnMouseHover(WPARAM wParam, CPoint ptPos);

	DUIWIN_BEGIN_MSG_MAP()
		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_LBUTTONUP(OnLButtonUp)
		MSG_WM_MOUSEMOVE(OnMouseMove)
		MSG_WM_MOUSEHOVER(OnMouseHover)
	DUIWIN_END_MSG_MAP()

	CRect m_rcText;
};

//////////////////////////////////////////////////////////////////////////
// Button Control
// Use id attribute to process click event
// 
// Usage: <button id=xx>inner text example</button>
//
class DUI_EXP CDuiButton : public CDuiWindow
{
	DUIOBJ_DECLARE_CLASS_NAME(CDuiButton, "button")
public:
	CDuiButton():m_bTabStop(FALSE)
	{

	}
protected:
	BOOL m_bTabStop;

	virtual BOOL NeedRedrawWhenStateChange()
	{
		return TRUE;
	}

	virtual BOOL IsTabStop()
	{
		return m_bTabStop;
	}

	virtual UINT OnGetDuiCode()
	{
		return DUIC_WANTCHARS;
	}

	virtual void DuiDrawFocus(HDC hdc)
	{
		if(m_bTabStop) __super::DuiDrawFocus(hdc);
	}

protected:
	void OnPaint(CDCHandle dc);

	void OnLButtonDown(UINT uFlag,CPoint pt);

	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

public:
	DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
		DUIWIN_INT_ATTRIBUTE("tabstop", m_bTabStop, FALSE)
	DUIWIN_DECLARE_ATTRIBUTES_END()

	DUIWIN_BEGIN_MSG_MAP()
		MSG_WM_PAINT(OnPaint)
		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_KEYDOWN(OnKeyDown)
	DUIWIN_END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////
// Image Control
// Use src attribute specify a resource id
// 
// Usage: <img skin="skin" sub="0"/>
//
class DUI_EXP CDuiImageWnd : public CDuiWindow
{
	DUIOBJ_DECLARE_CLASS_NAME(CDuiImageWnd, "img")
public:
	CDuiImageWnd();

	~CDuiImageWnd();

	void OnPaint(CDCHandle dc);

	LRESULT OnCalcSize(BOOL bCalcValidRects, LPSIZE pSize);

	BOOL SetSkin(CDuiSkinBase *pSkin,int nSubID=0);

	BOOL SetIcon(int nSubID);
protected:
	BOOL m_bManaged;
	int m_nSubImageID;
	CDuiSkinBase *m_pSkin;
	//BOOL m_bCalc;

	DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
		DUIWIN_SKIN_ATTRIBUTE("skin", m_pSkin, TRUE)
		DUIWIN_INT_ATTRIBUTE("sub", m_nSubImageID, FALSE)		
	DUIWIN_DECLARE_ATTRIBUTES_END()

	DUIWIN_BEGIN_MSG_MAP()
		MSG_WM_PAINT(OnPaint)
		MSG_WM_CALCSIZE(OnCalcSize)
	DUIWIN_END_MSG_MAP()
};


class DUI_EXP CDuiAnimateImgWnd : public CDuiWindow
{
	DUIOBJ_DECLARE_CLASS_NAME(CDuiAnimateImgWnd, "animateimg")
public:
	CDuiAnimateImgWnd();

	void OnPaint(CDCHandle dc);

	LRESULT OnCalcSize(BOOL bCalcValidRects, LPSIZE pSize);

	void OnDuiTimer(char cID);

	void Start();
	void Stop();

	void OnDestroy();

	virtual BOOL Load(TiXmlElement* pTiXmlElem);
protected:
	DUIWIN_BEGIN_MSG_MAP()
		MSG_WM_PAINT(OnPaint)
		MSG_WM_CALCSIZE(OnCalcSize)
		MSG_WM_DUITIMER(OnDuiTimer)
		MSG_WM_DESTROY(OnDestroy)
	DUIWIN_END_MSG_MAP()

	DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
		DUIWIN_SKIN_ATTRIBUTE("skin", m_pSkin, TRUE)
		DUIWIN_UINT_ATTRIBUTE("speed", m_nSpeed, FALSE)
		DUIWIN_UINT_ATTRIBUTE("autostart", m_bAutoStart, FALSE)
	DUIWIN_DECLARE_ATTRIBUTES_END()

protected:
	CDuiSkinBase *m_pSkin;
	int			  m_nSpeed;
	int			  m_iCurFrame;
	BOOL		  m_bAutoStart;
};
//////////////////////////////////////////////////////////////////////////
// Progress Control
// Use id attribute to process click event
// 
// Usage: <progress bgskin=xx posskin=xx min=0 max=100 value=10,showpercent=0/>
//

class DUI_EXP CDuiProgress : public CDuiWindow
{
	DUIOBJ_DECLARE_CLASS_NAME(CDuiProgress, "progress")
public:
	CDuiProgress();


	LRESULT OnCalcSize(BOOL bCalcValidRects, LPSIZE pSize);

	void OnPaint(CDCHandle dc);

	BOOL SetValue(DWORD dwValue);

	DWORD GetValue();

protected:
	DWORD m_dwMinValue;
	DWORD m_dwMaxValue;
	DWORD m_dwValue;
	DWORD m_dwRight;
	BOOL m_bShowPercent;
	CDuiSkinBase *m_pSkinBg;
	CDuiSkinBase *m_pSkinPos;

	DUIWIN_BEGIN_MSG_MAP()
		MSG_WM_PAINT(OnPaint)
		MSG_WM_CALCSIZE(OnCalcSize)
	DUIWIN_END_MSG_MAP()

	DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
		DUIWIN_SKIN_ATTRIBUTE("bgskin", m_pSkinBg, TRUE)
		DUIWIN_SKIN_ATTRIBUTE("posskin", m_pSkinPos, TRUE)
		DUIWIN_DWORD_ATTRIBUTE("min", m_dwMinValue, FALSE)
		DUIWIN_DWORD_ATTRIBUTE("max", m_dwMaxValue, FALSE)
		DUIWIN_DWORD_ATTRIBUTE("value", m_dwValue, FALSE)
		DUIWIN_DWORD_ATTRIBUTE("right", m_dwRight, FALSE)
		DUIWIN_UINT_ATTRIBUTE("showpercent", m_bShowPercent, FALSE)
	DUIWIN_DECLARE_ATTRIBUTES_END()
};

//////////////////////////////////////////////////////////////////////////
// Image Button Control
// 
// Usage: <imgbtn src=xx />
//
class DUI_EXP CDuiImageBtnWnd : public CDuiImageWnd
{
	DUIOBJ_DECLARE_CLASS_NAME(CDuiImageBtnWnd, "imgbtn")
public:
	CDuiImageBtnWnd();

	virtual BOOL NeedRedrawWhenStateChange();

	void OnPaint(CDCHandle dc);

	virtual void OnStateChanged(DWORD dwOldState,DWORD dwNewState);
	void OnDuiTimer(char cTimerID);
protected:
	BOOL m_bAnimate;
	BYTE m_byAlpha;

	DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
		DUIWIN_INT_ATTRIBUTE("animate", m_bAnimate, FALSE)
	DUIWIN_DECLARE_ATTRIBUTES_END()

	DUIWIN_BEGIN_MSG_MAP()
		MSG_WM_PAINT(OnPaint)
		MSG_WM_DUITIMER(OnDuiTimer)
	DUIWIN_END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////
// Line Control
// Simple HTML "HR" tag
//
// Usage: <hr style=solid size=1 crbg=.../>
//
class DUI_EXP CDuiLine : public CDuiWindow
{
	DUIOBJ_DECLARE_CLASS_NAME(CDuiLine, "hr")

public:

	CDuiLine();

	// Do nothing
	void OnPaint(CDCHandle dc);
protected:
	int m_nPenStyle;
	int m_nLineSize;
	BOOL m_bLineShadow;
	COLORREF m_crShadow;

	DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
		DUIWIN_INT_ATTRIBUTE("size", m_nLineSize, FALSE)
		DUIWIN_UINT_ATTRIBUTE("shadow", m_bLineShadow, FALSE)
		DUIWIN_COLOR_ATTRIBUTE("crshadow", m_crShadow, FALSE)
		DUIWIN_ENUM_ATTRIBUTE("style", int, FALSE)
			DUIWIN_ENUM_VALUE("solid", PS_SOLID)             // default
			DUIWIN_ENUM_VALUE("dash", PS_DASH)               /* -------  */ 
			DUIWIN_ENUM_VALUE("dot", PS_DOT)                 /* .......  */ 
			DUIWIN_ENUM_VALUE("dashdot", PS_DASHDOT)         /* _._._._  */ 
			DUIWIN_ENUM_VALUE("dashdotdot", PS_DASHDOTDOT)   /* _.._.._  */ 
		DUIWIN_ENUM_END(m_nPenStyle)
	DUIWIN_DECLARE_ATTRIBUTES_END()

	DUIWIN_BEGIN_MSG_MAP()
		MSG_WM_PAINT(OnPaint)
	DUIWIN_END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////
// Check Box
//
// Usage: <check state=1>This is a check-box</check>
//
class DUI_EXP CDuiCheckBox : public CDuiWindow
{
	DUIOBJ_DECLARE_CLASS_NAME(CDuiCheckBox, "check")

		enum {
			CheckBoxSize = 15,
			CheckBoxSpacing = 4,
	};

public:

	CDuiCheckBox();

	void OnPaint(CDCHandle dc);
	LRESULT OnCalcSize(BOOL bCalcValidRects, LPSIZE pSize);
protected:

	CDuiSkinBase *m_pSkin;
	CDuiSkinBase *m_pFocusSkin;

	UINT _GetDrawState();

	virtual void GetClient(LPRECT pRect);

	virtual BOOL NeedRedrawWhenStateChange()
	{
		return TRUE;
	}
	
	virtual UINT OnGetDuiCode()
	{
		return DUIC_WANTCHARS;
	}

	virtual BOOL IsTabStop()
	{
		return TRUE;
	}

	virtual void DuiDrawFocus(HDC hdc);

	void OnLButtonDown(UINT nFlags, CPoint point);

	void OnLButtonUp(UINT nFlags, CPoint point);

	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
		DUIWIN_SKIN_ATTRIBUTE("skin", m_pSkin, FALSE)
		DUIWIN_SKIN_ATTRIBUTE("focusskin", m_pFocusSkin, FALSE)
		DUIWIN_UINT_ATTRIBUTE("state", m_dwState, FALSE)
	DUIWIN_DECLARE_ATTRIBUTES_END()

	DUIWIN_BEGIN_MSG_MAP()
		MSG_WM_PAINT(OnPaint)
		MSG_WM_CALCSIZE(OnCalcSize)
		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_LBUTTONUP(OnLButtonUp)
		MSG_WM_KEYDOWN(OnKeyDown)
	DUIWIN_END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////
// Icon Control
// Use src attribute specify a resource id
// 
// Usage: <icon src=xx size="16"/>
//
class DUI_EXP CDuiIconWnd : public CDuiWindow
{
	DUIOBJ_DECLARE_CLASS_NAME(CDuiIconWnd, "icon")
public:
	CDuiIconWnd();

	virtual BOOL Load(TiXmlElement* pTiXmlElem);

	void OnPaint(CDCHandle dc);

	LRESULT OnCalcSize(BOOL bCalcValidRects, LPSIZE pSize);
	HICON AttachIcon(HICON hIcon);

	void LoadIconFile( LPCWSTR lpFIleName );
protected:

	void _ReloadIcon();

	HICON m_theIcon;
	UINT m_uResID;
	UINT m_uResIDCurrent;
	int m_nSize;

	DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
		DUIWIN_UINT_ATTRIBUTE("src", m_uResID, FALSE)
		DUIWIN_INT_ATTRIBUTE("size", m_nSize, FALSE)
	DUIWIN_DECLARE_ATTRIBUTES_END()

	DUIWIN_BEGIN_MSG_MAP()
		MSG_WM_PAINT(OnPaint)
		MSG_WM_CALCSIZE(OnCalcSize)
	DUIWIN_END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////
// Radio Box
//
// Usage: <radio state=1>This is a check-box</radio>
//
class DUI_EXP CDuiRadioBox : public CDuiWindow
{
	DUIOBJ_DECLARE_CLASS_NAME(CDuiRadioBox, "radio")

		enum {
			RadioBoxSize = 15,
			RadioBoxSpacing = 4,
	};

public:

	CDuiRadioBox();


	void OnPaint(CDCHandle dc);

	LRESULT OnCalcSize(BOOL bCalcValidRects, LPSIZE pSize);

protected:

	// CDuiRadioBoxTheme m_theme;
	CDuiSkinBase *m_pSkin;
	CDuiSkinBase *m_pFocusSkin;

	int m_nState;

	UINT _GetDrawState();

	virtual BOOL NeedRedrawWhenStateChange();

	virtual void  GetClient(LPRECT pRect);

	virtual void DuiDrawFocus(HDC hdc);

	virtual BOOL IsTabStop(){return TRUE;}

	virtual UINT OnGetDuiCode()
	{
		return DUIC_WANTCHARS;
	}
	void OnLButtonDown(UINT nFlags, CPoint point);

	void OnLButtonUp(UINT nFlags, CPoint point);

	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
		DUIWIN_SKIN_ATTRIBUTE("skin", m_pSkin, FALSE)
		DUIWIN_SKIN_ATTRIBUTE("focusskin", m_pFocusSkin, FALSE)
		DUIWIN_UINT_ATTRIBUTE("check", m_nState, FALSE)
	DUIWIN_DECLARE_ATTRIBUTES_END()

	DUIWIN_BEGIN_MSG_MAP()
		MSG_WM_PAINT(OnPaint)
		MSG_WM_CALCSIZE(OnCalcSize)
		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_LBUTTONUP(OnLButtonUp)
		MSG_WM_KEYDOWN(OnKeyDown)
	DUIWIN_END_MSG_MAP()
};


class DUI_EXP CDuiToggle : public CDuiWindow
{
	DUIOBJ_DECLARE_CLASS_NAME(CDuiToggle, "togglectrl")
public:
	CDuiToggle();

	void SetToggle(BOOL bToggle,BOOL bUpdate=TRUE);

	BOOL GetToggle();
protected:
	void OnPaint(CDCHandle dc);
	void OnLButtonUp(UINT nFlags,CPoint pt);

	LRESULT OnCalcSize(BOOL bCalcValidRects, LPSIZE pSize);
	DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
		DUIWIN_INT_ATTRIBUTE("toggled", m_bToggled, TRUE)
	DUIWIN_DECLARE_ATTRIBUTES_END()

	DUIWIN_BEGIN_MSG_MAP()
		MSG_WM_PAINT(OnPaint)
		MSG_WM_LBUTTONUP(OnLButtonUp)
		MSG_WM_CALCSIZE(OnCalcSize)
	DUIWIN_END_MSG_MAP()
protected:
	BOOL m_bToggled;
};

//<group crline1="b8d5e2" crline2="999999">group text</>
class DUI_EXP CDuiGroup : public CDuiPanel
{
	DUIOBJ_DECLARE_CLASS_NAME(CDuiGroup, "group")
public:
	CDuiGroup();

protected:
	void OnPaint(CDCHandle dc);
	COLORREF m_crLine1,m_crLine2;
	int		 m_nRound;
public:
	DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
		DUIWIN_COLOR_ATTRIBUTE("crline1", m_crLine1, FALSE)
		DUIWIN_COLOR_ATTRIBUTE("crline2", m_crLine2, FALSE)
		DUIWIN_INT_ATTRIBUTE("round",m_nRound,FALSE)
	DUIWIN_DECLARE_ATTRIBUTES_END()

	DUIWIN_BEGIN_MSG_MAP()
		MSG_WM_PAINT(OnPaint)
	DUIWIN_END_MSG_MAP()
};

}//namespace DuiEngine