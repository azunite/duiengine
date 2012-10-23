#include "duistd.h"
#include "MemDC.h"
namespace DuiEngine{

CMemDC::CMemDC()
:m_bBmpOwner(FALSE)
,m_bHasBitmap(FALSE)
{
}

CMemDC::CMemDC( HDC hdc, const CRect & rc )
:m_bBmpOwner(TRUE)
,m_bHasBitmap(TRUE)
{
	CreateCompatibleDC(hdc);
	DUIASSERT(m_hDC != NULL);
	HBITMAP hBmp=CreateCompatibleBitmap(hdc,rc.Width(),rc.Height());
	m_hOldBmp=SelectBitmap(hBmp);
	SetViewportOrg(-rc.left, -rc.top);
}

CMemDC::CMemDC( HDC hdc,HBITMAP hBmp)
:m_bBmpOwner(FALSE)
,m_bHasBitmap(TRUE)
{
	CreateCompatibleDC(hdc);
	DUIASSERT(m_hDC != NULL);
	if(hBmp)
		m_hOldBmp=__super::SelectBitmap(hBmp);
	else
		m_hOldBmp=NULL;
	SetViewportOrg(0,0);
}

CMemDC::~CMemDC(void)
{
	if(m_hDC && m_hOldBmp)
	{
		HBITMAP hBmp=SelectBitmap(m_hOldBmp);
		if(m_bBmpOwner) DeleteObject(hBmp);
	}
}

HBITMAP CMemDC::SelectBitmap( HBITMAP hBmp )
{
	if(hBmp)
	{
		m_hOldBmp=__super::SelectBitmap(hBmp);
		m_bBmpOwner=FALSE;
		m_bHasBitmap=TRUE;
		SetViewportOrg(0,0);
		return m_hOldBmp;
	}else if(m_bHasBitmap)
	{
		HBITMAP hBmp=__super::SelectBitmap(m_hOldBmp);
		m_hOldBmp=NULL;
		m_bBmpOwner=FALSE;
		m_bHasBitmap=FALSE;
		return hBmp;
	}else
	{
		return NULL;
	}
}

}//namespace DuiEngine
