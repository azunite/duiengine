#include <DuiResProviderBase.h>

BOOL ExpLua_DuiResProvider(lua_State *L)
{
	try{
		lua_tinker::class_add<DuiResProviderBase>(L,"DuiResProviderBase");
		lua_tinker::class_def<DuiResProviderBase>(L,"HasResource",&DuiResProviderBase::HasResource);
		lua_tinker::class_def<DuiResProviderBase>(L,"LoadIcon",&DuiResProviderBase::LoadIcon);
 		lua_tinker::class_def<DuiResProviderBase>(L,"LoadBitmap",&DuiResProviderBase::LoadBitmap);
 		lua_tinker::class_def<DuiResProviderBase>(L,"LoadImage",&DuiResProviderBase::LoadImage);
 		lua_tinker::class_def<DuiResProviderBase>(L,"GetRawBufferSize",&DuiResProviderBase::GetRawBufferSize);
 		lua_tinker::class_def<DuiResProviderBase>(L,"GetRawBuffer",&DuiResProviderBase::GetRawBuffer);
 		lua_tinker::class_def<DuiResProviderBase>(L,"GetImageDecoder",&DuiResProviderBase::GetImageDecoder);
 
 		lua_tinker::class_add<DuiResProviderPE>(L,"DuiResProviderPE");
 		lua_tinker::class_inh<DuiResProviderPE,DuiResProviderBase>(L);
 		lua_tinker::class_con<DuiResProviderPE>(L,lua_tinker::constructor<DuiResProviderPE,HINSTANCE,CDuiImgDecoder*>);
 
 		lua_tinker::class_add<DuiResProviderFiles>(L,"DuiResProviderFiles");
 		lua_tinker::class_inh<DuiResProviderFiles,DuiResProviderBase>(L);
 		lua_tinker::class_con<DuiResProviderFiles>(L,lua_tinker::constructor<DuiResProviderFiles,CDuiImgDecoder*>);
 		lua_tinker::class_def<DuiResProviderFiles>(L,"Init",&DuiResProviderFiles::Init);
	
		return TRUE;
	}catch(...)
	{
		return FALSE;
	}
}