//////////////////////////////////////////////////////////////////////////
//  Class Name: CDuiImage
//////////////////////////////////////////////////////////////////////////

#include "duistd.h"
#include "duiobject.h"
#include "duiimage.h"
#include "DuiSystem.h"


#pragma comment(lib, "gdiplus.lib")

namespace DuiEngine{

static BOOL TransparentBlt2(
							HDC hdcDest,            // 目标DC
							int nXOriginDest,       // 目标X偏移
							int nYOriginDest,       // 目标Y偏移
							int nWidthDest,         // 目标宽度
							int nHeightDest,        // 目标高度
							HDC hdcSrc,             // 源DC
							int nXOriginSrc,        // 源X起点
							int nYOriginSrc,        // 源Y起点
							int nWidthSrc,          // 源宽度
							int nHeightSrc,         // 源高度
							UINT crTransparent      // 透明色,COLORREF类型
							)
{
	HBITMAP hOldImageBMP = NULL, hImageBMP = NULL, hOldMaskBMP = NULL, hMaskBMP = NULL;
	HDC     hImageDC = NULL, hMaskDC = NULL;

	hImageBMP = ::CreateCompatibleBitmap(hdcDest, nWidthDest, nHeightDest);   // 创建兼容位图
	hMaskBMP = ::CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);           // 创建单色掩码位图
	hImageDC = ::CreateCompatibleDC(hdcDest);
	hMaskDC = ::CreateCompatibleDC(hdcDest);

	hOldImageBMP = (HBITMAP)::SelectObject(hImageDC, hImageBMP);
	hOldMaskBMP = (HBITMAP)::SelectObject(hMaskDC, hMaskBMP);

	// 将源DC中的位图拷贝到临时DC中
	if (nWidthDest == nWidthSrc && nHeightDest == nHeightSrc)
		::BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, SRCCOPY);
	else
		::StretchBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, 
		hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, SRCCOPY);

	// 设置透明色
	::SetBkColor(hImageDC, crTransparent);

	// 生成透明区域为白色，其它区域为黑色的掩码位图
	::BitBlt(hMaskDC, 0, 0, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCCOPY);

	// 生成透明区域为黑色，其它区域保持不变的位图
	::SetBkColor(hImageDC, RGB(0,0,0));
	::SetTextColor(hImageDC, RGB(255,255,255));
	::BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);

	// 透明部分保持屏幕不变，其它部分变成黑色
	COLORREF crBg = ::SetBkColor(hdcDest, RGB(255, 255, 255));
	COLORREF crText = ::SetTextColor(hdcDest, RGB(0, 0, 0));
	::BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);

	// "或"运算,生成最终效果
	::BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCPAINT);

	// 清理、恢复	
	::SelectObject(hImageDC, hOldImageBMP);
	::DeleteDC(hImageDC);
	::SelectObject(hMaskDC, hOldMaskBMP);
	::DeleteDC(hMaskDC);
	::DeleteObject(hImageBMP);
	::DeleteObject(hMaskBMP);

	::SetBkColor(hdcDest, crBg);
	::SetTextColor(hdcDest, crText);

	return TRUE;
}


CDuiBitmap::CDuiBitmap():m_hBitmap(NULL),m_bManaged(FALSE),m_crMask(CLR_INVALID)
{
}

CDuiBitmap::CDuiBitmap(HBITMAP hBitmap):m_hBitmap(hBitmap),m_bManaged(TRUE)
{

}

CDuiBitmap::operator HBITMAP()  const
{
	return m_hBitmap;
}

void CDuiBitmap::Clear()
{
	if(m_bManaged && m_hBitmap) DeleteObject(m_hBitmap);
	m_hBitmap=NULL;
	m_bManaged=FALSE;
}

BOOL CDuiBitmap::IsEmpty(){return m_hBitmap==NULL;}
BOOL CDuiBitmap::GetImageSize(SIZE & sz)
{
	if(IsEmpty()) return FALSE;
	BITMAP bm;
	GetObject(m_hBitmap,sizeof(bm),&bm);
	sz.cx=bm.bmWidth;
	sz.cy=bm.bmHeight;
	return TRUE;			
}

int CDuiBitmap::GetWidth()
{
	if(IsEmpty()) return 0;
	BITMAP bm;
	GetObject(m_hBitmap,sizeof(bm),&bm);
	return bm.bmWidth;
}
int CDuiBitmap::GetHeight()
{
	if(IsEmpty()) return 0;
	BITMAP bm;
	GetObject(m_hBitmap,sizeof(bm),&bm);
	return bm.bmHeight;
}

BOOL CDuiBitmap::BitBlt(HDC hdc,int x,int y,int nWid,int nHei,int xSrc,int ySrc,BYTE byAlpha/*=0xFF*/)
{
	if(IsEmpty()) return FALSE;
	BOOL bRet=FALSE;
	HDC hMemdc=CreateCompatibleDC(hdc);
	HGDIOBJ hOldBmp=SelectObject(hMemdc,m_hBitmap);
	if(m_crMask!=CLR_INVALID)
	{
		bRet=TransparentBlt2(hdc,x,y,nWid,nHei,hMemdc,xSrc,ySrc,nWid,nHei,m_crMask);
	}else
	{
		bRet=::BitBlt(hdc,x,y,nWid,nHei,hMemdc,xSrc,ySrc,SRCCOPY);
	}
	SelectObject(hMemdc,hOldBmp);
	DeleteDC(hMemdc);
	return bRet;
}

BOOL CDuiBitmap::StretchBlt(HDC hdc,int x,int y,int nWid,int nHei,int xSrc,int ySrc,int nWidSrc,int nHeiSrc,BYTE byAlpha/*=0xFF*/)
{
	if(IsEmpty()) return FALSE;
	if(nWid==nWidSrc && nHei==nHeiSrc) return BitBlt(hdc,x,y,nWid,nHei,xSrc,ySrc,byAlpha);
	BOOL bRet=FALSE;
	HDC hMemdc=CreateCompatibleDC(hdc);
	HGDIOBJ hOldBmp=SelectObject(hMemdc,m_hBitmap);
	if(m_crMask!=CLR_INVALID)
	{
		bRet=TransparentBlt2(hdc,x,y,nWid,nHei,hMemdc,xSrc,ySrc,nWidSrc,nHeiSrc,m_crMask);
	}else
	{
		bRet=::StretchBlt(hdc,x,y,nWid,nHei,hMemdc,xSrc,ySrc,nWidSrc,nHeiSrc,SRCCOPY);
	}
	SelectObject(hMemdc,hOldBmp);
	DeleteDC(hMemdc);
	return bRet;
}

BOOL CDuiBitmap::TileBlt(HDC hdc,int x,int y,int nWid,int nHei,int xSrc,int ySrc,int nWidSrc,int nHeiSrc,BYTE byAlpha/*=0xFF*/)
{
	if(IsEmpty()) return FALSE;
	if(nWid==nWidSrc && nHei==nHeiSrc) return BitBlt(hdc,x,y,nWid,nHei,xSrc,ySrc,byAlpha);
	BOOL bRet=FALSE;
	HDC hMemdc=CreateCompatibleDC(hdc);
	HGDIOBJ hOldBmp=SelectObject(hMemdc,m_hBitmap);

	BOOL bTransDraw=m_crMask!=CLR_INVALID;

	int yt=y;
	while(yt<y+nHei)
	{
		int xt=x;
		int nHeiT=min(nHeiSrc,y+nHei-yt);
		while(xt<x+nWid)
		{
			int nWidT=min(nWidSrc,x+nWid-xt);
			if(bTransDraw)
			{
				bRet=TransparentBlt2(hdc,xt,yt,nWidT,nHeiT,hMemdc,xSrc,ySrc,nWidT,nHeiT,m_crMask);
			}else
			{
				bRet=::BitBlt(hdc,xt,yt,nWidT,nHeiT,hMemdc,xSrc,ySrc,SRCCOPY);
			}
			xt+=nWidT;
		}
		yt+=nHeiT;
	}
	SelectObject(hMemdc,hOldBmp);
	DeleteDC(hMemdc);
	return TRUE;
}

BOOL CDuiBitmap::LoadImg(LPCTSTR pszFileName)
{
	Clear();
	m_hBitmap = (HBITMAP)::LoadImage(NULL, pszFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	if(m_hBitmap)
	{
		m_bManaged=TRUE;
	}
	return !IsEmpty();
}

BOOL CDuiBitmap::LoadImg(UINT nIDResource,LPCSTR pszType/*=NULL*/)
{
	Clear();
	CResBase *pRes=DuiSystem::getSingleton().GetResProvider()->GetRes(pszType,nIDResource);
	if(!pRes) return FALSE;

	if(RES_FILE==pRes->GetResMode())
	{
		CResFile *pResFile=static_cast<CResFile*>(pRes);
		m_hBitmap = (HBITMAP)::LoadImageA(NULL, pResFile->strFilePath, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	}else if(RES_PE==pRes->GetResMode())
	{
		CResPE *pResPE=static_cast<CResPE*>(pRes);
		m_hBitmap = LoadBitmap(pResPE->hInst,MAKEINTRESOURCE(pResPE->uID));
	}
	delete pRes;
	if(!m_hBitmap) return FALSE;
	m_bManaged=TRUE;
	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
// CDuiImgX

ULONG_PTR CDuiImgX::s_gdiplusToken = 0;

CDuiImgX::CDuiImgX():m_pImg(NULL)
{

}

CDuiImgX::CDuiImgX(HBITMAP hBmp)
{
	m_pImg=new Gdiplus::Bitmap(hBmp,NULL);
}

void CDuiImgX::Clear()
{
	if(m_pImg) delete m_pImg;
	m_pImg=NULL;
}
BOOL CDuiImgX::IsEmpty(){return m_pImg==NULL;}
BOOL CDuiImgX::GetImageSize(SIZE &sz)
{
	if(IsEmpty()) return FALSE;
	sz.cx=m_pImg->GetWidth();
	sz.cy=m_pImg->GetHeight();
	return TRUE;			
}

int CDuiImgX::GetWidth()
{
	if(IsEmpty()) return 0;
	return m_pImg->GetWidth();
}

int CDuiImgX::GetHeight()
{
	if(IsEmpty()) return 0;
	return m_pImg->GetHeight();
}

BOOL CDuiImgX::BitBlt(HDC hdc,int x,int y,int nWid,int nHei,int xSrc,int ySrc,BYTE byAlpha/*=0xFF*/)
{
	if(IsEmpty()) return FALSE;
	Gdiplus::Graphics graphics(hdc);
	Gdiplus::ImageAttributes *pImgAttr=NULL;
	if(byAlpha!=0xFF)
	{
		Gdiplus::ColorMatrix ClrMatrix =         { 
			1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, float(byAlpha)/0xFF, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f
		};
		pImgAttr=new Gdiplus::ImageAttributes;
		pImgAttr->SetColorMatrix(&ClrMatrix);
	}
	BOOL bRet= 0==graphics.DrawImage(m_pImg,Gdiplus::Rect(x,y,nWid,nHei),xSrc,ySrc,nWid,nHei,Gdiplus::UnitPixel,pImgAttr);
	if(byAlpha!=0xFF)
	{
		delete pImgAttr;
	}
	return bRet;
}

BOOL CDuiImgX::StretchBlt(HDC hdc,int x,int y,int nWid,int nHei,int xSrc,int ySrc,int nWidSrc,int nHeiSrc,BYTE byAlpha/*=0xFF*/)
{
	if(IsEmpty()) return FALSE;
	Gdiplus::Graphics graphics(hdc);
	Gdiplus::ImageAttributes *pImgAttr=NULL;
	if(byAlpha!=0xFF)
	{
		Gdiplus::ColorMatrix ClrMatrix =         { 
			1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, float(byAlpha)/0xFF, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f
		};
		pImgAttr=new Gdiplus::ImageAttributes;
		pImgAttr->SetColorMatrix(&ClrMatrix);
	}
	BOOL bRet= 0==graphics.DrawImage(m_pImg,Gdiplus::Rect(x,y,nWid,nHei),xSrc,ySrc,nWidSrc,nHeiSrc,Gdiplus::UnitPixel,pImgAttr);
	if(byAlpha!=0xFF)
	{
		delete pImgAttr;
	}
	ATLASSERT(bRet);
	return bRet;
}
BOOL CDuiImgX::TileBlt(HDC hdc,int x,int y,int nWid,int nHei,int xSrc,int ySrc,int nWidSrc,int nHeiSrc,BYTE byAlpha/*=0xFF*/)
{
	if(IsEmpty()) return FALSE;
	if(nWid==nWidSrc && nHei==nHeiSrc) return BitBlt(hdc,x,y,nWid,nHei,xSrc,ySrc,byAlpha);
	Gdiplus::Graphics graphics(hdc);
	Gdiplus::ImageAttributes *pImgAttr=NULL;
	if(byAlpha!=0xFF)
	{
		Gdiplus::ColorMatrix ClrMatrix =         { 
			1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, float(byAlpha)/0xFF, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f
		};
		pImgAttr=new Gdiplus::ImageAttributes;
		pImgAttr->SetColorMatrix(&ClrMatrix);
	}
	int yt=y;
	while(yt<y+nHei)
	{
		int xt=x;
		int nHeiT=min(nHeiSrc,y+nHei-yt);
		while(xt<x+nWid)
		{
			int nWidT=min(nWidSrc,x+nWid-xt);
			graphics.DrawImage(m_pImg,Gdiplus::Rect(xt,yt,nWidT,nHeiT),xSrc,ySrc,nWidSrc,nHeiSrc,Gdiplus::UnitPixel,pImgAttr);
			xt+=nWidT;
		}
		yt+=nHeiT;
	}
	if(byAlpha!=0xFF)
	{
		delete pImgAttr;
	}
	return TRUE;
}


BOOL CDuiImgX::LoadImg(LPCTSTR pszFileName)
{
	Clear();
#ifdef _UNICODE
	Gdiplus::Image *pImg=new Gdiplus::Image(pszFileName);
#else
	WCHAR szFileName[MAX_PATH+1];
	MultiByteToWideChar(CP_ACP,0,pszFileName,-1,szFileName,MAX_PATH);
	Gdiplus::Image *pImg=new Gdiplus::Image(szFileName);
#endif
	if(pImg->GetLastStatus() != 0)
	{
		delete pImg;
		m_pImg=NULL;
	}
	m_pImg=new Gdiplus::Bitmap(pImg->GetWidth(),pImg->GetHeight());
	Gdiplus::Graphics *g=new Gdiplus::Graphics(m_pImg);
	g->DrawImage(pImg,0,0,pImg->GetWidth(),pImg->GetHeight());
	delete g;
	delete pImg;

	return !IsEmpty();
}


BOOL CDuiImgX::LoadImg(UINT nIDResource,LPCSTR pszType)
{
	Clear();

	CResBase *pRes=DuiSystem::getSingleton().GetResProvider()->GetRes(pszType,nIDResource);
	if(!pRes) return FALSE;

	if(RES_FILE==pRes->GetResMode())
	{
		CResFile *pResFile=static_cast<CResFile*>(pRes);
		CStringW strFilePath=CA2W(pResFile->strFilePath);
		m_pImg=new Gdiplus::Image(strFilePath);
	}else if(RES_PE==pRes->GetResMode())
	{
		CResPE *pResPE=static_cast<CResPE*>(pRes);
		CMyBuffer<char> imgBuf;
		if(pResPE->GetResBuffer(imgBuf))
		{
			int len = imgBuf.size();
			HGLOBAL hMem = ::GlobalAlloc(GMEM_FIXED, len);
			BYTE* pMem = (BYTE*)::GlobalLock(hMem);

			memcpy(pMem, imgBuf, len);

			IStream* pStm = NULL;
			::CreateStreamOnHGlobal(hMem, TRUE, &pStm);

			m_pImg = Gdiplus::Image::FromStream(pStm);

			::GlobalUnlock(hMem);
			pStm->Release();
		}
	}
	delete pRes;

	if(m_pImg && m_pImg->GetLastStatus() != 0)
	{
		delete m_pImg;
		m_pImg=NULL;
	}
	return !IsEmpty();
}


void CDuiImgX::InitGdiplus()
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&s_gdiplusToken, &gdiplusStartupInput, NULL);
}
void CDuiImgX::UninitGdiplus()
{
	Gdiplus::GdiplusShutdown(s_gdiplusToken);
}


}//namespace DuiEngine