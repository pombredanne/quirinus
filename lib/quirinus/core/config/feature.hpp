/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_CONFIG_FEATURE_HPP
#define QUIRINUS_CORE_CONFIG_FEATURE_HPP
#include "include.hpp"
#include "arch.hpp"
#include "system.hpp"
#include "platform.hpp"


// C++11 compatibility
#if (__cplusplus > 199711L) \
|| (defined(__STDCXX_VERSION__) && (__STDCXX_VERSION__ >= 201001L))
  #define QUIRINUS_FEATURE_CXX11 1
#else
  #define QUIRINUS_FEATURE_CXX11 0
#endif


// C99 long long type
#if !defined(QUIRINUS_FEATURE_LONGLONG)
  #if defined(_POSIX_V6_ILP32_OFFBIG) \
  || defined(_POSIX_V6_LPBIG_OFFBIG) \
  || defined(_POSIX_V6_LP64_OFF64) \
  || (defined(__WATCOMC__) && defined(__WATCOM_INT64__)) \
  || (defined(_MSC_VER) && (_INTEGRAL_MAX_BITS >= 64)) \
  || (defined(__BORLANDC__) && (__BORLANDC__ > 0x460)) \
  || defined(__MWERKS__) \
  || defined(__SUNPRO_C) \
  || defined(__SUNPRO_CC) \
  || defined(__APPLE_CC__) \
  || defined(__alpha) \
  || defined(__DECC) \
  || defined(_CRAYC) \
  || defined(__LONG_LONG_MAX__) \
  || defined(__SIZEOF_LONG_LONG__) \
  || (defined(LLONG_MIN) && defined(LLONG_MAX) && defined(ULLONG_MAX))
    #define QUIRINUS_FEATURE_LONGLONG 1
  #else
    #define QUIRINUS_FEATURE_LONGLONG 0
  #endif
#endif


// GCC 128-bit int type
#if !defined(QUIRINUS_FEATURE_INT128)
  #if defined(__SIZEOF_INT128__)
    #define QUIRINUS_FEATURE_INT128 1
  #else
    #define QUIRINUS_FEATURE_INT128 0
  #endif
#endif


// C99 long double type
#if !defined(QUIRINUS_FEATURE_LONGDOUBLE)
  #if defined(__SIZEOF_LONG_DOUBLE__) \
  || (defined(__LDBL_MIN__) && defined(__LDBL_MAX__))
    #define QUIRINUS_FEATURE_LONGDOUBLE 1
  #else
    #define QUIRINUS_FEATURE_LONGDOUBLE 0
  #endif
#endif


// NaN support
#if !defined(QUIRINUS_FEATURE_NAN)
  #if defined(NAN)
    #define QUIRINUS_FEATURE_NAN 1
  #else
    #define QUIRINUS_FEATURE_NAN 0
  #endif
#endif


// Infinity support
#if !defined(QUIRINUS_FEATURE_INFINITY)
  #if defined(INFINITY)
    #define QUIRINUS_FEATURE_INFINITY 1
  #else
    #define QUIRINUS_FEATURE_INFINITY 0
  #endif
#endif


// Langinfo support
#if !defined(QUIRINUS_FEATURE_LANGINFO)
  #if defined(QUIRINUS_PLATFORM_UNIX)
    #define QUIRINUS_FEATURE_LANGINFO 1
  #else
    #define QUIRINUS_FEATURE_LANGINFO 0
  #endif
#endif
#if (QUIRINUS_FEATURE_LANGINFO)
  #include <langinfo.h>
#endif


// Symlink support
#if !defined(QUIRINUS_FEATURE_SYMLINK)
  #if defined(QUIRINUS_PLATFORM_UNIX)
    #define QUIRINUS_FEATURE_SYMLINK 1
  #elif defined(QUIRINUS_PLATFORM_WINDOWS)
    #if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
      #define QUIRINUS_FEATURE_SYMLINK 1
    #else
      #define QUIRINUS_FEATURE_SYMLINK 0
    #endif
  #else
    #define QUIRINUS_FEATURE_SYMLINK 0
  #endif
#endif


// Large file system support
#if !defined(QUIRINUS_FEATURE_LFS)
  #if defined(QUIRINUS_PLATFORM_UNIX)
    #define QUIRINUS_FEATURE_LFS 1
  #elif defined(QUIRINUS_PLATFORM_WINDOWS)
    #define QUIRINUS_FEATURE_LFS 1
  #else
    #define QUIRINUS_FEATURE_LFS 0
  #endif
#endif


// POSIX file system
#if !defined(QUIRINUS_FEATURE_POSIX)
  #if defined(QUIRINUS_PLATFORM_UNIX) \
  || defined(QUIRINUS_PLATFORM_BSD)
    #define QUIRINUS_FEATURE_POSIX 1
  #else
    #define QUIRINUS_FEATURE_POSIX 0
  #endif
#endif


#endif // QUIRINUS_CORE_CONFIG_FEATURE_HPP
