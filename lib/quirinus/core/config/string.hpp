/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_CONFIG_STRING_HPP
#define QUIRINUS_CORE_CONFIG_STRING_HPP
#include "stdint.hpp"


#define UNICODE_MIN 0x000000
#define UNICODE_MAX 0x10FFFF


// Unicode error states
#define UNICODE_STATE_SUCCESS     0   // success
#define UNICODE_STATE_NULLPTR     1   // null pointer
#define UNICODE_STATE_ISOLATED    2   // isolated code point
#define UNICODE_STATE_OVERLONG    3   // overlong code point
#define UNICODE_STATE_TRUNCATED   4   // truncated code point
#define UNICODE_STATE_ILLEGAL     5   // illegal code point
#define UNICODE_STATE_HEADER      6   // incorrect most significant bits
#define UNICODE_STATE_SURROGATE   7   // missing high or low surrogate


#if !defined(UNICODE_WCHAR_SIZE)
  #if defined(__SIZEOF_WCHAR_T__)
    #if (__SIZEOF_WCHAR_T__ == 4)
      #define UNICODE_WCHAR_SIZE 4
    #else
      #define UNICODE_WCHAR_SIZE 2
    #endif
  #elif defined(__WCHAR_MAX__)
    #if (__WCHAR_MAX__ > 0xFFFF)
      #define UNICODE_WCHAR_SIZE 4
    #else
      #define UNICODE_WCHAR_SIZE 2
    #endif
  #else
    #if (WCHAR_MAX > 0xFFFF)
      #define UNICODE_WCHAR_SIZE 4
    #else
      #define UNICODE_WCHAR_SIZE 2
    #endif
  #endif
#endif

#endif // QUIRINUS_CORE_CONFIG_STRING_HPP
