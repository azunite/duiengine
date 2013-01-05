//////////////////////////////////////////////////////////////////////////
//  Class Name: CDuiDropDownListOwner / CDuiDropDownListBase /
//              CDuiDropDownList / CDuiDropDownListEx
// Description: The common dropdown list
//     Creator: JinHui
//     Version: 2012.12.20 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "duiwnd.h"
#include "duihostwnd.h"
#include "duilistbox.h"
#include "duilistboxex.h"
#include "duiwndcmnctrl.h"

namespace DuiEngine
{

#define IDC_DROPDOWN_LIST	100

class CDuiDropDownListBase;
class CDuiDropDownList;
class CDuiDropDownListEx;

class DUI_EXP CDuiDropDownListOwner
{
	friend class CDuiDropDownListBase;
	friend class CDuiDropDownList;
	friend class CDuiDropDownListEx;

public:
	CDuiDropDownListOwner() {}
	virtual ~CDuiDropDownListOwner(){}

protected:

	virtual HWND GetHostHwnd() = 0;

	virtual CDuiWindow* GetWindow() = 0;

	virtual int  GetListItemCount() = 0;

	virtual LPCTSTR	GetListItemText(int nItem) = 0;

	virtual int GetListItemIcon(int nItem) = 0;

	virtual DWORD GetListItemData(int nItem) { return 0; }

	virtual int GetListCurSel() { return -1; }

	virtual int GetAnimateTime() { return 200; }

	virtual void OnDropDownListClose() = 0;	
};

///////////////////////////////////////////////////////////////////////////////////////////

class DUI_EXP CDuiDropDownListBase : public CDuiHostWnd
					   , public CDuiMessageFilter
{
public:
	CDuiDropDownListBase(CDuiDropDownListOwner* pOwner,int nDropHeight);
	virtual ~CDuiDropDownListBase(){}
	
	virtual void DeleteItem(int iItem) = 0;
	virtual void UpdateItems(const CRect * prcOwner=NULL)=0;

protected:
	int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnKillFocus(HWND wndFocus);
	void OnClose();

	virtual void CreateListBox(TiXmlElement *pXmlTemplate) = 0;
	virtual void OnFinalMessage(HWND);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	BOOL FixPosition(const CRect * prcOwner, int nDropHeight);

protected:

	int			m_nDropHeight;
	CDuiDropDownListOwner* m_pOwner;

	BEGIN_MSG_MAP_EX(CDuiDropDownList)
		MSG_WM_CREATE(OnCreate)
		MSG_WM_KILLFOCUS(OnKillFocus)
		MSG_WM_CLOSE(OnClose)
		CHAIN_MSG_MAP(CDuiHostWnd)
	END_MSG_MAP()
};

///////////////////////////////////////////////////////////////////////////////////////////

class DUI_EXP CDuiDropDownList : public CDuiDropDownListBase
{
public:
	CDuiDropDownList(CDuiDropDownListOwner* pOwner,int nDropHeight);
	virtual ~CDuiDropDownList(){}

	virtual void DeleteItem(int iItem);
	virtual void UpdateItems(const CRect * prcOwner=NULL);

protected:

	virtual void CreateListBox(TiXmlElement *pXmlTemplate);

	CDuiListBox *m_pListBox;
};

///////////////////////////////////////////////////////////////////////////////////////////

class DUI_EXP CDuiDropDownListEx : public CDuiDropDownListBase
{
public:
	CDuiDropDownListEx(CDuiDropDownListOwner* pOwner,int nDropHeight);
	virtual ~CDuiDropDownListEx(){}

	virtual void DeleteItem(int iItem);
	virtual void UpdateItems(const CRect * prcOwner=NULL);

protected:

	virtual void CreateListBox(TiXmlElement *pXmlTemplate);

	int m_nTextID;
	int m_nIconID;
	CDuiListBoxEx *m_pListBox;
};

}//namespace