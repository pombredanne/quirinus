/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_STRING_U32_DECODE_HPP
#define QUIRINUS_CORE_STRING_U32_DECODE_HPP
#include "character.hpp"
#include "u32_mbslen.hpp"
namespace quirinus {


int
u32_decode(const bytechar* encptr,
           const size_t& enclen,
           unicode*& decptr,
           size_t& declen,
           size_t& offset);


int
u32_decode(const std::vector<bytechar>& enc,
           std::vector<unicode>& dec,
           size_t& offset);


} // namespace quirinus
#endif // QUIRINUS_CORE_STRING_U32_DECODE_HPP
