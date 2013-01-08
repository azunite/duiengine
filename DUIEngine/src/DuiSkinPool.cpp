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
    AddKeyObject(CDuiImageList::GetClassName(),new TplSkinFactory<CDuiImageList>());
    AddKeyObject(CDuiSkinImgFrame::GetClassName(),new TplSkinFactory<CDuiSkinImgFrame>());
    AddKeyObject(CDuiSkinButton::GetClassName(),new TplSkinFactory<CDuiSkinButton>());
    AddKeyObject(CDuiSkinGradation::GetClassName(),new TplSkinFactory<CDuiSkinGradation>());
    AddKeyObject(CDuiScrollbarSkin::GetClassName(),new TplSkinFactory<CDuiScrollbarSkin>());
    AddKeyObject(CDuiSkinMenuBorder::GetClassName(),new TplSkinFactory<CDuiSkinMenuBorder>());
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
    DuiResProviderBase *pRes=DuiSystem::getSingleton().GetResProvider();
    if(!pRes) return FALSE;

    DWORD dwSize=pRes->GetRawBufferSize(DUIRES_XML_TYPE,uResID);
    if(dwSize==0) return FALSE;

    CMyBuffer<char> strXml;
    strXml.Allocate(dwSize);
    pRes->GetRawBuffer(DUIRES_XML_TYPE,uResID,strXml,dwSize);

    return Init(strXml);
}

BOOL DuiSkinPool::Init(LPCSTR lpszXml)
{
    TiXmlDocument xmlDoc;

    xmlDoc.Parse(lpszXml, NULL, TIXML_ENCODING_UTF8);

    if (xmlDoc.Error())
        return FALSE;

    return _InitSkins(xmlDoc.RootElement());
}

int DuiSkinPool::LoadSkins(LPCSTR strOwnerName)
{
    int nLoaded=0;
    CStringA strSkinName, strTypeName;

    TiXmlElement *pXmlSkin=m_pXmlSkinDesc->FirstChildElement();
    while(pXmlSkin)
    {
        CStringA strOwner= pXmlSkin->Attribute("owner");
        if(strOwner==strOwnerName)
        {
            strSkinName = pXmlSkin->Attribute("name");
            strTypeName = pXmlSkin->Value();

            if (strSkinName.IsEmpty() || strTypeName.IsEmpty())
                continue;

            DUIASSERT(!HasKey(strSkinName));
            if(DuiSkinFactoryManager::getSingleton().HasKey(strTypeName))
            {
                CSkinFactory *pSkinFactory=DuiSkinFactoryManager::getSingleton().GetKeyObject(strTypeName);
                CDuiSkinBase *pSkin = pSkinFactory->NewSkin();

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
        CDuiMap<CStringA,DuiSkinPtr>::CPair *p=m_mapNamedObj->GetNext(pos);
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

BOOL DuiSkinPool::_InitSkins(TiXmlElement *pXmlSkinRootElem)
{
    if (strcmp(pXmlSkinRootElem->Value(), "skins") != 0)
        return FALSE;
    m_pXmlSkinDesc=pXmlSkinRootElem->Clone()->ToElement();
    LoadSkins("");
    return TRUE;
}

void DuiSkinPool::OnKeyRemoved(const DuiSkinPtr & obj )
{
    CSkinFactory *pFactory=DuiSkinFactoryManager::getSingleton().GetKeyObject(obj->GetObjectClass());
    pFactory->DeleteSkin(obj);
}
}//namespace DuiEngine