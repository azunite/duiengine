/*
** Lua binding: tolua
** Generated automatically by tolua++-1.0.92 on Sun Feb 15 22:29:47 2009.
*/

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件:
#include <windows.h> 

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_tolua_open (lua_State* tolua_S);


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
}


const char * GetResource(const char * szEntry,const char *szType,unsigned int *pnSize)
{
	HMODULE hMod=GetModuleHandle(NULL);
	HRSRC hRsRc=FindResourceEx(hMod,szType,szEntry,MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL));
	if(!hRsRc) return NULL;
	else
	{
		HGLOBAL   hGlobal   =   LoadResource(hMod,   hRsRc); 
		if(!hGlobal) return NULL;
		else
		{
			*pnSize=SizeofResource(hMod,hRsRc);
			return (const char *)LockResource(hGlobal);
		}
	}
}

/* Open function */
TOLUA_API int tolua_tolua_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);

  { /* begin embedded lua code */
	  char *pScript;
	  unsigned int nSize;
   int top = lua_gettop(tolua_S);
	pScript=(char*)GetResource("IDR_LUA_compat-5.1","LUA",&nSize);
   tolua_dobuffer(tolua_S,pScript,nSize,"tolua embedded: src/bin/lua/compat-5.1.lua");
   lua_settop(tolua_S, top);
  } /* end of embedded lua code */


  { /* begin embedded lua code */
	  char *pScript;
	  unsigned int nSize;
   int top = lua_gettop(tolua_S);
   pScript=(char*)GetResource("IDR_LUA_compat","LUA",&nSize);
   tolua_dobuffer(tolua_S,pScript,nSize,"tolua embedded: src/bin/lua/compat.lua");
   lua_settop(tolua_S, top);
  } /* end of embedded lua code */


  { /* begin embedded lua code */
	  char *pScript;
	  unsigned int nSize;
   int top = lua_gettop(tolua_S);

   pScript=(char*)GetResource("IDR_LUA_basic","LUA",&nSize);
   tolua_dobuffer(tolua_S,pScript,nSize,"tolua embedded: src/bin/lua/basic.lua");
   lua_settop(tolua_S, top);
  } /* end of embedded lua code */


  { /* begin embedded lua code */
	  char *pScript;
	  unsigned int nSize;
   int top = lua_gettop(tolua_S);
   pScript=(char*)GetResource("IDR_LUA_feature","LUA",&nSize);
   tolua_dobuffer(tolua_S,pScript,nSize,"tolua embedded: src/bin/lua/feature.lua");
   lua_settop(tolua_S, top);
  } /* end of embedded lua code */


  { /* begin embedded lua code */
	  char *pScript;
	  unsigned int nSize;
   int top = lua_gettop(tolua_S);
   pScript=(char*)GetResource("IDR_LUA_verbatim","LUA",&nSize);
   tolua_dobuffer(tolua_S,pScript,nSize,"tolua embedded: src/bin/lua/verbatim.lua");
   lua_settop(tolua_S, top);
  } /* end of embedded lua code */


  { /* begin embedded lua code */
	  char *pScript;
	  unsigned int nSize;
   int top = lua_gettop(tolua_S);
   pScript=(char*)GetResource("IDR_LUA_code","LUA",&nSize);
   tolua_dobuffer(tolua_S,pScript,nSize,"tolua embedded: src/bin/lua/code.lua");
   lua_settop(tolua_S, top);
  } /* end of embedded lua code */


  { /* begin embedded lua code */
	  char *pScript;
	  unsigned int nSize;
   int top = lua_gettop(tolua_S);
   pScript=(char*)GetResource("IDR_LUA_typedef","LUA",&nSize);
   tolua_dobuffer(tolua_S,pScript,nSize,"tolua embedded: src/bin/lua/typedef.lua");
   lua_settop(tolua_S, top);
  } /* end of embedded lua code */


  { /* begin embedded lua code */
	  char *pScript;
	  unsigned int nSize;
   int top = lua_gettop(tolua_S);
   pScript=(char*)GetResource("IDR_LUA_container","LUA",&nSize);
   tolua_dobuffer(tolua_S,pScript,nSize,"tolua embedded: src/bin/lua/container.lua");
   lua_settop(tolua_S, top);
  } /* end of embedded lua code */


  { /* begin embedded lua code */
	  char *pScript;
	  unsigned int nSize;
   int top = lua_gettop(tolua_S);
   pScript=(char*)GetResource("IDR_LUA_package","LUA",&nSize);
   tolua_dobuffer(tolua_S,pScript,nSize,"tolua embedded: src/bin/lua/package.lua");
   lua_settop(tolua_S, top);
  } /* end of embedded lua code */


  { /* begin embedded lua code */
	  char *pScript;
	  unsigned int nSize;
   int top = lua_gettop(tolua_S);
   pScript=(char*)GetResource("IDR_LUA_module","LUA",&nSize);
   tolua_dobuffer(tolua_S,pScript,nSize,"tolua embedded: src/bin/lua/module.lua");
   lua_settop(tolua_S, top);
  } /* end of embedded lua code */


  { /* begin embedded lua code */
	  char *pScript;
	  unsigned int nSize;
   int top = lua_gettop(tolua_S);
   pScript=(char*)GetResource("IDR_LUA_namespace","LUA",&nSize);
   tolua_dobuffer(tolua_S,pScript,nSize,"tolua embedded: src/bin/lua/namespace.lua");
   lua_settop(tolua_S, top);
  } /* end of embedded lua code */


  { /* begin embedded lua code */
	  char *pScript;
	  unsigned int nSize;
   int top = lua_gettop(tolua_S);
   pScript=(char*)GetResource("IDR_LUA_define","LUA",&nSize);
   tolua_dobuffer(tolua_S,pScript,nSize,"tolua embedded: src/bin/lua/define.lua");
   lua_settop(tolua_S, top);
  } /* end of embedded lua code */


  { /* begin embedded lua code */
	  char *pScript;
	  unsigned int nSize;
   int top = lua_gettop(tolua_S);
   pScript=(char*)GetResource("IDR_LUA_enumerate","LUA",&nSize);
   
   tolua_dobuffer(tolua_S,pScript,nSize,"tolua embedded: src/bin/lua/enumerate.lua");
   lua_settop(tolua_S, top);
  } /* end of embedded lua code */


  { /* begin embedded lua code */
	  char *pScript;
	  unsigned int nSize;
  int top = lua_gettop(tolua_S);
   pScript=(char*)GetResource("IDR_LUA_declaration","LUA",&nSize);

   tolua_dobuffer(tolua_S,pScript,nSize,"tolua embedded: src/bin/lua/declaration.lua");
   lua_settop(tolua_S, top);
  } /* end of embedded lua code */


  { /* begin embedded lua code */
	  char *pScript;
	  unsigned int nSize;
  int top = lua_gettop(tolua_S);
   pScript=(char*)GetResource("IDR_LUA_variable","LUA",&nSize);
   
   tolua_dobuffer(tolua_S,pScript,nSize,"tolua embedded: src/bin/lua/variable.lua");
   lua_settop(tolua_S, top);
  } /* end of embedded lua code */


  { /* begin embedded lua code */
	  char *pScript;
	  unsigned int nSize;
   int top = lua_gettop(tolua_S);
   pScript=(char*)GetResource("IDR_LUA_array","LUA",&nSize);

   tolua_dobuffer(tolua_S,pScript,nSize,"tolua embedded: src/bin/lua/array.lua");
   lua_settop(tolua_S, top);
  } /* end of embedded lua code */


  { /* begin embedded lua code */
	  char *pScript;
	  unsigned int nSize;
  int top = lua_gettop(tolua_S);
   pScript=(char*)GetResource("IDR_LUA_function","LUA",&nSize);

   tolua_dobuffer(tolua_S,pScript,nSize,"tolua embedded: src/bin/lua/function.lua");
   lua_settop(tolua_S, top);
  } /* end of embedded lua code */


  { /* begin embedded lua code */
	  char *pScript;
	  unsigned int nSize;
   int top = lua_gettop(tolua_S);
   pScript=(char*)GetResource("IDR_LUA_operator","LUA",&nSize);
   
   tolua_dobuffer(tolua_S,pScript,nSize,"tolua embedded: src/bin/lua/operator.lua");
   lua_settop(tolua_S, top);
  } /* end of embedded lua code */


  { /* begin embedded lua code */
	  char *pScript;
	  unsigned int nSize;
   int top = lua_gettop(tolua_S);
   pScript=(char*)GetResource("IDR_LUA_template_class","LUA",&nSize);
   tolua_dobuffer(tolua_S,pScript,nSize,"tolua embedded: src/bin/lua/template_class.lua");
   lua_settop(tolua_S, top);
  } /* end of embedded lua code */


  { /* begin embedded lua code */
	  char *pScript;
	  unsigned int nSize;
  int top = lua_gettop(tolua_S);
   pScript=(char*)GetResource("IDR_LUA_class","LUA",&nSize);
   tolua_dobuffer(tolua_S,pScript,nSize,"tolua embedded: src/bin/lua/class.lua");
   lua_settop(tolua_S, top);
  } /* end of embedded lua code */


  { /* begin embedded lua code */
	  char *pScript;
	  unsigned int nSize;
  int top = lua_gettop(tolua_S);
   pScript=(char*)GetResource("IDR_LUA_clean","LUA",&nSize);

   tolua_dobuffer(tolua_S,pScript,nSize,"tolua embedded: src/bin/lua/clean.lua");
   lua_settop(tolua_S, top);
  } /* end of embedded lua code */


  { /* begin embedded lua code */
	  char *pScript;
	  unsigned int nSize;
   int top = lua_gettop(tolua_S);
   pScript=(char*)GetResource("IDR_LUA_doit","LUA",&nSize);
   tolua_dobuffer(tolua_S,pScript,nSize,"tolua embedded: src/bin/lua/doit.lua");
   lua_settop(tolua_S, top);
  } /* end of embedded lua code */


  { /* begin embedded lua code */
   int top = lua_gettop(tolua_S);
   static unsigned char B[] = {
    10,108,111, 99, 97,108, 32,101,114,114, 44,109,115,103, 32,
     61, 32,112, 99, 97,108,108, 40,100,111,105,116, 41, 10,105,
    102, 32,110,111,116, 32,101,114,114, 32,116,104,101,110, 10,
     32,108,111, 99, 97,108, 32, 95, 44, 95, 44,108, 97, 98,101,
    108, 44,109,115,103, 32, 61, 32,115,116,114,102,105,110,100,
     40,109,115,103, 44, 34, 40, 46, 45, 58, 46, 45, 58, 37,115,
     42, 41, 40, 46, 42, 41, 34, 41, 10, 32,116,111,108,117, 97,
     95,101,114,114,111,114, 40,109,115,103, 44,108, 97, 98,101,
    108, 41, 10, 32,112,114,105,110,116, 40,100,101, 98,117,103,
     46,116,114, 97, 99,101, 98, 97, 99,107, 40, 41, 41, 10,101,
    110,100,32
   };
   
   tolua_dobuffer(tolua_S,(char *)B,sizeof(B),"tolua: embedded Lua code 23");
   lua_settop(tolua_S, top);
  } /* end of embedded lua code */

 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_tolua (lua_State* tolua_S) {
 return tolua_tolua_open(tolua_S);
};
#endif

