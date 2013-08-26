#pragma once

#include "DuiSingletonMap.h"

namespace DuiEngine{

class DUI_EXP DuiThreadActiveWndManager: public DuiSingletonMap<DuiThreadActiveWndManager,HWND,DWORD>
{
public:
	DuiThreadActiveWndManager();

	virtual ~DuiThreadActiveWndManager();

	static HWND SetActive(HWND hWnd);

	static HWND GetActive();

	static void EnterPaintLock();

	static void LeavePaintLock();

protected:
	HWND _SetActive(HWND hWnd);
	HWND _GetActive();

protected:

	CRITICAL_SECTION		m_lockMapActive;
	CRITICAL_SECTION		m_lockRepaint;
};

}//namespace DuiEngine