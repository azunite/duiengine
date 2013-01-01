#include "stdafx.h"
#include "DuiResProviderZip.h"

namespace DuiEngine{

	DuiResProviderZip::DuiResProviderZip(CDuiImgDecoder *pImgDecoder):DuiResProviderBase(pImgDecoder)
	{
	}

	DuiResProviderZip::~DuiResProviderZip(void)
	{
	}

	HBITMAP DuiResProviderZip::LoadBitmap( LPCSTR strType,UINT uID )
	{
		CString strPath=GetFilePath(uID,strType);
		if(strPath.IsEmpty()) return NULL;
		CZipFile zf;
		if(!m_zipFile.GetFile(strPath,zf)) return NULL;

		HDC hDC = GetDC(NULL);
		//读取位图头
		BITMAPFILEHEADER *pBmpFileHeader=(BITMAPFILEHEADER *)zf.GetData(); 
		//检测位图头
		if (pBmpFileHeader->bfType != ((WORD) ('M'<<8)|'B')) 
		{
			return NULL; 
		} 
		//判断位图长度
		if (pBmpFileHeader->bfSize > (UINT)zf.GetSize()) 
		{ 
			return NULL; 
		} 
		LPBITMAPINFO lpBitmap=(LPBITMAPINFO)(pBmpFileHeader+1); 
		LPVOID lpBits=(LPBYTE)zf.GetData()+pBmpFileHeader->bfOffBits;
		HBITMAP hBitmap= CreateDIBitmap(hDC,&lpBitmap->bmiHeader,CBM_INIT,lpBits,lpBitmap,DIB_RGB_COLORS);
		ReleaseDC(NULL,hDC);
		
		return hBitmap;
	}

	HICON DuiResProviderZip::LoadIcon( LPCSTR strType,UINT uID ,int cx/*=0*/,int cy/*=0*/)
	{
		CString strPath=GetFilePath(uID,strType);
		if(strPath.IsEmpty()) return NULL;
		CZipFile zf;
		if(!m_zipFile.GetFile(strPath,zf)) return NULL;
		TCHAR szTmp[MAX_PATH+1];
		GetTempPath(MAX_PATH,szTmp);
		GetTempFileName(szTmp,_T("ICO"),0,szTmp);
		FILE *f=_tfopen(szTmp,_T("wb"));
		if(!f) return NULL;
		fwrite(zf.GetData(),1,zf.GetSize(),f);
		fclose(f);
		HICON hIcon=(HICON)::LoadImage(NULL,szTmp,IMAGE_ICON,cx,cy,LR_DEFAULTSIZE|LR_DEFAULTCOLOR|LR_LOADFROMFILE);
		DeleteFile(szTmp);
		return hIcon;
	}

	CDuiImgBase * DuiResProviderZip::LoadImage( LPCSTR strType,UINT uID)
	{
		CString strPath=GetFilePath(uID,strType);
		if(strPath.IsEmpty()) return NULL;
		CZipFile zf;
		if(!m_zipFile.GetFile(strPath,zf)) return NULL;
		CDuiImgBase *pImg=GetImageDecoder()->CreateDuiImage(strType);
		if(pImg) pImg->LoadFromMemory(zf.GetData(),zf.GetSize());
		return pImg;
	}

	BOOL DuiResProviderZip::Init( LPCTSTR pszZipFile )
	{
		if(!m_zipFile.Open(pszZipFile)) return FALSE;
		return LoadSkin();
	}

	BOOL DuiResProviderZip::Init( HINSTANCE hInst,UINT uID,LPCTSTR pszType/*=_T("ZIP")*/ )
	{
		if(!m_zipFile.Open(hInst,MAKEINTRESOURCE(uID),pszType)) return FALSE;
		return LoadSkin();
	}

	CString DuiResProviderZip::GetFilePath( UINT uID,LPCSTR pszType )
	{
		DuiResID resID(pszType,uID);
		std::map<DuiResID,CString>::iterator it = m_mapFiles.find(resID);
		if(it==m_mapFiles.end()) return _T("");
		return it->second;
	}

	size_t DuiResProviderZip::GetRawBufferSize( LPCSTR strType,UINT uID )
	{
		CString strPath=GetFilePath(uID,strType);
		if(strPath.IsEmpty()) return FALSE;
		ZIP_FIND_DATA zfd;
		HANDLE hf=m_zipFile.FindFirstFile(strPath,&zfd);
		if(INVALID_HANDLE_VALUE==hf) return 0;
		m_zipFile.FindClose(hf);
		return zfd.nFileSizeUncompressed;
	}

	BOOL DuiResProviderZip::GetRawBuffer( LPCSTR strType,UINT uID,LPVOID pBuf,size_t size )
	{
		CString strPath=GetFilePath(uID,strType);
		if(strPath.IsEmpty()) return FALSE;
		CZipFile zf;
		if(!m_zipFile.GetFile(strPath,zf)) return NULL;
		if(size<zf.GetSize())
		{
			SetLastError(ERROR_INSUFFICIENT_BUFFER);
			return FALSE;
		}
		memcpy(pBuf,zf.GetData(),zf.GetSize());
		return TRUE;
	}

	BOOL DuiResProviderZip::HasResource( LPCSTR strType,UINT uID )
	{
		DuiResID resID(strType,uID);
		std::map<DuiResID,CString>::iterator it = m_mapFiles.find(resID);
		return it!=m_mapFiles.end();
	}

	BOOL DuiResProviderZip::LoadSkin()
	{
		CZipFile zf;
		BOOL bIdx=m_zipFile.GetFile(_T("index.xml"),zf);
		if(!bIdx) return FALSE;

		TiXmlDocument xmlDoc;
		CStringA strFileName;
		CStringA xmlBuf((char*)zf.GetData(),zf.GetSize());
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

}//namespace DuiEngine