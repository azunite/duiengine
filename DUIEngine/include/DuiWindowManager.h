//////////////////////////////////////////////////////////////////////////
// CDuiWindow Handle Manager
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "DuiSingletonMap.h"

namespace DuiEngine
{

class CDuiWindow;
// DuiWindow Handle
typedef DWORD HDUIWND;

class DUI_EXP DuiWindowManager :public DuiSingletonMap<DuiWindowManager,CDuiWindow*,HDUIWND>
{
public:

    DuiWindowManager();

    ~DuiWindowManager();

    // Get DuiWindow pointer from handle
    static CDuiWindow* GetWindow(HDUIWND hDuiWnd);

    // Specify a handle to a DuiWindow
    static HDUIWND NewWindow(CDuiWindow *pDuiWnd);

    // Destroy DuiWindow
    static BOOL DestroyWindow(HDUIWND hDuiWnd);
protected:

    CRITICAL_SECTION m_lockWndMap;

    HDUIWND m_hNextWnd;
};

}//namespace DuiEngine