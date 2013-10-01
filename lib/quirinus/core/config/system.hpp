/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_CONFIG_SYSTEM_HPP
#define QUIRINUS_CORE_CONFIG_SYSTEM_HPP


#if defined(AMIGA) \
|| defined(__amigaos__)
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_AMIGAOS
    #define QUIRINUS_OS "AmigaOS"
  #endif
#endif

#if defined(_AIX) \
|| defined(__TOS_AIX__)
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_AIX
    #define QUIRINUS_OS "AIX"
  #endif
#endif

#if defined(__ANDROID__)
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_ANDROID
    #define QUIRINUS_OS "Android"
  #endif
#endif

#if defined(__BEOS__)
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_BEOS
    #define QUIRINUS_OS "BeOS"
  #endif
#endif


#if defined(__CYGWIN__)
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_CYGWIN
    #define QUIRINUS_OS "Cygwin"
  #endif
#endif

#if defined(DGUX) \
|| defined(__dgux__) \
|| defined(__DGUX__)
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_DGUX
    #define QUIRINUS_OS "DG-UX"
  #endif
#endif

#if defined(bsdi) \
|| defined(__bsdi__)
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_BSDI
    #define QUIRINUS_OS "BSDI"
  #endif
#endif

#if defined(__FreeBSD__)
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_FREEBSD
    #define QUIRINUS_OS "FreeBSD"
  #endif
#endif

#if defined(__DragonFly__)
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_DRAGONFLY
    #define QUIRINUS_OS "DragonFly"
  #endif
#endif

#if defined(_CRAY) \
|| defined(_UNICOS)
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_GRAY
    #define QUIRINUS_OS "GRAY"
  #endif
#endif

#if defined(hpux) \
|| defined(__hpux) \
|| defined(_HPUX_SOURCE)
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_HPUX
    #define QUIRINUS_OS "HP-UX"
  #endif
#endif

#if defined(__GNU__) \
|| defined(__gnu_hurd__)
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_HURD
    #define QUIRINUS_OS "GNU/Hurd"
  #endif
#endif

#if defined(sgi) \
|| defined(__sgi) \
|| defined(mips) \
|| defined(_SGI_SOURCE)
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_IRIX
    #define QUIRINUS_OS "IRIX"
  #endif
#endif

#if (defined(__FreeBSD_kernel__) && defined(__GLIBC__))
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_KFREEBSD
    #define QUIRINUS_OS "GNU/kFreeBSD"
  #endif
#endif

#if defined(linux) \
|| defined(__linux) \
|| defined(__linux__)
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_LINUX
    #define QUIRINUS_OS "Linux"
  #endif
#endif

#if defined(__Lynx__)
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_LYNXOS
    #define QUIRINUS_OS "LynxOS"
  #endif
#endif

#if defined(macintosh) \
|| defined(Macintosh) \
|| defined(__MACOS__)
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_MACOS
    #define QUIRINUS_OS "MacOS"
  #endif
#endif

#if defined(__MACOSX__) \
|| (defined(__APPLE__) && defined(__MACH__))
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_MACOSX
    #define QUIRINUS_OS "MacOSX"
  #endif
#endif

#if defined(__minix)
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_MINIX
    #define QUIRINUS_OS "Minix"
  #endif
#endif

  #if defined(__MORPHOS__)
    #define QUIRINUS_OS_MORPHOS
    #define QUIRINUS_OS "MorphOS"
  #endif

#if defined(mpeix) \
|| defined(__mpexl)
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_MPEIX
    #define QUIRINUS_OS "MPEIX"
  #endif
#endif

#if defined(MSDOS) \
|| defined(_MSDOS) \
|| defined(__DOS__) \
|| defined(__MSDOS__)
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_MSDOS
    #define QUIRINUS_OS "MS-DOS"
  #endif
#endif

#if defined(__NetBSD__)
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_NETBSD
    #define QUIRINUS_OS "NetBSD"
  #endif
#endif

#if defined(__OpenBSD__)
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_OPENBSD
    #define QUIRINUS_OS "OpenBSD"
  #endif
#endif

#if defined(OS2) \
|| defined(_OS2) \
|| defined(__OS2__) \
|| defined(__TOS_OS2__)
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_OS2
    #define QUIRINUS_OS "OS/2"
  #endif
#endif

#if defined(__QNX__) \
|| defined(__QNXNTO__)
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_QNX
    #define QUIRINUS_OS "QNX"
  #endif
#endif

#if defined(sun) \
|| defined(__sun__) \
|| defined(__SUNPRO_C)
  #if !defined(QUIRINUS_OS)
    #if defined(__SVR4) \
    || defined(__svr4__)
      #define QUIRINUS_OS_SOLARIS
      #define QUIRINUS_OS "Solaris"
    #else
      #define QUIRINUS_OS_SUN
      #define QUIRINUS_OS "Sun"
    #endif
  #endif
#endif

#if defined(__SYMBIAN32__)
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_SYMBIAN
    #define QUIRINUS_OS "SymbianOS"
  #endif
#endif

#if defined(ultrix) \
|| defined(__ultrix) \
|| defined(__ultrix__)
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_ULTRIX
    #define QUIRINUS_OS "ULTRIX"
  #endif
#endif

#if defined(_WIN16) \
|| defined(_WIN32) \
|| defined(_WIN64) \
|| defined(__WINDOWS__) \
|| defined(__MINGW32__) \
|| defined(__MINGW64__)
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_WINDOWS
    #define QUIRINUS_OS "Windows"
  #endif
#endif

#if defined(_WIN32_WCE)
  #if !defined(QUIRINUS_OS)
    #define QUIRINUS_OS_WINDOWSCE
    #define QUIRINUS_OS "WindowsCE"
  #endif
#endif

#if !defined(QUIRINUS_OS)
  #define QUIRINUS_OS ""
#endif


#endif // QUIRINUS_CORE_CONFIG_SYSTEM_HPP
