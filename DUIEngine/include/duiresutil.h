//////////////////////////////////////////////////////////////////////////
//   File Name: bkresutil.h
// Description: Beike Resource Helper
//     Creator: Zhang Xiaoxuan
//     Version: 2009.5.13 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "DuiSingletonMap.h"

#define DUIRES_XML_TYPE _T("xml")
#define DUIRES_IMGX_TYPE _T("imgx")

#ifdef _DEBUG
#   define DUIRES_ASSERTW(expr, format, ...) \
    (void) ((!!(expr)) || \
    (1 != _CrtDbgReportW(_CRT_ASSERT, _CRT_WIDE(__FILE__), __LINE__, NULL, format, __VA_ARGS__)) || \
    (_CrtDbgBreak(), 0))

#   define DUIRES_ASSERTA(expr, format, ...) \
	(void) ((!!(expr)) || \
	(1 != _CrtDbgReport(_CRT_ASSERT, __FILE__, __LINE__, NULL, format, __VA_ARGS__)) || \
	(_CrtDbgBreak(), 0))

#else
#   define DUIRES_ASSERTW
#	define DUIRES_ASSERTA
#endif


class DuiResID
{
public:
	DuiResID(CStringA str="",int id=0)
	{
		strType=str;
		nID=id;
	}

	CStringA strType;
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
		CStringA strType=resid.strType;
		strType.MakeLower();
		for(int i=0;i<strType.GetLength();i++)
		{
			uRet=uRet*68+strType[i];
		}

		return (ULONG)(uRet*10000+(UINT)resid.nID);
	}

	static bool CompareElements( INARGTYPE element1, INARGTYPE element2 )
	{
		return _stricmp(element1.strType,element2.strType)==0 && element1.nID==element2.nID;
	}

	static int CompareElementsOrdered( INARGTYPE element1, INARGTYPE element2 )
	{
		int nRet=_stricmp(element1.strType,element2.strType);
		if(nRet<0) return -1;
		if(nRet>0) return 1;
		return element1.nID-element2.nID;
	}
};

namespace DuiEngine{

class DUI_EXP DuiResManager : public DuiSingletonMap<DuiResManager,CStringA,DuiResID>
{
public:
	DuiResManager():m_hInstanceRes(NULL){}

    BOOL SetResourcePath(LPCSTR lpszPath,LPCSTR lpszXmlIDFile);

    void SetResourceDLL(LPCTSTR lpszPath);
	
	void SetResourceDLL(HINSTANCE hInst);

    BOOL LoadResource(UINT uResID, CStringA &strBuffRet, LPCTSTR lpszResType = DUIRES_XML_TYPE);

    BOOL LoadResource(UINT uResID, HBITMAP &hBitmap);

	BOOL LoadResource(UINT uResID, HICON &hIcon,int nSize);

protected:

    BOOL _LoadEmbedResource(UINT uResID, CStringA &strRet, LPCTSTR lpszResType = DUIRES_XML_TYPE);

    CStringA m_strResourcePath;
    HINSTANCE m_hInstanceRes;
};

}//namespace DuiEngine