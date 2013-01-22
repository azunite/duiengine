#pragma once

#include "duiobject.h"
#include "duiimgbase.h"
#include "duiimgpool.h"
#include "duiref.h"

namespace DuiEngine
{

class DUI_EXP CDuiSkinBase : public CDuiObject,public CDuiRef
{
public:
    CDuiSkinBase():m_pDuiImg(NULL),m_strOwner(""),m_bManaged(FALSE)
    {
    }
    virtual ~CDuiSkinBase()
    {
        if(m_bManaged && m_pDuiImg)
        {
            delete m_pDuiImg;
            m_pDuiImg=NULL;
        }
    }

    void OnFinalRelease()
    {
        delete this;
    }

    void SetOwner(CDuiStringA strOwner)
    {
        m_strOwner=strOwner;
    }

    CDuiStringA GetOwner()
    {
        return m_strOwner;
    }


    virtual CDuiImgBase * SetImage(CDuiImgBase *pImg)
    {
        if(m_bManaged && m_pDuiImg) delete m_pDuiImg;
        CDuiImgBase * pRet=m_pDuiImg;
        m_pDuiImg=pImg;
        m_bManaged=TRUE;
        return pRet;
    }
    CDuiImgBase * GetImage()
    {
        return m_pDuiImg;
    }

    virtual void Draw(CDCHandle dc, CRect rcDraw, DWORD dwState,BYTE byAlpha=0xFF) = NULL;

    virtual SIZE GetSkinSize()
    {
        SIZE ret = {0, 0};

        return ret;
    }

    virtual BOOL IgnoreState()
    {
        return TRUE;
    }

    virtual void SetWidth(LONG width)
    {
    }

    virtual int GetStates()
    {
        return 1;
    }

    enum
    {
        Frame_Part_All        = 0x0000002FUL,
        Frame_Part_Top        = 0x00000001UL,
        Frame_Part_Middle     = 0x00000002UL,
        Frame_Part_Bottom     = 0x00000004UL,
        Frame_Part_Left       = 0x00000008UL,
        Frame_Part_Center     = 0x00000010UL,
        Frame_Part_Right      = 0x00000020UL,
    };

    static BOOL ExtentBlt(CDuiImgBase *pImgDraw,BOOL bTile,HDC hdc,int x,int y,int nWid,int nHei,int xSrc,int ySrc,int nWidSrc,int nHeiSrc,BYTE byAlpha=0xFF);
    static void FrameDraw(CDCHandle &dc, CDuiImgBase *pImgDraw, const CRect &rcSour,const  CRect &rcDraw,const  CRect &rcMargin, COLORREF crBg, UINT uDrawPart ,BOOL bTile,BYTE byAlpha=0xFF);

    DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
    DUIWIN_IMAGE_ATTRIBUTE("src", m_pDuiImg, TRUE)
    DUIWIN_DECLARE_ATTRIBUTES_END()
protected:

    virtual void OnAttributeFinish(TiXmlElement* pXmlElem)
    {
        //加载图片文件参数，它保存在皮肤的imgparam子节点中
        TiXmlElement *pXmlImgParam=pXmlElem->FirstChildElement("imgparam");
        if(m_pDuiImg) m_pDuiImg->SetAttributes(pXmlImgParam);
    }

    CDuiImgBase *m_pDuiImg;
    CDuiStringA	m_strOwner;
    BOOL		m_bManaged;
};



}//namespace DuiEngine
