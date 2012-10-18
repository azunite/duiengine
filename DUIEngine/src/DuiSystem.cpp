#include "duistd.h"
#include "DuiSystem.h"
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
		ATLASSERT(m_pBuf);
		delete []m_pBuf;
		m_pBuf=NULL;
		m_nCount=0;
	}

	CResPE resPE;
	resPE.hInst=DuiSystem::getSingleton().GetInstance();
	resPE.uID=uXmlResID;
	resPE.strType=pszType;

	CMyBuffer<char> strXml;
	if(resPE.GetResBuffer(strXml))
	{
		TiXmlDocument xmlDoc;
		xmlDoc.Parse(strXml);
		if(!xmlDoc.Error())
		{
			TiXmlElement *pItem=xmlDoc.RootElement();
			while(pItem)
			{
				ATLASSERT(strcmp(pItem->Value(),"name2id")==0);
				pItem=pItem->NextSiblingElement();
				m_nCount++;
			}
			m_pBuf=new CNamedID[m_nCount];

			pItem=xmlDoc.RootElement();
			int iItem=0;
			while(pItem)
			{
				ATLASSERT(strcmp(pItem->Value(),"name2id")==0);
				m_pBuf[iItem++]=CNamedID(pItem->Attribute("name"),atoi(pItem->Attribute("id")));
				pItem=pItem->NextSiblingElement();
			}
			qsort(m_pBuf,m_nCount,sizeof(CNamedID),CNamedID::Compare);
		}
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

	new DuiString();
	new DuiCSS();
	new DuiFontPool();
 	new DuiStylePool();
	new DuiImgPool();

}

void DuiSystem::destroySingletons()
{
	delete DuiFontPool::getSingletonPtr();
 	delete DuiStylePool::getSingletonPtr();
	delete DuiString::getSingletonPtr();

	delete CDuiTimerEx::getSingletonPtr();
	delete DuiWindowManager::getSingletonPtr();
	delete DuiWindowFactoryManager::getSingletonPtr();

	delete DuiSkinPool::getSingletonPtr();
	delete DuiSkinFactoryManager::getSingletonPtr();
	delete DuiCSS::getSingletonPtr();
	delete DuiImgPool::getSingletonPtr();

	delete DuiThreadActiveWndManager::getSingletonPtr();
}

BOOL DuiSystem::GetResBuf( UINT uID,LPCSTR pszType,CMyBuffer<char> &buf )
{
	if(!m_pResProvider) return FALSE;
	CResBase *pRes=m_pResProvider->GetRes(pszType,uID);
	if(!pRes) return FALSE;
	BOOL bRet=FALSE;
	if(pRes->GetResMode()==RES_PE)
	{
		CResPE *pResPE=static_cast<CResPE*>(pRes);
		bRet=pResPE->GetResBuffer(buf);
	}else if(pRes->GetResMode()==RES_FILE)
	{
		CResFile *pResFile=static_cast<CResFile*>(pRes);
		FILE *f=fopen(pResFile->strFilePath,"rb");
		if(f)
		{
			int len=_filelength(_fileno(f));
			buf.Allocate(len);
			bRet=(len==fread(buf,1,len,f));
			fclose(f);
		}
	}else if(pRes->GetResMode()==RES_MEM)
	{
		CResMem *pResMem=static_cast<CResMem*>(pRes);
		buf.Attach(pResMem->resBuf,pResMem->resBuf.size());
		bRet=TRUE;
	}
	return bRet;
}

void DuiSystem::logEvent( const CStringA & message, LoggingLevel level /*= Standard*/ )
{
	if(m_pLogger) m_pLogger->logEvent(message,level);
}

void DuiSystem::logEvent(LoggingLevel level , LPCSTR pszFormat, ...)
{
	if(!m_pLogger) return;
	char szBuffer[1025] = { 0 };
	va_list argList;
	va_start(argList, pszFormat);
	::wvsprintfA((char*)szBuffer, pszFormat, argList);
	va_end(argList);
	m_pLogger->logEvent(szBuffer,level);
}

}//namespace DuiEngine