#pragma once

namespace DuiEngine{

class DUI_EXP CMemDC :	public CDC
{
public:
	CMemDC();
	CMemDC(HDC hdc, const CRect & rc);
	CMemDC(HDC hdc, HBITMAP hBmp);
	~CMemDC(void);

	HBITMAP SelectBitmap(HBITMAP hBmp);
	BOOL	HasBitmap(){return m_bHasBitmap;}
protected:
	HBITMAP		m_hOldBmp;
	BOOL		m_bBmpOwner;
	BOOL		m_bHasBitmap;
};

}//namespace DuiEngine