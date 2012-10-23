//////////////////////////////////////////////////////////////////////////
//   File Name: DuiWnd.h
// Description: DuiWindow Definition
//     Creator: Zhang Xiaoxuan
//     Version: 2009.04.28 - 1.0 - Create
//				2011.09.01 - 2.0 huang jianxiong
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "DuiWindowManager.h"
#include "DuiTimerEx.h"
#include "DuiContainer.h"
#include "duimsgcracker.h"

#include "duiwndstyle.h"
#include "duistringpool.h"
#include "DuiSkinPool.h"
#include "duiwndnotify.h"
#include "gdialpha.h"
#include "duiref.h"
#include <OCIdl.h>

namespace DuiEngine{

/////////////////////////////////////////////////////////////////////////
enum {NormalShow=0,ParentShow=1};	//提供WM_SHOWWINDOW消息识别是父窗口显示还是要显示本窗口

typedef struct tagDUIWNDPOS {
	int     x;
	int     y;
	int     cx;
	int     cy;
} DUIWNDPOS,*LPDUIWNDPOS;


#define DUIC_WANTARROWS     0x0001      /* Control wants arrow keys         */
#define DUIC_WANTTAB        0x0002      /* Control wants tab keys           */
#define DUIC_WANTRETURN		0x0004		/* Control wants return keys		*/
#define DUIC_WANTCHARS      0x0008      /* Want WM_CHAR messages            */
#define DUIC_WANTALLKEYS    0xFFFF      /* Control wants all keys           */

class DUI_EXP CDuiTimerID
{
public:
	DWORD	hDuiWnd:24;		//窗口句柄,如果窗口句柄超过24位范围，则不能使用这种方式设置定时器
	DWORD	uTimerID:7;		//定时器ID，一个窗口最多支持128个定时器。
	DWORD	bDuiTimer:1;	//区别通用定时器的标志，标志为1时，表示该定时器为DUI定时器

	CDuiTimerID(HDUIWND hWnd,char id)
	{
		DUIASSERT(hWnd<0x00FFFFFF && id>=0);
		bDuiTimer=1;
		hDuiWnd=hWnd;
		uTimerID=id;
	}
	CDuiTimerID(DWORD dwID)
	{
		memcpy(this,&dwID,sizeof(DWORD));
	}
	operator DWORD &() const
	{
		return *(DWORD*)this;
	}
};

#define ICWND_FIRST	((CDuiWindow*)-1)
#define ICWND_LAST	NULL

class DUI_EXP DuiDCPaint 
{
public:
	DuiDCPaint()
		: bDuiModeChanged(FALSE)
		, nOldDuiMode(OPAQUE)
		, bFontChanged(FALSE)
		, hftOld(NULL)
		, bTextColorChanged(FALSE)
		, crOld(CLR_INVALID)
		, bBgColorChanged(FALSE)
		, crOldBg(CLR_INVALID)
	{
	}
	BOOL     bDuiModeChanged;
	int      nOldDuiMode;
	BOOL     bFontChanged;
	HFONT    hftOld;
	BOOL     bTextColorChanged;
	COLORREF crOld;
	BOOL     bBgColorChanged;
	COLORREF crOldBg;
	CRect    rcClient;
};

//////////////////////////////////////////////////////////////////////////
// CDuiWindow
//////////////////////////////////////////////////////////////////////////

typedef enum tagGDUI_CODE
{
	GDUI_FIRSTCHILD=0,
	GDUI_LASTCHILD,
	GDUI_PREVSIBLING,
	GDUI_NEXTSIBLING,
	GDUI_PARENT,
	GDUI_OWNER,
}GDUI_CODE;

//tolua_begin
class DUI_EXP CDuiWindow : public CDuiObject
				 , public CDuiRef
{
	//tolua_end
	DUIOBJ_DECLARE_CLASS_NAME(CDuiWindow, "duiwindow")
public:
	//tolua_begin
    CDuiWindow();

    virtual ~CDuiWindow();
//tolua_end
	virtual void OnFinalRelease();

    enum {
        // Specify by "width" attribute
        SizeX_Mask          = 0x0007UL, 
        SizeX_Specify       = 0x0001UL, // width > 0
        SizeX_FitContent    = 0x0002UL, // width <= 0
        SizeX_FitParent     = 0x0004UL, // width = "full" default

        // Specify by "height" attribute
        SizeY_Mask          = 0x0070UL, 
        SizeY_Specify       = 0x0010UL, // height > 0
        SizeY_FitContent    = 0x0020UL, // height <= 0 default
        SizeY_FitParent     = 0x0040UL, // height = "full" default

        Position_Mask       = 0x0300UL, 

        // Specify by "valign" attribute, only using at  panel control (Vert-Align)
        Align_Mask				= 0xF000UL, 
        VAlign_Top				= 0x0000UL, // valign = top
        VAlign_Middle			= 0x1000UL, // valign = middle
        VAlign_Bottom			= 0x2000UL, // valign = bottom
    };

    struct DUIDLG_POSITION_ITEM
    {
        BOOL bCenter;
        BOOL bMinus;
        int  nPos;
    };

    struct DUIDLG_POSITION
    {
        int nCount;
        union
        {
            struct
            {
                DUIDLG_POSITION_ITEM Left;
                DUIDLG_POSITION_ITEM Top;
                DUIDLG_POSITION_ITEM Right;
                DUIDLG_POSITION_ITEM Bottom;
            };
            DUIDLG_POSITION_ITEM Item[4];
        };
    };

	typedef struct tagDUIMSG
	{
		UINT uMsg;
		WPARAM wParam;
		LPARAM lParam;
	}DUIMSG,*PDUIMSG;
protected:
    HDUIWND m_hDuiWnd;
	CDuiContainer *m_pContainer;
	CDuiWindow *m_pOwner;
	CDuiWindow *m_pParent,*m_pFirstChild, *m_pLastChild, *m_pNextSibling,*m_pPrevSibling;	//窗口树结构
	int	m_nChildrenCount;
	DUIMSG		*m_pCurMsg;

    UINT m_uCmdID;
    CRect m_rcWindow;
    UINT m_uPositionType;
    DuiStyle m_style;
    CString m_strInnerText;
    LONG m_lSpecifyWidth;
    LONG m_lSpecifyHeight;
    DWORD m_dwState;
    UINT m_uVAlign;
    CString m_strLinkUrl;
    BOOL m_bMsgTransparent;		//不处理用户操作标志
	BOOL m_bVisible;
    CString m_strToolTipText;
	int	 m_nSepSpace;	//自动排版的水平空格
	BOOL m_bClipClient;

	CDuiSkinBase * m_pBgSkin;
	CDuiSkinBase * m_pNcSkin;

    DUIDLG_POSITION m_dlgpos;
	int				m_nMaxWidth;	//自动计算大小时使用
	BOOL m_bUpdateLocked;//暂时锁定更新
#ifdef _DEBUG
	DWORD m_nMainThreadId;
#endif
	ULONG_PTR m_uData; 
public:

    //////////////////////////////////////////////////////////////////////////
    // Method Define

	// Get align
    UINT GetAlign();	//tolua_export
    // Get position type
    DWORD GetPositionType();//tolua_export

    // Set position type
    void SetPositionType(DWORD dwPosType, DWORD dwMask = 0xFFFFFFFF);//tolua_export

	void SetFixSize(int nWid,int nHei);//tolua_export
	void SetBkColor(COLORREF cr);//tolua_export

    // Get DuiWindow rect(position in container)
    void GetRect(LPRECT prect);//tolua_export

	virtual void GetClient(LPRECT pRect);//tolua_export

    void GetDlgPosition(DUIDLG_POSITION *pPos);
    // Get inner text
    LPCTSTR GetInnerText();//tolua_export


    // Set inner text
    HRESULT SetInnerText(LPCTSTR lpszText);//tolua_export

	VOID TestMainThread();

    // Send a message to DuiWindow
    LRESULT DuiSendMessage(UINT Msg, WPARAM wParam = 0, LPARAM lParam = 0,BOOL *pbMsgHandled=NULL);//tolua_export

	PDUIMSG GetCurDuiMsg(){return m_pCurMsg;}

    // Move DuiWindow to new place
    void Move(LPRECT prect);//tolua_export

	void Move(int x,int y, int cx=-1,int cy=-1);//tolua_export

	void ReCalcWndPos();

    // Set current cursor, when hover
    virtual BOOL OnDuiSetCursor(const CPoint &pt);

	// Get tooltip Info
	virtual BOOL OnUpdateToolTip(HDUIWND hCurTipHost,HDUIWND &hNewTipHost,CRect &rcTip,CString &strTip);

    // Get DuiWindow state
    DWORD GetState(void);//tolua_export

    // Modify DuiWindow state
    DWORD ModifyState(DWORD dwStateAdd, DWORD dwStateRemove,BOOL bUpdate=FALSE);//tolua_export

    // Get Command ID
    UINT GetCmdID();//tolua_export
	void SetCmdID(UINT uNewID);//tolua_export
	ULONG_PTR GetCmdData();//tolua_export

	ULONG_PTR SetCmdData(ULONG_PTR uData);//tolua_export

	//************************************
	// Method:    SetDuiTimer
	// Function:  利用窗口定时器来设置一个ID为0-127的DUI定时器
	// Access:    public 
	// Returns:   BOOL
	// Parameter: char id
	// Parameter: UINT uElapse
	// remark: 
	//************************************
	BOOL SetDuiTimer(char id,UINT uElapse);

	//************************************
	// Method:    KillDuiTimer
	// Function:  删除一个DUI定时器
	// Access:    public 
	// Returns:   void
	// Parameter: char id
	// remark: 
	//************************************
	void KillDuiTimer(char id);

	//************************************
	// Method:    SetDuiTimerEx
	// Function:  利用函数定时器来模拟一个兼容窗口定时器
	// Access:    public 
	// Returns:   BOOL
	// Parameter: UINT_PTR id
	// Parameter: UINT uElapse
	// remark: 能够使用SetDuiTimer时尽量不用SetDuiTimerEx，在Kill时效率会比较低
	//************************************
	BOOL SetDuiTimerEx(UINT_PTR id,UINT uElapse);

	//************************************
	// Method:    KillDuiTimerEx
	// Function:  删除一个SetDuiTimerEx设置的定时器
	// Access:    public 
	// Returns:   void
	// Parameter: UINT_PTR id
	// remark: 需要枚举定时器列表
	//************************************
	void KillDuiTimerEx(UINT_PTR id);

    HDUIWND GetDuiHwnd();//tolua_export


	CDuiWindow *GetParent();//tolua_export

    void SetParent(CDuiWindow *pParent);//tolua_export

	CDuiWindow *GetTopLevelParent();

	BOOL DestroyChild(CDuiWindow *pChild);//tolua_export

	int GetChildrenCount();//tolua_export

	CDuiWindow * GetChild(UINT uCmdID);//tolua_export

	virtual void SetChildContainer(CDuiWindow *pChild);//tolua_export

	void InsertChild(CDuiWindow *pNewChild,CDuiWindow *pInsertAfter=ICWND_LAST);//tolua_export

	BOOL RemoveChild(CDuiWindow *pChild);//tolua_export

    BOOL IsChecked();//tolua_export

    BOOL IsDisabled(BOOL bCheckParent = FALSE);//tolua_export

    BOOL IsVisible(BOOL bCheckParent = FALSE);//tolua_export
    void SetVisible(BOOL bVisible,BOOL bUpdate=FALSE);//tolua_export

	void EnableWindow( BOOL bEnable);//tolua_export

	void SetCheck(BOOL bCheck);//tolua_export

    BOOL NeedRedrawParent();

    LPCTSTR GetLinkUrl();//tolua_export

	CDuiContainer *GetContainer();

	void SetContainer(CDuiContainer *pContainer);

	void SetOwner(CDuiWindow *pOwner);//tolua_export

	CDuiWindow *GetOwner();//tolua_export

	BOOL IsMsgTransparent();

	DuiStyle& GetStyle();

	CDuiWindow* FindChildByCmdID(UINT uCmdID);//tolua_export


	// 从XML创建子窗口
	// std::string utf8Xml: utf8 编码的XML串
	// return : 顶层的最后一个窗口
	CDuiWindow *LoadXmlChildren(std::string utf8Xml);//tolua_export


	void NotifyInvalidate();//tolua_export
	void NotifyInvalidateRect(LPRECT lprect);//tolua_export
	void NotifyInvalidateRect(const CRect& rect);//tolua_export
	void LockUpdate();
	void UnlockUpdate();
	BOOL IsUpdateLocked();
	void BringWindowToTop();//tolua_export

public:
    //////////////////////////////////////////////////////////////////////////
    // Virtual functions
	virtual void OnStateChanged(DWORD dwOldState,DWORD dwNewState){}

	virtual BOOL LoadChildren(TiXmlElement* pTiXmlChildElem);
	// Create DuiWindow from xml element
	virtual BOOL Load(TiXmlElement* pTiXmlElem);//tolua_export

	virtual HDUIWND DuiGetHWNDFromPoint(CPoint ptHitTest, BOOL bOnlyText);//tolua_export

	virtual LRESULT DuiNotify(LPNMHDR pnms);//tolua_export

	virtual UINT OnGetDuiCode();

	virtual BOOL IsTabStop();

	virtual BOOL OnDuiNcHitTest(CPoint pt);

	virtual BOOL RedrawRegion(CDCHandle& dc, CRgn& rgn);
	
	virtual BOOL IsClipClient(){return m_bClipClient;}

	virtual void OnAttributeChanged(CStringA strAttrName,BOOL bLoading,HRESULT hRet);
public:

 	//************************************
 	// Method:    GetDuiDC
 	// Function:  获取一个与DUI窗口相适应的内存DC
 	// Access:    public 
 	// Returns:   HDC
 	// Parameter: LPRECT pRc - DC范围
 	// Parameter: DWORD gdcFlags 同OLEDCFLAGS
 	// remark: 使用ReleaseDuiDC释放
 	//************************************
 	HDC GetDuiDC(const LPRECT pRc=NULL,DWORD gdcFlags=0);
	

	//************************************
	// Method:    ReleaseDuiDC
	// Function:  释放由GetDuiDC获取的DC
	// Access:    public 
	// Returns:   void
	// Parameter: HDC hdc
	// remark: 
	//************************************
	void ReleaseDuiDC(HDC hdc);

	//************************************
	// Method:    PaintBackground
	// Function:  画窗口的背景内容
	// Access:    public 
	// Returns:   void
	// Parameter: HDC hdc 目标DC
	// Parameter: LPRECT pRc 目标位置
	// remark:	目标位置必须在窗口位置内
	//************************************
	void PaintBackground(HDC hdc,LPRECT pRc);

	//************************************
	// Method:    PaintForeground
	// Function:  画窗口的前景内容
	// Access:    public 
	// Returns:   void
	// Parameter: HDC hdc 目标DC
	// Parameter: LPRECT pRc 目标位置
	// remark:	目标位置必须在窗口位置内
	//************************************
	void PaintForeground(HDC hdc,LPRECT pRc);

protected:
	CRect		m_rcGetDC;
	DWORD		m_gdcFlags;

public:
	HDUIWND GetDuiCapture();
	HDUIWND SetDuiCapture();

	BOOL ReleaseDuiCapture();
	void SetDuiFocus();

	CDuiWindow *GetCheckedRadioButton();//tolua_export

	void CheckRadioButton(CDuiWindow * pRadioBox);//tolua_export

	BOOL SetItemVisible(UINT uItemID, BOOL bVisible);//tolua_export

	BOOL IsItemVisible(UINT uItemID, BOOL bCheckParent = FALSE);//tolua_export
	BOOL GetItemCheck(UINT uItemID);//tolua_export

	BOOL SetItemCheck(UINT uItemID, BOOL bCheck);//tolua_export
	BOOL EnableItem(UINT uItemID, BOOL bEnable);//tolua_export
	BOOL IsItemEnable(UINT uItemID, BOOL bCheckParent = FALSE);//tolua_export

	CDuiWindow *GetDuiWindow(int uCode);	//tolua_export

	//************************************
	// Method:    BeforePaint
	// Function:  为DC准备好当前窗口的绘图环境
	// Access:    public 
	// Returns:   void
	// Parameter: CDCHandle & dc
	// Parameter: DuiDCPaint & DuiDC
	// remark: 
	//************************************
	void BeforePaint(CDCHandle &dc, DuiDCPaint &DuiDC);

	//************************************
	// Method:    AfterPaint
	// Function:  恢复由BeforePaint设置的DC状态
	// Access:    public 
	// Returns:   void
	// Parameter: CDCHandle & dc
	// Parameter: DuiDCPaint & DuiDC
	// remark: 
	//************************************
	void AfterPaint(CDCHandle &dc, DuiDCPaint &DuiDC);

	//************************************
	// Method:    BeforePaintEx
	// Function:  为DC准备好当前窗口的绘图环境,从顶层窗口开始设置
	// Access:    public 
	// Returns:   int 当前的DC环境
	// Parameter: CDCHandle & dc
	// remark: 使用前使用SaveDC来保存状态，使用后调用RestoreDC来恢复状态
	//************************************
	void BeforePaintEx(CDCHandle &dc);

	BOOL IsMsgHandled() const;

	void SetMsgHandled(BOOL bHandled);

protected:
	BOOL m_bMsgHandled;

	DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
		DUIWIN_SKIN_ATTRIBUTE("skin", m_pBgSkin, TRUE)//直接获得皮肤对象
		DUIWIN_SKIN_ATTRIBUTE("ncskin", m_pNcSkin, TRUE)//直接获得皮肤对象
		DUIWIN_CUSTOM_ATTRIBUTE("name",OnAttributeName)
		DUIWIN_STYLE_ATTRIBUTE("class", m_style, TRUE)	//获得style
		DUIWIN_CHAIN_ATTRIBUTE(m_style)					//支持对style中的属性定制
		DUIWIN_INT_ATTRIBUTE("id", m_uCmdID, FALSE)
		DUIWIN_INT_ATTRIBUTE("data", m_uData, 0 )
		DUIWIN_TSTRING_ATTRIBUTE("href", m_strLinkUrl, FALSE)
		DUIWIN_TSTRING_ATTRIBUTE("tip", m_strToolTipText, FALSE)
		DUIWIN_ENUM_ATTRIBUTE("valign", UINT, TRUE)
			DUIWIN_ENUM_VALUE("top", VAlign_Top)
			DUIWIN_ENUM_VALUE("middle", VAlign_Middle)
			DUIWIN_ENUM_VALUE("bottom", VAlign_Bottom)
		DUIWIN_ENUM_END(m_uVAlign)
		DUIWIN_CUSTOM_ATTRIBUTE("pos", OnAttributePosition)
		DUIWIN_INT_ATTRIBUTE("show", m_bVisible,FALSE)
		DUIWIN_INT_ATTRIBUTE("msgtransparent", m_bMsgTransparent, FALSE)	
		DUIWIN_INT_ATTRIBUTE("sep", m_nSepSpace, FALSE)
		DUIWIN_INT_ATTRIBUTE("maxwidth",m_nMaxWidth,FALSE)
		DUIWIN_INT_ATTRIBUTE("clipclient",m_bClipClient,FALSE)
	DUIWIN_DECLARE_ATTRIBUTES_END()

protected:
	//************************************
	// Method:    _PaintBackground
	// Function:  从顶层窗口开始绘制窗口内容到指定DC，到pEnd时结束绘制。
	// Access:    protected 
	// Returns:   BOOL 返回TRUE时结束递归
	// Parameter: HDC hdc	目标DC
	// Parameter: CRect * pRc	目标位置
	// Parameter: CDuiWindow * pCurWnd 当前窗口指针
	// Parameter: CDuiWindow * pEnd		结束窗口
	// remark: 函数递归调用
	//************************************
	static BOOL _PaintBackground(HDC hdc,CRect *pRc,CDuiWindow *pCurWnd,CDuiWindow *pEnd);
	
	//************************************
	// Method:    _PaintForeground
	// Function:  从pStart指定的窗口开始绘制pRc的内容，直接窗口链结尾
	// Access:    protected static 
	// Returns:   void
	// Parameter: HDC hdc	目标DC
	// Parameter: CRect * pRc	目标位置
	// Parameter: CDuiWindow * pCurWnd 当前窗口指针
	// Parameter: CDuiWindow * pStart 开始绘制位置
	// Parameter: BOOL & bInRange	pCurWnd是否在绘制链中
	// remark:  函数递归调用
	//************************************
	static void _PaintForeground(HDC hdc,CRect *pRc,CDuiWindow *pCurWnd,CDuiWindow *pStart,BOOL &bInRange);

	virtual BOOL NeedRedrawWhenStateChange();
	virtual void DuiDrawText(HDC hdc,LPCTSTR pszBuf,int cchText,LPRECT pRect,UINT uFormat);
	virtual void DuiDrawFocus(HDC hdc);

	//////////////////////////////////////////////////////////////////////////
	// Message Handler

	//************************************
	// Method:    DuiWndProc
	// Function:  默认的消息处理函数
	// Access:    virtual public 
	// Returns:   BOOL
	// Parameter: UINT uMsg
	// Parameter: WPARAM wParam
	// Parameter: LPARAM lParam
	// Parameter: LRESULT & lResult
	// remark: 在消息映射表中没有处理的消息进入该函数处理
	//************************************
	virtual BOOL DuiWndProc(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT & lResult){ return FALSE;}

	void OnWindowPosChanged(LPDUIWNDPOS lpWndPos);

	int OnCreate(LPVOID);

	void OnDestroy();
	
	// Draw background default
	BOOL OnEraseBkgnd(CDCHandle dc);

	// Draw inner text default
	void OnPaint(CDCHandle dc);


	//************************************
	// Method:    OnNcPaint
	// Function:  draw non-client area
	// Access:    protected 
	// Returns:   void
	// Parameter: CDCHandle dc
	// remark: 
	//************************************
	void OnNcPaint(CDCHandle dc);

	virtual CRect GetViewRect();

	void OnCalcChildPos(CDuiWindow *pDuiWndChild);

	// Calc DuiWindow size
	LRESULT OnCalcSize(BOOL bCalcValidRects, LPSIZE pSize);


	BOOL OnDefKeyDown(UINT nChar, UINT nFlags);

	void OnShowWindow(BOOL bShow, UINT nStatus);

	void OnLButtonDown(UINT nFlags,CPoint pt);

	void OnLButtonUp(UINT nFlags,CPoint pt);

	void OnMouseMove(UINT nFlags,CPoint pt){}

	void OnMouseHover(WPARAM wParam, CPoint ptPos);

	void OnMouseLeave();

	BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	void OnSetDuiFocus();
	void OnKillDuiFocus();

	HRESULT OnAttributePosition(CStringA& strValue, BOOL bLoading);
	HRESULT OnAttributeName(CStringA& strValue, BOOL bLoading);
  
    DUIWIN_BEGIN_MSG_MAP()
		MSG_WM_ERASEBKGND(OnEraseBkgnd)
        MSG_WM_PAINT(OnPaint)
		MSG_WM_NCPAINT_EX(OnNcPaint)
		MSG_WM_CREATE(OnCreate)
        MSG_WM_DESTROY(OnDestroy)
        MSG_WM_DUIWINPOSCHANGED(OnWindowPosChanged)
        MSG_WM_CALCSIZE(OnCalcSize)
        MSG_WM_SHOWWINDOW(OnShowWindow)
		MSG_WM_CALCWNDPOS(OnCalcChildPos)
		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_LBUTTONUP(OnLButtonUp)
		MSG_WM_MOUSEMOVE(OnMouseMove)
		MSG_WM_MOUSEHOVER(OnMouseHover)
		MSG_WM_MOUSELEAVE(OnMouseLeave)
		MSG_WM_MOUSEWHEEL(OnMouseWheel)
		MSG_WM_SETFOCUS_EX(OnSetDuiFocus)
		MSG_WM_KILLFOCUS_EX(OnKillDuiFocus)
    DUIWIN_END_MSG_MAP_BASE()
	//tolua_begin
};
//tolua_end
}//namespace DuiEngine