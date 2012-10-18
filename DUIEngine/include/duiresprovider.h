//////////////////////////////////////////////////////////////////////////
//   File Name: duiresprovider.h
// Description: Resource Provider
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "DuiSingletonMap.h"
#include "mybuffer.h"
#include <vector>
#include <io.h>
#include <GdiPlus.h>

#define DUIRES_XML_TYPE "xml"
#define DUIRES_IMGX_TYPE "imgx"
#define DUIRES_BMP_TYPE "bitmap"
#define DUIRES_ICON_TYPE "icon"

#define EXT_IDMAP	"idmap"		//文件夹资源的文件映射表扩展名

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
		DuiResID(CStringA str="",UINT id=0)
		{
			strType=str;
			nID=(int)id;
		}

		bool operator < ( const DuiResID & rt) const
		{
			int nret=_stricmp(strType,rt.strType);
			if(nret==0) nret=(int)(nID-rt.nID);
			return nret<0;
		}

		CStringA strType;
		int	 nID;
	};

	class DUI_EXP DuiResProviderBase
	{
	public:
		virtual ~DuiResProviderBase(){}
		virtual HBITMAP	LoadBitmap(LPCSTR strType,UINT uID)=NULL;
		virtual HICON   LoadIcon(LPCSTR strType,UINT uID)=NULL;
		virtual Gdiplus::Image * LoadImage(LPCSTR strType,UINT uID)=NULL;
		virtual BOOL GetResBuffer(LPCSTR strType,UINT uID,CMyBuffer<char> & buf)=NULL;
	};

	class DUI_EXP DuiResProviderPE:public DuiResProviderBase
	{
	public:
		DuiResProviderPE(HINSTANCE hInst):m_hResInst(hInst)
		{
		}
		HBITMAP	LoadBitmap(LPCSTR strType,UINT uID);
		HICON   LoadIcon(LPCSTR strType,UINT uID);
		Gdiplus::Image * LoadImage(LPCSTR strType,UINT uID);
		BOOL GetResBuffer(LPCSTR strType,UINT uID,CMyBuffer<char> & buf);

	protected:
		HINSTANCE m_hResInst;
	};

	class DUI_EXP DuiResProviderFiles:public DuiResProviderBase
	{
	public:

		DuiResProviderFiles(const CStringA & strPath);

		HBITMAP	LoadBitmap(LPCSTR strType,UINT uID);
		HICON   LoadIcon(LPCSTR strType,UINT uID);
		Gdiplus::Image * LoadImage(LPCSTR strType,UINT uID);
		BOOL GetResBuffer(LPCSTR strType,UINT uID,CMyBuffer<char> & buf);

	protected:
		CStringA GetRes( LPCSTR strType,UINT uID );

		BOOL AddIdMap(const CStringA & strIdmapFile);
		CStringA m_strPath;
		std::map<DuiResID,CStringA> m_mapFiles;
	};

}//namespace DuiEngine