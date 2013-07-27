#pragma once

#include <algorithm>
#include "duiwnd.h"
#include "duiwndpanel.h"
#include "DuiHeaderCtrl.h"

namespace DuiEngine
{

	typedef bool (CALLBACK *PFNLVCOMPAREEX)(LPARAM, LPARAM, LPARAM);

	template <class T >
	class CDuiListArray : public CDuiArray<T>
	{
	public:
		void Reverse()
		{
// 			std::reverse(m_aT, m_aT + m_nSize);
		}

		void Sort()
		{
// 			sort(m_aT, m_aT + m_nSize);
		}

		template< class Pred > inline
			void Sort(Pred Compare)
		{
// 			std::sort(m_aT, m_aT + m_nSize, Compare);
		}

		BOOL IsEmpty()
		{
			return (GetCount() == 0);
		}

	};

	typedef struct _DXLVSUBITEM
	{
		_DXLVSUBITEM()
		{
			nImage = 0;
			strText=NULL;
			cchTextMax=0;
		}

		LPTSTR strText;
		int		cchTextMax;
		UINT    nImage;
	} DXLVSUBITEM;

	typedef CDuiListArray<DXLVSUBITEM>   ArrSubItem;

	typedef struct _DXLVITEM
	{
		_DXLVITEM()
		{
			crText = RGB(0,0,0);
			dwData = 0;
			arSubItems=NULL;
		}

		ArrSubItem  *arSubItems;
		COLORREF    crText;
		DWORD       dwData;
	} DXLVITEM;

	//////////////////////////////////////////////////////////////////////////
	//  CDuiListCtrl
	class DUI_EXP CDuiListCtrl : public CDuiPanelEx
	{
		DUIOBJ_DECLARE_CLASS_NAME(CDuiListCtrl, "listctrl")

	public:
		CDuiListCtrl();
		virtual ~CDuiListCtrl();

		int             InsertColumn(int nIndex, LPCTSTR pszText, int nWidth, LPARAM lParam=0);
		int             InsertItem(int nItem, LPCTSTR pszText, int nImage=-1);

		BOOL            SetItemData(int nItem, DWORD dwData);
		DWORD           GetItemData(int nItem);

		BOOL            SetSubItem(int nItem, int nSubItem, LPCTSTR pszText, LPARAM lParam=0);
		BOOL            GetSubItem(int nItem, int nSubItem, DXLVITEM* plv);

		BOOL            SetItemText(int nItem, int nSubItem, LPCTSTR pszText);
		CDuiStringT         GetItemText(int nItem, int nSubItem);

		int             GetSelectedItem();
		void            SetSelectedItem(int nItem);

		int             GetItemCount();
		int             GetColumnCount();

		void            SetItemColor(int nItem, COLORREF crText);

		int             GetCountPerPage(BOOL bPartial);

		void            DeleteItem(int nItem);
		void            DeleteAllItems();

		virtual BOOL    LoadChildren(pugi::xml_node xmlNode);

		//  自动修改pt的位置为相对当前项的偏移量
		int             HitTest(const CPoint& pt);

		BOOL            SortItems(PFNLVCOMPAREEX pfnCompare);

	protected:
		int             GetTopIndex() const;

		CRect           GetItemRect(int nItem, int nSubItem=0);
		virtual void    DrawItem(CDCHandle dc, CRect rcItem, int nItem);

		void            RedrawItem(int nItem);

		void            NotifySelChange(int nOldSel, int nNewSel, UINT uMsg);

		void            OnPaint(CDCHandle dc);
		void            OnDestroy();

		bool            OnHeaderClick(CDuiWindow* pSender, LPNMHDR pNmhdr);
		bool            OnHeaderSizeChanging(CDuiWindow* pSender, LPNMHDR pNmhdr);
		bool            OnHeaderSwap(CDuiWindow* pSender, LPNMHDR pNmhdr);

		virtual BOOL    OnScroll(BOOL bVertical,UINT uCode,int nPos);
		virtual void    OnLButtonDown(UINT nFlags, CPoint pt);
		virtual void    OnLButtonUp(UINT nFlags, CPoint pt);
		virtual void    OnLButtonDblClk(UINT nFlags, CPoint pt);
		virtual void    OnSize(UINT nType, CSize size);

		CRect           GetListRect();
		void            UpdateScrollBar();
		void			UpdateHeaderCtrl();

		class CompareItem
		{
		public:
			CompareItem(PFNLVCOMPAREEX pfnCompare) : m_pfnCompare(pfnCompare) {}
			inline bool operator() (const DXLVITEM& listItem1, const DXLVITEM& listItem2)
			{
				if (m_pfnCompare != NULL)
				{
					return (m_pfnCompare(listItem1.dwData, listItem2.dwData, 0));
				}

				return true;
			}

		protected:
			PFNLVCOMPAREEX m_pfnCompare;
		};

	protected:
		int             m_nHeaderHeight;
		int             m_nItemHeight;

		//  当前选中的列表项
		int             m_nSelectItem;
		int             m_nHoverItem;
		BOOL            m_bHotTrack;

		CPoint          m_ptIcon;
		CPoint          m_ptText;

		int             m_nMargin;

		COLORREF        m_crItemBg1;
		COLORREF        m_crItemBg2;
		COLORREF        m_crItemSelBg;
		COLORREF        m_crText;
		COLORREF        m_crSelText;

		CDuiSkinBase*    m_pItemSkin;
		CDuiSkinBase*    m_pIconSkin;

	protected:
		typedef CDuiListArray<DXLVITEM> ArrLvItem;

		CDuiHeaderCtrl*  m_pHeader;
		ArrLvItem       m_arrItems;
		CPoint          m_ptOrigin;

	protected:
		DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
			DUIWIN_INT_ATTRIBUTE("headerHeight", m_nHeaderHeight, FALSE)
			DUIWIN_INT_ATTRIBUTE("itemHeight", m_nItemHeight, FALSE)
			DUIWIN_SKIN_ATTRIBUTE("itemskin", m_pItemSkin, TRUE)
			DUIWIN_SKIN_ATTRIBUTE("iconskin", m_pIconSkin, TRUE)
			DUIWIN_COLOR_ATTRIBUTE("critembg1", m_crItemBg1, FALSE)
			DUIWIN_COLOR_ATTRIBUTE("critembg2", m_crItemBg2, FALSE)
			DUIWIN_COLOR_ATTRIBUTE("critemselbg", m_crItemSelBg, FALSE)
			DUIWIN_COLOR_ATTRIBUTE("crtext", m_crText, FALSE)
			DUIWIN_COLOR_ATTRIBUTE("crseltext", m_crSelText, FALSE)
			DUIWIN_INT_ATTRIBUTE("icon-x", m_ptIcon.x, FALSE)
			DUIWIN_INT_ATTRIBUTE("icon-y", m_ptIcon.y, FALSE)
			DUIWIN_INT_ATTRIBUTE("text-x", m_ptText.x, FALSE)
			DUIWIN_INT_ATTRIBUTE("text-y", m_ptText.y, FALSE)
			DUIWIN_INT_ATTRIBUTE("hottrack", m_bHotTrack, FALSE)
		DUIWIN_DECLARE_ATTRIBUTES_END()

		DUIWIN_BEGIN_MSG_MAP()
			MSG_WM_PAINT(OnPaint)
			MSG_WM_DESTROY(OnDestroy)
			MSG_WM_SIZE(OnSize)
			MSG_WM_LBUTTONDOWN(OnLButtonDown)
			MSG_WM_LBUTTONUP(OnLButtonUp)
			MSG_WM_LBUTTONDBLCLK(OnLButtonDblClk)
		DUIWIN_END_MSG_MAP()
	};

}//end of namespace
