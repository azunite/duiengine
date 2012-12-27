#pragma once
#include "duisingletonmap.h"
#include "duiwnd.h"

namespace DuiEngine{

class CDuiWindowFactory
{
public:
	virtual CDuiWindow* NewWindow() = 0;

	virtual void DeleteWindow(CDuiWindow* pWnd) = 0;

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
	CDuiWindow* NewWindow()
	{
		return new T;
	}

	void DeleteWindow(CDuiWindow* pWnd)
	{
		delete static_cast<T*>(pWnd);
	}

	virtual const CStringA & getWindowType()
	{
		return m_strTypeName;
	}

protected:
	CStringA m_strTypeName;
};



typedef CDuiWindowFactory* CDuiWindowFactoryPtr;
class DUI_EXP DuiWindowFactoryManager :
	public DuiSingletonMap<DuiWindowFactoryManager,CDuiWindowFactoryPtr,CStringA>
{
public:
	DuiWindowFactoryManager(void);

	//************************************
	// Method:    RegisterFactory,注册APP自定义的窗口类
	// FullName:  DuiEngine::DuiWindowFactoryManager::RegisterFactory
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Parameter: CDuiWindowFactory * pWndFactory
	//************************************
	bool RegisterFactory(CDuiWindowFactory *pWndFactory)
	{
		if(HasKey(pWndFactory->getWindowType())) return false;
		AddKeyObject(pWndFactory->getWindowType(),pWndFactory);
// 		(*m_mapNamedObj)[pWndFactory->getWindowType()]=pWndFactory;
		return true;
	}

	//************************************
	// Method:    UnregisterFactor,反注册APP自定义的窗口类
	// FullName:  DuiEngine::DuiWindowFactoryManager::UnregisterFactor
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Parameter: CDuiWindowFactory * pWndFactory
	//************************************
	bool UnregisterFactory(CDuiWindowFactory *pWndFactory)
	{
		if(!HasKey(pWndFactory->getWindowType())) return false;
		m_mapNamedObj->erase(pWndFactory->getWindowType());
		return true;
	}

protected:
	static void OnKeyRemoved(const CDuiWindowFactoryPtr & obj)
	{
		delete obj;
	}

	void AddStandardWindowFactory();
};

}//namespace DuiEngine