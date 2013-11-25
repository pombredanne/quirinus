/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_STRING_NULLSTRLEN_HPP
#define QUIRINUS_CORE_STRING_NULLSTRLEN_HPP
#include "character.hpp"
namespace quirinus {


size_t
nullstrlen(const bytechar* str);


size_t
nullstrlen(const widechar* str);


size_t
nullstrlen(const unicode* str);


size_t
nullstrlen(const char* str);


size_t
nullstrlen(const wchar_t* str);


} // namespace quirinus
#endif // QUIRINUS_CORE_STRING_NULLSTRLEN_HPP
