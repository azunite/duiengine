#pragma once

#include "DuiSingletonMap.h"

namespace DuiEngine
{

class DUI_EXP DuiCSS :public DuiSingletonMap<DuiCSS,TiXmlElement *,CDuiStringA>
{
public:
    DuiCSS():m_pXmlRoot(NULL)
    {
    }
    virtual ~DuiCSS()
    {
        if(m_pXmlRoot) delete m_pXmlRoot;
    }

    BOOL Init(UINT uXmlID);
	BOOL Init(TiXmlElement *pTiXml);
protected:
	TiXmlElement	*m_pXmlRoot;
};

}//namespace DuiEngine

