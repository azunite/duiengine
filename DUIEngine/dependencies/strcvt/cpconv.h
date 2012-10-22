#ifndef __STDCONV_H__
#define __STDCONV_H__

#pragma once

#include "stdstr.h"

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

#define CA2W CvtA2W
#define CW2A CvtW2A
#define CA2A CvtA2A
#define CW2W CvtW2W

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

#endif//NO_STDSTR

CStringA CvtW2A(CStringW str,unsigned int cp=CP_ACP);
CStringW CvtW2W(CStringW str,unsigned int cp=CP_ACP);
CStringA CvtA2A(CStringA str,unsigned int cp=CP_ACP);
CStringW CvtA2W(CStringA str,unsigned int cp=CP_ACP);

#endif // __STDCONV_H__
