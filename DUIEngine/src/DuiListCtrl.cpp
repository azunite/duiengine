#include "duistd.h"
#include "DuiListCtrl.h"

namespace DuiEngine
{

	CDuiListCtrl::CDuiListCtrl(void)
		:m_nHeaderHeight(20)
		,m_nItemHeight(20)
		,m_pHeader(NULL)
	{
		m_bClipClient=TRUE;
	}

	CDuiListCtrl::~CDuiListCtrl(void)
	{
	}

	int CDuiListCtrl::InsertColumn( int iIndex,LPCTSTR pszText,int nWidth,LPARAM lParam )
	{
		DUIASSERT(m_pHeader);
		int nRet=m_pHeader->InsertItem(iIndex,pszText,nWidth,ST_NULL,lParam);
		
		//todo:update list data
		return nRet;
	}

	BOOL CDuiListCtrl::LoadChildren( pugi::xml_node xmlNode )
	{
		if(strcmp(xmlNode.name(),CDuiHeaderCtrl::GetClassName())!=0)//listctrl的子控件只能是一个header控件
			return FALSE;
		if(!__super::LoadChildren(xmlNode)) return FALSE;
		m_pHeader = (CDuiHeaderCtrl*)GetDuiWindow(GDUI_FIRSTCHILD);
		DUIASSERT(m_pHeader->IsClass(CDuiHeaderCtrl::GetClassName()));
		//设定header的pos属性
		CDuiStringA strPos;
		strPos.Format("0,0,-0,%d",m_nHeaderHeight);
		m_pHeader->SetAttribute("pos",strPos);
		m_pHeader->subscribeEvent(DUINM_HDCLICK,Subscriber(&CDuiListCtrl::OnHeaderClick,this));
		m_pHeader->subscribeEvent(DUINM_HDSIZECHANGING,Subscriber(&CDuiListCtrl::OnHeaderSizeChanging,this));
		m_pHeader->subscribeEvent(DUINM_HDSWAP,Subscriber(&CDuiListCtrl::OnHeaderSwap,this));
		return TRUE;
	}

	int CDuiListCtrl::InsertItem( int iItem,LPCTSTR pszText,LPARAM lParam )
	{
		if(iItem<0 || iItem>GetItemCount()) iItem=GetItemCount();
		DUILVITEM lvi;
		lvi.pszText=_tcsdup(pszText);
		lvi.cchTextMax=_tcslen(pszText);
		lvi.iSubItem=0;
		lvi.lParam=lParam;

		int nPos=iItem*GetColumnCount();
		m_arrItems.InsertAt(nPos,lvi,1);
		//为子项插入空数据
		for(int i=1;i<GetColumnCount();i++)
		{
			DUILVITEM lviSub;
			lviSub.iSubItem=i;
			m_arrItems.InsertAt(++nPos,lviSub);
		}
		UpdateScrollBar();
		return iItem;
	}

	BOOL CDuiListCtrl::SetSubItem( int iItem,int iSubItem,LPCTSTR pszText,LPARAM lParam )
	{
		if(iItem>=GetItemCount() || iSubItem>=GetColumnCount()) return FALSE;
		//toto:
		return TRUE;
	}

	BOOL CDuiListCtrl::GetSubItem( int iItem,int iSubItem,DUILVITEM *plv )
	{
		if(iItem>=GetItemCount() || iSubItem>=GetColumnCount()) return FALSE;
		//toto:
		return TRUE;
	}

	int CDuiListCtrl::GetItemCount()
	{
		return m_arrItems.GetCount()/GetColumnCount();
	}

	CRect CDuiListCtrl::GetListRect()
	{
		CRect rcList;
		GetClient(&rcList);
		rcList.top+=m_nHeaderHeight;
		return rcList;
	}

	//更新滚动条
	void CDuiListCtrl::UpdateScrollBar()
	{
		CSize szView;
		szView.cx=m_pHeader->GetWidth();
		szView.cy=GetItemCount()*m_nItemHeight;

		CRect rcClient;
		CDuiPanel::GetClient(&rcClient);
		rcClient.top+=m_nHeaderHeight;

		CSize size=rcClient.Size();
		m_wBarVisible=DUISB_NULL;	//关闭滚动条

		if(size.cy<szView.cy || (size.cy<szView.cy+m_nSbWid && size.cx<szView.cx))
		{
			//需要纵向滚动条
			m_wBarVisible|=DUISB_VERT;
			m_siVer.nMin=0;
			m_siVer.nMax=szView.cy-1;
			m_siVer.nPage=size.cy;

			if(size.cx<szView.cx+m_nSbWid)
			{
				//需要横向滚动条
				m_wBarVisible |= DUISB_HORZ;
				m_siVer.nPage=size.cy-m_nSbWid > 0 ? size.cy-m_nSbWid : 0;

				m_siHoz.nMin=0;
				m_siHoz.nMax=szView.cx-1;
				m_siHoz.nPage=size.cx-m_nSbWid > 0 ? size.cx-m_nSbWid : 0;
			}
			else
			{
				//不需要横向滚动条
				m_siHoz.nPage=size.cx;
				m_siHoz.nMin=0;
				m_siHoz.nMax=m_siHoz.nPage-1;
				m_siHoz.nPos=0;
				m_ptOrigin.x=0;
			}
		}
		else
		{
			//不需要纵向滚动条
			m_siVer.nPage=size.cy;
			m_siVer.nMin=0;
			m_siVer.nMax=size.cy-1;
			m_siVer.nPos=0;
			m_ptOrigin.y=0;

			if(size.cx<szView.cx)
			{
				//需要横向滚动条
				m_wBarVisible|=DUISB_HORZ;
				m_siHoz.nMin=0;
				m_siHoz.nMax=szView.cx-1;
				m_siHoz.nPage=size.cx;
			}
			else
			{
				//不需要横向滚动条
				m_siHoz.nPage=size.cx;
				m_siHoz.nMin=0;
				m_siHoz.nMax=m_siHoz.nPage-1;
				m_siHoz.nPos=0;
				m_ptOrigin.x=0;
			}
		}

		SetScrollPos(TRUE,m_siVer.nPos,TRUE);
		SetScrollPos(FALSE,m_siHoz.nPos,TRUE);

		DuiSendMessage(WM_NCCALCSIZE);//重新计算客户区及非客户区

		//根据需要调整原点位置
		if(HasScrollBar(FALSE) && m_ptOrigin.x+m_siHoz.nPage>szView.cx)
		{
			m_ptOrigin.x=szView.cx-m_siHoz.nPage;
		}
		if(HasScrollBar(TRUE) && m_ptOrigin.y+m_siVer.nPage>szView.cy)
		{
			m_ptOrigin.y=szView.cy-m_siVer.nPage;
		}
		NotifyInvalidate();
	}

	void CDuiListCtrl::DeleteItem( int iItem )
	{
		if(iItem>=0 && iItem < GetItemCount())
		{
			for(int i=0;i<GetColumnCount();i++)
			{
				DUILVITEM &lvi=m_arrItems[iItem*GetColumnCount()];
				if(lvi.pszText) free(lvi.pszText);
				m_arrItems.RemoveAt(iItem*GetColumnCount());
			}
			UpdateScrollBar();
		}
	}

	void CDuiListCtrl::DeleteAllItems()
	{
		for(int i=0;i<m_arrItems.GetCount();i++)
		{
			DUILVITEM &lvi=m_arrItems[i];
			if(lvi.pszText) free(lvi.pszText);
		}
		m_arrItems.RemoveAll();
		UpdateScrollBar();
	}


	CRect CDuiListCtrl::GetItemRect( int iItem,int iSubItem/*=0*/ )
	{
		if(!(iItem>=0 && iItem<GetItemCount() && iSubItem>=0 && iSubItem<GetColumnCount())) return CRect();

		CRect rcItem;
		rcItem.top=m_nItemHeight*iItem;
		rcItem.bottom=rcItem.top+m_nItemHeight;
		rcItem.left=0,rcItem.right=0;
		for(int iCol=0;iCol<GetColumnCount();iCol++)
		{
			DUIHDITEM hdi;
			hdi.mask=DUIHDI_WIDTH|DUIHDI_ORDER;
			m_pHeader->GetItem(iCol,&hdi);
			rcItem.left=rcItem.right;
			rcItem.right=rcItem.left+hdi.cx;
			if(hdi.iOrder==iSubItem) break;
		}
		CRect rcList=GetListRect();
		rcItem.OffsetRect(rcList.TopLeft());//变换到窗口坐标
		rcItem.OffsetRect(-m_ptOrigin);		//根据原点坐标修正
		return rcItem;
	}

	void CDuiListCtrl::DrawItem( CDCHandle dc,CRect rcItem,int iItem, const DUILVITEM *plv )
	{
		CGdiAlpha::FillRect(dc,rcItem,(HBRUSH)GetStockObject(NULL_BRUSH));
		if(plv->pszText) CGdiAlpha::DrawText(dc,plv->pszText,plv->cchTextMax,rcItem,DT_SINGLELINE|DT_VCENTER);
	}

	void CDuiListCtrl::OnPaint( CDCHandle dc )
	{
		DuiDCPaint duiDC;
		BeforePaint(dc,duiDC);
		CRect rcList=GetListRect();
		int iFirstVisible=m_ptOrigin.y/m_nItemHeight;
		int nLastVisible=(m_ptOrigin.y+rcList.Height())/m_nItemHeight;
		
		for(int i=iFirstVisible;i<=nLastVisible && i<GetItemCount();i++)
		{
			for(int j=0;j<GetColumnCount();j++)
			{
				CRect rcItem=GetItemRect(i,j);
				CRect rcVisiblePart;
				rcVisiblePart.IntersectRect(rcItem,rcList);
				if(rcVisiblePart.IsRectEmpty()) continue;
				DrawItem(dc,rcItem,i,m_arrItems.GetData()+i*GetColumnCount()+j);
			}
		}
		AfterPaint(dc,duiDC);
	}

	void CDuiListCtrl::OnDestroy()
	{
		DeleteAllItems();
		__super::OnDestroy();
	}

	int CDuiListCtrl::GetColumnCount()
	{
		return m_pHeader->GetItemCount();
	}

	BOOL CDuiListCtrl::OnScroll( BOOL bVertical,UINT uCode,int nPos )
	{
		BOOL bRet=__super::OnScroll(bVertical,uCode,nPos);
		if(bVertical)
		{
			m_ptOrigin.y=m_siVer.nPos;
		}else
		{
			m_ptOrigin.x=m_siHoz.nPos;
		}
		NotifyInvalidate();
		if(uCode==SB_THUMBTRACK)
			UpdateWindow(GetContainer()->GetHostHwnd());
		return bRet;
	}

	bool CDuiListCtrl::OnHeaderClick( CDuiWindow * pSender, LPNMHDR pNmhdr )
	{
		return true;
	}

	bool CDuiListCtrl::OnHeaderSizeChanging( CDuiWindow * pSender, LPNMHDR pNmhdr )
	{
		NotifyInvalidateRect(GetListRect());
		return true;
	}

	bool CDuiListCtrl::OnHeaderSwap( CDuiWindow * pSender, LPNMHDR pNmhdr )
	{
		NotifyInvalidateRect(GetListRect());
		return true;
	}
}//end of namespece DuiEngine