#include "duistd.h"
#include "DuiSkinPool.h"
#include "duiskin.h"
#include "duisystem.h"
#include "mybuffer.h"

namespace DuiEngine
{

template<> DuiSkinFactoryManager * Singleton<DuiSkinFactoryManager>::ms_Singleton=0;

void DuiSkinFactoryManager::AddStandardSkin()
{
    AddKeyObject(CDuiImageList::GetClassName(),new TplSkinFactory<CDuiImageList>);
    AddKeyObject(CDuiSkinImgFrame::GetClassName(),new TplSkinFactory<CDuiSkinImgFrame>);
    AddKeyObject(CDuiSkinButton::GetClassName(),new TplSkinFactory<CDuiSkinButton>);
    AddKeyObject(CDuiSkinGradation::GetClassName(),new TplSkinFactory<CDuiSkinGradation>);
    AddKeyObject(CDuiScrollbarSkin::GetClassName(),new TplSkinFactory<CDuiScrollbarSkin>);
    AddKeyObject(CDuiSkinMenuBorder::GetClassName(),new TplSkinFactory<CDuiSkinMenuBorder>);
}

void DuiSkinFactoryManager::OnSkinRemoved( const CSkinFactoryPtr & obj )
{
	delete obj;
}

CDuiSkinBase * DuiSkinFactoryManager::CreateSkinByName( LPCSTR pszClassName )
{
	if(!HasKey(pszClassName)) return NULL;
	return GetKeyObject(pszClassName)->NewSkin();
}

//////////////////////////////////////////////////////////////////////////
// DuiSkinPool
template<> DuiSkinPool * Singleton<DuiSkinPool>::ms_Singleton =0;

DuiSkinPool::DuiSkinPool()
{
    m_pFunOnKeyRemoved=OnKeyRemoved;
}

DuiSkinPool::~DuiSkinPool()
{
}

BOOL DuiSkinPool::Init(UINT uResID)
{
	pugi::xml_document xmlDoc;
	if(!DuiSystem::getSingleton().LoadXmlDocment(xmlDoc,uResID)) return FALSE;

	return Init(xmlDoc.child("skins"));
}

BOOL DuiSkinPool::Init(pugi::xml_node xmlNode)
{
	if (strcmp(xmlNode.name(), "skins") != 0)
	{
		DUIASSERT(FALSE);
		return FALSE;
	}

	m_xmlSkinDesc.append_copy(xmlNode);
	LoadSkins("");
	return TRUE;
}

int DuiSkinPool::LoadSkins(LPCSTR strOwnerName)
{
    int nLoaded=0;
    CDuiStringA strSkinName, strTypeName;

	pugi::xml_node xmlSkin=m_xmlSkinDesc.child("skins").first_child();
    while(xmlSkin)
    {
        CDuiStringA strOwner= xmlSkin.attribute("owner").value();
        if(strOwner==strOwnerName)
        {
			strTypeName = xmlSkin.name();
            strSkinName = xmlSkin.attribute("name").value();

            if (strSkinName.IsEmpty() || strTypeName.IsEmpty())
                continue;

            DUIASSERT(!HasKey(strSkinName));
			CDuiSkinBase *pSkin=DuiSkinFactoryManager::getSingleton().CreateSkinByName(strTypeName);
            if(pSkin)
            {
                pSkin->Load(xmlSkin);
                pSkin->SetOwner(strOwnerName);
                AddKeyObject(strSkinName,pSkin);
                nLoaded++;
            }
            else
            {
                DUIRES_ASSERTA(FALSE,"load skin error,type=%s,name=%s",strTypeName,strSkinName);
            }
        }
		xmlSkin=xmlSkin.next_sibling();
    }

    return nLoaded;
}


int DuiSkinPool::FreeSkins( LPCSTR strOwnerName )
{
    if(!strOwnerName || strlen(strOwnerName)==0) return 0;

    int nFreed=0;

    POSITION pos=m_mapNamedObj->GetStartPosition();
    while(pos)
    {
        CDuiMap<CDuiStringA,DuiSkinPtr>::CPair *p=m_mapNamedObj->GetNext(pos);
        if(p->m_value->GetOwner()==strOwnerName)
        {
            OnKeyRemoved(p->m_value);
            m_mapNamedObj->RemoveAtPos((POSITION)p);
            nFreed++;
        }
    }
    return nFreed;
}

CDuiSkinBase* DuiSkinPool::GetSkin(LPCSTR strSkinName)
{
    if(!HasKey(strSkinName))
	{
		DUIRES_ASSERTA(FALSE,"GetSkin[%s] Failed!",strSkinName);
		return NULL;
	}
    return GetKeyObject(strSkinName);
}

void DuiSkinPool::OnKeyRemoved(const DuiSkinPtr & obj )
{
	obj->Release();
}
}//namespace DuiEngine