/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_TYPEINFO_INT_HPP
#define QUIRINUS_TYPEINFO_INT_HPP
namespace quirinus {


template <>
struct Int::typeinfo<signed char>
{
  typedef signed char type;
  typedef signed char stype;
  typedef unsigned char utype;
  static const bool sign = true;
  static const size_t typeno = 0;
  static const signed char min = SCHAR_MIN;
  static const signed char max = SCHAR_MAX;
};

template <>
struct Int::typeinfo<unsigned char>
{
  typedef unsigned char type;
  typedef signed char stype;
  typedef unsigned char utype;
  static const bool sign = false;
  static const size_t typeno = 1;
  static const unsigned char min = 0;
  static const unsigned char max = UCHAR_MAX;
};


template <>
struct Int::typeinfo<signed short>
{
  typedef signed short type;
  typedef signed short stype;
  typedef unsigned short utype;
  static const bool sign = true;
  static const size_t typeno = 2;
  static const signed short min = SHRT_MIN;
  static const signed short max = SHRT_MAX;
};

template <>
struct Int::typeinfo<unsigned short>
{
  typedef unsigned short type;
  typedef signed short stype;
  typedef unsigned short utype;
  static const bool sign = false;
  static const size_t typeno = 3;
  static const unsigned short min = 0;
  static const unsigned short max = USHRT_MAX;
};


template <>
struct Int::typeinfo<signed int>
{
  typedef signed int type;
  typedef signed int stype;
  typedef unsigned int utype;
  static const bool sign = true;
  static const size_t typeno = 4;
  static const signed int min = INT_MIN;
  static const signed int max = INT_MAX;
};

template <>
struct Int::typeinfo<unsigned int>
{
  typedef unsigned int type;
  typedef signed int stype;
  typedef unsigned int utype;
  static const bool sign = false;
  static const size_t typeno = 5;
  static const unsigned int min = 0;
  static const unsigned int max = UINT_MAX;
};


template <>
struct Int::typeinfo<signed long>
{
  typedef signed long type;
  typedef signed long stype;
  typedef unsigned long utype;
  static const bool sign = true;
  static const size_t typeno = 6;
  static const signed long min = LONG_MIN;
  static const signed long max = LONG_MAX;
};

template <>
struct Int::typeinfo<unsigned long>
{
  typedef unsigned long type;
  typedef signed long stype;
  typedef unsigned long utype;
  static const bool sign = false;
  static const size_t typeno = 7;
  static const signed long min = 0;
  static const signed long max = ULONG_MAX;
};


#if (QUIRINUS_FEATURE_LONGLONG)
template <>
struct Int::typeinfo<signed long long>
{
  typedef signed long long type;
  typedef signed long long stype;
  typedef unsigned long long utype;
  static const bool sign = true;
  static const size_t typeno = 8;
  static const signed long long min = LLONG_MIN;
  static const signed long long max = LLONG_MAX;
};

template <>
struct Int::typeinfo<unsigned long long>
{
  typedef unsigned long long type;
  typedef signed long long stype;
  typedef unsigned long long utype;
  static const bool sign = false;
  static const size_t typeno = 9;
  static const signed long long min = 0;
  static const signed long long max = ULLONG_MAX;
};
#endif


#if (QUIRINUS_FEATURE_INT128)
template <>
struct Int::typeinfo<int128_t>
{
  typedef int128_t type;
  typedef int128_t stype;
  typedef uint128_t utype;
  static const bool sign = true;
  static const size_t typeno = 10;
  static const int128_t min = LLONG_MIN;
  static const int128_t max = LLONG_MAX;
};

template <>
struct Int::typeinfo<uint128_t>
{
  typedef uint128_t type;
  typedef int128_t stype;
  typedef uint128_t utype;
  static const bool sign = false;
  static const size_t typeno = 11;
  static const int128_t min = 0;
  static const int128_t max = 0;
};
#endif


} // namespace quirinus
#endif // QUIRINUS_TYPEINFO_INT_HPP
