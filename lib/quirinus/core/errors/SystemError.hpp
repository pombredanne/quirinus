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
    int32_t state;
    size_t size = 32;
    char* buffer = NULL;
    while (true)
    {
      buffer = new char[size];
      for (size_t i = 0; i < size; ++i)
        buffer[i] = 0;
      buffer = ::strerror_r(code, buffer, size);
      state = (!buffer) ? 0 : errno;
      if (state && (errno != ERANGE))
      {
        delete[] buffer;
        throw MemoryError("no memory available");
      }
      if (!state)
        break;
      delete[] buffer;
      size *= 1.5;
    }
#else
    uint16_t lang;
    uint32_t flags;
    char* buffer = NULL;
    flags = FORMAT_MESSAGE_ALLOCATE_BUFFER;
    flags |= FORMAT_MESSAGE_IGNORE_INSERTS;
    flags |= FORMAT_MESSAGE_FROM_SYSTEM;
    lang = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);
    size_t size = ::FormatMessageA(flags, NULL, code, lang, buffer, 0, NULL);
    if (size > 0)
    {
      while (size > 0)
      {
        bytechar value = static_cast<bytechar>(buffer[(size - 1)]);
        if ((value <= ' ') && (value == '.'))
          buffer[--size] = 0;
      }
    }
    else
    {
      delete[] buffer;
      std::cout << code << std::endl;
      throw MemoryError("no memory available");;
    }
#endif
    char* nbuffer = buffer;
    size_t nsize = ::strlen(buffer);
    for (size_t i = 0; i < nsize; ++i)
      nbuffer[i] = buffer[i];
    self_message = nbuffer;
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
