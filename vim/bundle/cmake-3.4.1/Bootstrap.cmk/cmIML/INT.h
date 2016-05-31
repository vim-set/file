/*============================================================================
  Kitware Information Macro Library
  Copyright 2010-2011 Kitware, Inc.
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:

  * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

  * Neither the name of Kitware, Inc. nor the names of its contributors
    may be used to endorse or promote products derived from this
    software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
  HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
============================================================================*/
#ifndef cmIML_INT_H
#define cmIML_INT_H
/*
This header defines macros with information about sized integer types.
Only information that can be determined using the preprocessor at
compilation time is available.  No try-compile results may be added
here.  Instead we memorize results on platforms of interest.

An includer may optionally define the following macros to suppress errors:

Input:
  cmIML_INT_NO_VERIFY          = skip verification declarations
  cmIML_INT_NO_ERROR_INT64_T   = type 'cmIML_INT_int64_t' is optional (*)
  cmIML_INT_NO_ERROR_UINT64_T  = type 'cmIML_INT_uint64_t' is optional (*)
  cmIML_INT_NO_ERROR_INTPTR_T  = type 'cmIML_INT_intptr_t' is optional (*)
  cmIML_INT_NO_ERROR_UINTPTR_T = type 'cmIML_INT_uintptr_t' is optional (*)

An includer may optionally define the following macros to override defaults.
Either way, an includer may test these macros after inclusion:

  cmIML_INT_HAVE_STDINT_H   = include <stdint.h>
  cmIML_INT_NO_STDINT_H     = do not include <stdint.h>
  cmIML_INT_HAVE_INTTYPES_H = include <inttypes.h>
  cmIML_INT_NO_INTTYPES_H   = do not include <inttypes.h>

An includer may test the following macros after inclusion:

  cmIML_INT_HAVE_INT#_T     = type 'int#_t' is available
  cmIML_INT_HAVE_UINT#_T    = type 'uint#_t' is available
                                # = 8, 16, 32, 64, PTR

  cmIML_INT_int#_t          = signed integer type exactly # bits wide
  cmIML_INT_uint#_t         = unsigned integer type exactly # bits wide
                                # = 8, 16, 32, 64 (*), ptr (*)

  cmIML_INT_NO_INT64_T      = type 'cmIML_INT_int64_t' not available
  cmIML_INT_NO_UINT64_T     = type 'cmIML_INT_uint64_t' not available
  cmIML_INT_NO_INTPTR_T     = type 'cmIML_INT_intptr_t' not available
  cmIML_INT_NO_UINTPTR_T    = type 'cmIML_INT_uintptr_t' not available

  cmIML_INT_INT#_C(c)       = signed integer constant at least # bits wide
  cmIML_INT_UINT#_C(c)      = unsigned integer constant at least # bits wide
                                # = 8, 16, 32, 64 (*)

  cmIML_INT_<fmt>#          = print or scan format, <fmt> in table below
                                # = 8, 16, 32, 64, PTR (*)

             signed                unsigned
           ----------- ------------------------------
          |  decimal  | decimal  octal   hexadecimal |
    print | PRId PRIi |  PRIu    PRIo    PRIx  PRIX  |
     scan | SCNd SCNi |  SCNu    SCNo    SCNx        |
           ----------- ------------------------------

    The SCN*8 and SCN*64 format macros will not be defined on systems
    with scanf implementations known not to support them.

  cmIML_INT_BROKEN_<fmt># = macro <fmt># is incorrect if defined
    Some compilers define integer format macros incorrectly for their
    own formatted print/scan implementations.

  cmIML_INT_BROKEN_INT#_C  = macro INT#_C is incorrect if defined
  cmIML_INT_BROKEN_UINT#_C = macro UINT#_C is incorrect if defined
    Some compilers define integer constant macros incorrectly and
    cannot handle literals as large as the integer type or even
    produce bad preprocessor syntax.

  cmIML_INT_BROKEN_INT8_T   = type 'int8_t' is available but incorrect
    Some compilers have a flag to make 'char' (un)signed but do not account
    for it while defining int8_t in the non-default case.

  The broken cases do not affect correctness of the macros documented above.
*/

#include "ABI.h"

/*--------------------------------------------------------------------------*/
#if defined(cmIML_INT_HAVE_STDINT_H) /* Already defined. */
#elif defined(cmIML_INT_NO_STDINT_H) /* Already defined. */
#elif defined(HAVE_STDINT_H) /* Optionally provided by includer.  */
# define cmIML_INT_HAVE_STDINT_H 1
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L /* C99 */
# define cmIML_INT_HAVE_STDINT_H 1
#elif defined(_MSC_VER) /* MSVC */
# if _MSC_VER >= 1600
#  define cmIML_INT_HAVE_STDINT_H 1
# else
#  define cmIML_INT_NO_STDINT_H 1
# endif
#elif defined(__BORLANDC__) /* Borland */
# if __BORLANDC__ >= 0x560
#  define cmIML_INT_HAVE_STDINT_H 1
# else
#  define cmIML_INT_NO_STDINT_H 1
# endif
#elif defined(__WATCOMC__) /* Watcom */
# define cmIML_INT_NO_STDINT_H 1
#endif

/*--------------------------------------------------------------------------*/
#if defined(cmIML_INT_HAVE_INTTYPES_H) /* Already defined. */
#elif defined(cmIML_INT_NO_INTTYPES_H) /* Already defined. */
#elif defined(HAVE_INTTYPES_H) /* Optionally provided by includer.  */
# define cmIML_INT_HAVE_INTTYPES_H 1
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L /* C99 */
# define cmIML_INT_HAVE_INTTYPES_H 1
#elif defined(_MSC_VER) /* MSVC */
# define cmIML_INT_NO_INTTYPES_H 1
#elif defined(__BORLANDC__) /* Borland */
# define cmIML_INT_NO_INTTYPES_H 1
#elif defined(__WATCOMC__) /* Watcom */
# define cmIML_INT_NO_INTTYPES_H 1
#else /* Assume it exists.  */
# define cmIML_INT_HAVE_INTTYPES_H 1
#endif

/*--------------------------------------------------------------------------*/
#if defined(cmIML_INT_HAVE_STDINT_H) && defined(cmIML_INT_NO_STDINT_H)
# error "Both cmIML_INT_HAVE_STDINT_H and cmIML_INT_NO_STDINT_H defined!"
#endif
#if defined(cmIML_INT_HAVE_INTTYPES_H) && defined(cmIML_INT_NO_INTTYPES_H)
# error "Both cmIML_INT_HAVE_INTTYPES_H and cmIML_INT_NO_INTTYPES_H defined!"
#endif

#if defined(cmIML_INT_HAVE_STDINT_H)
# include <stdint.h>
#endif
#if defined(cmIML_INT_HAVE_INTTYPES_H)
# if defined(__cplusplus) && !defined(__STDC_FORMAT_MACROS)
#  define __STDC_FORMAT_MACROS
# endif
# include <inttypes.h>
#endif

#if defined(cmIML_INT_HAVE_STDINT_H) || defined(cmIML_INT_HAVE_INTTYPES_H)
#define cmIML_INT_HAVE_INT8_T 1
#define cmIML_INT_HAVE_UINT8_T 1
#define cmIML_INT_HAVE_INT16_T 1
#define cmIML_INT_HAVE_UINT16_T 1
#define cmIML_INT_HAVE_INT32_T 1
#define cmIML_INT_HAVE_UINT32_T 1
#define cmIML_INT_HAVE_INT64_T 1
#define cmIML_INT_HAVE_UINT64_T 1
#define cmIML_INT_HAVE_INTPTR_T 1
#define cmIML_INT_HAVE_UINTPTR_T 1
#endif

#if defined(_AIX43) && !defined(_AIX50) && !defined(_AIX51)
  /* AIX 4.3 defines these incorrectly with % and no quotes. */
# define cmIML_INT_BROKEN_PRId8
# define cmIML_INT_BROKEN_SCNd8
# define cmIML_INT_BROKEN_PRIi8
# define cmIML_INT_BROKEN_SCNi8
# define cmIML_INT_BROKEN_PRIo8
# define cmIML_INT_BROKEN_SCNo8
# define cmIML_INT_BROKEN_PRIu8
# define cmIML_INT_BROKEN_SCNu8
# define cmIML_INT_BROKEN_PRIx8
# define cmIML_INT_BROKEN_SCNx8
# define cmIML_INT_BROKEN_PRIX8
# define cmIML_INT_BROKEN_PRId16
# define cmIML_INT_BROKEN_SCNd16
# define cmIML_INT_BROKEN_PRIi16
# define cmIML_INT_BROKEN_SCNi16
# define cmIML_INT_BROKEN_PRIo16
# define cmIML_INT_BROKEN_SCNo16
# define cmIML_INT_BROKEN_PRIu16
# define cmIML_INT_BROKEN_SCNu16
# define cmIML_INT_BROKEN_PRIx16
# define cmIML_INT_BROKEN_SCNx16
# define cmIML_INT_BROKEN_PRIX16
# define cmIML_INT_BROKEN_PRId32
# define cmIML_INT_BROKEN_SCNd32
# define cmIML_INT_BROKEN_PRIi32
# define cmIML_INT_BROKEN_SCNi32
# define cmIML_INT_BROKEN_PRIo32
# define cmIML_INT_BROKEN_SCNo32
# define cmIML_INT_BROKEN_PRIu32
# define cmIML_INT_BROKEN_SCNu32
# define cmIML_INT_BROKEN_PRIx32
# define cmIML_INT_BROKEN_SCNx32
# define cmIML_INT_BROKEN_PRIX32
# define cmIML_INT_BROKEN_PRId64
# define cmIML_INT_BROKEN_SCNd64
# define cmIML_INT_BROKEN_PRIi64
# define cmIML_INT_BROKEN_SCNi64
# define cmIML_INT_BROKEN_PRIo64
# define cmIML_INT_BROKEN_SCNo64
# define cmIML_INT_BROKEN_PRIu64
# define cmIML_INT_BROKEN_SCNu64
# define cmIML_INT_BROKEN_PRIx64
# define cmIML_INT_BROKEN_SCNx64
# define cmIML_INT_BROKEN_PRIX64
# define cmIML_INT_BROKEN_PRIdPTR
# define cmIML_INT_BROKEN_SCNdPTR
# define cmIML_INT_BROKEN_PRIiPTR
# define cmIML_INT_BROKEN_SCNiPTR
# define cmIML_INT_BROKEN_PRIoPTR
# define cmIML_INT_BROKEN_SCNoPTR
# define cmIML_INT_BROKEN_PRIuPTR
# define cmIML_INT_BROKEN_SCNuPTR
# define cmIML_INT_BROKEN_PRIxPTR
# define cmIML_INT_BROKEN_SCNxPTR
# define cmIML_INT_BROKEN_PRIXPTR
#endif

#if (defined(__SUNPRO_C)||defined(__SUNPRO_CC)) && defined(_CHAR_IS_UNSIGNED)
# define cmIML_INT_BROKEN_INT8_T /* system type defined incorrectly */
#elif defined(__BORLANDC__) && defined(_CHAR_UNSIGNED)
# define cmIML_INT_BROKEN_INT8_T /* system type defined incorrectly */
#endif

/*--------------------------------------------------------------------------*/
#if defined(cmIML_INT_HAVE_INT8_T) && !defined(cmIML_INT_BROKEN_INT8_T)
# define cmIML_INT_int8_t int8_t
#else
# define cmIML_INT_int8_t signed char
#endif
#if defined(cmIML_INT_HAVE_UINT8_T)
# define cmIML_INT_uint8_t uint8_t
#else
# define cmIML_INT_uint8_t unsigned char
#endif

#if defined(__INTEL_COMPILER)
# if defined(_WIN32)
#  define cmIML_INT__NO_SCN8
# endif
#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
# define cmIML_INT__NO_SCN8
#elif defined(__BORLANDC__)
# define cmIML_INT__NO_SCN8
# define cmIML_INT__NO_SCN64
#elif defined(_MSC_VER)
# define cmIML_INT__NO_SCN8
#elif defined(__WATCOMC__)
# define cmIML_INT__NO_SCN8
# elif defined(__hpux) /* HP runtime lacks support (any compiler) */
# define cmIML_INT__NO_SCN8
#endif

/* 8-bit d, i */
#if defined(cmIML_INT_HAVE_INT8_T) && defined(PRId8) \
  && !defined(cmIML_INT_BROKEN_PRId8)
# define cmIML_INT_PRId8 PRId8
#else
# define cmIML_INT_PRId8   "d"
#endif
#if defined(cmIML_INT_HAVE_INT8_T) && defined(SCNd8) \
  && !defined(cmIML_INT_BROKEN_SCNd8)
# define cmIML_INT_SCNd8 SCNd8
#elif !defined(cmIML_INT__NO_SCN8)
# define cmIML_INT_SCNd8 "hhd"
#endif
#if defined(cmIML_INT_HAVE_INT8_T) && defined(PRIi8) \
  && !defined(cmIML_INT_BROKEN_PRIi8)
# define cmIML_INT_PRIi8 PRIi8
#else
# define cmIML_INT_PRIi8   "i"
#endif
#if defined(cmIML_INT_HAVE_INT8_T) && defined(SCNi8) \
  && !defined(cmIML_INT_BROKEN_SCNi8)
# define cmIML_INT_SCNi8 SCNi8
#elif !defined(cmIML_INT__NO_SCN8)
# define cmIML_INT_SCNi8 "hhi"
#endif

/* 8-bit o, u, x, X */
#if defined(cmIML_INT_HAVE_UINT8_T) && defined(PRIo8) \
  && !defined(cmIML_INT_BROKEN_PRIo8)
# define cmIML_INT_PRIo8 PRIo8
#else
# define cmIML_INT_PRIo8   "o"
#endif
#if defined(cmIML_INT_HAVE_UINT8_T) && defined(SCNo8) \
  && !defined(cmIML_INT_BROKEN_SCNo8)
# define cmIML_INT_SCNo8 SCNo8
#elif !defined(cmIML_INT__NO_SCN8)
# define cmIML_INT_SCNo8 "hho"
#endif
#if defined(cmIML_INT_HAVE_UINT8_T) && defined(PRIu8) \
  && !defined(cmIML_INT_BROKEN_PRIu8)
# define cmIML_INT_PRIu8 PRIu8
#else
# define cmIML_INT_PRIu8   "u"
#endif
#if defined(cmIML_INT_HAVE_UINT8_T) && defined(SCNu8) \
  && !defined(cmIML_INT_BROKEN_SCNu8)
# define cmIML_INT_SCNu8 SCNu8
#elif !defined(cmIML_INT__NO_SCN8)
# define cmIML_INT_SCNu8 "hhu"
#endif
#if defined(cmIML_INT_HAVE_UINT8_T) && defined(PRIx8) \
  && !defined(cmIML_INT_BROKEN_PRIx8)
# define cmIML_INT_PRIx8 PRIx8
#else
# define cmIML_INT_PRIx8   "x"
#endif
#if defined(cmIML_INT_HAVE_UINT8_T) && defined(SCNx8) \
  && !defined(cmIML_INT_BROKEN_SCNx8)
# define cmIML_INT_SCNx8 SCNx8
#elif !defined(cmIML_INT__NO_SCN8)
# define cmIML_INT_SCNx8 "hhx"
#endif
#if defined(cmIML_INT_HAVE_UINT8_T) && defined(PRIX8) \
  && !defined(cmIML_INT_BROKEN_PRIX8)
# define cmIML_INT_PRIX8 PRIX8
#else
# define cmIML_INT_PRIX8   "X"
#endif

/* 8-bit constants */
#if defined(INT8_C) && !defined(cmIML_INT_BROKEN_INT8_C)
# define cmIML_INT_INT8_C(c) INT8_C(c)
#else
# define cmIML_INT_INT8_C(c) c
#endif
#if defined(UINT8_C) && !defined(cmIML_INT_BROKEN_UINT8_C)
# define cmIML_INT_UINT8_C(c) UINT8_C(c)
#else
# define cmIML_INT_UINT8_C(c) c ## u
#endif

/*--------------------------------------------------------------------------*/
#if defined(cmIML_INT_HAVE_INT16_T)
# define cmIML_INT_int16_t int16_t
#else
# define cmIML_INT_int16_t signed short
#endif
#if defined(cmIML_INT_HAVE_UINT16_T)
# define cmIML_INT_uint16_t uint16_t
#else
# define cmIML_INT_uint16_t unsigned short
#endif

/* 16-bit d, i */
#if defined(cmIML_INT_HAVE_INT16_T) && defined(PRId16) \
  && !defined(cmIML_INT_BROKEN_PRId16)
# define cmIML_INT_PRId16 PRId16
#else
# define cmIML_INT_PRId16  "d"
#endif
#if defined(cmIML_INT_HAVE_INT16_T) && defined(SCNd16) \
  && !defined(cmIML_INT_BROKEN_SCNd16)
# define cmIML_INT_SCNd16 SCNd16
#else
# define cmIML_INT_SCNd16 "hd"
#endif
#if defined(cmIML_INT_HAVE_INT16_T) && defined(PRIi16) \
  && !defined(cmIML_INT_BROKEN_PRIi16)
# define cmIML_INT_PRIi16 PRIi16
#else
# define cmIML_INT_PRIi16  "i"
#endif
#if defined(cmIML_INT_HAVE_INT16_T) && defined(SCNi16) \
  && !defined(cmIML_INT_BROKEN_SCNi16)
# define cmIML_INT_SCNi16 SCNi16
#else
# define cmIML_INT_SCNi16 "hi"
#endif

/* 16-bit o, u, x, X */
#if defined(cmIML_INT_HAVE_UINT16_T) && defined(PRIo16) \
  && !defined(cmIML_INT_BROKEN_PRIo16)
# define cmIML_INT_PRIo16 PRIo16
#else
# define cmIML_INT_PRIo16  "o"
#endif
#if defined(cmIML_INT_HAVE_UINT16_T) && defined(SCNo16) \
  && !defined(cmIML_INT_BROKEN_SCNo16)
# define cmIML_INT_SCNo16 SCNo16
#else
# define cmIML_INT_SCNo16 "ho"
#endif
#if defined(cmIML_INT_HAVE_UINT16_T) && defined(PRIu16) \
  && !defined(cmIML_INT_BROKEN_PRIu16)
# define cmIML_INT_PRIu16 PRIu16
#else
# define cmIML_INT_PRIu16  "u"
#endif
#if defined(cmIML_INT_HAVE_UINT16_T) && defined(SCNu16) \
  && !defined(cmIML_INT_BROKEN_SCNu16)
# define cmIML_INT_SCNu16 SCNu16
#else
# define cmIML_INT_SCNu16 "hu"
#endif
#if defined(cmIML_INT_HAVE_UINT16_T) && defined(PRIx16) \
  && !defined(cmIML_INT_BROKEN_PRIx16)
# define cmIML_INT_PRIx16 PRIx16
#else
# define cmIML_INT_PRIx16  "x"
#endif
#if defined(cmIML_INT_HAVE_UINT16_T) && defined(SCNx16) \
  && !defined(cmIML_INT_BROKEN_SCNx16)
# define cmIML_INT_SCNx16 SCNx16
#else
# define cmIML_INT_SCNx16 "hx"
#endif
#if defined(cmIML_INT_HAVE_UINT16_T) && defined(PRIX16) \
  && !defined(cmIML_INT_BROKEN_PRIX16)
# define cmIML_INT_PRIX16 PRIX16
#else
# define cmIML_INT_PRIX16  "X"
#endif

/* 16-bit constants */
#if defined(INT16_C) && !defined(cmIML_INT_BROKEN_INT16_C)
# define cmIML_INT_INT16_C(c) INT16_C(c)
#else
# define cmIML_INT_INT16_C(c) c
#endif
#if defined(UINT16_C) && !defined(cmIML_INT_BROKEN_UINT16_C)
# define cmIML_INT_UINT16_C(c) UINT16_C(c)
#else
# define cmIML_INT_UINT16_C(c) c ## u
#endif

/*--------------------------------------------------------------------------*/
#if defined(cmIML_INT_HAVE_INT32_T)
# define cmIML_INT_int32_t int32_t
#else
# define cmIML_INT_int32_t signed int
#endif
#if defined(cmIML_INT_HAVE_UINT32_T)
# define cmIML_INT_uint32_t uint32_t
#else
# define cmIML_INT_uint32_t unsigned int
#endif

/* 32-bit d, i */
#if defined(cmIML_INT_HAVE_INT32_T) && defined(PRId32) \
  && !defined(cmIML_INT_BROKEN_PRId32)
# define cmIML_INT_PRId32 PRId32
#else
# define cmIML_INT_PRId32 "d"
#endif
#if defined(cmIML_INT_HAVE_INT32_T) && defined(SCNd32) \
  && !defined(cmIML_INT_BROKEN_SCNd32)
# define cmIML_INT_SCNd32 SCNd32
#else
# define cmIML_INT_SCNd32 "d"
#endif
#if defined(cmIML_INT_HAVE_INT32_T) && defined(PRIi32) \
  && !defined(cmIML_INT_BROKEN_PRIi32)
# define cmIML_INT_PRIi32 PRIi32
#else
# define cmIML_INT_PRIi32 "i"
#endif
#if defined(cmIML_INT_HAVE_INT32_T) && defined(SCNi32) \
  && !defined(cmIML_INT_BROKEN_SCNi32)
# define cmIML_INT_SCNi32 SCNi32
#else
# define cmIML_INT_SCNi32 "i"
#endif

/* 32-bit o, u, x, X */
#if defined(cmIML_INT_HAVE_UINT32_T) && defined(PRIo32) \
  && !defined(cmIML_INT_BROKEN_PRIo32)
# define cmIML_INT_PRIo32 PRIo32
#else
# define cmIML_INT_PRIo32 "o"
#endif
#if defined(cmIML_INT_HAVE_UINT32_T) && defined(SCNo32) \
  && !defined(cmIML_INT_BROKEN_SCNo32)
# define cmIML_INT_SCNo32 SCNo32
#else
# define cmIML_INT_SCNo32 "o"
#endif
#if defined(cmIML_INT_HAVE_UINT32_T) && defined(PRIu32) \
  && !defined(cmIML_INT_BROKEN_PRIu32)
# define cmIML_INT_PRIu32 PRIu32
#else
# define cmIML_INT_PRIu32 "u"
#endif
#if defined(cmIML_INT_HAVE_UINT32_T) && defined(SCNu32) \
  && !defined(cmIML_INT_BROKEN_SCNu32)
# define cmIML_INT_SCNu32 SCNu32
#else
# define cmIML_INT_SCNu32 "u"
#endif
#if defined(cmIML_INT_HAVE_UINT32_T) && defined(PRIx32) \
  && !defined(cmIML_INT_BROKEN_PRIx32)
# define cmIML_INT_PRIx32 PRIx32
#else
# define cmIML_INT_PRIx32 "x"
#endif
#if defined(cmIML_INT_HAVE_UINT32_T) && defined(SCNx32) \
  && !defined(cmIML_INT_BROKEN_SCNx32)
# define cmIML_INT_SCNx32 SCNx32
#else
# define cmIML_INT_SCNx32 "x"
#endif
#if defined(cmIML_INT_HAVE_UINT32_T) && defined(PRIX32) \
  && !defined(cmIML_INT_BROKEN_PRIX32)
# define cmIML_INT_PRIX32 PRIX32
#else
# define cmIML_INT_PRIX32 "X"
#endif

#if defined(__hpux) && defined(__GNUC__) && !defined(__LP64__) \
 && defined(__CONCAT__) && defined(__CONCAT_U__)
  /* Some HPs define UINT32_C incorrectly and break GNU.  */
# define cmIML_INT_BROKEN_UINT32_C
#endif

/* 32-bit constants */
#if defined(INT32_C) && !defined(cmIML_INT_BROKEN_INT32_C)
# define cmIML_INT_INT32_C(c) INT32_C(c)
#else
# define cmIML_INT_INT32_C(c) c
#endif
#if defined(UINT32_C) && !defined(cmIML_INT_BROKEN_UINT32_C)
# define cmIML_INT_UINT32_C(c) UINT32_C(c)
#else
# define cmIML_INT_UINT32_C(c) c ## u
#endif

/*--------------------------------------------------------------------------*/
#if defined(cmIML_INT_HAVE_INT64_T)
# define cmIML_INT_int64_t int64_t
#elif cmIML_ABI_SIZEOF_LONG == 8
# define cmIML_INT_int64_t signed long
#elif defined(cmIML_ABI_SIZEOF_LONG_LONG) && cmIML_ABI_SIZEOF_LONG_LONG == 8
# define cmIML_INT_int64_t signed long long
#elif defined(cmIML_ABI_SIZEOF___INT64)
# define cmIML_INT_int64_t signed __int64
#elif defined(cmIML_INT_NO_ERROR_INT64_T)
# define cmIML_INT_NO_INT64_T
#else
# error "No type known for 'int64_t'."
#endif
#if defined(cmIML_INT_HAVE_UINT64_T)
# define cmIML_INT_uint64_t uint64_t
#elif cmIML_ABI_SIZEOF_LONG == 8
# define cmIML_INT_uint64_t unsigned long
#elif defined(cmIML_ABI_SIZEOF_LONG_LONG) && cmIML_ABI_SIZEOF_LONG_LONG == 8
# define cmIML_INT_uint64_t unsigned long long
#elif defined(cmIML_ABI_SIZEOF___INT64)
# define cmIML_INT_uint64_t unsigned __int64
#elif defined(cmIML_INT_NO_ERROR_UINT64_T)
# define cmIML_INT_NO_UINT64_T
#else
# error "No type known for 'uint64_t'."
#endif

#if defined(__INTEL_COMPILER)
#elif defined(__BORLANDC__)
# define cmIML_INT__NO_FMTLL /* type 'long long' but not 'll' format */
# define cmIML_INT_BROKEN_INT64_C   /* system macro defined incorrectly */
# define cmIML_INT_BROKEN_UINT64_C  /* system macro defined incorrectly */
#elif defined(_MSC_VER) && _MSC_VER < 1400
# define cmIML_INT__NO_FMTLL /* type 'long long' but not 'll' format */
#endif

#if cmIML_ABI_SIZEOF_LONG == 8
# define cmIML_INT__FMT64 "l"
#elif defined(cmIML_ABI_SIZEOF_LONG_LONG) && cmIML_ABI_SIZEOF_LONG_LONG == 8
# if !defined(cmIML_INT__NO_FMTLL)
#  define cmIML_INT__FMT64 "ll"
# else
#  define cmIML_INT__FMT64 "I64"
# endif
#elif defined(cmIML_ABI_SIZEOF___INT64)
# if defined(__BORLANDC__)
#  define cmIML_INT__FMT64 "L"
# else
#  define cmIML_INT__FMT64 "I64"
# endif
#endif

/* 64-bit d, i */
#if defined(cmIML_INT_HAVE_INT64_T) && defined(PRId64) \
  && !defined(cmIML_INT_BROKEN_PRId64)
# define cmIML_INT_PRId64 PRId64
#elif defined(cmIML_INT__FMT64)
# define cmIML_INT_PRId64 cmIML_INT__FMT64 "d"
#endif
#if defined(cmIML_INT_HAVE_INT64_T) && defined(SCNd64) \
  && !defined(cmIML_INT_BROKEN_SCNd64)
# define cmIML_INT_SCNd64 SCNd64
#elif defined(cmIML_INT__FMT64) && !defined(cmIML_INT__NO_SCN64)
# define cmIML_INT_SCNd64 cmIML_INT__FMT64 "d"
#endif
#if defined(cmIML_INT_HAVE_INT64_T) && defined(PRIi64) \
  && !defined(cmIML_INT_BROKEN_PRIi64)
# define cmIML_INT_PRIi64 PRIi64
#elif defined(cmIML_INT__FMT64)
# define cmIML_INT_PRIi64 cmIML_INT__FMT64 "d"
#endif
#if defined(cmIML_INT_HAVE_INT64_T) && defined(SCNi64) \
  && !defined(cmIML_INT_BROKEN_SCNi64)
# define cmIML_INT_SCNi64 SCNi64
#elif defined(cmIML_INT__FMT64) && !defined(cmIML_INT__NO_SCN64)
# define cmIML_INT_SCNi64 cmIML_INT__FMT64 "d"
#endif

/* 64-bit o, u, x, X */
#if defined(cmIML_INT_HAVE_UINT64_T) && defined(PRIo64) \
  && !defined(cmIML_INT_BROKEN_PRIo64)
# define cmIML_INT_PRIo64 PRIo64
#elif defined(cmIML_INT__FMT64)
# define cmIML_INT_PRIo64 cmIML_INT__FMT64 "o"
#endif
#if defined(cmIML_INT_HAVE_UINT64_T) && defined(SCNo64) \
  && !defined(cmIML_INT_BROKEN_SCNo64)
# define cmIML_INT_SCNo64 SCNo64
#elif defined(cmIML_INT__FMT64) && !defined(cmIML_INT__NO_SCN64)
# define cmIML_INT_SCNo64 cmIML_INT__FMT64 "o"
#endif
#if defined(cmIML_INT_HAVE_UINT64_T) && defined(PRIu64) \
  && !defined(cmIML_INT_BROKEN_PRIu64)
# define cmIML_INT_PRIu64 PRIu64
#elif defined(cmIML_INT__FMT64)
# define cmIML_INT_PRIu64 cmIML_INT__FMT64 "u"
#endif
#if defined(cmIML_INT_HAVE_UINT64_T) && defined(SCNu64) \
  && !defined(cmIML_INT_BROKEN_SCNu64)
# define cmIML_INT_SCNu64 SCNu64
#elif defined(cmIML_INT__FMT64) && !defined(cmIML_INT__NO_SCN64)
# define cmIML_INT_SCNu64 cmIML_INT__FMT64 "u"
#endif
#if defined(cmIML_INT_HAVE_UINT64_T) && defined(PRIx64) \
  && !defined(cmIML_INT_BROKEN_PRIx64)
# define cmIML_INT_PRIx64 PRIx64
#elif defined(cmIML_INT__FMT64)
# define cmIML_INT_PRIx64 cmIML_INT__FMT64 "x"
#endif
#if defined(cmIML_INT_HAVE_UINT64_T) && defined(SCNx64) \
  && !defined(cmIML_INT_BROKEN_SCNx64)
# define cmIML_INT_SCNx64 SCNx64
#elif defined(cmIML_INT__FMT64) && !defined(cmIML_INT__NO_SCN64)
# define cmIML_INT_SCNx64 cmIML_INT__FMT64 "x"
#endif
#if defined(cmIML_INT_HAVE_UINT64_T) && defined(PRIX64) \
  && !defined(cmIML_INT_BROKEN_PRIX64)
# define cmIML_INT_PRIX64 PRIX64
#elif defined(cmIML_INT__FMT64)
# define cmIML_INT_PRIX64 cmIML_INT__FMT64 "X"
#endif

/* 64-bit constants */
#if defined(cmIML_INT_HAVE_INT64_T) && defined(INT64_C) \
  && !defined(cmIML_INT_BROKEN_INT64_C)
# define cmIML_INT_INT64_C(c) INT64_C(c)
#elif cmIML_ABI_SIZEOF_LONG == 8
# define cmIML_INT_INT64_C(c) c ## l
#elif defined(cmIML_ABI_SIZEOF_LONG_LONG) && cmIML_ABI_SIZEOF_LONG_LONG == 8
# define cmIML_INT_INT64_C(c) c ## ll
#elif defined(cmIML_ABI_SIZEOF___INT64)
# define cmIML_INT_INT64_C(c) c ## i64
#endif
#if defined(cmIML_INT_HAVE_UINT64_T) && defined(UINT64_C) \
  && !defined(cmIML_INT_BROKEN_UINT64_C)
# define cmIML_INT_UINT64_C(c) UINT64_C(c)
#elif cmIML_ABI_SIZEOF_LONG == 8
# define cmIML_INT_UINT64_C(c) c ## ul
#elif defined(cmIML_ABI_SIZEOF_LONG_LONG) && cmIML_ABI_SIZEOF_LONG_LONG == 8
# define cmIML_INT_UINT64_C(c) c ## ull
#elif defined(cmIML_ABI_SIZEOF___INT64)
# define cmIML_INT_UINT64_C(c) c ## ui64
#endif

/*--------------------------------------------------------------------------*/
#if defined(cmIML_INT_HAVE_INTPTR_T)
# define cmIML_INT_intptr_t intptr_t
#elif cmIML_ABI_SIZEOF_DATA_PTR == 4
# define cmIML_INT_intptr_t cmIML_INT_int32_t
#elif !defined(cmIML_INT_NO_INT64_T)
# define cmIML_INT_intptr_t cmIML_INT_int64_t
#elif defined(cmIML_INT_NO_ERROR_INTPTR_T)
# define cmIML_INT_NO_INTPTR_T
#else
# error "No type known for 'intptr_t'."
#endif
#if defined(cmIML_INT_HAVE_UINTPTR_T)
# define cmIML_INT_uintptr_t uintptr_t
#elif cmIML_ABI_SIZEOF_DATA_PTR == 4
# define cmIML_INT_uintptr_t cmIML_INT_uint32_t
#elif !defined(cmIML_INT_NO_UINT64_T)
# define cmIML_INT_uintptr_t cmIML_INT_uint64_t
#elif defined(cmIML_INT_NO_ERROR_UINTPTR_T)
# define cmIML_INT_NO_UINTPTR_T
#else
# error "No type known for 'uintptr_t'."
#endif

#if defined(cmIML_INT_HAVE_INTPTR_T) && defined(PRIdPTR) \
  && !defined(cmIML_INT_BROKEN_PRIdPTR)
# define cmIML_INT_PRIdPTR PRIdPTR
#elif cmIML_ABI_SIZEOF_DATA_PTR == 4
# define cmIML_INT_PRIdPTR cmIML_INT_PRId32
#elif !defined(cmIML_INT_NO_UINT64_T)
# define cmIML_INT_PRIdPTR cmIML_INT_PRId64
#endif
#if defined(cmIML_INT_HAVE_INTPTR_T) && defined(SCNdPTR) \
  && !defined(cmIML_INT_BROKEN_SCNdPTR)
# define cmIML_INT_SCNdPTR SCNdPTR
#elif cmIML_ABI_SIZEOF_DATA_PTR == 4
# define cmIML_INT_SCNdPTR cmIML_INT_SCNd32
#elif !defined(cmIML_INT_NO_UINT64_T)
# define cmIML_INT_SCNdPTR cmIML_INT_SCNd64
#endif
#if defined(cmIML_INT_HAVE_INTPTR_T) && defined(PRIiPTR) \
  && !defined(cmIML_INT_BROKEN_PRIiPTR)
# define cmIML_INT_PRIiPTR PRIiPTR
#elif cmIML_ABI_SIZEOF_DATA_PTR == 4
# define cmIML_INT_PRIiPTR cmIML_INT_PRIi32
#elif !defined(cmIML_INT_NO_UINT64_T)
# define cmIML_INT_PRIiPTR cmIML_INT_PRIi64
#endif
#if defined(cmIML_INT_HAVE_INTPTR_T) && defined(SCNiPTR) \
  && !defined(cmIML_INT_BROKEN_SCNiPTR)
# define cmIML_INT_SCNiPTR SCNiPTR
#elif cmIML_ABI_SIZEOF_DATA_PTR == 4
# define cmIML_INT_SCNiPTR cmIML_INT_SCNi32
#elif !defined(cmIML_INT_NO_UINT64_T)
# define cmIML_INT_SCNiPTR cmIML_INT_SCNi64
#endif

#if defined(cmIML_INT_HAVE_UINTPTR_T) && defined(PRIoPTR) \
  && !defined(cmIML_INT_BROKEN_PRIoPTR)
# define cmIML_INT_PRIoPTR PRIoPTR
#elif cmIML_ABI_SIZEOF_DATA_PTR == 4
# define cmIML_INT_PRIoPTR cmIML_INT_PRIo32
#elif !defined(cmIML_INT_NO_UINT64_T)
# define cmIML_INT_PRIoPTR cmIML_INT_PRIo64
#endif
#if defined(cmIML_INT_HAVE_UINTPTR_T) && defined(SCNoPTR) \
  && !defined(cmIML_INT_BROKEN_SCNoPTR)
# define cmIML_INT_SCNoPTR SCNoPTR
#elif cmIML_ABI_SIZEOF_DATA_PTR == 4
# define cmIML_INT_SCNoPTR cmIML_INT_SCNo32
#elif !defined(cmIML_INT_NO_UINT64_T)
# define cmIML_INT_SCNoPTR cmIML_INT_SCNo64
#endif
#if defined(cmIML_INT_HAVE_UINTPTR_T) && defined(PRIuPTR) \
  && !defined(cmIML_INT_BROKEN_PRIuPTR)
# define cmIML_INT_PRIuPTR PRIuPTR
#elif cmIML_ABI_SIZEOF_DATA_PTR == 4
# define cmIML_INT_PRIuPTR cmIML_INT_PRIu32
#elif !defined(cmIML_INT_NO_UINT64_T)
# define cmIML_INT_PRIuPTR cmIML_INT_PRIu64
#endif
#if defined(cmIML_INT_HAVE_UINTPTR_T) && defined(SCNuPTR) \
  && !defined(cmIML_INT_BROKEN_SCNuPTR)
# define cmIML_INT_SCNuPTR SCNuPTR
#elif cmIML_ABI_SIZEOF_DATA_PTR == 4
# define cmIML_INT_SCNuPTR cmIML_INT_SCNu32
#elif !defined(cmIML_INT_NO_UINT64_T)
# define cmIML_INT_SCNuPTR cmIML_INT_SCNu64
#endif
#if defined(cmIML_INT_HAVE_UINTPTR_T) && defined(PRIxPTR) \
  && !defined(cmIML_INT_BROKEN_PRIxPTR)
# define cmIML_INT_PRIxPTR PRIxPTR
#elif cmIML_ABI_SIZEOF_DATA_PTR == 4
# define cmIML_INT_PRIxPTR cmIML_INT_PRIx32
#elif !defined(cmIML_INT_NO_UINT64_T)
# define cmIML_INT_PRIxPTR cmIML_INT_PRIx64
#endif
#if defined(cmIML_INT_HAVE_UINTPTR_T) && defined(SCNxPTR) \
  && !defined(cmIML_INT_BROKEN_SCNxPTR)
# define cmIML_INT_SCNxPTR SCNxPTR
#elif cmIML_ABI_SIZEOF_DATA_PTR == 4
# define cmIML_INT_SCNxPTR cmIML_INT_SCNx32
#elif !defined(cmIML_INT_NO_UINT64_T)
# define cmIML_INT_SCNxPTR cmIML_INT_SCNx64
#endif
#if defined(cmIML_INT_HAVE_UINTPTR_T) && defined(PRIXPTR) \
  && !defined(cmIML_INT_BROKEN_PRIXPTR)
# define cmIML_INT_PRIXPTR PRIXPTR
#elif cmIML_ABI_SIZEOF_DATA_PTR == 4
# define cmIML_INT_PRIXPTR cmIML_INT_PRIX32
#elif !defined(cmIML_INT_NO_UINT64_T)
# define cmIML_INT_PRIXPTR cmIML_INT_PRIX64
#endif

/*--------------------------------------------------------------------------*/
#if !defined(cmIML_INT_NO_VERIFY)
#define cmIML_INT__VERIFY(n, x, y) extern int (*n)[x]; extern int (*n)[y]
#define cmIML_INT__VERIFY_BOOL(m, b) cmIML_INT__VERIFY(m##__VERIFY__, 2, (b)?2:3)
#define cmIML_INT__VERIFY_TYPE(t, s) cmIML_INT__VERIFY(t##__VERIFY__, s, sizeof(t))
#define cmIML_INT__VERIFY_SIGN(t, u, o) cmIML_INT__VERIFY_BOOL(t##__SIGN, (t)((u)1 << ((sizeof(t)<<3)-1)) o 0)

cmIML_INT__VERIFY_TYPE(cmIML_INT_int8_t,    1);
cmIML_INT__VERIFY_TYPE(cmIML_INT_uint8_t,   1);
cmIML_INT__VERIFY_TYPE(cmIML_INT_int16_t,   2);
cmIML_INT__VERIFY_TYPE(cmIML_INT_uint16_t,  2);
cmIML_INT__VERIFY_TYPE(cmIML_INT_int32_t,   4);
cmIML_INT__VERIFY_TYPE(cmIML_INT_uint32_t,  4);
#if !defined(cmIML_INT_NO_INT64_T)
cmIML_INT__VERIFY_TYPE(cmIML_INT_int64_t,   8);
#endif
#if !defined(cmIML_INT_NO_UINT64_T)
cmIML_INT__VERIFY_TYPE(cmIML_INT_uint64_t,  8);
#endif
#if !defined(cmIML_INT_NO_INTPTR_T)
cmIML_INT__VERIFY_TYPE(cmIML_INT_intptr_t,  sizeof(void*));
#endif
#if !defined(cmIML_INT_NO_UINTPTR_T)
cmIML_INT__VERIFY_TYPE(cmIML_INT_uintptr_t, sizeof(void*));
#endif

cmIML_INT__VERIFY_SIGN(cmIML_INT_int8_t,    cmIML_INT_uint8_t,   <);
cmIML_INT__VERIFY_SIGN(cmIML_INT_uint8_t,   cmIML_INT_uint8_t,   >);
cmIML_INT__VERIFY_SIGN(cmIML_INT_int16_t,   cmIML_INT_uint16_t,  <);
cmIML_INT__VERIFY_SIGN(cmIML_INT_uint16_t,  cmIML_INT_uint16_t,  >);
cmIML_INT__VERIFY_SIGN(cmIML_INT_int32_t,   cmIML_INT_uint32_t,  <);
cmIML_INT__VERIFY_SIGN(cmIML_INT_uint32_t,  cmIML_INT_uint32_t,  >);
#if !defined(cmIML_INT_NO_INT64_T)
cmIML_INT__VERIFY_SIGN(cmIML_INT_int64_t,   cmIML_INT_uint64_t,  <);
#endif
#if !defined(cmIML_INT_NO_UINT64_T)
cmIML_INT__VERIFY_SIGN(cmIML_INT_uint64_t,  cmIML_INT_uint64_t,  >);
#endif
#if !defined(cmIML_INT_NO_INTPTR_T)
cmIML_INT__VERIFY_SIGN(cmIML_INT_intptr_t,  cmIML_INT_uintptr_t, <);
#endif
#if !defined(cmIML_INT_NO_UINTPTR_T)
cmIML_INT__VERIFY_SIGN(cmIML_INT_uintptr_t, cmIML_INT_uintptr_t, >);
#endif

#undef cmIML_INT__VERIFY_SIGN
#undef cmIML_INT__VERIFY_TYPE
#undef cmIML_INT__VERIFY_BOOL
#undef cmIML_INT__VERIFY

#endif

#endif
