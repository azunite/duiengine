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
	pugi::xml_document xmlDoc;
	if(!DuiSystem::getSingleton().LoadXmlDocment(xmlDoc,uResID)) return FALSE;
	return Init(xmlDoc.first_child());
}

BOOL DuiStringPool::Init( pugi::xml_node xmlNode )
{
	if (strcmp(xmlNode.name(), "string") != 0)
	{
		DUIASSERT(FALSE);
		return FALSE;
	}
	LPCSTR lpszStringID = NULL;
	UINT uStringID = 0;

	for (pugi::xml_node xmlStr=xmlNode.child("s"); xmlStr; xmlStr=xmlStr.next_sibling("s"))
	{
		uStringID=xmlStr.attribute("id").as_int(-1);
		if(uStringID==-1) continue;
		CDuiStringA str=xmlStr.text().get();
		if(str.IsEmpty()) str=xmlStr.attribute("text").value();
		AddKeyObject(uStringID,CDuiStringT(DUI_CA2T(str, CP_UTF8)));
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