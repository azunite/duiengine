#ifndef _DUIRESPROVIDERBASE_
#define _DUIRESPROVIDERBASE_
#pragma once

#include "DuiImgBase.h"
#include "DuiImgDecoder_Def.h"

#define DUIRES_XML_TYPE "XML"
#define DUIRES_IMGX_TYPE "IMGX"
#define DUIRES_BMP_TYPE "BMP"
#define DUIRES_ICON_TYPE "ICO"

#define INDEX_XML	"index.xml"		//文件夹资源的文件映射表索引表文件名

#define MAX_RES_TYPE		10

#ifdef _DEBUG
#include <crtdbg.h>
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

	class DUI_EXP DuiResID
	{
	public:
		DuiResID(LPCSTR pszType,UINT id=0)
		{
			if(pszType)
			{
				strcpy_s(szType,MAX_RES_TYPE,pszType);
			}else
			{
				szType[0]=0;
			}
			nID=(int)id;
		}

		char szType[MAX_RES_TYPE+1];
		int	 nID;
	};


	template<>
	class DUI_EXP CElementTraits< DuiResID > :
		public CElementTraitsBase< DuiResID >
	{
	public:
		static ULONG Hash( INARGTYPE resid )
		{
			ULONG_PTR uRet=0;
			CStringA strType=resid.szType;
			strType.MakeLower();
			for(int i=0;i<strType.GetLength();i++)
			{
				uRet=uRet*68+strType[i];
			}

			return (ULONG)(uRet*10000+(UINT)resid.nID);
		}

		static bool CompareElements( INARGTYPE element1, INARGTYPE element2 )
		{
			return _stricmp(element1.szType,element2.szType)==0 && element1.nID==element2.nID;
		}

		static int CompareElementsOrdered( INARGTYPE element1, INARGTYPE element2 )
		{
			int nRet=_stricmp(element1.szType,element2.szType);
			if(nRet<0) return -1;
			if(nRet>0) return 1;
			return element1.nID-element2.nID;
		}
	};

	class DUI_EXP DuiResProviderBase
	{
	public:
		DuiResProviderBase(CDuiImgDecoder *pImgDecoder)
		{
			if(pImgDecoder==NULL)
			{
				m_bDefImgDecoder=TRUE;
				m_pImgDecoder=new CDuiImgDecoder_Def;
			}else
			{
				m_bDefImgDecoder=FALSE;
				m_pImgDecoder=pImgDecoder;
			}
		}
		virtual ~DuiResProviderBase(){
			if(m_bDefImgDecoder) delete m_pImgDecoder;
		}
		virtual BOOL HasResource(LPCSTR strType,UINT uID)=NULL;
		virtual HICON   LoadIcon(LPCSTR strType,UINT uID,int cx=0,int cy=0)=NULL;
		virtual HBITMAP	LoadBitmap(LPCSTR strType,UINT uID)=NULL;
		virtual CDuiImgBase * LoadImage(LPCSTR strType,UINT uID)=NULL;
		virtual size_t GetRawBufferSize(LPCSTR strType,UINT uID)=NULL;
		virtual BOOL GetRawBuffer(LPCSTR strType,UINT uID,LPVOID pBuf,size_t size)=NULL;

		CDuiImgDecoder *GetImageDecoder(){return m_pImgDecoder;};
	protected:
		CDuiImgDecoder * m_pImgDecoder;
		BOOL	m_bDefImgDecoder;
	};
}//namespace DuiEngine
#endif//_DUIRESPROVIDERBASE_
