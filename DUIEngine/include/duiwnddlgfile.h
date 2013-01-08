#pragma once

#include "duiwndpanel.h"
#include "DuiSystem.h"
#include "mybuffer.h"

namespace DuiEngine
{

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

        DuiResProviderBase *pRes=DuiSystem::getSingleton().GetResProvider();
        if(!pRes) return FALSE;

        DWORD dwSize=pRes->GetRawBufferSize(DUIRES_XML_TYPE,nChildSrc);
        if(dwSize==0) return FALSE;

        CMyBuffer<char> strXml;
        strXml.Allocate(dwSize);
        pRes->GetRawBuffer(DUIRES_XML_TYPE,nChildSrc,strXml,dwSize);

        TiXmlDocument xmlDoc;
        {
            xmlDoc.Parse(strXml, NULL, TIXML_ENCODING_UTF8);
        }
        if (xmlDoc.Error())
        {
            DUIASSERT(FALSE);
            return FALSE;
        }

        TiXmlElement *pSubTiElement = xmlDoc.RootElement();
        return LoadChildren(pSubTiElement);
    }

};

}//namespace DuiEngine