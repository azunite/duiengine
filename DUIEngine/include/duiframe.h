//////////////////////////////////////////////////////////////////////////
//  Class Name: CDuiFrame
// Description: A DuiWindow Frame.
//     Creator: Huang Jianxiong
//     Version: 2011.9.1 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma  once

#include "duiwndpanel.h"
#include "DuiFrameDropTarget.h"
#include "FocusManager.h"

namespace DuiEngine
{

class DUI_EXP CDuiFrame : public CDuiPanel
    , public CDuiContainer
{
public:
    CDuiFrame();

	virtual BOOL RegisterDragDrop(HDUIWND hDuiWnd,IDropTarget *pDropTarget);

	virtual BOOL RevokeDragDrop(HDUIWND hDuiWnd);

	IDropTarget * GetDropTarget(){return &m_dropTarget;}

	CFocusManager * GetFocusManager() {return &m_focusMgr;}

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

	virtual void OnActivate(UINT nState);

protected:
    HDUIWND m_hCapture;
	CPoint	m_ptSave;
    HDUIWND m_hHover;
    BOOL	m_bNcHover;

	CFocusManager m_focusMgr;

	CDuiFrameDropTarget m_dropTarget;
};

}//namespace DuiEngine

