#pragma once

#include "duiobject.h"
#include "duiimage.h"
#include "duiimgpool.h"

namespace DuiEngine{

	class DUI_EXP CDuiSkinBase : public CDuiObject
	{
	public:
		CDuiSkinBase():m_pDuiImg(NULL),m_strOwner("")
		{
		}

		void SetOwner(CStringA strOwner)
		{
			m_strOwner=strOwner;
		}

		CStringA GetOwner() { return m_strOwner;}

		virtual ~CDuiSkinBase()
		{
		}

		CDuiImgBase * GetImage(){return m_pDuiImg;}
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

		enum {
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

	protected:

		virtual void OnAttributeFinish(TiXmlElement* pXmlElem)
		{
			TiXmlElement *pXmlImgParam=pXmlElem->FirstChildElement("imgparam");
			if(pXmlImgParam && m_pDuiImg)
			{//加载图片文件参数，它保存在皮肤的imgparam子节点中
				m_pDuiImg->Load(pXmlImgParam);
			}
		}
		DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
			DUIWIN_IMAGE_ATTRIBUTE("src", m_pDuiImg, TRUE)
		DUIWIN_DECLARE_ATTRIBUTES_END()

		CDuiImgBase *m_pDuiImg;
		CStringA	m_strOwner;
	};



}//namespace DuiEngine
