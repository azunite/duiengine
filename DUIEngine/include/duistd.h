// Change these values to use different versions
#define WINVER		0x0500
#define _WIN32_WINNT	0x0501
#define _WIN32_IE	0x0601
#define _RICHEDIT_VER	0x0200

#undef _ATL_MIN_CRT
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#define _WTL_NO_CSTRING

# pragma warning(disable: 4661)

#include <atlbase.h>
#include <atlwin.h>
#include <atlstr.h>
#include <atltrace.h>
#include <atlcoll.h>


#include <atlapp.h>
#include <atlframe.h>
#include <atlcrack.h>
#include <atlmisc.h>
// #include <atlctrls.h>

#include "tinyxml.h"
#include <string>

// #define TOLUA_API	extern "C"

#ifdef DLL_DUI
# ifdef DUIENGINE_EXPORTS
#  define DUI_EXP __declspec(dllexport)
# else
#  define DUI_EXP __declspec(dllimport)
# endif // DUIENGINE_EXPORTS
#else
#define DUI_EXP
#endif

#pragma warning(disable:4251)
#pragma warning(disable:4275)
