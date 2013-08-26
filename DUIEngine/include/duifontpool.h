//////////////////////////////////////////////////////////////////////////
//  Class Name: DUIFontPool
// Description: Font Pool
//     Creator: ZhangXiaoxuan
//     Version: 2009.4.22 - 1.0 - Change stl::map to CAtlMap
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "duisingletonmap.h"



#define DUIF_BOLD        0x0004U
#define DUIF_UNDERLINE   0x0002U
#define DUIF_ITALIC      0x0001U

#define DUIF_MAKEKEY(bold, underline, italic, adding) \
    (WORD)((adding << 8) \
    | (bold ? DUIF_BOLD : 0) \
    | (underline ? DUIF_UNDERLINE : 0) \
    | (italic ? DUIF_ITALIC : 0))

#define DUIF_ISBOLD(key)         ((key & DUIF_BOLD) == DUIF_BOLD)
#define DUIF_ISUNDERLINE(key)    ((key & DUIF_UNDERLINE) == DUIF_UNDERLINE)
#define DUIF_ISITALIC(key)       ((key & DUIF_ITALIC) == DUIF_ITALIC)
#define DUIF_GETADDING(key)      (key >> 8)

#define DUIF_DEFAULTFONT         (DUIF_MAKEKEY(FALSE, FALSE, FALSE, 0))
#define DUIF_BOLDFONT            (DUIF_MAKEKEY(TRUE, FALSE, FALSE, 0))

#define DUIF_GetFont(key)        DuiFontPool::GetFont(key)

namespace DuiEngine
{
	class FontKey
	{
	public:
		FontKey(DWORD dwStyle,CString strFaceName=_T(""))
		{
			this->strFaceName=strFaceName;
			this->dwStyle=dwStyle;
		}

		ULONG Hash() const
		{
			ULONG_PTR uRet=0;
			CString strType=strFaceName;
			strType.MakeLower();
			for(int i=0;i<strType.GetLength();i++)
			{
				uRet=uRet*68+strType[i];
			}

			return (ULONG)(uRet*10000+(UINT)dwStyle+1);
		}

		bool operator < ( const FontKey &rt) const
		{
			ULONG u1=Hash();
			ULONG u2=rt.Hash();
			return u1<u2;
		}

		CString strFaceName;
		DWORD	 dwStyle;
	};


class DUI_EXP DuiFontPool :public DuiSingletonMap<DuiFontPool,HFONT,FontKey>
{
public:
    DuiFontPool();

    HFONT GetFont(WORD uKey,CString strFaceName=_T(""));

    HFONT GetFont(BOOL bBold, BOOL bUnderline, BOOL bItalic, char chAdding = 0,CString strFaceName=_T(""));
    void SetDefaultFont(LPCTSTR lpszFaceName, LONG lSize);
protected:
	static void OnKeyRemoved(const HFONT & obj)
	{
		DeleteObject(obj);
	}

    HFONT _CreateDefaultGUIFont();
                                                                           
    HFONT _CreateNewFont(BOOL bBold, BOOL bUnderline, BOOL bItalic, char chAdding,CString strFaceName=_T(""));

    LONG _GetFontAbsHeight(LONG lSize);

	LOGFONT m_lfDefault;
	CString m_strFaceName;
	LONG m_lFontSize;
};

}//namespace DuiEngine

