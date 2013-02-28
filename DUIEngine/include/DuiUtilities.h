#pragma once

#include <assert.h>

namespace DuiEngine
{
	void DUI_EXP DuiHiMetricToPixel(const SIZEL * lpSizeInHiMetric, LPSIZEL lpSizeInPix);
	void DUI_EXP DuiPixelToHiMetric(const SIZEL * lpSizeInPix, LPSIZEL lpSizeInHiMetric);
	void DUI_EXP DuiTrace(LPCTSTR pstrFormat, ...);

	#define DUITRACE DuiTrace
	#define DUIASSERT(x) assert(x)
	#define DUIASSERT_NE(a,b) DUIASSERT(a!=b)

}//end of namespace DuiEngine
