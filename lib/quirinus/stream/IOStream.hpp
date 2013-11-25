/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_STREAM_IOSTREAM_HPP
#define QUIRINUS_STREAM_IOSTREAM_HPP
#include "Stream.hpp"
#include "ConsoleInputStream.hpp"
#include "ConsoleOutputStream.hpp"
#include "ConsoleErrorStream.hpp"
namespace quirinus {
namespace stream {


class IOStream: public Object
{
private:
  Stream* self;
public:
  ~IOStream()
  { delete self; }

  IOStream()
  : self(NULL)
  {}

  IOStream(const Stream& object)
  : self(object.clone())
  {}

  IOStream(const IOStream& object)
  : self(NULL)
  {
    if (object.self)
      self = object.self->clone();
  }


  // Virtual functions
  inline IOStream*
  clone() const
  { return new IOStream(*this); }

  inline Bytes
  repr() const
  {
    if (self)
      return self->repr();
    return "stream::IOStream";
  }


  // Swap function
  inline void
  swap(IOStream& lhs, IOStream& rhs)
  {
    using std::swap;
    swap(lhs.self, rhs.self);
  }


  // Assignment function
  inline IOStream&
  operator=(IOStream object)
  {
    swap(*this, object);
    return *this;
  }


  // IOStream functions
  inline Bytes
  mode() const
  {
    if (self)
      return self->mode();
    return "";
  }

  inline Bool
  isatty() const
  {
    if (self)
      return self->isatty();
    return false;
  }

  inline Int
  fd() const
  {
    if (self)
      return self->fd();
    return -1;
  }

  inline void
  fd(const Int& fd)
  {
    if (self)
      return self->fd(fd);
  }

  inline Bytes
  read(const Int& size = 0) const
  {
    if (self)
      return self->read(size);
    return "";
  }

  inline Int
  write(const Bytes& data = "")
  {
    if (self)
      return self->write(data);
    return 0;
  }

  inline void
  flush()
  {
    if (self)
      return self->flush();
  }
};


} // namespace stream
} // namespace quirinus
#endif // QUIRINUS_STREAM_IOSTREAM_HPP
