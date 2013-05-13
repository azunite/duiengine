#pragma once

#include "DuiSingletonMap.h"

namespace DuiEngine
{

class DUI_EXP DuiCSS :public DuiSingletonMap<DuiCSS,pugi::xml_node,CDuiStringA>
{
public:
    DuiCSS()
    {
    }
    virtual ~DuiCSS()
    {
    }

    BOOL Init(UINT uXmlID);
	BOOL Init(pugi::xml_node xmlNode);
protected:
	pugi::xml_document m_xmlRoot;
};

}//namespace DuiEngine

