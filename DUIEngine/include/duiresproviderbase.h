#ifndef _DUIRESPROVIDERBASE_
#define _DUIRESPROVIDERBASE_
#pragma once

#include <GdiPlus.h>

#define DUIRES_XML_TYPE "XML"
#define DUIRES_IMGX_TYPE "IMGX"
#define DUIRES_BMP_TYPE "BMP"
#define DUIRES_ICON_TYPE "ICO"

#define INDEX_XML	"index.xml"		//文件夹资源的文件映射表索引表文件名

#define MAX_TYPE		10

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
		DuiResID(LPCSTR pszType,UINT id=0)
		{
			ATLASSERT(pszType);
			strcpy_s(szType,MAX_TYPE,pszType);
			nID=(int)id;
		}

		bool operator < ( const DuiResID & rt) const
		{
			int nret=_stricmp(szType,rt.szType);
			if(nret==0) nret=(int)(nID-rt.nID);
			return nret<0;
		}

		char szType[MAX_TYPE+1];
		int	 nID;
	};

	class DUI_EXP DuiResProviderBase
	{
	public:
		virtual ~DuiResProviderBase(){}
		virtual HBITMAP	LoadBitmap(LPCSTR strType,UINT uID)=NULL;
		virtual HICON   LoadIcon(LPCSTR strType,UINT uID,int cx=0,int cy=0)=NULL;
		virtual Gdiplus::Image * LoadImage(LPCSTR strType,UINT uID)=NULL;
		virtual size_t GetRawBufferSize(LPCSTR strType,UINT uID)=NULL;
		virtual BOOL GetRawBuffer(LPCSTR strType,UINT uID,LPVOID pBuf,size_t size)=NULL;
	};
}//namespace DuiEngine
#endif//_DUIRESPROVIDERBASE_
