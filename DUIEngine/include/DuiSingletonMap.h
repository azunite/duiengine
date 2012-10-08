#pragma once
#include "DUISingleton.h"

namespace DuiEngine{

template<class TClass,class TObj,class TKey=CStringA>
class DUI_EXP DuiSingletonMap :public Singleton<TClass>
{
public:
	DuiSingletonMap(void (*funOnKeyRemoved)(const TObj &)=NULL):m_pFunOnKeyRemoved(funOnKeyRemoved){}
	virtual ~DuiSingletonMap(){ RemoveAll();}

	bool HasKey(const TKey & key)
	{
		return m_mapNamedObj.Lookup(key)!=NULL;
	}
	bool GetKeyObject(const TKey & key,TObj & obj)
	{
		if(!HasKey(key)) return false;
		obj=m_mapNamedObj[key];
		return true;
	}
	TObj & GetKeyObject(const TKey & key)
	{
		return m_mapNamedObj[key];
	}
	bool AddKeyObject(const TKey & key,const TObj & obj)
	{
		if(HasKey(key)) return false;
		m_mapNamedObj[key]=obj;
		return true;
	}
	void SetKeyObject(const TKey & key,const TObj & obj)
	{
		m_mapNamedObj[key]=obj;
	}
	bool RemoveKeyObject(const TKey & key)
	{
		if(!HasKey(key)) return false;
		if(m_pFunOnKeyRemoved)
		{
			m_pFunOnKeyRemoved(m_mapNamedObj[key]);
		}
		return m_mapNamedObj.RemoveKey(key);
	}
	void RemoveAll()
	{
		if(m_pFunOnKeyRemoved)
		{
			POSITION pos=m_mapNamedObj.GetStartPosition();
			while(pos)
		 {
			 CAtlMap<TKey,TObj>::CPair * pPair=m_mapNamedObj.GetNext(pos);
			 m_pFunOnKeyRemoved(pPair->m_value);
		 }
		}
		m_mapNamedObj.RemoveAll();
	}
	size_t GetCount()
	{
		return m_mapNamedObj.GetCount();
	}
protected:
	void (*m_pFunOnKeyRemoved)(const TObj &obj);

	CAtlMap<TKey,TObj> m_mapNamedObj;

};



}//namespace DuiEngine