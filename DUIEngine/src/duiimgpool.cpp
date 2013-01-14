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
#include "DuiSystem.h"

namespace DuiEngine
{

template<> DuiImgPool * Singleton<DuiImgPool>::ms_Singleton =0;

DuiImgPool::DuiImgPool()
{
    m_pFunOnKeyRemoved=OnImageRemoved;
}

DuiImgPool::~DuiImgPool()
{
    RemoveAll();//需要先清理图片，再释放gdi+，否则基类释放内存时会出错。
}

CDuiImgBase * DuiImgPool::GetImage(UINT uResID,LPCSTR pszType)
{
    DuiResID resid(pszType,uResID);
    if(HasKey(resid))
    {
        return GetKeyObject(resid);
    }
    else
    {
        DuiResProviderBase * pResProvider=DuiSystem::getSingleton().GetResProvider();
        DUIASSERT(pResProvider);
        CDuiImgBase *pImg=NULL;
        if(pszType)
        {
            pImg=pResProvider->LoadImage(pszType,uResID);
        }
        else
        {
            //枚举所有支持的图片资源类型自动匹配
            CDuiImgDecoder *pImgDecoder=pResProvider->GetImageDecoder();
            DUIASSERT(pImgDecoder);
            LPCSTR pszTypes=pImgDecoder->GetSupportTypes();
            while(*pszTypes)
            {
                if(pResProvider->HasResource(pszTypes,uResID))
                {
                    pImg=pResProvider->LoadImage(pszTypes,uResID);
                    if(pImg) break;
                }
                pszTypes+=strlen(pszTypes)+1;
            }
        }
        if(pImg)
        {
            AddKeyObject(resid,pImg);
            if(pszType!=NULL) AddKeyObject(DuiResID(NULL,uResID),pImg);//ID唯一时保证不使用类型也能找到该图片资源
        }
        return pImg;
    }
}

}//namespace DuiEngine