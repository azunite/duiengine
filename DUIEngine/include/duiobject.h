//////////////////////////////////////////////////////////////////////////
//   File Name: DuiObject.h
// Description: DuiObject Definition
//     Creator: Zhang Xiaoxuan
//     Version: 2009.04.28 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma once

#if !defined(TINYXML_INCLUDED)
    #error Please include tinyxml.h first!
#endif

#include "duifontpool.h"
#include "DuiCSS.h"

//////////////////////////////////////////////////////////////////////////

// DuiObject Class Name Declaration
#define DUIOBJ_DECLARE_CLASS_NAME(theclass, classname)   \
public:                                                 \
    static BOOL CheckAndNew(LPCSTR lpszName,void **ppRet)       \
    {                                                   \
        if (strcmp(GetClassName(), lpszName)  == 0)     \
		{\
			* (theclass**)ppRet=new theclass;							\
			return TRUE;                        \
		}\
        else                                            \
            return FALSE;                                \
    }                                                   \
                                                        \
    static LPCSTR GetClassName()                        \
    {                                                   \
        return classname;                               \
    }                                                   \
                                                        \
    virtual LPCSTR GetObjectClass()                     \
    {                                                   \
        return classname;                               \
    }                                                   \
                                                        \
    virtual BOOL IsClass(LPCSTR lpszName)               \
    {                                                   \
        if(strcmp(GetClassName(), lpszName)  == 0) return TRUE;  \
		return __super::IsClass(lpszName);				\
    }                                                   \

//////////////////////////////////////////////////////////////////////////
// Xml Attributes Declaration Map

// Attribute Declaration
#define DUIWIN_DECLARE_ATTRIBUTES_BEGIN()                            \
public:                                                             \
    virtual HRESULT SetAttribute(                                   \
        const CStringA & strAttribName,                                     \
        const CStringA &  strValue,                                          \
        BOOL     bLoading=FALSE)                                    \
    {                                                               \
        HRESULT hRet = E_FAIL;										\


#define DUIWIN_DECLARE_ATTRIBUTES_END()                              \
			return __super::SetAttribute(                       \
										strAttribName,         \
										strValue,              \
										bLoading               \
										);                     \
		OnAttributeChanged(strAttribName,bLoading,hRet);		\
		return hRet;                                                \
    }                                                               \

#define DUIWIN_CHAIN_ATTRIBUTE(varname)			                   \
        if (SUCCEEDED(hRet = varname.SetAttribute(strAttribName, strValue, bLoading)))   \
        {                                                           \
            /*return hRet;*/                                            \
        }                                                           \
        else                                                        \

#define DUIWIN_CUSTOM_ATTRIBUTE(attribname, func)                    \
        if (attribname == strAttribName)                            \
        {                                                           \
            hRet = func(strValue, bLoading);                        \
        }                                                           \
        else                                                        \

// Int = %d StringA
#define DUIWIN_INT_ATTRIBUTE(attribname, varname, allredraw)         \
        if (attribname == strAttribName)                            \
        {                                                           \
			int nRet=0;												\
            ::StrToIntExA(strValue,STIF_SUPPORT_HEX,&nRet);			\
			varname=nRet;											\
            hRet = allredraw ? S_OK : S_FALSE;                      \
        }                                                           \
        else                                                        \

// Rect = %d,%d,%d,%d StringA
#define DUIWIN_RECT_ATTRIBUTE(attribname, varname, allredraw)         \
        if (attribname == strAttribName)                            \
        {                                                           \
			sscanf(strValue,"%d,%d,%d,%d",&varname.left,&varname.top,&varname.right,&varname.bottom);\
            hRet = allredraw ? S_OK : S_FALSE;                      \
        }                                                           \
        else                                                        \


// Size = %d,%d StringA
#define DUIWIN_SIZE_ATTRIBUTE(attribname, varname, allredraw)         \
		if (attribname == strAttribName)                            \
		{                                                           \
			sscanf(strValue,"%d,%d",&varname.cx,&varname.cy);\
			hRet = allredraw ? S_OK : S_FALSE;                      \
		}                                                           \
		else                                                        \

// Point = %d,%d StringA
#define DUIWIN_POINT_ATTRIBUTE(attribname, varname, allredraw)         \
		if (attribname == strAttribName)                            \
		{                                                           \
			sscanf(strValue,"%d,%d",&varname.x,&varname.y);\
			hRet = allredraw ? S_OK : S_FALSE;                      \
		}                                                           \
		else                                                        \


// Float = %f StringA
#define DUIWIN_FLOAT_ATTRIBUTE(attribname, varname, allredraw)         \
		if (attribname == strAttribName)                            \
		{                                                           \
			sscanf(strValue,"%f",&varname);                        \
			hRet = allredraw ? S_OK : S_FALSE;                      \
		}                                                           \
		else                                                        \

// UInt = %u StringA
#define DUIWIN_UINT_ATTRIBUTE(attribname, varname, allredraw)        \
        if (attribname == strAttribName)                            \
        {                                                           \
			int nRet=0;												\
            ::StrToIntExA(strValue,STIF_SUPPORT_HEX,&nRet);			\
			varname = (UINT)nRet;									\
            hRet = allredraw ? S_OK : S_FALSE;                      \
        }                                                           \
        else                                                        \

// DWORD = %u StringA
#define DUIWIN_DWORD_ATTRIBUTE(attribname, varname, allredraw)       \
        if (attribname == strAttribName)                            \
        {                                                           \
			int nRet=0;												\
			::StrToIntExA(strValue,STIF_SUPPORT_HEX,&nRet);			\
			varname = (DWORD)nRet;									\
            hRet = allredraw ? S_OK : S_FALSE;                      \
        }                                                           \
        else                                                        \

// WORD = %u StringA
#define DUIWIN_WORD_ATTRIBUTE(attribname, varname, allredraw)       \
	if (attribname == strAttribName)                            \
		{                                                           \
		int nRet=0;												\
		::StrToIntExA(strValue,STIF_SUPPORT_HEX,&nRet);			\
		varname = (WORD)nRet;									\
		hRet = allredraw ? S_OK : S_FALSE;                      \
		}                                                           \
		else                                                        \


// bool = 0 or 1 StringA
#define DUIWIN_BIT_ATTRIBUTE(attribname, varname, maskbit, allredraw) \
		if (attribname == strAttribName)                            \
		{                                                           \
			int nRet=0;												\
			::StrToInt(strValue,&nRet);								\
			if(nRet) varname|=maskbit;								\
			else	 varname &=~(maskbit);							\
			hRet = allredraw ? S_OK : S_FALSE;						\
		}                                                           \
		else                                                        \


// StringA = StringA
#define DUIWIN_STRING_ATTRIBUTE(attribname, varname, allredraw)      \
        if (attribname == strAttribName)                            \
        {                                                           \
            varname = strValue;                                     \
            hRet = allredraw ? S_OK : S_FALSE;                      \
        }                                                           \
        else                                                        \

// StringW = StringA
#define DUIWIN_WSTRING_ATTRIBUTE(attribname, varname, allredraw)      \
		if (attribname == strAttribName)                            \
		{                                                           \
			varname = CA2W(strValue, CP_UTF8);;                                     \
			hRet = allredraw ? S_OK : S_FALSE;                      \
		}                                                           \
		else                                                        \


// StringT = StringA
#define DUIWIN_TSTRING_ATTRIBUTE(attribname, varname, allredraw)     \
        if (attribname == strAttribName)                            \
        {                                                           \
            varname = CA2T(strValue, CP_UTF8);                      \
			DuiString::getSingleton().BuildString(varname);						\
            hRet = allredraw ? S_OK : S_FALSE;                      \
        }                                                           \
        else                                                        \

// DWORD = %X StringA
#define DUIWIN_HEX_ATTRIBUTE(attribname, varname, allredraw)         \
		if (attribname == strAttribName)                            \
		{                                                           \
			varname = CDuiObject::HexStringToULong(strValue);        \
			hRet = allredraw ? S_OK : S_FALSE;                      \
		}                                                           \
		else                                                        \

// COLORREF = %06X StringA
#define DUIWIN_COLOR_ATTRIBUTE(attribname, varname, allredraw)       \
        if (attribname == strAttribName)                            \
        {                                                           \
            varname = CDuiObject::HexStringToColor(strValue);        \
            hRet = allredraw ? S_OK : S_FALSE;                      \
        }                                                           \
        else                                                        \

// HFONT = %04X StringA
#define DUIWIN_FONT_ATTRIBUTE(attribname, varname, allredraw)        \
        if (attribname == strAttribName)                            \
        {                                                           \
			int nPos=strValue.ReverseFind(':');\
			if(nPos!=-1)\
			{\
				DWORD dwValue = CDuiObject::HexStringToULong(strValue,nPos);  \
				CStringA strFace=strValue.Right(strValue.GetLength()-nPos-1);\
				CString strFaceT=CA2T(strFace,CP_UTF8);\
				varname = DuiFontPool::getSingleton().GetFont(LOWORD(dwValue),strFaceT);    \
			}else\
			{\
				DWORD dwValue = CDuiObject::HexStringToULong(strValue);  \
				varname = DuiFontPool::getSingleton().GetFont(LOWORD(dwValue));         \
			}\
            hRet = allredraw ? S_OK : S_FALSE;                      \
        }                                                           \
        else                                                        \

// Value In {String1 : Value1, String2 : Value2 ...}
#define DUIWIN_ENUM_ATTRIBUTE(attribname, vartype, allredraw)        \
        if (attribname == strAttribName)                            \
        {                                                           \
            vartype varTemp;                                        \
                                                                    \
            hRet = allredraw ? S_OK : S_FALSE;                      \

#define DUIWIN_ENUM_VALUE(enumstring, enumvalue)                     \
            if (strValue == enumstring)                             \
                varTemp = enumvalue;                                \
            else                                                    \

#define DUIWIN_ENUM_END(varname)                                     \
                return E_FAIL;                                      \
                                                                    \
            varname = varTemp;                                      \
        }                                                           \
        else                                                        \

// DuiStyle From StringA Key
#define DUIWIN_STYLE_ATTRIBUTE(attribname, varname, allredraw)       \
        if (attribname == strAttribName)                            \
        {                                                           \
            DuiStylePool::GetStyle(strValue,varname);                  \
            hRet = allredraw ? S_OK : S_FALSE;                      \
        }                                                           \
        else                                                        \

// DuiSkinPool From StringA Key
#define DUIWIN_SKIN_ATTRIBUTE(attribname, varname, allredraw)        \
        if (attribname == strAttribName)                            \
        {                                                           \
            varname = DuiSkinPool::getSingleton().GetSkin(strValue);                    \
            hRet = allredraw ? S_OK : S_FALSE;                      \
        }                                                           \
        else                                                        \


#define DUIWIN_IMAGE_ATTRIBUTE(attribname, varname, allredraw)        \
	if (attribname == strAttribName)                            \
		{                                                           \
		varname = DuiImgPool::getSingleton().GetImage(StrToIntA(strValue));        \
		hRet = allredraw ? S_OK : S_FALSE;                      \
		}                                                           \
		else                                                        \


namespace DuiEngine{

//tolua_begin
class DUI_EXP CDuiObject
{
public:
    CDuiObject()
    {
    }

    virtual ~CDuiObject()
    {
    }

	virtual BOOL IsClass(LPCSTR lpszName) {return FALSE;}
    virtual LPCSTR GetObjectClass() = 0;

    virtual BOOL Load(TiXmlElement* pXmlElem)
    {
		if(!pXmlElem) return FALSE;
#ifdef _DEBUG
		{
			TiXmlPrinter printer;
			printer.SetStreamPrinting();
			pXmlElem->Accept( &printer );
			m_strXml=printer.CStr();
		}
#endif
		//检索并设置类的默认属性
		LoadTemplateAttribute(GetObjectClass());

		//设置当前对象的属性
        for (TiXmlAttribute *pAttrib = pXmlElem->FirstAttribute(); NULL != pAttrib; pAttrib = pAttrib->Next())
        {
            SetAttribute(pAttrib->Name(), pAttrib->Value(), TRUE);
        }
		OnAttributeFinish(pXmlElem);
        return TRUE;
    }

    virtual HRESULT SetAttribute(const CStringA &  strAttribName, const CStringA &  strValue, BOOL bLoading)
    {
        return DefAttributeProc(strAttribName,strValue,bLoading);
    }

	virtual HRESULT SetAttributeW(const CStringA &  strAttribName, const CStringW &  strValue, BOOL bLoading)
	{
		CStringA strValueUTF8=CW2A(strValue,CP_UTF8);
		return SetAttribute(strAttribName,strValueUTF8,bLoading);
	}

	virtual HRESULT DefAttributeProc(const CStringA & strAttribName,const CStringA & strValue, BOOL bLoading)
	{
		return E_FAIL;
	}
	//tolua_end
protected:
	virtual void OnAttributeFinish(TiXmlElement* pXmlElem){}
	virtual void OnAttributeChanged(CStringA strAttrName,BOOL bLoading,HRESULT hRet){}
	//************************************
	// Method:    LoadTemplateAttribute
	// Function:  从类属性模板载入属性
	// Access:    protected 
	// Returns:   void
	// Parameter: CStringA strTemplate
	// remark: 使用属性baseClass来支持嵌套
	//************************************
	void LoadTemplateAttribute(CStringA strTemplate)
	{
		if(!DuiCSS::getSingleton().HasKey(strTemplate)) return;
		TiXmlElement *pObjDefAttr=DuiCSS::getSingleton().GetKeyObject(strTemplate);
		const char * pszBaseCls=pObjDefAttr->Attribute("baseClass");
		if(pszBaseCls) LoadTemplateAttribute(pszBaseCls);//深度优先，防止属性重复问题

		for (TiXmlAttribute *pAttrib = pObjDefAttr->FirstAttribute(); NULL != pAttrib; pAttrib = pAttrib->Next())
		{
			if(strcmp(pAttrib->Name(),"baseClass")==0) continue;
			SetAttribute(pAttrib->Name(), pAttrib->Value(), TRUE);
		}
	}

    static ULONG HexStringToULong(LPCSTR lpszValue, int nSize = -1)
    {
        LPCSTR pchValue = lpszValue;
        ULONG ulValue = 0;
        while (*pchValue && nSize != 0)
        {
            ulValue <<= 4;

            if ('a' <= *pchValue && 'f' >= *pchValue)
                ulValue |= (*pchValue - 'a' + 10);
            else if ('A' <= *pchValue && 'F' >= *pchValue)
                ulValue |= (*pchValue - 'A' + 10);
            else if ('0' <= *pchValue && '9' >= *pchValue)
                ulValue |= (*pchValue - '0');
            else
                return 0;

            ++ pchValue;
            -- nSize;
        }

        return ulValue;
    }

    static COLORREF HexStringToColor(LPCSTR lpszValue)
    {
        return RGB(
            HexStringToULong(lpszValue, 2), 
            HexStringToULong(lpszValue + 2, 2), 
            HexStringToULong(lpszValue + 4, 2)
            );
    }

#ifdef	_DEBUG
	CStringA m_strXml;
#endif//_DEBUG
	//tolua_begin
};
//tolua_end

}//namespace DuiEngine
