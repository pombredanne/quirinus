/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_FILESYSTEM_WALKER_HPP
#define QUIRINUS_FILESYSTEM_WALKER_HPP
#include "FilePath.hpp"
#include "cwd.hpp"
namespace quirinus {
namespace filesystem {


class Walker: public Object
{
private:
  FilePath self_root;
  std::vector<FilePath> self_dirs;
  std::vector<FilePath> self_files;
public:
  typedef std::vector<FilePath>::iterator iterator;
  typedef std::vector<FilePath>::const_iterator const_iterator;
  typedef std::vector<FilePath>::reverse_iterator reverse_iterator;
  typedef std::vector<FilePath>::const_reverse_iterator const_reverse_iterator;
public:
  ~Walker()
  {}

  Walker(const FilePath& path)
  : self_root(path)
  {
    FilePath root(path);
    if (root == Path::CURDIR)
      root = filesystem::cwd();
    else if (root == Path::PARDIR)
    {
      Bytes stack = filesystem::cwd();
      const bytechar* head = stack.head();
      const bytechar* tail = (stack.tail() - 1);
#if (QUIRINUS_FEATURE_POSIX)
      for (; ((tail >= head) && (*tail != '/')); --tail);
#else
      for (; ((tail >= head) && (*tail != '\\')); --tail);
#endif
      root = Bytes(head, tail);
    }
#if (QUIRINUS_FEATURE_POSIX)
    int fd = 0;
    int state = 0;
    long namelen = 0;
    size_t bufsize = 0;
    DIR* handle = NULL;
    struct dirent64* xbuffer = NULL;
    struct dirent64* buffer = new dirent64;
    handle = ::opendir(root);
    if (!handle)
      throw SystemError(errno);
    fd = ::dirfd(handle);
    namelen = ::fpathconf(fd, _PC_NAME_MAX);
    namelen = ((namelen == -1) ? QUIRINUS_FILESYSTEM_NAME_MAX : namelen);
    bufsize = (offsetof(struct dirent64, d_name) + namelen + 1);
    xbuffer = reinterpret_cast<dirent64*>(::malloc(bufsize));
    while (true)
    {
      state = ::readdir64_r(handle, xbuffer, &buffer);
      if (state && buffer)
        throw SystemError(errno);
      if (!buffer)
        break;
      if ((strcmp(buffer->d_name, ".") == 0)
      ||  (strcmp(buffer->d_name, "..") == 0))
        continue;
  #if defined(_DIRENT_HAVE_D_TYPE)
      if (buffer->d_type & DT_UNKNOWN)
      {
  #endif
        FilePath path(buffer->d_name);
        if (path.is_dir())
          self_dirs.push_back(path);
        else
          self_files.push_back(path);
  #if defined(_DIRENT_HAVE_D_TYPE)
      }
      else if (buffer->d_type & DT_DIR)
        self_dirs.push_back(buffer->d_name);
      else
        self_files.push_back(buffer->d_name);
  #endif
    }
    ::closedir(handle);
#else
    DWORD state = 0;
    HANDLE handle = NULL;
    DWORD attributes = 0;
    FilePath dir(root / "*");
    WIN32_FIND_DATAW buffer;
    handle = ::FindFirstFileW(dir, &buffer);
    if (handle == INVALID_HANDLE_VALUE)
    {
      state = ::GetLastError();
      throw SystemError(state);
    }
    while (true)
    {
      state = ::FindNextFileW(handle, &buffer);
      if (!state)
        break;
      Unicode stack(buffer.cFileName);
      if ((stack == Path::CURDIR) \
      ||  (stack == Path::PARDIR))
        continue;
      attributes = buffer.dwFileAttributes;
      if (attributes & FILE_ATTRIBUTE_DIRECTORY)
        self_dirs.push_back(stack);
      else
        self_files.push_back(stack);
    }
    state = ((!state) ? ::GetLastError() : 0);
    if (state && (state != ERROR_NO_MORE_FILES))
    {
      ::FindClose(handle);
      throw SystemError(state);
    }
    ::FindClose(handle);
#endif
  }


  // Iterator functions
  iterator
  dirs_begin()
  { return self_dirs.begin(); }

  const_iterator
  dirs_begin() const
  { return self_dirs.begin(); }

  iterator
  dirs_end()
  { return self_dirs.end(); }

  const_iterator
  dirs_end() const
  { return self_dirs.end(); }


  reverse_iterator
  dirs_rbegin()
  { return self_dirs.rend(); }

  const_reverse_iterator
  dirs_rbegin() const
  { return self_dirs.rend(); }

  reverse_iterator
  dirs_rend()
  { return self_dirs.rend(); }

  const_reverse_iterator
  dirs_rend() const
  { return self_dirs.rend(); }


  iterator
  files_begin()
  { return self_files.begin(); }

  const_iterator
  files_begin() const
  { return self_files.begin(); }

  iterator
  files_end()
  { return self_files.end(); }

  const_iterator
  files_end() const
  { return self_files.end(); }


  reverse_iterator
  files_rbegin()
  { return self_files.rend(); }

  const_reverse_iterator
  files_rbegin() const
  { return self_files.rend(); }

  reverse_iterator
  files_rend()
  { return self_files.rend(); }

  const_reverse_iterator
  files_rend() const
  { return self_files.rend(); }


  // Walker functions
  FilePath
  root() const
  { return self_root; }
};


} // namespace filesystem
} // namespace quirinus
#endif // QUIRINUS_FILESYSTEM_WALKER_HPP
