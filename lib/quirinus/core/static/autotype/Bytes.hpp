/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_STATIC_AUTOTYPE_BYTES_HPP
#define QUIRINUS_CORE_STATIC_AUTOTYPE_BYTES_HPP
namespace quirinus {


template <>
struct autotype<Bytes, Bytes>
{ typedef Bytes type; };


template <>
struct autotype<Bytes, const char*>
{ typedef Bytes type; };


template <>
struct autotype<const char*, Bytes>
{ typedef Bytes type; };


template <size_t COUNT>
struct autotype<Bytes, char[COUNT]>
{ typedef Bytes type; };


template <size_t COUNT>
struct autotype<char[COUNT], Bytes>
{ typedef Bytes type; };


template <>
struct autotype<Bytes, const wchar_t*>
{ typedef Unicode type; };


template <>
struct autotype<const wchar_t*, Bytes>
{ typedef Unicode type; };


template <size_t COUNT>
struct autotype<Bytes, wchar_t[COUNT]>
{ typedef Bytes type; };


template <size_t COUNT>
struct autotype<wchar_t[COUNT], Bytes>
{ typedef Bytes type; };


template <>
struct autotype<Bytes, const bytechar*>
{ typedef Bytes type; };


template <>
struct autotype<const bytechar*, Bytes>
{ typedef Bytes type; };


template <>
struct autotype<Bytes, const widechar*>
{ typedef Unicode type; };


template <>
struct autotype<const widechar*, Bytes>
{ typedef Unicode type; };


template <>
struct autotype<Bytes, const unicode*>
{ typedef Unicode type; };


template <>
struct autotype<const unicode*, Bytes>
{ typedef Unicode type; };


} // namespace quirinus
#endif // QUIRINUS_CORE_STATIC_AUTOTYPE_BYTES_HPP
