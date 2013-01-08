#include "duistd.h"
#include "DuiSystem.h"
#include "mybuffer.h"
#include "SimpleWnd.h"
#include <search.h>


namespace DuiEngine{

	template<> DuiSystem* Singleton<DuiSystem>::ms_Singleton = 0;

	DuiSystem::DuiSystem(HINSTANCE hInst,LPCTSTR pszHostClassName/*=_T("DuiHostWnd")*/)
		:m_hInst(hInst)
		,m_atomWnd(0)
		,m_p(NULL)
		,m_pResProvider(NULL)
		,m_pLogger(NULL)
		,m_pBuf(NULL),m_nCount(0)
	{
		InitializeCriticalSection(&m_cs);
		m_atomWnd=CSimpleWnd::RegisterSimpleWnd(hInst,pszHostClassName);
		m_hHeapExecutable=HeapCreate(HEAP_CREATE_ENABLE_EXECUTE,0,0);
		createSingletons();
	}

	DuiSystem::~DuiSystem(void)
	{
		destroySingletons();

		UnregisterClass((LPCTSTR)m_atomWnd,m_hInst);
		DeleteCriticalSection(&m_cs);

		//name id map
		if(m_pBuf && m_nCount) delete []m_pBuf;
		m_nCount=0;
		m_pBuf=NULL;
		HeapDestroy(m_hHeapExecutable);
	}

	void DuiSystem::LockSharePtr( void * pObj )
	{
		EnterCriticalSection(&m_cs);
		m_p=pObj;
	}

	void * DuiSystem::GetSharePtr()
	{
		return m_p;
	}

	void * DuiSystem::ReleaseSharePtr()
	{
		void *pRet=m_p;
		LeaveCriticalSection(&m_cs);
		return pRet;
	}


	size_t DuiSystem::InitName2ID( UINT uXmlResID ,LPCSTR pszType/*=DUIRES_XML_TYPE*/)
	{
		if(m_nCount)
		{
			DUIASSERT(m_pBuf);
			delete []m_pBuf;
			m_pBuf=NULL;
			m_nCount=0;
		}

		DuiResProviderPE resProvider(m_hInst,NULL);

		DWORD dwSize=resProvider.GetRawBufferSize(pszType,uXmlResID);
		if(dwSize==0) return 0;

		CMyBuffer<char> strXml;
		strXml.Allocate(dwSize);
		resProvider.GetRawBuffer(pszType,uXmlResID,strXml,dwSize);

		TiXmlDocument xmlDoc;
		xmlDoc.Parse(strXml);
		if(!xmlDoc.Error())
		{
			TiXmlElement *pItem=xmlDoc.RootElement();
			while(pItem)
			{
				DUIASSERT(strcmp(pItem->Value(),"name2id")==0);
				pItem=pItem->NextSiblingElement();
				m_nCount++;
			}
			m_pBuf=new CNamedID[m_nCount];

			pItem=xmlDoc.RootElement();
			int iItem=0;
			while(pItem)
			{
				DUIASSERT(strcmp(pItem->Value(),"name2id")==0);
				m_pBuf[iItem++]=CNamedID(pItem->Attribute("name"),atoi(pItem->Attribute("id")));
				pItem=pItem->NextSiblingElement();
			}
			qsort(m_pBuf,m_nCount,sizeof(CNamedID),CNamedID::Compare);
		}
		return m_nCount;
	}

	UINT DuiSystem::Name2ID( CStringA strName )
	{
		if(m_nCount==0) return 0;
		CNamedID *pFind=(CNamedID*)bsearch(&CNamedID(strName,0),m_pBuf,m_nCount,sizeof(CNamedID),CNamedID::Compare);
		if(pFind) return pFind->uID;
		else return 0;
	}

	void DuiSystem::createSingletons()
	{
		new DuiThreadActiveWndManager();
		new DuiSkinFactoryManager();
		new DuiSkinPool();
		new DuiWindowFactoryManager();
		new DuiWindowManager();
		new CDuiTimerEx();
		new DuiStringPool();
		new DuiCSS();
		new DuiFontPool();
		new DuiStylePool();
		new DuiImgPool();

	}

	void DuiSystem::destroySingletons()
	{
		delete DuiFontPool::getSingletonPtr();
		delete DuiStylePool::getSingletonPtr();
		delete DuiStringPool::getSingletonPtr();
		delete CDuiTimerEx::getSingletonPtr();
		delete DuiWindowFactoryManager::getSingletonPtr();
		delete DuiSkinPool::getSingletonPtr();
		delete DuiSkinFactoryManager::getSingletonPtr();
		delete DuiCSS::getSingletonPtr();
		delete DuiImgPool::getSingletonPtr();
		delete DuiThreadActiveWndManager::getSingletonPtr();
		delete DuiWindowManager::getSingletonPtr();
	}

	void DuiSystem::logEvent( LPCTSTR message, LoggingLevel level /*= Standard*/ )
	{
		if(m_pLogger) m_pLogger->logEvent(message,level);
	}

	void DuiSystem::logEvent(LoggingLevel level , LPCTSTR pszFormat, ...)
	{
		if(!m_pLogger) return;
		TCHAR szBuffer[1025] = { 0 };
		va_list argList;
		va_start(argList, pszFormat);
		::wvnsprintf(szBuffer,ARRAYSIZE(szBuffer)-1, pszFormat, argList);
		va_end(argList);
		m_pLogger->logEvent(szBuffer,level);
	}

}//namespace DuiEngine