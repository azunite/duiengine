#pragma once

#include "../image3d/3dTransform.h"
using namespace IMAGE3D;

namespace DuiEngine
{

class CDui3DPreview :
	public CDuiWindow
{
	DUIOBJ_DECLARE_CLASS_NAME(CDui3DPreview, "image3dprev")
public:
	CDui3DPreview(void);
	~CDui3DPreview(void);

	PARAM3DTRANSFORM & Get3dParam(){return m_3dparam;}

	void Update();

	DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
		DUIWIN_SKIN_ATTRIBUTE("image", m_pImage,TRUE)
		DUIWIN_INT_ATTRIBUTE("rotate-x", m_3dparam.nRotateX,TRUE)
		DUIWIN_INT_ATTRIBUTE("rotate-y", m_3dparam.nRotateY,TRUE)
		DUIWIN_INT_ATTRIBUTE("rotate-z", m_3dparam.nRotateZ,TRUE)
		DUIWIN_INT_ATTRIBUTE("offset-z", m_3dparam.nOffsetZ,TRUE)
	DUIWIN_DECLARE_ATTRIBUTES_END()
protected:
	void OnSize(UINT nType, CSize size);
	void OnPaint(CDCHandle dc);
	int OnCreate(LPVOID);

	DUIWIN_BEGIN_MSG_MAP()
		MSG_WM_SIZE(OnSize)
		MSG_WM_PAINT(OnPaint)
		MSG_WM_CREATE(OnCreate)
	DUIWIN_END_MSG_MAP()

	CDuiSkinBase *m_pImage;
	HBITMAP			m_hBmpOrig;
	HBITMAP			m_hBmpTrans;

	PARAM3DTRANSFORM	m_3dparam;
};

}