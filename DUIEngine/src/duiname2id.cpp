#include "duistd.h"
#include "duiname2id.h"
#include "DuiSystem.h"
#include <search.h>

namespace DuiEngine
{

template<> DuiName2ID* Singleton<DuiName2ID>::ms_Singleton=0;

size_t DuiName2ID::Init( UINT uXmlResID ,LPCSTR pszType/*=DUIRES_XML_TYPE*/)
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

UINT DuiName2ID::Name2ID( CStringA strName )
{
    if(m_nCount==0) return 0;
    CNamedID *pFind=(CNamedID*)bsearch(&CNamedID(strName,0),m_pBuf,m_nCount,sizeof(CNamedID),CNamedID::Compare);
    if(pFind) return pFind->uID;
    else return 0;
}

}//namespace DuiEngine