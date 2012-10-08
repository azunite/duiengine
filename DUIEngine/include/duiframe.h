//////////////////////////////////////////////////////////////////////////
//  Class Name: CDuiFrame
// Description: A DuiWindow Frame.
//     Creator: Huang Jianxiong
//     Version: 2011.9.1 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma  once

#include "duiwndpanel.h"

namespace DuiEngine
{

class DUI_EXP CDuiFrame : public CDuiPanel
				, public CDuiContainer
{
public:
	CDuiFrame();

	virtual LRESULT DoFrameEvent(UINT uMsg,WPARAM wParam,LPARAM lParam);


	virtual BOOL OnReleaseDuiCapture();

	virtual HDUIWND OnSetDuiCapture(HDUIWND hDuiWnd);
	virtual void OnSetDuiFocus(HDUIWND hDuiWnd);

	virtual HDUIWND GetDuiCapture();

	virtual HDUIWND GetDuiFocus();

	virtual HDUIWND GetDuiHover();

protected:
	virtual void OnFrameMouseMove(UINT uFlag,CPoint pt);

	virtual void OnFrameMouseLeave();


	virtual BOOL OnFrameSetCursor(const CPoint &pt);

	virtual void OnFrameMouseEvent(UINT uMsg,WPARAM wParam,LPARAM lParam);

	virtual void OnFrameKeyEvent(UINT uMsg,WPARAM wParam,LPARAM lParam);
	virtual void OnFrameKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	static CDuiWindow * GetNextKeyHostWnd(CDuiWindow *pCurWnd,CDuiWindow *pFirst);

protected:
	HDUIWND m_hCapture;
	HDUIWND m_hHover;
	BOOL	m_bNcHover;
	HDUIWND m_hFocus;
};

}//namespace DuiEngine

