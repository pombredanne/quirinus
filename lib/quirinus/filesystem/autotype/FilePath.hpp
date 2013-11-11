/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_AUTOTYPE_FILEPATH_HPP
#define QUIRINUS_AUTOTYPE_FILEPATH_HPP
namespace quirinus {


// char type
template <>
struct autotype<filesystem::FilePath, const char*>
{ typedef filesystem::FilePath type; };

template <>
struct autotype<const char*, filesystem::FilePath>
{ typedef filesystem::FilePath type; };

template <size_t COUNT>
struct autotype<filesystem::FilePath, char[COUNT]>
{ typedef filesystem::FilePath type; };

template <size_t COUNT>
struct autotype<char[COUNT], filesystem::FilePath>
{ typedef filesystem::FilePath type; };


// wchar_t type
template <>
struct autotype<filesystem::FilePath, const wchar_t*>
{ typedef filesystem::FilePath type; };

template <>
struct autotype<const wchar_t*, filesystem::FilePath>
{ typedef filesystem::FilePath type; };

template <size_t COUNT>
struct autotype<filesystem::FilePath, wchar_t[COUNT]>
{ typedef filesystem::FilePath type; };

template <size_t COUNT>
struct autotype<wchar_t[COUNT], filesystem::FilePath>
{ typedef filesystem::FilePath type; };


// bytechar type
template <>
struct autotype<filesystem::FilePath, const bytechar*>
{ typedef filesystem::FilePath type; };

template <>
struct autotype<const bytechar*, filesystem::FilePath>
{ typedef filesystem::FilePath type; };

template <size_t COUNT>
struct autotype<filesystem::FilePath, bytechar[COUNT]>
{ typedef filesystem::FilePath type; };

template <size_t COUNT>
struct autotype<bytechar[COUNT], filesystem::FilePath>
{ typedef filesystem::FilePath type; };


// widechar type
template <>
struct autotype<filesystem::FilePath, const widechar*>
{ typedef filesystem::FilePath type; };

template <>
struct autotype<const widechar*, filesystem::FilePath>
{ typedef filesystem::FilePath type; };

template <size_t COUNT>
struct autotype<filesystem::FilePath, widechar[COUNT]>
{ typedef filesystem::FilePath type; };

template <size_t COUNT>
struct autotype<widechar[COUNT], filesystem::FilePath>
{ typedef filesystem::FilePath type; };


// unicode type
template <>
struct autotype<filesystem::FilePath, const unicode*>
{ typedef filesystem::FilePath type; };

template <>
struct autotype<const unicode*, filesystem::FilePath>
{ typedef filesystem::FilePath type; };

template <size_t COUNT>
struct autotype<filesystem::FilePath, unicode[COUNT]>
{ typedef filesystem::FilePath type; };

template <size_t COUNT>
struct autotype<unicode[COUNT], filesystem::FilePath>
{ typedef filesystem::FilePath type; };


// Bytes type
template <>
struct autotype<filesystem::FilePath, Bytes>
{ typedef filesystem::FilePath type; };

template <>
struct autotype<Bytes, filesystem::FilePath>
{ typedef filesystem::FilePath type; };


// Unicode type
template <>
struct autotype<filesystem::FilePath, Unicode>
{ typedef filesystem::FilePath type; };

template <>
struct autotype<Unicode, filesystem::FilePath>
{ typedef filesystem::FilePath type; };


} // namespace quirinus
#endif // QUIRINUS_AUTOTYPE_FILEPATH_HPP
