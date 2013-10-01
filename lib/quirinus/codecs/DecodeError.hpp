/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CODECS_DECODEERROR_HPP
#define QUIRINUS_CODECS_DECODEERROR_HPP
namespace quirinus {
namespace codecs {


class DecodeError: public Error
{
private:
  Int self_code;
  Int self_offset;
  Codec* self_codec;
  const char* self_message;
public:
  ~DecodeError() throw()
  {
    delete self_codec;
    delete[] self_message;
  }

  DecodeError()
  {}

  DecodeError(const char* message)
  {
    if (message)
      self_message = nullstrdup(message);
    else
      self_message = NULL;
  }

  DecodeError(const Int& code,
              const Int& offset,
              const Codec& codec)
  {
    self_code = code;
    self_offset = offset;
    self_codec = codec.clone();
    self_message = NULL;
  }


  // Message function
  inline const char*
  what() const throw()
  {
    std::ostringstream sstream;
    sstream << "codecs::DecodeError";
    if (self_message)
      sstream << ": " << self_message;
    else
    {
      sstream << ':' << ' ';
      Bytes encoding = self_codec->encoding();
      if (self_code == UNICODE_STATE_NULLPTR)
        sstream << "null string pointer";
      else if (self_code == UNICODE_STATE_ISOLATED)
        sstream << "isolated code point";
      else if (self_code == UNICODE_STATE_OVERLONG)
        sstream << "overlong code point";
      else if (self_code == UNICODE_STATE_TRUNCATED)
        sstream << "truncated code point";
      else if (self_code == UNICODE_STATE_ILLEGAL)
        sstream << "illegal code point";
      else if (self_code == UNICODE_STATE_HEADER)
        sstream << "incorrect most significant bits";
      else if (self_code == UNICODE_STATE_SURROGATE)
        sstream << "missing high or low surrogate";
      else
        sstream << "unknown encode error";
      sstream << '(' << "offset=" << self_offset << ')';
    }
    return sstream.str().c_str();
  }
};


} // namespace codecs
} // namespace quirinus
#endif // QUIRINUS_CODECS_DECODEERROR_HPP
