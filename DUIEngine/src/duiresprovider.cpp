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

	CResBase * DuiResProviderPE::GetRes( LPCSTR strType,UINT uID )
	{
		if(!m_hResInst) return NULL;
		if(!FindResourceA(m_hResInst,MAKEINTRESOURCEA(uID),strType)) return NULL;
		CResPE *pRet=new CResPE;
		pRet->hInst=m_hResInst;
		pRet->strType=strType;
		pRet->uID=uID;
		return pRet;
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
		CResFile *pRet=new CResFile;
		pRet->strFilePath=it->second;
		return pRet;
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
}//namespace DuiEngine