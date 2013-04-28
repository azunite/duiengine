// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//  are changed infrequently
//

#pragma once

#include <duistd.h>
#include <duihostwnd.h>
#include <duictrls.h>
#include <duiwndnotify.h>
#include <DuiCSS.h>

#ifdef DLL_DUI	//DLL version duiengine support lua
#include "..\scriptModule\luaScriptModule\luaScriptModule\luaScriptModule.h"

#ifdef _DEBUG
#pragma comment(lib,"..\\scriptModule\\luaScriptModule\\lib\\luaScriptModule_d.lib")
#else
#pragma comment(lib,"..\\scriptModule\\luaScriptModule\\lib\\luaScriptModule.lib")
#endif

#endif


#include "resource.h"	//APP资源
#include "duires/res.h" //包含DUI资源定义

#include "../zlib/zconf.h"
#include "../zlib/zlib.h"

using namespace DuiEngine;

#ifdef _DEBUG

# pragma comment(lib, "tinyxml_d.lib")
#pragma comment(lib,"zlib_d.lib")

	#ifdef DLL_DUI
	# pragma comment(lib, "duiengine_d.lib")
	#else
	# pragma comment(lib, "duiengine_static_d.lib")
	#endif
#else

# pragma comment(lib, "tinyxml.lib")
#pragma comment(lib,"zlib.lib")

	#ifdef DLL_DUI
	# pragma comment(lib, "duiengine.lib")
	#else
	# pragma comment(lib, "duiengine_static.lib")
	#endif

#endif





