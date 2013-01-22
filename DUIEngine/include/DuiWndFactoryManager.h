#pragma once
#include "duisingletonmap.h"
#include "duiwnd.h"

namespace DuiEngine
{

class CDuiWindowFactory
{
public:
    virtual ~CDuiWindowFactory() {}
    virtual CDuiWindow* NewWindow() = 0;

    virtual void DeleteWindow(CDuiWindow* pWnd) = 0;

    virtual const CDuiStringA & getWindowType()=0;

	virtual	BOOL IsSysWindow()=0;
};

template <typename T>
class TplDuiWindowFactory : public CDuiWindowFactory
{
public:
    //! Default constructor.
	TplDuiWindowFactory(BOOL bSysCtrl=FALSE):m_bSysCtrl(bSysCtrl)
    {
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

    virtual const CDuiStringA & getWindowType()
    {
        return m_strTypeName;
    }

	virtual BOOL IsSysWindow() {return m_bSysCtrl;}
protected:
    CDuiStringA m_strTypeName;
	BOOL	m_bSysCtrl;
};



typedef CDuiWindowFactory* CDuiWindowFactoryPtr;
class DUI_EXP DuiWindowFactoryManager :
    public DuiSingletonMap<DuiWindowFactoryManager,CDuiWindowFactoryPtr,CDuiStringA>
{
public:
    DuiWindowFactoryManager(void);

    //************************************
    // Method:    RegisterFactory,注册APP自定义的窗口类
    // FullName:  DuiEngine::DuiWindowFactoryManager::RegisterFactory
    // Access:    public
    // Returns:   bool
    // Qualifier:
    // Parameter: CDuiWindowFactory * pWndFactory:窗口工厂指针
	// Parameter: bool bReplace:强制替换原有工厂标志
    //************************************
    bool RegisterFactory(CDuiWindowFactory *pWndFactory,bool bReplace=false)
    {
        if(HasKey(pWndFactory->getWindowType()))
		{
			if(!bReplace) return false;
			RemoveKeyObject(pWndFactory->getWindowType());
		}
        AddKeyObject(pWndFactory->getWindowType(),pWndFactory);
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
        m_mapNamedObj->RemoveKey(pWndFactory->getWindowType());
        return true;
    }

	CDuiWindow *CreateWindowByName(LPCSTR pszClassName);
protected:
    static void OnWndFactoryRemoved(const CDuiWindowFactoryPtr & obj);

    void AddStandardWindowFactory();
};

}//namespace DuiEngine