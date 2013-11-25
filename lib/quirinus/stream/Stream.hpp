/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_STREAM_STREAM_HPP
#define QUIRINUS_STREAM_STREAM_HPP
namespace quirinus {
namespace stream {


class Stream;
class IOStream;
class ConsoleInputStream;
class ConsoleOutputStream;
class ConsoleErrorStream;


class Stream: public Object
{
public:
  friend class IOStream;
public:
  virtual Stream* clone() const = 0;
  virtual Bytes mode() const = 0;
  virtual Bool isatty() const = 0;
  virtual Int fd() const = 0;
  virtual void fd(const Int&) = 0;
  virtual Bytes read(const Int&) const = 0;
  virtual Int write(const Bytes&) = 0;
  virtual void flush() = 0;
public:
  virtual ~Stream()
  {}

  Stream()
  {}
};


} // namespace stream
} // namespace quirinus
#endif // QUIRINUS_STREAM_STREAM_HPP
