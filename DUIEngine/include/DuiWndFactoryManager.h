#pragma once
#include "duisingletonmap.h"
#include "duiwnd.h"

namespace DuiEngine{

class CDuiWindowFactory
{
public:
	virtual DuiEngine::CDuiWindow* NewWindow() = 0;

	virtual void DeleteWindow(DuiEngine::CDuiWindow* pWnd) = 0;

	virtual const CStringA & getWindowType()=0;
};

template <typename T>
class TplDuiWindowFactory : public CDuiWindowFactory
{
public:
	//! Default constructor.
	TplDuiWindowFactory(){
		m_strTypeName=T::GetClassName();
	}

	// Implement WindowFactory interface
	DuiEngine::CDuiWindow* NewWindow()
	{
		return new T;
	}
	void DeleteWindow(DuiEngine::CDuiWindow* pWnd)
	{
		delete pWnd;
	}
	virtual const CStringA & getWindowType()
	{
		return m_strTypeName;
	}

protected:
	CStringA m_strTypeName;
};



typedef CDuiWindowFactory* CDuiWindowFactoryPtr;
class DuiWindowFactoryManager :
	public DuiSingletonMap<DuiWindowFactoryManager,CDuiWindowFactoryPtr,CStringA>
{
public:
	DuiWindowFactoryManager(void);

	template <typename T>
	bool addFactory()
	{
		CDuiWindowFactory *pWndFactory= new T;
		if(HasKey(pWndFactory->GetTypeName())) return false;
		return AddKeyObject(pWndFactory->GetTypeName(),pWndFactory);
	}

	CDuiWindowFactory * removeFactory(const CStringA & strWndType)
	{
		if(!HasKey(strWndType)) return NULL;
		CDuiWindowFactory *pRet=GetKeyObject(strWndType);
		RemoveKeyObject(strWndType);
		return pRet;
	}
	

protected:
	static void OnKeyRemoved(const CDuiWindowFactoryPtr & obj)
	{
		delete obj;
	}

	void AddStandardWindowFactory();
};

}//namespace DuiEngine