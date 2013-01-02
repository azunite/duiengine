#ifndef __DUISTR_H__
#define __DUISTR_H__

#pragma once

#include <tchar.h>

template<class _Elem,int elesize=sizeof(_Elem)>
class DUI_EXP CStdString : public STL_NS::basic_string<_Elem>
{
public:
	typedef STL_NS::basic_string<_Elem> _basestr;
	CStdString(){}
	CStdString(const _Elem ch):_basestr(1,ch)
	{
	}
	CStdString(const CStdString& src):_basestr(src)
	{

	}
	CStdString(const _basestr & src):_basestr(src)
	{

	}
	CStdString(const _Elem * lpsz, size_t nLen = -1)
	{
		if(lpsz)
		{
			if(nLen==-1) assign(lpsz);
			else assign(lpsz,nLen);
		}
	}

	operator const _Elem *() const
	{
		return _basestr::c_str();
	}

	_Elem operator[] (int nIndex) const
	{
		return at(nIndex);
	}

	void MakeLower()
	{
		size_t i;
		if(sizeof(_Elem)==1)
			for(i=0;i<size();i++)
			{
				char & ch=(char &)at(i);
				if(isupper(ch)) ch=tolower(ch);
			}
		else
			for(i=0;i<size();i++)
			{
				wchar_t & ch=(wchar_t &)at(i);
				if(iswupper(ch)) ch=towlower(ch);
			}
	}

	void MakeUpper()
	{
		size_t i;
		if(sizeof(_Elem)==1)
			for(i=0;i<size();i++)
			{
				char & ch=(char &)at(i);
				if(islower(ch)) ch=toupper(ch);
			}
		else
			for(i=0;i<size();i++)
			{
				wchar_t & ch=(wchar_t &)at(i);
				if(iswlower(ch)) ch=towupper(ch);
			}
	}

	int GetLength() const
	{
		return size();
	}

	bool IsEmpty() const
	{
		return empty();
	}

	void Empty() 
	{
		clear();
	}

	int ReverseFind(const _Elem ch) const
	{
		return rfind(ch);
	}

	int Find(const _Elem * psz,const int iStart=0) const
	{
		return find(psz,iStart);
	}

	int Find(_Elem ch,const int iStart=0) const
	{
		return find(ch,iStart);
	}

	CStdString Right(int nLength) const
	{
		int nOffset=size()-nLength;
		return substr(nOffset,nLength);
	}
	CStdString Left(int nLength) const
	{
		return substr(0,nLength);
	}

	CStdString Mid(int iPos, int nLength = -1) const
	{
		if(nLength==-1) nLength=size()-iPos;
		return substr(iPos,nLength);
	}

	int __cdecl Format(const _Elem * pstrFormat, ...)
	{
		CStdString sFormat = pstrFormat;
		int iRet=0;
		_Elem szBuffer[1025] = { 0 };
		va_list argList;
		va_start(argList, pstrFormat);
		if(sizeof(_Elem)==1)
		{
			const char * pszFormat=(const char *)sFormat.c_str();
			iRet = ::wvsprintfA((char*)szBuffer, pszFormat, argList);
		}
		else
			iRet = ::wvsprintfW((wchar_t*)szBuffer, (const wchar_t *)sFormat.c_str(), argList);
		va_end(argList);
		assign(szBuffer);
		return iRet;
	}

};

class DUI_EXP CDuiStrCpCvt{
public:
	static CStdString<char> CvtW2A(const CStdString<wchar_t> & str,unsigned int cp=CP_ACP)
	{
		char szBuf[1024];
		int nRet=WideCharToMultiByte(cp,0,str,str.GetLength(),szBuf,1024,NULL,NULL);
		if(nRet>0) return CStdString<char>(szBuf,nRet);
		if(GetLastError()==ERROR_INSUFFICIENT_BUFFER)
		{
			int nRet=WideCharToMultiByte(cp,0,str,str.GetLength(),NULL,0,NULL,NULL);
			if(nRet>0)
			{
				char *pBuf=new char[nRet];
				WideCharToMultiByte(cp,0,str,str.GetLength(),pBuf,nRet,NULL,NULL);
				CStdString<char> strRet(pBuf,nRet);
				delete []pBuf;
				return strRet;
			}
		}
		return "";
	}

	static CStdString<wchar_t> CvtA2W(const CStdString<char> & str,unsigned int cp=CP_ACP)
	{
		wchar_t szBuf[1024];
		int nRet=MultiByteToWideChar(cp,0,str,str.GetLength(),szBuf,1024);
		if(nRet>0)
		{
			return CStdString<wchar_t>(szBuf,nRet);
		}
		if(GetLastError()==ERROR_INSUFFICIENT_BUFFER)
		{
			int nRet=MultiByteToWideChar(cp,0,str,str.GetLength(),NULL,0);
			if(nRet>0)
			{
				wchar_t *pBuf=new wchar_t[nRet];
				MultiByteToWideChar(cp,0,str,str.GetLength(),pBuf,nRet);
				CStdString<wchar_t> strRet(pBuf,nRet);
				delete []pBuf;
				return strRet;
			}
		}
		return L"";
	}

	static CStdString<char> CvtA2A(const CStdString<char> & str,unsigned int cp=CP_ACP)
	{
		if(cp==CP_ACP)
			return str;
		CStdString<wchar_t> strw=CvtA2W(str,cp);
		return CvtW2A(strw);
	}

	static CStdString<wchar_t> CvtW2W(const CStdString<wchar_t> &str,unsigned int cp=CP_ACP)
	{
		return str;
	}

};


#ifndef CP_ACP
#define CP_ACP 0
#endif//CP_ACP

#ifndef NO_STDSTR

typedef  CStdString<char> CStringA;
typedef  CStdString<wchar_t> CStringW;

#ifdef UNICODE
typedef  CStringW CString;
#else
typedef  CStringA CString;
#endif // UNICODE

typedef CString CStringT;

#define CA2W CDuiStrCpCvt::CvtA2W
#define CW2A CDuiStrCpCvt::CvtW2A
#define CA2A CDuiStrCpCvt::CvtA2A
#define CW2W CDuiStrCpCvt::CvtW2W

#ifdef UNICODE
#define CA2T CA2W
#define CT2A CW2A
#define CW2T CW2W
#define CT2W CW2W
#else
#define CA2T CA2A
#define CT2A CA2A
#define CW2T CW2A
#define CT2W CA2W
#endif // UNICODE

#endif //NO_STDSTR

#endif // __DUISTR_H__

/////////////////////////////////////////////////////////////////////////////
