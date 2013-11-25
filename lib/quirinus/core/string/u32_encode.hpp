/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_STRING_U32_ENCODE_HPP
#define QUIRINUS_CORE_STRING_U32_ENCODE_HPP
#include "character.hpp"
#include "u32_ucslen.hpp"
namespace quirinus {


int
u32_encode(const unicode* decptr,
           const size_t& declen,
           bytechar*& encptr,
           size_t& enclen,
           size_t& offset);


int
u32_encode(const std::vector<unicode>& dec,
           std::vector<bytechar>& enc,
           size_t& offset);


} // namespace quirinus
#endif // QUIRINUS_CORE_STRING_U32_ENCODE_HPP
