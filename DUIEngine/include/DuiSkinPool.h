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
    virtual void DeleteSkin(CDuiSkinBase *)=NULL;
    virtual const CStringA & GetTypeName()=NULL;
	virtual BOOL IsSysSkin()=NULL;
};

template<typename T>
class TplSkinFactory :public CSkinFactory
{
public:
	TplSkinFactory(BOOL bSysSkin=FALSE):m_bSysSkin(bSysSkin)
    {
        m_strTypeName=T::GetClassName();
    }

    virtual CDuiSkinBase * NewSkin()
    {
        return new T;
    }

    virtual void DeleteSkin(CDuiSkinBase * pSkin)
    {
        delete static_cast<T*>(pSkin);
    }

    virtual const CStringA & GetTypeName()
    {
        return m_strTypeName;
    }

	virtual BOOL IsSysSkin(){return m_bSysSkin;}

protected:
    CStringA m_strTypeName;
	BOOL	m_bSysSkin;
};

typedef CSkinFactory * CSkinFactoryPtr;
class DUI_EXP DuiSkinFactoryManager: public DuiSingletonMap<DuiSkinFactoryManager,CSkinFactoryPtr,CStringA>
{
public:
    DuiSkinFactoryManager()
    {
        m_pFunOnKeyRemoved=OnSkinRemoved;
        AddStandardSkin();
    }

    bool RegisterFactory(CSkinFactory *pSkinFactory,bool bReplace=false)
    {
        if(HasKey(pSkinFactory->GetTypeName()))
		{
			if(!bReplace) return false;
			RemoveKeyObject(pSkinFactory->GetTypeName());
		}
        AddKeyObject(pSkinFactory->GetTypeName(),pSkinFactory);
        return true;
    }

    bool UnregisterFactory(CSkinFactory *pSkinFactory)
    {
        if(!HasKey(pSkinFactory->GetTypeName())) return false;
        m_mapNamedObj->RemoveKey(pSkinFactory->GetTypeName());
        return true;
    }

	CDuiSkinBase * CreateSkinByName(LPCSTR pszClassName);

protected:
    static void OnSkinRemoved(const CSkinFactoryPtr & obj);
    void AddStandardSkin();
};

typedef CDuiSkinBase * DuiSkinPtr;
class DUI_EXP DuiSkinPool :public DuiSingletonMap<DuiSkinPool,DuiSkinPtr,CStringA>
{
public:
    DuiSkinPool();

    virtual ~DuiSkinPool();

    BOOL Init(UINT uResID);

    BOOL Init(LPCSTR lpszXml);

    CDuiSkinBase* GetSkin(LPCSTR strSkinName);

    int LoadSkins(LPCSTR  pszOwnerName);

    int FreeSkins(LPCSTR  pszOwnerName);


protected:
    static void OnKeyRemoved(const DuiSkinPtr & obj);

    BOOL _InitSkins(TiXmlElement *pXmlSkinRootElem);

    TiXmlElement * m_pXmlSkinDesc;
};

}//namespace DuiEngine