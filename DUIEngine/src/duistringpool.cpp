//////////////////////////////////////////////////////////////////////////
//   File Name: bkstringpool.h
// Description: String Pool
//     Creator: Zhang Xiaoxuan
//     Version: 2009.5.13 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#include "duistd.h"
#include "duistringpool.h"
#include "DuiSystem.h"

namespace DuiEngine{

template<> DuiString* Singleton<DuiString>::ms_Singleton	= 0;


BOOL DuiString::BuildString(CString &strContainer)
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
		CString strNewSub=GetKeyObject((UINT)nID);
		strContainer = strContainer.Left(nSubStringStart)
			+ strNewSub
			+ strContainer.Mid(nSubStringEnd);
		nSubStringEnd+=strNewSub.GetLength()-(nSubStringEnd-nSubStringStart);
		bRet=TRUE;
	}
	return bRet;
}

BOOL DuiString::Init(UINT uResID)
{
	CMyBuffer<char> strXml;
	BOOL bRet = FALSE;

	bRet = DuiSystem::getSingleton().GetResBuf(uResID,DUIRES_XML_TYPE, strXml);
	if (!bRet)
		return FALSE;

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
		CStringA str=pXmlChild->GetText();
		if(str.IsEmpty()) str=pXmlChild->Attribute("text");
		AddKeyObject(uStringID,CString(CA2T(str, CP_UTF8)));
	}

	return TRUE;
}

CString DuiString::Get( UINT uID )
{
	CString strRet;
	if(HasKey(uID))
	{
		strRet=GetKeyObject(uID);
		BuildString(strRet);
	}
	return strRet;
}

}//namespace DuiEngine