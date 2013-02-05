//////////////////////////////////////////////////////////////////////////
//   File Name: DuiWndStyle.h
// Description: DuiWindow Styles Definition
//     Creator: Zhang Xiaoxuan
//     Version: 2009.04.28 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#include "duistd.h"
#include "duiwndstyle.h"
#include "DuiSystem.h"
#include "mybuffer.h"

namespace DuiEngine
{

DuiStyle::DuiStyle()
    : m_uAlign(Align_Left)
	, m_uVAlign(VAlign_Middle)
    , m_nTextAlign(0)
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

UINT DuiStyle::GetTextAlign()
{
	if(m_nTextAlign) return m_nTextAlign;
	UINT uRet=0;
	switch(m_uAlign)
	{
	case Align_Center: uRet |= DT_CENTER;break;
	case Align_Right: uRet|= DT_RIGHT;break;
	}
	switch(m_uVAlign)
	{
	case VAlign_Middle:uRet |= DT_VCENTER|DT_SINGLELINE;break;
	case VAlign_Bottom:uRet|= DT_BOTTOM|DT_SINGLELINE;break;
	}
	if(m_bDotted) uRet|=DT_END_ELLIPSIS;
	return uRet;
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
	TiXmlDocument xmlDoc;
	if(!DuiSystem::getSingleton().LoadXmlDocment(&xmlDoc,uResID)) return FALSE;
	return Init(xmlDoc.RootElement());
}

// Load style-pool from xml tree
BOOL DuiStylePool::Init(TiXmlElement *pXmlStyleRootElem)
{
	DUIASSERT(pXmlStyleRootElem);

    if (strcmp(pXmlStyleRootElem->Value(), "style") != 0)
	{
		DUIASSERT(FALSE);
		return FALSE;
	}

	LPCSTR lpszClassName = NULL;

    for (TiXmlElement* pXmlChild = pXmlStyleRootElem->FirstChildElement("class"); NULL != pXmlChild; pXmlChild = pXmlChild->NextSiblingElement("class"))
    {
        lpszClassName = pXmlChild->Attribute("name");
        if (!lpszClassName)
            continue;

        GetKeyObject(lpszClassName).Load(pXmlChild);
    }
	return TRUE;
}

}//namespace DuiEngine