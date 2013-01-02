#pragma once
#include "DUISingleton.h"
namespace DuiEngine{

template<class TClass,class TObj,class TKey=CStringA>
class DUI_EXP DuiSingletonMap :public Singleton<TClass>
{
public:
	DuiSingletonMap(void (*funOnKeyRemoved)(const TObj &)=NULL):m_pFunOnKeyRemoved(funOnKeyRemoved)
	{
		m_mapNamedObj=new STL_NS::map<TKey,TObj>;
	}
	virtual ~DuiSingletonMap(){
		RemoveAll();
		delete m_mapNamedObj;
	}

	bool HasKey(const TKey & key)
	{
		return m_mapNamedObj->find(key)!=m_mapNamedObj->end();
	}
	bool GetKeyObject(const TKey & key,TObj & obj)
	{
		if(!HasKey(key)) return false;
		obj=(*m_mapNamedObj)[key];
		return true;
	}
	TObj & GetKeyObject(const TKey & key)
	{
		return (*m_mapNamedObj)[key];
	}
	bool AddKeyObject(const TKey & key,const TObj & obj)
	{
		if(HasKey(key)) return false;
		(*m_mapNamedObj)[key]=obj;
		return true;
	}
	void SetKeyObject(const TKey & key,const TObj & obj)
	{
		(*m_mapNamedObj)[key]=obj;
	}
	bool RemoveKeyObject(const TKey & key)
	{
		if(!HasKey(key)) return false;
		if(m_pFunOnKeyRemoved)
		{
			m_pFunOnKeyRemoved((*m_mapNamedObj)[key]);
		}
		m_mapNamedObj->erase(key);
		return true;
	}
	void RemoveAll()
	{
		if(m_pFunOnKeyRemoved)
		{
			STL_NS::map<TKey,TObj>::iterator it=m_mapNamedObj->begin();
			while(it!=m_mapNamedObj->end())
			{
				m_pFunOnKeyRemoved(it->second);
				it++;
			}
		}
		m_mapNamedObj->clear();
	}
	size_t GetCount()
	{
		return m_mapNamedObj->size();
	}
protected:
	void (*m_pFunOnKeyRemoved)(const TObj &obj);

	STL_NS::map<TKey,TObj> *m_mapNamedObj;
};



}//namespace DuiEngine