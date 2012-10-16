#ifndef __DUISTR_H__
#define __DUISTR_H__

#pragma once

#include <string>
#include <tchar.h>

namespace DuiEngine
{

template<class _Elem,int elesize=sizeof(_Elem)>
class CDuiString : public std::basic_string<_Elem>
{
public:
	typedef std::basic_string<_Elem> _basestr;
	CDuiString(){}
	CDuiString(const _Elem ch):_basestr(1,ch)
	{
	}
	CDuiString(const CDuiString& src):_basestr(src)
	{

	}
	CDuiString(const _basestr & src):_basestr(src)
	{

	}
	CDuiString(const _Elem * lpsz, size_t nLen = -1)
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

	CDuiString Right(int nLength) const
	{
		int nOffset=size()-nLength;
		return substr(nOffset,nLength);
	}
	CDuiString Left(int nLength) const
	{
		return substr(0,nLength);
	}

	CDuiString Mid(int iPos, int nLength = -1) const
	{
		if(nLength==-1) nLength=size()-iPos;
		return substr(iPos,nLength);
	}

	int __cdecl Format(const _Elem * pstrFormat, ...)
	{
		CDuiString sFormat = pstrFormat;
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

}//namespace DuiEngine

typedef  DuiEngine::CDuiString<char> CStringA;
typedef  DuiEngine::CDuiString<wchar_t> CStringW;

#ifdef UNICODE
typedef  CStringW CString;
#else
typedef  CStringA CString;
#endif // UNICODE

typedef CString CStringT;

#endif // __DUISTR_H__

/////////////////////////////////////////////////////////////////////////////
