#include "duistd.h"
#include "duiname2id.h"
#include "duiresutil.h"
#include <search.h>

namespace DuiEngine{

template<> DuiName2ID* Singleton<DuiName2ID>::ms_Singleton=0;

size_t DuiName2ID::Init( UINT uXmlResID )
{
	size_t nRet=0;
	CStringA strXml;
 	if(DuiResManager::getSingleton().LoadResource(uXmlResID,strXml))
	{
		TiXmlDocument xmlDoc;
		xmlDoc.Parse(strXml);
		if(!xmlDoc.Error())
		{
			TiXmlElement *pItem=xmlDoc.RootElement();
			while(pItem)
			{
				ATLASSERT(strcmp(pItem->Value(),"name2id")==0);
				m_mapName2ID.Add(CNamedID(pItem->Attribute("name"),atoi(pItem->Attribute("id"))));
				pItem=pItem->NextSiblingElement();
			}
			nRet=m_mapName2ID.GetSize();
			qsort(m_mapName2ID.GetData(),nRet,sizeof(CNamedID),CNamedID::Compare);
		}
	}
	return nRet;
}

UINT DuiName2ID::Name2ID( CStringA strName )
{
	CNamedID *pFind=(CNamedID*)bsearch(&CNamedID(strName,0),m_mapName2ID.GetData(),m_mapName2ID.GetSize(),sizeof(CNamedID),CNamedID::Compare);
	if(pFind) return pFind->uID;
	else return 0;
}

}//namespace DuiEngine