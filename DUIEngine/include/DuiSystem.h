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

namespace DuiEngine{

class DUI_EXP DuiSystem :
	public Singleton<DuiSystem>
{
	class CNamedID
	{
	public:
		CNamedID(){}
		CNamedID(CStringA name,UINT id):strName(name),uID(id)
		{

		}

		static int Compare( __in const void * id1, __in const void * id2 )
		{
			CNamedID *pid1=(CNamedID*)id1;
			CNamedID *pid2=(CNamedID*)id2;
			return strcmp(pid1->strName,pid2->strName);
		}

		CStringA	strName;
		UINT		uID;
	};

public:
	DuiSystem(HINSTANCE hInst,LPCTSTR pszHostClassName=_T("DuiHostWnd"));
	~DuiSystem(void);

	void LockSharePtr( void * pObj );
	void * GetSharePtr();
	void * ReleaseSharePtr();

	HINSTANCE GetInstance(){return m_hInst;}
	ATOM GetHostWndAtom(){return m_atomWnd;}

	DuiResProviderBase * SetResProvider(DuiResProviderBase *pNewResProvider)
	{
		DuiResProviderBase *pRet=m_pResProvider;
		m_pResProvider=pNewResProvider;
		return pRet;
	}
	DuiResProviderBase * GetResProvider(){return m_pResProvider;}

	BOOL GetResBuf(UINT uID,LPCSTR pszType,CMyBuffer<char> &buf);

	Logger *SetLogger(Logger *pLogger)
	{
		Logger *pRet=m_pLogger;
		m_pLogger=pLogger;
		return pRet;
	}
	Logger * GetLogger() {return m_pLogger;}

	void logEvent(const CStringA & message, LoggingLevel level = Standard);

	void logEvent(LoggingLevel level , LPCSTR format, ...);

	UINT Name2ID(CStringA strName);

	size_t InitName2ID(UINT uXmlResID ,LPCSTR pszType=DUIRES_XML_TYPE);

protected:
	void createSingletons();
	void destroySingletons();
	void * m_p;
	CRITICAL_SECTION m_cs;

	ATOM			m_atomWnd;

	DuiResProviderBase	* m_pResProvider;
	Logger * m_pLogger;
	HINSTANCE m_hInst;

	//name-id map
	CNamedID *m_pBuf;
	int		  m_nCount;

};

}//namespace DuiEngine