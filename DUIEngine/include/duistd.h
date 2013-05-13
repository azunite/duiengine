#include "duidef.h"

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


# pragma warning(disable:4661)
# pragma warning(disable:4251)

#include <Windows.h>
#include <CommCtrl.h>
#include <Shlwapi.h>
#include <OleCtl.h>
#include <tchar.h>
#include <stdio.h>

//export pugixml interface
#include "../dependencies/pugixml/pugixml.hpp"

#include "DuiUtilities.h"

#ifndef NO_DUITYPES
#define _WTYPES_NS DuiEngine
#include "wtl.mini/duicrack.h"
#include "wtl.mini/duimisc.h"
#include "wtl.mini/duigdi.h"
#endif

#include "wtl.mini/duistr.h" //注意：如果CDuiStringT已经定义，可以定义NO_DUISTR来防止命名冲突
#include "wtl.mini/duicoll.h"

#include "DuiAttrCrack.h"
