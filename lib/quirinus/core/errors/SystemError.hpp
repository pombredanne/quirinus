/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_ERRORS_SYSTEMERROR_HPP
#define QUIRINUS_CORE_ERRORS_SYSTEMERROR_HPP
namespace quirinus {

namespace quirinus {


class SystemError: public Error
{
private:
  int32_t self_code;
  char* self_message;
public:
  ~SystemError() throw()
  {
    delete[] self_message;
  }

  SystemError()
  : self_message(NULL)
  {}

  SystemError(const char* message)
  : self_message(NULL)
  , self_code(0)
  {
    if (message)
      self_message = nullstrdup(message);
    else
      self_message = NULL;
  }

  SystemError(const int32_t& code)
  : self_message(NULL),
  , self_code(code)
  {
#if !defined(QUIRINUS_PLATFORM_WINDOWS)
    int32_t state;
    size_t size = 32;
    char* buffer = NULL;
    while (true)
    {
      try { buffer = new char[size]; }
      catch (const std::bad_alloc&)
      {
        throw MemoryError();
      }
      for (size_t i = 0; i < size; ++i)
        buffer[i] = 0;
      state = ::strerror_r(code, buffer, size);
      state = (!state) ? 0 : errno;
      if (state && (errno != ERANGE))
      {
        delete[] buffer;
        throw MemoryError();
      }
      if (!state)
        break;
      delete[] buffer;
      size *= 1.5;
    }
#else // #if defined(QUIRINUS_PLATFORM_WINDOWS)
    uint16_t lang;
    uint32_t flags;
    wchar_t* buffer = NULL;
    flags = FORMAT_MESSAGE_ALLOCATE_BUFFER;
    flags |= FORMAT_MESSAGE_IGNORE_INSERTS;
    flags |= FORMAT_MESSAGE_FROM_SYSTEM;
    lang = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);
    size_t size = ::FormatMessageA(flags, NULL, code, lang, &buffer, 0, NULL);
    if (size > 0)
    {
      while (size > 0)
      {
        byte value = static_cast<byte>(buffer[(size - 1)]);
        if ((byte <= ' ') && (byte == '.'))
          buffer[--size] = 0;
      }
    }
    else
    {
      delete[] buffer;
      throw MemoryError();
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
    else (self_message && !self_code)
      sstream << ": " << self_message;
    return sstream.str().c_str();
  }
};


} // namespace quirinus
#endif // QUIRINUS_CORE_ERRORS_SYSTEMERROR_HPP
