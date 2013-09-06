#include "duistd.h"
#include "DuiSkinBase.h"
#include "gdialpha.h"

namespace DuiEngine
{

BOOL CDuiSkinBase::ExtentBlt(CDuiImgBase *pImgDraw,BOOL bTile,HDC hdc,int x,int y,int nWid,int nHei,int xSrc,int ySrc,int nWidSrc,int nHeiSrc,BYTE byAlpha/*=0xFF*/)
{
    if(bTile) return pImgDraw->TileBlt(hdc,x,y,nWid,nHei,xSrc,ySrc,nWidSrc,nHeiSrc,byAlpha);
    else return pImgDraw->StretchBlt(hdc,x,y,nWid,nHei,xSrc,ySrc,nWidSrc,nHeiSrc,byAlpha);
}

void CDuiSkinBase::FrameDraw(CDCHandle &dc, CDuiImgBase *pImgDraw, const CRect &rcSour,const  CRect &rcDraw, CRect rcMargin, COLORREF crBg, UINT uDrawPart ,BOOL bTile,BYTE byAlpha/*=0xFF*/)
{
    CRect rcClient = rcDraw;

	if(rcDraw.IsRectEmpty()) return;
	int xOverflow=rcMargin.left+rcMargin.right-rcDraw.Width();
	if(xOverflow>0)
	{
		rcMargin.left-=xOverflow/2;
		rcMargin.right-=xOverflow/2;
		if(rcMargin.left<0) {rcMargin.right+=-rcMargin.left;rcMargin.left=0;}
		else if(rcMargin.right<0) {rcMargin.left+=-rcMargin.right;rcMargin.right=0;}
	}
	int yOverflow=rcMargin.top+rcMargin.bottom-rcDraw.Height();
	if(yOverflow>0)
	{
		rcMargin.top-=xOverflow/2;
		rcMargin.bottom-=xOverflow/2;
		if(rcMargin.top<0) {rcMargin.bottom+=-rcMargin.top;rcMargin.top=0;}
		else if(rcMargin.bottom<0) {rcMargin.top+=-rcMargin.bottom;rcMargin.bottom=0;}
	}

    DUIASSERT(dc.m_hDC);
    DUIASSERT(!pImgDraw->IsEmpty());
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


}//namespace DuiEngine