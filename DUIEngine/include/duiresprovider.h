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
		DuiResProviderPE(HINSTANCE hInst);
		HBITMAP	LoadBitmap(LPCSTR strType,UINT uID);
		HICON   LoadIcon(LPCSTR strType,UINT uID,int cx=0,int cy=0);
		Gdiplus::Image * LoadImage(LPCSTR strType,UINT uID);
		size_t GetRawBufferSize(LPCSTR strType,UINT uID);
		BOOL GetRawBuffer(LPCSTR strType,UINT uID,LPVOID pBuf,size_t size);
	protected:
		HINSTANCE m_hResInst;
	};

	class DUI_EXP DuiResProviderFiles:public DuiResProviderBase
	{
	public:

		DuiResProviderFiles(const CStringA & strPath);

		HBITMAP	LoadBitmap(LPCSTR strType,UINT uID);
		HICON   LoadIcon(LPCSTR strType,UINT uID,int cx=0,int cy=0);
		Gdiplus::Image * LoadImage(LPCSTR strType,UINT uID);
		size_t GetRawBufferSize(LPCSTR strType,UINT uID);
		BOOL GetRawBuffer(LPCSTR strType,UINT uID,LPVOID pBuf,size_t size);

	protected:
		CStringA GetRes( LPCSTR strType,UINT uID );

		BOOL AddIdMap(const CStringA & strIdmapFile);
		CStringA m_strPath;
		std::map<DuiResID,CStringA> m_mapFiles;
	};

}//namespace DuiEngine