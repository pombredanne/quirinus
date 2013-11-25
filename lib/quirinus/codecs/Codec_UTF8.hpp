/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CODECS_CODEC_UTF8_HPP
#define QUIRINUS_CODECS_CODEC_UTF8_HPP
#include "Codec.hpp"
namespace quirinus {
namespace codecs {


class Codec_UTF8: public Codec
{
public:
  ~Codec_UTF8()
  {}

  Codec_UTF8()
  {}


  // Virtual functions
  inline Codec_UTF8*
  clone() const
  { return new Codec_UTF8; }

  inline Bytes
  repr() const
  { return "codecs::Codec(\"UTF-8\")"; }


  // Codec functions
  inline Int
  codepage() const
  { return 65001; }

  inline Bytes
  encoding() const
  { return "UTF-8"; }

  inline Unicode
  decode(const Bytes& object) const
  {
    int state;
    size_t offset = 0;
    size_t declen = 0;
    unicode* decptr = NULL;
    size_t enclen = object.length();
    const bytechar* encptr = static_cast<const bytechar*>(object);
    state = u8_decode(encptr, enclen, decptr, declen, offset);
    if (state != UNICODE_STATE_SUCCESS)
      throw DecodeError(state, offset, "UTF-8");
    return Unicode(decptr, declen);
  }

  inline Bytes
  encode(const Unicode& object) const
  {
    int state;
    size_t offset = 0;
    size_t enclen = 0;
    bytechar* encptr = NULL;
    size_t declen = object.length();
    const unicode* decptr = static_cast<const unicode*>(object);
    state = u8_encode(decptr, declen, encptr, enclen, offset);
    if (state != UNICODE_STATE_SUCCESS)
      throw EncodeError(state, offset, "UTF-8");
    return Bytes(encptr, enclen);
  }
};


} // namespace codecs
} // namespace quirinus
#endif // QUIRINUS_CODECS_CODEC_UTF8_HPP
