/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_ERRORS_SYSTEMERROR_HPP
#define QUIRINUS_CORE_ERRORS_SYSTEMERROR_HPP
namespace quirinus {


class SystemError: public Error
{
private:
  int32_t self_code;
  char* self_message;
public:
  ~SystemError() throw()
  { delete[] self_message; }

  SystemError()
  : self_code(0)
  , self_message(NULL)
  {}

  SystemError(const char* message)
  : self_code(0)
  , self_message(NULL)
  {
    if (message)
      self_message = nullstrdup(message);
    else
      self_message = NULL;
  }

  SystemError(const int64_t& code,
              const bool& POSIX = true)
  : self_code(code)
  , self_message(NULL)
  {
#if (QUIRINUS_FEATURE_POSIX)
    char* buffer = strerror(code);
#else
    DWORD lang = 0;
    DWORD flags = 0;
    DWORD state = 0;
    size_t size = 64;
    char* buffer = NULL;
    flags = FORMAT_MESSAGE_FROM_SYSTEM;
    flags |= FORMAT_MESSAGE_IGNORE_INSERTS;
    lang = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);
    while (true)
    {
      buffer = new char[size];
      ::memset(buffer, 0, size);
      state = ::FormatMessageA(flags, NULL, code, lang, buffer, size, NULL);
      if (state)
        break;
      delete[] buffer;
      size *= 1.5;
    }
#endif
    self_message = nullstrdup(buffer);
  }


  // Message function
  inline const char*
  what() const throw()
  {
    std::ostringstream sstream;
    sstream << "SystemError";
    if (self_message && self_code)
      sstream << '[' << self_code << ']' << ": " << self_message;
    else if (self_message && !self_code)
      sstream << ": " << self_message;
    return sstream.str().c_str();
  }
};


} // namespace quirinus
#endif // QUIRINUS_CORE_ERRORS_SYSTEMERROR_HPP
