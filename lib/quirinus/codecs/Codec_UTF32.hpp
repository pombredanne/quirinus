/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CODECS_CODEC_UTF32_HPP
#define QUIRINUS_CODECS_CODEC_UTF32_HPP
#include "Codec.hpp"
namespace quirinus {
namespace codecs {


class Codec_UTF32: public Codec
{
public:
  ~Codec_UTF32()
  {}

  Codec_UTF32()
  {}


  // Virtual functions
  inline Codec_UTF32*
  clone() const
  { return new Codec_UTF32; }

  inline Bytes
  repr() const
  { return "codecs::Codec(\"UTF-16\")"; }


  // Codec functions
  inline Int
  codepage() const
  {
    struct sysinfo sys;
    sysinfo(&sys);
    if (sys.byteorder == -1)
      return 12000;
    return 12001;
  }

  inline Bytes
  encoding() const
  { return "UTF-32"; }

  Unicode
  decode(const Bytes& object) const
  {
    int state;
    size_t offset = 0;
    size_t declen = 0;
    unicode* decptr = NULL;
    size_t enclen = object.length();
    const bytechar* encptr = static_cast<const bytechar*>(object);
    state = u32_decode(encptr, enclen, decptr, declen, offset);
    if (state != UNICODE_STATE_SUCCESS)
      throw DecodeError(state, offset, "UTF-32");
    return Unicode(decptr, declen);
  }

  Bytes
  encode(const Unicode& object) const
  {
    int state;
    size_t offset = 0;
    size_t enclen = 0;
    bytechar* encptr = NULL;
    size_t declen = object.length();
    const unicode* decptr = static_cast<const unicode*>(object);
    state = u32_encode(decptr, declen, encptr, enclen, offset);
    if (state != UNICODE_STATE_SUCCESS)
      throw EncodeError(state, offset, "UTF-32");
    return Bytes(encptr, enclen);
  }
};


} // namespace codecs
} // namespace quirinus
#endif // QUIRINUS_CODECS_CODEC_UTF32_HPP
