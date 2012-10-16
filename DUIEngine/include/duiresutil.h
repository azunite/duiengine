//////////////////////////////////////////////////////////////////////////
//   File Name: duiresutil.h
// Description: Resource Manager
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "DuiSingletonMap.h"
#include "mybuffer.h"

#define DUIRES_XML_TYPE "xml"
#define DUIRES_IMGX_TYPE "imgx"

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


namespace DuiEngine{

	class DuiResID
	{
	public:
		DuiResID(CStringA str="",int id=0)
		{
			strType=str;
			nID=id;
		}

		bool operator < ( const DuiResID & rt) const
		{
			int nret=_stricmp(strType,rt.strType);
			if(nret==0) nret=nID-rt.nID;
			return nret<0;
		}

		CStringA strType;
		int	 nID;
	};


class DUI_EXP DuiResManager : public DuiSingletonMap<DuiResManager,CStringA,DuiResID>
{
public:
	DuiResManager():m_hInstanceRes(NULL){}

    BOOL SetResourcePath(LPCSTR lpszPath,LPCSTR lpszXmlIDFile);

    void SetResourceDLL(LPCTSTR lpszPath);
	
	void SetResourceDLL(HINSTANCE hInst);

    BOOL LoadResource(UINT uResID, CMyBuffer<char> &strBuffRet, LPCSTR lpszResType = DUIRES_XML_TYPE);

    BOOL LoadResource(UINT uResID, HBITMAP &hBitmap);

	BOOL LoadResource(UINT uResID, HICON &hIcon,int nSize);

protected:

    BOOL _LoadEmbedResource(UINT uResID, CMyBuffer<char> &strRet, LPCSTR lpszResType = DUIRES_XML_TYPE);

    CStringA m_strResourcePath;
    HINSTANCE m_hInstanceRes;
};

}//namespace DuiEngine