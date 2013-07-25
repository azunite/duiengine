#ifndef _DUIRESPROVIDERBASE_
#define _DUIRESPROVIDERBASE_
#pragma once

#include "DuiImgBase.h"
#include "DuiImgDecoder_Def.h"

#define DUIRES_XML_TYPE _T("XML")
#define DUIRES_IMGX_TYPE _T("IMGX")
#define DUIRES_BMP_TYPE _T("BMP")
#define DUIRES_ICON_TYPE _T("ICO")

#define INDEX_XML	_T("index.xml")		//文件夹资源的文件映射表索引表文件名

#define MAX_RES_TYPE		10

class DUI_EXP DuiResID
{
public:
	DuiResID(LPCTSTR pszType,UINT id=0)
	{
		if(pszType)
		{
			_tcscpy_s(szType,MAX_RES_TYPE,pszType);
		}
		else
		{
			szType[0]=0;
		}
		nID=(int)id;
	}

	TCHAR szType[MAX_RES_TYPE+1];
	int	 nID;
};


template<>
class CElementTraits< DuiResID > :
	public CElementTraitsBase< DuiResID >
{
public:
	static ULONG Hash( INARGTYPE resid )
	{
		ULONG_PTR uRet=0;
		CDuiStringT strType=resid.szType;
		strType.MakeLower();
		for(int i=0; i<strType.GetLength(); i++)
		{
			uRet=uRet*68+strType[i];
		}

		return (ULONG)(uRet*10000+(UINT)resid.nID);
	}

	static bool CompareElements( INARGTYPE element1, INARGTYPE element2 )
	{
		return _tcsicmp(element1.szType,element2.szType)==0 && element1.nID==element2.nID;
	}

	static int CompareElementsOrdered( INARGTYPE element1, INARGTYPE element2 )
	{
		int nRet=_tcsicmp(element1.szType,element2.szType);
		if(nRet<0) return -1;
		if(nRet>0) return 1;
		return element1.nID-element2.nID;
	}
};

namespace DuiEngine
{


class DUI_EXP DuiResProviderBase
{
public:
    DuiResProviderBase(CDuiImgDecoder *pImgDecoder)
    {
        if(pImgDecoder==NULL)
        {
            m_bDefImgDecoder=TRUE;
            m_pImgDecoder=new CDuiImgDecoder_Def;
        }
        else
        {
            m_bDefImgDecoder=FALSE;
            m_pImgDecoder=pImgDecoder;
        }
    }
    virtual ~DuiResProviderBase()
    {
        if(m_bDefImgDecoder) delete m_pImgDecoder;
    }
    virtual BOOL HasResource(LPCTSTR strType,UINT uID)=NULL;
    virtual HICON   LoadIcon(LPCTSTR strType,UINT uID,int cx=0,int cy=0)=NULL;
    virtual HBITMAP	LoadBitmap(LPCTSTR strType,UINT uID)=NULL;
    virtual CDuiImgBase * LoadImage(LPCTSTR strType,UINT uID)=NULL;
    virtual size_t GetRawBufferSize(LPCTSTR strType,UINT uID)=NULL;
    virtual BOOL GetRawBuffer(LPCTSTR strType,UINT uID,LPVOID pBuf,size_t size)=NULL;

    CDuiImgDecoder *GetImageDecoder()
    {
        return m_pImgDecoder;
    };
protected:
    CDuiImgDecoder * m_pImgDecoder;
    BOOL	m_bDefImgDecoder;
};
}//namespace DuiEngine
#endif//_DUIRESPROVIDERBASE_
