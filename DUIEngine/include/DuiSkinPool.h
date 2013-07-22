#pragma once
#include "DuiSingletonMap.h"
#include "DuiSkinBase.h"

namespace DuiEngine
{

class CSkinFactory
{
public:
    virtual ~CSkinFactory() {}
    virtual CDuiSkinBase * NewSkin()=NULL;
    virtual const CDuiStringA & GetTypeName()=NULL;
	virtual CSkinFactory * Clone()=NULL;
};

template<typename T>
class TplSkinFactory :public CSkinFactory
{
public:
	TplSkinFactory():m_strTypeName(T::GetClassName())
    {
    }

    virtual CDuiSkinBase * NewSkin()
    {
        return new T;
    }

    virtual const CDuiStringA & GetTypeName()
    {
        return m_strTypeName;
    }

	virtual CSkinFactory * Clone()
	{
		return new TplSkinFactory<T>;
	}
protected:
    CDuiStringA m_strTypeName;
};

typedef CSkinFactory * CSkinFactoryPtr;
class DUI_EXP DuiSkinFactoryManager: public DuiSingletonMap<DuiSkinFactoryManager,CSkinFactoryPtr,CDuiStringA>
{
public:
    DuiSkinFactoryManager()
    {
        m_pFunOnKeyRemoved=OnSkinRemoved;
        AddStandardSkin();
    }

    bool RegisterFactory(CSkinFactory &skinFactory,bool bReplace=false)
    {
        if(HasKey(skinFactory.GetTypeName()))
		{
			if(!bReplace) return false;
			RemoveKeyObject(skinFactory.GetTypeName());
		}
        AddKeyObject(skinFactory.GetTypeName(),skinFactory.Clone());
        return true;
    }

    bool UnregisterFactory(const CDuiStringA & strClassName)
    {
		return RemoveKeyObject(strClassName);
    }

	CDuiSkinBase * CreateSkinByName(LPCSTR pszClassName);

protected:
    static void OnSkinRemoved(const CSkinFactoryPtr & obj);
    void AddStandardSkin();
};

typedef CDuiSkinBase * DuiSkinPtr;
class DUI_EXP DuiSkinPool :public DuiSingletonMap<DuiSkinPool,DuiSkinPtr,CDuiStringA>
{
public:
    DuiSkinPool();

    virtual ~DuiSkinPool();

    BOOL Init(UINT uResID);

	BOOL Init(pugi::xml_node xmlNode);

    CDuiSkinBase* GetSkin(LPCSTR strSkinName);

    int LoadSkins(LPCSTR  pszOwnerName);

    int FreeSkins(LPCSTR  pszOwnerName);
protected:
    static void OnKeyRemoved(const DuiSkinPtr & obj);

	pugi::xml_document m_xmlSkinDesc;
};

}//namespace DuiEngine