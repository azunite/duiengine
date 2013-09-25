//////////////////////////////////////////////////////////////////////////
//   File Name: DuiObject.h
// Description: DuiObject Definition
//     Creator: Zhang Xiaoxuan
//     Version: 2009.04.28 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma once

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
														\
	virtual LPCSTR BaseObjectClassName()				\
	{													\
		return __super::GetObjectClass();				\
	}													\


namespace DuiEngine
{

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

    virtual LPCSTR GetObjectClass()
	{
		return NULL;
	}

	virtual LPCSTR BaseObjectClassName()
	{
		return NULL;
	}

    virtual BOOL Load(pugi::xml_node xmlNode)
    {
        if(!xmlNode) return FALSE;
#ifdef _DEBUG
        {
			pugi::xml_writer_buff writer;
			xmlNode.print(writer);
			m_strXml=DUI_CA2A(CDuiStringA(writer.buffer(),writer.size()),CP_UTF8);
        }
#endif
        //检索并设置类的默认属性
		pugi::xml_node defAttr = DuiCSS::getSingleton().GetDefAttribute(GetObjectClass());
		if(defAttr)
		{
			for (pugi::xml_attribute attr = defAttr.first_attribute(); attr; attr = attr.next_attribute())
			{
				SetAttribute(attr.name(), attr.value(), TRUE);
			}
		}

        //设置当前对象的属性
		for (pugi::xml_attribute attr = xmlNode.first_attribute(); attr; attr = attr.next_attribute())
        {
            SetAttribute(attr.name(), attr.value(), TRUE);
        }
        OnAttributeFinish(xmlNode);
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
	virtual void OnAttributeFinish(pugi::xml_node xmlNode) {}
    virtual void OnAttributeChanged(const CDuiStringA & strAttrName,BOOL bLoading,HRESULT hRet) {}
    //************************************
    // Method:    LoadTemplateAttribute
    // Function:  从类属性模板载入属性
    // Access:    protected
    // Returns:   void
    // Parameter: CDuiStringA strTemplate
    //************************************
    void LoadDefAttribute(const CDuiStringA & strClassName)
    {
        if(!DuiCSS::getSingleton().HasKey(strClassName)) return;
        pugi::xml_node xmlNode=DuiCSS::getSingleton().GetKeyObject(strClassName);

		for (pugi::xml_attribute attr= xmlNode.first_attribute(); attr; attr = attr.next_attribute())
        {
            if(strcmp(attr.name(),"baseClass")==0) continue;//baseClass属性不需要了。huangjianxiong:2013.8.25
            SetAttribute(attr.name(), attr.value(), TRUE);
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
		COLORREF cr=RGB(
			HexStringToULong(lpszValue, 2),
			HexStringToULong(lpszValue + 2, 2),
			HexStringToULong(lpszValue + 4, 2)
			);
		if(strlen(lpszValue)>6)
		{
			cr |= HexStringToULong(lpszValue + 6, 2)<<24;
		}
		return cr;
    }

#ifdef	_DEBUG
    CDuiStringA m_strXml;
#endif//_DEBUG
    //tolua_begin
};
//tolua_end

}//namespace DuiEngine
