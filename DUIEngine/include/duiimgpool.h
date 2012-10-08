//////////////////////////////////////////////////////////////////////////
//  Class Name: DuiImgPool
// Description: Image Pool
//     Creator: Huang Jianxiong
//     Version: 2012.8.24 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "duiimage.h"
#include "DuiSingletonMap.h"

namespace DuiEngine{

typedef CDuiImgBase * CDuiImgBasePtr;
class DUI_EXP DuiImgPool:public DuiSingletonMap<DuiImgPool,CDuiImgBasePtr,UINT>
{
public:
    DuiImgPool();
    virtual ~DuiImgPool();

    CDuiImgBase * GetImage(UINT uResID);

	//增加一个图片文件到图片库中
	//LPCTSTR pszFileName:图片文件名
	//return:图片的ID,图片加载失败返回-1
	UINT AddImage(LPCWSTR pszFileName,BOOL bBmp);

protected:
	static void OnKeyRemoved(const CDuiImgBasePtr & obj)
	{
		delete obj;
	}

    ULONG_PTR m_gdiplusToken;

	UINT		 m_uAutoID;
};

}//namespace DuiEngine