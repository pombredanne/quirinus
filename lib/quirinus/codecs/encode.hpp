/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CODECS_ENCODE_HPP
#define QUIRINUS_CODECS_ENCODE_HPP
#include "Codec.hpp"
#include "UTF8Codec.hpp"
#include "UTF16Codec.hpp"
#include "UTF32Codec.hpp"
#include "LookupError.hpp"
#include "lookup.hpp"
namespace quirinus {
namespace codecs {


inline Bytes
encode(const Unicode& ustring,
       const Bytes& encoding)
{
  Codec* codec = lookup(encoding);
  Bytes bstring = codec->encode(ustring);
  delete codec;
  return bstring;
}


} // namespace codecs
} // namespace quirinus
#endif // QUIRINUS_CODECS_ENCODE_HPP
