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
  virtual Int mode() const = 0;
  virtual Int ino() const = 0;
  virtual Int dev() const = 0;
  virtual Int rdev() const = 0;
  virtual Int nlink() const = 0;
  virtual Int uid() const = 0;
  virtual Int gid() const = 0;
  virtual Int size() const = 0;
  virtual Int atime() const = 0;
  virtual Int ctime() const = 0;
  virtual Int mtime() const = 0;
public:
  virtual Bool exists() const = 0;
  virtual Bool lexists() const = 0;
  virtual Bool isblock() const = 0;
  virtual Bool isdevice() const = 0;
  virtual Bool isdir() const = 0;
  virtual Bool isfifo() const = 0;
  virtual Bool isfile() const = 0;
  virtual Bool islink() const = 0;
  virtual Bool issocket() const = 0;
public:
  virtual ~Path()
  {}

  Path()
  {}
};


} // namespace filesystem
} // namespace quirinus
#endif // QUIRINUS_FILESYSTEM_PATH_HPP
