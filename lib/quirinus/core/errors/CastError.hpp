/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_ERRORS_CASTERROR_HPP
#define QUIRINUS_CORE_ERRORS_CASTERROR_HPP
namespace quirinus {


class CastError: public Error
{
private:
  char* self_message;
public:
  ~CastError() throw()
  { delete[] self_message; }

  CastError()
  : self_message(NULL)
  {}

  CastError(const char* message)
  : self_message(NULL)
  {
    if (message)
      self_message = nullstrdup(message);
    else
      self_message = NULL;
  }


  // Message function
  inline const char*
  what() const throw()
  {
    std::ostringstream sstream;
    sstream << "CastError";
    if (self_message)
      sstream << ": " << self_message;
    return sstream.str().c_str();
  }
};


} // namespace quirinus
#endif // QUIRINUS_CORE_ERRORS_CASTERROR_HPP
