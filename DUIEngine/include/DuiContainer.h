#pragma once


namespace DuiEngine
{

class DUI_EXP CDuiContainer
{
    friend class CDuiWindow;
public:
	virtual BOOL RegisterDragDrop(HDUIWND hDuiWnd,IDropTarget *pDropTarget)=NULL;

	virtual BOOL RevokeDragDrop(HDUIWND hDuiWnd)=NULL;

    virtual LRESULT OnDuiNotify(LPNMHDR pHdr)=NULL;

    virtual HWND GetHostHwnd()=NULL;

    virtual BOOL IsTranslucent()=NULL;

    virtual CRect GetContainerRect()=NULL;

    virtual HDC OnGetDuiDC(CRect & rc,DWORD gdcFlags)=NULL;

    virtual void OnReleaseDuiDC(HDC hdc,CRect &rc,DWORD gdcFlags)=NULL;

    virtual void OnRedraw(const CRect &rc)=NULL;

    virtual HDUIWND GetDuiCapture()=NULL;

    virtual BOOL OnReleaseDuiCapture()=NULL;

    virtual HDUIWND OnSetDuiCapture(HDUIWND hDuiWnd)=NULL;

    virtual void OnSetDuiFocus(HDUIWND hDuiWnd)=NULL;

    virtual HDUIWND GetDuiHover()=NULL;

    virtual HDUIWND GetDuiFocus()=NULL;

    virtual BOOL DuiCreateCaret(HBITMAP hBmp,int nWidth,int nHeight)=NULL;

    virtual BOOL DuiShowCaret(BOOL bShow)=NULL;

    virtual BOOL DuiSetCaretPos(int x,int y)=NULL;
};


}//namespace DuiEngine

