// magicbox2.cpp : main source file for magicbox2.exe
//

#include "stdafx.h"
#include "menuwndhook.h"
#include "DuiSystem.h"

#ifdef _DEBUG
#include "..\memleakdetect\MemLeakDetect.h"
static CMemLeakDetect memLeakDetect;
#endif
 
#include "MainDlg.h"
 
CAppModule _Module;
 

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{
	HRESULT hRes = CoInitialize(NULL);
	ATLASSERT(SUCCEEDED(hRes));

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	DefWindowProc(NULL, 0, 0, 0L);
	AtlInitCommonControls(ICC_BAR_CLASSES);	// add flags to support other controls
	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));
	AtlAxWinInit();

	DuiSystem duiSystem;

#ifdef __DUIFILE_RC
    char szCurrentDir[MAX_PATH]; memset( szCurrentDir, 0, sizeof(szCurrentDir) );
    GetModuleFileNameA( NULL, szCurrentDir, sizeof(szCurrentDir) );
    LPSTR lpInsertPos = strrchr( szCurrentDir, L'\\' );
    *lpInsertPos = '\0';   
    lstrcatA( szCurrentDir, "\\..\\dui_demo" );
	DuiResManager::getSingleton().SetResourcePath( szCurrentDir, "layout\\idmap.xml");
	DuiResManager::getSingleton().SetResourcePath( szCurrentDir, "layout\\def_skin_idmap.xml");
#else
	DuiResManager::getSingleton().SetResourceDLL(hInstance);
#endif
	// 以下 Load xx 的语句是必须的，否则皮肤将不能显示
	DuiName2ID::getSingleton().Init(IDR_DUI_NAME2ID);		//加载ID名称对照表
	DuiString::getSingleton().Init(IDR_DUI_STRING_DEF); // 加载字符串
	DuiFontPool::getSingleton().SetDefaultFont(DuiString::getSingleton().Get(IDS_APP_FONT), -12); // 设置字体

	DuiSkinPool::getSingleton().Init(IDR_DUI_SKIN_DEF); // 加载皮肤
	DuiStylePool::getSingleton().Init(IDR_DUI_STYLE_DEF); // 加载风格
	DuiCSS::getSingleton().Init(IDR_DUI_OBJATTR_DEF);//加载类默认属性

	CMenuWndHook::InstallHook(hInstance,"skin_menuborder");
	int nRet = 0; 
	// BLOCK: Run application
	{
		CMainDlg dlgMain;  
		nRet = dlgMain.DoModal();  
	}
	_Module.Term(); 
	//释放资源 
	CMenuWndHook::UnInstallHook();

	CoUninitialize();
	return nRet;
}
