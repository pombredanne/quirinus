/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_CONFIG_ARCH_HPP
#define QUIRINUS_CORE_CONFIG_ARCH_HPP


#if defined(__alpha__) \
|| defined(__alpha) \
|| defined(_M_ALPHA)
  #if !defined(QUIRINUS_ARCH)
    #define QUIRINUS_ARCH_ALPHA
    #define QUIRINUS_ARCH "Alpha"
  #endif
#endif

#if defined(__amd64__) \
|| defined(__x86_64__) \
|| defined(__x86_64) \
|| defined(__amd64) \
|| defined(_M_X64) \
|| defined(_M_AMD64)
  #if !defined(QUIRINUS_ARCH)
    #define QUIRINUS_ARCH_AMD64
    #define QUIRINUS_ARCH "AMD64"
  #endif
#endif

#if defined(__arm__)
  #if !defined(QUIRINUS_ARCH)
    #define QUIRINUS_ARCH_ARM
    #define QUIRINUS_ARCH "ARM"
  #endif
#endif

#if defined(__aarch64__)
  #if !defined(QUIRINUS_ARCH)
    #define QUIRINUS_ARCH_ARM64
    #define QUIRINUS_ARCH "ARM64"
  #endif
#endif

#if defined(__convex__)
  #if !defined(QUIRINUS_ARCH)
    #define QUIRINUS_ARCH_CONVEX
    #define QUIRINUS_ARCH "Convex"
  #endif
#endif

#if defined(__epiphany__)
  #if !defined(QUIRINUS_ARCH)
    #define QUIRINUS_ARCH_EPIPHANY
    #define QUIRINUS_ARCH "Epiphany"
  #endif
#endif

#if defined(__hppa__)
  #if !defined(QUIRINUS_ARCH)
    #define QUIRINUS_ARCHA
    #define QUIRINUS_ARCH "HP/PA RISC"
  #endif
#endif

#if defined(i386) \
|| defined(__i386__) \
|| defined(__IA32__) \
|| defined(_M_IX86) \
|| defined(__X86__) \
|| defined(__I86__) \
|| defined(__i386) \
|| defined(_X86_)
  #if !defined(QUIRINUS_ARCH)
    #define QUIRINUS_ARCH_X86
    #define QUIRINUS_ARCH "Intel x86"
  #endif
#endif

#if defined(__ia64__) \
|| defined(_IA64) \
|| defined(__ia64) \
|| defined(_M_IA64) \
|| defined(__IA64__) \
|| defined(__itanium__)
  #if !defined(QUIRINUS_ARCH)
    #define QUIRINUS_ARCH_IA64
    #define QUIRINUS_ARCH "Intel IA-64"
  #endif
#endif

#if defined(__m68k__) \
|| defined(__MC68K__) \
|| defined(M68000)
  #if !defined(QUIRINUS_ARCH)
    #define QUIRINUS_ARCH_M68K
    #define QUIRINUS_ARCH "Motorola 68k"
  #endif
#endif

#if defined(__mips__) \
|| defined(mips) \
|| defined(__mips) \
|| defined(__MIPS__)
  #if !defined(QUIRINUS_ARCH)
    #define QUIRINUS_ARCH_MIPS
    #define QUIRINUS_ARCH "MIPS"
  #endif
#endif

#if defined(__powerpc__) \
|| defined(__ppc__) \
|| defined(__powerpc) \
|| defined(__POWERPC__) \
|| defined(_M_PPC) \
|| defined(_ARCH_PPC) \
|| defined(__PPCGECKO__) \
|| defined(__PPCBROADWAY__)
  #if !defined(QUIRINUS_ARCH)
    #define QUIRINUS_ARCH_POWERPC
    #define QUIRINUS_ARCH "PowerPC"
  #endif
#endif

#if defined(pyr)
  #if !defined(QUIRINUS_ARCH)
    #define QUIRINUS_ARCH_PYRAMID
    #define QUIRINUS_ARCH "Pyramid 9810"
  #endif
#endif

#if defined(__sparc__) \
|| defined(__sparc)
  #if !defined(QUIRINUS_ARCH)
    #define QUIRINUS_ARCH_SPARC
    #define QUIRINUS_ARCH "SPARC"
  #endif
#endif

#if defined(__sh__)
  #if !defined(QUIRINUS_ARCH)
    #define QUIRINUS_ARCH_SUPERH
    #define QUIRINUS_ARCH "SuperH"
  #endif
#endif

#if defined(__370__)
  #if !defined(QUIRINUS_ARCH)
    #define QUIRINUS_ARCH_SYSTEM370
    #define QUIRINUS_ARCH "System/370"
  #endif
#endif

#if defined(__s390__)
  #if !defined(QUIRINUS_ARCH)
    #define QUIRINUS_ARCH_SYSTEM390
    #define QUIRINUS_ARCH
  #endif
#endif

#if defined(__SYSC_ZARCH__)
  #if !defined(QUIRINUS_ARCH)
    #define QUIRINUS_ARCH_ZARCH
    #define QUIRINUS_ARCH "z/Architecture"
  #endif
#endif

#if !defined(QUIRINUS_ARCH)
  #define QUIRINUS_ARCH ""
#endif


#endif // QUIRINUS_CORE_CONFIG_ARCH_HPP
