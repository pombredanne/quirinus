/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CODECS_CODEC_HPP
#define QUIRINUS_CODECS_CODEC_HPP
namespace quirinus {
namespace codecs {


class Codec;
class Codec_ASCII;
class Codec_UTF8;
class Codec_UTF16;
class Codec_UTF32;


class Codec: public Object
{
private:
  friend class Codec_ASCII;
  friend class Codec_UTF8;
  friend class Codec_UTF16;
  friend class Codec_UTF32;
protected:
  Int self_codepage;
  Bytes self_encoding;
  const unicode* self_table;
public:
  virtual ~Codec()
  {}

  Codec()
  : self_codepage(0)
  , self_encoding("")
  , self_table(NULL)
  {}

  Codec(const Bytes& encoding,
        const Int& codepage,
        const unicode* table)
  : self_codepage(0)
  , self_encoding("")
  , self_table(NULL)
  {
    if (!table)
      throw ValueError("null pointer access");
    self_codepage = codepage;
    self_encoding = encoding;
    self_table = table;
  }


  // Swap function
  inline void
  swap(Codec& lhs, Codec& rhs)
  {
    using std::swap;
    swap(lhs.self_encoding, rhs.self_encoding);
    swap(lhs.self_codepage, rhs.self_codepage);
    swap(lhs.self_table, rhs.self_table);
  }


  // Virtual functions
  inline Codec*
  clone() const
  { return new Codec; }

  inline Bytes
  repr() const
  {
    std::ostringstream sstream;
    sstream << "codecs::Codec";
    if (self_table)
      sstream << "\"(" << self_encoding << ")\"";
    return sstream.str().c_str();
  }


  // Codec functions
  virtual Int
  codepage() const
  { return self_codepage; }

  virtual Bytes
  encoding() const
  { return self_encoding; }

  virtual Unicode
  decode(const Bytes& object) const
  {
    const int state = UNICODE_STATE_ILLEGAL;
    const char* encoding = self_encoding;
    const unicode* table = self_table;
    const size_t length = object.length();
    const bytechar* encptr = object.head();
    unicode* decptr = new unicode[length];
    for (size_t offset = 0; offset < length; ++offset)
    {
      for (size_t i = 0; ; i += 2)
      {
        if (table[i] == 0x110000)
        {
          delete[] decptr;
          throw DecodeError(state, offset, encoding);
        }
        if (table[i] == encptr[offset])
        {
          uint32_t code = table[i + 1];
          decptr[offset] = code;
          break;
        }
      }
    }
    Unicode result(decptr, length);
    delete[] decptr;
    return result;
  }

  virtual Bytes
  encode(const Unicode& object) const
  {
    const int state = UNICODE_STATE_ILLEGAL;
    const char* encoding = self_encoding;
    const unicode* table = (self_table + 1);
    const size_t length = object.length();
    const unicode* decptr = object.head();
    bytechar* encptr = new bytechar[length];
    for (size_t offset = 0; offset < length; ++offset)
    {
      for (size_t i = 0; ; i += 2)
      {
        if (table[i] == 0x110000)
        {
          delete[] encptr;
          throw EncodeError(state, offset, encoding);
        }
        if (table[i] == decptr[offset])
        {
          uint8_t code = table[i - 1];
          encptr[offset] = code;
          break;
        }
      }
    }
    Bytes result(encptr, length);
    delete[] encptr;
    return result;
  }
};


} // namespace codecs
} // namespace quirinus
#endif // QUIRINUS_CODECS_CODEC_HPP
