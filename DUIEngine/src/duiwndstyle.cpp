//////////////////////////////////////////////////////////////////////////
//   File Name: DuiWndStyle.h
// Description: DuiWindow Styles Definition
//     Creator: Zhang Xiaoxuan
//     Version: 2009.04.28 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#include "duistd.h"
#include "duiwndstyle.h"

namespace DuiEngine{

DuiStyle::DuiStyle()
: m_uAlign(0)
, m_nTextAlign(DT_VCENTER | DT_SINGLELINE)
, m_crBg(CLR_INVALID)
, m_crBgHover(CLR_INVALID)
, m_crText(CLR_INVALID)
, m_crHoverText(CLR_INVALID)
, m_crDisabledText(RGB(0xA0, 0xA0, 0xA0))
, m_crPushText(CLR_INVALID)
, m_ftText(NULL)
, m_ftHover(NULL)
, m_ftPush(NULL)
, m_nMarginX(0)
, m_nMarginY(0)
, m_nSpacing(0)
, m_nLineSpacing(20)
, m_lpCursorName(IDC_ARROW)
, m_bDotted(FALSE)
{
}

// Get class name
LPCSTR DuiStyle::GetName()
{
	return m_strClassName;
}


//////////////////////////////////////////////////////////////////////////
//DUI style pool
//////////////////////////////////////////////////////////////////////////
template<> DuiStylePool * Singleton<DuiStylePool>::ms_Singleton =0;


// Get style object from pool by class name
BOOL DuiStylePool::GetStyle(LPCSTR lpszName, DuiStyle& style)
{
	if(!getSingleton().HasKey(lpszName)) return FALSE;
	style=getSingleton().GetKeyObject(lpszName);
	return TRUE;
}

BOOL DuiStylePool::Init(UINT uResID)
{
	CMyBuffer<char> strXml;
	BOOL bRet = DuiResManager::getSingleton().LoadResource(uResID, strXml);

	if (!bRet)
		return FALSE;

	return Init(strXml);
}

BOOL DuiStylePool::Init(LPCSTR lpszXml)
{
	TiXmlDocument xmlDoc;

	xmlDoc.Parse(lpszXml, NULL, TIXML_ENCODING_UTF8);

	if (xmlDoc.Error())
		return FALSE;

	getSingleton()._LoadStylePool(xmlDoc.RootElement());

	return TRUE;
}

// Load style-pool from xml tree
void DuiStylePool::_LoadStylePool(TiXmlElement *pXmlStyleRootElem)
{
	RemoveAll();

	LPCSTR lpszClassName = NULL;

	if (!pXmlStyleRootElem)
		return;

	if (strcmp(pXmlStyleRootElem->Value(), "style") != 0)
		return;

	for (TiXmlElement* pXmlChild = pXmlStyleRootElem->FirstChildElement("class"); NULL != pXmlChild; pXmlChild = pXmlChild->NextSiblingElement("class"))
	{
		lpszClassName = pXmlChild->Attribute("name");
		if (!lpszClassName)
			continue;

		GetKeyObject(lpszClassName).Load(pXmlChild);
	}
}

}//namespace DuiEngine