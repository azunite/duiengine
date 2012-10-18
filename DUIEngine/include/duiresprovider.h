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

	class DUI_EXP CResBase
	{
	public:
		virtual ~CResBase(){}

		virtual HBITMAP	LoadBitmap()=NULL;
		virtual HICON   LoadIcon()=NULL;
		virtual Gdiplus::Image * LoadImage()=NULL;
		virtual BOOL GetResBuffer(CMyBuffer<char> & buf)=NULL;
	};

	class DUI_EXP CResPE:public CResBase
	{
	public:
		CResPE(HINSTANCE _hInst,UINT _uID,const CStringA & _strType);

		HBITMAP	LoadBitmap();
		HICON   LoadIcon();
		Gdiplus::Image * LoadImage();
		BOOL GetResBuffer(CMyBuffer<char> & buf);
	protected:
		HINSTANCE hInst;
		CStringA strType;
		UINT uID;
	};

	class DUI_EXP CResFile:public CResBase
	{
	public:
		CResFile(const CStringA & strFile);

		HBITMAP	LoadBitmap();
		HICON   LoadIcon();
		Gdiplus::Image * LoadImage();
		BOOL GetResBuffer(CMyBuffer<char> & buf);
	protected:
		CStringA	strFilePath;//文件路径
	};


	class DUI_EXP DuiResProviderBase
	{
	public:
		virtual ~DuiResProviderBase(){}
		virtual CResBase * GetRes(LPCSTR strResType,UINT uResID)=NULL;		
	};

	class DUI_EXP DuiResProviderPE:public DuiResProviderBase
	{
	public:
		DuiResProviderPE(HINSTANCE hInst):m_hResInst(hInst)
		{
		}

		CResBase * GetRes(LPCSTR strType,UINT uID);
	protected:
		HINSTANCE m_hResInst;
	};

	class DUI_EXP DuiResProviderFiles:public DuiResProviderBase
	{
	public:

		DuiResProviderFiles(const CStringA & strPath);

		CResBase * GetRes(LPCSTR strType,UINT uID);

	protected:
		BOOL AddIdMap(const CStringA & strIdmapFile);
		CStringA m_strPath;
		std::map<DuiResID,CStringA> m_mapFiles;
	};

}//namespace DuiEngine