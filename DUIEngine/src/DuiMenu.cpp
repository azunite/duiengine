#include "duistd.h"
#include "DuiMenu.h"
#include "DuiSystem.h"
#include "gdialpha.h"
#include "mybuffer.h"

namespace DuiEngine{

CDuiMenuAttr::CDuiMenuAttr()
:m_pItemSkin(NULL)
,m_pIconSkin(NULL)
,m_pSepSkin(NULL)
,m_pCheckSkin(NULL)
,m_hFont(0)
,m_nItemHei(0)
,m_nIconMargin(2)
,m_nTextMargin(5)
,m_szIcon(CX_ICON,CY_ICON)
{
	m_crTxtNormal=GetSysColor(COLOR_MENUTEXT);
	m_crTxtSel=GetSysColor(COLOR_HIGHLIGHTTEXT);
	m_crTxtGray=GetSysColor(COLOR_GRAYTEXT);
}

void CDuiMenuAttr::OnAttributeFinish( TiXmlElement* pXmlElem )
{
	DUIASSERT(m_pItemSkin);
	if(m_nItemHei==0) m_nItemHei=m_pItemSkin->GetSkinSize().cy;
	if(!m_hFont) m_hFont=DuiFontPool::getSingleton().GetFont(DUIF_DEFAULTFONT);
}
//////////////////////////////////////////////////////////////////////////

CDuiMenuODWnd::CDuiMenuODWnd()
{

}

void CDuiMenuODWnd::OnInitMenu( HMENU menu )
{
	::SendMessage(GetParent(m_hWnd),WM_INITMENU,(WPARAM)menu,0);
}

void CDuiMenuODWnd::OnInitMenuPopup( HMENU menuPopup, UINT nIndex, BOOL bSysMenu )
{
	::SendMessage(GetParent(m_hWnd),WM_INITMENUPOPUP,(WPARAM)menuPopup,MAKELPARAM(nIndex,bSysMenu));
}

void CDuiMenuODWnd::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
	CRect rcItem=lpDrawItemStruct->rcItem;
	DuiMenuItemData *pdmmi=(DuiMenuItemData*)lpDrawItemStruct->itemData;

	CDCHandle dc(lpDrawItemStruct->hDC);
	CDCHandle dcMem;
	dcMem.CreateCompatibleDC(dc);
	CBitmap	  bmp=CGdiAlpha::CreateBitmap32(dc,rcItem.Width(),rcItem.Height());
	CBitmapHandle hOldBmp=dcMem.SelectBitmap(bmp);
	dcMem.BitBlt(0,0,rcItem.Width(),rcItem.Height(),dc,rcItem.left,rcItem.top,SRCCOPY);
	rcItem.MoveToXY(0,0);

	if(pdmmi)
	{
		MENUITEMINFO mii={sizeof(MENUITEMINFO),MIIM_FTYPE,0};
		HMENU menuPopup=pdmmi->hMenu;
		GetMenuItemInfo(menuPopup,pdmmi->nID,FALSE,&mii);

		BOOL bDisabled = lpDrawItemStruct->itemState & ODS_GRAYED;
		BOOL bSelected = lpDrawItemStruct->itemState & ODS_SELECTED;
		BOOL bChecked = lpDrawItemStruct->itemState & ODS_CHECKED;
		BOOL bRadio = mii.fType&MFT_RADIOCHECK;

		m_pItemSkin->Draw(dcMem,rcItem,bSelected?1:0);	//draw back

		//draw icon
		CRect rcIcon;
		rcIcon.left=rcItem.left+m_nIconMargin;
		rcIcon.right=rcIcon.left+m_szIcon.cx;
		rcIcon.top=rcItem.top+(rcItem.Height()-m_szIcon.cy)/2;
		rcIcon.bottom=rcIcon.top+m_szIcon.cy;
		if(bChecked)
		{
			if(m_pCheckSkin)
			{
				if(bRadio) m_pCheckSkin->Draw(dcMem,rcIcon,1);
				else m_pCheckSkin->Draw(dcMem,rcIcon,0);
			}
		}
		else if(pdmmi->itemInfo.iIcon!=-1 && m_pIconSkin) 
		{
			m_pIconSkin->Draw(dcMem,rcIcon,pdmmi->itemInfo.iIcon);
		}
		rcItem.left=rcIcon.right+m_nIconMargin;

		//draw text
		CRect rcTxt=rcItem;
		rcTxt.DeflateRect(m_nTextMargin,0);
		dcMem.SetBkMode(TRANSPARENT);

		COLORREF crOld=dcMem.SetTextColor(bDisabled?m_crTxtGray:(bSelected?m_crTxtSel:m_crTxtNormal));


		HFONT hOldFont=0;
		hOldFont=dcMem.SelectFont(m_hFont);
		dcMem.DrawText(pdmmi->itemInfo.strText,pdmmi->itemInfo.strText.GetLength(),&rcTxt,DT_SINGLELINE|DT_VCENTER|DT_LEFT);
		dcMem.SelectFont(hOldFont);

		dcMem.SetTextColor(crOld);

		if(bSelected && m_pItemSkin->GetStates()>2)
		{//draw select mask
			CRect rcItem=lpDrawItemStruct->rcItem;
			rcItem.MoveToXY(0,0);
			m_pItemSkin->Draw(dcMem,rcItem,2);
		}
	}else //if(strcmp("sep",pXmlItem->Value())==0)
	{
		m_pItemSkin->Draw(dcMem,rcItem,0);	//draw back
		if(m_pIconSkin) 
		{
			rcItem.left += m_pIconSkin->GetSkinSize().cx+m_nIconMargin*2;
		}

		if(m_pSepSkin)
			m_pSepSkin->Draw(dcMem,&rcItem,0);
		else
		{
			CGdiAlpha::DrawLine(dcMem, rcItem.left, rcItem.top, rcItem.right, rcItem.top, RGB(196,196,196), PS_SOLID);
			CGdiAlpha::DrawLine(dcMem, rcItem.left, rcItem.top+1, rcItem.right, rcItem.top+1, RGB(255,255,255), PS_SOLID);
		}
	}
	rcItem=lpDrawItemStruct->rcItem;
	dc.BitBlt(rcItem.left,rcItem.top,rcItem.Width(),rcItem.Height(),dcMem,0,0,SRCCOPY);
	dcMem.SelectBitmap(hOldBmp);
	dcMem.DeleteDC();
	bmp.DeleteObject();
}

void CDuiMenuODWnd::MeasureItem( LPMEASUREITEMSTRUCT lpMeasureItemStruct )
{
	if(lpMeasureItemStruct->CtlType != ODT_MENU) return;
	
	DuiMenuItemData *pdmmi=(DuiMenuItemData*)lpMeasureItemStruct->itemData;
	if(pdmmi)
	{//menu item
		lpMeasureItemStruct->itemHeight = m_nItemHei;
		lpMeasureItemStruct->itemWidth = m_szIcon.cx+m_nIconMargin*2;

		CDCHandle dc=::GetDC(NULL);
		HFONT hOldFont=0;
		hOldFont=dc.SelectFont(m_hFont);
		SIZE szTxt;
		dc.GetTextExtent(pdmmi->itemInfo.strText,pdmmi->itemInfo.strText.GetLength(),&szTxt);
		lpMeasureItemStruct->itemWidth += szTxt.cx+m_nTextMargin*2;
		dc.SelectFont(hOldFont);
		::ReleaseDC(NULL,dc);
	}else
	{// separator
		lpMeasureItemStruct->itemHeight = m_pSepSkin?m_pSepSkin->GetSkinSize().cy:3;
		lpMeasureItemStruct->itemWidth=0;
	}

}

void CDuiMenuODWnd::OnMenuSelect( UINT nItemID, UINT nFlags, HMENU menu )
{
	::SendMessage(GetParent(m_hWnd),WM_MENUSELECT,MAKEWPARAM(nItemID,nFlags),(LPARAM)menu);
}

//////////////////////////////////////////////////////////////////////////

CDuiMenu::CDuiMenu():m_pParent(NULL),m_hMenu(0)
{
}

CDuiMenu::CDuiMenu(CDuiMenu *pParent):m_pParent(pParent)
{
}

CDuiMenu::~CDuiMenu(void)
{
	DestroyMenu();
}

BOOL CDuiMenu::LoadMenu( UINT uResID )
{
	if(::IsMenu(m_hMenu)) return FALSE;

	DuiResProviderBase *pRes=DuiSystem::getSingleton().GetResProvider();
	if(!pRes) return FALSE;
	DWORD dwSize=pRes->GetRawBufferSize(DUIRES_XML_TYPE,uResID);
	if(dwSize==0) return FALSE;

	CMyBuffer<char> strXml;
	strXml.Allocate(dwSize);
	pRes->GetRawBuffer(DUIRES_XML_TYPE,uResID,strXml,dwSize);

	TiXmlDocument xmlDoc;

	xmlDoc.Parse(strXml);
	if(xmlDoc.Error())
	{
		return FALSE;
	}
	TiXmlElement *pRoot=xmlDoc.RootElement();
	if(strcmp(pRoot->Value(),"menu")!=0)
	{
		return FALSE;
	}
	if(!CreatePopupMenu()) return FALSE;

	m_menuSkin.Load(pRoot);
	DUIASSERT(m_menuSkin.m_pItemSkin);

	BuildMenu(m_hMenu,pRoot);

	return TRUE;
}

CDuiMenu CDuiMenu::GetSubMenu(int nPos)
{
	HMENU hSubMenu=::GetSubMenu(m_hMenu,nPos);
	CDuiMenu ret(this);
	ret.m_hMenu=hSubMenu;
	ret.m_menuSkin=m_menuSkin;
	return ret;
}

BOOL CDuiMenu::InsertMenu(UINT nPosition, UINT nFlags, UINT_PTR nIDNewItem,CString strText, int iIcon)
{
	nFlags|=MF_OWNERDRAW;
	if(nFlags&MF_SEPARATOR)
	{
		return ::InsertMenu(m_hMenu,nPosition,nFlags,(UINT_PTR)0,(LPCTSTR)NULL);
	}

	DuiMenuItemData *pMenuData=new DuiMenuItemData;
	pMenuData->hMenu=m_hMenu;
	pMenuData->itemInfo.iIcon=iIcon;
	pMenuData->itemInfo.strText=strText;

	if(nFlags&MF_POPUP)
	{//插入子菜单，
		CDuiMenu *pSubMenu=(CDuiMenu*)(LPVOID)nIDNewItem;
		DUIASSERT(pSubMenu->m_pParent==NULL);
		pMenuData->nID=(UINT_PTR)pSubMenu->m_hMenu;
	}else
	{
		pMenuData->nID=nIDNewItem;
	}

	if(!::InsertMenu(m_hMenu,nPosition,nFlags,pMenuData->nID,(LPCTSTR)pMenuData))
	{
		delete pMenuData;
		return FALSE;
	}

	CDuiMenu *pRootMenu=this;
	while(pRootMenu->m_pParent) pRootMenu=pRootMenu->m_pParent;
	//将分配的内存放到根菜单的内存节点列表中
	pRootMenu->m_arrDmmi.push_back(pMenuData);

	if(nFlags&MF_POPUP)
	{//对子菜单还需要做数据迁移处理
		CDuiMenu *pSubMenu=(CDuiMenu*)(LPVOID)nIDNewItem;
		for(int i=0;i<pSubMenu->m_arrDmmi.size();i++)
			pRootMenu->m_arrDmmi.push_back(pSubMenu->m_arrDmmi[i]);
		pSubMenu->m_arrDmmi.clear();
		pSubMenu->m_pParent=this;
	}
	return TRUE;
}

UINT CDuiMenu::TrackPopupMenu(
					UINT uFlags,
					int x,
					int y,
					HWND hWnd,
					LPCRECT prcRect
					)
{
	DUIASSERT(IsMenu(m_hMenu));

	CDuiMenuODWnd menuOwner;
	*(static_cast<CDuiMenuAttr*>(&menuOwner))=m_menuSkin;
	menuOwner.Create(NULL,WS_POPUP,WS_EX_NOACTIVATE,0,0,0,0,hWnd,NULL);
	UINT uNewFlags=uFlags|TPM_RETURNCMD;
	UINT uRet=::TrackPopupMenu(m_hMenu,uNewFlags,x,y,0,menuOwner.m_hWnd,prcRect);
	menuOwner.DestroyWindow();
	if(uRet && !(uFlags&TPM_RETURNCMD)) SendMessage(hWnd,WM_COMMAND,uRet,0);
	return uRet;
}

void CDuiMenu::BuildMenu( HMENU menuPopup,TiXmlElement *pTiXmlMenu )
{
	TiXmlElement *pTiXmlItem=pTiXmlMenu->FirstChildElement();

	while(pTiXmlItem)
	{
		if(strcmp("item",pTiXmlItem->Value())==0)
		{
			DuiMenuItemData *pdmmi=new DuiMenuItemData;
			pdmmi->hMenu=menuPopup;
			pdmmi->itemInfo.iIcon=-1;

			int nID=0;
			BOOL bCheck=FALSE,bDisable=FALSE,bRadio=FALSE;
			pTiXmlItem->Attribute("id",&nID);
			pTiXmlItem->Attribute("check",&bCheck);
			pTiXmlItem->Attribute("radio",&bRadio);
			pTiXmlItem->Attribute("disable",&bDisable);
			pTiXmlItem->Attribute("icon",&pdmmi->itemInfo.iIcon);
			pdmmi->itemInfo.strText=CA2T(pTiXmlItem->GetText(),CP_UTF8);

			if(!pTiXmlItem->FirstChildElement())
			{
				pdmmi->nID=nID;
				UINT uFlag=MF_OWNERDRAW;
				if(bCheck) uFlag|=MF_CHECKED;
				if(bDisable) uFlag |= MF_GRAYED;
				if(bRadio) uFlag |= MFT_RADIOCHECK|MF_CHECKED;
				AppendMenu(menuPopup,uFlag,(UINT_PTR)pdmmi->nID,(LPCTSTR)pdmmi);
			}
			else
			{
				HMENU hSubMenu=::CreatePopupMenu();
				pdmmi->nID=(UINT_PTR)hSubMenu;
				UINT uFlag=MF_OWNERDRAW|MF_POPUP;
				if(bDisable) uFlag |= MF_GRAYED;
				AppendMenu(menuPopup,uFlag,(UINT_PTR)hSubMenu,(LPCTSTR)pdmmi);
				BuildMenu(hSubMenu,pTiXmlItem);//build sub menu
			}
			m_arrDmmi.push_back(pdmmi);
		}else if(strcmp("sep",pTiXmlItem->Value())==0)
		{
			AppendMenu(menuPopup,MF_SEPARATOR|MF_OWNERDRAW,(UINT_PTR)0,(LPCTSTR)NULL);
		}
		pTiXmlItem=pTiXmlItem->NextSiblingElement();
	}
}

void CDuiMenu::DestroyMenu()
{
	if(!m_pParent)
	{
		if(m_hMenu) ::DestroyMenu(m_hMenu);
		for(int i=0;i<m_arrDmmi.size();i++) delete m_arrDmmi[i];
		m_arrDmmi.clear();
	}
}

}//namespace DuiEngine