#pragma once
#include "duiwndpanel.h"
#include "DuiHeaderCtrl.h"
#include "wtl.mini/duicoll.h"

namespace DuiEngine
{
	struct DUI_EXP DUILVITEM
	{
		DUILVITEM()
		{
			mask=0xFFFFFFF;
			iSubItem=0;
			pszText=NULL;
			cchTextMax=0;
			iImage=-1;
			lParam=0;
		}
		UINT mask; 
		int iSubItem; 
		UINT state; 
		LPTSTR pszText; 
		int cchTextMax; 
		int iImage; 
		LPARAM lParam;
	};


	class DUI_EXP CDuiListCtrl : public CDuiPanelEx
	{
		DUIOBJ_DECLARE_CLASS_NAME(CDuiListCtrl, "listctrl")
	public:
		CDuiListCtrl(void);
		~CDuiListCtrl(void);

		int InsertColumn(int iIndex,LPCTSTR pszText,int nWidth,LPARAM lParam);
		int InsertItem(int iItem,LPCTSTR pszText,LPARAM lParam);
		BOOL SetSubItem(int iItem,int iSubItem,LPCTSTR pszText,LPARAM lParam);
		BOOL GetSubItem(int iItem,int iSubItem,DUILVITEM *plv);

		int GetItemCount();
		int GetColumnCount();

		void DeleteItem(int iItem);
		void DeleteAllItems();

		virtual BOOL LoadChildren(pugi::xml_node xmlNode);

		DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
			DUIWIN_INT_ATTRIBUTE("headerHeight",m_nHeaderHeight,FALSE)
			DUIWIN_INT_ATTRIBUTE("itemHeight",m_nItemHeight,FALSE)
		DUIWIN_DECLARE_ATTRIBUTES_END()
	protected:
		CRect GetItemRect(int iItem,int iSubItem=0);
		virtual void DrawItem(CDCHandle dc,CRect rcItem,int iItem, const DUILVITEM *plv);
		void OnPaint(CDCHandle dc);
		void OnDestroy();

		bool OnHeaderClick( CDuiWindow * pSender, LPNMHDR pNmhdr );
		bool OnHeaderSizeChanging( CDuiWindow * pSender, LPNMHDR pNmhdr );
		bool OnHeaderSwap( CDuiWindow * pSender, LPNMHDR pNmhdr );
		
		virtual BOOL OnScroll(BOOL bVertical,UINT uCode,int nPos);

		DUIWIN_BEGIN_MSG_MAP()
			MSG_WM_PAINT(OnPaint)
			MSG_WM_DESTROY(OnDestroy)
		DUIWIN_END_MSG_MAP()

		CRect GetListRect();
		void UpdateScrollBar();
		int		m_nHeaderHeight;
		int		m_nItemHeight;
		
		CDuiHeaderCtrl	*m_pHeader;
		

		CDuiArray<DUILVITEM> m_arrItems;
		CPoint	m_ptOrigin;//视口原点
	};
}
