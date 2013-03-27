#pragma once

//设置资源文件的\链接方式，需要在include "duires.h"前定义
#ifdef _DEBUG
#define __DUIFILE_RC	1
#endif

#include "duires.h"

//////////////////////////////////////////////////////////////////////////

#ifndef __DUIRES_RC
# include "winres.rc2"
# include "winres.h"
#endif
