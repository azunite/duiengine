#include "duistd.h"
#include "DuiWindowManager.h"
#include "DuiTimerEx.h"

namespace DuiEngine{

//////////////////////////////////////////////////////////////////////////
template<> DuiWindowManager* Singleton<DuiWindowManager>::ms_Singleton=0;


DuiWindowManager::DuiWindowManager()
: m_hNextWnd(NULL)
{
	::InitializeCriticalSection(&m_lockWndMap);
}

DuiWindowManager::~DuiWindowManager()
{
	::DeleteCriticalSection(&m_lockWndMap);
}

// Get DuiWindow pointer from handle
CDuiWindow* DuiWindowManager::GetWindow(HDUIWND hDuiWnd)
{
	if(!hDuiWnd) return NULL;
	CDuiWindow *pRet=NULL;
	::EnterCriticalSection(&getSingleton().m_lockWndMap);

	getSingleton().GetKeyObject(hDuiWnd,pRet);
	::LeaveCriticalSection(&getSingleton().m_lockWndMap);
	return pRet;
}

// Specify a handle to a DuiWindow
HDUIWND DuiWindowManager::NewWindow(CDuiWindow *pDuiWnd)
{
	DUIASSERT(pDuiWnd);
	::EnterCriticalSection(&getSingleton().m_lockWndMap);

	HDUIWND hDuiWndNext = ++ getSingleton().m_hNextWnd;
	getSingleton().AddKeyObject(hDuiWndNext,pDuiWnd);
	::LeaveCriticalSection(&getSingleton().m_lockWndMap);

	return hDuiWndNext;
}

// Destroy DuiWindow
BOOL DuiWindowManager::DestroyWindow(HDUIWND hDuiWnd)
{
	::EnterCriticalSection(&getSingleton().m_lockWndMap);

	BOOL bRet=getSingleton().RemoveKeyObject(hDuiWnd);
	CDuiTimerEx::KillTimer(hDuiWnd);

	::LeaveCriticalSection(&getSingleton().m_lockWndMap);

	return bRet;
}

}//namespace DuiEngine