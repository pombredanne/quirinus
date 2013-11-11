/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_AUTOTYPE_BYTES_HPP
#define QUIRINUS_AUTOTYPE_BYTES_HPP
namespace quirinus {


// char type
template <>
struct autotype<Bytes, const char*>
{ typedef Bytes type; };

template <>
struct autotype<const char*, Bytes>
{ typedef Bytes type; };

template <size_t SIZE>
struct autotype<Bytes, char[SIZE]>
{ typedef Bytes type; };

template <size_t SIZE>
struct autotype<char[SIZE], Bytes>
{ typedef Bytes type; };


// wchar_t type
template <>
struct autotype<Bytes, const wchar_t*>
{ typedef Unicode type; };

template <>
struct autotype<const wchar_t*, Bytes>
{ typedef Unicode type; };

template <size_t SIZE>
struct autotype<Bytes, wchar_t[SIZE]>
{ typedef Unicode type; };

template <size_t SIZE>
struct autotype<wchar_t[SIZE], Bytes>
{ typedef Unicode type; };


// bytechar type
template <>
struct autotype<Bytes, const bytechar*>
{ typedef Bytes type; };

template <>
struct autotype<const bytechar*, Bytes>
{ typedef Bytes type; };

template <size_t SIZE>
struct autotype<Bytes, bytechar[SIZE]>
{ typedef Bytes type; };

template <size_t SIZE>
struct autotype<bytechar[SIZE], Bytes>
{ typedef Bytes type; };


// widechar type
template <>
struct autotype<Bytes, const widechar*>
{ typedef Unicode type; };

template <>
struct autotype<const widechar*, Bytes>
{ typedef Unicode type; };

template <size_t SIZE>
struct autotype<Bytes, widechar[SIZE]>
{ typedef Unicode type; };

template <size_t SIZE>
struct autotype<widechar[SIZE], Bytes>
{ typedef Unicode type; };


// unicode type
template <>
struct autotype<Bytes, const unicode*>
{ typedef Unicode type; };

template <>
struct autotype<const unicode*, Bytes>
{ typedef Unicode type; };

template <size_t SIZE>
struct autotype<Bytes, unicode[SIZE]>
{ typedef Unicode type; };

template <size_t SIZE>
struct autotype<unicode[SIZE], Bytes>
{ typedef Unicode type; };


} // namespace quirinus
#endif // QUIRINUS_AUTOTYPE_BYTES_HPP
