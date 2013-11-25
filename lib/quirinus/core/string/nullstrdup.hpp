/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_STRING_NULLSTRDUP_HPP
#define QUIRINUS_CORE_STRING_NULLSTRDUP_HPP
#include "character.hpp"
#include "nullstrlen.hpp"
namespace quirinus {


bytechar*
nullstrdup(const bytechar* str);


widechar*
nullstrdup(const widechar* str);


unicode*
nullstrdup(const unicode* str);


char*
nullstrdup(const char* str);


wchar_t*
nullstrdup(const wchar_t* str);


} // namespace quirinus
#endif // QUIRINUS_CORE_STRING_NULLSTRDUP_HPP
