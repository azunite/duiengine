//////////////////////////////////////////////////////////////////////////
//   File Name: duiresprovider.cpp
// Description: Resource Provider
//////////////////////////////////////////////////////////////////////////
#include "duistd.h"
#include "duiresprovider.h"
#include "mybuffer.h"
#include <io.h>

namespace DuiEngine{

	DuiResProviderPE::DuiResProviderPE( HINSTANCE hInst ) :m_hResInst(hInst)
	{

	}
	HBITMAP DuiResProviderPE::LoadBitmap( LPCSTR strType,UINT uID )
	{
		return ::LoadBitmap(m_hResInst,MAKEINTRESOURCE(uID));
	}

	HICON DuiResProviderPE::LoadIcon( LPCSTR strType,UINT uID ,int cx/*=0*/,int cy/*=0*/)
	{
		return (HICON)::LoadImage(m_hResInst,MAKEINTRESOURCE(uID),IMAGE_ICON,cx,cy,LR_DEFAULTCOLOR|LR_DEFAULTSIZE);
	}

	Gdiplus::Image * DuiResProviderPE::LoadImage( LPCSTR strType,UINT uID )
	{
		Gdiplus::Image *pImage=NULL;
		DWORD dwSize=GetRawBufferSize(strType,uID);
		if(dwSize==0) return NULL;

		HGLOBAL hMem = ::GlobalAlloc(GMEM_FIXED, dwSize);
		BYTE* pMem = (BYTE*)::GlobalLock(hMem);
		GetRawBuffer(strType,uID,pMem,dwSize);

		IStream* pStm = NULL;
		::CreateStreamOnHGlobal(hMem, TRUE, &pStm);

		pImage = Gdiplus::Image::FromStream(pStm);

		pStm->Release();
		::GlobalUnlock(hMem);
		GlobalFree(hMem);

		return pImage;	
	}

	size_t DuiResProviderPE::GetRawBufferSize( LPCSTR strType,UINT uID )
	{
		HRSRC hRsrc = ::FindResourceA(m_hResInst, MAKEINTRESOURCEA(uID), strType);

		if (NULL == hRsrc)
			return 0;

		return ::SizeofResource(m_hResInst, hRsrc); 
	}

	BOOL DuiResProviderPE::GetRawBuffer( LPCSTR strType,UINT uID,LPVOID pBuf,size_t size )
	{
		HRSRC hRsrc = ::FindResourceA(m_hResInst, MAKEINTRESOURCEA(uID), strType);

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


	DuiResProviderFiles::DuiResProviderFiles( const CStringA & strPath ) :m_strPath(strPath)
	{
		AddIdMap(CStringA(strPath)+"\\"+INDEX_XML);
	}

	CStringA DuiResProviderFiles::GetRes( LPCSTR strType,UINT uID )
	{
		DuiResID resID(strType,uID);
		std::map<DuiResID,CStringA>::iterator it=m_mapFiles.find(resID);
		if(it==m_mapFiles.end()) return "";
		return it->second;
	}

	BOOL DuiResProviderFiles::AddIdMap( const CStringA & strIdmapFile )
	{
		CMyBuffer<char>  xmlBuf;

		FILE *f=fopen(strIdmapFile,"rb");
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
		CStringA strFileName;

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
				strFile=CW2A(strFileW);
				if(!m_strPath.IsEmpty()) strFile.Format("%s\\%s",(LPCSTR)m_strPath,(LPCSTR)strFile);
				m_mapFiles[id]=strFile;
			}
			pXmlElem=pXmlElem->NextSiblingElement();
		}

		return TRUE;
	}

	HBITMAP DuiResProviderFiles::LoadBitmap( LPCSTR strType,UINT uID )
	{
		CStringA strPath=GetRes(strType,uID);
		if(strPath.IsEmpty()) return NULL;
		return (HBITMAP)::LoadImageA(NULL, strPath, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	}

	HICON DuiResProviderFiles::LoadIcon( LPCSTR strType,UINT uID ,int cx/*=0*/,int cy/*=0*/)
	{
		CStringA strPath=GetRes(strType,uID);
		if(strPath.IsEmpty()) return NULL;
		return (HICON)::LoadImageA(NULL, strPath, IMAGE_ICON, cx, cy, LR_LOADFROMFILE);
	}

	Gdiplus::Image * DuiResProviderFiles::LoadImage( LPCSTR strType,UINT uID )
	{
		CStringA strPath=GetRes(strType,uID);
		if(strPath.IsEmpty()) return NULL;
		CStringW strPathW=CA2W(strPath);
		Gdiplus::Image *pImg=new Gdiplus::Image(strPathW);
		if(pImg->GetLastStatus() != 0)
		{
			delete pImg;
			pImg=NULL;
		}
		return pImg;
	}

	size_t DuiResProviderFiles::GetRawBufferSize( LPCSTR strType,UINT uID )
	{
		CStringA strPath=GetRes(strType,uID);
		if(strPath.IsEmpty()) return 0;
		WIN32_FIND_DATAA wfd;
		HANDLE hf=FindFirstFileA(strPath,&wfd);
		if(!hf) return 0;
		FindClose(hf);
		return wfd.nFileSizeLow;
	}

	BOOL DuiResProviderFiles::GetRawBuffer( LPCSTR strType,UINT uID,LPVOID pBuf,size_t size )
	{
		CStringA strPath=GetRes(strType,uID);
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
}//namespace DuiEngine