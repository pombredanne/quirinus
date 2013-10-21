/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_FILESYSTEM_VIRTUALPATH_HPP
#define QUIRINUS_FILESYSTEM_VIRTUALPATH_HPP
#include "Path.hpp"
namespace quirinus {
namespace filesystem {


class VirtualPath: public Path
{
private:
  uint64_t self_mode;  // Access mode and file type
  uint64_t self_dev;   // ID of device containing the file
  uint64_t self_ino;   // Serial number for the file
  uint64_t self_uid;   // User ID of file owner
  uint64_t self_gid;   // Group ID of file owner
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

  VirtualPath(const VirtualPath& object)
  {
    self_mode = object.self_mode;
    self_dev = object.self_dev;
    self_ino = object.self_ino;
    self_uid = object.self_uid;
    self_gid = object.self_gid;
    self_links = object.self_links;
    self_size = object.self_size;
    self_atime = object.self_atime;
    self_ctime = object.self_ctime;
    self_mtime = object.self_mtime;
  }

  VirtualPath(const Path& object)
  {
    const size_t fields = 10;
    uint64_t** members = new uint64_t*[fields];
    typedef Int (Path::*MemberFunction)() const;
    MemberFunction* functions = new MemberFunction[fields];
    members[0] = &self_mode;    functions[0] = &Path::mode;
    members[1] = &self_dev;     functions[1] = &Path::dev;
    members[2] = &self_ino;     functions[2] = &Path::ino;
    members[3] = &self_uid;     functions[3] = &Path::uid;
    members[4] = &self_gid;     functions[4] = &Path::gid;
    members[5] = &self_links;   functions[5] = &Path::links;
    members[6] = &self_size;    functions[6] = &Path::size;
    members[7] = &self_atime;   functions[7] = &Path::atime;
    members[8] = &self_ctime;   functions[8] = &Path::ctime;
    members[9] = &self_mtime;   functions[9] = &Path::mtime;
    for (size_t i = 0; i < fields; ++i)
      *members[i] = (object.*functions[i])();
    delete[] members;
    delete[] functions;
  }


  // Swap function
  friend inline void
  swap(VirtualPath& lhs, VirtualPath& rhs)
  {
    using std::swap;
    swap(lhs.self_mode, rhs.self_mode);
    swap(lhs.self_dev, rhs.self_dev);
    swap(lhs.self_ino, rhs.self_ino);
    swap(lhs.self_uid, rhs.self_uid);
    swap(lhs.self_gid, rhs.self_gid);
    swap(lhs.self_links, rhs.self_links);
    swap(lhs.self_size, rhs.self_size);
    swap(lhs.self_atime, rhs.self_atime);
    swap(lhs.self_ctime, rhs.self_ctime);
    swap(lhs.self_mtime, rhs.self_mtime);
  }


  // Assignment function
  inline VirtualPath&
  operator=(VirtualPath object)
  {
    swap(*this, object);
    return *this;
  }


  // Virtual functions
  inline VirtualPath*
  clone() const
  { return new VirtualPath(*this); }


  // Filesystem functions
  inline void
  mode(const Int& mode)
  { self_mode = mode; }

  inline Int
  mode() const
  { return self_mode; }


  inline void
  dev(const Int& dev)
  { self_dev = dev; }

  inline Int
  dev() const
  { return self_dev; }


  inline void
  ino(const Int& ino)
  { self_ino = ino; }

  inline Int
  ino() const
  { return self_ino; }


  inline void
  uid(const Int& uid)
  { self_uid = uid; }

  inline Int
  uid() const
  { return self_uid; }


  inline void
  gid(const Int& gid)
  { self_gid = gid; }

  inline Int
  gid() const
  { return self_gid; }


  inline void
  links(const Int& links)
  { self_links = links; }

  inline Int
  links() const
  { return self_links; }


  inline void
  size(const Int& size)
  { self_size = size; }

  inline Int
  size() const
  { return self_size; }


  inline void
  atime(const Int& atime)
  { self_atime = atime; }

  inline Int
  atime() const
  { return self_atime; }


  inline void
  ctime(const Int& ctime)
  { self_ctime = ctime; }

  inline Int
  ctime() const
  { return self_ctime; }


  inline void
  mtime(const Int& mtime)
  { self_mtime = mtime; }

  inline Int
  mtime() const
  { return self_mtime; }


  inline Bool
  isblock() const
  { return ((self_mode & S_IFMT) == S_IFBLK); }


  inline Bool
  isdevice() const
  { return ((self_mode & S_IFMT) == S_IFCHR); }


  inline Bool
  isdir() const
  { return ((self_mode & S_IFMT) == S_IFDIR); }


  inline Bool
  isfifo() const
  { return ((self_mode & S_IFMT) == S_IFIFO); }


  inline Bool
  isfile() const
  { return ((self_mode & S_IFMT) == S_IFREG); }


  inline Bool
  islink() const
  { return ((self_mode & S_IFMT) == S_IFLNK); }


  inline Bool
  issocket() const
  { return ((self_mode & S_IFMT) == S_IFSOCK); }
};


} // namespace filesystem
} // namespace quirinus
#endif // QUIRINUS_FILESYSTEM_VIRTUALPATH_HPP
