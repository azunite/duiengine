#pragma once

#ifndef DUI_EXP
#define DUI_EXP
#endif

#include "../DUIEngine/dependencies/strcvt/cpconv.h"
#include "../duiengine/dependencies/tinyxml/tinyxml.h"
#include "../DUIEngine/include/duiresproviderbase.h"
#include "../DUIEngine/include/DuiImgBase.h"

#include "ZipArchive.h"
#include <map>


namespace DuiEngine{

class DuiResProviderBase;

class DuiResProviderZip : public DuiResProviderBase
{
public:
	DuiResProviderZip(CDuiImgDecoder *pImgDecoder=NULL);
	~DuiResProviderZip(void);

	HBITMAP	LoadBitmap(LPCSTR strType,UINT uID);
	HICON   LoadIcon(LPCSTR strType,UINT uID,int cx=0,int cy=0);
	CDuiImgBase * LoadImage(LPCSTR strType,UINT uID);
	size_t GetRawBufferSize(LPCSTR strType,UINT uID);
	BOOL GetRawBuffer(LPCSTR strType,UINT uID,LPVOID pBuf,size_t size);

	BOOL Init(LPCTSTR pszZipFile);
protected:
	CString GetFilePath(UINT uID,LPCSTR pszType);
	std::map<DuiResID,CString> m_mapFiles;

	CZipArchive m_zipFile;
};

}//namespace DuiEngine
