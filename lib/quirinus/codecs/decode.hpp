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
namespace quirinus {
namespace codecs {


inline Unicode
decode(const Bytes& bstring,
       const Bytes& encoding)
{
  Codec* codec = NULL;

  if ((encoding == "UTF-8")
  ||  (encoding == "UTF8")
  ||  (encoding == "CP65001"))
    codec = new UTF8Codec;

  if ((encoding == "UTF-16")
  ||  (encoding == "UTF16")
  ||  (encoding == "CP1200")
  ||  (encoding == "CP1201"))
    codec = new UTF16Codec;

  if ((encoding == "UTF-32")
  ||  (encoding == "UTF32")
  ||  (encoding == "CP12000")
  ||  (encoding == "CP12001"))
    codec = new UTF32Codec;

  Unicode ustring = codec->decode(bstring);
  delete codec;
  return ustring;
}


} // namespace codecs
} // namespace quirinus
#endif // QUIRINUS_CODECS_DECODE_HPP
