//////////////////////////////////////////////////////////////////////////
//   File Name: bkstringpool.h
// Description: String Pool
//     Creator: Zhang Xiaoxuan
//     Version: 2009.5.13 - 1.0 - Create
//				2012.8.28 - 2.0 huang jianxiogn
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "DuiSingletonMap.h"

namespace DuiEngine{

class DUI_EXP DuiString :public DuiSingletonMap<DuiString,CString,UINT>
{
public:
	BOOL BuildString(CString &strContainer);
    BOOL Init(UINT uResID);
	CString Get(UINT uID);
};

}//namespace DuiEngine