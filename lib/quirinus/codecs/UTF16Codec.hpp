/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CODECS_UTF16CODEC_HPP
#define QUIRINUS_CODECS_UTF16CODEC_HPP
#include "Codec.hpp"
namespace quirinus {
namespace codecs {


class UTF16Codec: public Codec
{
public:
  ~UTF16Codec()
  {}

  UTF16Codec()
  {}


  // Virtual functions
  inline UTF16Codec*
  clone() const
  { return new UTF16Codec; }

  inline Bytes
  repr() const
  { return "codecs::UTF-16"; }


  // Codec functions
  inline Bytes
  encoding() const
  { return "UTF-16"; }

  inline Unicode
  decode(const Bytes& object) const
  {
    int state;
    size_t offset = 0;
    size_t declen = 0;
    unicode* decptr = NULL;
    size_t enclen = object.length();
    const bytechar* encptr = static_cast<const bytechar*>(object);
    state = u16_decode(encptr, enclen, decptr, declen, offset);
    if (state != UNICODE_STATE_SUCCESS)
      throw DecodeError(state, offset, "UTF-16");
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
    state = u16_encode(decptr, declen, encptr, enclen, offset);
    if (state != UNICODE_STATE_SUCCESS)
      throw EncodeError(state, offset, "UTF-16");
    return Bytes(encptr, enclen);
  }
};


} // namespace codecs
} // namespace quirinus
#endif // QUIRINUS_CODECS_UTF16CODEC_HPP
