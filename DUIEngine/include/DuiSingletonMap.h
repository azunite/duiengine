#pragma once
#include "DUISingleton.h"

namespace DuiEngine{

template<class TClass,class TObj,class TKey=CStringA>
class DUI_EXP DuiSingletonMap :public Singleton<TClass>
{
public:
	DuiSingletonMap(void (*funOnKeyRemoved)(const TObj &)=NULL):m_pFunOnKeyRemoved(funOnKeyRemoved){}
	virtual ~DuiSingletonMap(){ RemoveAll();}

	bool HasKey(const TKey & key);
	bool GetKeyObject(const TKey & key,TObj & obj);
	TObj & GetKeyObject(const TKey & key);
	bool AddKeyObject(const TKey & key,const TObj & obj);
	void SetKeyObject(const TKey & key,const TObj & obj);
	bool RemoveKeyObject(const TKey & key);
	void RemoveAll();
	size_t GetCount();
protected:
	void (*m_pFunOnKeyRemoved)(const TObj &obj);

	CAtlMap<TKey,TObj> m_mapNamedObj;

};

template<class TClass,class TObj,class TKey>
void DuiSingletonMap<TClass, TObj, TKey>::SetKeyObject( const TKey & key,const TObj & obj )
{
	m_mapNamedObj[key]=obj;
}

template<class TClass,class TObj,class TKey>
TObj & DuiSingletonMap<TClass,TObj,TKey>::GetKeyObject( const TKey & key )
{
	return m_mapNamedObj[key];
}

template<class TClass,class TObj,class TKey>
size_t DuiSingletonMap<TClass,TObj,TKey>::GetCount()
{
	return m_mapNamedObj.GetCount();
}

template<class TClass,class TObj,class TKey>
bool DuiSingletonMap<TClass,TObj,TKey>::GetKeyObject( const TKey & key,TObj & obj )
{
	if(!HasKey(key)) return false;
	obj=m_mapNamedObj[key];
	return true;
}
 
template<class TClass,class TObj,class TKey>
 bool DuiSingletonMap<TClass,TObj,TKey>::HasKey(const TKey & key)
 {
 	return m_mapNamedObj.Lookup(key)!=NULL;
 }
 
 template<class TClass,class TObj,class TKey>
 bool DuiSingletonMap<TClass,TObj,TKey>::AddKeyObject(const TKey & key,const TObj & obj)
 {
 	if(HasKey(key)) return false;
 	m_mapNamedObj[key]=obj;
 	return true;
 }
 
 template<class TClass,class TObj,class TKey>
 bool DuiSingletonMap<TClass,TObj,TKey>::RemoveKeyObject(const TKey & key)
 {
	if(!HasKey(key)) return false;
	if(m_pFunOnKeyRemoved)
	{
		m_pFunOnKeyRemoved(m_mapNamedObj[key]);
	}
 	return m_mapNamedObj.RemoveKey(key);
 }


 template<class TClass,class TObj,class TKey>
 void DuiSingletonMap<TClass,TObj,TKey>::RemoveAll()
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

}//namespace DuiEngine