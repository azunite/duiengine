//////////////////////////////////////////////////////////////////////////
//   File Name: bkresutil.h
// Description: Beike Resource Helper
//     Creator: Zhang Xiaoxuan
//     Version: 2009.5.13 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////
#include "duistd.h"
#include "duiresutil.h"

namespace DuiEngine{

template<> DuiResManager * Singleton<DuiResManager>::ms_Singleton=NULL;

BOOL DuiResManager::SetResourcePath(LPCSTR lpszPath,LPCSTR lpszXmlIDFile)
{
	TiXmlDocument xmlDoc;
	CStringA strFileName;
	CStringA strXml;
	strFileName.Format("%s\\%s", lpszPath, lpszXmlIDFile);

	HANDLE hFile = ::CreateFileA(
		strFileName, GENERIC_READ, FILE_SHARE_READ, 
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE != hFile)
	{
		DWORD dwSize = ::GetFileSize(hFile, NULL);
		if (0 != dwSize)
		{
			DWORD dwRead = 0;
			BOOL bRet = ::ReadFile(hFile, strXml.GetBuffer(dwSize + 10), dwSize, &dwRead, NULL);
			if (!bRet || dwRead != dwSize)
			{
				strXml.ReleaseBuffer(dwSize);
				return FALSE;
			}

			strXml.ReleaseBuffer(dwSize);
		}

		::CloseHandle(hFile);
	}
	xmlDoc.Parse(strXml);
	if(xmlDoc.Error()) return FALSE;
	TiXmlElement *pXmlElem = xmlDoc.RootElement();
	while(pXmlElem)
	{
		CStringA strValue = pXmlElem->Value();
		if(strValue=="resid")
		{
			DuiResID id;
			id.strType=pXmlElem->Attribute("type");
			pXmlElem->Attribute("id",&id.nID);
			CStringA strFile = pXmlElem->Attribute("file");
			AddKeyObject(id,strFile);
		}
		pXmlElem=pXmlElem->NextSiblingElement();
	}

	m_strResourcePath = lpszPath;
	return TRUE;
}

void DuiResManager::SetResourceDLL(LPCTSTR lpszPath)
{
	SetResourceDLL(LoadLibrary(lpszPath));
}

void DuiResManager::SetResourceDLL(HINSTANCE hInst)
{
	if (m_hInstanceRes)  ::FreeLibrary(m_hInstanceRes);
	m_hInstanceRes=hInst;
}

BOOL DuiResManager::LoadResource(UINT uResID, CStringA &strBuffRet, LPCTSTR lpszResType/* = DUIRES_TYPE*/)
{
	if (!m_strResourcePath.IsEmpty())
	{
		CStringA strFilePath;
		DuiResID resid(lpszResType,uResID);
		if(!HasKey(resid)) return FALSE;
		CStringA strName=GetKeyObject(resid);

		strFilePath.Format("%s\\%s", m_strResourcePath, strName);

		HANDLE hFile = ::CreateFileA(
			strFilePath, GENERIC_READ, FILE_SHARE_READ, 
			NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (INVALID_HANDLE_VALUE != hFile)
		{
			DWORD dwSize = ::GetFileSize(hFile, NULL);
			DWORD dwRead = 0;
			if (0 != dwSize)
			{
				::ReadFile(hFile, strBuffRet.GetBuffer(dwSize + 10), dwSize, &dwRead, NULL);
				strBuffRet.ReleaseBuffer(dwRead);
			}

			::CloseHandle(hFile);
			return dwRead == dwSize;
		}else
		{
			return FALSE;
		}
	}else
	{
		BOOL bRet = _LoadEmbedResource(uResID, strBuffRet, lpszResType);
		DUIRES_ASSERTW(bRet, L"Failed loading %s %u", lpszResType, uResID);
		return bRet;
	}
}

BOOL DuiResManager::LoadResource(UINT uResID, HBITMAP &hBitmap)
{
	BOOL bRet = FALSE;

	if (!m_strResourcePath.IsEmpty())
	{
		CStringA strFilePath;
		DuiResID resid("BMP",uResID);
		if(!HasKey(resid)) return FALSE;

		CStringA strName=GetKeyObject(resid);

		strFilePath.Format("%s\\%s", m_strResourcePath, strName);

		hBitmap = (HBITMAP)::LoadImageA(NULL, strFilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		DUIRES_ASSERTW(NULL != hBitmap, L"Failed loading bitmap %u", uResID);

		return  (NULL != hBitmap);
	}else if (m_hInstanceRes)
	{
		hBitmap = ::LoadBitmap(m_hInstanceRes, MAKEINTRESOURCE(uResID));
		DUIRES_ASSERTW(NULL != hBitmap, L"Failed loading bitmap %u", uResID);
		return (NULL != hBitmap);
	}else
	{
		hBitmap = ::LoadBitmap((HINSTANCE)&__ImageBase, MAKEINTRESOURCE(uResID));
		DUIRES_ASSERTW(NULL != hBitmap, L"Failed loading bitmap %u", uResID);
		return NULL != hBitmap;
	}
}
BOOL DuiResManager::LoadResource(UINT uResID, HICON &hIcon,int nSize)
{
	BOOL bRet = FALSE;

	if (!m_strResourcePath.IsEmpty())
	{
		CStringA strFilePath;
		DuiResID resid("ICO",uResID);
		if(!HasKey(resid)) return FALSE;
		CStringA strName=GetKeyObject(resid);
		strFilePath.Format("%s\\%s", m_strResourcePath, strName);

		hIcon = (HICON)::LoadImageA(NULL, strFilePath, IMAGE_ICON, nSize, nSize, LR_LOADFROMFILE);
		DUIRES_ASSERTW(NULL != hIcon, L"Failed loading Icon %u", uResID);

		return (NULL != hIcon);
	}else if (m_hInstanceRes)
	{
		hIcon = ::LoadIcon(m_hInstanceRes, MAKEINTRESOURCE(uResID));
		DUIRES_ASSERTW(NULL != hIcon, L"Failed loading Icon %u", uResID);
		return (NULL != hIcon);
	}else
	{
		hIcon = ::LoadIcon((HINSTANCE)&__ImageBase, MAKEINTRESOURCE(uResID));

		DUIRES_ASSERTW(NULL != hIcon, L"Failed loading Icon %u", uResID);

		return NULL != hIcon;
	}
}


BOOL DuiResManager::_LoadEmbedResource(UINT uResID, CStringA &strRet, LPCTSTR lpszResType/* = DUIRES_TYPE*/)
{
	HINSTANCE hInst=m_hInstanceRes;
	if(!hInst) hInst=(HINSTANCE)&__ImageBase;

	HRSRC hRsrc = ::FindResource(hInst, MAKEINTRESOURCE(uResID), lpszResType);

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

	memcpy(strRet.GetBuffer(dwSize + 1), pBuffer, dwSize);
	strRet.ReleaseBuffer(dwSize);

	::FreeResource(hGlobal);

	return TRUE;
}

}//namespace DuiEngine