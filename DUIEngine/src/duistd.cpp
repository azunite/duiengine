#include "duistd.h"

void DUI_EXP DuiTrace(LPCTSTR pstrFormat, ...)
{
#ifdef _DEBUG
	TCHAR szBuffer[300] = { 0 };
	va_list args;
	va_start(args, pstrFormat);
	::wvnsprintf(szBuffer, ARRAYSIZE(szBuffer)-1, pstrFormat, args);
	_tcscat(szBuffer, _T("\n"));
	va_end(args);
	::OutputDebugString(szBuffer);
#endif
}
