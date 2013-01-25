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
 

namespace DuiEngine
{

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

    virtual BOOL IsClass(LPCSTR lpszName)
    {
        return FALSE;
    }
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

    virtual HRESULT SetAttribute(const CDuiStringA &  strAttribName, const CDuiStringA &  strValue, BOOL bLoading)
    {
        return DefAttributeProc(strAttribName,strValue,bLoading);
    }

    virtual HRESULT SetAttributeW(const CDuiStringA &  strAttribName, const CDuiStringW &  strValue, BOOL bLoading)
    {
        CDuiStringA strValueUTF8=DUI_CW2A(strValue,CP_UTF8);
        return SetAttribute(strAttribName,strValueUTF8,bLoading);
    }

    virtual HRESULT DefAttributeProc(const CDuiStringA & strAttribName,const CDuiStringA & strValue, BOOL bLoading)
    {
        return E_FAIL;
    }
    //tolua_end
protected:
    virtual void OnAttributeFinish(TiXmlElement* pXmlElem) {}
    virtual void OnAttributeChanged(const CDuiStringA & strAttrName,BOOL bLoading,HRESULT hRet) {}
    //************************************
    // Method:    LoadTemplateAttribute
    // Function:  从类属性模板载入属性
    // Access:    protected
    // Returns:   void
    // Parameter: CDuiStringA strTemplate
    // remark: 使用属性baseClass来支持嵌套
    //************************************
    void LoadTemplateAttribute(CDuiStringA strTemplate)
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
    CDuiStringA m_strXml;
#endif//_DEBUG
    //tolua_begin
};
//tolua_end

}//namespace DuiEngine
