#include <DuiSystem.h>

typedef 
void (DuiSystem::*FUN_LOGEVENT)(LPCTSTR , LoggingLevel level);


BOOL ExpLua_DuiSystem(lua_State *L)
{
	try{
		lua_tinker::class_add<DuiSystem>(L,"DuiSystem");
		lua_tinker::class_def<DuiSystem>(L,"GetInstance",&DuiSystem::GetInstance);
		lua_tinker::class_def<DuiSystem>(L,"SetResProvider",&DuiSystem::SetResProvider);
		lua_tinker::class_def<DuiSystem>(L,"GetResProvider",&DuiSystem::GetResProvider);
		lua_tinker::class_def<DuiSystem>(L,"SetLogger",&DuiSystem::SetLogger);
		lua_tinker::class_def<DuiSystem>(L,"GetLogger",&DuiSystem::GetLogger);
		lua_tinker::class_def<DuiSystem>(L,"logEvent",(FUN_LOGEVENT)&DuiSystem::logEvent);
		lua_tinker::class_def<DuiSystem>(L,"Name2ID",&DuiSystem::Name2ID);
		lua_tinker::class_def<DuiSystem>(L,"GetScriptModule",&DuiSystem::GetScriptModule);
		lua_tinker::class_def<DuiSystem>(L,"SetScriptModule",&DuiSystem::SetScriptModule);
		lua_tinker::def(L,"DuiSystem_getSingleton",&DuiSystem::getSingletonPtr);

		return TRUE;
	}catch(...)
	{
		return FALSE;
	}
}