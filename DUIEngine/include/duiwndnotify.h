#pragma once

#ifndef HSTREEITEM
typedef ULONG_PTR HSTREEITEM;
#endif

namespace DuiEngine
{

#define IDC_RICHVIEW_WIN            2000

//////////////////////////////////////////////////////////////////////////
// Notify Messages For DuiWin User
class CDuiWindow;

#define DUI_NOTIFY_ID_HANDLER(id, func) \
	if (uMsg == WM_NOTIFY && id == wParam) \
	{ \
	SetMsgHandled(TRUE); \
	lResult = func((LPNMHDR)lParam); \
	if(IsMsgHandled()) \
	return TRUE; \
	}


#define MSG_DUI_NOTIFY(ctrlid) DUI_NOTIFY_ID_HANDLER(ctrlid, OnDuiNotify_##ctrlid)

#define DUI_NOTIFY_MAP(ctrlid)                   \
    LRESULT OnDuiNotify_##ctrlid(LPNMHDR pnmh)   \
    {                                           \
        UINT_PTR  uCode = pnmh->code;           \
 

#define DUI_NOTIFY_MAP_END()                     \
        SetMsgHandled(FALSE);                   \
        return FALSE;                           \
    }                                           \
 
#define DUI_CHAIN_NOTIFY_MAP(ChainClass, ctrlid)                 \
        if(ChainClass::OnDuiNotify_##ctrlid(pnmh))               \
            return TRUE;                                        \
 

// LRESULT OnDuiNotifyHandler(LPNMHDR pnmh)
#define DUI_NOTIFY_HANDLER(id, cd, func) \
	if(cd == pnmh->code && id == pnmh->idFrom) \
	{ \
		return func(pnmh); \
	}

// void OnDuiItemCommandData(UINT uData)
#define DUI_NOTIFY_ID_CMD_DATA(itemid, func)                                  \
	if (DUINM_COMMAND == uCode && itemid == ((DuiEngine::LPDUINMCOMMAND)pnmh)->uItemID)  \
	{                                                                       \
	func(((LPDUINMCOMMAND)pnmh)->uItemData);                            \
	return TRUE;                                                        \
	}

// void OnDuiItemCommand()
#define DUI_NOTIFY_ID_COMMAND(itemid, func)                                  \
    if (DUINM_COMMAND == uCode && itemid == ((DuiEngine::LPDUINMCOMMAND)pnmh)->uItemID)  \
    {                                                                       \
        func();                                                             \
        return TRUE;                                                        \
    }                                                                       \
 
#define DUI_NOTIFY_ID_COMMAND_EX(itemidbegin, itemidend, func)					\
	if (DUINM_COMMAND == uCode && itemidbegin <= ((DuiEngine::LPDUINMCOMMAND)pnmh)->uItemID	\
		&& itemidend >= ((LPDUINMCOMMAND)pnmh)->uItemID )						\
	{																			\
		func(((LPDUINMCOMMAND)pnmh)->uItemID);                                   \
		return TRUE;															\
	}																			\
 
// void OnDuiCommand(UINT uItemID)
#define DUI_NOTIFY_COMMAND(func)                                                     \
    if (DUINM_COMMAND == uCode)                                                      \
    {                                                                               \
        func(((LPDUINMCOMMAND)pnmh)->uItemID);   \
        return TRUE;                                                                \
    }                                                                               \
 

// Command Notify
#define DUINM_COMMAND  1
typedef struct _DUINMCOMMAND
{
    NMHDR       hdr;
    UINT        uItemID;
    ULONG_PTR   uItemData;
} DUINMCOMMAND, *LPDUINMCOMMAND;


// Tab Sel Change Notify
#define DUINM_TAB_SELCHANGING  9

typedef struct _DUINMTABSELCHANGE
{
    NMHDR       hdr;
    UINT        uTabID;
    UINT        uTabItemIDNew;
    UINT        uTabItemIDOld;
    BOOL        bCancel;
} DUINMTABSELCHANGE, *LPDUINMTABSELCHANGE;

// BOOL OnDuiTabSelChange(int nTabItemIDOld, int nTabItemIDNew)
#define DUI_NOTIFY_TAB_SELCHANGE(tabid, func)                                        \
    if (DUINM_TAB_SELCHANGING == uCode && tabid == ((DuiEngine::LPDUINMTABSELCHANGE)pnmh)->uTabID) \
    {                                                                               \
        BOOL bRet = func(                                                           \
            ((LPDUINMTABSELCHANGE)pnmh)->uTabItemIDOld,                              \
            ((LPDUINMTABSELCHANGE)pnmh)->uTabItemIDNew);                             \
        if (!bRet)                                                                  \
            ((LPDUINMTABSELCHANGE)pnmh)->bCancel = TRUE;                             \
        return TRUE;                                                                \
    }                                                                               \
 
// Tab Sel Change Notify
#define DUINM_TAB_SELCHANGED  10
typedef struct _DUINMTABSELCHANGED
{
    NMHDR       hdr;
    UINT        uTabID;
    UINT        uTabItemIDNew;
    UINT        uTabItemIDOld;
} DUINMTABSELCHANGED, *LPDUINMTABSELCHANGED;

// void OnDuiTabSelChanged(int nTabItemIDOld, int nTabItemIDNew)
#define DUI_NOTIFY_TAB_SELCHANGED(tabid, func)                                        \
	if (DUINM_TAB_SELCHANGED == uCode && tabid == ((DuiEngine::LPDUINMTABSELCHANGE)pnmh)->uTabID) \
{                                                                               \
	func(                                                           \
	((LPDUINMTABSELCHANGE)pnmh)->uTabItemIDOld,                              \
	((LPDUINMTABSELCHANGE)pnmh)->uTabItemIDNew);                             \
	return TRUE;                                                                \
}                                                                               \
 
#define DUINM_TAB_ITEMHOVER	11
typedef struct _DUINMTABITEMHOVER
{
    NMHDR       hdr;
    UINT        iItem;
    CRect		rcItem;
} DUINMTABITEMHOVER, *LPDUINMTABITEMHOVER;

#define DUINM_TAB_ITEMLEAVE 12
typedef DUINMTABITEMHOVER DUINMTABITEMLEAVE, *LPDUINMTABITEMLEAVE;

class CDuiScrollBar;
#define DUINM_SCROLL	14
typedef struct tagDUINMSCROLL
{
    NMHDR       hdr;
    UINT		uSbCode;
    int			nPos;
    BOOL		bVertical;
    CDuiScrollBar *pScrollBar;
} DUINMSCROLL,*PDUINMSCROLL;

// void OnDropdownSelChanged(int nIndex)
#define DUI_NOTIFY_SCROLL(id, func)                                  \
	if (DUINM_SCROLL == uCode && id == pnmh->idFrom)  \
{                                                                       \
	func(((PDUINMSCROLL)pnmh)->uSbCode,((DuiEngine::PDUINMSCROLL)pnmh)->nPos,((DuiEngine::PDUINMSCROLL)pnmh)->pScrollBar);   \
	return TRUE;                                                        \
}

class CDuiItemPanel;

// Item Click Notify
#define DUINM_LBITEMNOTIFY     15

typedef struct tagDUINMITEMNOTIFY
{
    NMHDR       hdr;
    LPNMHDR		pOriginHdr;	//原始消息
    CDuiItemPanel *pItem;
    CDuiWindow *	pHostDuiWin;
} DUINMITEMNOTIFY, *LPDUINMITEMNOTIFY;


#define DUINM_ITEMMOUSEEVENT	16
typedef struct tagDUINMITEMMOUSEEVENT
{
    NMHDR       hdr;
    CDuiItemPanel *	pItem;
    UINT		uMsg;
    WPARAM		wParam;
    LPARAM		lParam;
} DUINMITEMMOUSEEVENT, *LPDUINMITEMMOUSEEVENT;



// Get Display Info Notify
#define DUINM_GETLBDISPINFO  17
typedef struct tagDUINMGETLBDISPINFO
{
    NMHDR       hdr;
    int         nListItemID;
    BOOL        bHover;
    BOOL        bSelect;
    CDuiItemPanel *	pItem;
    CDuiWindow *	pHostDuiWin;
} DUINMGETLBDISPINFO, *LPDUINMGETLBDISPINFO;

#define DUINM_LBSELCHANGING 18
#define DUINM_LBSELCHANGED	19
typedef struct tagDUINMLBSELCHANGE
{
    NMHDR       hdr;
    int nNewSel;
    int nOldSel;
    UINT uHoverID;
    UINT uMsg;
} DUINMLBSELCHANGE, *LPDUINMLBSELCHANGE;


// Get Display Info Notify
#define DUINM_GETTBDISPINFO  20
typedef struct tagDUINMGETTBDISPINFO
{
    NMHDR       hdr;
    HSTREEITEM  hItem;
    BOOL        bHover;
    BOOL        bSelect;
    CDuiItemPanel *	pItem;
    CDuiWindow *	pHostDuiWin;
} DUINMGETTBDISPINFO, *LPDUINMGETTBDISPINFO;

#define DUINM_TBSELCHANGING	21
typedef struct tagDUINMTBSELCHANGING
{
	NMHDR       hdr;
	HSTREEITEM hNewSel;
	HSTREEITEM hOldSel;
	BOOL		bCancel;
} DUINMTBSELCHANGING, *LPDUINMTBSELCHANGING;


#define DUINM_TBSELCHANGED	22
typedef struct tagDUINMTBSELCHANGED
{
    NMHDR       hdr;
    HSTREEITEM hNewSel;
    HSTREEITEM hOldSel;
} DUINMTBSELCHANGED, *LPDUINMTBSELCHANGED;


#define DUINM_RICHEDIT_NOTIFY	25
typedef struct tagDUIRICHEDITNOTIFY
{
    NMHDR hdr;
    DWORD iNotify;
    LPVOID pv;
} DUIRICHEDITNOTIFY,*LPDUIRICHEDITNOTIFY;

class CDuiSliderBar;
#define DUINM_SLIDER	30
typedef struct tagDUINMSLIDER
{
	NMHDR hdr;
	UINT uSbCode;
	CDuiSliderBar *pSliderBar;
	int	 nPos;
	BOOL bVertical;
} DUINMSLIDER,*LPDUINMSLIDER;

//////////////////////////////////////////////////////////////////////////
//  internal notify message

#define DUINM_INTERNAL_FIRST	1000
#define DUINM_INTERNAL_LAST		2000

class CDuiRealWnd;

typedef struct _DUINMREALWNDCMN
{
    NMHDR       hdr;
    UINT        uItemID;
    CDuiRealWnd *	pRealWnd;
} DUINMREALWNDCMN, *LPDUINMREALWNDCMN;

typedef struct _DUINMREALWNDMSGPROC
{
    NMHDR       hdr;
    UINT        uItemID;
    CDuiRealWnd *	pRealWnd;
    HWND		hWnd;
    UINT		uMsg;
    WPARAM		wParam;
    LPARAM		lParam;
    BOOL		bMsgHandled;
} DUINMREALWNDMSGPROC;

#define DUINM_REALWND_CREATE	DUINM_INTERNAL_FIRST
#define DUINM_REALWND_INIT		(DUINM_INTERNAL_FIRST+1)
#define DUINM_REALWND_DESTROY	(DUINM_INTERNAL_FIRST+2)
#define DUINM_REALWND_SIZE	(DUINM_INTERNAL_FIRST+3)

}//namespace DuiEngine
