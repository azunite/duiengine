// Change these values to use different versions
#define WINVER		0x0500
#define _WIN32_WINNT	0x0501
#define _WIN32_IE	0x0601
#define _RICHEDIT_VER	0x0200

#undef _ATL_MIN_CRT
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
// #define _WTL_NO_CSTRING

# pragma warning(disable: 4661)

#include <Windows.h>
#include <CommCtrl.h>
#include <Shlwapi.h>
#include <OleCtl.h>

#define ATLASSERT(x)

#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lParam)	((int)(short)LOWORD(lParam))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lParam)	((int)(short)HIWORD(lParam))
#endif

#ifndef NO_DUITYPES

#define _WTYPES_NS DuiEngine
#include "wtl.mini/duistr.h"
#include "wtl.mini/duicrack.h"
#include "wtl.mini/duimisc.h"
#include "wtl.mini/duigdi.h"

#endif

#include "cpconv.h" //可以通过定义NO_STRCVT来屏蔽DUIEngine自带的编码转换接口

#include "tinyxml.h"
#include <string>

#pragma comment(lib,"shlwapi.lib")
#pragma comment(lib,"Msimg32.lib")
#pragma comment(lib,"Comctl32.lib")

#ifdef DLL_DUI
# ifdef DUIENGINE_EXPORTS
# pragma message("dll export")
#  define DUI_EXP __declspec(dllexport)
# else
#  define DUI_EXP __declspec(dllimport)
# endif // DUIENGINE_EXPORTS
#else
#define DUI_EXP
#endif

#pragma warning(disable:4251)
#pragma warning(disable:4275)
