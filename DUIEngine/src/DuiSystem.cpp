#include "duistd.h"
#include "DuiSystem.h"

#include "DuiThreadActiveWndManager.h"

#include "duiresutil.h"
#include "DuiCSS.h"
#include "duistringpool.h"
#include "duifontpool.h"
#include "duiskin.h"
#include "duiwndstyle.h"
#include "duiimgpool.h"
#include "duiname2id.h"
#include "DuiWindowManager.h"
#include "DuiWndFactoryManager.h"

namespace DuiEngine{

template<> DuiSystem* Singleton<DuiSystem>::ms_Singleton	= 0;

DuiSystem::DuiSystem(void)
{
	createSingletons();
}

DuiSystem::~DuiSystem(void)
{
	destroySingletons();
}


void DuiSystem::createSingletons()
{
	new DuiThreadActiveWndManager();
	new DuiName2ID();
	new DuiResManager();
	new DuiSkinFactoryManager();
	new DuiSkinPool();
	new DuiWindowFactoryManager();
	new DuiWindowManager();
	new CDuiTimerEx();

	new DuiString();
	new DuiCSS();
	new DuiFontPool();
 	new DuiStylePool();
	new DuiImgPool();

}

void DuiSystem::destroySingletons()
{
	delete DuiFontPool::getSingletonPtr();
 	delete DuiStylePool::getSingletonPtr();
	delete DuiName2ID::getSingletonPtr();

	delete CDuiTimerEx::getSingletonPtr();
	delete DuiWindowManager::getSingletonPtr();
	delete DuiWindowFactoryManager::getSingletonPtr();

	delete DuiSkinPool::getSingletonPtr();
	delete DuiSkinFactoryManager::getSingletonPtr();
	delete DuiCSS::getSingletonPtr();
	delete DuiImgPool::getSingletonPtr();
	delete DuiString::getSingletonPtr();

	delete DuiResManager::getSingletonPtr();
	delete DuiThreadActiveWndManager::getSingletonPtr();
}

}//namespace DuiEngine