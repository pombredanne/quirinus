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
  Int self_mode;  // Access mode and file type
  Int self_dev;   // ID of device containing the file
  Int self_ino;   // Serial number for the file
  Int self_uid;   // User ID of file owner
  Int self_gid;   // Group ID of file owner
  Int self_links; // Number of links to the file
  Int self_size;  // Size of the file in bytes
  Int self_atime; // Last access time of the file
  Int self_ctime; // Last change time of the file
  Int self_mtime; // Last modify time of the file
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

#if (QUIRINUS_FEATURE_CXX11)
  VirtualPath(VirtualPath&& object)
  { swap(*this, object); }
#endif

  VirtualPath(const Path& object)
  {
    const size_t fields = 10;
    Int** members = new Int*[fields];
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
  friend void
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
  VirtualPath&
  operator=(VirtualPath object)
  {
    swap(*this, object);
    return *this;
  }


  // Virtual functions
  VirtualPath*
  clone() const
  { return new VirtualPath(*this); }


  // Filesystem functions
  void
  mode(const Int& mode)
  { self_mode = mode; }

  Int
  mode() const
  { return self_mode; }


  void
  dev(const Int& dev)
  { self_dev = dev; }

  Int
  dev() const
  { return self_dev; }


  void
  ino(const Int& ino)
  { self_ino = ino; }

  Int
  ino() const
  { return self_ino; }


  void
  uid(const Int& uid)
  { self_uid = uid; }

  Int
  uid() const
  { return self_uid; }


  void
  gid(const Int& gid)
  { self_gid = gid; }

  Int
  gid() const
  { return self_gid; }


  void
  links(const Int& links)
  { self_links = links; }

  Int
  links() const
  { return self_links; }


  void
  size(const Int& size)
  { self_size = size; }

  Int
  size() const
  { return self_size; }


  void
  atime(const Int& atime)
  { self_atime = atime; }

  Int
  atime() const
  { return self_atime; }


  void
  ctime(const Int& ctime)
  { self_ctime = ctime; }

  Int
  ctime() const
  { return self_ctime; }


  void
  mtime(const Int& mtime)
  { self_mtime = mtime; }

  Int
  mtime() const
  { return self_mtime; }


  Bool
  is_block() const
  { return ((self_mode & Path::FMT) == Path::BLK); }


  Bool
  is_device() const
  { return ((self_mode & Path::FMT) == Path::CHR); }


  Bool
  is_dir() const
  { return ((self_mode & Path::FMT) == Path::DIR); }


  Bool
  is_fifo() const
  { return ((self_mode & Path::FMT) == Path::FIFO); }


  Bool
  is_file() const
  { return ((self_mode & Path::FMT) == Path::REG); }


  Bool
  is_link() const
  { return ((self_mode & Path::FMT) == Path::LNK); }


  Bool
  is_socket() const
  { return ((self_mode & Path::FMT) == Path::SOCK); }
};


} // namespace filesystem
} // namespace quirinus
#endif // QUIRINUS_FILESYSTEM_VIRTUALPATH_HPP
