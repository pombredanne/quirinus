/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CODECS_LOOKUPERROR_HPP
#define QUIRINUS_CODECS_LOOKUPERROR_HPP
namespace quirinus {
namespace codecs {


class LookupError: public Error
{
private:
  char* self_encoding;
public:
  ~LookupError() throw()
  { delete[] self_encoding; }

  LookupError()
  : self_encoding(NULL)
  {}

  LookupError(const char* encoding)
  : self_encoding(NULL)
  {
    if (encoding)
      self_encoding = nullstrdup(encoding);
    else
      self_encoding = NULL;
  }


  // Message function
  inline const char*
  what() const throw()
  {
    std::ostringstream sstream;
    sstream << "LookupError";
    if (self_encoding)
      sstream << ": " << self_encoding;
    return sstream.str().c_str();
  }
};


} // namespace codecs
} // namespace quirinus
#endif // QUIRINUS_CODECS_LOOKUPERROR_HPP
