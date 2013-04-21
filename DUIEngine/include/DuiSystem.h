#pragma once
#include "duisingleton.h"

#include "DuiThreadActiveWndManager.h"

#include "duiresprovider.h"
#include "DuiCSS.h"
#include "duistringpool.h"
#include "duifontpool.h"
#include "duiskin.h"
#include "duiwndstyle.h"
#include "duiimgpool.h"
#include "DuiWindowManager.h"
#include "DuiWndFactoryManager.h"
#include "DuiLogger.h"
#include "DuiMessageBox.h"
#include "DuiScriptModule.h"

namespace DuiEngine
{

#define DUI_MAX_NAME	30	//控件名字的最大长度

class DUI_EXP DuiSystem :
    public Singleton<DuiSystem>
{
	friend class CSimpleWnd;
	friend class CDuiMessageBox;
    class CNamedID
    {
    public:
        CNamedID() {}
        CNamedID(LPCSTR name,UINT id)
        {
            DUIASSERT(strlen(name)<=DUI_MAX_NAME);
            strcpy_s(strName,DUI_MAX_NAME,name);
            uID=id;
        }

        static int Compare( __in const void * id1, __in const void * id2 )
        {
            CNamedID *pid1=(CNamedID*)id1;
            CNamedID *pid2=(CNamedID*)id2;
            return strcmp(pid1->strName,pid2->strName);
        }

        char 		strName[DUI_MAX_NAME+1];
        UINT		uID;
    };

public:
    DuiSystem(HINSTANCE hInst,LPCTSTR pszHostClassName=_T("DuiHostWnd"));
    ~DuiSystem(void);


    HINSTANCE GetInstance()
    {
        return m_hInst;
    }

    DuiResProviderBase * SetResProvider(DuiResProviderBase *pNewResProvider)
    {
        DuiResProviderBase *pRet=m_pResProvider;
        m_pResProvider=pNewResProvider;
        return pRet;
    }
    DuiResProviderBase * GetResProvider()
    {
        return m_pResProvider;
    }

    DuiLogger *SetLogger(DuiLogger *pLogger)
    {
        DuiLogger *pRet=m_pLogger;
        m_pLogger=pLogger;
        return pRet;
    }
    DuiLogger * GetLogger()
    {
        return m_pLogger;
    }

	IScriptModule * GetScriptModule()
	{
		return m_pScriptModule;
	}

	IScriptModule * SetScriptModule(IScriptModule *pScriptModule)
	{
		IScriptModule *pRet=m_pScriptModule;
		m_pScriptModule=pScriptModule;
		return pRet;
	}

    void logEvent(LPCTSTR message, LoggingLevel level = Standard);

    void logEvent(LoggingLevel level , LPCTSTR format, ...);

    UINT Name2ID(LPCSTR strName);

    size_t InitName2ID(UINT uXmlResID ,LPCSTR pszType=DUIRES_XML_TYPE);

	BOOL Init(UINT uXmlResID ,LPCSTR pszType=DUIRES_XML_TYPE);

	BOOL LoadXmlDocment(TiXmlDocument *pXmlDoc,UINT uXmlResID ,LPCSTR pszType=DUIRES_XML_TYPE);

	BOOL SetMsgBoxTemplate(UINT uXmlResID,LPCSTR pszType=DUIRES_XML_TYPE);
protected:
	TiXmlElement * GetMsgBoxTemplate(){return m_pTiXmlMsgBoxTempl;}
	void LockSharePtr( void * pObj );
	void * GetSharePtr();
	void * ReleaseSharePtr();

	ATOM GetHostWndAtom()
	{
		return m_atomWnd;
	}

	HANDLE GetExecutableHeap()
	{
		return m_hHeapExecutable;
	}

    void createSingletons();
    void destroySingletons();
    void * m_p;
    HANDLE m_hHeapExecutable;

    CRITICAL_SECTION m_cs;

    ATOM			m_atomWnd;

    DuiResProviderBase	* m_pResProvider;
	IScriptModule		* m_pScriptModule;
    DuiLogger * m_pLogger;
    HINSTANCE m_hInst;

    //name-id map
    CNamedID *m_pBuf;
    int		  m_nCount;

	TiXmlElement *m_pTiXmlMsgBoxTempl;
};

}//namespace DuiEngine