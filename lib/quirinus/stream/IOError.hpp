/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_STREAM_IOERROR_HPP
#define QUIRINUS_STREAM_IOERROR_HPP
namespace quirinus {
namespace stream {


class IOError: public Error
{
private:
  char* self_message;
public:
  ~IOError() throw()
  { delete[] self_message; }

  IOError()
  : self_message(NULL)
  {}

  IOError(const char* message)
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
    sstream << "IOError";
    if (self_message)
      sstream << ": " << self_message;
    return sstream.str().c_str();
  }
};


} // namespace stream
} // namespace quirinus
#endif // QUIRINUS_STREAM_IOERROR_HPP
