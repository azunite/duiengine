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
#include "DuiSystem.h"
#include "GradientFillHelper.h"

namespace DuiEngine{


CDuiImageList::CDuiImageList():m_lSubImageWidth(0),m_bTile(FALSE)
{

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

	ALPHAINFO ai;
	CGdiAlpha::AlphaBackup(dc,&rcDraw,ai);

	dc.FillSolidRect(&rcDraw, m_crTo);

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
	CGdiAlpha::AlphaRestore(dc,ai);
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

GUID CDuiSkinGif::ms_Guid = Gdiplus::FrameDimensionTime;

void CDuiSkinGif::OnSetImage()
{
	if(!m_pDuiImg)
	{
		m_nFrames=0;
		if(m_pFrameDelay)
		{
			delete []m_pFrameDelay;
			m_pFrameDelay=NULL;
		}
	}else
	{
		CDuiImgX *pImgX=static_cast<CDuiImgX *>(m_pDuiImg);
		if(!pImgX) m_pDuiImg=NULL;
		else{
			Gdiplus::Image * m_pImage=pImgX->GetImage();
			UINT nCount = m_pImage->GetFrameDimensionsCount();
			if (nCount == 0)
			{
				m_pDuiImg=NULL;
				m_nFrames=0;
				if(m_pFrameDelay)
				{
					delete []m_pFrameDelay;
					m_pFrameDelay=NULL;
				}
				return;
			}

			GUID* pDimensionIDs = new GUID[nCount];
			if (pDimensionIDs != NULL)
			{
				m_pImage->GetFrameDimensionsList(pDimensionIDs, nCount);
				m_nFrames = m_pImage->GetFrameCount(&pDimensionIDs[0]);
				delete pDimensionIDs;
			}
			if(m_nFrames>1)
			{
				UINT nSize = m_pImage->GetPropertyItemSize(PropertyTagFrameDelay);
				DUIASSERT (nSize);

				Gdiplus::PropertyItem * pPropertyItem = (Gdiplus::PropertyItem *)malloc(nSize);
				if (pPropertyItem != NULL)
				{
					m_pImage->GetPropertyItem(PropertyTagFrameDelay, nSize, pPropertyItem);

					m_pFrameDelay = new long[m_nFrames];
					if (m_pFrameDelay != NULL)
					{
						for (int i = 0; i < (int)m_nFrames; i++)
						{
							m_pFrameDelay[i] = ((long*)pPropertyItem->value)[i] * 10;
							if (m_pFrameDelay[i] < 100)
								m_pFrameDelay[i] = 100;
						}
					}
					free(pPropertyItem);
				}
			}
		}
	}
}

void CDuiSkinGif::OnAttributeChanged( CStringA strAttrName,BOOL bLoading,HRESULT hRet )
{
	if(strAttrName=="src") 
		OnSetImage();
}

void CDuiSkinGif::Draw( CDCHandle dc, CRect rcDraw, DWORD dwState,BYTE byAlpha/*=0xFF*/ )
{
	if(dwState!=-1) SelectActiveFrame(dwState);
	CDuiImgX *pImgX=static_cast<CDuiImgX *>(m_pDuiImg);
	Gdiplus::Image *pImg=pImgX->GetImage();
	Gdiplus::Graphics graphics(dc);
	graphics.DrawImage(pImg,Gdiplus::Rect(rcDraw.left, rcDraw.top, rcDraw.Width(), rcDraw.Height()));
}

long CDuiSkinGif::GetFrameDelay( int iFrame )
{
	if(iFrame==-1) iFrame=m_iFrame;
	long nRet=-1;
	if(m_nFrames>1 && iFrame>=0 && iFrame<m_nFrames)
	{
		nRet=m_pFrameDelay[iFrame];
	}
	return nRet;
}

void CDuiSkinGif::ActiveNextFrame()
{
	if(m_nFrames>1)
	{
		m_iFrame++;
		if(m_iFrame==m_nFrames) m_iFrame=0;
		SelectActiveFrame(m_iFrame);
	}
}

void CDuiSkinGif::SelectActiveFrame( int iFrame )
{
	if(m_nFrames>1 && iFrame<m_nFrames)
	{
		CDuiImgX *pImgX=static_cast<CDuiImgX *>(m_pDuiImg);
		Gdiplus::Image *pImg=pImgX->GetImage();
		Gdiplus::Status status=pImg->SelectActiveFrame(&ms_Guid, iFrame);
	}
}
}//namespace DuiEngine