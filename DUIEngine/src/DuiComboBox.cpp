#include "duistd.h"
#include "DuiComboBox.h"


namespace DuiEngine
{

#define DEF_ITEMHEI	20

CComboList::CComboList(CDuiComboBox* pOwner,int nDropHeight)
:m_pOwner(pOwner)
,m_nTextID(-1)
,m_nIconID(-1)
,m_nDropHeight(nDropHeight)
{
	MsgFilterRegister(pOwner->GetContainer()->GetHostHwnd());
}

void CComboList::DeleteItem( int iItem )
{
	m_pListBox->DeleteItem(iItem);
}

void CComboList::UpdateItems(const CRect * prcOwner)
{
	int nItems=m_pOwner->m_arrCbItem.size();
	BOOL bShowTop=FALSE;
	if(prcOwner)
	{
		int nDropHeight=m_nDropHeight;
		if(nItems!=0 && nItems*m_pListBox->GetItemHeight()+m_pListBox->GetStyle().m_nMarginY*2<m_nDropHeight)
		{
			nDropHeight=nItems*m_pListBox->GetItemHeight()+m_pListBox->GetStyle().m_nMarginY*2;
		}

		MONITORINFO oMonitor = {0};
		oMonitor.cbSize = sizeof(oMonitor);
		::GetMonitorInfo(::MonitorFromWindow(GetContainer()->GetHostHwnd(), MONITOR_DEFAULTTOPRIMARY), &oMonitor);

		if(prcOwner->bottom+nDropHeight>oMonitor.rcWork.bottom)
		{
			bShowTop=TRUE;
			MoveWindow(prcOwner->left,prcOwner->top-nDropHeight,prcOwner->Width(),nDropHeight,FALSE);
		}else
		{
			MoveWindow(prcOwner->left,prcOwner->bottom,prcOwner->Width(),nDropHeight,FALSE);
		}
	}
	m_pListBox->SetItemCount(NULL,nItems);
	for(int i=0;i<nItems;i++)
	{
		CDuiPanel *pPanel=m_pListBox->GetDuiItem(i);
		if(m_nTextID!=-1)
		{
			CDuiWindow *pText=pPanel->FindChildByCmdID(m_nTextID);
			if(pText) pText->SetInnerText(m_pOwner->m_arrCbItem[i].strText);
		}
		if(m_nIconID!=-1)
		{
			CDuiImageWnd *pIcon=(CDuiImageWnd*)pPanel->FindChildByCmdID(m_nIconID);
			if(pIcon && pIcon->IsClass(CDuiImageWnd::GetClassName()))
				pIcon->SetIcon(m_pOwner->m_arrCbItem[i].iIcon);
		}
	}
	m_pListBox->SetCurSel(m_pOwner->m_iCurSel);
	m_pListBox->EnsureVisible(m_pOwner->m_iCurSel);	
	if(prcOwner)
	{
		AnimateWindow(m_hWnd,200,AW_SLIDE|AW_ACTIVATE|(bShowTop?AW_VER_NEGATIVE:AW_VER_POSITIVE));
	}
}

int CComboList::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	int nRet=__super::OnCreate(lpCreateStruct);
	if(nRet!=0) return nRet;

	m_pListBox=new CDuiListBox;
	InsertChild(m_pListBox);
	m_pListBox->SetCmdID(IDC_LIST);

	TiXmlElement *pXmlTemplate=(TiXmlElement *)lpCreateStruct->lpCreateParams;
	DUIASSERT(pXmlTemplate);
	pXmlTemplate->Attribute("id_text",&m_nTextID);
	pXmlTemplate->Attribute("id_icon",&m_nIconID);

	m_pListBox->Load(pXmlTemplate);
	m_pListBox->SetAttribute("pos", "0,0,-0,-0", TRUE);
	m_pListBox->SetAttribute("hottrack","1",TRUE);
	CRect rcClient;
	GetClientRect(&rcClient);
	Move(&rcClient);
	m_pListBox->SetOwner(m_pOwner);//chain notify message to combobox
	return 0;
}

void CComboList::OnFinalMessage(HWND)
{
	MsgFilterUnregister(m_pOwner->GetContainer()->GetHostHwnd());
	m_pOwner->m_pListBox=NULL;
	delete this;
}

void CComboList::OnKillFocus( HWND wndFocus )
{
	PostMessage(WM_CLOSE);
}

void CComboList::OnClose()
{
	DefWindowProc();
	m_pOwner->OnListClose();
}

BOOL CComboList::PreTranslateMessage( MSG* pMsg )
{
	return _PreTranslateMessage(pMsg);
}
//////////////////////////////////////////////////////////////////////////
// CComboEdit
CComboEdit::CComboEdit( CDuiComboBox *pOwner ) :m_pOwner(pOwner)
{

}

void CComboEdit::OnMouseHover( WPARAM wParam, CPoint ptPos )
{
	__super::OnMouseHover(wParam,ptPos);
	m_pOwner->DuiSendMessage(WM_MOUSEHOVER,wParam,MAKELPARAM(ptPos.x,ptPos.y));
}

void CComboEdit::OnMouseLeave()
{
	__super::OnMouseLeave();
	m_pOwner->DuiSendMessage(WM_MOUSELEAVE);
}

//////////////////////////////////////////////////////////////////////////
// CDuiComboBox
CDuiComboBox::CDuiComboBox(void)
:m_pSkinBtn(DuiSkinPool::getSingleton().GetSkin("comboboxbtn"))
,m_pEdit(NULL)
,m_pXmlListStyle(NULL)
,m_iCurSel(-1)
,m_bDropdown(TRUE)
,m_nDropHeight(200)
,m_dwBtnState(DuiWndState_Normal)
,m_pListBox(NULL)
{
}

CDuiComboBox::~CDuiComboBox(void)
{
	if(m_pXmlListStyle) delete m_pXmlListStyle;
}


BOOL CDuiComboBox::LoadChildren( TiXmlElement* pTiXmlChildElem )
{
	BOOL bRet=FALSE;
	TiXmlNode *pTiXmlParent=pTiXmlChildElem->Parent();
	DUIASSERT(pTiXmlParent);
	//初始化列表数据
	TiXmlElement *pTiXmlItems=pTiXmlParent->FirstChildElement("items");
	if(pTiXmlItems)
	{
		TiXmlElement *pItem=pTiXmlItems->FirstChildElement("item");
		while(pItem)
		{
			CBITEM cbi={_T(""),0,0};
			cbi.strText=CA2T(pItem->Attribute("text"),CP_UTF8);
			pItem->Attribute("icon",&cbi.iIcon);
			const char *pszData=pItem->Attribute("data");
			if(pszData) cbi.dwData=atoi(pszData);
			m_arrCbItem.push_back(cbi);
			pItem=pItem->NextSiblingElement("item");
		}
		bRet=TRUE;
	}
	//获取列表模板
	TiXmlElement *pTiListStyle=pTiXmlParent->FirstChildElement("liststyle");
	if(pTiListStyle)
	{
		m_pXmlListStyle=pTiListStyle->Clone()->ToElement();
	}

	DUIASSERT(m_pSkinBtn);
	//创建edit对象
	if(!m_bDropdown)
	{
		SIZE szBtn=m_pSkinBtn->GetSkinSize();
		m_pEdit=new CComboEdit(this);
		InsertChild(m_pEdit);
		TiXmlElement *pTiEditStyle=pTiXmlParent->FirstChildElement("editstyle");
		if(pTiEditStyle)
			m_pEdit->Load(pTiEditStyle);
		else
			m_pEdit->DuiSendMessage(WM_CREATE);
		CStringA strPos;
		strPos.Format("0,0,-%d,-0",szBtn.cx);
		m_pEdit->SetAttribute("pos",strPos,TRUE);
	}
	if(m_iCurSel!=-1 && m_iCurSel>=m_arrCbItem.size())
		m_iCurSel=-1;
	int iSel=m_iCurSel;
	m_iCurSel=-1;
	SetCurSel(iSel);
	return bRet;
}


void CDuiComboBox::GetDropBtnRect(LPRECT prc)
{
	SIZE szBtn=m_pSkinBtn->GetSkinSize();
	GetClient(prc);
	prc->left=prc->right-szBtn.cx;
}

void CDuiComboBox::OnPaint( CDCHandle dc )
{

	if(m_iCurSel != -1 && m_pEdit==NULL)
	{
		DuiDCPaint DuiDC;

		BeforePaint(dc, DuiDC);
		CRect rcClient;
		GetClient(&rcClient);
		SIZE szBtn=m_pSkinBtn->GetSkinSize();
		rcClient.right-=szBtn.cx;

		DuiDrawText(dc,m_strInnerText, m_strInnerText.GetLength(), rcClient, DT_LEFT|DT_VCENTER|DT_SINGLELINE|(m_style.m_bDotted?DT_WORD_ELLIPSIS:0));

		AfterPaint(dc, DuiDC);
	}
	CRect rcBtn;
	GetDropBtnRect(&rcBtn);
	m_pSkinBtn->Draw(dc,rcBtn,IIF_STATE3(m_dwBtnState,DuiWndState_Normal,DuiWndState_Hover,DuiWndState_PushDown));
}

void CDuiComboBox::OnLButtonDown( UINT nFlags,CPoint pt )
{
	if(m_dwBtnState==DuiWndState_PushDown) return;
	m_dwBtnState=DuiWndState_PushDown;
	CRect rcBtn;
	GetDropBtnRect(&rcBtn);
	NotifyInvalidateRect(rcBtn);
	//todo:show list window
	CRect rc;
	GetRect(&rc);
	CSimpleWnd wnd(GetContainer()->GetHostHwnd());
	wnd.ClientToScreen(&rc);

	m_pListBox=new CComboList(this,m_nDropHeight);

	m_pListBox->Create(GetContainer()->GetHostHwnd(),NULL,WS_POPUP,WS_EX_TOOLWINDOW,0,0,0,0,m_pXmlListStyle);
 	m_pListBox->UpdateItems(&rc);
}

void CDuiComboBox::OnLButtonUp(UINT nFlags,CPoint pt)
{
}

void CDuiComboBox::OnMouseMove( UINT nFlags,CPoint pt )
{
	if(m_dwBtnState==DuiWndState_PushDown) return;

	__super::OnMouseHover(nFlags,pt);
	CRect rcBtn;
	GetDropBtnRect(&rcBtn);
	if(rcBtn.PtInRect(pt))
	{
		m_dwBtnState=DuiWndState_Hover;
		NotifyInvalidateRect(rcBtn);
	}else if(m_dwBtnState==DuiWndState_Hover)
	{
		m_dwBtnState=DuiWndState_Normal;
		NotifyInvalidateRect(rcBtn);
	}
}

void CDuiComboBox::OnMouseLeave()
{
	if(m_dwBtnState==DuiWndState_PushDown) return;

	if(GetState()&DuiWndState_Hover) 
		__super::OnMouseLeave();
	if(m_dwBtnState==DuiWndState_Hover)
	{
		m_dwBtnState=DuiWndState_Normal;
		CRect rcBtn;
		GetDropBtnRect(&rcBtn);
		NotifyInvalidateRect(rcBtn);
	}
}

LRESULT CDuiComboBox::DuiNotify(LPNMHDR pnms)
{
	LRESULT lRet=0;
	if(pnms->idFrom==IDC_LIST)
	{
		pnms->idFrom=GetCmdID();
		if(pnms->code==DUINM_LBSELCHANGED && m_pListBox)
		{//select item changed
			DUINMLBSELCHANGE *pnmclk = (DUINMLBSELCHANGE *)pnms;
			if(pnmclk->uMsg==WM_LBUTTONUP)
			{
				m_pListBox->PostMessage(WM_CLOSE);
				SetCurSel(pnmclk->nNewSel);
				lRet=__super::DuiNotify(pnms);
			}
		}else
		{
			lRet=__super::DuiNotify(pnms);
		}
		pnms->idFrom=IDC_LIST;
	}else
	{
		lRet=__super::DuiNotify(pnms);
	}
	return lRet;
}

int CDuiComboBox::SetCurSel( int iSel )
{
	if(iSel!=m_iCurSel)
	{
		if(iSel==-1)
		{
			m_iCurSel=-1;
			if(m_pEdit)
				m_pEdit->SetWindowText(NULL);
			else
				SetInnerText(NULL);
		}else
		{
			if(iSel>=0 && iSel<m_arrCbItem.size())
			{
				m_iCurSel=iSel;
				if(m_pEdit)
					m_pEdit->SetWindowText(m_arrCbItem[iSel].strText);
				else
					SetInnerText(m_arrCbItem[iSel].strText);
			}else
			{
				return CB_ERR;
			}
		}
		NotifyInvalidate();
	}
	return m_iCurSel;
}

int CDuiComboBox::GetCurSel()
{
	return m_iCurSel;
}

BOOL CDuiComboBox::GetItemInfo( int iItem,CBITEM *pCbItem )
{
	if(iItem<0 || iItem>=m_arrCbItem.size()) return FALSE;
	*pCbItem=m_arrCbItem[iItem];
	return TRUE;
}

int CDuiComboBox::InsertItem(int iPos, LPCTSTR pszText,int iIcon,DWORD dwData )
{
	CBITEM cbi={pszText,iIcon,dwData};
	if(iPos<0 || iPos>m_arrCbItem.size()) iPos=m_arrCbItem.size();
	m_arrCbItem.insert(m_arrCbItem.begin()+iPos,cbi);
	if(m_pListBox)
	{//update list box
		m_pListBox->UpdateItems();
	}
	return iPos;
}

BOOL CDuiComboBox::DeleteItem( int iItem )
{
	if(iItem<0 || iItem>=m_arrCbItem.size()) return FALSE;
	m_arrCbItem.erase(m_arrCbItem.begin()+iItem);
	if(m_pListBox)
	{//update list box
		m_pListBox->DeleteItem(iItem);
	}
	return TRUE;
}

int CDuiComboBox::GetWindowText( LPTSTR lpString, int nMaxCount )
{
	if(m_bDropdown)
	{
		if(m_iCurSel==-1) return 0;
		else
		{
			int nRet=m_arrCbItem[m_iCurSel].strText.GetLength();
			if(nRet>nMaxCount-1) nRet=nMaxCount-1;
			_tcsncpy(lpString,m_arrCbItem[m_iCurSel].strText,nRet);
			lpString[nRet]=0;
			return nRet;
		}
	}else
	{
		DUIASSERT(m_pEdit);
		return m_pEdit->GetWindowText(lpString,nMaxCount);
	}
}

BOOL CDuiComboBox::SetWindowText(CString strText)
{
	if(m_bDropdown) return FALSE;
	return m_pEdit->SetWindowText(strText);
}

void CDuiComboBox::OnListClose()
{
	m_dwBtnState=DuiWndState_Normal;
	HDUIWND hHover=GetContainer()->GetDuiHover();
	if(GetDuiHwnd()!=hHover && (!m_pEdit || hHover!=m_pEdit->GetDuiHwnd()))
	{
		ModifyState(0,DuiWndState_Hover);
	}
	NotifyInvalidate();
}


}//namespace DuiEngine

