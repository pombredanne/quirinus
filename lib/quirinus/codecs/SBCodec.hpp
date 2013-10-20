/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CODECS_SBCODEC_HPP
#define QUIRINUS_CODECS_SBCODEC_HPP
namespace quirinus {
namespace codecs {


class SBCodec: public Codec
{
private:
  unicode* self_table;
  char* self_encoding;
public:
  ~SBCodec()
  {
    delete[] self_encoding;
  }

  SBCodec(const char* encoding, const unicode* table)
  {
    self_table = table;
    self_encoding = nullstrdup(encoding);
  }


  // Virtual functions
  inline SBCodec*
  clone() const
  {
    return new SBCodec(self_encoding, self_table);
  }

  inline Bytes
  repr() const
  {
    std::ostringstream sstream;
    sstream << "codecs::" << self_encoding;
    return sstream.str().c_str();
  }


  // Codec functions
  inline Bytes
  encoding() const
  {
    return self_encoding;
  }

  inline Int
  offset() const
  {
    return self_offset;
  }

  inline Unicode
  decode(const Bytes& object) const
  {
    unicode code = 0;
    size_t offset = 0;
    unicode* decptr = NULL;
    size_t len = object.length();
    const bytechar* encptr = object;
    decptr = new unicode[len];
    for (size_t i = 0; i < len; ++i)
    {
      code = this->bytetouc(encptr[i]);
      if (code == 0x110000)
      {
        delete[] decptr;
        throw DecodeError(UNICODE_STATE_ILLEGAL, offset, *this);
      }
      decptr[i] = static_cast<unicode>(code);
      ++offset;
    }
    return Unicode(decptr, len);
  }

  inline Bytes
  encode(const Unicode& object) const
  {
    unicode code = 0;
    size_t offset = 0;
    bytechar* encptr = NULL;
    size_t len = object.length();
    const unicode* decptr = object;
    encptr = new bytechar[len];
    for (size_t i = 0; i < len; ++i)
    {
      code = this->uctobyte(decptr[i]);
      if (code == 0x110000)
      {
        delete[] decptr;
        throw EncodeError(UNICODE_STATE_ILLEGAL, offset, *this);
      }
      encptr[i] = static_cast<bytechar>(code);
      ++offset;
    }
    return Bytes(encptr, len);
  }
private:
  inline unicode
  bytetouc(const bytechar& code) const
  {
    size_t counter = 0;
    const unicode* table = self_table;
    while (counter < 256)
    {
      if (code == *table)
        return *++table;
      table += 2;
      ++counter;
    }
    return 0x110000;
  }

  inline unicode
  uctobyte(const unicode& code) const
  {
    size_t counter = 0;
    const unicode* table = self_table;
    while (counter < 256)
    {
      if (code == *++table)
        return *--table;
      table += 2;
      ++counter;
    }
    return 0x110000;
  }
};


} // namespace codecs
} // namespace quirinus
#endif // QUIRINUS_CODECS_SBCODEC_HPP
