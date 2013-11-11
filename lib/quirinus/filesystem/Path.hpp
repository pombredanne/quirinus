/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_FILESYSTEM_PATH_HPP
#define QUIRINUS_FILESYSTEM_PATH_HPP
namespace quirinus {
namespace filesystem {


class Path: public Object
{
public:
  static const Bytes SEP;
  static const Bytes ALTSEP;
  static const Bytes CURDIR;
  static const Bytes PARDIR;
  static const Bytes EXTSEP;
  static const Bytes PATHSEP;
  static const Bytes DEVNULL;
public:
  virtual Int mode() const = 0;
  virtual Int ino() const = 0;
  virtual Int dev() const = 0;
  virtual Int links() const = 0;
  virtual Int uid() const = 0;
  virtual Int gid() const = 0;
  virtual Int size() const = 0;
  virtual Int atime() const = 0;
  virtual Int ctime() const = 0;
  virtual Int mtime() const = 0;
public:
  virtual Bool is_block() const = 0;
  virtual Bool is_device() const = 0;
  virtual Bool is_dir() const = 0;
  virtual Bool is_fifo() const = 0;
  virtual Bool is_file() const = 0;
  virtual Bool is_link() const = 0;
  virtual Bool is_socket() const = 0;
public:
  static Bytes
  encoding()
  {
    struct quirinus::sysinfo sys;
    quirinus::sysinfo(&sys);
    return sys.encoding.filesystem;
  }
public:
  virtual ~Path()
  {}

  Path()
  {}
};


} // namespace filesystem
} // namespace quirinus
#endif // QUIRINUS_FILESYSTEM_PATH_HPP
