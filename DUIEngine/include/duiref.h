#pragma once

namespace DuiEngine
{

class DUI_EXP CDuiRef
{
public:
    CDuiRef():m_nRef(1)
    {
    }

    ~CDuiRef()
    {

    }

    int AddRef()
    {
        return ++m_nRef;
    }

    void Release()
    {
        --m_nRef;
        if(m_nRef==0)
        {
            OnFinalRelease();
        }
    }

protected:
    virtual void OnFinalRelease()=NULL;

    int m_nRef;
};

}//namespace DuiEngine