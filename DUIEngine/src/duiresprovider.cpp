//////////////////////////////////////////////////////////////////////////
//   File Name: duiresprovider.cpp
// Description: Resource Provider
//////////////////////////////////////////////////////////////////////////
#include "duistd.h"
#include "duiresprovider.h"
#include "mybuffer.h"
#include <io.h>

namespace DuiEngine
{

DuiResProviderPE::DuiResProviderPE( HINSTANCE hInst ,CDuiImgDecoder *pImgDecoder)
    : DuiResProviderBase(pImgDecoder),m_hResInst(hInst)
{

}

HBITMAP DuiResProviderPE::LoadBitmap( LPCSTR strType,UINT uID )
{
    return LoadBitmapA(m_hResInst,MAKEINTRESOURCEA(uID));
}

HICON DuiResProviderPE::LoadIcon( LPCSTR strType,UINT uID ,int cx/*=0*/,int cy/*=0*/)
{
    return (HICON)::LoadImageA(m_hResInst, MAKEINTRESOURCEA(uID), IMAGE_ICON, cx, cy, LR_DEFAULTCOLOR);
}

CDuiImgBase * DuiResProviderPE::LoadImage( LPCSTR strType,UINT uID )
{
    if(!HasResource(strType,uID)) return NULL;
    CDuiImgBase *pImg=GetImageDecoder()->CreateDuiImage(strType);
    if(pImg)
    {
        if(!pImg->LoadFromResource(m_hResInst,strType,uID))
        {
            GetImageDecoder()->DestoryDuiImage(pImg);
            pImg=NULL;
        }
    }
    return pImg;
}

size_t DuiResProviderPE::GetRawBufferSize( LPCSTR strType,UINT uID )
{
    HRSRC hRsrc = MyFindResource(strType,uID);

    if (NULL == hRsrc)
        return 0;

    return ::SizeofResource(m_hResInst, hRsrc);
}

BOOL DuiResProviderPE::GetRawBuffer( LPCSTR strType,UINT uID,LPVOID pBuf,size_t size )
{
    DUIASSERT(strType);
    HRSRC hRsrc = MyFindResource(strType,uID);

    if (NULL == hRsrc)
        return FALSE;

    size_t dwSize = ::SizeofResource(m_hResInst, hRsrc);
    if (0 == dwSize)
        return FALSE;

    if(size < dwSize)
    {
        SetLastError(ERROR_INSUFFICIENT_BUFFER);
        return FALSE;
    }
    HGLOBAL hGlobal = ::LoadResource(m_hResInst, hRsrc);
    if (NULL == hGlobal)
        return FALSE;

    LPVOID pBuffer = ::LockResource(hGlobal);
    if (NULL == pBuffer)
        return FALSE;

    memcpy(pBuf,pBuffer,dwSize);

    ::FreeResource(hGlobal);

    return TRUE;
}

BOOL DuiResProviderPE::HasResource( LPCSTR strType,UINT uID )
{
    DUIASSERT(strType);
    return MyFindResource(strType,uID)!=NULL;
}

HRSRC DuiResProviderPE::MyFindResource( LPCSTR strType, UINT uID )
{
    if(_stricmp(strType,DUIRES_BMP_TYPE)==0) strType=MAKEINTRESOURCEA(2);//RT_BITMAP;
    else if(_stricmp(strType,DUIRES_ICON_TYPE)==0) strType=MAKEINTRESOURCEA(3);//RT_ICON;

    return ::FindResourceA(m_hResInst, MAKEINTRESOURCEA(uID), strType);
}


DuiResProviderFiles::DuiResProviderFiles(CDuiImgDecoder *pImgDecoder):DuiResProviderBase(pImgDecoder)
{
}

CDuiStringA DuiResProviderFiles::GetRes( LPCSTR strType,UINT uID )
{
    DuiResID resID(strType,uID);
    CDuiMap<DuiResID,CDuiStringA>::CPair *p=m_mapFiles.Lookup(resID);
    if(!p) return "";
    CDuiStringA strRet=m_strPath+"\\"+p->m_value;
    return strRet;
}

HBITMAP DuiResProviderFiles::LoadBitmap( LPCSTR strType,UINT uID )
{
    CDuiStringA strPath=GetRes(strType,uID);
    if(strPath.IsEmpty()) return NULL;
    return (HBITMAP)::LoadImageA(NULL, strPath, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
}

HICON DuiResProviderFiles::LoadIcon( LPCSTR strType,UINT uID ,int cx/*=0*/,int cy/*=0*/)
{
    CDuiStringA strPath=GetRes(strType,uID);
    if(strPath.IsEmpty()) return NULL;
    return (HICON)::LoadImageA(NULL, strPath, IMAGE_ICON, cx, cy, LR_LOADFROMFILE);
}

CDuiImgBase * DuiResProviderFiles::LoadImage( LPCSTR strType,UINT uID )
{
    if(!HasResource(strType,uID)) return NULL;
    CDuiImgBase * pImg=GetImageDecoder()->CreateDuiImage(strType);
    if(pImg)
    {
        CDuiStringA strPath=GetRes(strType,uID);
        if(!pImg->LoadFromFile(strPath))
        {
            GetImageDecoder()->DestoryDuiImage(pImg);
            pImg=NULL;
        }
    }
    return pImg;
}

size_t DuiResProviderFiles::GetRawBufferSize( LPCSTR strType,UINT uID )
{
    CDuiStringA strPath=GetRes(strType,uID);
    if(strPath.IsEmpty()) return 0;
    WIN32_FIND_DATAA wfd;
    HANDLE hf=FindFirstFileA(strPath,&wfd);
    if(INVALID_HANDLE_VALUE==hf) return 0;
    FindClose(hf);
    return wfd.nFileSizeLow;
}

BOOL DuiResProviderFiles::GetRawBuffer( LPCSTR strType,UINT uID,LPVOID pBuf,size_t size )
{
    CDuiStringA strPath=GetRes(strType,uID);
    if(strPath.IsEmpty()) return FALSE;
    FILE *f=fopen(strPath,"rb");
    if(!f) return FALSE;
    size_t len=_filelength(_fileno(f));
    if(len>size)
    {
        SetLastError(ERROR_INSUFFICIENT_BUFFER);
        fclose(f);
        return FALSE;
    }
    BOOL bRet=(len==fread(pBuf,1,len,f));

    fclose(f);
    return bRet;
}

BOOL DuiResProviderFiles::Init( LPCSTR pszPath )
{
    CMyBuffer<char>  xmlBuf;
    CDuiStringA strPathIndex=pszPath;
    strPathIndex+="\\";
    strPathIndex+=INDEX_XML;
    FILE *f=fopen(strPathIndex,"rb");
    if(!f) return(FALSE);
    int nLen=_filelength(_fileno(f));
    if(nLen>100*1024)
    {
        fclose(f);
        return FALSE;
    }
    xmlBuf.Allocate(nLen);
    if(nLen!=fread(xmlBuf,1,nLen,f))
    {
        fclose(f);
        return FALSE;
    }
    fclose(f);

    TiXmlDocument xmlDoc;
    CDuiStringA strFileName;

    xmlDoc.Parse(xmlBuf);
    if(xmlDoc.Error()) return FALSE;
    TiXmlElement *pXmlElem = xmlDoc.RootElement();
    while(pXmlElem)
    {
        CDuiStringA strValue = pXmlElem->Value();
        if(strValue=="resid")
        {
            DuiResID id(pXmlElem->Attribute("type"));
            pXmlElem->Attribute("id",&(int)id.nID);
            CDuiStringA strFile = pXmlElem->Attribute("file");
            CDuiStringW strFileW=DUI_CA2W(strFile,CP_UTF8);
            strFile=DUI_CW2A(strFileW);
            if(!m_strPath.IsEmpty()) strFile.Format("%s\\%s",(LPCSTR)m_strPath,(LPCSTR)strFile);
            m_mapFiles[id]=strFile;
        }
        pXmlElem=pXmlElem->NextSiblingElement();
    }

    m_strPath=pszPath;
    return TRUE;
}

BOOL DuiResProviderFiles::HasResource( LPCSTR strType,UINT uID )
{
    DuiResID resID(strType,uID);
    CDuiMap<DuiResID,CDuiStringA>::CPair *p=m_mapFiles.Lookup(resID);
    return (p!=NULL);
}

}//namespace DuiEngine