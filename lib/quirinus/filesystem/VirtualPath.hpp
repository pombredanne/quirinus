/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_FILESYSTEM_VIRTUALPATH_HPP
#define QUIRINUS_FILESYSTEM_VIRTUALPATH_HPP
namespace quirinus {
namespace filesystem {


class VirtualPath: public Path
{
private:
  uint32_t self_mode;  // Access mode and file type
  uint64_t self_dev;   // ID of device containing the file
  uint64_t self_ino;   // Serial number for the file
  uint32_t self_uid;   // User ID of file owner
  uint32_t self_gid;   // Group ID of file owner
  uint64_t self_links; // Number of links to the file
  uint64_t self_size;  // Size of the file in bytes
  uint64_t self_atime; // Last access time of the file
  uint64_t self_ctime; // Last change time of the file
  uint64_t self_mtime; // Last modify time of the file
public:
  ~VirtualPath()
  {}

  VirtualPath()
  {}


  // Access mode and file type
  inline void
  mode(const Int& mode)
  { self_mode = mode; }

  inline Int
  mode() const
  { return self_mode; }


  // ID of device containing the file
  inline void
  dev(const Int& dev)
  { self_dev = dev; }

  inline Int
  dev() const
  { return self_dev; }


  // Serial number for the file
  inline void
  ino(const Int& ino)
  { self_ino = ino; }

  inline Int
  ino() const
  { return self_ino; }


  // User ID of file owner
  inline void
  uid(const Int& uid)
  { self_uid = uid; }

  inline Int
  uid() const
  { return self_uid; }


  // Group ID of file owner
  inline void
  gid(const Int& gid)
  { self_gid = gid; }

  inline Int
  gid() const
  { return self_gid; }


  // Number of links to the file
  inline void
  links(const Int& links)
  { self_links = links; }

  inline Int
  nlink() const
  { return self_links; }


  // Size of the file in bytes
  inline void
  size(const Int& size)
  { self_size = size; }

  inline Int
  size() const
  { return self_size; }


  // Last access time of the file
  inline void
  atime(const Int& atime)
  { self_atime = atime; }

  inline Int
  atime() const
  { return self_atime; }


  // Last change time of the file
  inline void
  ctime(const Int& ctime)
  { self_ctime = ctime; }

  inline Int
  ctime() const
  { return self_ctime; }


  // Last modify time of the file
  inline void
  mtime(const Int& mtime)
  { self_mtime = mtime; }

  inline Int
  mtime() const
  { return self_mtime; }
};


} // namespace filesystem
} // namespace quirinus
#endif // QUIRINUS_FILESYSTEM_VIRTUALPATH_HPP
