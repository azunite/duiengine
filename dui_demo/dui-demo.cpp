// dui-demo.cpp : main source file
//

#include "stdafx.h"
#include "menuwndhook.h"
#include "DuiSystem.h" 
#include "DuiDefaultLogger.h"

#include "DuiSkinGif.h"	//应用层定义的皮肤对象

//从ZIP文件加载皮肤模块
#include "zipskin/DuiResProviderZip.h"


#ifdef _DEBUG
// #include <vld.h>//使用Vitural Leaker Detector来检测内存泄漏，可以从http://vld.codeplex.com/ 下载
#endif

#include "MainDlg.h"
#include "ResModeSelDlg.h"

//演示如何使用引擎外部实现的DUI控件
class  CDuiListBox2 :public CDuiListBoxEx
{
public:
	DUIOBJ_DECLARE_CLASS_NAME(CDuiListBox2, "listboxex")

};


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{
	HRESULT hRes = OleInitialize(NULL);
	DUIASSERT(SUCCEEDED(hRes));
 
	//////////////////////////////////////////////////////////////////////////
	//<--资源类型选择 
	DuiSystem * pDuiModeSel = new DuiSystem(hInstance);
	DuiSystem::getSingletonPtr();

	DuiResProviderZip *pResModeSel= new DuiResProviderZip;
	pResModeSel->Init(hInstance,IDR_ZIP_MODESEL,_T("ZIP"));
	pDuiModeSel->SetResProvider(pResModeSel);
 	DuiSkinPool::getSingleton().Init(100); // 加载皮肤,为了不依赖于程序中的宏定义，此处的ID采用硬编码
 	DuiStylePool::getSingleton().Init(101); // 加载风格
 	DuiCSS::getSingleton().Init(104);//加载类默认属性
	int nMode=-1;
 	{
 		CResModeSelDlg dlgModeSel;  
 		if(IDOK==dlgModeSel.DoModal())
 		{
 			nMode=dlgModeSel.m_nMode;
 		}
 	}
	delete pResModeSel;
	delete pDuiModeSel;

	if(nMode==-1) return -1;

	//资源类型选择完成 -->
	
	DuiSystem *pDuiSystem=new DuiSystem(hInstance);

	//生成控件类厂并注册到系统
	TplDuiWindowFactory<CDuiListBox2> *pFacListCtrl= new TplDuiWindowFactory<CDuiListBox2>;
	DuiWindowFactoryManager::getSingleton().RegisterFactory(pFacListCtrl,true);

	//生成皮肤类厂并注册到系统
	TplSkinFactory<CDuiSkinGif> * pFacSkinGif = new TplSkinFactory<CDuiSkinGif>;
	DuiSkinFactoryManager::getSingleton().RegisterFactory(pFacSkinGif);


	char szCurrentDir[MAX_PATH]; memset( szCurrentDir, 0, sizeof(szCurrentDir) );
	GetModuleFileNameA( NULL, szCurrentDir, sizeof(szCurrentDir) );
	LPSTR lpInsertPos = strrchr( szCurrentDir, L'\\' );
	*lpInsertPos = '\0';   

	DefaultLogger loger;
	loger.setLogFilename(DUI_CA2T(CDuiStringA(szCurrentDir)+"\\dui-demo.log")); 
	pDuiSystem->SetLogger(&loger);
	pDuiSystem->InitName2ID(IDR_NAME2ID,"XML2");//加载ID名称对照表,该资源属于APP级别，所有皮肤应该共享该名字表，名字表总是从程序资源加载

	//根据选择的资源加载模式生成resprovider 
	switch(nMode)
	{
	case 0://load from files
		{
			lstrcatA( szCurrentDir, "\\..\\dui_demo" );
			DuiResProviderFiles *pResFiles=new DuiResProviderFiles;
			if(!pResFiles->Init(szCurrentDir))
			{
				DUIASSERT(0);
				return 1;
			}
			pDuiSystem->SetResProvider(pResFiles);
			pDuiSystem->logEvent(_T("load resource from files"));
		}
		break;
	case 1://load from PE
		{
			pDuiSystem->SetResProvider(new DuiResProviderPE(hInstance));
			pDuiSystem->logEvent(_T("load resource from exe"));
		}
		break;
	default://load form ZIP
		{
			//从ZIP文件加载皮肤
			DuiResProviderZip *zipSkin=new DuiResProviderZip;
			CDuiStringT strZip=DUI_CA2T(szCurrentDir)+_T("\\def_skin.zip");
			if(!zipSkin->Init(strZip))
			{ 
				DUIASSERT(0);
				return 1;
			}
			pDuiSystem->SetResProvider(zipSkin); 
			pDuiSystem->logEvent(_T("load resource from zip"));
		}
		break;
	}

// 2013前版本使用的系统初始化代码，新版本使用DuiSystem::Init来处理。
//	以下 Load xx 的语句是必须的，否则皮肤将不能显示。这部分资源属性皮肤级别，不同的皮肤可以有不同的定义
// 	BOOL bOK=DuiStringPool::getSingleton().Init(IDR_DUI_STRING_DEF); // 加载字符串
// 	DuiFontPool::getSingleton().SetDefaultFont(DuiStringPool::getSingleton().Get(IDS_APP_FONT), -12); // 设置字体,必须在style加载前设置。
// 	bOK=DuiSkinPool::getSingleton().Init(IDR_DUI_SKIN_DEF); // 加载皮肤
// 	bOK=DuiStylePool::getSingleton().Init(IDR_DUI_STYLE_DEF); // 加载风格
// 	bOK=DuiCSS::getSingleton().Init(IDR_DUI_OBJATTR_DEF);//加载类默认属性

	BOOL bOK=pDuiSystem->Init(IDR_DUI_INIT); //初始化DUI系统,原来的系统初始化方式依然可以使用。
	pDuiSystem->SetMsgBoxTemplate(IDR_DUI_MSGBOX);

#ifdef DLL_DUI
	CLuaScriptModule scriptLua;
	scriptLua.executeScriptFile("..\\dui_demo\\lua\\test.lua");
	pDuiSystem->SetScriptModule(&scriptLua);
#endif

	CMenuWndHook::InstallHook(hInstance,"skin_menuborder");
	int nRet = 0; 
	// BLOCK: Run application
	{
		pDuiSystem->logEvent(_T("demo started"));
		CMainDlg dlgMain;  
		nRet = dlgMain.DoModal();  
		pDuiSystem->logEvent(_T("demo end"));
	}


	delete pDuiSystem->GetResProvider();
	//释放资源 
	CMenuWndHook::UnInstallHook();

	DuiSkinPool::getSingleton().RemoveAll();//以DLL方式使用DuiEngine时，使用了自定义皮肤类型时需要先删除皮肤池才能正常释放皮肤类厂。

	//从系统中反注册控件及皮肤类厂并删除类厂对象
	DuiWindowFactoryManager::getSingleton().UnregisterFactory(pFacListCtrl);
	delete pFacListCtrl;
	DuiSkinFactoryManager::getSingleton().UnregisterFactory(pFacSkinGif);
	delete pFacSkinGif;

	delete pDuiSystem;

	OleUninitialize();
	return nRet;
}
