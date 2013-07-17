//////////////////////////////////////////////////////////////////////////
//   File Name: duiresprovider.h
// Description: Resource Provider
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "duiresproviderbase.h"

namespace DuiEngine
{


class DUI_EXP DuiResProviderPE:public DuiResProviderBase
{
public:
    DuiResProviderPE(HINSTANCE hInst,CDuiImgDecoder *pImgDecoder=NULL);
    HBITMAP	LoadBitmap(LPCTSTR strType,UINT uID);
    HICON   LoadIcon(LPCTSTR strType,UINT uID,int cx=0,int cy=0);
    CDuiImgBase * LoadImage(LPCTSTR strType,UINT uID);
    size_t GetRawBufferSize(LPCTSTR strType,UINT uID);
    BOOL GetRawBuffer(LPCTSTR strType,UINT uID,LPVOID pBuf,size_t size);
    BOOL HasResource(LPCTSTR strType,UINT uID);

protected:
    HRSRC MyFindResource(LPCTSTR strType, UINT uID );
    HINSTANCE m_hResInst;
};

class DUI_EXP DuiResProviderFiles:public DuiResProviderBase
{
public:

    DuiResProviderFiles(CDuiImgDecoder *pImgDecoder=NULL);

    BOOL HasResource(LPCTSTR strType,UINT uID);
    HBITMAP	LoadBitmap(LPCTSTR strType,UINT uID);
    HICON   LoadIcon(LPCTSTR strType,UINT uID,int cx=0,int cy=0);
    CDuiImgBase * LoadImage(LPCTSTR strType,UINT uID);
    size_t GetRawBufferSize(LPCTSTR strType,UINT uID);
    BOOL GetRawBuffer(LPCTSTR strType,UINT uID,LPVOID pBuf,size_t size);

    BOOL Init(LPCTSTR pszPath);
protected:
    CDuiStringT GetRes( LPCTSTR strType,UINT uID );

    CDuiStringT m_strPath;
    CDuiMap<DuiResID,CDuiStringT> m_mapFiles;
};

}//namespace DuiEngine