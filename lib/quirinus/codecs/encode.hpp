/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CODECS_ENCODE_HPP
#define QUIRINUS_CODECS_ENCODE_HPP
#include "lookup.hpp"
namespace quirinus {
namespace codecs {


Bytes
encode(const Unicode& ustring,
       const Bytes& encoding);


} // namespace codecs
} // namespace quirinus
#endif // QUIRINUS_CODECS_ENCODE_HPP
