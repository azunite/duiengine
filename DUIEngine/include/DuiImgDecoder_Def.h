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

    virtual CDuiImgBase* CreateDuiImage(LPCTSTR pszType);
    virtual void DestoryDuiImage(CDuiImgBase* pImg);
    virtual LPCTSTR GetSupportTypes()
    {
        return _T("BMP\0IMGX\0");
    }
};

}//end of namespace DuiEngine