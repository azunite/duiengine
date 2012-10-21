#pragma once

#ifdef DUI_DLL
#define DUI_EXP _cdecl(dllimport)
#else
#ifndef DUI_EXP
#define DUI_EXP
#endif
#endif

#include "../DUIEngine/include/wtl.mini/duistr.h"
#include "../DUIEngine/include/duiresproviderbase.h"

#include "ZipArchive.h"
#include <map>

namespace DuiEngine{

class DuiResProviderBase;

class DuiResProviderZip : public DuiResProviderBase
{
public:
	DuiResProviderZip();
	~DuiResProviderZip(void);

	HBITMAP	LoadBitmap(LPCSTR strType,UINT uID);
	HICON   LoadIcon(LPCSTR strType,UINT uID,int cx=0,int cy=0);
	Gdiplus::Image * LoadImage(LPCSTR strType,UINT uID);
	BOOL GetResBuffer(LPCSTR strType,UINT uID,CMyBuffer<char> & buf);

	BOOL OpenZip(LPCTSTR pszZipFile);
protected:
	CString GetFilePath(UINT uID,LPCSTR pszType);
	BOOL AddIdMap(const CZipFile & zipFile);
	std::map<DuiResID,CString> m_mapFiles;

	CZipArchive m_zipFile;
};

}//namespace DuiEngine
