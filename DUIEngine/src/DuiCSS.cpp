#include "duistd.h"
#include "DuiCSS.h"
#include "DuiSystem.h"
#include "mybuffer.h"

namespace DuiEngine
{

template<> DuiCSS *Singleton<DuiCSS>::ms_Singleton =0;


BOOL DuiCSS::Init(UINT uXmlID)
{
	pugi::xml_document xmlDoc;
	if(!DuiSystem::getSingleton().LoadXmlDocment(xmlDoc,uXmlID)) return FALSE;
	return Init(xmlDoc.child("objattr"));
}

BOOL DuiCSS::Init( pugi::xml_node xmlNode )
{
	if (strcmp(xmlNode.name(), "objattr") != 0)
	{
		DUIASSERT(FALSE);
		return FALSE;
	}

	m_xmlRoot.append_copy(xmlNode);

	pugi::xml_node xmlObjAttr=m_xmlRoot.child("objattr").first_child();
	while(xmlObjAttr)
	{
		AddKeyObject(xmlObjAttr.name(),xmlObjAttr);
		xmlObjAttr=xmlObjAttr.next_sibling();
	}
	return TRUE;
}


}//namespace DuiEngine

