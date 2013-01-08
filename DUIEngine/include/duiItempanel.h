//////////////////////////////////////////////////////////////////////////
//  Class Name: CDuiItemPanel
// Description: A Framework wrapping frame to be used in a duiwindow.
//     Creator: Huang Jianxiong
//     Version: 2011.10.20 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma  once

#include "duiframe.h"

namespace DuiEngine
{

class CDuiItemPanel;

class DUI_EXP CDuiItemContainer
{
public:
    virtual void OnItemSetCapture(CDuiItemPanel *pItem,BOOL bCapture)=NULL;
    virtual BOOL OnItemGetRect(CDuiItemPanel *pItem,CRect &rcItem)=NULL;
};

class DUI_EXP CDuiItemPanel : public CDuiFrame
{
public:
    CDuiItemPanel(CDuiWindow *pFrameHost,TiXmlElement *pXml,CDuiItemContainer *pItemContainer=NULL);
    virtual ~CDuiItemPanel() {}

    virtual void OnFinalRelease();

    virtual LRESULT DoFrameEvent(UINT uMsg,WPARAM wParam,LPARAM lParam);

    virtual LRESULT CDuiItemPanel::OnDuiNotify(LPNMHDR pHdr);

    virtual CRect GetContainerRect();

    virtual HDC OnGetDuiDC(CRect & rc ,DWORD gdcFlags);

    virtual void OnReleaseDuiDC(HDC hdc,CRect &rc,DWORD gdcFlags);

    virtual void OnRedraw(const CRect &rc);

    virtual BOOL OnReleaseDuiCapture();

    virtual HDUIWND OnSetDuiCapture(HDUIWND hDuiWNd);
    virtual HWND GetHostHwnd();

    virtual BOOL IsTranslucent();

    virtual BOOL DuiCreateCaret(HBITMAP hBmp,int nWidth,int nHeight);

    virtual BOOL DuiShowCaret(BOOL bShow);

    virtual BOOL DuiSetCaretPos(int x,int y);

    virtual void ModifyItemState(DWORD dwStateAdd, DWORD dwStateRemove);

    virtual HDUIWND DuiGetHWNDFromPoint(POINT ptHitTest, BOOL bOnlyText);

    virtual void Draw(CDCHandle dc,const CRect & rc);

    virtual void SetSkin(CDuiSkinBase *pSkin);
    virtual void SetColor(COLORREF crBk,COLORREF crSelBk);

    virtual BOOL NeedRedrawWhenStateChange();

    CRect GetItemRect();
    void SetItemCapture(BOOL bCapture);
    void SetItemData(DWORD dwData);
    DWORD GetItemData();

    BOOL OnUpdateToolTip(HDUIWND hCurTipHost,HDUIWND &hNewTipHost,CRect &rcTip,CString &strTip);

protected:
    CDuiWindow * m_pFrmHost;
    CDuiItemContainer * m_pItemContainer;
    COLORREF m_crBk, m_crSelBk;
    DWORD		m_dwData;
};


}//namespace DuiEngine