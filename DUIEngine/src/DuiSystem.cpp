#include "duistd.h"
#include "DuiSystem.h"
#include "SimpleWnd.h"

#include "DuiThreadActiveWndManager.h"

#include "duiresutil.h"
#include "DuiCSS.h"
#include "duistringpool.h"
#include "duifontpool.h"
#include "duiskin.h"
#include "duiwndstyle.h"
#include "duiimgpool.h"
#include "duiname2id.h"
#include "DuiWindowManager.h"
#include "DuiWndFactoryManager.h"

namespace DuiEngine{

template<> DuiSystem* Singleton<DuiSystem>::ms_Singleton = 0;

DuiSystem::DuiSystem(HINSTANCE hInst,LPCTSTR pszHostClassName/*=_T("DuiHostWnd")*/)
:m_hInst(hInst)
,m_atomWnd(0)
,m_p(NULL)
{
	InitializeCriticalSection(&m_cs);
	m_atomWnd=CSimpleWnd::RegisterSimpleWnd(hInst,pszHostClassName);

	createSingletons();
}

DuiSystem::~DuiSystem(void)
{
	destroySingletons();
	
	UnregisterClass((LPCTSTR)m_atomWnd,m_hInst);
	DeleteCriticalSection(&m_cs);
}

void DuiSystem::LockSharePtr( void * pObj )
{
	EnterCriticalSection(&m_cs);
	m_p=pObj;
}

void * DuiSystem::GetSharePtr()
{
	return m_p;
}

void * DuiSystem::ReleaseSharePtr()
{
	void *pRet=m_p;
	LeaveCriticalSection(&m_cs);
	return pRet;
}


void DuiSystem::createSingletons()
{
	new DuiThreadActiveWndManager();
	new DuiName2ID();
	new DuiResManager();
	new DuiSkinFactoryManager();
	new DuiSkinPool();
	new DuiWindowFactoryManager();
	new DuiWindowManager();
	new CDuiTimerEx();

	new DuiString();
	new DuiCSS();
	new DuiFontPool();
 	new DuiStylePool();
	new DuiImgPool();

}

void DuiSystem::destroySingletons()
{
	delete DuiFontPool::getSingletonPtr();
 	delete DuiStylePool::getSingletonPtr();
	delete DuiName2ID::getSingletonPtr();
	delete DuiString::getSingletonPtr();

	delete CDuiTimerEx::getSingletonPtr();
	delete DuiWindowManager::getSingletonPtr();
	delete DuiWindowFactoryManager::getSingletonPtr();

	delete DuiSkinPool::getSingletonPtr();
	delete DuiSkinFactoryManager::getSingletonPtr();
	delete DuiCSS::getSingletonPtr();
	delete DuiImgPool::getSingletonPtr();

	delete DuiResManager::getSingletonPtr();
	delete DuiThreadActiveWndManager::getSingletonPtr();
}

}//namespace DuiEngine