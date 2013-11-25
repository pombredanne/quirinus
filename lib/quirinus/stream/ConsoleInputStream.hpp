/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_STREAM_CONSOLEINPUTSTREAM_HPP
#define QUIRINUS_STREAM_CONSOLEINPUTSTREAM_HPP
#include "Stream.hpp"
#include "IOError.hpp"
namespace quirinus {
namespace stream {


class ConsoleInputStream: public Stream
{
private:
  Int self_fd;
public:
  friend class IOStream;
public:
  ~ConsoleInputStream()
  {}

  ConsoleInputStream()
  : self_fd(STDIN_FILENO)
  {}


  // Virtual functions
  inline ConsoleInputStream*
  clone() const
  { return new ConsoleInputStream; }

  inline Bytes
  repr() const
  { return "stream::stdin"; }


  // Stream functions
  inline Bytes
  mode() const
  { return "rb"; }

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
  write(const Bytes&)
  { throw IOError("stdin stream is not writeable"); }

  Bytes
  read(const Int& size = 0) const
  {
    if (size < 0)
      throw ValueError("size must be a positive integer");
    std::vector<bytechar> stack;
    if (size == 0)
    {
      int character = 0;
      while (true)
      {
        character = ::getchar();
        if (character == EOF)
          break;
        stack.push_back(character);
      }
    }
    else
    {
      for (Int i = 0; i < size; ++i)
        stack.push_back(::getchar());
    }
    const bytechar* head = &*stack.begin();
    const bytechar* tail = &*stack.end();
    return Bytes(head, tail);
  }

  void
  flush()
  {}


  Stream& reference()
  { return *this; }
private:
  Stream& operator=(Stream& object);
};


} // namespace stream
} // namespace quirinus
#endif // QUIRINUS_STREAM_CONSOLEINPUTSTREAM_HPP
