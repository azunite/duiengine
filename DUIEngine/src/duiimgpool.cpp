//////////////////////////////////////////////////////////////////////////
//  Class Name: DuiImgPool
// Description: Image Pool
//     Creator: Huang jianxiong
//     Version: 2012.8.30 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "duistd.h"
#include "duiobject.h"
#include "duiimgpool.h"
#include "duiresprovider.h"

namespace DuiEngine{

#define IDC_AUTOID_START		65535	//自动编号的起始ID，方便在程序中动态增加图片到图片库中

template<> DuiImgPool * Singleton<DuiImgPool>::ms_Singleton =0;

DuiImgPool::DuiImgPool()
{
	CDuiImgX::InitGdiplus();
	m_pFunOnKeyRemoved=OnKeyRemoved;
	m_uAutoID=IDC_AUTOID_START;
}

DuiImgPool::~DuiImgPool()
{
	RemoveAll();//需要先清理图片，再释放gdi+，否则基类释放内存时会出错。
	CDuiImgX::UninitGdiplus();
}

CDuiImgBase * DuiImgPool::GetImage(UINT uResID)
{
	if(HasKey(uResID)) 
	{
		return GetKeyObject(uResID);
	}else
	{
		CDuiImgBase *pImg=new CDuiImgX;
		pImg->LoadImg(uResID,DUIRES_IMGX_TYPE);
		if(pImg->IsEmpty())
		{
			delete pImg;
			pImg=new CDuiBitmap;
			pImg->LoadImg(uResID,DUIRES_BMP_TYPE);
			if(pImg->IsEmpty())
			{
				delete pImg;
				return NULL;
			}
		}
		AddKeyObject(uResID,pImg);
		return pImg;
	}
}

//增加一个图片文件到图片库中
//LPCTSTR pszFileName:图片文件名
//return:图片的ID,图片加载失败返回-1
UINT DuiImgPool::AddImage(LPCWSTR pszFileName,BOOL bBmp)
{
	CDuiImgBase *pImg=NULL;
	if(bBmp)
	{
		pImg=new CDuiBitmap;
	}else
	{
		pImg=new CDuiImgX;
	}
	pImg->LoadImg(pszFileName);
	if(pImg->IsEmpty())
	{
		delete pImg;
		return -1;
	}
	AddKeyObject(m_uAutoID,pImg);
	return m_uAutoID++;
}

}//namespace DuiEngine