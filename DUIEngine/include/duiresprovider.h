//////////////////////////////////////////////////////////////////////////
//   File Name: duiresprovider.h
// Description: Resource Provider
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "duiresproviderbase.h"
#include <map>


namespace DuiEngine{


	class DUI_EXP DuiResProviderPE:public DuiResProviderBase
	{
	public:
		DuiResProviderPE(HINSTANCE hInst,CDuiImgDecoder *pImgDecoder=NULL);
		HBITMAP	LoadBitmap(LPCSTR strType,UINT uID);
		HICON   LoadIcon(LPCSTR strType,UINT uID,int cx=0,int cy=0);
		CDuiImgBase * LoadImage(LPCSTR strType,UINT uID);
		size_t GetRawBufferSize(LPCSTR strType,UINT uID);
		BOOL GetRawBuffer(LPCSTR strType,UINT uID,LPVOID pBuf,size_t size);
		BOOL HasResource(LPCSTR strType,UINT uID);

	protected:
		HINSTANCE m_hResInst;
	};

	class DUI_EXP DuiResProviderFiles:public DuiResProviderBase
	{
	public:

		DuiResProviderFiles(CDuiImgDecoder *pImgDecoder=NULL);

		BOOL HasResource(LPCSTR strType,UINT uID);
		HBITMAP	LoadBitmap(LPCSTR strType,UINT uID);
		HICON   LoadIcon(LPCSTR strType,UINT uID,int cx=0,int cy=0);
		CDuiImgBase * LoadImage(LPCSTR strType,UINT uID);
		size_t GetRawBufferSize(LPCSTR strType,UINT uID);
		BOOL GetRawBuffer(LPCSTR strType,UINT uID,LPVOID pBuf,size_t size);

		BOOL Init(LPCSTR pszPath);
	protected:
		CStringA GetRes( LPCSTR strType,UINT uID );

		CStringA m_strPath;
		std::map<DuiResID,CStringA> m_mapFiles;
	};

}//namespace DuiEngine