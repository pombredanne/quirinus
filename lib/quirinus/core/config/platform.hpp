/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_CONFIG_PLATFORM_HPP
#define QUIRINUS_CORE_CONFIG_PLATFORM_HPP


#if defined(VMS) \
|| defined(__VMS)
  #if !defined(QUIRINUS_PLATFORM)
    #define QUIRINUS_PLATFORM_VMS
    #define QUIRINUS_PLATFORM "VMS"
  #endif
#endif

#if defined(unix) \
|| defined(__unix) \
|| defined(__unix__) \
|| defined(QUIRINUS_SYSTEM_AIX) \
|| defined(QUIRINUS_SYSTEM_OSF) \
|| defined(QUIRINUS_SYSTEM_QNX) \
|| defined(QUIRINUS_SYSTEM_CYGWIN) \
|| (defined(QUIRINUS_SYSTEM_AMIGAOS) && defined(__GNUC__))
  #if !defined(QUIRINUS_PLATFORM)
    #define QUIRINUS_PLATFORM_UNIX
    #define QUIRINUS_PLATFORM "Unix"
  #endif
#endif

#if defined(QUIRINUS_SYSTEM_BSDI)\
|| defined(QUIRINUS_SYSTEM_FREEBSD) \
|| defined(QUIRINUS_SYSTEM_NETBSD) \
|| defined(QUIRINUS_SYSTEM_OPENBSD) \
|| defined(QUIRINUS_SYSTEM_DRAGONFLY) \
|| defined(_SYSTYPE_BSD)
  #if !defined(QUIRINUS_PLATFORM)
    #define QUIRINUS_PLATFORM_BSD
    #define QUIRINUS_PLATFORM "BSD"
  #endif
#endif

#if defined(QUIRINUS_SYSTEM_WINDOWS)
  #if !defined(QUIRINUS_PLATFORM)
    #define QUIRINUS_PLATFORM_WINDOWS
    #define QUIRINUS_PLATFORM "Windows"
  #endif
#endif

#if !defined(QUIRINUS_PLATFORM)
  #define QUIRINUS_PLATFORM ""
#endif


// POSIX platform include
#if defined(QUIRINUS_PLATFORM_UNIX) \
|| defined(QUIRINUS_PLATFORM_BSD)
  #include <termios.h>
#endif


// Windows platform include
#if defined(QUIRINUS_PLATFORM_WINDOWS)
  #include <io.h>
  #include <fcntl.h>
  #include <windows.h>
#endif


#endif // QUIRINUS_CORE_CONFIG_PLATFORM_HPP
