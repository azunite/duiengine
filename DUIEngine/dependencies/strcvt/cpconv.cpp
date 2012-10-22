#include "stdafx.h"
#include "cpconv.h"

CStringA CvtW2A(CStringW str,unsigned int cp)
{
	char szBuf[1024];
	int nRet=WideCharToMultiByte(cp,0,str,str.GetLength(),szBuf,1024,NULL,NULL);
	if(nRet>0) return CStringA(szBuf,nRet);
	if(GetLastError()==ERROR_INSUFFICIENT_BUFFER)
	{
		int nRet=WideCharToMultiByte(cp,0,str,str.GetLength(),NULL,0,NULL,NULL);
		if(nRet>0)
		{
			char *pBuf=new char[nRet];
			WideCharToMultiByte(cp,0,str,str.GetLength(),pBuf,nRet,NULL,NULL);
			CStringA strRet(pBuf,nRet);
			delete []pBuf;
			return strRet;
		}
	}
	return "";
}

CStringW CvtA2W(CStringA str,unsigned int cp)
{
	wchar_t szBuf[1024];
	int nRet=MultiByteToWideChar(cp,0,str,str.GetLength(),szBuf,1024);
	if(nRet>0)
	{
		return CStringW(szBuf,nRet);
	}
	if(GetLastError()==ERROR_INSUFFICIENT_BUFFER)
	{
		int nRet=MultiByteToWideChar(cp,0,str,str.GetLength(),NULL,0);
		if(nRet>0)
		{
			wchar_t *pBuf=new wchar_t[nRet];
			MultiByteToWideChar(cp,0,str,str.GetLength(),pBuf,nRet);
			CStringW strRet(pBuf,nRet);
			delete []pBuf;
			return strRet;
		}
	}
	return L"";
}

CStringA CvtA2A(CStringA str,unsigned int cp)
{
	return str;
}

CStringW CvtW2W(CStringW str,unsigned int cp)
{
	return str;
}

