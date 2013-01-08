#pragma once

#include "DuiImgBase.h"
#include "duiimage.h"

namespace DuiEngine
{

class DUI_EXP CDuiImgDecoder_Def
    :public CDuiImgDecoder
{
public:
    CDuiImgDecoder_Def(void);
    ~CDuiImgDecoder_Def(void);

    virtual CDuiImgBase* CreateDuiImage(LPCSTR pszType);
    virtual void DestoryDuiImage(CDuiImgBase* pImg);
    virtual LPCSTR GetSupportTypes()
    {
        return "BMP\0IMGX\0";
    }
};

}//end of namespace DuiEngine