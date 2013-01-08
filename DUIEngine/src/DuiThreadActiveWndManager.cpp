#include "duistd.h"
#include "DuiThreadActiveWndManager.h"

namespace DuiEngine
{


//////////////////////////////////////////////////////////////////////////
//	DuiThreadActiveWndManager
//////////////////////////////////////////////////////////////////////////
template<> DuiThreadActiveWndManager* Singleton<DuiThreadActiveWndManager>::ms_Singleton = NULL;

DuiThreadActiveWndManager::DuiThreadActiveWndManager()
{
    ::InitializeCriticalSection(&m_lockRepaint);
    ::InitializeCriticalSection(&m_lockMapActive);
}

DuiThreadActiveWndManager::~DuiThreadActiveWndManager()
{
    ::DeleteCriticalSection(&m_lockRepaint);
    ::DeleteCriticalSection(&m_lockMapActive);
}

HWND DuiThreadActiveWndManager::SetActive(HWND hWnd)
{
    return getSingleton()._SetActive(hWnd);
}

HWND DuiThreadActiveWndManager::GetActive()
{
    return getSingleton()._GetActive();
}

void DuiThreadActiveWndManager::EnterPaintLock()
{
    ::EnterCriticalSection(&getSingleton().m_lockRepaint);
}

void DuiThreadActiveWndManager::LeavePaintLock()
{
    ::LeaveCriticalSection(&getSingleton().m_lockRepaint);
}

HWND DuiThreadActiveWndManager::_SetActive(HWND hWnd)
{
    ::EnterCriticalSection(&m_lockMapActive);
    HWND	hWndLastActive	= _GetActive();
    SetKeyObject(::GetCurrentThreadId(),hWnd);
    ::LeaveCriticalSection(&m_lockMapActive);
    return hWndLastActive;
}

HWND DuiThreadActiveWndManager::_GetActive()
{
    ::EnterCriticalSection(&m_lockMapActive);
    HWND	hWndAct = NULL;
    GetKeyObject(::GetCurrentThreadId(),hWndAct);
    ::LeaveCriticalSection(&m_lockMapActive);
    return hWndAct;
}

}//namespace DuiEngine