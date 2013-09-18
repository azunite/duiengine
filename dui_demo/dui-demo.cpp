// dui-demo.cpp : main source file
//

#include "stdafx.h"
#include "menuwndhook.h"
#include "DuiSystem.h" 
#include "DuiDefaultLogger.h"

#include "DuiSkinGif.h"	//应用层定义的皮肤对象

//从ZIP文件加载皮肤模块
#if !defined(_WIN64)
#include "zipskin/DuiResProviderZip.h"
#endif

#ifdef _DEBUG
#include <vld.h>//使用Vitural Leaker Detector来检测内存泄漏，可以从http://vld.codeplex.com/ 下载
#endif

#include "MainDlg.h"
#include "ResModeSelDlg.h"

//演示如何使用引擎外部实现的DUI控件
class  CDuiListBox2 :public CDuiListBoxEx
{
public:
	DUIOBJ_DECLARE_CLASS_NAME(CDuiListBox2, "listboxex")

};
//派生一个只有纵向滚动条皮肤
class CDuiVScrollBarSkin : public DuiEngine::CDuiScrollbarSkin
{
	DUIOBJ_DECLARE_CLASS_NAME(CDuiVScrollBarSkin, "vscrollbar")

public:

	CDuiVScrollBarSkin():m_nStates(3)
	{

	}

	virtual void Draw(CDCHandle dc, CRect rcDraw, DWORD dwState,BYTE byAlpha=0xff)
	{
		if(!m_pDuiImg) return;
		int nSbCode=LOWORD(dwState);
		int nState=LOBYTE(HIWORD(dwState));
		BOOL bVertical=HIBYTE(HIWORD(dwState));
		if(bVertical)
		{
			CRect rcMargin(0,0,0,0);
			rcMargin.top=m_nMagin,rcMargin.bottom=m_nMagin;
			CRect rcSour=GetPartRect(nSbCode,nState,bVertical);
			FrameDraw(dc, m_pDuiImg , rcSour,rcDraw,rcMargin, CLR_INVALID, m_uDrawPart,m_bTile,byAlpha);
		}
	}

	//指示滚动条皮肤是否支持显示上下箭头
	virtual BOOL HasArrow(){return FALSE;}
	virtual int GetIdealSize(){
		if(!m_pDuiImg) return 0;
		return m_pDuiImg->GetWidth()/(1+m_nStates);//图片分成4 or 5 部分横向排列，第一块是轨道，2,3,4,5分别对应滑块的正常，浮动，下压, Disable状态
	}
	DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
		DUIWIN_INT_ATTRIBUTE("states",m_nStates,FALSE)
		DUIWIN_DECLARE_ATTRIBUTES_END()
protected:
	//返回源指定部分在原位图上的位置。
	CRect GetPartRect(int nSbCode, int nState,BOOL bVertical)
	{
		CRect rc;
		if(!bVertical || nSbCode==SB_LINEDOWN || nSbCode==SB_LINEUP) return rc;

		rc.right=GetImage()->GetWidth()/(1+m_nStates);
		rc.bottom=GetImage()->GetHeight();

		if(nSbCode == SB_PAGEUP || nSbCode == SB_PAGEDOWN)
		{
			return rc;
		}
		rc.OffsetRect(rc.Width()*(1+nState),0);
		return rc;
	}

	int m_nStates;
};



int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{
	HRESULT hRes = OleInitialize(NULL);
	DUIASSERT(SUCCEEDED(hRes));

#if !defined(_WIN64)
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
#else
	int nMode=0;	//64位时直接从文件加载资源
#endif
	//资源类型选择完成 -->
	
	DuiSystem *pDuiSystem=new DuiSystem(hInstance);

	//生成控件类厂并注册到系统
	DuiWindowFactoryManager::getSingleton().RegisterFactory(TplDuiWindowFactory<CDuiListBox2>(),true);

	//生成皮肤类厂并注册到系统
	DuiSkinFactoryManager::getSingleton().RegisterFactory(TplSkinFactory<CDuiVScrollBarSkin>());
	DuiSkinFactoryManager::getSingleton().RegisterFactory(TplSkinFactory<CDuiSkinGif>());


	TCHAR szCurrentDir[MAX_PATH]; memset( szCurrentDir, 0, sizeof(szCurrentDir) );
	GetModuleFileName( NULL, szCurrentDir, sizeof(szCurrentDir) );
	LPTSTR lpInsertPos = _tcsrchr( szCurrentDir, _T('\\') );
	*lpInsertPos = _T('\0');   

	DefaultLogger loger;
	loger.setLogFilename(CDuiStringT(szCurrentDir)+_T("\\dui-demo.log")); 
	pDuiSystem->SetLogger(&loger);
	pDuiSystem->InitName2ID(IDR_NAME2ID,_T("XML2"));//加载ID名称对照表,该资源属于APP级别，所有皮肤应该共享该名字表，名字表总是从程序资源加载

	//根据选择的资源加载模式生成resprovider 
	switch(nMode)
	{
	case 0://load from files
		{
			_tcscat( szCurrentDir, _T("\\..\\dui_demo") );
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
#if !defined(_WIN64)
			//从ZIP文件加载皮肤
			DuiResProviderZip *zipSkin=new DuiResProviderZip;
			CDuiStringT strZip=CDuiStringT(szCurrentDir)+_T("\\def_skin.zip");
			if(!zipSkin->Init(strZip))
			{ 
				DUIASSERT(0);
				return 1;
			}
			pDuiSystem->SetResProvider(zipSkin); 
			pDuiSystem->logEvent(_T("load resource from zip"));
#else
			return -1;
#endif;
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

#if defined(DLL_DUI) && !defined(_WIN64)
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
	DuiWindowFactoryManager::getSingleton().UnregisterFactory(CDuiListBox2::GetClassName());
	DuiSkinFactoryManager::getSingleton().UnregisterFactory(CDuiSkinGif::GetClassName());

	delete pDuiSystem;

	OleUninitialize();
	return nRet;
}
