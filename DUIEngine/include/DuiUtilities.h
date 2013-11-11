#pragma once

#include <assert.h>

namespace DuiEngine
{
	void DUI_EXP DuiHiMetricToPixel(const SIZEL * lpSizeInHiMetric, LPSIZEL lpSizeInPix);
	void DUI_EXP DuiPixelToHiMetric(const SIZEL * lpSizeInPix, LPSIZEL lpSizeInHiMetric);
	void DUI_EXP DuiTrace(LPCTSTR pstrFormat, ...);
}//end of namespace DuiEngine

#define DUITRACE DuiTrace
#define DUIASSERT(x) assert(x)
#define DUIASSERT_NE(a,b) DUIASSERT(a!=b)

#ifdef _DUI_DISABLE_NO_VTABLE
#define DUI_NO_VTABLE
#else
#define DUI_NO_VTABLE __declspec(novtable)
#endif