// magicbox2.cpp : main source file for magicbox2.exe
//

#include "stdafx.h"
#include "DuiSystem.h" 
#include "DuiDefaultLogger.h"
 

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
	loger.setLogFilename(DUI_CA2T(CDuiStringA(szCurrentDir)+"\\dui-demo.log"));
	duiSystem.SetLogger(&loger);

	duiSystem.logEvent(_T("demo started"));
	duiSystem.InitName2ID(IDR_NAME2ID,"XML2");//加载ID名称对照表,该资源属于APP级别，所有皮肤应该共享该名字表，名字表总是从程序资源加载
#ifdef __DUIFILE_RC 
	//从文件夹加载皮肤,指定皮肤位置
       lstrcatA( szCurrentDir, "\\..\\skin" );
	DuiResProviderFiles *pResFiles=new DuiResProviderFiles;
	if(!pResFiles->Init(szCurrentDir))
	{
		DUIASSERT(0);
		return 1;
	}
	duiSystem.SetResProvider(pResFiles);
#else 
	//从资源加载皮肤
	duiSystem.SetResProvider(new DuiResProviderPE(hInstance));
#endif 
	BOOL bOK=duiSystem.Init(IDR_DUI_INIT); //初始化DUI系统,原来的系统初始化方式依然可以使用。
	duiSystem.SetMsgBoxTemplate(IDR_DUI_MSGBOX);

	int nRet = 0; 
	// BLOCK: Run application
	{
		CMainDlg dlgMain;  
		nRet = dlgMain.DoModal();  
	}

	duiSystem.logEvent(_T("demo end"));

	delete duiSystem.GetResProvider();

	CoUninitialize();
	return nRet;
}
