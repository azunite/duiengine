// magicbox2.cpp : main source file for magicbox2.exe
//

#include "stdafx.h"
#include "menuwndhook.h"
#include "DuiSystem.h"
#include "DuiDefaultLogger.h"

//从ZIP文件加载皮肤模块
#include "../zipresprovider/DuiResProviderZip.h"
#ifdef DEBUG
#pragma comment(lib,"zlib_d.lib")
#pragma comment(lib,"zipresprovider_d.lib")
#else
#pragma comment(lib,"zlib.lib")
#pragma comment(lib,"zipresprovider.lib")
#endif

#ifdef _DEBUG
#include "..\memleakdetect\MemLeakDetect.h"
// static CMemLeakDetect memLeakDetect;
#endif
 
#include "MainDlg.h"
 

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{
	HRESULT hRes = CoInitialize(NULL);
	DUIASSERT(SUCCEEDED(hRes));
 
	char szCurrentDir[MAX_PATH]; memset( szCurrentDir, 0, sizeof(szCurrentDir) );
	GetModuleFileNameA( NULL, szCurrentDir, sizeof(szCurrentDir) );
	LPSTR lpInsertPos = strrchr( szCurrentDir, L'\\' );
	*lpInsertPos = '\0';   

	DuiSystem duiSystem(hInstance);
	DefaultLogger loger;
	loger.setLogFilename(CStringA(szCurrentDir)+"\\dui-demo.log");
	duiSystem.SetLogger(&loger);

	//从ZIP文件加载皮肤
	DuiResProviderZip *zipSkin=new DuiResProviderZip;
	CString strZip=CA2T(szCurrentDir)+_T("\\def_skin.zip");
	if(!zipSkin->Init(strZip))
	{
		DUIASSERT(0);
		return 1;
	}
	duiSystem.SetResProvider(zipSkin); 

	duiSystem.logEvent("demo started");
	duiSystem.InitName2ID(IDR_DUI_NAME2ID);//加载ID名称对照表,该资源属于APP级别，所有皮肤应该共享该名字表，名字表总是从程序资源加载
#ifdef __DUIFILE_RC 
//     lstrcatA( szCurrentDir, "\\..\\dui_demo" );
// 	DuiResProviderFiles *pResFiles=new DuiResProviderFiles;
// 	if(!pResFiles->Init(szCurrentDir))
// 	{
// 		DUIASSERT(0);
// 		return 1;
// 	}
// 	duiSystem.SetResProvider(pResFiles);
#else 
// 	duiSystem.SetResProvider(new DuiResProviderPE(hInstance));
#endif 
	// 以下 Load xx 的语句是必须的，否则皮肤将不能显示。这部分资源属性皮肤级别，不同的皮肤可以有不同的定义
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

	duiSystem.logEvent("demo end");

	delete duiSystem.GetResProvider();
	//释放资源 
	CMenuWndHook::UnInstallHook();

	CoUninitialize();
	return nRet;
}
