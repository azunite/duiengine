//////////////////////////////////////////////////////////////////////////
//   File Name: bkstringpool.h
// Description: String Pool
//     Creator: Zhang Xiaoxuan
//     Version: 2009.5.13 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#include "duistd.h"
#include "duistringpool.h"
#include "DuiSystem.h"
#include "mybuffer.h"

namespace DuiEngine
{

template<> DuiStringPool* Singleton<DuiStringPool>::ms_Singleton	= 0;


BOOL DuiStringPool::BuildString(CDuiStringT &strContainer)
{
    BOOL bRet=FALSE;
    int nSubStringStart=-1;
    int nSubStringEnd=0;
    while ((nSubStringStart = strContainer.Find(L"%str", nSubStringEnd))!=-1)
    {
        nSubStringEnd = strContainer.Find(L'%', nSubStringStart + 4);
        if(nSubStringEnd==-1)
            break;
        nSubStringEnd++;
        int nID = ::StrToInt((LPCTSTR)strContainer + nSubStringStart + 4);
        if (0 >= nID)
            break;
        CDuiStringT strNewSub=GetKeyObject((UINT)nID);
        strContainer = strContainer.Left(nSubStringStart)
                       + strNewSub
                       + strContainer.Mid(nSubStringEnd);
        nSubStringEnd+=strNewSub.GetLength()-(nSubStringEnd-nSubStringStart);
        bRet=TRUE;
    }
    return bRet;
}

BOOL DuiStringPool::Init(UINT uResID)
{
    DuiResProviderBase *pRes=DuiSystem::getSingleton().GetResProvider();
    if(!pRes) return FALSE;

    DWORD dwSize=pRes->GetRawBufferSize(DUIRES_XML_TYPE,uResID);
    if(dwSize==0) return FALSE;

    CMyBuffer<char> strXml;
    strXml.Allocate(dwSize);
    pRes->GetRawBuffer(DUIRES_XML_TYPE,uResID,strXml,dwSize);

    TiXmlDocument xmlDoc;

    xmlDoc.Parse(strXml, NULL, TIXML_ENCODING_UTF8);

    if (xmlDoc.Error())
        return FALSE;

    LPCSTR lpszStringID = NULL;
    UINT uStringID = 0;

    TiXmlElement *pXmlStringRootElem = xmlDoc.RootElement();

    if (!pXmlStringRootElem)
        return FALSE;

    if (strcmp(pXmlStringRootElem->Value(), "string") != 0)
        return FALSE;

    for (TiXmlElement* pXmlChild = pXmlStringRootElem->FirstChildElement("s"); NULL != pXmlChild; pXmlChild = pXmlChild->NextSiblingElement("s"))
    {
        lpszStringID = pXmlChild->Attribute("id");
        if (!lpszStringID)
            continue;

        uStringID = (UINT)(ULONG)::StrToIntA(lpszStringID);
        CDuiStringA str=pXmlChild->GetText();
        if(str.IsEmpty()) str=pXmlChild->Attribute("text");
        AddKeyObject(uStringID,CDuiStringT(CA2T(str, CP_UTF8)));
    }

    return TRUE;
}

LPCTSTR DuiStringPool::Get( UINT uID )
{
    m_strTmp.Assign(NULL);
    if(HasKey(uID))
    {
        m_strTmp=GetKeyObject(uID);
        BuildString(m_strTmp);
    }
    return m_strTmp;
}

}//namespace DuiEngine