#pragma once

#ifndef DUI_EXP
#define DUI_EXP
#endif

#include "../../DUIEngine/include/duiresproviderbase.h"
#include "../../DUIEngine/include/DuiImgBase.h"

#include "ZipArchive.h"

namespace DuiEngine{

class DuiResProviderBase;

class DuiResProviderZip : public DuiResProviderBase
{
public:
	DuiResProviderZip(CDuiImgDecoder *pImgDecoder=NULL);
	~DuiResProviderZip(void);

	HBITMAP	LoadBitmap(LPCTSTR strType,UINT uID);
	HICON   LoadIcon(LPCTSTR strType,UINT uID,int cx=0,int cy=0);
	CDuiImgBase * LoadImage(LPCTSTR strType,UINT uID);
	size_t GetRawBufferSize(LPCTSTR strType,UINT uID);
	BOOL GetRawBuffer(LPCTSTR strType,UINT uID,LPVOID pBuf,size_t size);
	BOOL HasResource(LPCTSTR strType,UINT uID);

	BOOL Init(LPCTSTR pszZipFile);
	BOOL Init(HINSTANCE hInst,UINT uID,LPCTSTR pszType=_T("ZIP"));
protected:
	BOOL LoadSkin();
	CDuiStringT GetFilePath(UINT uID,LPCTSTR pszType);
	CDuiMap<DuiResID,CDuiStringT> m_mapFiles;

	CZipArchive m_zipFile;
};

}//namespace DuiEngine
