/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CODECS_DECODE_HPP
#define QUIRINUS_CODECS_DECODE_HPP
#include "Codec.hpp"
#include "UTF8Codec.hpp"
#include "UTF16Codec.hpp"
#include "UTF32Codec.hpp"
#include "lookup.hpp"
namespace quirinus {
namespace codecs {


inline Unicode
decode(const Bytes& bstring,
       const Bytes& encoding)
{
  Codec* codec = lookup(encoding);
  Unicode ustring = codec->decode(bstring);
  delete codec;
  return ustring;
}


} // namespace codecs
} // namespace quirinus
#endif // QUIRINUS_CODECS_DECODE_HPP
