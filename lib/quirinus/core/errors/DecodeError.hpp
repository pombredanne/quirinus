/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CODECS_DECODEERROR_HPP
#define QUIRINUS_CODECS_DECODEERROR_HPP
namespace quirinus {


class DecodeError: public Error
{
private:
  int self_state;
  size_t self_offset;
  char* self_encoding;
  char* self_message;
public:
  ~DecodeError() throw()
  {
    delete[] self_encoding;
    delete[] self_message;
  }

  DecodeError()
  : self_state(0)
  , self_offset(0)
  , self_encoding(NULL)
  , self_message(NULL)
  {}

  DecodeError(const char* message)
  : self_state(0)
  , self_offset(0)
  , self_encoding(NULL)
  , self_message(NULL)
  { self_message = nullstrdup(message); }

  DecodeError(const int& state,
              const size_t& offset,
              const char* encoding)
  : self_state(0)
  , self_offset(0)
  , self_encoding(NULL)
  , self_message(NULL)
  {
    self_state = state;
    self_offset = offset;
    self_encoding = nullstrdup(encoding);
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
      sstream << self_encoding << ':' << ' ';
      if (self_state == UNICODE_STATE_NULLPTR)
        sstream << "null string pointer";
      else if (self_state == UNICODE_STATE_ISOLATED)
        sstream << "isolated code point";
      else if (self_state == UNICODE_STATE_OVERLONG)
        sstream << "overlong code point";
      else if (self_state == UNICODE_STATE_TRUNCATED)
        sstream << "truncated code point";
      else if (self_state == UNICODE_STATE_ILLEGAL)
        sstream << "illegal code point";
      else if (self_state == UNICODE_STATE_HEADER)
        sstream << "incorrect most significant bits";
      else if (self_state == UNICODE_STATE_SURROGATE)
        sstream << "missing high or low surrogate";
      else
        sstream << "unknown encode error";
      sstream << ' ' << '(' << "offset=" << self_offset << ')';
    }
    return sstream.str().c_str();
  }
};


} // namespace quirinus
#endif // QUIRINUS_CODECS_DECODEERROR_HPP
