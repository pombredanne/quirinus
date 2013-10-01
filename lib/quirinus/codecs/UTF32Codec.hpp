/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CODECS_UTF32CODEC_HPP
#define QUIRINUS_CODECS_UTF32CODEC_HPP
#include "Codec.hpp"
#include "DecodeError.hpp"
#include "EncodeError.hpp"
namespace quirinus {
namespace codecs {


class UTF32Codec: public Codec
{
public:
  ~UTF32Codec()
  {}

  UTF32Codec()
  {}


  // Virtual functions
  inline UTF32Codec*
  clone() const
  {
    return new UTF32Codec;
  }


  // Codec functions
  Bytes encoding() const
  {
    return "UTF-32";
  }

  Unicode decode(const Bytes& object) const
  {
    int state;
    size_t offset = 0;
    size_t declen = 0;
    unicode* decptr = NULL;
    size_t enclen = object.length();
    const bytechar* encptr = object;
    state = u32_decode(encptr, enclen, decptr, declen, offset);
    if (state != UNICODE_STATE_SUCCESS)
      throw DecodeError(state, offset, *this);
    return Unicode(decptr, declen);
  }

  Bytes encode(const Bytes& object) const
  {
    int state;
    size_t offset = 0;
    size_t enclen = 0;
    bytechar* encptr = NULL;
    size_t declen = object.length();
    const unicode* decptr = object;
    state = u32_encode(decptr, declen, encptr, enclen, offset);
    if (state != UNICODE_STATE_SUCCESS)
      throw DecodeError(state, offset, *this);
    return Bytes(encptr, enclen);
  }
};


} // namespace codecs
} // namespace quirinus
#endif // QUIRINUS_CODECS_UTF32CODEC_HPP
