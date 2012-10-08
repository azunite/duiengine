#pragma once

//////////////////////////////////////////////////////////////////////////
// DEFINE_DUIRES:用于资源定义，在资源中使用需要先定义__DUIRES_RC,在代码中则不定义该宏
#ifdef __DUIRES_RC

#ifndef __DUIFILE_RC
#   define DEFINE_DUIRES(id, type, id_number, file_name)  \
    id_number type file_name

#else

#   define DEFINE_DUIRES(id, type, id_number, file_name)

#endif


#else

#   define DEFINE_DUIRES(id, type, id_number, file_name)  \
    const UINT id = id_number;

#endif

//////////////////////////////////////////////////////////////////////////

#   define DEFINE_XML(id, id_number, file_name)     \
    DEFINE_DUIRES(id, XML, id_number, file_name)

#   define DEFINE_BMP(id, id_number, file_name)     \
    DEFINE_DUIRES(id, BITMAP, id_number, file_name)

#   define DEFINE_ICO(id, id_number, file_name)     \
    DEFINE_DUIRES(id, ICON, id_number, file_name)

#   define DEFINE_IMGX(id, id_number, file_name)     \
    DEFINE_DUIRES(id, IMGX, id_number, file_name)

//////////////////////////////////////////////////////////////////////////
