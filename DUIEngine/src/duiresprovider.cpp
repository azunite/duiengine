//////////////////////////////////////////////////////////////////////////
//   File Name: duiresprovider.cpp
// Description: Resource Provider
//////////////////////////////////////////////////////////////////////////
#include "duistd.h"
#include "duiresprovider.h"

namespace DuiEngine{

	HBITMAP DuiResProviderPE::LoadBitmap( LPCSTR strType,UINT uID )
	{
		return ::LoadBitmap(m_hResInst,MAKEINTRESOURCE(uID));
	}

	HICON DuiResProviderPE::LoadIcon( LPCSTR strType,UINT uID )
	{
		return ::LoadIcon(m_hResInst,MAKEINTRESOURCE(uID));
	}

	Gdiplus::Image * DuiResProviderPE::LoadImage( LPCSTR strType,UINT uID )
	{
		Gdiplus::Image *pImage=NULL;
		CMyBuffer<char> imgBuf;
		if(GetResBuffer(strType,uID,imgBuf))
		{
			int len = imgBuf.size();
			HGLOBAL hMem = ::GlobalAlloc(GMEM_FIXED, len);
			BYTE* pMem = (BYTE*)::GlobalLock(hMem);

			memcpy(pMem, imgBuf, len);

			IStream* pStm = NULL;
			::CreateStreamOnHGlobal(hMem, TRUE, &pStm);

			pImage = Gdiplus::Image::FromStream(pStm);

			::GlobalUnlock(hMem);
			pStm->Release();
		}
		return pImage;	}

	BOOL DuiResProviderPE::GetResBuffer( LPCSTR strType,UINT uID,CMyBuffer<char> & buf )
	{
		HRSRC hRsrc = ::FindResourceA(m_hResInst, MAKEINTRESOURCEA(uID), strType);

		if (NULL == hRsrc)
			return FALSE;

		DWORD dwSize = ::SizeofResource(m_hResInst, hRsrc); 
		if (0 == dwSize)
			return FALSE;

		HGLOBAL hGlobal = ::LoadResource(m_hResInst, hRsrc); 
		if (NULL == hGlobal)
			return FALSE;

		LPVOID pBuffer = ::LockResource(hGlobal); 
		if (NULL == pBuffer)
			return FALSE;

		buf.AllocateBytes(dwSize);
		memcpy(buf,pBuffer,dwSize);
		// 			buf.Attach((char*)pBuffer,dwSize);

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

	HICON DuiResProviderFiles::LoadIcon( LPCSTR strType,UINT uID )
	{
		CStringA strPath=GetRes(strType,uID);
		if(strPath.IsEmpty()) return NULL;
		return (HICON)::LoadImageA(NULL, strPath, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
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

	BOOL DuiResProviderFiles::GetResBuffer( LPCSTR strType,UINT uID,CMyBuffer<char> & buf )
	{
		CStringA strPath=GetRes(strType,uID);
		if(strPath.IsEmpty()) return FALSE;
		FILE *f=fopen(strPath,"rb");
		if(!f) return FALSE;
		int len=_filelength(_fileno(f));
		buf.AllocateBytes(len);

		BOOL bRet=(len==fread(buf,1,len,f));
		if(!bRet) buf.Free();
		fclose(f);
		return bRet;
	}


}//namespace DuiEngine