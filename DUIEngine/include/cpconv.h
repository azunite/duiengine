#ifndef __STDCONV_H__
#define __STDCONV_H__

#pragma once

#ifndef CP_ACP
#define CP_ACP 0
#endif//CP_ACP

CStringA CvtW2A(CStringW str,unsigned int cp=CP_ACP);
CStringW CvtW2W(CStringW str,unsigned int cp=CP_ACP);
CStringA CvtA2A(CStringA str,unsigned int cp=CP_ACP);
CStringW CvtA2W(CStringA str,unsigned int cp=CP_ACP);

#ifndef NO_STRCVT

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

#endif//NO_STRCVT

#endif // __STDCONV_H__
