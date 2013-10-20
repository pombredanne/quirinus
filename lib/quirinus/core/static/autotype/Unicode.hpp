/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_STATIC_AUTOTYPE_UNICODE_HPP
#define QUIRINUS_CORE_STATIC_AUTOTYPE_UNICODE_HPP
namespace quirinus {


// Unicode type
template <>
struct autotype<Unicode, Unicode>
{ typedef Unicode type; };


// char type
template <>
struct autotype<Unicode, const char*>
{ typedef Unicode type; };

template <>
struct autotype<const char*, Unicode>
{ typedef Unicode type; };

template <size_t COUNT>
struct autotype<Unicode, char[COUNT]>
{ typedef Unicode type; };

template <size_t COUNT>
struct autotype<char[COUNT], Unicode>
{ typedef Unicode type; };


// wchar_t type
template <>
struct autotype<Unicode, const wchar_t*>
{ typedef Unicode type; };

template <>
struct autotype<const wchar_t*, Unicode>
{ typedef Unicode type; };

template <size_t COUNT>
struct autotype<Unicode, wchar_t[COUNT]>
{ typedef Unicode type; };

template <size_t COUNT>
struct autotype<wchar_t[COUNT], Unicode>
{ typedef Unicode type; };


// bytechar type
template <>
struct autotype<Unicode, const bytechar*>
{ typedef Unicode type; };

template <>
struct autotype<const bytechar*, Unicode>
{ typedef Unicode type; };

template <size_t COUNT>
struct autotype<Unicode, bytechar[COUNT]>
{ typedef Unicode type; };

template <size_t COUNT>
struct autotype<bytechar[COUNT], Unicode>
{ typedef Unicode type; };


// widechar type
template <>
struct autotype<Unicode, const widechar*>
{ typedef Unicode type; };

template <>
struct autotype<const widechar*, Unicode>
{ typedef Unicode type; };

template <size_t COUNT>
struct autotype<Unicode, widechar[COUNT]>
{ typedef Unicode type; };

template <size_t COUNT>
struct autotype<widechar[COUNT], Unicode>
{ typedef Unicode type; };


// unicode type
template <>
struct autotype<Unicode, const unicode*>
{ typedef Unicode type; };

template <>
struct autotype<const unicode*, Unicode>
{ typedef Unicode type; };

template <size_t COUNT>
struct autotype<Unicode, unicode[COUNT]>
{ typedef Unicode type; };

template <size_t COUNT>
struct autotype<unicode[COUNT], Unicode>
{ typedef Unicode type; };


// Unicode type
template <>
struct autotype<Unicode, Bytes>
{ typedef Unicode type; };


template <>
struct autotype<Bytes, Unicode>
{ typedef Unicode type; };


} // namespace quirinus
#endif // QUIRINUS_CORE_STATIC_AUTOTYPE_UNICODE_HPP
