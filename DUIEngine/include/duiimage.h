//////////////////////////////////////////////////////////////////////////
//  Module: DUI Image Loader
//	version 1.0 Huang jianxiong
//////////////////////////////////////////////////////////////////////////

#pragma once

#include <GdiPlus.h>

namespace DuiEngine{


class DUI_EXP CDuiImgBase : public CDuiObject
{
public:
	virtual ~CDuiImgBase(){}
	virtual void Clear()=NULL;
	virtual BOOL GetImageSize(SIZE & sz)=NULL;
	virtual int GetWidth()=NULL;
	virtual int GetHeight()=NULL;
	virtual BOOL IsEmpty(){return TRUE;}
	virtual BOOL BitBlt(HDC hdc,int x,int y,int nWid,int nHei,int xSrc,int ySrc,BYTE byAlpha=0xFF)=NULL;
	virtual BOOL StretchBlt(HDC hdc,int x,int y,int nWid,int nHei,int xSrc,int ySrc,int nWidSrc,int nHeiSrc,BYTE byAlpha=0xFF)=NULL;
	virtual BOOL TileBlt(HDC hdc,int x,int y,int nWid,int nHei,int xSrc,int ySrc,int nWidSrc,int nHeiSrc,BYTE byAlpha=0xFF)=NULL;
	virtual BOOL LoadImg(LPCTSTR pszFileName)=NULL;
	virtual BOOL LoadImg(UINT nIDResource,LPCSTR pszType)=NULL;
};


class DUI_EXP CDuiBitmap : public CDuiImgBase
{
public:
	DUIOBJ_DECLARE_CLASS_NAME(CDuiBitmap, "DuiBitmap")
	CDuiBitmap();
	~CDuiBitmap(){Clear();}

	CDuiBitmap(HBITMAP hBitmap);

	operator HBITMAP()  const;

	virtual void Clear();

	virtual BOOL IsEmpty();
	virtual BOOL GetImageSize(SIZE & sz);

	virtual int GetWidth();

	virtual int GetHeight();

	virtual BOOL BitBlt(HDC hdc,int x,int y,int nWid,int nHei,int xSrc,int ySrc,BYTE byAlpha=0xFF);

	virtual BOOL StretchBlt(HDC hdc,int x,int y,int nWid,int nHei,int xSrc,int ySrc,int nWidSrc,int nHeiSrc,BYTE byAlpha=0xFF);

	virtual BOOL TileBlt(HDC hdc,int x,int y,int nWid,int nHei,int xSrc,int ySrc,int nWidSrc,int nHeiSrc,BYTE byAlpha=0xFF);

	virtual BOOL LoadImg(LPCTSTR pszFileName);

	virtual BOOL LoadImg(UINT nIDResource,LPCSTR pszType);

	DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
		DUIWIN_COLOR_ATTRIBUTE("mask", m_crMask, TRUE)
	DUIWIN_DECLARE_ATTRIBUTES_END()
protected:
	HBITMAP m_hBitmap;
	COLORREF	m_crMask;
	BOOL	m_bManaged;
};

class DUI_EXP CDuiImgX :public CDuiImgBase
{
public:
	DUIOBJ_DECLARE_CLASS_NAME(CDuiImgX, "DuiImgX")
	CDuiImgX();

	CDuiImgX(HBITMAP hBmp);
	~CDuiImgX(){Clear();}

	virtual void Clear();
	virtual BOOL IsEmpty();
	virtual BOOL GetImageSize(SIZE &sz);

	virtual int GetWidth();

	virtual int GetHeight();

	virtual BOOL BitBlt(HDC hdc,int x,int y,int nWid,int nHei,int xSrc,int ySrc,BYTE byAlpha=0xFF);

	virtual BOOL StretchBlt(HDC hdc,int x,int y,int nWid,int nHei,int xSrc,int ySrc,int nWidSrc,int nHeiSrc,BYTE byAlpha=0xFF);
	virtual BOOL TileBlt(HDC hdc,int x,int y,int nWid,int nHei,int xSrc,int ySrc,int nWidSrc,int nHeiSrc,BYTE byAlpha=0xFF);


	virtual BOOL LoadImg(LPCTSTR pszFileName);

	virtual BOOL LoadImg(UINT nIDResource,LPCSTR pszType);

	Gdiplus::Image * GetImage() const {return m_pImg;}

	static void InitGdiplus();
	static void UninitGdiplus();
protected:
	Gdiplus::Image *m_pImg;
	static ULONG_PTR s_gdiplusToken;
};

}//namespace DuiEngine