#include "duistd.h"
#include "DuiCSS.h"
#include "duiresutil.h"


namespace DuiEngine
{

template<> DuiCSS *Singleton<DuiCSS>::ms_Singleton =0;


BOOL DuiCSS::Init(UINT uXmlID)
{
	CStringA strXml;
	BOOL bRet=DuiResManager::getSingleton().LoadResource(uXmlID,strXml,DUIRES_XML_TYPE);
	if(!bRet) return FALSE;
	TiXmlDocument *pXmlDoc=new TiXmlDocument;
	if(!pXmlDoc) return FALSE;
	pXmlDoc->Parse(strXml);
	if(pXmlDoc->Error())
	{
		delete pXmlDoc;
		return FALSE;
	}


	TiXmlElement *pObjAttr=pXmlDoc->RootElement();
	while(pObjAttr)
	{
		AddKeyObject(pObjAttr->Value(),pObjAttr);
		pObjAttr=pObjAttr->NextSiblingElement();
	}
	m_pXmlDoc=pXmlDoc;
	return TRUE;
}


}//namespace DuiEngine

