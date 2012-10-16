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
	m_mapNamedObj[idEvent]=ti;
	return TRUE;
}

void CDuiTimerEx::_KillTimer( HDUIWND hDuiWnd,UINT_PTR uTimerID )
{
	std::map<UINT_PTR,TIMERINFO>::iterator it=m_mapNamedObj.begin();
	while(it!=m_mapNamedObj.end())
	{
		if(it->second.hDuiWnd==hDuiWnd && it->second.uTimerID==uTimerID)
		{
			::KillTimer(NULL,it->first);
			m_mapNamedObj.erase(it);
			break;
		}
		it++;
	}
}

void CDuiTimerEx::_KillTimer( HDUIWND hDuiWnd )
{
	std::map<UINT_PTR,TIMERINFO>::iterator it=m_mapNamedObj.begin();
	while(it!=m_mapNamedObj.end())
	{
		std::map<UINT_PTR,TIMERINFO>::iterator it1=it;
		if(it1->second.hDuiWnd==hDuiWnd)
		{
			::KillTimer(NULL,it1->first);
			m_mapNamedObj.erase(it1);
			break;
		}
		it++;
	}
}


VOID CALLBACK CDuiTimerEx::_TimerProc( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime )
{
	TIMERINFO ti;
	if(getSingleton().GetKeyObject(idEvent,ti))
	{
		CDuiWindow *pDuiWnd=DuiWindowManager::GetWindow(ti.hDuiWnd);
		if(pDuiWnd) pDuiWnd->DuiSendMessage(UM_DUI_TIMEREX,ti.uTimerID);
	}
}

}//namespace DuiEngine