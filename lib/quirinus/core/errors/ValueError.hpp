/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_ERRORS_VALUEERROR_HPP
#define QUIRINUS_CORE_ERRORS_VALUEERROR_HPP
namespace quirinus {


class ValueError: public Error
{
private:
  char* self_str;
public:
  ~ValueError() throw()
  {
    delete[] self_str;
  }

  ValueError()
  : self_str(NULL)
  {}

  ValueError(const char* message)
  : self_str(NULL)
  {
    if (message)
    {
      size_t length = ::strlen(message);
      self_str = new char[(length + 1)];
      for (size_t i = 0; i < length; ++i)
        self_str[i] = message[i];
      self_str[length] = 0;
    }
    else
      self_str = NULL;
  }


  // Message function
  inline const char*
  what() const throw()
  {
    std::ostringstream sstream;
    sstream << "ValueError";
    if (self_str)
      sstream << ": " << self_str;
    return sstream.str().c_str();
  }
};


} // namespace quirinus
#endif // QUIRINUS_CORE_ERRORS_VALUEERROR_HPP
