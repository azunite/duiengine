#include "duistd.h"
#include "DuiSystem.h"
#include "mybuffer.h"
#include "SimpleWnd.h"
#include <search.h>


namespace DuiEngine
{

template<> DuiSystem* Singleton<DuiSystem>::ms_Singleton = 0;

DuiSystem::DuiSystem(HINSTANCE hInst,LPCTSTR pszHostClassName/*=_T("DuiHostWnd")*/)
    :m_hInst(hInst)
    ,m_pResProvider(NULL)
    ,m_pLogger(NULL)
	,m_pScriptModule(NULL)
    ,m_pBuf(NULL),m_nCount(0)
	,m_funCreateTextServices(NULL)
{
    createSingletons();
	CSimpleWndHelper::Init(hInst,pszHostClassName);
	m_rich20=LoadLibrary(_T("riched20.dll"));
	if(m_rich20) m_funCreateTextServices= (PCreateTextServices)GetProcAddress(m_rich20,"CreateTextServices");
}

DuiSystem::~DuiSystem(void)
{
    destroySingletons();
	CSimpleWndHelper::Destroy();
    //name id map
    if(m_pBuf && m_nCount) delete []m_pBuf;
    m_nCount=0;
    m_pBuf=NULL;

	if(m_rich20) FreeLibrary(m_rich20);
	m_funCreateTextServices=NULL;
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

	pugi::xml_document xmlDoc;
	if(!xmlDoc.load_buffer(strXml,strXml .size(),pugi::parse_default,pugi::encoding_utf8)) return 0;

	pugi::xml_node xmlNode=xmlDoc.first_child();
	while(xmlNode)
	{
		DUIASSERT(strcmp(xmlNode.name(),"name2id")==0);
		xmlNode=xmlNode.next_sibling();
		m_nCount++;
	}
	m_pBuf=new CNamedID[m_nCount];

	xmlNode=xmlDoc.first_child();
	int iItem=0;
	while(xmlNode)
	{
		m_pBuf[iItem++]=CNamedID(xmlNode.attribute("name").value(),xmlNode.attribute("id").as_int(0));
		xmlNode=xmlNode.next_sibling();
	}
	qsort(m_pBuf,m_nCount,sizeof(CNamedID),CNamedID::Compare);

	return m_nCount;
}

UINT DuiSystem::Name2ID( LPCSTR strName )
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

BOOL DuiSystem::Init( UINT uXmlResID ,LPCSTR pszType/*=DUIRES_XML_TYPE*/ )
{
	pugi::xml_document xmlDoc;
	if(!LoadXmlDocment(xmlDoc,uXmlResID,pszType)) return FALSE;
	//set default font
	pugi::xml_node xmlFont;
	xmlFont=xmlDoc.first_child().child("font");
	if(xmlFont)
	{
		int nSize=xmlFont.attribute("size").as_int(12);
		DuiFontPool::getSingleton().SetDefaultFont(DUI_CA2T(xmlFont.attribute("face").value()),nSize);
	}
	//load string table
	pugi::xml_node xmlStr=xmlDoc.first_child().child("string");
	if(xmlStr)
	{
		DuiStringPool::getSingleton().Init(xmlStr);
	}
	//load style table
	pugi::xml_node xmlStyle=xmlDoc.first_child().child("style");
	if(xmlStyle)
	{
		DuiStylePool::getSingleton().Init(xmlStyle);
	}
	//load skin
	pugi::xml_node xmlSkin=xmlDoc.first_child().child("skins");
	if(xmlSkin)
	{
		DuiSkinPool::getSingleton().Init(xmlSkin);
	}
	pugi::xml_node xmlObjAttr=xmlDoc.first_child().child("objattr");
	//load objattr
	if(xmlObjAttr)
	{
		DuiCSS::getSingleton().Init(xmlObjAttr);
	}
	return TRUE;
}

BOOL DuiSystem::LoadXmlDocment(pugi::xml_document & xmlDoc, UINT uXmlResID ,LPCSTR pszType/*=DUIRES_XML_TYPE*/ )
{
	DUIASSERT(GetResProvider());
	DuiResProviderBase *pRes=DuiSystem::getSingleton().GetResProvider();
	if(!pRes) return FALSE;

	DWORD dwSize=pRes->GetRawBufferSize(pszType,uXmlResID);
	if(dwSize==0) return FALSE;

	CMyBuffer<char> strXml;
	strXml.Allocate(dwSize);
	pRes->GetRawBuffer(pszType,uXmlResID,strXml,dwSize);

	pugi::xml_parse_result result= xmlDoc.load_buffer(strXml,strXml.size(),pugi::parse_default,pugi::encoding_utf8);
	DUIRES_ASSERTA(result,"parse xml error! resid=%d,desc=%s,offset=%d",uXmlResID,result.description(),result.offset);
	return result;
}

BOOL DuiSystem::SetMsgBoxTemplate( UINT uXmlResID,LPCSTR pszType/*=DUIRES_XML_TYPE*/ )
{
	if(!LoadXmlDocment(m_xmlMsgBoxTempl,uXmlResID,pszType)) goto format_error;
	if(!m_xmlMsgBoxTempl.child("layer").attribute("frame_size").value()[0]) goto format_error;
	if(!m_xmlMsgBoxTempl.child("layer").attribute("minsize").value()[0]) goto format_error;

	return TRUE;
format_error:
	m_xmlMsgBoxTempl.reset();
	return FALSE;
}

HRESULT DuiSystem::CreateTextServices( IUnknown *punkOuter, ITextHost *pITextHost, IUnknown **ppUnk )
{
	if(!m_funCreateTextServices) return E_NOTIMPL;
	return m_funCreateTextServices(punkOuter,pITextHost,ppUnk);
}
}//namespace DuiEngine