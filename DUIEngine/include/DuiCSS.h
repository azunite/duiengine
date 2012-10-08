#pragma once

#include "DuiSingletonMap.h"

namespace DuiEngine
{

class DUI_EXP DuiCSS :public DuiSingletonMap<DuiCSS,TiXmlElement *,CStringA>
{
public:
	DuiCSS():m_pXmlDoc(NULL)
	{
	}
	virtual ~DuiCSS()
	{
		if(m_pXmlDoc) delete m_pXmlDoc;
	}

	BOOL Init(UINT uXmlID);
protected:
	TiXmlDocument	*m_pXmlDoc;
};

}//namespace DuiEngine

