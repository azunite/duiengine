//////////////////////////////////////////////////////////////////////////
//   File Name: DuiSkinPool
// Description: DuiWindow Skin Definition
//     Creator: ZhangXiaoxuan
//     Version: 2009.4.22 - 1.0 - Create
//				2011.6.18   1.1   huangjianxiong
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "duistd.h"
#include "duiskin.h"

#include "duiimage.h"
#include "duiimgpool.h"
#include "gdialpha.h"

namespace DuiEngine{


BOOL CDuiSkinBase::ExtentBlt(CDuiImgBase *pImgDraw,BOOL bTile,HDC hdc,int x,int y,int nWid,int nHei,int xSrc,int ySrc,int nWidSrc,int nHeiSrc,BYTE byAlpha/*=0xFF*/)
{
	if(bTile) return pImgDraw->TileBlt(hdc,x,y,nWid,nHei,xSrc,ySrc,nWidSrc,nHeiSrc,byAlpha);
	else return pImgDraw->StretchBlt(hdc,x,y,nWid,nHei,xSrc,ySrc,nWidSrc,nHeiSrc,byAlpha);
}

void CDuiSkinBase::FrameDraw(CDCHandle &dc, CDuiImgBase *pImgDraw, const CRect &rcSour,const  CRect &rcDraw,const  CRect &rcMargin, COLORREF crBg, UINT uDrawPart ,BOOL bTile,BYTE byAlpha/*=0xFF*/)
{
	CRect rcClient = rcDraw;

	ATLASSERT(dc.m_hDC);
	ATLASSERT(!pImgDraw->IsEmpty());
	rcClient.DeflateRect(
		(uDrawPart & Frame_Part_Left)   ? rcMargin.left  : 0, 
		(uDrawPart & Frame_Part_Top)    ? rcMargin.top   : 0, 
		(uDrawPart & Frame_Part_Right)  ? rcMargin.right : 0, 
		(uDrawPart & Frame_Part_Bottom) ? rcMargin.bottom: 0 
		);

	if ((Frame_Part_Left | Frame_Part_Top) == (uDrawPart & (Frame_Part_Left | Frame_Part_Top)))
	{
		pImgDraw->BitBlt(
			dc, 
			rcDraw.left, rcDraw.top, 
			rcMargin.left, rcMargin.top, 
			rcSour.left, rcSour.top,
			byAlpha
			);
	}
	if ((Frame_Part_Right | Frame_Part_Top) == (uDrawPart & (Frame_Part_Right | Frame_Part_Top)))
	{
		pImgDraw->BitBlt(
			dc, 
			rcClient.right, rcDraw.top, 
			rcMargin.right, rcMargin.top, 
			rcSour.right - rcMargin.right, rcSour.top,
			byAlpha
			);
	}
	if ((Frame_Part_Left | Frame_Part_Bottom) == (uDrawPart & (Frame_Part_Left | Frame_Part_Bottom)))
	{
		pImgDraw->BitBlt(
			dc, 
			rcDraw.left, rcClient.bottom, 
			rcMargin.left, rcMargin.bottom, 
			rcSour.left , rcSour.bottom-rcMargin.bottom,
			byAlpha
			);
	}
	if ((Frame_Part_Right | Frame_Part_Bottom) == (uDrawPart & (Frame_Part_Right | Frame_Part_Bottom)))
	{
		pImgDraw->BitBlt(
			dc, 
			rcClient.right, rcClient.bottom, 
			rcMargin.right , rcMargin.bottom, 
			rcSour.right - rcMargin.right, rcSour.bottom - rcMargin.bottom,
			byAlpha
			);
	}
	if (Frame_Part_Top == (uDrawPart & Frame_Part_Top))
	{
		ExtentBlt(pImgDraw,bTile,
			dc, 
			rcClient.left, rcDraw.top, 
			rcClient.Width(), rcMargin.top, 
			rcSour.left + rcMargin.left, rcSour.top, 
			rcSour.Width() - rcMargin.left-rcMargin.right, rcMargin.top,
			byAlpha
			);
	}
	if (Frame_Part_Left == (uDrawPart & Frame_Part_Left))
	{
		ExtentBlt(pImgDraw,bTile,
			dc, 
			rcDraw.left, rcClient.top, 
			rcMargin.left, rcClient.Height(), 
			rcSour.left, rcSour.top + rcMargin.top, 
			rcMargin.left, rcSour.Height() - rcMargin.top-rcMargin.bottom,
			byAlpha
			);
	}
	if (Frame_Part_Bottom == (uDrawPart & Frame_Part_Bottom))
	{
		ExtentBlt(pImgDraw,bTile,
			dc, 
			rcClient.left, rcClient.bottom, 
			rcClient.Width(), rcMargin.bottom, 
			rcSour.left+rcMargin.left, rcSour.bottom-rcMargin.bottom, 
			rcSour.Width() - rcMargin.left -rcMargin.right, rcMargin.bottom,
			byAlpha
			);
	}
	if (Frame_Part_Right == (uDrawPart & Frame_Part_Right))
	{
		ExtentBlt(pImgDraw,bTile,
			dc, 
			rcClient.right, rcClient.top, 
			rcMargin.right, rcClient.Height(), 
			rcSour.right - rcMargin.right, rcSour.top + rcMargin.top, 
			rcMargin.right, rcSour.Height()-rcMargin.top-rcMargin.bottom,
			byAlpha
			);
	}

	//从图片中获得alpha通道
	CRect rcSourMD=rcSour;
	rcSourMD.DeflateRect(rcMargin.left,rcMargin.top,rcMargin.right,rcMargin.bottom);
	ExtentBlt(pImgDraw,bTile,
		dc, 
		rcClient.left, rcClient.top, 
		rcClient.Width(), rcClient.Height(), 
		rcSourMD.left, rcSourMD.top, 
		rcSourMD.Width(), rcSourMD.Height(), 
		byAlpha
		);
	if (CLR_INVALID != crBg)
	{
		CGdiAlpha::FillSolidRect(dc,rcClient, crBg);
	}
}

typedef BOOL (WINAPI * FnGradientFill)(HDC, PTRIVERTEX, ULONG, PVOID, ULONG, ULONG);

BOOL WINAPI CDuiSkinBase::GradientFill2(HDC hDC, PTRIVERTEX pVertices, DWORD nVertices, PVOID pMeshElements, ULONG nMeshElements, ULONG dwMode)
{
	HMODULE hMod = ::LoadLibrary(_T("msimg32.dll"));
	if (hMod)
	{
		FnGradientFill pfnGradientFill = (FnGradientFill)::GetProcAddress(hMod, "GradientFill");
		if (pfnGradientFill)
			pfnGradientFill(hDC, pVertices, nVertices, pMeshElements, nMeshElements, dwMode);
		::FreeLibrary(hMod);
	}

	return TRUE;
}

void CDuiSkinBase::GradientFillRectV(HDC hdc, CRect &rcFill, FRG_PARAM params[], int nCount)
{
	GRADIENT_RECT gRect = {0, 1};
	TRIVERTEX vert[2] = {
		{rcFill.left, rcFill.top, 0, 0, 0, 0}, 
		{rcFill.right, rcFill.top, 0, 0, 0, 0}
	};
	int i = 0;

	for (i = 1; i < nCount && vert[0].y <= rcFill.bottom; i ++)
	{
		vert[0].y = vert[1].y;
		vert[1].y += params[i].lOffset;
		vert[0].Red     = GetRValue(params[i - 1].crColor) << 8;
		vert[0].Green   = GetGValue(params[i - 1].crColor) << 8;
		vert[0].Blue    = GetBValue(params[i - 1].crColor) << 8;
		vert[1].Red     = GetRValue(params[i].crColor) << 8;
		vert[1].Green   = GetGValue(params[i].crColor) << 8;
		vert[1].Blue    = GetBValue(params[i].crColor) << 8;

		HMODULE hMod = ::LoadLibrary(_T("msimg32.dll"));
		if (hMod)
		{
			GradientFill2(hdc, vert, 2, &gRect, 1, GRADIENT_FILL_RECT_V);
		}
	}
}

void CDuiSkinBase::GradientFillRectH(HDC hdc, CRect &rcFill, FRG_PARAM params[], int nCount)
{
	GRADIENT_RECT gRect = {0, 1};
	TRIVERTEX vert[2] = {
		{rcFill.left, rcFill.top, 0, 0, 0, 0}, 
		{rcFill.left, rcFill.bottom, 0, 0, 0, 0}
	};
	int i = 0;

	for (i = 1; i < nCount && vert[0].x <= rcFill.right; i ++)
	{
		vert[0].x = vert[1].x;
		vert[1].x += params[i].lOffset;
		vert[0].Red     = GetRValue(params[i - 1].crColor) << 8;
		vert[0].Green   = GetGValue(params[i - 1].crColor) << 8;
		vert[0].Blue    = GetBValue(params[i - 1].crColor) << 8;
		vert[1].Red     = GetRValue(params[i].crColor) << 8;
		vert[1].Green   = GetGValue(params[i].crColor) << 8;
		vert[1].Blue    = GetBValue(params[i].crColor) << 8;
		GradientFill2(hdc, vert, 2, &gRect, 1, GRADIENT_FILL_RECT_H);
	}
}

void CDuiSkinBase::GradientFillRectV(HDC hdc, CRect &rcFill, COLORREF crTop, COLORREF crBottom)
{
	FRG_PARAM frgDraw[2] = {
		{0, crTop}, 
		{rcFill.Height(), crBottom}, 
	};

	GradientFillRectV(hdc, rcFill, frgDraw, 2);
}

void CDuiSkinBase::GradientFillRectH(HDC hdc, CRect &rcFill, COLORREF crLeft, COLORREF crRight)
{
	FRG_PARAM frgDraw[2] = {
		{0, crLeft}, 
		{rcFill.Width(), crRight}, 
	};

	GradientFillRectH(hdc, rcFill, frgDraw, 2);
}

CDuiImageList::CDuiImageList():m_lSubImageWidth(0),m_bTile(FALSE)
{

}

void CDuiImageList::SetImageID(UINT uID)
{
	m_pDuiImg=DuiImgPool::getSingleton().GetImage(uID);
}

void CDuiImageList::SetImageSkin(CDuiImgBase *pImg)
{
	m_pDuiImg=pImg;
}

CDuiImgBase * CDuiImageList::GetImage()
{
	return m_pDuiImg;
}

void CDuiImageList::SetPropTile(BOOL bTile)
{
	m_bTile=bTile;
}

void CDuiImageList::Draw(CDCHandle dc, CRect rcDraw, DWORD dwState,BYTE byAlpha)
{
	SIZE sz=GetSkinSize();
	if(m_pDuiImg)
	{
		ExtentBlt(m_pDuiImg,m_bTile,dc,rcDraw.left,rcDraw.top,rcDraw.Width(),rcDraw.Height(),dwState*sz.cx,0,sz.cx,sz.cy,byAlpha);
	}
}

SIZE CDuiImageList::GetSkinSize()
{
	SIZE ret = {0, 0};

	if(m_pDuiImg) m_pDuiImg->GetImageSize(ret);

	if (0 != m_lSubImageWidth)
		ret.cx = m_lSubImageWidth;

	return ret;
}

BOOL CDuiImageList::IgnoreState()
{
	return (0 == m_lSubImageWidth);
}

int CDuiImageList::GetStates()
{
	if(0 == m_lSubImageWidth) 
		return 1;
	else 
		return m_pDuiImg->GetWidth()/m_lSubImageWidth;
}


CDuiSkinImgFrame::CDuiSkinImgFrame()
: m_crBg(CLR_INVALID)
, m_lSkinParamLeft(0)
, m_lSkinParamTop(0)
, m_lSkinParamRight(-1)
, m_lSkinParamBottom(-1)
, m_uDrawPart(Frame_Part_All)
{
}

void CDuiSkinImgFrame::Draw(CDCHandle dc, CRect rcDraw, DWORD dwState,BYTE byAlpha)
{
	SIZE sz;
	if(!m_pDuiImg) return;
	m_pDuiImg->GetImageSize(sz);
	int nWid=m_lSubImageWidth;
	if(nWid==0) nWid=sz.cx;
	CRect rcSour(dwState*nWid,0,(dwState+1)*nWid,sz.cy);

	FrameDraw(dc, m_pDuiImg , rcSour,rcDraw, CRect(m_lSkinParamLeft, m_lSkinParamTop,m_lSkinParamRight,m_lSkinParamBottom), m_crBg, m_uDrawPart,m_bTile,byAlpha);
}

void CDuiSkinImgFrame::OnAttributeFinish(TiXmlElement* pXmlElem)
{
	if(m_lSkinParamRight==-1) m_lSkinParamRight=m_lSkinParamLeft;
	if(m_lSkinParamBottom==-1) m_lSkinParamBottom=m_lSkinParamTop;
}

void CDuiSkinImgFrame::SetMargin(int nLeft,int nTop,int nRight,int nBottom)
{
	m_lSkinParamLeft=nLeft;
	m_lSkinParamRight=nRight;
	m_lSkinParamTop=nTop;
	m_lSkinParamBottom=nBottom;
}

CDuiSkinButton::CDuiSkinButton()
: m_crBorder(RGB(0x70, 0x70, 0x70))
, m_crBg(RGB(0xEE, 0xEE, 0xEE))
, m_crBgUpNormal(RGB(0xEE, 0xEE, 0xEE))
, m_crBgUpHover(RGB(0xEE, 0xEE, 0xEE))
, m_crBgUpPush(RGB(0xCE, 0xCE, 0xCE))
, m_crBgDownNormal(RGB(0xD6, 0xD6, 0xD6))
, m_crBgDownHover(RGB(0xE0, 0xE0, 0xE0))
, m_crBgDownPush(RGB(0xC0, 0xC0, 0xC0))
{

}

void CDuiSkinButton::Draw(CDCHandle dc, CRect rcDraw, DWORD dwState,BYTE byAlpha)
{
	CPen penFrame;
	CRect rcBg = rcDraw;

	ALPHAINFO ai;
	CGdiAlpha::AlphaBackup(dc,rcDraw,ai);

	rcDraw.DeflateRect(1, 1);
	dc.FillSolidRect(&rcDraw, m_crBg);

	rcBg.DeflateRect(2, 2);

	if (DuiWndState_Disable == (DuiWndState_Disable & dwState))
	{

	}
	else
		GradientFillRectV(
		dc, rcBg, 
		IIF_STATE3(dwState, m_crBgUpNormal, m_crBgUpHover, m_crBgUpPush), 
		IIF_STATE3(dwState, m_crBgDownNormal, m_crBgDownHover, m_crBgDownPush));


	penFrame.CreatePen(
		PS_SOLID, 
		1, 
		m_crBorder
		);

	HPEN hpenOld = dc.SelectPen(penFrame);
	HBRUSH hbshOld = NULL, hbshNull = (HBRUSH)::GetStockObject(NULL_BRUSH);

	hbshOld = dc.SelectBrush(hbshNull);

	rcDraw.DeflateRect(-1, -1);
	dc.RoundRect(rcDraw, CPoint(2,2));

	dc.SelectBrush(hbshOld);
	dc.SelectPen(hpenOld);

	CGdiAlpha::AlphaRestore(dc,ai);
}

BOOL CDuiSkinButton::IgnoreState()
{
	return FALSE;
}

int CDuiSkinButton::GetStates()
{
	return 4;
}


CDuiSkinGradation::CDuiSkinGradation()
: m_uDirection(0)
, m_crFrom(CLR_INVALID)
, m_crTo(CLR_INVALID)
, m_nSize(0)
{
}

void CDuiSkinGradation::Draw(CDCHandle dc, CRect rcDraw, DWORD dwState,BYTE byAlpha)
{
	CRect rcGradation = rcDraw;
	CRgn rgnDraw;

	rgnDraw.CreateRectRgn(rcDraw.left, rcDraw.top, rcDraw.right, rcDraw.bottom);

	CGdiAlpha::FillSolidRect(dc,&rcDraw, m_crTo);

	int nID = dc.SaveDC();

	dc.SelectClipRgn(rgnDraw);

	if (0 == m_uDirection)
	{
		if (0 < m_nSize)
			rcGradation.right = rcGradation.left + m_nSize;
		GradientFillRectH(dc, rcGradation, m_crFrom, m_crTo);
	}
	else
	{
		if (0 < m_nSize)
			rcGradation.bottom = rcGradation.top + m_nSize;
		GradientFillRectV(dc, rcGradation, m_crFrom, m_crTo);
	}

	dc.RestoreDC(nID);
}


CDuiScrollbarSkin::CDuiScrollbarSkin():m_nThumbLeft(0)
{

}

void CDuiScrollbarSkin::Draw(CDCHandle dc, CRect rcDraw, DWORD dwState,BYTE byAlpha)
{
	if(!m_pDuiImg) return;
	int nSbCode=LOWORD(dwState);
	int nState=LOBYTE(HIWORD(dwState));
	BOOL bVertical=HIBYTE(HIWORD(dwState));
	CRect rcMargin(0,0,0,0);

	if(nSbCode==SB_CORNOR)
	{
		CSize sz=GetSkinSize();
		CSize szFrame(sz.cx/9,sz.cx/9);
		CRect rcSour(szFrame.cx*8,0,szFrame.cx*9,szFrame.cy);
		FrameDraw(dc, m_pDuiImg , rcSour,rcDraw,rcMargin, CLR_INVALID, m_uDrawPart,m_bTile,byAlpha);
		return ;
	}
	int iPart=-1;
	switch(nSbCode)
	{
	case SB_LINEUP: iPart=0;break;
	case SB_LINEDOWN:iPart=1;break;
	case SB_THUMBTRACK:iPart=2;break;
	case SB_PAGEUP:case SB_PAGEDOWN: iPart=3;break;
	}
	if(!bVertical) iPart+=4;

	CSize sz=GetSkinSize();
	CSize szFrame(sz.cx/9,sz.cx/9);
	CRect rcSour(CPoint(szFrame.cx*iPart,szFrame.cy*nState),szFrame);

	if(nSbCode==SB_THUMBTRACK)
	{
		if(bVertical) 
			rcMargin.top=m_nThumbLeft,rcMargin.bottom=m_nThumbLeft;
		else 
			rcMargin.left=m_nThumbLeft,rcMargin.right=m_nThumbLeft;
	}
	FrameDraw(dc, m_pDuiImg , rcSour,rcDraw,rcMargin, CLR_INVALID, m_uDrawPart,m_bTile,byAlpha);
}

template<> DuiSkinFactoryManager * Singleton<DuiSkinFactoryManager>::ms_Singleton=0;

void DuiSkinFactoryManager::AddStandardSkin()
{
	AddKeyObject(CDuiImageList::GetClassName(),new TplSkinFactory<CDuiImageList>());
	AddKeyObject(CDuiSkinImgFrame::GetClassName(),new TplSkinFactory<CDuiSkinImgFrame>());
	AddKeyObject(CDuiSkinButton::GetClassName(),new TplSkinFactory<CDuiSkinButton>());
	AddKeyObject(CDuiSkinImgHorzExtend::GetClassName(),new TplSkinFactory<CDuiSkinImgHorzExtend>());
	AddKeyObject(CDuiSkinGradation::GetClassName(),new TplSkinFactory<CDuiSkinGradation>());
	AddKeyObject(CDuiScrollbarSkin::GetClassName(),new TplSkinFactory<CDuiScrollbarSkin>());
	AddKeyObject(CDuiMenuBorderSkin::GetClassName(),new TplSkinFactory<CDuiMenuBorderSkin>());
}

//////////////////////////////////////////////////////////////////////////
// DuiSkinPool
template<> DuiSkinPool * Singleton<DuiSkinPool>::ms_Singleton =0;

DuiSkinPool::DuiSkinPool():m_pXmlSkinDesc(NULL)
{
	m_pFunOnKeyRemoved=OnKeyRemoved;
}

DuiSkinPool::~DuiSkinPool()
{
	if(m_pXmlSkinDesc) delete m_pXmlSkinDesc;
}

BOOL DuiSkinPool::Init(UINT uResID)
{
	CMyBuffer<char> strXml;
	BOOL bRet = DuiResManager::getSingleton().LoadResource(uResID, strXml);

	if (!bRet)
		return FALSE;

	return Init(strXml);
}

BOOL DuiSkinPool::Init(LPCSTR lpszXml)
{
	TiXmlDocument xmlDoc;

	xmlDoc.Parse(lpszXml, NULL, TIXML_ENCODING_UTF8);

	if (xmlDoc.Error())
		return FALSE;

	return _InitSkins(xmlDoc.RootElement());
}

int DuiSkinPool::LoadSkins(CStringA strOwnerName)
{
	int nLoaded=0;
	CStringA strSkinName, strTypeName;

	TiXmlElement *pXmlSkin=m_pXmlSkinDesc->FirstChildElement();
	while(pXmlSkin)
	{
		CStringA strOwner= pXmlSkin->Attribute("owner");
		if(strOwner==strOwnerName)
		{
			strSkinName = pXmlSkin->Attribute("name");
			strTypeName = pXmlSkin->Value();

			if (strSkinName.IsEmpty() || strTypeName.IsEmpty())
				continue;

			ATLASSERT(!HasKey(strSkinName));
			if(DuiSkinFactoryManager::getSingleton().HasKey(strTypeName)) 
			{
				CSkinFactory *pSkinFactory=DuiSkinFactoryManager::getSingleton().GetKeyObject(strTypeName);
				CDuiSkinBase *pSkin = pSkinFactory->NewSkin();

				pSkin->Load(pXmlSkin);

				pSkin->SetOwner(strOwnerName);

				AddKeyObject(strSkinName,pSkin);
				nLoaded++;
			}else
			{
				DUIRES_ASSERTA(FALSE,"load skin error,type=%s,name=%s",strTypeName,strSkinName);
			}
		}
		pXmlSkin=pXmlSkin->NextSiblingElement();
	}

	return nLoaded;
}


int DuiSkinPool::FreeSkins( CStringA strOwnerName )
{
	if(strOwnerName.IsEmpty()) return 0;

	int nFreed=0;

	std::map<CStringA,DuiSkinPtr>::iterator pos=m_mapNamedObj.begin();
	while(pos!=m_mapNamedObj.end())
	{
		std::map<CStringA,DuiSkinPtr>::iterator posPrev=pos;
		pos++;
		if(posPrev->second->GetOwner()==strOwnerName)
		{
			OnKeyRemoved(posPrev->second);
			m_mapNamedObj.erase(posPrev);
			nFreed++;
		}
	}
	return nFreed;
}

CDuiSkinBase* DuiSkinPool::GetSkin(CStringA strSkinName)
{
	if(!HasKey(strSkinName)) return NULL;
	return GetKeyObject(strSkinName);
}

BOOL DuiSkinPool::_InitSkins(TiXmlElement *pXmlSkinRootElem)
{
	if (strcmp(pXmlSkinRootElem->Value(), "skins") != 0)
		return FALSE;
	m_pXmlSkinDesc=pXmlSkinRootElem->Clone()->ToElement();
	LoadSkins("");
	return TRUE;
}

void DuiSkinPool::OnKeyRemoved(const DuiSkinPtr & obj )
{
	CSkinFactory *pFactory=DuiSkinFactoryManager::getSingleton().GetKeyObject(obj->GetObjectClass());
	pFactory->DeleteSkin(obj);
}

}//namespace DuiEngine