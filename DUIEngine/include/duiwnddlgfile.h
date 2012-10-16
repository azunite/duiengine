#pragma once

#include "duiwndpanel.h"

namespace DuiEngine{

/*
使用另外一个资源XML来加载子元素

<dlgfile src=16 />
*/
class DUI_EXP CDuiDialogFile : public CDuiDialog
{
    DUIOBJ_DECLARE_CLASS_NAME(CDuiDialogFile, "dlgfile")

public:

    virtual BOOL Load(TiXmlElement* pTiXmlElem)
    {
		if (!CDuiWindow::Load(pTiXmlElem))
			return FALSE;

		int			nChildSrc=-1;
		pTiXmlElem->Attribute("src",&nChildSrc);

		if (nChildSrc == -1)
			return FALSE;
		CMyBuffer<char>	strXML;
		BOOL		bRet   = DuiResManager::getSingleton().LoadResource(nChildSrc,strXML);
		if (!bRet)	return TRUE;

		TiXmlDocument xmlDoc;
		{
			xmlDoc.Parse(strXML, NULL, TIXML_ENCODING_UTF8);
		}
		if (xmlDoc.Error())
		{
			ATLASSERT(FALSE);
			return FALSE;
		}

		TiXmlElement *pSubTiElement = xmlDoc.RootElement();
        return LoadChildren(pSubTiElement);
    }

};

}//namespace DuiEngine