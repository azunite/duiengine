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

#include "duiimgpool.h"
#include "gdialpha.h"
#include "DuiSystem.h"
#include "GradientFillHelper.h"

namespace DuiEngine
{


CDuiImageList::CDuiImageList():m_lSubImageWidth(0),m_nStates(0),m_bTile(FALSE)
{

}

void CDuiImageList::Draw(CDCHandle dc, CRect rcDraw, DWORD dwState,BYTE byAlpha)
{
    if(m_pDuiImg)
	{
		SIZE sz=GetSkinSize();
		ExtentBlt(m_pDuiImg,m_bTile,dc,rcDraw.left,rcDraw.top,rcDraw.Width(),rcDraw.Height(),dwState*sz.cx,0,sz.cx,sz.cy,byAlpha);
	}
}

SIZE CDuiImageList::GetSkinSize()
{
    SIZE ret = {0, 0};
    if(m_pDuiImg) m_pDuiImg->GetImageSize(ret);
    if(m_lSubImageWidth!=0) ret.cx = m_lSubImageWidth;
    return ret;
}

BOOL CDuiImageList::IgnoreState()
{
    return GetStates()==1;
}

int CDuiImageList::GetStates()
{
	return m_nStates;
}

void CDuiImageList::OnAttributeFinish(pugi::xml_node xmlNode )
{
	__super::OnAttributeFinish(xmlNode);

	DUIASSERT(m_pDuiImg);
	if(0 != m_lSubImageWidth)
	{
		if(0== m_nStates) //定义了子图宽度，没有定义子图数量
			m_nStates=m_pDuiImg->GetWidth()/m_lSubImageWidth;
	}else if(0 != m_nStates)
	{//定义了子图数量，没有定义子图宽度
		m_lSubImageWidth = m_pDuiImg->GetWidth()/m_nStates;
	}else
	{//两者都没有定义
		m_nStates=1;
		m_lSubImageWidth=m_pDuiImg->GetWidth();
	}
}

CDuiSkinImgFrame::CDuiSkinImgFrame()
    : m_crBg(CLR_INVALID)
    , m_uDrawPart(Frame_Part_All)
	, m_rcMargin(0,0,-1,-1)
{
}

void CDuiSkinImgFrame::Draw(CDCHandle dc, CRect rcDraw, DWORD dwState,BYTE byAlpha)
{
    if(!m_pDuiImg) return;
	SIZE sz=GetSkinSize();
    CRect rcSour(dwState*sz.cx,0,(dwState+1)*sz.cx,sz.cy);

    FrameDraw(dc, m_pDuiImg , rcSour,rcDraw, m_rcMargin, m_crBg, m_uDrawPart,m_bTile,byAlpha);
}

void CDuiSkinImgFrame::OnAttributeFinish(pugi::xml_node xmlNode)
{
	__super::OnAttributeFinish(xmlNode);
	if(m_rcMargin.right==-1)
	{
		DUIASSERT(m_lSubImageWidth>=m_rcMargin.left);
		if(m_lSubImageWidth>m_rcMargin.left*2)
			m_rcMargin.right=m_rcMargin.left;
		else
			m_rcMargin.right=0;
	}
	if(m_rcMargin.bottom==-1)
	{
		DUIASSERT(m_pDuiImg);
		int nHei=m_pDuiImg->GetHeight();
		DUIASSERT(nHei>=m_rcMargin.top);
		if(nHei>m_rcMargin.top*2)
			m_rcMargin.bottom=m_rcMargin.top;
		else
			m_rcMargin.bottom=0;
	}
}

void CDuiSkinImgFrame::SetMargin(int nLeft,int nTop,int nRight,int nBottom)
{
	m_rcMargin.SetRect(nLeft,nTop,nRight,nBottom);
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


CDuiScrollbarSkin::CDuiScrollbarSkin():m_nMagin(0),m_bHasGripper(FALSE)
{
	
}

CRect CDuiScrollbarSkin::GetPartRect(int nSbCode, int nState,BOOL bVertical)
{
	CSize sz=GetSkinSize();
	CSize szFrame(sz.cx/9,sz.cx/9);
	if(nSbCode==SB_CORNOR)
	{
		return CRect(CPoint(szFrame.cx*8,0),szFrame);
	}else if(nSbCode==SB_THUMBGRIPPER)
	{
		return CRect(CPoint(szFrame.cx*8,(1+(bVertical?0:1))*szFrame.cy),szFrame);
	}else
	{
		CRect rcRet;
		int iPart=-1;
		switch(nSbCode)
		{
		case SB_LINEUP:
			iPart=0;
			break;
		case SB_LINEDOWN:
			iPart=1;
			break;
		case SB_THUMBTRACK:
			iPart=2;
			break;
		case SB_PAGEUP:
		case SB_PAGEDOWN:
			iPart=3;
			break;
		}
		if(!bVertical) iPart+=4;
		
		return CRect(CPoint(szFrame.cx*iPart,szFrame.cy*nState),szFrame);
	}
}

void CDuiScrollbarSkin::Draw(CDCHandle dc, CRect rcDraw, DWORD dwState,BYTE byAlpha)
{
    if(!m_pDuiImg) return;
    int nSbCode=LOWORD(dwState);
    int nState=LOBYTE(HIWORD(dwState));
    BOOL bVertical=HIBYTE(HIWORD(dwState));
    CRect rcMargin(0,0,0,0);
    if(bVertical)
        rcMargin.top=m_nMagin,rcMargin.bottom=m_nMagin;
    else
        rcMargin.left=m_nMagin,rcMargin.right=m_nMagin;

	CRect rcSour=GetPartRect(nSbCode,nState,bVertical);
    FrameDraw(dc, m_pDuiImg , rcSour,rcDraw,rcMargin, CLR_INVALID, m_uDrawPart,m_bTile,byAlpha);

    if(nSbCode==SB_THUMBTRACK && m_bHasGripper)
    {
		rcSour=GetPartRect(SB_THUMBGRIPPER,0,bVertical);
        if (bVertical)
			rcDraw.top+=(rcDraw.Height()-rcSour.Height())/2,rcDraw.bottom=rcDraw.top+rcSour.Height();
        else
			rcDraw.left+=(rcDraw.Width()-rcSour.Width())/2,rcDraw.right=rcDraw.left+rcSour.Width();
        FrameDraw(dc, m_pDuiImg , rcSour,rcDraw,rcMargin, CLR_INVALID, m_uDrawPart,m_bTile,byAlpha);
    }
}

}//namespace DuiEngine