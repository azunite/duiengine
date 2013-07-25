// dllmain.cpp : DllMain 的实现。

#include "duistd.h"

#if defined(USING_ATL) && defined(DLL_DUI)
//只有使用ATL的动态库版本才需要DllMain

class CDuiEngineModule : public CAtlDllModuleT< CDuiEngineModule >
{
} _AtlModule;

// DLL 入口点
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	return _AtlModule.DllMain(dwReason, lpReserved); 
}

#endif