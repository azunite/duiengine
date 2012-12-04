#pragma once
#include "duiwnd.h"
#include "DuiRichEdit.h"
#include "duiwndcmnctrl.h"
#include "duihostwnd.h"
#include "duilistctrl.h"
#include <vector>

namespace DuiEngine
{

#define IDC_LIST	100

struct CBITEM
{
	CString strText;
	int iIcon;
	DWORD dwData;
};

class CDuiComboBox;
class CComboList : public CDuiHostWnd
				 , public CDuiMessageFilter
{
public:
	CComboList(CDuiComboBox* pOwner,int nDropHeight);
	void DeleteItem(int iItem);
	void UpdateItems(const CRect * prcOwner=NULL);
protected:
	int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnKillFocus(HWND wndFocus);
	void OnClose();

	virtual void OnFinalMessage(HWND);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	BEGIN_MSG_MAP_EX(CComboList)
		MSG_WM_CREATE(OnCreate)
		MSG_WM_KILLFOCUS(OnKillFocus)
		MSG_WM_CLOSE(OnClose)
		CHAIN_MSG_MAP(CDuiHostWnd)
	END_MSG_MAP()
	CDuiListBox *m_pListBox;
	CDuiComboBox* m_pOwner;
	int			 m_nTextID;
	int			 m_nIconID;
	int			m_nDropHeight;
};

class CComboEdit:public CDuiRichEdit
{
public:
	CComboEdit(CDuiComboBox *pOwner);

protected:
	void OnMouseHover(WPARAM wParam, CPoint ptPos);
	
	void OnMouseLeave();

	virtual LRESULT DuiNotify(LPNMHDR pnms);

	DUIWIN_BEGIN_MSG_MAP()
		MSG_WM_MOUSEHOVER(OnMouseHover)
		MSG_WM_MOUSELEAVE(OnMouseLeave)
	DUIWIN_END_MSG_MAP()
};

class DUI_EXP CDuiComboBox :
	public CDuiWindow
{
	friend class CComboList;
	DUIOBJ_DECLARE_CLASS_NAME(CDuiComboBox, "combobox")
public:
	CDuiComboBox(void);
	~CDuiComboBox(void);

	int SetCurSel(int iSel);

	int GetCurSel();

	BOOL GetItemInfo(int iItem,CBITEM *pCbItem);

	int InsertItem(int iPos,LPCTSTR pszText,int iIcon,DWORD dwData);

	BOOL DeleteItem(int iItem);

	int GetWindowText(LPTSTR lpString, int nMaxCount );
	
	BOOL SetWindowText(CString strText);

	virtual LRESULT DuiNotify(LPNMHDR pnms);

	DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
		DUIWIN_INT_ATTRIBUTE("dropdown", m_bDropdown, FALSE)
		DUIWIN_INT_ATTRIBUTE("dropheight", m_nDropHeight, FALSE)
		DUIWIN_INT_ATTRIBUTE("cursel", m_iCurSel, FALSE)
		DUIWIN_SKIN_ATTRIBUTE("btnskin", m_pSkinBtn, FALSE)
	DUIWIN_DECLARE_ATTRIBUTES_END()
protected:
	void GetDropBtnRect(LPRECT prc);
	virtual BOOL LoadChildren(TiXmlElement* pTiXmlChildElem);
	
	void OnPaint(CDCHandle dc);
	void OnLButtonDown(UINT nFlags,CPoint pt);
	void OnLButtonUp(UINT nFlags,CPoint pt);
	void OnMouseMove(UINT nFlags,CPoint pt);
	void OnMouseLeave();

	void OnListClose();
	DUIWIN_BEGIN_MSG_MAP()
		MSG_WM_PAINT(OnPaint)
		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_LBUTTONUP(OnLButtonUp)
		MSG_WM_MOUSEMOVE(OnMouseMove)
		MSG_WM_MOUSELEAVE(OnMouseLeave)
	DUIWIN_END_MSG_MAP()
	CDuiRichEdit *m_pEdit;
	CComboList   *m_pListBox;
	TiXmlElement * m_pXmlListStyle;
	CDuiSkinBase *m_pSkinBtn;
	DWORD		  m_dwBtnState;
	
	BOOL m_bDropdown;
	int  m_nDropHeight;
	int		m_iCurSel;

	std::vector<CBITEM> m_arrCbItem;
};

}//namespace