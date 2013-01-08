#include "duistd.h"
#include "DuiCSS.h"
#include "DuiSystem.h"
#include "mybuffer.h"

namespace DuiEngine
{

template<> DuiCSS *Singleton<DuiCSS>::ms_Singleton =0;


BOOL DuiCSS::Init(UINT uXmlID)
{
    DuiResProviderBase *pRes=DuiSystem::getSingleton().GetResProvider();
    if(!pRes) return FALSE;
    DWORD dwSize=pRes->GetRawBufferSize(DUIRES_XML_TYPE,uXmlID);
    if(dwSize==0) return FALSE;

    CMyBuffer<char> strXml;
    strXml.Allocate(dwSize);
    pRes->GetRawBuffer(DUIRES_XML_TYPE,uXmlID,strXml,dwSize);

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

