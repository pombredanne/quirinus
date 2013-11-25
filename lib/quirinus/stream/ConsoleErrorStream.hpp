/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_STREAM_CONSOLEERRORSTREAM_HPP
#define QUIRINUS_STREAM_CONSOLEERRORSTREAM_HPP
#include "Stream.hpp"
#include "IOError.hpp"
namespace quirinus {
namespace stream {


class ConsoleErrorStream: public Stream
{
private:
  int self_fd;
public:
  friend class IOStream;
public:
  ~ConsoleErrorStream()
  {}

  ConsoleErrorStream()
  : self_fd(STDERR_FILENO)
  {}


  // Virtual functions
  inline ConsoleErrorStream*
  clone() const
  { return new ConsoleErrorStream; }

  inline Bytes
  repr() const
  { return "stream::stderr"; }


  // Stream functions
  inline Bytes
  mode() const
  { return "wb"; }

  inline Bool
  isatty() const
  { return true; }

  inline Int
  fd() const
  { return self_fd; }

  inline void
  fd(const Int& fd)
  { self_fd = fd; }

  Int
  write(const Bytes& data = "")
  {
    const size_t size = data.length();
    const bytechar* buffer = &*data.head();
    ::write(self_fd, buffer, size);
    return size;
  }

  Bytes
  read(const Int&) const
  { throw IOError("stderr stream is not readable"); }

  void
  flush()
  {}
private:
  Stream& operator=(Stream& object);
};


} // namespace stream
} // namespace quirinus
#endif // QUIRINUS_STREAM_CONSOLEERRORSTREAM_HPP
