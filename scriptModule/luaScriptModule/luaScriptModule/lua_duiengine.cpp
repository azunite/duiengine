/*
** Lua binding: duiengine
** Generated automatically by tolua++-1.0.93 on 04/22/13 06:58:38.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_duiengine_open (lua_State* tolua_S);

#include "require.h"
#include <duistd.h>
#include <wtl.mini/duimisc.h>
#include <DuiImgBase.h>
#include <DuiResProviderBase.h>
#include <DuiLogger.h>
#include <DuiScriptModule.h>
#include <DuiSystem.h>
#include <duiwnd.h>

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_DuiEngine__CSize (lua_State* tolua_S)
{
 DuiEngine::CSize* self = (DuiEngine::CSize*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_DuiEngine__CDuiWindow (lua_State* tolua_S)
{
 DuiEngine::CDuiWindow* self = (DuiEngine::CDuiWindow*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_DuiEngine__CPoint (lua_State* tolua_S)
{
 DuiEngine::CPoint* self = (DuiEngine::CPoint*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_HICON (lua_State* tolua_S)
{
 HICON* self = (HICON*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_HBITMAP (lua_State* tolua_S)
{
 HBITMAP* self = (HBITMAP*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_HINSTANCE (lua_State* tolua_S)
{
 HINSTANCE* self = (HINSTANCE*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_DuiEngine__CRect (lua_State* tolua_S)
{
 DuiEngine::CRect* self = (DuiEngine::CRect*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"SIZE");
 tolua_usertype(tolua_S,"DuiEngine::CSize");
 tolua_usertype(tolua_S,"DuiEngine::CPoint");
 tolua_usertype(tolua_S,"NMHDR");
 tolua_usertype(tolua_S,"HINSTANCE");
 tolua_usertype(tolua_S,"HICON");
 tolua_usertype(tolua_S,"DuiEngine::DuiResProviderBase");
 tolua_usertype(tolua_S,"HBITMAP");
 tolua_usertype(tolua_S,"POINT");
 tolua_usertype(tolua_S,"DuiEngine::DuiSystem");
 tolua_usertype(tolua_S,"DuiEngine::CDuiWindow");
 tolua_usertype(tolua_S,"RECT");
 tolua_usertype(tolua_S,"DuiEngine::CDuiImgDecoder");
 tolua_usertype(tolua_S,"LPNMHDR");
 tolua_usertype(tolua_S,"DuiEngine::IScriptModule");
 tolua_usertype(tolua_S,"LPCTSTR");
 tolua_usertype(tolua_S,"DuiEngine::DuiLogger");
 tolua_usertype(tolua_S,"HDC");
 tolua_usertype(tolua_S,"HWND");
 tolua_usertype(tolua_S,"DuiEngine::CDuiImgBase");
 tolua_usertype(tolua_S,"DuiEngine::CRect");
}

/* get function: cx of class  SIZE */
#ifndef TOLUA_DISABLE_tolua_get_SIZE_cx
static int tolua_get_SIZE_cx(lua_State* tolua_S)
{
  SIZE* self = (SIZE*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cx'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->cx);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: cx of class  SIZE */
#ifndef TOLUA_DISABLE_tolua_set_SIZE_cx
static int tolua_set_SIZE_cx(lua_State* tolua_S)
{
  SIZE* self = (SIZE*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cx'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->cx = ((  long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: cy of class  SIZE */
#ifndef TOLUA_DISABLE_tolua_get_SIZE_cy
static int tolua_get_SIZE_cy(lua_State* tolua_S)
{
  SIZE* self = (SIZE*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cy'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->cy);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: cy of class  SIZE */
#ifndef TOLUA_DISABLE_tolua_set_SIZE_cy
static int tolua_set_SIZE_cy(lua_State* tolua_S)
{
  SIZE* self = (SIZE*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cy'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->cy = ((  long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: x of class  POINT */
#ifndef TOLUA_DISABLE_tolua_get_POINT_x
static int tolua_get_POINT_x(lua_State* tolua_S)
{
  POINT* self = (POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->x);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: x of class  POINT */
#ifndef TOLUA_DISABLE_tolua_set_POINT_x
static int tolua_set_POINT_x(lua_State* tolua_S)
{
  POINT* self = (POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->x = ((  long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: y of class  POINT */
#ifndef TOLUA_DISABLE_tolua_get_POINT_y
static int tolua_get_POINT_y(lua_State* tolua_S)
{
  POINT* self = (POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->y);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: y of class  POINT */
#ifndef TOLUA_DISABLE_tolua_set_POINT_y
static int tolua_set_POINT_y(lua_State* tolua_S)
{
  POINT* self = (POINT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->y = ((  long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: left of class  RECT */
#ifndef TOLUA_DISABLE_tolua_get_RECT_left
static int tolua_get_RECT_left(lua_State* tolua_S)
{
  RECT* self = (RECT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'left'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->left);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: left of class  RECT */
#ifndef TOLUA_DISABLE_tolua_set_RECT_left
static int tolua_set_RECT_left(lua_State* tolua_S)
{
  RECT* self = (RECT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'left'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->left = ((  long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: top of class  RECT */
#ifndef TOLUA_DISABLE_tolua_get_RECT_top
static int tolua_get_RECT_top(lua_State* tolua_S)
{
  RECT* self = (RECT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'top'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->top);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: top of class  RECT */
#ifndef TOLUA_DISABLE_tolua_set_RECT_top
static int tolua_set_RECT_top(lua_State* tolua_S)
{
  RECT* self = (RECT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'top'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->top = ((  long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: right of class  RECT */
#ifndef TOLUA_DISABLE_tolua_get_RECT_right
static int tolua_get_RECT_right(lua_State* tolua_S)
{
  RECT* self = (RECT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'right'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->right);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: right of class  RECT */
#ifndef TOLUA_DISABLE_tolua_set_RECT_right
static int tolua_set_RECT_right(lua_State* tolua_S)
{
  RECT* self = (RECT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'right'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->right = ((  long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bottom of class  RECT */
#ifndef TOLUA_DISABLE_tolua_get_RECT_bottom
static int tolua_get_RECT_bottom(lua_State* tolua_S)
{
  RECT* self = (RECT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bottom'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->bottom);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bottom of class  RECT */
#ifndef TOLUA_DISABLE_tolua_set_RECT_bottom
static int tolua_set_RECT_bottom(lua_State* tolua_S)
{
  RECT* self = (RECT*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bottom'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bottom = ((  long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: hwndFrom of class  NMHDR */
#ifndef TOLUA_DISABLE_tolua_get_NMHDR_hwndFrom
static int tolua_get_NMHDR_hwndFrom(lua_State* tolua_S)
{
  NMHDR* self = (NMHDR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hwndFrom'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->hwndFrom,"HWND");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: hwndFrom of class  NMHDR */
#ifndef TOLUA_DISABLE_tolua_set_NMHDR_hwndFrom
static int tolua_set_NMHDR_hwndFrom(lua_State* tolua_S)
{
  NMHDR* self = (NMHDR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hwndFrom'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"HWND",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->hwndFrom = *((HWND*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: idFrom of class  NMHDR */
#ifndef TOLUA_DISABLE_tolua_get_NMHDR_unsigned_idFrom
static int tolua_get_NMHDR_unsigned_idFrom(lua_State* tolua_S)
{
  NMHDR* self = (NMHDR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'idFrom'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->idFrom);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: idFrom of class  NMHDR */
#ifndef TOLUA_DISABLE_tolua_set_NMHDR_unsigned_idFrom
static int tolua_set_NMHDR_unsigned_idFrom(lua_State* tolua_S)
{
  NMHDR* self = (NMHDR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'idFrom'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->idFrom = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: code of class  NMHDR */
#ifndef TOLUA_DISABLE_tolua_get_NMHDR_unsigned_code
static int tolua_get_NMHDR_unsigned_code(lua_State* tolua_S)
{
  NMHDR* self = (NMHDR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'code'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->code);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: code of class  NMHDR */
#ifndef TOLUA_DISABLE_tolua_set_NMHDR_unsigned_code
static int tolua_set_NMHDR_unsigned_code(lua_State* tolua_S)
{
  NMHDR* self = (NMHDR*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'code'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->code = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  DuiEngine::CSize */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CSize_new00
static int tolua_duiengine_DuiEngine_CSize_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CSize",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DuiEngine::CSize* tolua_ret = (DuiEngine::CSize*)  Mtolua_new((DuiEngine::CSize)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CSize");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  DuiEngine::CSize */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CSize_new00_local
static int tolua_duiengine_DuiEngine_CSize_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CSize",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DuiEngine::CSize* tolua_ret = (DuiEngine::CSize*)  Mtolua_new((DuiEngine::CSize)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  DuiEngine::CSize */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CSize_new01
static int tolua_duiengine_DuiEngine_CSize_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CSize",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int initCX = ((int)  tolua_tonumber(tolua_S,2,0));
  int initCY = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   DuiEngine::CSize* tolua_ret = (DuiEngine::CSize*)  Mtolua_new((DuiEngine::CSize)(initCX,initCY));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CSize");
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CSize_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  DuiEngine::CSize */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CSize_new01_local
static int tolua_duiengine_DuiEngine_CSize_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CSize",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int initCX = ((int)  tolua_tonumber(tolua_S,2,0));
  int initCY = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   DuiEngine::CSize* tolua_ret = (DuiEngine::CSize*)  Mtolua_new((DuiEngine::CSize)(initCX,initCY));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CSize_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  DuiEngine::CSize */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CSize_new02
static int tolua_duiengine_DuiEngine_CSize_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CSize",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"SIZE",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIZE initSize = *((SIZE*)  tolua_tousertype(tolua_S,2,0));
  {
   DuiEngine::CSize* tolua_ret = (DuiEngine::CSize*)  Mtolua_new((DuiEngine::CSize)(initSize));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CSize");
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CSize_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  DuiEngine::CSize */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CSize_new02_local
static int tolua_duiengine_DuiEngine_CSize_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CSize",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"SIZE",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIZE initSize = *((SIZE*)  tolua_tousertype(tolua_S,2,0));
  {
   DuiEngine::CSize* tolua_ret = (DuiEngine::CSize*)  Mtolua_new((DuiEngine::CSize)(initSize));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CSize_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  DuiEngine::CSize */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CSize_new03
static int tolua_duiengine_DuiEngine_CSize_new03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CSize",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"POINT",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  POINT initPt = *((POINT*)  tolua_tousertype(tolua_S,2,0));
  {
   DuiEngine::CSize* tolua_ret = (DuiEngine::CSize*)  Mtolua_new((DuiEngine::CSize)(initPt));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CSize");
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CSize_new02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  DuiEngine::CSize */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CSize_new03_local
static int tolua_duiengine_DuiEngine_CSize_new03_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CSize",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"POINT",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  POINT initPt = *((POINT*)  tolua_tousertype(tolua_S,2,0));
  {
   DuiEngine::CSize* tolua_ret = (DuiEngine::CSize*)  Mtolua_new((DuiEngine::CSize)(initPt));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CSize_new02_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  DuiEngine::CSize */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CSize_new04
static int tolua_duiengine_DuiEngine_CSize_new04(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CSize",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  unsigned long dwSize = (( unsigned long)  tolua_tonumber(tolua_S,2,0));
  {
   DuiEngine::CSize* tolua_ret = (DuiEngine::CSize*)  Mtolua_new((DuiEngine::CSize)(dwSize));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CSize");
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CSize_new03(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  DuiEngine::CSize */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CSize_new04_local
static int tolua_duiengine_DuiEngine_CSize_new04_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CSize",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  unsigned long dwSize = (( unsigned long)  tolua_tonumber(tolua_S,2,0));
  {
   DuiEngine::CSize* tolua_ret = (DuiEngine::CSize*)  Mtolua_new((DuiEngine::CSize)(dwSize));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CSize_new03_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  DuiEngine::CSize */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CSize__eq00
static int tolua_duiengine_DuiEngine_CSize__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CSize",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"SIZE",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DuiEngine::CSize* self = (const DuiEngine::CSize*)  tolua_tousertype(tolua_S,1,0);
  SIZE size = *((SIZE*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
    int tolua_ret = (  int)  self->operator==(size);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSize of class  DuiEngine::CSize */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CSize_SetSize00
static int tolua_duiengine_DuiEngine_CSize_SetSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CSize",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CSize* self = (DuiEngine::CSize*)  tolua_tousertype(tolua_S,1,0);
  int CX = ((int)  tolua_tonumber(tolua_S,2,0));
  int CY = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSize'", NULL);
#endif
  {
   self->SetSize(CX,CY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  DuiEngine::CSize */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CSize__add00
static int tolua_duiengine_DuiEngine_CSize__add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CSize",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"SIZE",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DuiEngine::CSize* self = (const DuiEngine::CSize*)  tolua_tousertype(tolua_S,1,0);
  SIZE size = *((SIZE*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   DuiEngine::CSize tolua_ret = (DuiEngine::CSize)  self->operator+(size);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((DuiEngine::CSize)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DuiEngine::CSize));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  DuiEngine::CSize */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CSize__sub00
static int tolua_duiengine_DuiEngine_CSize__sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CSize",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"SIZE",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DuiEngine::CSize* self = (const DuiEngine::CSize*)  tolua_tousertype(tolua_S,1,0);
  SIZE size = *((SIZE*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   DuiEngine::CSize tolua_ret = (DuiEngine::CSize)  self->operator-(size);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((DuiEngine::CSize)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DuiEngine::CSize));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  DuiEngine::CSize */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CSize__sub01
static int tolua_duiengine_DuiEngine_CSize__sub01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CSize",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const DuiEngine::CSize* self = (const DuiEngine::CSize*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   DuiEngine::CSize tolua_ret = (DuiEngine::CSize)  self->operator-();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((DuiEngine::CSize)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DuiEngine::CSize));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CSize__sub00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  DuiEngine::CSize */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CSize__add01
static int tolua_duiengine_DuiEngine_CSize__add01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CSize",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"POINT",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const DuiEngine::CSize* self = (const DuiEngine::CSize*)  tolua_tousertype(tolua_S,1,0);
  POINT point = *((POINT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   DuiEngine::CPoint tolua_ret = (DuiEngine::CPoint)  self->operator+(point);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((DuiEngine::CPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DuiEngine::CPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CSize__add00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  DuiEngine::CSize */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CSize__sub02
static int tolua_duiengine_DuiEngine_CSize__sub02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CSize",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"POINT",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const DuiEngine::CSize* self = (const DuiEngine::CSize*)  tolua_tousertype(tolua_S,1,0);
  POINT point = *((POINT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   DuiEngine::CPoint tolua_ret = (DuiEngine::CPoint)  self->operator-(point);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((DuiEngine::CPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DuiEngine::CPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CSize__sub01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  DuiEngine::CSize */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CSize__add02
static int tolua_duiengine_DuiEngine_CSize__add02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CSize",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const RECT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const DuiEngine::CSize* self = (const DuiEngine::CSize*)  tolua_tousertype(tolua_S,1,0);
  const RECT* lpRect = ((const RECT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   DuiEngine::CRect tolua_ret = (DuiEngine::CRect)  self->operator+(lpRect);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((DuiEngine::CRect)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DuiEngine::CRect));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CSize__add01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  DuiEngine::CSize */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CSize__sub03
static int tolua_duiengine_DuiEngine_CSize__sub03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CSize",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const RECT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const DuiEngine::CSize* self = (const DuiEngine::CSize*)  tolua_tousertype(tolua_S,1,0);
  const RECT* lpRect = ((const RECT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   DuiEngine::CRect tolua_ret = (DuiEngine::CRect)  self->operator-(lpRect);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((DuiEngine::CRect)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DuiEngine::CRect));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CSize__sub02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: cx of class  DuiEngine::CSize */
#ifndef TOLUA_DISABLE_tolua_get_DuiEngine__CSize_cx
static int tolua_get_DuiEngine__CSize_cx(lua_State* tolua_S)
{
  DuiEngine::CSize* self = (DuiEngine::CSize*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cx'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->cx);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: cx of class  DuiEngine::CSize */
#ifndef TOLUA_DISABLE_tolua_set_DuiEngine__CSize_cx
static int tolua_set_DuiEngine__CSize_cx(lua_State* tolua_S)
{
  DuiEngine::CSize* self = (DuiEngine::CSize*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cx'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->cx = ((  long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: cy of class  DuiEngine::CSize */
#ifndef TOLUA_DISABLE_tolua_get_DuiEngine__CSize_cy
static int tolua_get_DuiEngine__CSize_cy(lua_State* tolua_S)
{
  DuiEngine::CSize* self = (DuiEngine::CSize*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cy'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->cy);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: cy of class  DuiEngine::CSize */
#ifndef TOLUA_DISABLE_tolua_set_DuiEngine__CSize_cy
static int tolua_set_DuiEngine__CSize_cy(lua_State* tolua_S)
{
  DuiEngine::CSize* self = (DuiEngine::CSize*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cy'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->cy = ((  long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  DuiEngine::CPoint */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CPoint_new00
static int tolua_duiengine_DuiEngine_CPoint_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DuiEngine::CPoint* tolua_ret = (DuiEngine::CPoint*)  Mtolua_new((DuiEngine::CPoint)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  DuiEngine::CPoint */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CPoint_new00_local
static int tolua_duiengine_DuiEngine_CPoint_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DuiEngine::CPoint* tolua_ret = (DuiEngine::CPoint*)  Mtolua_new((DuiEngine::CPoint)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  DuiEngine::CPoint */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CPoint_new01
static int tolua_duiengine_DuiEngine_CPoint_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CPoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int initX = ((int)  tolua_tonumber(tolua_S,2,0));
  int initY = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   DuiEngine::CPoint* tolua_ret = (DuiEngine::CPoint*)  Mtolua_new((DuiEngine::CPoint)(initX,initY));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CPoint");
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CPoint_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  DuiEngine::CPoint */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CPoint_new01_local
static int tolua_duiengine_DuiEngine_CPoint_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CPoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int initX = ((int)  tolua_tonumber(tolua_S,2,0));
  int initY = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   DuiEngine::CPoint* tolua_ret = (DuiEngine::CPoint*)  Mtolua_new((DuiEngine::CPoint)(initX,initY));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CPoint_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  DuiEngine::CPoint */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CPoint_new02
static int tolua_duiengine_DuiEngine_CPoint_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"POINT",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  POINT initPt = *((POINT*)  tolua_tousertype(tolua_S,2,0));
  {
   DuiEngine::CPoint* tolua_ret = (DuiEngine::CPoint*)  Mtolua_new((DuiEngine::CPoint)(initPt));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CPoint");
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CPoint_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  DuiEngine::CPoint */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CPoint_new02_local
static int tolua_duiengine_DuiEngine_CPoint_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"POINT",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  POINT initPt = *((POINT*)  tolua_tousertype(tolua_S,2,0));
  {
   DuiEngine::CPoint* tolua_ret = (DuiEngine::CPoint*)  Mtolua_new((DuiEngine::CPoint)(initPt));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CPoint_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  DuiEngine::CPoint */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CPoint_new03
static int tolua_duiengine_DuiEngine_CPoint_new03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"SIZE",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIZE initSize = *((SIZE*)  tolua_tousertype(tolua_S,2,0));
  {
   DuiEngine::CPoint* tolua_ret = (DuiEngine::CPoint*)  Mtolua_new((DuiEngine::CPoint)(initSize));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CPoint");
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CPoint_new02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  DuiEngine::CPoint */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CPoint_new03_local
static int tolua_duiengine_DuiEngine_CPoint_new03_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"SIZE",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SIZE initSize = *((SIZE*)  tolua_tousertype(tolua_S,2,0));
  {
   DuiEngine::CPoint* tolua_ret = (DuiEngine::CPoint*)  Mtolua_new((DuiEngine::CPoint)(initSize));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CPoint_new02_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  DuiEngine::CPoint */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CPoint_new04
static int tolua_duiengine_DuiEngine_CPoint_new04(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CPoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  unsigned long dwPoint = (( unsigned long)  tolua_tonumber(tolua_S,2,0));
  {
   DuiEngine::CPoint* tolua_ret = (DuiEngine::CPoint*)  Mtolua_new((DuiEngine::CPoint)(dwPoint));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CPoint");
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CPoint_new03(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  DuiEngine::CPoint */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CPoint_new04_local
static int tolua_duiengine_DuiEngine_CPoint_new04_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CPoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  unsigned long dwPoint = (( unsigned long)  tolua_tonumber(tolua_S,2,0));
  {
   DuiEngine::CPoint* tolua_ret = (DuiEngine::CPoint*)  Mtolua_new((DuiEngine::CPoint)(dwPoint));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CPoint_new03_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Offset of class  DuiEngine::CPoint */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CPoint_Offset00
static int tolua_duiengine_DuiEngine_CPoint_Offset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CPoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CPoint* self = (DuiEngine::CPoint*)  tolua_tousertype(tolua_S,1,0);
  int xOffset = ((int)  tolua_tonumber(tolua_S,2,0));
  int yOffset = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Offset'", NULL);
#endif
  {
   self->Offset(xOffset,yOffset);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Offset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Offset of class  DuiEngine::CPoint */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CPoint_Offset01
static int tolua_duiengine_DuiEngine_CPoint_Offset01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"POINT",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  DuiEngine::CPoint* self = (DuiEngine::CPoint*)  tolua_tousertype(tolua_S,1,0);
  POINT point = *((POINT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Offset'", NULL);
#endif
  {
   self->Offset(point);
  }
 }
 return 0;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CPoint_Offset00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Offset of class  DuiEngine::CPoint */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CPoint_Offset02
static int tolua_duiengine_DuiEngine_CPoint_Offset02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"SIZE",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  DuiEngine::CPoint* self = (DuiEngine::CPoint*)  tolua_tousertype(tolua_S,1,0);
  SIZE size = *((SIZE*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Offset'", NULL);
#endif
  {
   self->Offset(size);
  }
 }
 return 0;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CPoint_Offset01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  DuiEngine::CPoint */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CPoint__eq00
static int tolua_duiengine_DuiEngine_CPoint__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"POINT",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DuiEngine::CPoint* self = (const DuiEngine::CPoint*)  tolua_tousertype(tolua_S,1,0);
  POINT point = *((POINT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
    int tolua_ret = (  int)  self->operator==(point);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPoint of class  DuiEngine::CPoint */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CPoint_SetPoint00
static int tolua_duiengine_DuiEngine_CPoint_SetPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CPoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CPoint* self = (DuiEngine::CPoint*)  tolua_tousertype(tolua_S,1,0);
  int X = ((int)  tolua_tonumber(tolua_S,2,0));
  int Y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPoint'", NULL);
#endif
  {
   self->SetPoint(X,Y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  DuiEngine::CPoint */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CPoint__add00
static int tolua_duiengine_DuiEngine_CPoint__add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"SIZE",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DuiEngine::CPoint* self = (const DuiEngine::CPoint*)  tolua_tousertype(tolua_S,1,0);
  SIZE size = *((SIZE*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   DuiEngine::CPoint tolua_ret = (DuiEngine::CPoint)  self->operator+(size);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((DuiEngine::CPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DuiEngine::CPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  DuiEngine::CPoint */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CPoint__sub00
static int tolua_duiengine_DuiEngine_CPoint__sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"SIZE",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DuiEngine::CPoint* self = (const DuiEngine::CPoint*)  tolua_tousertype(tolua_S,1,0);
  SIZE size = *((SIZE*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   DuiEngine::CPoint tolua_ret = (DuiEngine::CPoint)  self->operator-(size);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((DuiEngine::CPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DuiEngine::CPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  DuiEngine::CPoint */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CPoint__sub01
static int tolua_duiengine_DuiEngine_CPoint__sub01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CPoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const DuiEngine::CPoint* self = (const DuiEngine::CPoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   DuiEngine::CPoint tolua_ret = (DuiEngine::CPoint)  self->operator-();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((DuiEngine::CPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DuiEngine::CPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CPoint__sub00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  DuiEngine::CPoint */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CPoint__add01
static int tolua_duiengine_DuiEngine_CPoint__add01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"POINT",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const DuiEngine::CPoint* self = (const DuiEngine::CPoint*)  tolua_tousertype(tolua_S,1,0);
  POINT point = *((POINT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   DuiEngine::CPoint tolua_ret = (DuiEngine::CPoint)  self->operator+(point);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((DuiEngine::CPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DuiEngine::CPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CPoint__add00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  DuiEngine::CPoint */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CPoint__sub02
static int tolua_duiengine_DuiEngine_CPoint__sub02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CPoint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"POINT",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const DuiEngine::CPoint* self = (const DuiEngine::CPoint*)  tolua_tousertype(tolua_S,1,0);
  POINT point = *((POINT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   DuiEngine::CSize tolua_ret = (DuiEngine::CSize)  self->operator-(point);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((DuiEngine::CSize)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DuiEngine::CSize));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CPoint__sub01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: x of class  DuiEngine::CPoint */
#ifndef TOLUA_DISABLE_tolua_get_DuiEngine__CPoint_x
static int tolua_get_DuiEngine__CPoint_x(lua_State* tolua_S)
{
  DuiEngine::CPoint* self = (DuiEngine::CPoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->x);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: x of class  DuiEngine::CPoint */
#ifndef TOLUA_DISABLE_tolua_set_DuiEngine__CPoint_x
static int tolua_set_DuiEngine__CPoint_x(lua_State* tolua_S)
{
  DuiEngine::CPoint* self = (DuiEngine::CPoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->x = ((  long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: y of class  DuiEngine::CPoint */
#ifndef TOLUA_DISABLE_tolua_get_DuiEngine__CPoint_y
static int tolua_get_DuiEngine__CPoint_y(lua_State* tolua_S)
{
  DuiEngine::CPoint* self = (DuiEngine::CPoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->y);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: y of class  DuiEngine::CPoint */
#ifndef TOLUA_DISABLE_tolua_set_DuiEngine__CPoint_y
static int tolua_set_DuiEngine__CPoint_y(lua_State* tolua_S)
{
  DuiEngine::CPoint* self = (DuiEngine::CPoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->y = ((  long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_new00
static int tolua_duiengine_DuiEngine_CRect_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DuiEngine::CRect* tolua_ret = (DuiEngine::CRect*)  Mtolua_new((DuiEngine::CRect)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CRect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_new00_local
static int tolua_duiengine_DuiEngine_CRect_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DuiEngine::CRect* tolua_ret = (DuiEngine::CRect*)  Mtolua_new((DuiEngine::CRect)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_new01
static int tolua_duiengine_DuiEngine_CRect_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int l = ((int)  tolua_tonumber(tolua_S,2,0));
  int t = ((int)  tolua_tonumber(tolua_S,3,0));
  int r = ((int)  tolua_tonumber(tolua_S,4,0));
  int b = ((int)  tolua_tonumber(tolua_S,5,0));
  {
   DuiEngine::CRect* tolua_ret = (DuiEngine::CRect*)  Mtolua_new((DuiEngine::CRect)(l,t,r,b));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CRect");
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CRect_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_new01_local
static int tolua_duiengine_DuiEngine_CRect_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int l = ((int)  tolua_tonumber(tolua_S,2,0));
  int t = ((int)  tolua_tonumber(tolua_S,3,0));
  int r = ((int)  tolua_tonumber(tolua_S,4,0));
  int b = ((int)  tolua_tonumber(tolua_S,5,0));
  {
   DuiEngine::CRect* tolua_ret = (DuiEngine::CRect*)  Mtolua_new((DuiEngine::CRect)(l,t,r,b));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CRect_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_new02
static int tolua_duiengine_DuiEngine_CRect_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const RECT",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const RECT* srcRect = ((const RECT*)  tolua_tousertype(tolua_S,2,0));
  {
   DuiEngine::CRect* tolua_ret = (DuiEngine::CRect*)  Mtolua_new((DuiEngine::CRect)(*srcRect));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CRect");
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CRect_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_new02_local
static int tolua_duiengine_DuiEngine_CRect_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const RECT",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const RECT* srcRect = ((const RECT*)  tolua_tousertype(tolua_S,2,0));
  {
   DuiEngine::CRect* tolua_ret = (DuiEngine::CRect*)  Mtolua_new((DuiEngine::CRect)(*srcRect));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CRect_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_new03
static int tolua_duiengine_DuiEngine_CRect_new03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"POINT",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"SIZE",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  POINT point = *((POINT*)  tolua_tousertype(tolua_S,2,0));
  SIZE size = *((SIZE*)  tolua_tousertype(tolua_S,3,0));
  {
   DuiEngine::CRect* tolua_ret = (DuiEngine::CRect*)  Mtolua_new((DuiEngine::CRect)(point,size));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CRect");
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CRect_new02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_new03_local
static int tolua_duiengine_DuiEngine_CRect_new03_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"POINT",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"SIZE",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  POINT point = *((POINT*)  tolua_tousertype(tolua_S,2,0));
  SIZE size = *((SIZE*)  tolua_tousertype(tolua_S,3,0));
  {
   DuiEngine::CRect* tolua_ret = (DuiEngine::CRect*)  Mtolua_new((DuiEngine::CRect)(point,size));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CRect_new02_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_new04
static int tolua_duiengine_DuiEngine_CRect_new04(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"POINT",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"POINT",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  POINT topLeft = *((POINT*)  tolua_tousertype(tolua_S,2,0));
  POINT bottomRight = *((POINT*)  tolua_tousertype(tolua_S,3,0));
  {
   DuiEngine::CRect* tolua_ret = (DuiEngine::CRect*)  Mtolua_new((DuiEngine::CRect)(topLeft,bottomRight));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CRect");
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CRect_new03(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_new04_local
static int tolua_duiengine_DuiEngine_CRect_new04_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"POINT",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"POINT",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  POINT topLeft = *((POINT*)  tolua_tousertype(tolua_S,2,0));
  POINT bottomRight = *((POINT*)  tolua_tousertype(tolua_S,3,0));
  {
   DuiEngine::CRect* tolua_ret = (DuiEngine::CRect*)  Mtolua_new((DuiEngine::CRect)(topLeft,bottomRight));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CRect_new03_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Width of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_Width00
static int tolua_duiengine_DuiEngine_CRect_Width00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DuiEngine::CRect* self = (const DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Width'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Width();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Width'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Height of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_Height00
static int tolua_duiengine_DuiEngine_CRect_Height00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DuiEngine::CRect* self = (const DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Height'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Height();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Height'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Size of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_Size00
static int tolua_duiengine_DuiEngine_CRect_Size00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DuiEngine::CRect* self = (const DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Size'", NULL);
#endif
  {
   DuiEngine::CSize tolua_ret = (DuiEngine::CSize)  self->Size();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((DuiEngine::CSize)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DuiEngine::CSize));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Size'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TopLeft of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_TopLeft00
static int tolua_duiengine_DuiEngine_CRect_TopLeft00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CRect* self = (DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TopLeft'", NULL);
#endif
  {
   DuiEngine::CPoint& tolua_ret = (DuiEngine::CPoint&)  self->TopLeft();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"DuiEngine::CPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TopLeft'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: BottomRight of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_BottomRight00
static int tolua_duiengine_DuiEngine_CRect_BottomRight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CRect* self = (DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BottomRight'", NULL);
#endif
  {
   DuiEngine::CPoint& tolua_ret = (DuiEngine::CPoint&)  self->BottomRight();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"DuiEngine::CPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BottomRight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TopLeft of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_TopLeft01
static int tolua_duiengine_DuiEngine_CRect_TopLeft01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const DuiEngine::CRect* self = (const DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TopLeft'", NULL);
#endif
  {
   const DuiEngine::CPoint& tolua_ret = (const DuiEngine::CPoint&)  self->TopLeft();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const DuiEngine::CPoint");
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CRect_TopLeft00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: BottomRight of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_BottomRight01
static int tolua_duiengine_DuiEngine_CRect_BottomRight01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const DuiEngine::CRect* self = (const DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BottomRight'", NULL);
#endif
  {
   const DuiEngine::CPoint& tolua_ret = (const DuiEngine::CPoint&)  self->BottomRight();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const DuiEngine::CPoint");
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CRect_BottomRight00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: CenterPoint of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_CenterPoint00
static int tolua_duiengine_DuiEngine_CRect_CenterPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DuiEngine::CRect* self = (const DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CenterPoint'", NULL);
#endif
  {
   DuiEngine::CPoint tolua_ret = (DuiEngine::CPoint)  self->CenterPoint();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((DuiEngine::CPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DuiEngine::CPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CenterPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsRectEmpty of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_IsRectEmpty00
static int tolua_duiengine_DuiEngine_CRect_IsRectEmpty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DuiEngine::CRect* self = (const DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsRectEmpty'", NULL);
#endif
  {
    int tolua_ret = (  int)  self->IsRectEmpty();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsRectEmpty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsRectNull of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_IsRectNull00
static int tolua_duiengine_DuiEngine_CRect_IsRectNull00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DuiEngine::CRect* self = (const DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsRectNull'", NULL);
#endif
  {
    int tolua_ret = (  int)  self->IsRectNull();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsRectNull'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PtInRect of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_PtInRect00
static int tolua_duiengine_DuiEngine_CRect_PtInRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CRect",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"POINT",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DuiEngine::CRect* self = (const DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
  POINT point = *((POINT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PtInRect'", NULL);
#endif
  {
    int tolua_ret = (  int)  self->PtInRect(point);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PtInRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRect of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_SetRect00
static int tolua_duiengine_DuiEngine_CRect_SetRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CRect* self = (DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
  int x1 = ((int)  tolua_tonumber(tolua_S,2,0));
  int y1 = ((int)  tolua_tonumber(tolua_S,3,0));
  int x2 = ((int)  tolua_tonumber(tolua_S,4,0));
  int y2 = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRect'", NULL);
#endif
  {
   self->SetRect(x1,y1,x2,y2);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRect of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_SetRect01
static int tolua_duiengine_DuiEngine_CRect_SetRect01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"POINT",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"POINT",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  DuiEngine::CRect* self = (DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
  POINT topLeft = *((POINT*)  tolua_tousertype(tolua_S,2,0));
  POINT bottomRight = *((POINT*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRect'", NULL);
#endif
  {
   self->SetRect(topLeft,bottomRight);
  }
 }
 return 0;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CRect_SetRect00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRectEmpty of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_SetRectEmpty00
static int tolua_duiengine_DuiEngine_CRect_SetRectEmpty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CRect* self = (DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRectEmpty'", NULL);
#endif
  {
   self->SetRectEmpty();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRectEmpty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InflateRect of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_InflateRect00
static int tolua_duiengine_DuiEngine_CRect_InflateRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CRect* self = (DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InflateRect'", NULL);
#endif
  {
   self->InflateRect(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InflateRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InflateRect of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_InflateRect01
static int tolua_duiengine_DuiEngine_CRect_InflateRect01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"SIZE",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  DuiEngine::CRect* self = (DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
  SIZE size = *((SIZE*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InflateRect'", NULL);
#endif
  {
   self->InflateRect(size);
  }
 }
 return 0;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CRect_InflateRect00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: InflateRect of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_InflateRect02
static int tolua_duiengine_DuiEngine_CRect_InflateRect02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  DuiEngine::CRect* self = (DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
  int l = ((int)  tolua_tonumber(tolua_S,2,0));
  int t = ((int)  tolua_tonumber(tolua_S,3,0));
  int r = ((int)  tolua_tonumber(tolua_S,4,0));
  int b = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InflateRect'", NULL);
#endif
  {
   self->InflateRect(l,t,r,b);
  }
 }
 return 0;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CRect_InflateRect01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: DeflateRect of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_DeflateRect00
static int tolua_duiengine_DuiEngine_CRect_DeflateRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CRect* self = (DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DeflateRect'", NULL);
#endif
  {
   self->DeflateRect(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DeflateRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DeflateRect of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_DeflateRect01
static int tolua_duiengine_DuiEngine_CRect_DeflateRect01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"SIZE",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  DuiEngine::CRect* self = (DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
  SIZE size = *((SIZE*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DeflateRect'", NULL);
#endif
  {
   self->DeflateRect(size);
  }
 }
 return 0;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CRect_DeflateRect00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: DeflateRect of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_DeflateRect02
static int tolua_duiengine_DuiEngine_CRect_DeflateRect02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  DuiEngine::CRect* self = (DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
  int l = ((int)  tolua_tonumber(tolua_S,2,0));
  int t = ((int)  tolua_tonumber(tolua_S,3,0));
  int r = ((int)  tolua_tonumber(tolua_S,4,0));
  int b = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DeflateRect'", NULL);
#endif
  {
   self->DeflateRect(l,t,r,b);
  }
 }
 return 0;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CRect_DeflateRect01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: OffsetRect of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_OffsetRect00
static int tolua_duiengine_DuiEngine_CRect_OffsetRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CRect* self = (DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OffsetRect'", NULL);
#endif
  {
   self->OffsetRect(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OffsetRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OffsetRect of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_OffsetRect01
static int tolua_duiengine_DuiEngine_CRect_OffsetRect01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"SIZE",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  DuiEngine::CRect* self = (DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
  SIZE size = *((SIZE*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OffsetRect'", NULL);
#endif
  {
   self->OffsetRect(size);
  }
 }
 return 0;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CRect_OffsetRect00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: OffsetRect of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_OffsetRect02
static int tolua_duiengine_DuiEngine_CRect_OffsetRect02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"POINT",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  DuiEngine::CRect* self = (DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
  POINT point = *((POINT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OffsetRect'", NULL);
#endif
  {
   self->OffsetRect(point);
  }
 }
 return 0;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CRect_OffsetRect01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: NormalizeRect of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_NormalizeRect00
static int tolua_duiengine_DuiEngine_CRect_NormalizeRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CRect* self = (DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NormalizeRect'", NULL);
#endif
  {
   self->NormalizeRect();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NormalizeRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MoveToY of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_MoveToY00
static int tolua_duiengine_DuiEngine_CRect_MoveToY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CRect* self = (DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
  int y = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MoveToY'", NULL);
#endif
  {
   self->MoveToY(y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MoveToY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MoveToX of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_MoveToX00
static int tolua_duiengine_DuiEngine_CRect_MoveToX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CRect* self = (DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MoveToX'", NULL);
#endif
  {
   self->MoveToX(x);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MoveToX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MoveToXY of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_MoveToXY00
static int tolua_duiengine_DuiEngine_CRect_MoveToXY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CRect* self = (DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MoveToXY'", NULL);
#endif
  {
   self->MoveToXY(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MoveToXY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MoveToXY of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_MoveToXY01
static int tolua_duiengine_DuiEngine_CRect_MoveToXY01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CRect",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"POINT",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  DuiEngine::CRect* self = (DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
  POINT pt = *((POINT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MoveToXY'", NULL);
#endif
  {
   self->MoveToXY(pt);
  }
 }
 return 0;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CRect_MoveToXY00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect__eq00
static int tolua_duiengine_DuiEngine_CRect__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CRect",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const RECT",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DuiEngine::CRect* self = (const DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
  const RECT* rect = ((const RECT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
    int tolua_ret = (  int)  self->operator==(*rect);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect__add00
static int tolua_duiengine_DuiEngine_CRect__add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CRect",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"POINT",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DuiEngine::CRect* self = (const DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
  POINT pt = *((POINT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   DuiEngine::CRect tolua_ret = (DuiEngine::CRect)  self->operator+(pt);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((DuiEngine::CRect)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DuiEngine::CRect));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect__sub00
static int tolua_duiengine_DuiEngine_CRect__sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CRect",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"POINT",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DuiEngine::CRect* self = (const DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
  POINT pt = *((POINT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   DuiEngine::CRect tolua_ret = (DuiEngine::CRect)  self->operator-(pt);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((DuiEngine::CRect)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DuiEngine::CRect));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect__add01
static int tolua_duiengine_DuiEngine_CRect__add01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CRect",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"SIZE",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const DuiEngine::CRect* self = (const DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
  SIZE size = *((SIZE*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   DuiEngine::CRect tolua_ret = (DuiEngine::CRect)  self->operator+(size);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((DuiEngine::CRect)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DuiEngine::CRect));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CRect__add00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator- of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect__sub01
static int tolua_duiengine_DuiEngine_CRect__sub01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CRect",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"SIZE",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const DuiEngine::CRect* self = (const DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
  SIZE size = *((SIZE*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'", NULL);
#endif
  {
   DuiEngine::CRect tolua_ret = (DuiEngine::CRect)  self->operator-(size);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((DuiEngine::CRect)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DuiEngine::CRect));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_duiengine_DuiEngine_CRect__sub00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: MulDiv of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CRect_MulDiv00
static int tolua_duiengine_DuiEngine_CRect_MulDiv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::CRect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DuiEngine::CRect* self = (const DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
  int nMultiplier = ((int)  tolua_tonumber(tolua_S,2,0));
  int nDivisor = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MulDiv'", NULL);
#endif
  {
   DuiEngine::CRect tolua_ret = (DuiEngine::CRect)  self->MulDiv(nMultiplier,nDivisor);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((DuiEngine::CRect)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DuiEngine::CRect));
     tolua_pushusertype(tolua_S,tolua_obj,"DuiEngine::CRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MulDiv'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: left of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_get_DuiEngine__CRect_left
static int tolua_get_DuiEngine__CRect_left(lua_State* tolua_S)
{
  DuiEngine::CRect* self = (DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'left'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->left);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: left of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_set_DuiEngine__CRect_left
static int tolua_set_DuiEngine__CRect_left(lua_State* tolua_S)
{
  DuiEngine::CRect* self = (DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'left'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->left = ((  long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: top of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_get_DuiEngine__CRect_top
static int tolua_get_DuiEngine__CRect_top(lua_State* tolua_S)
{
  DuiEngine::CRect* self = (DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'top'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->top);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: top of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_set_DuiEngine__CRect_top
static int tolua_set_DuiEngine__CRect_top(lua_State* tolua_S)
{
  DuiEngine::CRect* self = (DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'top'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->top = ((  long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: right of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_get_DuiEngine__CRect_right
static int tolua_get_DuiEngine__CRect_right(lua_State* tolua_S)
{
  DuiEngine::CRect* self = (DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'right'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->right);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: right of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_set_DuiEngine__CRect_right
static int tolua_set_DuiEngine__CRect_right(lua_State* tolua_S)
{
  DuiEngine::CRect* self = (DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'right'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->right = ((  long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bottom of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_get_DuiEngine__CRect_bottom
static int tolua_get_DuiEngine__CRect_bottom(lua_State* tolua_S)
{
  DuiEngine::CRect* self = (DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bottom'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->bottom);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bottom of class  DuiEngine::CRect */
#ifndef TOLUA_DISABLE_tolua_set_DuiEngine__CRect_bottom
static int tolua_set_DuiEngine__CRect_bottom(lua_State* tolua_S)
{
  DuiEngine::CRect* self = (DuiEngine::CRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bottom'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bottom = ((  long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: LoadFromResource of class  DuiEngine::CDuiImgBase */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CDuiImgBase_LoadFromResource00
static int tolua_duiengine_DuiEngine_CDuiImgBase_LoadFromResource00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CDuiImgBase",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"HINSTANCE",0,&tolua_err)) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CDuiImgBase* self = (DuiEngine::CDuiImgBase*)  tolua_tousertype(tolua_S,1,0);
  HINSTANCE hInst = *((HINSTANCE*)  tolua_tousertype(tolua_S,2,0));
  const char* pszType = ((const char*)  tolua_tostring(tolua_S,3,0));
  unsigned int uID = (( unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoadFromResource'", NULL);
#endif
  {
    int tolua_ret = (  int)  self->LoadFromResource(hInst,pszType,uID);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoadFromResource'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LoadFromFile of class  DuiEngine::CDuiImgBase */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CDuiImgBase_LoadFromFile00
static int tolua_duiengine_DuiEngine_CDuiImgBase_LoadFromFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CDuiImgBase",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CDuiImgBase* self = (DuiEngine::CDuiImgBase*)  tolua_tousertype(tolua_S,1,0);
  const char* pszPath = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoadFromFile'", NULL);
#endif
  {
    int tolua_ret = (  int)  self->LoadFromFile(pszPath);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoadFromFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LoadFromMemory of class  DuiEngine::CDuiImgBase */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CDuiImgBase_LoadFromMemory00
static int tolua_duiengine_DuiEngine_CDuiImgBase_LoadFromMemory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CDuiImgBase",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CDuiImgBase* self = (DuiEngine::CDuiImgBase*)  tolua_tousertype(tolua_S,1,0);
   _userdata pBuf = ((  _userdata)  tolua_touserdata(tolua_S,2,0));
  unsigned long dwSize = (( unsigned long)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoadFromMemory'", NULL);
#endif
  {
    int tolua_ret = (  int)  self->LoadFromMemory(pBuf,dwSize);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoadFromMemory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetImageSize of class  DuiEngine::CDuiImgBase */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CDuiImgBase_GetImageSize00
static int tolua_duiengine_DuiEngine_CDuiImgBase_GetImageSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CDuiImgBase",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"SIZE",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CDuiImgBase* self = (DuiEngine::CDuiImgBase*)  tolua_tousertype(tolua_S,1,0);
  SIZE* sz = ((SIZE*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetImageSize'", NULL);
#endif
  {
    int tolua_ret = (  int)  self->GetImageSize(*sz);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetImageSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWidth of class  DuiEngine::CDuiImgBase */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CDuiImgBase_GetWidth00
static int tolua_duiengine_DuiEngine_CDuiImgBase_GetWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CDuiImgBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CDuiImgBase* self = (DuiEngine::CDuiImgBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWidth'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetWidth();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHeight of class  DuiEngine::CDuiImgBase */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CDuiImgBase_GetHeight00
static int tolua_duiengine_DuiEngine_CDuiImgBase_GetHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CDuiImgBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CDuiImgBase* self = (DuiEngine::CDuiImgBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHeight'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetHeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsEmpty of class  DuiEngine::CDuiImgBase */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CDuiImgBase_IsEmpty00
static int tolua_duiengine_DuiEngine_CDuiImgBase_IsEmpty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CDuiImgBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CDuiImgBase* self = (DuiEngine::CDuiImgBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsEmpty'", NULL);
#endif
  {
    int tolua_ret = (  int)  self->IsEmpty();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsEmpty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: BitBlt of class  DuiEngine::CDuiImgBase */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CDuiImgBase_BitBlt00
static int tolua_duiengine_DuiEngine_CDuiImgBase_BitBlt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CDuiImgBase",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"HDC",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,10,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CDuiImgBase* self = (DuiEngine::CDuiImgBase*)  tolua_tousertype(tolua_S,1,0);
  HDC hdc = *((HDC*)  tolua_tousertype(tolua_S,2,0));
  int x = ((int)  tolua_tonumber(tolua_S,3,0));
  int y = ((int)  tolua_tonumber(tolua_S,4,0));
  int nWid = ((int)  tolua_tonumber(tolua_S,5,0));
  int nHei = ((int)  tolua_tonumber(tolua_S,6,0));
  int xSrc = ((int)  tolua_tonumber(tolua_S,7,0));
  int ySrc = ((int)  tolua_tonumber(tolua_S,8,0));
  unsigned char byAlpha = (( unsigned char)  tolua_tonumber(tolua_S,9,0xFF));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BitBlt'", NULL);
#endif
  {
    int tolua_ret = (  int)  self->BitBlt(hdc,x,y,nWid,nHei,xSrc,ySrc,byAlpha);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BitBlt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: StretchBlt of class  DuiEngine::CDuiImgBase */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CDuiImgBase_StretchBlt00
static int tolua_duiengine_DuiEngine_CDuiImgBase_StretchBlt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CDuiImgBase",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"HDC",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,11,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,12,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CDuiImgBase* self = (DuiEngine::CDuiImgBase*)  tolua_tousertype(tolua_S,1,0);
  HDC hdc = *((HDC*)  tolua_tousertype(tolua_S,2,0));
  int x = ((int)  tolua_tonumber(tolua_S,3,0));
  int y = ((int)  tolua_tonumber(tolua_S,4,0));
  int nWid = ((int)  tolua_tonumber(tolua_S,5,0));
  int nHei = ((int)  tolua_tonumber(tolua_S,6,0));
  int xSrc = ((int)  tolua_tonumber(tolua_S,7,0));
  int ySrc = ((int)  tolua_tonumber(tolua_S,8,0));
  int nWidSrc = ((int)  tolua_tonumber(tolua_S,9,0));
  int nHeiSrc = ((int)  tolua_tonumber(tolua_S,10,0));
  unsigned char byAlpha = (( unsigned char)  tolua_tonumber(tolua_S,11,0xFF));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StretchBlt'", NULL);
#endif
  {
    int tolua_ret = (  int)  self->StretchBlt(hdc,x,y,nWid,nHei,xSrc,ySrc,nWidSrc,nHeiSrc,byAlpha);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StretchBlt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TileBlt of class  DuiEngine::CDuiImgBase */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CDuiImgBase_TileBlt00
static int tolua_duiengine_DuiEngine_CDuiImgBase_TileBlt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CDuiImgBase",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"HDC",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,11,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,12,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CDuiImgBase* self = (DuiEngine::CDuiImgBase*)  tolua_tousertype(tolua_S,1,0);
  HDC hdc = *((HDC*)  tolua_tousertype(tolua_S,2,0));
  int x = ((int)  tolua_tonumber(tolua_S,3,0));
  int y = ((int)  tolua_tonumber(tolua_S,4,0));
  int nWid = ((int)  tolua_tonumber(tolua_S,5,0));
  int nHei = ((int)  tolua_tonumber(tolua_S,6,0));
  int xSrc = ((int)  tolua_tonumber(tolua_S,7,0));
  int ySrc = ((int)  tolua_tonumber(tolua_S,8,0));
  int nWidSrc = ((int)  tolua_tonumber(tolua_S,9,0));
  int nHeiSrc = ((int)  tolua_tonumber(tolua_S,10,0));
  unsigned char byAlpha = (( unsigned char)  tolua_tonumber(tolua_S,11,0xFF));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TileBlt'", NULL);
#endif
  {
    int tolua_ret = (  int)  self->TileBlt(hdc,x,y,nWid,nHei,xSrc,ySrc,nWidSrc,nHeiSrc,byAlpha);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TileBlt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateDuiImage of class  DuiEngine::CDuiImgDecoder */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CDuiImgDecoder_CreateDuiImage00
static int tolua_duiengine_DuiEngine_CDuiImgDecoder_CreateDuiImage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CDuiImgDecoder",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CDuiImgDecoder* self = (DuiEngine::CDuiImgDecoder*)  tolua_tousertype(tolua_S,1,0);
   const _cstring pszType = ((  const _cstring)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateDuiImage'", NULL);
#endif
  {
   DuiEngine::CDuiImgBase* tolua_ret = (DuiEngine::CDuiImgBase*)  self->CreateDuiImage(pszType);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CDuiImgBase");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateDuiImage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DestoryDuiImage of class  DuiEngine::CDuiImgDecoder */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CDuiImgDecoder_DestoryDuiImage00
static int tolua_duiengine_DuiEngine_CDuiImgDecoder_DestoryDuiImage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CDuiImgDecoder",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"DuiEngine::CDuiImgBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CDuiImgDecoder* self = (DuiEngine::CDuiImgDecoder*)  tolua_tousertype(tolua_S,1,0);
  DuiEngine::CDuiImgBase* pImg = ((DuiEngine::CDuiImgBase*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DestoryDuiImage'", NULL);
#endif
  {
   self->DestoryDuiImage(pImg);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DestoryDuiImage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSupportTypes of class  DuiEngine::CDuiImgDecoder */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CDuiImgDecoder_GetSupportTypes00
static int tolua_duiengine_DuiEngine_CDuiImgDecoder_GetSupportTypes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CDuiImgDecoder",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CDuiImgDecoder* self = (DuiEngine::CDuiImgDecoder*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSupportTypes'", NULL);
#endif
  {
    const _cstring tolua_ret = (  const _cstring)  self->GetSupportTypes();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSupportTypes'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HasResource of class  DuiEngine::DuiResProviderBase */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_DuiResProviderBase_HasResource00
static int tolua_duiengine_DuiEngine_DuiResProviderBase_HasResource00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::DuiResProviderBase",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::DuiResProviderBase* self = (DuiEngine::DuiResProviderBase*)  tolua_tousertype(tolua_S,1,0);
  const char* strType = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned int uID = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HasResource'", NULL);
#endif
  {
    int tolua_ret = (  int)  self->HasResource(strType,uID);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HasResource'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LoadIcon of class  DuiEngine::DuiResProviderBase */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_DuiResProviderBase_LoadIcon00
static int tolua_duiengine_DuiEngine_DuiResProviderBase_LoadIcon00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::DuiResProviderBase",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::DuiResProviderBase* self = (DuiEngine::DuiResProviderBase*)  tolua_tousertype(tolua_S,1,0);
  const char* strType = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned int uID = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  int cx = ((int)  tolua_tonumber(tolua_S,4,0));
  int cy = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoadIcon'", NULL);
#endif
  {
   HICON tolua_ret = (HICON)  self->LoadIcon(strType,uID,cx,cy);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((HICON)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"HICON");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(HICON));
     tolua_pushusertype(tolua_S,tolua_obj,"HICON");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoadIcon'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LoadBitmap of class  DuiEngine::DuiResProviderBase */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_DuiResProviderBase_LoadBitmap00
static int tolua_duiengine_DuiEngine_DuiResProviderBase_LoadBitmap00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::DuiResProviderBase",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::DuiResProviderBase* self = (DuiEngine::DuiResProviderBase*)  tolua_tousertype(tolua_S,1,0);
  const char* strType = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned int uID = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoadBitmap'", NULL);
#endif
  {
   HBITMAP tolua_ret = (HBITMAP)  self->LoadBitmap(strType,uID);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((HBITMAP)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"HBITMAP");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(HBITMAP));
     tolua_pushusertype(tolua_S,tolua_obj,"HBITMAP");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoadBitmap'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LoadImage of class  DuiEngine::DuiResProviderBase */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_DuiResProviderBase_LoadImage00
static int tolua_duiengine_DuiEngine_DuiResProviderBase_LoadImage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::DuiResProviderBase",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::DuiResProviderBase* self = (DuiEngine::DuiResProviderBase*)  tolua_tousertype(tolua_S,1,0);
  const char* strType = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned int uID = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoadImage'", NULL);
#endif
  {
   DuiEngine::CDuiImgBase* tolua_ret = (DuiEngine::CDuiImgBase*)  self->LoadImage(strType,uID);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CDuiImgBase");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoadImage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRawBufferSize of class  DuiEngine::DuiResProviderBase */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_DuiResProviderBase_GetRawBufferSize00
static int tolua_duiengine_DuiEngine_DuiResProviderBase_GetRawBufferSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::DuiResProviderBase",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::DuiResProviderBase* self = (DuiEngine::DuiResProviderBase*)  tolua_tousertype(tolua_S,1,0);
  const char* strType = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned int uID = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRawBufferSize'", NULL);
#endif
  {
   unsigned long tolua_ret = ( unsigned long)  self->GetRawBufferSize(strType,uID);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRawBufferSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRawBuffer of class  DuiEngine::DuiResProviderBase */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_DuiResProviderBase_GetRawBuffer00
static int tolua_duiengine_DuiEngine_DuiResProviderBase_GetRawBuffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::DuiResProviderBase",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::DuiResProviderBase* self = (DuiEngine::DuiResProviderBase*)  tolua_tousertype(tolua_S,1,0);
  const char* strType = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned int uID = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  void* pBuf = ((void*)  tolua_touserdata(tolua_S,4,0));
  unsigned long size = (( unsigned long)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRawBuffer'", NULL);
#endif
  {
    int tolua_ret = (  int)  self->GetRawBuffer(strType,uID,pBuf,size);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRawBuffer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetImageDecoder of class  DuiEngine::DuiResProviderBase */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_DuiResProviderBase_GetImageDecoder00
static int tolua_duiengine_DuiEngine_DuiResProviderBase_GetImageDecoder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::DuiResProviderBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::DuiResProviderBase* self = (DuiEngine::DuiResProviderBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetImageDecoder'", NULL);
#endif
  {
   DuiEngine::CDuiImgDecoder* tolua_ret = (DuiEngine::CDuiImgDecoder*)  self->GetImageDecoder();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CDuiImgDecoder");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetImageDecoder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLoggingLevel of class  DuiEngine::DuiLogger */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_DuiLogger_setLoggingLevel00
static int tolua_duiengine_DuiEngine_DuiLogger_setLoggingLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::DuiLogger",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::DuiLogger* self = (DuiEngine::DuiLogger*)  tolua_tousertype(tolua_S,1,0);
  DuiEngine::LoggingLevel level = ((DuiEngine::LoggingLevel) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLoggingLevel'", NULL);
#endif
  {
   self->setLoggingLevel(level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLoggingLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLoggingLevel of class  DuiEngine::DuiLogger */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_DuiLogger_getLoggingLevel00
static int tolua_duiengine_DuiEngine_DuiLogger_getLoggingLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::DuiLogger",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DuiEngine::DuiLogger* self = (const DuiEngine::DuiLogger*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLoggingLevel'", NULL);
#endif
  {
   DuiEngine::LoggingLevel tolua_ret = (DuiEngine::LoggingLevel)  self->getLoggingLevel();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLoggingLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: logEvent of class  DuiEngine::DuiLogger */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_DuiLogger_logEvent00
static int tolua_duiengine_DuiEngine_DuiLogger_logEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::DuiLogger",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"LPCTSTR",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::DuiLogger* self = (DuiEngine::DuiLogger*)  tolua_tousertype(tolua_S,1,0);
  LPCTSTR tolua_var_1 = *((LPCTSTR*)  tolua_tousertype(tolua_S,2,0));
  DuiEngine::LoggingLevel level = ((DuiEngine::LoggingLevel) (int)  tolua_tonumber(tolua_S,3,DuiEngine::Standard));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'logEvent'", NULL);
#endif
  {
   self->logEvent(tolua_var_1,level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'logEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLogFilename of class  DuiEngine::DuiLogger */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_DuiLogger_setLogFilename00
static int tolua_duiengine_DuiEngine_DuiLogger_setLogFilename00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::DuiLogger",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"LPCTSTR",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::DuiLogger* self = (DuiEngine::DuiLogger*)  tolua_tousertype(tolua_S,1,0);
  LPCTSTR filename = *((LPCTSTR*)  tolua_tousertype(tolua_S,2,0));
  bool append = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLogFilename'", NULL);
#endif
  {
   self->setLogFilename(filename,append);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLogFilename'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetScriptEngine of class  DuiEngine::IScriptModule */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_IScriptModule_GetScriptEngine00
static int tolua_duiengine_DuiEngine_IScriptModule_GetScriptEngine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::IScriptModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::IScriptModule* self = (DuiEngine::IScriptModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetScriptEngine'", NULL);
#endif
  {
   void* tolua_ret = (void*)  self->GetScriptEngine();
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetScriptEngine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadScriptFile of class  DuiEngine::IScriptModule */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_IScriptModule_loadScriptFile00
static int tolua_duiengine_DuiEngine_IScriptModule_loadScriptFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::IScriptModule",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::IScriptModule* self = (DuiEngine::IScriptModule*)  tolua_tousertype(tolua_S,1,0);
   const _cstring pszScriptFile = ((  const _cstring)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadScriptFile'", NULL);
#endif
  {
   int tolua_ret = (int)  self->loadScriptFile(pszScriptFile);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadScriptFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: loadScriptString of class  DuiEngine::IScriptModule */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_IScriptModule_loadScriptString00
static int tolua_duiengine_DuiEngine_IScriptModule_loadScriptString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::IScriptModule",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::IScriptModule* self = (DuiEngine::IScriptModule*)  tolua_tousertype(tolua_S,1,0);
   const _cstring pszScriptStr = ((  const _cstring)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadScriptString'", NULL);
#endif
  {
   int tolua_ret = (int)  self->loadScriptString(pszScriptStr);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadScriptString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: executeScriptFile of class  DuiEngine::IScriptModule */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_IScriptModule_executeScriptFile00
static int tolua_duiengine_DuiEngine_IScriptModule_executeScriptFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::IScriptModule",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::IScriptModule* self = (DuiEngine::IScriptModule*)  tolua_tousertype(tolua_S,1,0);
   const _cstring pszScriptFile = ((  const _cstring)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'executeScriptFile'", NULL);
#endif
  {
   self->executeScriptFile(pszScriptFile);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'executeScriptFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: executeScriptedEventHandler of class  DuiEngine::IScriptModule */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_IScriptModule_executeScriptedEventHandler00
static int tolua_duiengine_DuiEngine_IScriptModule_executeScriptedEventHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::IScriptModule",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"DuiEngine::CDuiWindow",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"LPNMHDR",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::IScriptModule* self = (DuiEngine::IScriptModule*)  tolua_tousertype(tolua_S,1,0);
   const _cstring handler_name = ((  const _cstring)  tolua_tostring(tolua_S,2,0));
  DuiEngine::CDuiWindow* pSender = ((DuiEngine::CDuiWindow*)  tolua_tousertype(tolua_S,3,0));
  LPNMHDR pNmhdr = *((LPNMHDR*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'executeScriptedEventHandler'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->executeScriptedEventHandler(handler_name,pSender,pNmhdr);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'executeScriptedEventHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: executeString of class  DuiEngine::IScriptModule */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_IScriptModule_executeString00
static int tolua_duiengine_DuiEngine_IScriptModule_executeString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::IScriptModule",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::IScriptModule* self = (DuiEngine::IScriptModule*)  tolua_tousertype(tolua_S,1,0);
   const _cstring str = ((  const _cstring)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'executeString'", NULL);
#endif
  {
   self->executeString(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'executeString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIdentifierString of class  DuiEngine::IScriptModule */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_IScriptModule_getIdentifierString00
static int tolua_duiengine_DuiEngine_IScriptModule_getIdentifierString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DuiEngine::IScriptModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DuiEngine::IScriptModule* self = (const DuiEngine::IScriptModule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIdentifierString'", NULL);
#endif
  {
    const _cstring tolua_ret = (  const _cstring)  self->getIdentifierString();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIdentifierString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: subscribeEvent of class  DuiEngine::IScriptModule */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_IScriptModule_subscribeEvent00
static int tolua_duiengine_DuiEngine_IScriptModule_subscribeEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::IScriptModule",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"DuiEngine::CDuiWindow",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::IScriptModule* self = (DuiEngine::IScriptModule*)  tolua_tousertype(tolua_S,1,0);
  DuiEngine::CDuiWindow* target = ((DuiEngine::CDuiWindow*)  tolua_tousertype(tolua_S,2,0));
  unsigned int uEvent = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
   const _cstring subscriber_name = ((  const _cstring)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'subscribeEvent'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->subscribeEvent(target,uEvent,subscriber_name);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'subscribeEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInstance of class  DuiEngine::DuiSystem */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_DuiSystem_GetInstance00
static int tolua_duiengine_DuiEngine_DuiSystem_GetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::DuiSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::DuiSystem* self = (DuiEngine::DuiSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInstance'", NULL);
#endif
  {
   HINSTANCE tolua_ret = (HINSTANCE)  self->GetInstance();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((HINSTANCE)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"HINSTANCE");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(HINSTANCE));
     tolua_pushusertype(tolua_S,tolua_obj,"HINSTANCE");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetResProvider of class  DuiEngine::DuiSystem */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_DuiSystem_SetResProvider00
static int tolua_duiengine_DuiEngine_DuiSystem_SetResProvider00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::DuiSystem",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"DuiEngine::DuiResProviderBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::DuiSystem* self = (DuiEngine::DuiSystem*)  tolua_tousertype(tolua_S,1,0);
  DuiEngine::DuiResProviderBase* pNewResProvider = ((DuiEngine::DuiResProviderBase*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetResProvider'", NULL);
#endif
  {
   DuiEngine::DuiResProviderBase* tolua_ret = (DuiEngine::DuiResProviderBase*)  self->SetResProvider(pNewResProvider);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::DuiResProviderBase");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetResProvider'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetResProvider of class  DuiEngine::DuiSystem */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_DuiSystem_GetResProvider00
static int tolua_duiengine_DuiEngine_DuiSystem_GetResProvider00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::DuiSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::DuiSystem* self = (DuiEngine::DuiSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetResProvider'", NULL);
#endif
  {
   DuiEngine::DuiResProviderBase* tolua_ret = (DuiEngine::DuiResProviderBase*)  self->GetResProvider();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::DuiResProviderBase");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetResProvider'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLogger of class  DuiEngine::DuiSystem */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_DuiSystem_SetLogger00
static int tolua_duiengine_DuiEngine_DuiSystem_SetLogger00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::DuiSystem",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"DuiEngine::DuiLogger",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::DuiSystem* self = (DuiEngine::DuiSystem*)  tolua_tousertype(tolua_S,1,0);
  DuiEngine::DuiLogger* pLogger = ((DuiEngine::DuiLogger*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLogger'", NULL);
#endif
  {
   DuiEngine::DuiLogger* tolua_ret = (DuiEngine::DuiLogger*)  self->SetLogger(pLogger);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::DuiLogger");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLogger'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLogger of class  DuiEngine::DuiSystem */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_DuiSystem_GetLogger00
static int tolua_duiengine_DuiEngine_DuiSystem_GetLogger00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::DuiSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::DuiSystem* self = (DuiEngine::DuiSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLogger'", NULL);
#endif
  {
   DuiEngine::DuiLogger* tolua_ret = (DuiEngine::DuiLogger*)  self->GetLogger();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::DuiLogger");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLogger'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: logEvent of class  DuiEngine::DuiSystem */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_DuiSystem_logEvent00
static int tolua_duiengine_DuiEngine_DuiSystem_logEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::DuiSystem",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"LPCTSTR",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::DuiSystem* self = (DuiEngine::DuiSystem*)  tolua_tousertype(tolua_S,1,0);
  LPCTSTR message = *((LPCTSTR*)  tolua_tousertype(tolua_S,2,0));
  DuiEngine::LoggingLevel level = ((DuiEngine::LoggingLevel) (int)  tolua_tonumber(tolua_S,3,DuiEngine::Standard));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'logEvent'", NULL);
#endif
  {
   self->logEvent(message,level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'logEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Name2ID of class  DuiEngine::DuiSystem */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_DuiSystem_Name2ID00
static int tolua_duiengine_DuiEngine_DuiSystem_Name2ID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::DuiSystem",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::DuiSystem* self = (DuiEngine::DuiSystem*)  tolua_tousertype(tolua_S,1,0);
   const _cstring strName = ((  const _cstring)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Name2ID'", NULL);
#endif
  {
   unsigned int tolua_ret = ( unsigned int)  self->Name2ID(strName);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Name2ID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InitName2ID of class  DuiEngine::DuiSystem */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_DuiSystem_InitName2ID00
static int tolua_duiengine_DuiEngine_DuiSystem_InitName2ID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::DuiSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::DuiSystem* self = (DuiEngine::DuiSystem*)  tolua_tousertype(tolua_S,1,0);
  unsigned int uXmlResID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
   const _cstring pszType = ((  const _cstring)  tolua_tostring(tolua_S,3,DUIRES_XML_TYPE));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InitName2ID'", NULL);
#endif
  {
   unsigned long tolua_ret = ( unsigned long)  self->InitName2ID(uXmlResID,pszType);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InitName2ID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Init of class  DuiEngine::DuiSystem */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_DuiSystem_Init00
static int tolua_duiengine_DuiEngine_DuiSystem_Init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::DuiSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::DuiSystem* self = (DuiEngine::DuiSystem*)  tolua_tousertype(tolua_S,1,0);
  unsigned int uXmlResID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
   const _cstring pszType = ((  const _cstring)  tolua_tostring(tolua_S,3,DUIRES_XML_TYPE));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Init'", NULL);
#endif
  {
    int tolua_ret = (  int)  self->Init(uXmlResID,pszType);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMsgBoxTemplate of class  DuiEngine::DuiSystem */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_DuiSystem_SetMsgBoxTemplate00
static int tolua_duiengine_DuiEngine_DuiSystem_SetMsgBoxTemplate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::DuiSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::DuiSystem* self = (DuiEngine::DuiSystem*)  tolua_tousertype(tolua_S,1,0);
  unsigned int uXmlResID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
   const _cstring pszType = ((  const _cstring)  tolua_tostring(tolua_S,3,DUIRES_XML_TYPE));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMsgBoxTemplate'", NULL);
#endif
  {
    int tolua_ret = (  int)  self->SetMsgBoxTemplate(uXmlResID,pszType);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMsgBoxTemplate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetScriptModule of class  DuiEngine::DuiSystem */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_DuiSystem_GetScriptModule00
static int tolua_duiengine_DuiEngine_DuiSystem_GetScriptModule00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::DuiSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::DuiSystem* self = (DuiEngine::DuiSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetScriptModule'", NULL);
#endif
  {
   DuiEngine::IScriptModule* tolua_ret = (DuiEngine::IScriptModule*)  self->GetScriptModule();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::IScriptModule");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetScriptModule'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetScriptModule of class  DuiEngine::DuiSystem */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_DuiSystem_SetScriptModule00
static int tolua_duiengine_DuiEngine_DuiSystem_SetScriptModule00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::DuiSystem",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"DuiEngine::IScriptModule",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::DuiSystem* self = (DuiEngine::DuiSystem*)  tolua_tousertype(tolua_S,1,0);
  DuiEngine::IScriptModule* pScriptModule = ((DuiEngine::IScriptModule*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetScriptModule'", NULL);
#endif
  {
   DuiEngine::IScriptModule* tolua_ret = (DuiEngine::IScriptModule*)  self->SetScriptModule(pScriptModule);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::IScriptModule");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetScriptModule'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSingletonPtr of class  DuiEngine::DuiSystem */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_DuiSystem_getSingletonPtr00
static int tolua_duiengine_DuiEngine_DuiSystem_getSingletonPtr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::DuiSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DuiEngine::DuiSystem* tolua_ret = (DuiEngine::DuiSystem*)  DuiEngine::DuiSystem::getSingletonPtr();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::DuiSystem");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSingletonPtr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  DuiEngine::CDuiWindow */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CDuiWindow_new00
static int tolua_duiengine_DuiEngine_CDuiWindow_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CDuiWindow",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DuiEngine::CDuiWindow* tolua_ret = (DuiEngine::CDuiWindow*)  Mtolua_new((DuiEngine::CDuiWindow)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CDuiWindow");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  DuiEngine::CDuiWindow */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CDuiWindow_new00_local
static int tolua_duiengine_DuiEngine_CDuiWindow_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DuiEngine::CDuiWindow",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DuiEngine::CDuiWindow* tolua_ret = (DuiEngine::CDuiWindow*)  Mtolua_new((DuiEngine::CDuiWindow)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CDuiWindow");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  DuiEngine::CDuiWindow */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CDuiWindow_delete00
static int tolua_duiengine_DuiEngine_CDuiWindow_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CDuiWindow",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CDuiWindow* self = (DuiEngine::CDuiWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetParent of class  DuiEngine::CDuiWindow */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CDuiWindow_GetParent00
static int tolua_duiengine_DuiEngine_CDuiWindow_GetParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CDuiWindow",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CDuiWindow* self = (DuiEngine::CDuiWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetParent'", NULL);
#endif
  {
   DuiEngine::CDuiWindow* tolua_ret = (DuiEngine::CDuiWindow*)  self->GetParent();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CDuiWindow");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetParent of class  DuiEngine::CDuiWindow */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CDuiWindow_SetParent00
static int tolua_duiengine_DuiEngine_CDuiWindow_SetParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CDuiWindow",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"DuiEngine::CDuiWindow",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CDuiWindow* self = (DuiEngine::CDuiWindow*)  tolua_tousertype(tolua_S,1,0);
  DuiEngine::CDuiWindow* pParent = ((DuiEngine::CDuiWindow*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetParent'", NULL);
#endif
  {
   self->SetParent(pParent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTopLevelParent of class  DuiEngine::CDuiWindow */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CDuiWindow_GetTopLevelParent00
static int tolua_duiengine_DuiEngine_CDuiWindow_GetTopLevelParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CDuiWindow",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CDuiWindow* self = (DuiEngine::CDuiWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTopLevelParent'", NULL);
#endif
  {
   DuiEngine::CDuiWindow* tolua_ret = (DuiEngine::CDuiWindow*)  self->GetTopLevelParent();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CDuiWindow");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTopLevelParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DestroyChild of class  DuiEngine::CDuiWindow */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CDuiWindow_DestroyChild00
static int tolua_duiengine_DuiEngine_CDuiWindow_DestroyChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CDuiWindow",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"DuiEngine::CDuiWindow",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CDuiWindow* self = (DuiEngine::CDuiWindow*)  tolua_tousertype(tolua_S,1,0);
  DuiEngine::CDuiWindow* pChild = ((DuiEngine::CDuiWindow*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DestroyChild'", NULL);
#endif
  {
    int tolua_ret = (  int)  self->DestroyChild(pChild);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DestroyChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetChildrenCount of class  DuiEngine::CDuiWindow */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CDuiWindow_GetChildrenCount00
static int tolua_duiengine_DuiEngine_CDuiWindow_GetChildrenCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CDuiWindow",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CDuiWindow* self = (DuiEngine::CDuiWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetChildrenCount'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetChildrenCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetChildrenCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetChild of class  DuiEngine::CDuiWindow */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CDuiWindow_GetChild00
static int tolua_duiengine_DuiEngine_CDuiWindow_GetChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CDuiWindow",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CDuiWindow* self = (DuiEngine::CDuiWindow*)  tolua_tousertype(tolua_S,1,0);
  unsigned int uCmdID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetChild'", NULL);
#endif
  {
   DuiEngine::CDuiWindow* tolua_ret = (DuiEngine::CDuiWindow*)  self->GetChild(uCmdID);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CDuiWindow");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindChildByCmdID of class  DuiEngine::CDuiWindow */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CDuiWindow_FindChildByCmdID00
static int tolua_duiengine_DuiEngine_CDuiWindow_FindChildByCmdID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CDuiWindow",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CDuiWindow* self = (DuiEngine::CDuiWindow*)  tolua_tousertype(tolua_S,1,0);
  unsigned int uCmdID = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindChildByCmdID'", NULL);
#endif
  {
   DuiEngine::CDuiWindow* tolua_ret = (DuiEngine::CDuiWindow*)  self->FindChildByCmdID(uCmdID);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CDuiWindow");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindChildByCmdID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindChildByName of class  DuiEngine::CDuiWindow */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CDuiWindow_FindChildByName00
static int tolua_duiengine_DuiEngine_CDuiWindow_FindChildByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CDuiWindow",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CDuiWindow* self = (DuiEngine::CDuiWindow*)  tolua_tousertype(tolua_S,1,0);
  const char* pszName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindChildByName'", NULL);
#endif
  {
   DuiEngine::CDuiWindow* tolua_ret = (DuiEngine::CDuiWindow*)  self->FindChildByName(pszName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CDuiWindow");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindChildByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LoadXmlChildren of class  DuiEngine::CDuiWindow */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_CDuiWindow_LoadXmlChildren00
static int tolua_duiengine_DuiEngine_CDuiWindow_LoadXmlChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DuiEngine::CDuiWindow",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DuiEngine::CDuiWindow* self = (DuiEngine::CDuiWindow*)  tolua_tousertype(tolua_S,1,0);
  const char* utf8Xml = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoadXmlChildren'", NULL);
#endif
  {
   DuiEngine::CDuiWindow* tolua_ret = (DuiEngine::CDuiWindow*)  self->LoadXmlChildren(utf8Xml);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DuiEngine::CDuiWindow");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoadXmlChildren'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DuiEngine::DuiMessageBox */
#ifndef TOLUA_DISABLE_tolua_duiengine_DuiEngine_DuiMessageBox00
static int tolua_duiengine_DuiEngine_DuiMessageBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"HWND",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"LPCTSTR",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"LPCTSTR",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  HWND hWnd = *((HWND*)  tolua_tousertype(tolua_S,1,0));
  LPCTSTR lpText = *((LPCTSTR*)  tolua_tousertype(tolua_S,2,0));
  LPCTSTR lpCaption = *((LPCTSTR*)  tolua_tousertype(tolua_S,3,0));
  unsigned int uType = (( unsigned int)  tolua_tonumber(tolua_S,4,MB_OK));
  {
   int tolua_ret = (int)  DuiEngine::DuiMessageBox(hWnd,lpText,lpCaption,uType);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DuiMessageBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_duiengine_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"MB_OK",MB_OK);
  tolua_constant(tolua_S,"MB_OKCANCEL",MB_OKCANCEL);
  tolua_constant(tolua_S,"MB_ABORTRETRYIGNORE",MB_ABORTRETRYIGNORE);
  tolua_constant(tolua_S,"MB_YESNOCANCEL",MB_YESNOCANCEL);
  tolua_constant(tolua_S,"MB_YESNO",MB_YESNO);
  tolua_constant(tolua_S,"MB_RETRYCANCEL",MB_RETRYCANCEL);
  tolua_constant(tolua_S,"MB_CANCELTRYCONTINUE",MB_CANCELTRYCONTINUE);
  tolua_constant(tolua_S,"MB_ICONHAND",MB_ICONHAND);
  tolua_constant(tolua_S,"MB_ICONQUESTION",MB_ICONQUESTION);
  tolua_constant(tolua_S,"MB_ICONEXCLAMATION",MB_ICONEXCLAMATION);
  tolua_constant(tolua_S,"MB_ICONASTERISK",MB_ICONASTERISK);
  tolua_cclass(tolua_S,"SIZE","SIZE","",NULL);
  tolua_beginmodule(tolua_S,"SIZE");
   tolua_variable(tolua_S,"cx",tolua_get_SIZE_cx,tolua_set_SIZE_cx);
   tolua_variable(tolua_S,"cy",tolua_get_SIZE_cy,tolua_set_SIZE_cy);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"POINT","POINT","",NULL);
  tolua_beginmodule(tolua_S,"POINT");
   tolua_variable(tolua_S,"x",tolua_get_POINT_x,tolua_set_POINT_x);
   tolua_variable(tolua_S,"y",tolua_get_POINT_y,tolua_set_POINT_y);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"RECT","RECT","",NULL);
  tolua_beginmodule(tolua_S,"RECT");
   tolua_variable(tolua_S,"left",tolua_get_RECT_left,tolua_set_RECT_left);
   tolua_variable(tolua_S,"top",tolua_get_RECT_top,tolua_set_RECT_top);
   tolua_variable(tolua_S,"right",tolua_get_RECT_right,tolua_set_RECT_right);
   tolua_variable(tolua_S,"bottom",tolua_get_RECT_bottom,tolua_set_RECT_bottom);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"NMHDR","NMHDR","",NULL);
  tolua_beginmodule(tolua_S,"NMHDR");
   tolua_variable(tolua_S,"hwndFrom",tolua_get_NMHDR_hwndFrom,tolua_set_NMHDR_hwndFrom);
   tolua_variable(tolua_S,"idFrom",tolua_get_NMHDR_unsigned_idFrom,tolua_set_NMHDR_unsigned_idFrom);
   tolua_variable(tolua_S,"code",tolua_get_NMHDR_unsigned_code,tolua_set_NMHDR_unsigned_code);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"DuiEngine",0);
  tolua_beginmodule(tolua_S,"DuiEngine");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"CSize","DuiEngine::CSize","SIZE",tolua_collect_DuiEngine__CSize);
   #else
   tolua_cclass(tolua_S,"CSize","DuiEngine::CSize","SIZE",NULL);
   #endif
   tolua_beginmodule(tolua_S,"CSize");
    tolua_function(tolua_S,"new",tolua_duiengine_DuiEngine_CSize_new00);
    tolua_function(tolua_S,"new_local",tolua_duiengine_DuiEngine_CSize_new00_local);
    tolua_function(tolua_S,".call",tolua_duiengine_DuiEngine_CSize_new00_local);
    tolua_function(tolua_S,"new",tolua_duiengine_DuiEngine_CSize_new01);
    tolua_function(tolua_S,"new_local",tolua_duiengine_DuiEngine_CSize_new01_local);
    tolua_function(tolua_S,".call",tolua_duiengine_DuiEngine_CSize_new01_local);
    tolua_function(tolua_S,"new",tolua_duiengine_DuiEngine_CSize_new02);
    tolua_function(tolua_S,"new_local",tolua_duiengine_DuiEngine_CSize_new02_local);
    tolua_function(tolua_S,".call",tolua_duiengine_DuiEngine_CSize_new02_local);
    tolua_function(tolua_S,"new",tolua_duiengine_DuiEngine_CSize_new03);
    tolua_function(tolua_S,"new_local",tolua_duiengine_DuiEngine_CSize_new03_local);
    tolua_function(tolua_S,".call",tolua_duiengine_DuiEngine_CSize_new03_local);
    tolua_function(tolua_S,"new",tolua_duiengine_DuiEngine_CSize_new04);
    tolua_function(tolua_S,"new_local",tolua_duiengine_DuiEngine_CSize_new04_local);
    tolua_function(tolua_S,".call",tolua_duiengine_DuiEngine_CSize_new04_local);
    tolua_function(tolua_S,".eq",tolua_duiengine_DuiEngine_CSize__eq00);
    tolua_function(tolua_S,"SetSize",tolua_duiengine_DuiEngine_CSize_SetSize00);
    tolua_function(tolua_S,".add",tolua_duiengine_DuiEngine_CSize__add00);
    tolua_function(tolua_S,".sub",tolua_duiengine_DuiEngine_CSize__sub00);
    tolua_function(tolua_S,".sub",tolua_duiengine_DuiEngine_CSize__sub01);
    tolua_function(tolua_S,".add",tolua_duiengine_DuiEngine_CSize__add01);
    tolua_function(tolua_S,".sub",tolua_duiengine_DuiEngine_CSize__sub02);
    tolua_function(tolua_S,".add",tolua_duiengine_DuiEngine_CSize__add02);
    tolua_function(tolua_S,".sub",tolua_duiengine_DuiEngine_CSize__sub03);
    tolua_variable(tolua_S,"cx",tolua_get_DuiEngine__CSize_cx,tolua_set_DuiEngine__CSize_cx);
    tolua_variable(tolua_S,"cy",tolua_get_DuiEngine__CSize_cy,tolua_set_DuiEngine__CSize_cy);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"CPoint","DuiEngine::CPoint","POINT",tolua_collect_DuiEngine__CPoint);
   #else
   tolua_cclass(tolua_S,"CPoint","DuiEngine::CPoint","POINT",NULL);
   #endif
   tolua_beginmodule(tolua_S,"CPoint");
    tolua_function(tolua_S,"new",tolua_duiengine_DuiEngine_CPoint_new00);
    tolua_function(tolua_S,"new_local",tolua_duiengine_DuiEngine_CPoint_new00_local);
    tolua_function(tolua_S,".call",tolua_duiengine_DuiEngine_CPoint_new00_local);
    tolua_function(tolua_S,"new",tolua_duiengine_DuiEngine_CPoint_new01);
    tolua_function(tolua_S,"new_local",tolua_duiengine_DuiEngine_CPoint_new01_local);
    tolua_function(tolua_S,".call",tolua_duiengine_DuiEngine_CPoint_new01_local);
    tolua_function(tolua_S,"new",tolua_duiengine_DuiEngine_CPoint_new02);
    tolua_function(tolua_S,"new_local",tolua_duiengine_DuiEngine_CPoint_new02_local);
    tolua_function(tolua_S,".call",tolua_duiengine_DuiEngine_CPoint_new02_local);
    tolua_function(tolua_S,"new",tolua_duiengine_DuiEngine_CPoint_new03);
    tolua_function(tolua_S,"new_local",tolua_duiengine_DuiEngine_CPoint_new03_local);
    tolua_function(tolua_S,".call",tolua_duiengine_DuiEngine_CPoint_new03_local);
    tolua_function(tolua_S,"new",tolua_duiengine_DuiEngine_CPoint_new04);
    tolua_function(tolua_S,"new_local",tolua_duiengine_DuiEngine_CPoint_new04_local);
    tolua_function(tolua_S,".call",tolua_duiengine_DuiEngine_CPoint_new04_local);
    tolua_function(tolua_S,"Offset",tolua_duiengine_DuiEngine_CPoint_Offset00);
    tolua_function(tolua_S,"Offset",tolua_duiengine_DuiEngine_CPoint_Offset01);
    tolua_function(tolua_S,"Offset",tolua_duiengine_DuiEngine_CPoint_Offset02);
    tolua_function(tolua_S,".eq",tolua_duiengine_DuiEngine_CPoint__eq00);
    tolua_function(tolua_S,"SetPoint",tolua_duiengine_DuiEngine_CPoint_SetPoint00);
    tolua_function(tolua_S,".add",tolua_duiengine_DuiEngine_CPoint__add00);
    tolua_function(tolua_S,".sub",tolua_duiengine_DuiEngine_CPoint__sub00);
    tolua_function(tolua_S,".sub",tolua_duiengine_DuiEngine_CPoint__sub01);
    tolua_function(tolua_S,".add",tolua_duiengine_DuiEngine_CPoint__add01);
    tolua_function(tolua_S,".sub",tolua_duiengine_DuiEngine_CPoint__sub02);
    tolua_variable(tolua_S,"x",tolua_get_DuiEngine__CPoint_x,tolua_set_DuiEngine__CPoint_x);
    tolua_variable(tolua_S,"y",tolua_get_DuiEngine__CPoint_y,tolua_set_DuiEngine__CPoint_y);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"CRect","DuiEngine::CRect","RECT",tolua_collect_DuiEngine__CRect);
   #else
   tolua_cclass(tolua_S,"CRect","DuiEngine::CRect","RECT",NULL);
   #endif
   tolua_beginmodule(tolua_S,"CRect");
    tolua_function(tolua_S,"new",tolua_duiengine_DuiEngine_CRect_new00);
    tolua_function(tolua_S,"new_local",tolua_duiengine_DuiEngine_CRect_new00_local);
    tolua_function(tolua_S,".call",tolua_duiengine_DuiEngine_CRect_new00_local);
    tolua_function(tolua_S,"new",tolua_duiengine_DuiEngine_CRect_new01);
    tolua_function(tolua_S,"new_local",tolua_duiengine_DuiEngine_CRect_new01_local);
    tolua_function(tolua_S,".call",tolua_duiengine_DuiEngine_CRect_new01_local);
    tolua_function(tolua_S,"new",tolua_duiengine_DuiEngine_CRect_new02);
    tolua_function(tolua_S,"new_local",tolua_duiengine_DuiEngine_CRect_new02_local);
    tolua_function(tolua_S,".call",tolua_duiengine_DuiEngine_CRect_new02_local);
    tolua_function(tolua_S,"new",tolua_duiengine_DuiEngine_CRect_new03);
    tolua_function(tolua_S,"new_local",tolua_duiengine_DuiEngine_CRect_new03_local);
    tolua_function(tolua_S,".call",tolua_duiengine_DuiEngine_CRect_new03_local);
    tolua_function(tolua_S,"new",tolua_duiengine_DuiEngine_CRect_new04);
    tolua_function(tolua_S,"new_local",tolua_duiengine_DuiEngine_CRect_new04_local);
    tolua_function(tolua_S,".call",tolua_duiengine_DuiEngine_CRect_new04_local);
    tolua_function(tolua_S,"Width",tolua_duiengine_DuiEngine_CRect_Width00);
    tolua_function(tolua_S,"Height",tolua_duiengine_DuiEngine_CRect_Height00);
    tolua_function(tolua_S,"Size",tolua_duiengine_DuiEngine_CRect_Size00);
    tolua_function(tolua_S,"TopLeft",tolua_duiengine_DuiEngine_CRect_TopLeft00);
    tolua_function(tolua_S,"BottomRight",tolua_duiengine_DuiEngine_CRect_BottomRight00);
    tolua_function(tolua_S,"TopLeft",tolua_duiengine_DuiEngine_CRect_TopLeft01);
    tolua_function(tolua_S,"BottomRight",tolua_duiengine_DuiEngine_CRect_BottomRight01);
    tolua_function(tolua_S,"CenterPoint",tolua_duiengine_DuiEngine_CRect_CenterPoint00);
    tolua_function(tolua_S,"IsRectEmpty",tolua_duiengine_DuiEngine_CRect_IsRectEmpty00);
    tolua_function(tolua_S,"IsRectNull",tolua_duiengine_DuiEngine_CRect_IsRectNull00);
    tolua_function(tolua_S,"PtInRect",tolua_duiengine_DuiEngine_CRect_PtInRect00);
    tolua_function(tolua_S,"SetRect",tolua_duiengine_DuiEngine_CRect_SetRect00);
    tolua_function(tolua_S,"SetRect",tolua_duiengine_DuiEngine_CRect_SetRect01);
    tolua_function(tolua_S,"SetRectEmpty",tolua_duiengine_DuiEngine_CRect_SetRectEmpty00);
    tolua_function(tolua_S,"InflateRect",tolua_duiengine_DuiEngine_CRect_InflateRect00);
    tolua_function(tolua_S,"InflateRect",tolua_duiengine_DuiEngine_CRect_InflateRect01);
    tolua_function(tolua_S,"InflateRect",tolua_duiengine_DuiEngine_CRect_InflateRect02);
    tolua_function(tolua_S,"DeflateRect",tolua_duiengine_DuiEngine_CRect_DeflateRect00);
    tolua_function(tolua_S,"DeflateRect",tolua_duiengine_DuiEngine_CRect_DeflateRect01);
    tolua_function(tolua_S,"DeflateRect",tolua_duiengine_DuiEngine_CRect_DeflateRect02);
    tolua_function(tolua_S,"OffsetRect",tolua_duiengine_DuiEngine_CRect_OffsetRect00);
    tolua_function(tolua_S,"OffsetRect",tolua_duiengine_DuiEngine_CRect_OffsetRect01);
    tolua_function(tolua_S,"OffsetRect",tolua_duiengine_DuiEngine_CRect_OffsetRect02);
    tolua_function(tolua_S,"NormalizeRect",tolua_duiengine_DuiEngine_CRect_NormalizeRect00);
    tolua_function(tolua_S,"MoveToY",tolua_duiengine_DuiEngine_CRect_MoveToY00);
    tolua_function(tolua_S,"MoveToX",tolua_duiengine_DuiEngine_CRect_MoveToX00);
    tolua_function(tolua_S,"MoveToXY",tolua_duiengine_DuiEngine_CRect_MoveToXY00);
    tolua_function(tolua_S,"MoveToXY",tolua_duiengine_DuiEngine_CRect_MoveToXY01);
    tolua_function(tolua_S,".eq",tolua_duiengine_DuiEngine_CRect__eq00);
    tolua_function(tolua_S,".add",tolua_duiengine_DuiEngine_CRect__add00);
    tolua_function(tolua_S,".sub",tolua_duiengine_DuiEngine_CRect__sub00);
    tolua_function(tolua_S,".add",tolua_duiengine_DuiEngine_CRect__add01);
    tolua_function(tolua_S,".sub",tolua_duiengine_DuiEngine_CRect__sub01);
    tolua_function(tolua_S,"MulDiv",tolua_duiengine_DuiEngine_CRect_MulDiv00);
    tolua_variable(tolua_S,"left",tolua_get_DuiEngine__CRect_left,tolua_set_DuiEngine__CRect_left);
    tolua_variable(tolua_S,"top",tolua_get_DuiEngine__CRect_top,tolua_set_DuiEngine__CRect_top);
    tolua_variable(tolua_S,"right",tolua_get_DuiEngine__CRect_right,tolua_set_DuiEngine__CRect_right);
    tolua_variable(tolua_S,"bottom",tolua_get_DuiEngine__CRect_bottom,tolua_set_DuiEngine__CRect_bottom);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"DuiEngine",0);
  tolua_beginmodule(tolua_S,"DuiEngine");
   tolua_cclass(tolua_S,"CDuiImgBase","DuiEngine::CDuiImgBase","",NULL);
   tolua_beginmodule(tolua_S,"CDuiImgBase");
    tolua_function(tolua_S,"LoadFromResource",tolua_duiengine_DuiEngine_CDuiImgBase_LoadFromResource00);
    tolua_function(tolua_S,"LoadFromFile",tolua_duiengine_DuiEngine_CDuiImgBase_LoadFromFile00);
    tolua_function(tolua_S,"LoadFromMemory",tolua_duiengine_DuiEngine_CDuiImgBase_LoadFromMemory00);
    tolua_function(tolua_S,"GetImageSize",tolua_duiengine_DuiEngine_CDuiImgBase_GetImageSize00);
    tolua_function(tolua_S,"GetWidth",tolua_duiengine_DuiEngine_CDuiImgBase_GetWidth00);
    tolua_function(tolua_S,"GetHeight",tolua_duiengine_DuiEngine_CDuiImgBase_GetHeight00);
    tolua_function(tolua_S,"IsEmpty",tolua_duiengine_DuiEngine_CDuiImgBase_IsEmpty00);
    tolua_function(tolua_S,"BitBlt",tolua_duiengine_DuiEngine_CDuiImgBase_BitBlt00);
    tolua_function(tolua_S,"StretchBlt",tolua_duiengine_DuiEngine_CDuiImgBase_StretchBlt00);
    tolua_function(tolua_S,"TileBlt",tolua_duiengine_DuiEngine_CDuiImgBase_TileBlt00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"CDuiImgDecoder","DuiEngine::CDuiImgDecoder","",NULL);
   tolua_beginmodule(tolua_S,"CDuiImgDecoder");
    tolua_function(tolua_S,"CreateDuiImage",tolua_duiengine_DuiEngine_CDuiImgDecoder_CreateDuiImage00);
    tolua_function(tolua_S,"DestoryDuiImage",tolua_duiengine_DuiEngine_CDuiImgDecoder_DestoryDuiImage00);
    tolua_function(tolua_S,"GetSupportTypes",tolua_duiengine_DuiEngine_CDuiImgDecoder_GetSupportTypes00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"DuiResProviderBase","DuiEngine::DuiResProviderBase","",NULL);
   tolua_beginmodule(tolua_S,"DuiResProviderBase");
    tolua_function(tolua_S,"HasResource",tolua_duiengine_DuiEngine_DuiResProviderBase_HasResource00);
    tolua_function(tolua_S,"LoadIcon",tolua_duiengine_DuiEngine_DuiResProviderBase_LoadIcon00);
    tolua_function(tolua_S,"LoadBitmap",tolua_duiengine_DuiEngine_DuiResProviderBase_LoadBitmap00);
    tolua_function(tolua_S,"LoadImage",tolua_duiengine_DuiEngine_DuiResProviderBase_LoadImage00);
    tolua_function(tolua_S,"GetRawBufferSize",tolua_duiengine_DuiEngine_DuiResProviderBase_GetRawBufferSize00);
    tolua_function(tolua_S,"GetRawBuffer",tolua_duiengine_DuiEngine_DuiResProviderBase_GetRawBuffer00);
    tolua_function(tolua_S,"GetImageDecoder",tolua_duiengine_DuiEngine_DuiResProviderBase_GetImageDecoder00);
   tolua_endmodule(tolua_S);
   tolua_constant(tolua_S,"Errors",DuiEngine::Errors);
   tolua_constant(tolua_S,"Warnings",DuiEngine::Warnings);
   tolua_constant(tolua_S,"Standard",DuiEngine::Standard);
   tolua_constant(tolua_S,"Informative",DuiEngine::Informative);
   tolua_constant(tolua_S,"Insane",DuiEngine::Insane);
   tolua_cclass(tolua_S,"DuiLogger","DuiEngine::DuiLogger","",NULL);
   tolua_beginmodule(tolua_S,"DuiLogger");
    tolua_function(tolua_S,"setLoggingLevel",tolua_duiengine_DuiEngine_DuiLogger_setLoggingLevel00);
    tolua_function(tolua_S,"getLoggingLevel",tolua_duiengine_DuiEngine_DuiLogger_getLoggingLevel00);
    tolua_function(tolua_S,"logEvent",tolua_duiengine_DuiEngine_DuiLogger_logEvent00);
    tolua_function(tolua_S,"setLogFilename",tolua_duiengine_DuiEngine_DuiLogger_setLogFilename00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"IScriptModule","DuiEngine::IScriptModule","",NULL);
   tolua_beginmodule(tolua_S,"IScriptModule");
    tolua_function(tolua_S,"GetScriptEngine",tolua_duiengine_DuiEngine_IScriptModule_GetScriptEngine00);
    tolua_function(tolua_S,"loadScriptFile",tolua_duiengine_DuiEngine_IScriptModule_loadScriptFile00);
    tolua_function(tolua_S,"loadScriptString",tolua_duiengine_DuiEngine_IScriptModule_loadScriptString00);
    tolua_function(tolua_S,"executeScriptFile",tolua_duiengine_DuiEngine_IScriptModule_executeScriptFile00);
    tolua_function(tolua_S,"executeScriptedEventHandler",tolua_duiengine_DuiEngine_IScriptModule_executeScriptedEventHandler00);
    tolua_function(tolua_S,"executeString",tolua_duiengine_DuiEngine_IScriptModule_executeString00);
    tolua_function(tolua_S,"getIdentifierString",tolua_duiengine_DuiEngine_IScriptModule_getIdentifierString00);
    tolua_function(tolua_S,"subscribeEvent",tolua_duiengine_DuiEngine_IScriptModule_subscribeEvent00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"DuiSystem","DuiEngine::DuiSystem","",NULL);
   tolua_beginmodule(tolua_S,"DuiSystem");
    tolua_function(tolua_S,"GetInstance",tolua_duiengine_DuiEngine_DuiSystem_GetInstance00);
    tolua_function(tolua_S,"SetResProvider",tolua_duiengine_DuiEngine_DuiSystem_SetResProvider00);
    tolua_function(tolua_S,"GetResProvider",tolua_duiengine_DuiEngine_DuiSystem_GetResProvider00);
    tolua_function(tolua_S,"SetLogger",tolua_duiengine_DuiEngine_DuiSystem_SetLogger00);
    tolua_function(tolua_S,"GetLogger",tolua_duiengine_DuiEngine_DuiSystem_GetLogger00);
    tolua_function(tolua_S,"logEvent",tolua_duiengine_DuiEngine_DuiSystem_logEvent00);
    tolua_function(tolua_S,"Name2ID",tolua_duiengine_DuiEngine_DuiSystem_Name2ID00);
    tolua_function(tolua_S,"InitName2ID",tolua_duiengine_DuiEngine_DuiSystem_InitName2ID00);
    tolua_function(tolua_S,"Init",tolua_duiengine_DuiEngine_DuiSystem_Init00);
    tolua_function(tolua_S,"SetMsgBoxTemplate",tolua_duiengine_DuiEngine_DuiSystem_SetMsgBoxTemplate00);
    tolua_function(tolua_S,"GetScriptModule",tolua_duiengine_DuiEngine_DuiSystem_GetScriptModule00);
    tolua_function(tolua_S,"SetScriptModule",tolua_duiengine_DuiEngine_DuiSystem_SetScriptModule00);
    tolua_function(tolua_S,"getSingletonPtr",tolua_duiengine_DuiEngine_DuiSystem_getSingletonPtr00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"CDuiWindow","DuiEngine::CDuiWindow","",tolua_collect_DuiEngine__CDuiWindow);
   #else
   tolua_cclass(tolua_S,"CDuiWindow","DuiEngine::CDuiWindow","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"CDuiWindow");
    tolua_function(tolua_S,"new",tolua_duiengine_DuiEngine_CDuiWindow_new00);
    tolua_function(tolua_S,"new_local",tolua_duiengine_DuiEngine_CDuiWindow_new00_local);
    tolua_function(tolua_S,".call",tolua_duiengine_DuiEngine_CDuiWindow_new00_local);
    tolua_function(tolua_S,"delete",tolua_duiengine_DuiEngine_CDuiWindow_delete00);
    tolua_function(tolua_S,"GetParent",tolua_duiengine_DuiEngine_CDuiWindow_GetParent00);
    tolua_function(tolua_S,"SetParent",tolua_duiengine_DuiEngine_CDuiWindow_SetParent00);
    tolua_function(tolua_S,"GetTopLevelParent",tolua_duiengine_DuiEngine_CDuiWindow_GetTopLevelParent00);
    tolua_function(tolua_S,"DestroyChild",tolua_duiengine_DuiEngine_CDuiWindow_DestroyChild00);
    tolua_function(tolua_S,"GetChildrenCount",tolua_duiengine_DuiEngine_CDuiWindow_GetChildrenCount00);
    tolua_function(tolua_S,"GetChild",tolua_duiengine_DuiEngine_CDuiWindow_GetChild00);
    tolua_function(tolua_S,"FindChildByCmdID",tolua_duiengine_DuiEngine_CDuiWindow_FindChildByCmdID00);
    tolua_function(tolua_S,"FindChildByName",tolua_duiengine_DuiEngine_CDuiWindow_FindChildByName00);
    tolua_function(tolua_S,"LoadXmlChildren",tolua_duiengine_DuiEngine_CDuiWindow_LoadXmlChildren00);
   tolua_endmodule(tolua_S);
   tolua_function(tolua_S,"DuiMessageBox",tolua_duiengine_DuiEngine_DuiMessageBox00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_duiengine (lua_State* tolua_S) {
 return tolua_duiengine_open(tolua_S);
};
#endif

