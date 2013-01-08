#pragma once

namespace DuiEngine
{

#define UM_MSGFILTER	(WM_USER+200)	//wparam: 1-register,0-unregister lparam: CMessageFilter *

class DUI_EXP CDuiMessageFilter
{
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg)=NULL;

    void MsgFilterRegister(HWND hHost)
    {
        ::SendMessage(hHost,UM_MSGFILTER,1,(LPARAM)this);
    }

    void MsgFilterUnregister(HWND hHost)
    {
        ::SendMessage(hHost,UM_MSGFILTER,0,(LPARAM)this);
    }
};

}//namespace DuiEngine