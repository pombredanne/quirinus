/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_CONFIG_SYSTEM_HPP
#define QUIRINUS_CORE_CONFIG_SYSTEM_HPP


#if defined(AMIGA) \
|| defined(__amigaos__)
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_AMIGAOS
    #define QUIRINUS_SYSTEM "AmigaOS"
  #endif
#endif


#if defined(_AIX) \
|| defined(__TOS_AIX__)
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_AIX
    #define QUIRINUS_SYSTEM "AIX"
  #endif
#endif


#if defined(__ANDROID__)
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_ANDROID
    #define QUIRINUS_SYSTEM "Android"
  #endif
#endif


#if defined(__BEOS__)
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_BEOS
    #define QUIRINUS_SYSTEM "BeOS"
  #endif
#endif


#if defined(__CYGWIN__)
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_CYGWIN
    #define QUIRINUS_SYSTEM "Cygwin"
  #endif
#endif


#if defined(DGUX) \
|| defined(__dgux__) \
|| defined(__DGUX__)
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_DGUX
    #define QUIRINUS_SYSTEM "DG-UX"
  #endif
#endif


#if defined(bsdi) \
|| defined(__bsdi__)
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_BSDI
    #define QUIRINUS_SYSTEM "BSDI"
  #endif
#endif


#if defined(__FreeBSD__)
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_FREEBSD
    #define QUIRINUS_SYSTEM "FreeBSD"
  #endif
#endif


#if defined(__DragonFly__)
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_DRAGONFLY
    #define QUIRINUS_SYSTEM "DragonFly"
  #endif
#endif


#if defined(_CRAY) \
|| defined(_UNICOS)
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_GRAY
    #define QUIRINUS_SYSTEM "GRAY"
  #endif
#endif


#if defined(hpux) \
|| defined(__hpux) \
|| defined(_HPUX_SOURCE)
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_HPUX
    #define QUIRINUS_SYSTEM "HP-UX"
  #endif
#endif


#if defined(__GNU__) \
|| defined(__gnu_hurd__)
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_HURD
    #define QUIRINUS_SYSTEM "GNU/Hurd"
  #endif
#endif


#if defined(sgi) \
|| defined(__sgi) \
|| defined(mips) \
|| defined(_SGI_SOURCE)
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_IRIX
    #define QUIRINUS_SYSTEM "IRIX"
  #endif
#endif


#if (defined(__FreeBSD_kernel__) && defined(__GLIBC__))
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_KFREEBSD
    #define QUIRINUS_SYSTEM "GNU/kFreeBSD"
  #endif
#endif


#if defined(linux) \
|| defined(__linux) \
|| defined(__linux__)
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_LINUX
    #define QUIRINUS_SYSTEM "Linux"
  #endif
#endif


#if defined(__Lynx__)
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_LYNXOS
    #define QUIRINUS_SYSTEM "LynxOS"
  #endif
#endif


#if defined(macintosh) \
|| defined(Macintosh) \
|| defined(__MACOS__)
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_MACOS
    #define QUIRINUS_SYSTEM "MacOS"
  #endif
#endif


#if defined(__MACOSX__) \
|| (defined(__APPLE__) && defined(__MACH__))
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_MACOSX
    #define QUIRINUS_SYSTEM "MacOSX"
  #endif
#endif


#if defined(__minix)
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_MINIX
    #define QUIRINUS_SYSTEM "Minix"
  #endif
#endif


#if defined(__MORPHOS__)
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_MORPHOS
    #define QUIRINUS_SYSTEM "MorphOS"
  #endif
#endif


#if defined(mpeix) \
|| defined(__mpexl)
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_MPEIX
    #define QUIRINUS_SYSTEM "MPEIX"
  #endif
#endif


#if defined(MSDOS) \
|| defined(_MSDOS) \
|| defined(__DOS__) \
|| defined(__MSDOS__)
  #error Quirinus does not support this system
#endif


#if defined(__NetBSD__)
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_NETBSD
    #define QUIRINUS_SYSTEM "NetBSD"
  #endif
#endif


#if defined(__OpenBSD__)
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_OPENBSD
    #define QUIRINUS_SYSTEM "OpenBSD"
  #endif
#endif


#if defined(OS2) \
|| defined(_OS2) \
|| defined(__OS2__) \
|| defined(__TOS_OS2__)
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_OS2
    #define QUIRINUS_SYSTEM "OS/2"
  #endif
#endif


#if defined(__QNX__) \
|| defined(__QNXNTO__)
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_QNX
    #define QUIRINUS_SYSTEM "QNX"
  #endif
#endif


#if defined(sun) \
|| defined(__sun__) \
|| defined(__SUNPRO_C)
  #if !defined(QUIRINUS_SYSTEM)
    #if defined(__SVR4) \
    || defined(__svr4__)
      #define QUIRINUS_SYSTEM_SOLARIS
      #define QUIRINUS_SYSTEM "Solaris"
    #else
      #define QUIRINUS_SYSTEM_SUN
      #define QUIRINUS_SYSTEM "Sun"
    #endif
  #endif
#endif


#if defined(__SYMBIAN32__)
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_SYMBIAN
    #define QUIRINUS_SYSTEM "SymbianOS"
  #endif
#endif


#if defined(ultrix) \
|| defined(__ultrix) \
|| defined(__ultrix__)
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_ULTRIX
    #define QUIRINUS_SYSTEM "ULTRIX"
  #endif
#endif


#if defined(_WIN16) \
|| defined(__WIN16__)
  #error Quirinus does not support this system
#endif
#if defined(_WIN32) \
|| defined(__WIN32__) \
|| defined(_WIN64) \
|| defined(__WIN64__) \
|| defined(__WINDOWS__) \
|| defined(__MINGW32__) \
|| defined(__MINGW64__)
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_WINDOWS
    #define QUIRINUS_SYSTEM "Windows"
  #endif
#endif
#if (defined(_WIN32) && !defined(__WIN32__))
  #define __WIN32__ _WIN32
#endif
#if (defined(_WIN64) && !defined(__WIN64__))
  #define __WIN64__ _WIN64
#endif


#if defined(_WIN32_WCE)
  #if !defined(QUIRINUS_SYSTEM)
    #define QUIRINUS_SYSTEM_WINDOWSCE
    #define QUIRINUS_SYSTEM "WindowsCE"
  #endif
#endif


#if !defined(QUIRINUS_SYSTEM)
  #define QUIRINUS_SYSTEM ""
#endif


#endif // QUIRINUS_CORE_CONFIG_SYSTEM_HPP
