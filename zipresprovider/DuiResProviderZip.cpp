#include "stdafx.h"
#include "DuiResProviderZip.h"
#include "../tinyxml/tinyxml.h"
#include "../DUIEngine/include/cpconv.h"
#pragma comment(lib, "gdiplus.lib")

namespace DuiEngine{

DuiResProviderZip::DuiResProviderZip(void)
{
}

DuiResProviderZip::~DuiResProviderZip(void)
{
}

HBITMAP LoadBmpFromBuffer(char *pBuffer, int nLength)
{
	HBITMAP hBitmap;
	HDC hDC = GetDC(NULL);
	BITMAPFILEHEADER bfhHeader; 
	//读取位图头
	memcpy(&bfhHeader, pBuffer, sizeof(BITMAPFILEHEADER));
	//检测位图头
	if (bfhHeader.bfType != ((WORD) ('M'<<8)|'B')) 
	{
		return NULL; 
	} 
	//判断位图长度
	if (bfhHeader.bfSize != nLength) 
	{ 
		return NULL; 
	} 
	UINT uBmpInfoLen=(UINT) bfhHeader.bfOffBits-sizeof(BITMAPFILEHEADER); 
	LPBITMAPINFO lpBitmap=(LPBITMAPINFO) new BYTE[uBmpInfoLen]; 
	memcpy(lpBitmap, pBuffer + sizeof(BITMAPFILEHEADER), uBmpInfoLen);
	//检测格式是否正确
	if ((*(LPDWORD)(lpBitmap)) != sizeof(BITMAPINFOHEADER)) 
	{ 
		return NULL; 
	} 
	DWORD dwBitlen=bfhHeader.bfSize - bfhHeader.bfOffBits; 
	LPVOID lpBits=new BYTE[dwBitlen]; 
	memcpy(lpBits, pBuffer + sizeof(BITMAPFILEHEADER) + uBmpInfoLen,dwBitlen);
	LPVOID lpBitsT;
	hBitmap=::CreateDIBSection(hDC,lpBitmap,DIB_RGB_COLORS, 
		&lpBitsT,NULL,0); 
	if (hBitmap == NULL)
	{//创建失败
		return NULL;
	}
	//复制位图
	BITMAP bmp; 
	GetObject(hBitmap, sizeof(BITMAP), &bmp);
	DWORD dwCount = (DWORD) bmp.bmWidthBytes * bmp.bmHeight; 
	memcpy(bmp.bmBits,lpBits,dwCount); 
	ReleaseDC(NULL,hDC);
	return hBitmap;
}

HBITMAP DuiResProviderZip::LoadBitmap( LPCSTR strType,UINT uID )
{
	CString strPath=GetFilePath(uID,strType);
	if(strPath.IsEmpty()) return NULL;
	CZipFile zf;
	if(!m_zipFile.GetFile(strPath,zf)) return NULL;
	return LoadBmpFromBuffer((char*)zf.GetData(),zf.GetSize());
}

HICON DuiResProviderZip::LoadIcon( LPCSTR strType,UINT uID ,int cx/*=0*/,int cy/*=0*/)
{
	CString strPath=GetFilePath(uID,strType);
	if(strPath.IsEmpty()) return NULL;
	CZipFile zf;
	if(!m_zipFile.GetFile(strPath,zf)) return NULL;

	return CreateIconFromResourceEx(zf.GetData(),zf.GetSize(),TRUE,0,cx,cy,LR_DEFAULTCOLOR|LR_DEFAULTSIZE);
}

Gdiplus::Image * DuiResProviderZip::LoadImage( LPCSTR strType,UINT uID )
{
	CString strPath=GetFilePath(uID,strType);
	if(strPath.IsEmpty()) return NULL;
	CZipFile zf;
	if(!m_zipFile.GetFile(strPath,zf)) return NULL;

	Gdiplus::Image *pImage=NULL;

	HGLOBAL hMem = ::GlobalAlloc(GMEM_FIXED, zf.GetSize());
	BYTE* pMem = (BYTE*)::GlobalLock(hMem);

	memcpy(pMem, zf.GetData(), zf.GetSize());

	IStream* pStm = NULL;
	::CreateStreamOnHGlobal(hMem, TRUE, &pStm);

	pImage = Gdiplus::Image::FromStream(pStm);

	::GlobalUnlock(hMem);
	pStm->Release();
	return pImage;	
}

BOOL DuiResProviderZip::GetResBuffer( LPCSTR strType,UINT uID,CMyBuffer<char> & buf )
{
	CString strPath=GetFilePath(uID,strType);
	if(strPath.IsEmpty()) return FALSE;
	CZipFile zf;
	if(!m_zipFile.GetFile(strPath,zf)) return NULL;
	buf.Allocate(zf.GetSize());
	memcpy(buf,zf.GetData(),zf.GetSize());
	buf[zf.GetSize()]=0;
	return TRUE;
}

BOOL DuiResProviderZip::OpenZip( LPCTSTR pszZipFile )
{
	if(!m_zipFile.Open(pszZipFile)) return FALSE;
	CZipFile zf;
	BOOL bIdx=m_zipFile.GetFile(_T("index.xml"),zf);
	if(!bIdx) return FALSE;
	return AddIdMap(zf);
}

BOOL DuiResProviderZip::AddIdMap( const CZipFile & zipFile )
{
	TiXmlDocument xmlDoc;
	CStringA strFileName;
	CStringA xmlBuf((char*)zipFile.GetData(),zipFile.GetSize());
	xmlDoc.Parse(xmlBuf);
	if(xmlDoc.Error()) return FALSE;
	TiXmlElement *pXmlElem = xmlDoc.RootElement();
	while(pXmlElem)
	{
		CStringA strValue = pXmlElem->Value();
		if(strValue=="resid")
		{
			DuiResID id(pXmlElem->Attribute("type"));
			pXmlElem->Attribute("id",&(int)id.nID);
			CStringA strFile = pXmlElem->Attribute("file");
			CStringW strFileW=CA2W(strFile,CP_UTF8);
			m_mapFiles[id]=CW2T(strFileW,CP_ACP);
		}
		pXmlElem=pXmlElem->NextSiblingElement();
	}
	return TRUE;
}	

CString DuiResProviderZip::GetFilePath( UINT uID,LPCSTR pszType )
{
	DuiResID resID(pszType,uID);
	std::map<DuiResID,CString>::iterator it = m_mapFiles.find(resID);
	if(it==m_mapFiles.end()) return _T("");
	return it->second;
}
}//namespace DuiEngine