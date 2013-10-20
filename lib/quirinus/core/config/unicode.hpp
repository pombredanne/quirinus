/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_CONFIG_UNICODE_HPP
#define QUIRINUS_CORE_CONFIG_UNICODE_HPP
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


// Type definitions
namespace quirinus {


// Character types
typedef uint8_t bytechar;
#if (QUIRINUS_FEATURE_CXX11)
typedef char16_t widechar;
typedef char32_t unicode;
#else
typedef uint16_t widechar;
typedef uint32_t unicode;
#endif

// Vector types
typedef std::vector<char> charstack;
typedef std::vector<wchar_t> wcharstack;
typedef std::vector<bytechar> bytecharstack;
typedef std::vector<widechar> widecharstack;
typedef std::vector<unicode> unicodestack;

// Stream types
typedef std::basic_istream< char, std::char_traits<char> > icharstream;
typedef std::basic_istream< char, std::char_traits<char> > iwcharstream;
typedef std::basic_ostream< char, std::char_traits<char> > ocharstream;
typedef std::basic_ostream< wchar_t, std::char_traits<wchar_t> > owcharstream;


} // namespace quirinus
#endif // QUIRINUS_CORE_CONFIG_UNICODE_HPP
