#pragma once
#include "DuiSingletonMap.h"
#include "DuiSkinBase.h"

namespace DuiEngine{

	class CSkinFactory
	{
	public:
		virtual ~CSkinFactory(){}
		virtual CDuiSkinBase * NewSkin()=NULL;
		virtual void DeleteSkin(CDuiSkinBase *)=NULL;
		virtual const CStringA & GetTypeName()=NULL;
	};

	template<typename T>
	class TplSkinFactory :public CSkinFactory
	{
	public:
		TplSkinFactory()
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

		virtual const CStringA & GetTypeName(){return m_strTypeName;}
	protected:
		CStringA m_strTypeName;
	};

	typedef CSkinFactory * CSkinFactoryPtr;
	class DUI_EXP DuiSkinFactoryManager: public DuiSingletonMap<DuiSkinFactoryManager,CSkinFactoryPtr,CStringA>
	{
	public:
		DuiSkinFactoryManager()
		{
			m_pFunOnKeyRemoved=OnKeyRemoved;
			AddStandardSkin();
		}

		bool RegisterFactory(CSkinFactory *pSkinFactory)
		{
			if(HasKey(pSkinFactory->GetTypeName())) return false;
			AddKeyObject(pSkinFactory->GetTypeName(),pSkinFactory);
			return true;
		}

		bool UnregisterFactory(CSkinFactory *pSkinFactory)
		{
			if(!HasKey(pSkinFactory->GetTypeName())) return false;
			m_mapNamedObj->erase(pSkinFactory->GetTypeName());
			return true;
		}

	protected:
		static void OnKeyRemoved(const CSkinFactoryPtr & obj)
		{
			delete obj;
		}
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

		CDuiSkinBase* GetSkin(CStringA strSkinName);

		int LoadSkins(CStringA  pszOwnerName);

		int FreeSkins(CStringA  pszOwnerName);


	protected:
		static void OnKeyRemoved(const DuiSkinPtr & obj);

		BOOL _InitSkins(TiXmlElement *pXmlSkinRootElem);

		TiXmlElement * m_pXmlSkinDesc;
	};

}//namespace DuiEngine