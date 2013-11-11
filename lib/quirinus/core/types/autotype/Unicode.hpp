/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_AUTOTYPE_UNICODE_HPP
#define QUIRINUS_AUTOTYPE_UNICODE_HPP
namespace quirinus {


// char type
template <>
struct autotype<Unicode, const char*>
{ typedef Unicode type; };

template <>
struct autotype<const char*, Unicode>
{ typedef Unicode type; };

template <size_t SIZE>
struct autotype<Unicode, char[SIZE]>
{ typedef Unicode type; };

template <size_t SIZE>
struct autotype<char[SIZE], Unicode>
{ typedef Unicode type; };


// wchar_t type
template <>
struct autotype<Unicode, const wchar_t*>
{ typedef Unicode type; };

template <>
struct autotype<const wchar_t*, Unicode>
{ typedef Unicode type; };

template <size_t SIZE>
struct autotype<Unicode, wchar_t[SIZE]>
{ typedef Unicode type; };

template <size_t SIZE>
struct autotype<wchar_t[SIZE], Unicode>
{ typedef Unicode type; };


// bytechar type
template <>
struct autotype<Unicode, const bytechar*>
{ typedef Unicode type; };

template <>
struct autotype<const bytechar*, Unicode>
{ typedef Unicode type; };

template <size_t SIZE>
struct autotype<Unicode, bytechar[SIZE]>
{ typedef Unicode type; };

template <size_t SIZE>
struct autotype<bytechar[SIZE], Unicode>
{ typedef Unicode type; };


// widechar type
template <>
struct autotype<Unicode, const widechar*>
{ typedef Unicode type; };

template <>
struct autotype<const widechar*, Unicode>
{ typedef Unicode type; };

template <size_t SIZE>
struct autotype<Unicode, widechar[SIZE]>
{ typedef Unicode type; };

template <size_t SIZE>
struct autotype<widechar[SIZE], Unicode>
{ typedef Unicode type; };


// unicode type
template <>
struct autotype<Unicode, const unicode*>
{ typedef Unicode type; };

template <>
struct autotype<const unicode*, Unicode>
{ typedef Unicode type; };

template <size_t SIZE>
struct autotype<Unicode, unicode[SIZE]>
{ typedef Unicode type; };

template <size_t SIZE>
struct autotype<unicode[SIZE], Unicode>
{ typedef Unicode type; };


// Unicode type
template <>
struct autotype<Unicode, Bytes>
{ typedef Unicode type; };


template <>
struct autotype<Bytes, Unicode>
{ typedef Unicode type; };


} // namespace quirinus
#endif // QUIRINUS_AUTOTYPE_UNICODE_HPP
