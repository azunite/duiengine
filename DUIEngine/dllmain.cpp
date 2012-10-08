// dllmain.cpp : DllMain 的实现。

#include "duistd.h"

class CDuiEngineModule : public CAtlDllModuleT< CDuiEngineModule >
{
} _AtlModule;

// DLL 入口点
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	return _AtlModule.DllMain(dwReason, lpReserved); 
}
