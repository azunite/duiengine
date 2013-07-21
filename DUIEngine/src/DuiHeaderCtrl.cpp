#include "duistd.h"
#include "DuiHeaderCtrl.h"

namespace DuiEngine
{
#define CX_HDITEM_MARGIN	2

	CDuiHeaderCtrl::CDuiHeaderCtrl(void)
		:m_bFixWidth(FALSE)
		,m_pSkinItem(NULL)
		,m_pSkinSort(NULL)
		,m_dwHitTest(-1)
		,m_bDragging(FALSE)
	{
		m_bClipClient=TRUE;
	}

	CDuiHeaderCtrl::~CDuiHeaderCtrl(void)
	{
	}

	int CDuiHeaderCtrl::InsertItem( int iItem,LPCTSTR pszText,int nWidth, DUIHDSORTFLAG stFlag,LPARAM lParam )
	{
		DUIASSERT(pszText);
		DUIASSERT(nWidth>=0);
		if(iItem==-1) iItem=m_arrItems.GetCount();
		DUIHDITEM item;
		item.mask=0xFFFFFFFF;
		item.cx=nWidth;
		item.pszText=_tcsdup(pszText);
		item.cchTextMax=_tcslen(pszText);
		item.stFlag=stFlag;
		item.state=0;
		item.lParam=lParam;
		m_arrItems.InsertAt(iItem,item);
		NotifyInvalidate();
		return iItem;
	}

	BOOL CDuiHeaderCtrl::GetItem( int iItem,DUIHDITEM *pItem )
	{
		if(iItem>=m_arrItems.GetCount()) return FALSE;
		if(pItem->mask & DUIHDI_TEXT)
		{
			 if(pItem->cchTextMax<m_arrItems[iItem].cchTextMax) return FALSE;
			 _tcscpy(pItem->pszText,m_arrItems[iItem].pszText);
		}
		if(pItem->mask & DUIHDI_WIDTH) pItem->cx=m_arrItems[iItem].cx;
		if(pItem->mask & DUIHDI_LPARAM) pItem->lParam=m_arrItems[iItem].lParam;
		if(pItem->mask & DUIHDI_SORTFLAG) pItem->stFlag=m_arrItems[iItem].stFlag;
		return TRUE;
	}

	void CDuiHeaderCtrl::OnPaint( CDCHandle dc )
	{
		DuiDCPaint duiDC;
		BeforePaint(dc,duiDC);
		CRect rcClient;
		GetClient(&rcClient);
		CRect rcItem(rcClient.left,rcClient.top,rcClient.left,rcClient.bottom);
		for(int i=0;i<m_arrItems.GetCount();i++)
		{
			rcItem.left=rcItem.right;
			rcItem.right=rcItem.left+m_arrItems[i].cx;
			DrawItem(dc,rcItem,m_arrItems.GetData()+i);
			if(rcItem.right>=rcClient.right) break;
		}
		AfterPaint(dc,duiDC);
	}

	void CDuiHeaderCtrl::DrawItem( CDCHandle dc,CRect rcItem,const LPDUIHDITEM pItem )
	{
		if(m_pSkinItem) m_pSkinItem->Draw(dc,rcItem,pItem->state);
		CGdiAlpha::DrawText(dc,pItem->pszText,pItem->cchTextMax,rcItem,m_style.GetTextAlign());
		if(pItem->stFlag==ST_NULL || !m_pSkinSort) return;
		CSize szSort=m_pSkinSort->GetSkinSize();
		CPoint ptSort;
		ptSort.y=rcItem.top+(rcItem.Height()-szSort.cy)/2;

		if(m_style.GetTextAlign()&DT_RIGHT)
			ptSort.x=rcItem.left+2;
		else
			ptSort.x=rcItem.right-szSort.cx-2;

		m_pSkinSort->Draw(dc,CRect(ptSort,szSort),pItem->stFlag==ST_UP?0:1);
	}

	BOOL CDuiHeaderCtrl::DeleteItem( int iItem )
	{
		if(iItem<0 || iItem>=m_arrItems.GetCount()) return FALSE;

		if(m_arrItems[iItem].pszText) free(m_arrItems[iItem].pszText);
		m_arrItems.RemoveAt(iItem);
		NotifyInvalidate();
		return TRUE;
	}

	void CDuiHeaderCtrl::DeleteAllItems()
	{
		for(int i=0;i<m_arrItems.GetCount();i++)
		{
			if(m_arrItems[i].pszText) free(m_arrItems[i].pszText);
		}
		m_arrItems.RemoveAll();
		NotifyInvalidate();
	}

	void CDuiHeaderCtrl::OnDestroy()
	{
		DeleteAllItems();
		__super::OnDestroy();
	}

	CRect CDuiHeaderCtrl::GetItemRect( int iItem )
	{
		CRect	rcClient;
		GetClient(&rcClient);
		CRect rcItem(rcClient.left,rcClient.top,rcClient.left,rcClient.bottom);
		for(int i=0;i<=iItem && i<m_arrItems.GetCount();i++)
		{
			rcItem.left=rcItem.right;
			rcItem.right=rcItem.left+m_arrItems[i].cx;
		}
		return rcItem;
	}

	void CDuiHeaderCtrl::RedrawItem( int iItem )
	{
		CRect rcItem=GetItemRect(iItem);
		CDCHandle dc=GetDuiDC(rcItem,OLEDC_PAINTBKGND);
		DuiDCPaint duiDC;
		BeforePaint(dc,duiDC);
		DrawItem(dc,rcItem,m_arrItems.GetData()+iItem);
		AfterPaint(dc,duiDC);
		ReleaseDuiDC(dc);
	}

	void CDuiHeaderCtrl::OnLButtonDown( UINT nFlags,CPoint pt )
	{
		if(m_bFixWidth) return;
		SetDuiCapture();
		m_bDragging=TRUE;
		m_ptClick=pt;
		m_dwHitTest=HitTest(pt);
		if(IsItemHover(m_dwHitTest))
		{
			m_arrItems[LOWORD(m_dwHitTest)].state=2;//pushdown
			RedrawItem(LOWORD(m_dwHitTest));
		}else if(m_dwHitTest!=-1)
		{
			m_nAdjItemOldWidth=m_arrItems[LOWORD(m_dwHitTest)].cx;
		}
	}

	void CDuiHeaderCtrl::OnLButtonUp( UINT nFlags,CPoint pt )
	{
		if(m_bFixWidth) return;
		if(IsItemHover(m_dwHitTest))
		{
			if(pt==m_ptClick)
			{//点击表头项
				m_arrItems[LOWORD(m_dwHitTest)].state=1;//hover
				RedrawItem(LOWORD(m_dwHitTest));
			}else
			{//拖动表头项

			}
		}else if(m_dwHitTest!=-1)
		{//调整表头宽度，发送一个调整完成消息

		}
		m_bDragging=FALSE;
		ReleaseDuiCapture();
	}

	void CDuiHeaderCtrl::OnMouseMove( UINT nFlags,CPoint pt )
	{
		if(m_bFixWidth) return;
		if(m_bDragging)
		{
			if(IsItemHover(m_dwHitTest))
			{

			}else if(m_dwHitTest!=-1)
			{//调节宽度
				int cxNew=m_nAdjItemOldWidth+pt.x-m_ptClick.x;
				if(cxNew<0) cxNew=0;
				m_arrItems[LOWORD(m_dwHitTest)].cx=cxNew;
				NotifyInvalidate();
				//发出调节宽度消息:todo
				UpdateWindow(GetContainer()->GetHostHwnd());//立即更新窗口
			}
		}else
		{
			DWORD dwHitTest=HitTest(pt);
			if(dwHitTest!=m_dwHitTest)
			{
				if(IsItemHover(m_dwHitTest))
				{
					WORD iHover=LOWORD(m_dwHitTest);
					m_arrItems[iHover].state=0;
					RedrawItem(iHover);
				}
				if(IsItemHover(dwHitTest))
				{
					WORD iHover=LOWORD(dwHitTest);
					m_arrItems[iHover].state=1;//hover
					RedrawItem(iHover);
				}
				m_dwHitTest=dwHitTest;
			}
		}
		
	}

	void CDuiHeaderCtrl::OnMouseLeave()
	{
		if(m_bFixWidth) return;
		if(IsItemHover(m_dwHitTest))
		{
			m_arrItems[LOWORD(m_dwHitTest)].state=0;
			RedrawItem(LOWORD(m_dwHitTest));
		}
		m_dwHitTest=-1;
	}

	BOOL CDuiHeaderCtrl::LoadChildren( pugi::xml_node xmlNode )
	{
		if(!xmlNode || strcmp(xmlNode.name(),"items")!=0)
			return FALSE;
		pugi::xml_node xmlItem=xmlNode.child("item");
		while(xmlItem)
		{
			DUIHDITEM item={0};
			item.mask=0xFFFFFFFF;
			CDuiStringT strTxt=DUI_CA2T(xmlItem.text().get(),CP_UTF8);
			item.pszText=_tcsdup(strTxt);
			item.cchTextMax=strTxt.GetLength();
			item.cx=xmlItem.attribute("width").as_int(50);
			item.lParam=xmlItem.attribute("userata").as_uint(0);
			item.stFlag=(DUIHDSORTFLAG)xmlItem.attribute("sortFlag").as_uint(ST_NULL);
			m_arrItems.InsertAt(m_arrItems.GetCount(),item);
			xmlItem=xmlItem.next_sibling("item");
		}
		return TRUE;
	}

	BOOL CDuiHeaderCtrl::OnDuiSetCursor( const CPoint &pt )
	{
		if(m_bFixWidth) return FALSE;
		DWORD dwHit=HitTest(pt);
		if(HIWORD(dwHit)==LOWORD(dwHit)) return FALSE;
		SetCursor(::LoadCursor(NULL,IDC_SIZEWE));
		return TRUE;
	}

	DWORD CDuiHeaderCtrl::HitTest( CPoint pt )
	{
		CRect	rcClient;
		GetClient(&rcClient);
		CRect rcItem(rcClient.left,rcClient.top,rcClient.left,rcClient.bottom);
		for(int i=0;i<m_arrItems.GetCount();i++)
		{
			rcItem.left=rcItem.right;
			rcItem.right=rcItem.left+m_arrItems[i].cx;
			if(pt.x<rcItem.left+CX_HDITEM_MARGIN)
			{
				int nLeft=i>0?i-1:0;
				return MAKELONG(nLeft,i);	
			}else if(pt.x<rcItem.right-CX_HDITEM_MARGIN)
			{
				return MAKELONG(i,i);
			}else if(pt.x<rcItem.right)
			{
				WORD nRight=(WORD)i+1;
				if(nRight>=m_arrItems.GetCount()) nRight=-1;//采用-1代表末尾
				return MAKELONG(i,nRight);
			}
		}
		return -1;
	}

}//end of namespace DuiEngine
