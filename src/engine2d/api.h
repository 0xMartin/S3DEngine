/*
 * Mesa 3-D graphics library
 *
 * Copyright (C) 1999-2006  Brian Paul   All Rights Reserved.
 * Copyright (C) 2009  VMware, Inc.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef API_H
#define API_H


#if defined(_WIN32) && !defined(__WIN32__) && !defined(__CYGWIN__)
#define __WIN32__
#endif

#if defined(__WIN32s__) && !defined(__CYGWIN__)
#  if (defined(_MSC_VER) || defined(__MINGW32__)) && defined(BUILD_GL32) /* tag specify we're building mesa as a DLL */
#    define E2API __declspec(dllexport)
#  elif (defined(_MSC_VER) || defined(__MINGW32__)) && defined(_DLL) /* tag specifying we're building for DLL runtime support */
#    define E2API __declspec(dllimport)
#  else /* for use with static link lib build of Win32 edition only */
#    define E2API extern
#  endif
#  if defined(__MINGW32__) && defined(GL_NO_STDCALL) || defined(UNDER_CE)  /* The generated DLLs by MingW with STDCALL are not compatible with the ones done by Microsoft's compilers */
#    define E2APIENTRY
#  else
#    define E2APIENTRY __stdcall
#  endif
#elif defined(__CYGWIN__) && defined(USE_OPENGL32) /* use native windows opengl32 */
#  define E2API extern
#  define E2APIENTRY __stdcall
#elif (defined(__GNUC__) && __GNUC__ >= 4) || (defined(__SUNPRO_C) && (__SUNPRO_C >= 0x590))
#  define E2API __attribute__((visibility("default")))
#  define E2APIENTRY
#endif /* WIN32 && !CYGWIN */

/*
 * WINDOWS: Include windows.h here to define APIENTRY.
 * It is also useful when applications include this file by
 * including only glut.h, since glut.h depends on windows.h.
 * Applications needing to include windows.h with parms other
 * than "WIN32_LEAN_AND_MEAN" may include windows.h before
 * glut.h or gl.h.
 */
#if defined(_WIN32) && !defined(APIENTRY) && !defined(__CYGWIN__)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <windows.h>
#endif

#ifndef E2API
#define E2API extern
#endif

#ifndef E2APIENTRY
#define E2APIENTRY
#endif

#ifndef APIENTRY
#define APIENTRY E2APIENTRY
#endif

/* "P" suffix to be used for a pointer to a function */
#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif

#ifndef E2APIENTRYP
#define E2APIENTRYP E2APIENTRY *
#endif


#endif // API_H
