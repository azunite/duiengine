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

DuiSkinPool::DuiSkinPool():m_pXmlSkinDesc(NULL)
{
    m_pFunOnKeyRemoved=OnKeyRemoved;
}

DuiSkinPool::~DuiSkinPool()
{
    if(m_pXmlSkinDesc) delete m_pXmlSkinDesc;
}

BOOL DuiSkinPool::Init(UINT uResID)
{
	TiXmlDocument xmlDoc;
	if(!DuiSystem::getSingleton().LoadXmlDocment(&xmlDoc,uResID)) return FALSE;
	return Init(xmlDoc.RootElement());
}

BOOL DuiSkinPool::Init(TiXmlElement *pXmlSkinRootElem)
{
	if (strcmp(pXmlSkinRootElem->Value(), "skins") != 0)
	{
		DUIASSERT(FALSE);
		return FALSE;
	}
	m_pXmlSkinDesc=pXmlSkinRootElem->Clone()->ToElement();
	LoadSkins("");
	return TRUE;
}

int DuiSkinPool::LoadSkins(LPCSTR strOwnerName)
{
    int nLoaded=0;
    CDuiStringA strSkinName, strTypeName;

    TiXmlElement *pXmlSkin=m_pXmlSkinDesc->FirstChildElement();
    while(pXmlSkin)
    {
        CDuiStringA strOwner= pXmlSkin->Attribute("owner");
        if(strOwner==strOwnerName)
        {
            strSkinName = pXmlSkin->Attribute("name");
            strTypeName = pXmlSkin->Value();

            if (strSkinName.IsEmpty() || strTypeName.IsEmpty())
                continue;

            DUIASSERT(!HasKey(strSkinName));
			CDuiSkinBase *pSkin=DuiSkinFactoryManager::getSingleton().CreateSkinByName(strTypeName);
            if(pSkin)
            {
                pSkin->Load(pXmlSkin);
                pSkin->SetOwner(strOwnerName);
                AddKeyObject(strSkinName,pSkin);
                nLoaded++;
            }
            else
            {
                DUIRES_ASSERTA(FALSE,"load skin error,type=%s,name=%s",strTypeName,strSkinName);
            }
        }
        pXmlSkin=pXmlSkin->NextSiblingElement();
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
    if(!HasKey(strSkinName)) return NULL;
    return GetKeyObject(strSkinName);
}

void DuiSkinPool::OnKeyRemoved(const DuiSkinPtr & obj )
{
    CSkinFactory *pFactory=DuiSkinFactoryManager::getSingleton().GetKeyObject(obj->GetObjectClass());
    pFactory->DeleteSkin(obj);
}
}//namespace DuiEngine