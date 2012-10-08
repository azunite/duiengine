#include "duistd.h"
#include "DuiTimerEx.h"
#include "duiwnd.h"

namespace DuiEngine{


//////////////////////////////////////////////////////////////////////////
//	CDuiTimerEx
//////////////////////////////////////////////////////////////////////////
template<> CDuiTimerEx * Singleton<CDuiTimerEx>::ms_Singleton=0;

BOOL CDuiTimerEx::_SetTimer( HDUIWND hDuiWnd,UINT_PTR uTimerID,UINT nElapse )
{
	_KillTimer(hDuiWnd,uTimerID);
	UINT_PTR idEvent=::SetTimer(NULL,uTimerID,nElapse,_TimerProc);
	if(idEvent==0) return FALSE;
	TIMERINFO ti={hDuiWnd,uTimerID};
	m_mapId2Info[idEvent]=ti;
	return TRUE;
}

void CDuiTimerEx::_KillTimer( HDUIWND hDuiWnd,UINT_PTR uTimerID )
{
	POSITION pos=m_mapId2Info.GetStartPosition();
	while(pos)
	{
		CAtlMap<UINT_PTR,TIMERINFO>::CPair *pPair=m_mapId2Info.GetNext(pos);
		if(pPair->m_value.hDuiWnd==hDuiWnd && pPair->m_value.uTimerID==uTimerID)
		{
			::KillTimer(NULL,pPair->m_key);
			m_mapId2Info.RemoveAtPos((POSITION)pPair);
			break;
		}
	}
}

void CDuiTimerEx::_KillTimer( HDUIWND hDuiWnd )
{
	POSITION pos=m_mapId2Info.GetStartPosition();
	while(pos)
	{
		CAtlMap<UINT_PTR,TIMERINFO>::CPair *pPair=m_mapId2Info.GetNext(pos);
		if(pPair->m_value.hDuiWnd==hDuiWnd)
		{
			::KillTimer(NULL,pPair->m_key);
			m_mapId2Info.RemoveAtPos((POSITION)pPair);
		}
	}
}


VOID CALLBACK CDuiTimerEx::_TimerProc( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{
	TIMERINFO ti;
	if(getSingleton().m_mapId2Info.Lookup(idEvent,ti))
	{
		CDuiWindow *pDuiWnd=DuiWindowManager::GetWindow(ti.hDuiWnd);
		if(pDuiWnd) pDuiWnd->DuiSendMessage(UM_DUI_TIMEREX,ti.uTimerID);
	}
}

}//namespace DuiEngine