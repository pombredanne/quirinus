/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CODECS_CODEC_ASCII_HPP
#define QUIRINUS_CODECS_CODEC_ASCII_HPP
namespace quirinus {
namespace codecs {


class Codec_ASCII: public Codec
{
public:
  ~Codec_ASCII()
  {}

  Codec_ASCII()
  {}


  // Virtual functions
  inline Codec_ASCII*
  clone() const
  { return new Codec_ASCII; }

  inline Bytes
  repr() const
  { return "Codec(\"US-ASCII\")"; }


  // Codec functions
  inline Int
  codepage() const
  { return 20127; }

  inline Bytes
  encoding() const
  { return "US-ASCII"; }

  Unicode
  decode(const Bytes& object) const
  {
    const int state = UNICODE_STATE_ILLEGAL;
    const size_t length = object.length();
    const bytechar* encptr = object.head();
    unicode* decptr = new unicode[length];
    for (size_t offset = 0; offset < length; ++offset)
    {
      if (encptr[offset] >= 0x80)
      {
        delete[] decptr;
        throw DecodeError(state, offset, "US-ASCII");
      }
      uint32_t code = encptr[offset];
      decptr[offset] = code;
    }
    Unicode result(decptr, length);
    delete[] decptr;
    return result;
  }

  Bytes
  encode(const Unicode& object) const
  {
    const int state = UNICODE_STATE_ILLEGAL;
    const size_t length = object.length();
    const unicode* decptr = object.head();
    bytechar* encptr = new bytechar[length];
    for (size_t offset = 0; offset < length; ++offset)
    {
      if (decptr[offset] >= 0x80)
      {
        delete[] encptr;
        throw DecodeError(state, offset, "US-ASCII");
      }
      uint8_t code = decptr[offset];
      encptr[offset] = code;
    }
    Bytes result(encptr, length);
    delete[] encptr;
    return result;
  }
};


} // namespace codecs
} // namespace quirinus
#endif // QUIRINUS_CODECS_CODEC_ASCII_HPP
