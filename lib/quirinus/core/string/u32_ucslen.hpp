/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_STRING_U32_UCSLEN_HPP
#define QUIRINUS_CORE_STRING_U32_UCSLEN_HPP
#include "character.hpp"
namespace quirinus {


int
u32_ucslen(const unicode* iter,
           const size_t& declen,
           size_t& enclen,
           size_t& offset);


} // namespace quirinus
#endif // QUIRINUS_CORE_STRING_U32_UCSLEN_HPP
