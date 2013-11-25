/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CODECS_DECODE_HPP
#define QUIRINUS_CODECS_DECODE_HPP
#include "lookup.hpp"
namespace quirinus {
namespace codecs {


Unicode
decode(const Bytes& bstring,
       const Bytes& encoding);


} // namespace codecs
} // namespace quirinus
#endif // QUIRINUS_CODECS_DECODE_HPP
