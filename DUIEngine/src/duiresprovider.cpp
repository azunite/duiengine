//////////////////////////////////////////////////////////////////////////
//   File Name: duiresprovider.cpp
// Description: Resource Provider
//////////////////////////////////////////////////////////////////////////
#include "duistd.h"
#include "duiresprovider.h"

namespace DuiEngine{


	BOOL CResPE::GetResBuffer( CMyBuffer<char> & buf )
	{
		HRSRC hRsrc = ::FindResourceA(hInst, MAKEINTRESOURCEA(uID), strType);

		if (NULL == hRsrc)
			return FALSE;

		DWORD dwSize = ::SizeofResource(hInst, hRsrc); 
		if (0 == dwSize)
			return FALSE;

		HGLOBAL hGlobal = ::LoadResource(hInst, hRsrc); 
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

	HBITMAP CResPE::LoadBitmap( )
	{
		return ::LoadBitmap(hInst,MAKEINTRESOURCE(uID));
	}

	HICON CResPE::LoadIcon()
	{
		return ::LoadIcon(hInst,MAKEINTRESOURCE(uID));
	}

	Gdiplus::Image * CResPE::LoadImage()
	{
		Gdiplus::Image *pImage=NULL;
		CMyBuffer<char> imgBuf;
		if(GetResBuffer(imgBuf))
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
		return pImage;
	}

	CResPE::CResPE( HINSTANCE _hInst,UINT _uID,const CStringA & _strType )
		:hInst(_hInst),uID(_uID),strType(_strType)
	{

	}
	CResBase * DuiResProviderPE::GetRes( LPCSTR strType,UINT uID )
	{
		if(!m_hResInst) return NULL;
		if(!FindResourceA(m_hResInst,MAKEINTRESOURCEA(uID),strType)) return NULL;
		return new CResPE(m_hResInst,uID,strType);
	}

	DuiResProviderFiles::DuiResProviderFiles( const CStringA & strPath ) :m_strPath(strPath)
	{
		WIN32_FIND_DATAA wfd;
		CStringA strFilter;
		strFilter.Format("%s\\*.%s",(LPCSTR)m_strPath,EXT_IDMAP);
		HANDLE hFnd=FindFirstFileA(strFilter,&wfd);
		if(hFnd)
		{
			do{
				CStringA strIdmap=strPath+"\\"+wfd.cFileName;
				AddIdMap(strIdmap);
			}while(FindNextFileA(hFnd,&wfd));
		}
	}

	CResBase * DuiResProviderFiles::GetRes( LPCSTR strType,UINT uID )
	{
		DuiResID resID(strType,uID);
		std::map<DuiResID,CStringA>::iterator it=m_mapFiles.find(resID);
		if(it==m_mapFiles.end()) return NULL;
		return new CResFile(it->second);
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
				DuiResID id;
				id.strType=pXmlElem->Attribute("type");
				pXmlElem->Attribute("id",&(int)id.nID);
				CStringA strFile = pXmlElem->Attribute("file");
				if(!m_strPath.IsEmpty()) strFile.Format("%s\\%s",(LPCSTR)m_strPath,(LPCSTR)strFile);
				m_mapFiles[id]=strFile;
			}
			pXmlElem=pXmlElem->NextSiblingElement();
		}

		return TRUE;
	}

	CResFile::CResFile( const CStringA & strFile )
	{
		strFilePath=strFile;
	}

	HBITMAP CResFile::LoadBitmap()
	{
		return (HBITMAP)::LoadImageA(NULL, (LPCSTR)strFilePath, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	}

	HICON CResFile::LoadIcon()
	{
		return (HICON)::LoadImageA(NULL, (LPCSTR)strFilePath, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	}

	Gdiplus::Image * CResFile::LoadImage()
	{
		CStringW strPathW=CA2W(strFilePath);
		Gdiplus::Image *pImg=new Gdiplus::Image(strPathW);
		if(pImg->GetLastStatus() != 0)
		{
			delete pImg;
			pImg=NULL;
		}
		return pImg;
	}

	BOOL CResFile::GetResBuffer( CMyBuffer<char> & buf )
	{
		FILE *f=fopen(strFilePath,"rb");
		if(!f) return FALSE;
		int len=_filelength(_fileno(f));
		buf.AllocateBytes(len);

		BOOL bRet=(len==fread(buf,1,len,f));
		if(!bRet) buf.Free();
		fclose(f);
		return bRet;
	}

}//namespace DuiEngine