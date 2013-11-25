/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_STRING_U16_MBSLEN_HPP
#define QUIRINUS_CORE_STRING_U16_MBSLEN_HPP
#include "character.hpp"
namespace quirinus {


int
u16_mbslen(const bytechar* iter,
           const size_t& enclen,
           size_t& declen,
           size_t& offset);


} // namespace quirinus
#endif // QUIRINUS_CORE_STRING_U16_MBSLEN_HPP
