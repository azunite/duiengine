#include "duistd.h"
#include "DuiCSS.h"
#include "DuiSystem.h"
#include "mybuffer.h"

namespace DuiEngine
{

template<> DuiCSS *Singleton<DuiCSS>::ms_Singleton =0;


BOOL DuiCSS::Init(UINT uXmlID)
{
	TiXmlDocument xmlDoc;
	if(!DuiSystem::getSingleton().LoadXmlDocment(&xmlDoc,uXmlID)) return FALSE;
	return Init(xmlDoc.RootElement());
}

BOOL DuiCSS::Init( TiXmlElement *pTiXml )
{
	if (strcmp(pTiXml->Value(), "objattr") != 0)
	{
		DUIASSERT(FALSE);
		return FALSE;
	}

	m_pXmlRoot=(TiXmlElement *)pTiXml->Clone();

	TiXmlElement *pObjAttr=m_pXmlRoot->FirstChildElement();
	while(pObjAttr)
	{
		AddKeyObject(pObjAttr->Value(),pObjAttr);
		pObjAttr=pObjAttr->NextSiblingElement();
	}
	return TRUE;
}


}//namespace DuiEngine

