//////////////////////////////////////////////////////////////////////////
//   File Name: DuiName2ID.h
// Description: Dui Name to ID definition
//     Creator: Huang Jianxiong
//     Version: 2012.01.26 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "DUISingleton.h"

namespace DuiEngine{

class DUI_EXP DuiName2ID : public Singleton<DuiName2ID>
{
	class CNamedID
	{
	public:
		CNamedID(CStringA name,UINT id):strName(name),uID(id)
		{

		}

		static int Compare( __in const void * id1, __in const void * id2 )
		{
			CNamedID *pid1=(CNamedID*)id1;
			CNamedID *pid2=(CNamedID*)id2;
			return pid1->strName.Compare(pid2->strName);
		}

		CStringA	strName;
		UINT		uID;
	};
public:
	DuiName2ID(){}
	~DuiName2ID(){}

	UINT Name2ID(CStringA strName);

    size_t Init(UINT uXmlResID);
	
protected:
	
	CSimpleArray<CNamedID>	m_mapName2ID;

};

}//namespace DuiEngine