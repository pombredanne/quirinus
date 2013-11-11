/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_FILESYSTEM_FILEPATH_HPP
#define QUIRINUS_FILESYSTEM_FILEPATH_HPP
#include "VirtualPath.hpp"
namespace quirinus {
namespace filesystem {


namespace {


byte*
mkpath(const byte* pointer,
       const size_t& size)
{
  byte* buffer = NULL;
  const byte* iter = pointer;
#if (QUIRINUS_FEATURE_POSIX)
  if (size == 1)
#else
  if (size == 2)
#endif
  {
#if (QUIRINUS_FEATURE_POSIX)
    const size_t size = 1;
    const size_t append = 1;
#else
    const size_t size = 2;
    const size_t append = 2;
#endif
    buffer = new byte[size + append];
    ::memcpy(buffer, iter, size);
    ::memset((buffer + size), 0, append);
    return buffer;
  }

  bool state;
  size_t nsize = 0;
#if (QUIRINUS_FEATURE_POSIX)
  const size_t append = 1;
  const bytechar sep = '/';
#else
  const size_t append = 2;
  const bytechar sep = '\\';
#endif
  const byte* tail = (pointer + size);

  // Calculate buffer size.
  state = false;
  for (iter = pointer; iter < tail; ++iter)
  {
    if ((*iter == '/') || (*iter == '\\'))
    {
      if (!state)
      {
        state = true;
        ++nsize;
      }
      continue;
    }
    else
    {
      state = false;
      ++nsize;
    }
  }

  // Fill buffer with characters.
  state = false;
  size_t index = 0;
  buffer = new byte[nsize + append];
  for (iter = pointer; iter < tail; ++iter)
  {
    if ((*iter == '/') || (*iter == '\\'))
    {
      if (!state)
        buffer[index++] = sep;
      state = true;
    }
    else
    {
      buffer[index++] = *iter;
      state = false;
    }
  }
  ::memset((buffer + nsize), 0, append);
  return buffer;
}


} // namespace


class FilePath: public Path
{
private:
  size_t self_size;
  void* self_path;
public:
  Int mode() const;
  Int dev() const;
  Int ino() const;
  Int uid() const;
  Int gid() const;
  Int links() const;
  Int size() const;
  Int atime() const;
  Int ctime() const;
  Int mtime() const;
public:
  Bool exists() const;
  Bool lexists() const;
  Bool is_block() const;
  Bool is_device() const;
  Bool is_dir() const;
  Bool is_fifo() const;
  Bool is_file() const;
  Bool is_link() const;
  Bool is_socket() const;
public:
  ~FilePath()
  { delete[] static_cast<byte*>(self_path); }

  FilePath()
  : self_path(NULL)
  {
    Unicode path(Path::CURDIR);
    FilePath stack(path);
    swap(*this, stack);
  }

  FilePath(const FilePath& object)
  : self_path(NULL)
  {
    byte* buffer = NULL;
#if (QUIRINUS_FEATURE_POSIX)
    const size_t append = 1;
#else
    const size_t append = 2;
#endif
    const byte* path = static_cast<byte*>(object.self_path);
    const size_t size = object.self_size;
    buffer = new byte[size + append];
    ::memcpy(buffer, path, size);
    ::memset((buffer + size), 0, append);
    self_path = buffer;
    self_size = size;
  }

#if (QUIRINUS_FEATURE_CXX11)
  FilePath(const FilePath&& object)
  : self_path(NULL)
  { swap(*this, object); }
#endif

  FilePath(const char* str)
  : self_path(NULL)
  {
    Bytes path(str);
    FilePath stack(path);
    swap(*this, stack);
  }

  FilePath(const wchar_t* str)
  : self_path(NULL)
  {
    Unicode path(str);
    FilePath stack(path);
    swap(*this, stack);
  }

  FilePath(const bytechar* str)
  : self_path(NULL)
  {
    Bytes path(str);
    FilePath stack(path);
    swap(*this, stack);
  }

  FilePath(const widechar* str)
  : self_path(NULL)
  {
    Unicode path(str);
    FilePath stack(path);
    swap(*this, stack);
  }

  FilePath(const unicode* str)
  : self_path(NULL)
  {
    Unicode path(str);
    FilePath stack(path);
    swap(*this, stack);
  }

  FilePath(const Bytes& str)
  : self_path(NULL)
  {
    if (str.nullcheck())
      throw ValueError("null character occured");
#if (QUIRINUS_FEATURE_POSIX)
    Bytes stack(str.head(), str.tail());
#else
    Bytes stack(codecs::convert(str, "UTF-8", "UTF-16"));
#endif
    self_size = stack.length();
    const bytechar* pointer = static_cast<const bytechar*>(stack);
    const size_t size = stack.length();
    self_path = mkpath(pointer, size);
#if (QUIRINUS_FEATURE_POSIX)
    self_size = nullstrlen(static_cast<char*>(self_path));
#else
    self_size = (nullstrlen(static_cast<wchar_t*>(self_path)) * 2);
#endif
  }

  FilePath(const Unicode& str)
  : self_path(NULL)
  {
    if (str.nullcheck())
      throw ValueError("null character occured");
    Bytes encoding = Path::encoding();
    Bytes stack = codecs::encode(str, encoding);
    const bytechar* pointer = static_cast<const bytechar*>(stack);
    const size_t size = stack.length();
    self_path = mkpath(pointer, size);
#if (QUIRINUS_FEATURE_POSIX)
    self_size = nullstrlen(static_cast<char*>(self_path));
#else
    self_size = (nullstrlen(static_cast<wchar_t*>(self_path)) * 2);
#endif
  }


  // Swap function
  friend void
  swap(FilePath& lhs, FilePath& rhs)
  {
    using std::swap;
    swap(lhs.self_size, rhs.self_size);
    swap(lhs.self_path, rhs.self_path);
  }


  // Assignement function
  FilePath&
  operator=(FilePath path)
  {
    swap(*this, path);
    return *this;
  }


  // Cast functions
  operator const char*() const
  {
#if (QUIRINUS_FEATURE_POSIX)
    return static_cast<const char*>(self_path);
#else
    throw CastError("C++ const char* casting failed");
#endif
  }

  operator const wchar_t*() const
  {
#if (QUIRINUS_FEATURE_POSIX)
    throw CastError("C++ const wchar_t* casting failed");
#else
    return static_cast<const wchar_t*>(self_path);
#endif
  }


  // Virtual functions
  FilePath*
  clone() const
  { return new FilePath(*this); }

  Bytes
  repr() const
  {
    try { return this->cast_unicode().repr(); }
    catch (const DecodeError& error) { return this->cast_bytes().repr(); }
  }

  Bytes
  cast_bytes() const
  {
    const size_t size = self_size;
    const byte* path = static_cast<byte*>(self_path);
#if (QUIRINUS_FEATURE_POSIX)
    return Bytes(path, size);
#else
    Bytes stack(path, size);
    return codecs::convert(stack, "UTF-16", "UTF-8");
#endif
  }

  Unicode
  cast_unicode() const
  {
    Bytes stack = this->cast_bytes();
#if (QUIRINUS_FEATURE_POSIX)
    Bytes encoding = Path::encoding();
    return codecs::decode(stack, encoding);
#else
    return codecs::decode(stack, "UTF-8");
#endif
  }


  // Comparison functions
  static int
  cmp(const FilePath& lhs, const FilePath& rhs)
  {
    Bytes loperand = lhs.cast_bytes();
    Bytes roperand = rhs.cast_bytes();
    return Bytes::cmp(loperand, roperand);
  }


  // Mathematic functions
  friend FilePath
  operator/(const FilePath& lhs, const FilePath& rhs)
  {
    if (lhs == Path::CURDIR)
      return rhs;
    if (rhs.is_absolute() \
    || (rhs == Path::CURDIR))
      return lhs;
    const byte* lpath = static_cast<byte*>(lhs.self_path);
    const byte* rpath = static_cast<byte*>(rhs.self_path);
#if (QUIRINUS_FEATURE_POSIX)
    const size_t append = 1;
    const byte separator[1] = {'/'};
#else
    const size_t append = 2;
    const byte separator[2] = {'\\', '\0'};
#endif
    const size_t lsize = lhs.self_size;
    const size_t rsize = rhs.self_size;
    const size_t size = (lsize + append + rsize);
    byte* buffer = new byte[size + append];
    ::memcpy(buffer, lpath, lsize);
    ::memcpy((buffer + lsize), separator, append);
    ::memcpy((buffer + lsize + append), rpath, rsize);
    ::memset((buffer + lsize + append + rsize), 0, append);
    Bytes encoding = Path::encoding();
    Bytes stack(buffer, size);
#if !(QUIRINUS_FEATURE_POSIX)
    stack = codecs::convert(stack, "UTF-16", "UTF-8");
#endif
    delete[] buffer;
    return stack;
  }


  // Unary functions
  FilePath&
  operator/=(const FilePath& object)
  {
    FilePath stack(*this / object);
    swap(*this, stack);
    return *this;
  }


  Bool
  is_absolute() const
  {
    Bytes stack = this->cast_bytes();
#if (QUIRINUS_FEATURE_POSIX)
    const bytechar* path = stack.head();
    return (path[0] == '/');
#else
    size_t size = 4;
    bool state = false;
    char* drive = new char[size];
    ::memset(drive, 0, size);
    drive[1] = '\x00'; drive[3] = ':';
    const bytechar* path = stack.head();
    for (char letter = 'A'; letter <= 'Z'; ++letter)
    {
      drive[0] = letter;
      if ((drive[1] == path[1])
      &&  (drive[3] == path[3]))
      {
        state = true;
        break;
      }
    }
    delete[] drive;
    return state;
#endif
  }


  FilePath
  canonical() const
  {
    bool abspath;
    FilePath path;
#if (QUIRINUS_FEATURE_POSIX)
    bytechar sep = '/';
#else
    bytechar sep = '\\';
#endif
    std::vector<Bytes> names;
    std::vector<Bytes> stack;
    const bytechar* byte_iter = NULL;
    const bytechar* byte_tail = NULL;
    const bytechar* name_iter = NULL;
    const bytechar* name_tail = NULL;
    std::vector<Bytes>::const_iterator names_iter;
    std::vector<Bytes>::const_iterator names_tail;
    std::vector<Bytes>::const_iterator names_temp;
    Bytes str = this->cast_bytes();

    // Split path into names.
    byte_iter = str.head();
    byte_tail = str.tail();
    abspath = (*byte_iter == sep);
    byte_iter += abspath;
    while (byte_iter < byte_tail)
    {
      if ((byte_iter[0] == '.')
      && (((byte_iter + 1) < byte_tail) && (byte_iter[1] == sep)))
      {
        byte_iter += 2;
        continue;
      }
      name_iter = byte_iter;
      name_tail = byte_iter;
      while ((name_tail < byte_tail) && (*name_tail != sep))
        ++name_tail;
      Bytes name(name_iter, name_tail);
      name_tail += (*name_tail == sep);
      names.push_back(name);
      byte_iter = name_tail;
    }

    // Process parent directories.
    names_iter = names.begin();
    names_tail = names.end();
    while (names_iter < names_tail)
    {
      size_t dirs = 0;
      size_t shift = 0;
      while ((names_iter < names_tail) && (*names_iter != Path::PARDIR))
        ++names_iter, ++dirs;
      while ((names_iter < names_tail) && (*names_iter == Path::PARDIR))
        ++names_iter, ++shift;

      // Append normal directories.
      if (!dirs && shift)
        continue;

      if (dirs && (shift <= dirs))
      {
        size_t diff = (dirs - shift);
        size_t offset = (dirs + shift);
        names_temp = (names_iter - offset);
        for (size_t i = 0; i < diff; ++i)
          stack.push_back(names_temp[i]);
        continue;
      }

      // Append parent directories.
      size_t backup = stack.size();
      if (shift > backup)
      {
        stack.clear();
        size_t diff = (shift - backup);
        for (size_t i = 0; i < diff; ++i)
          stack.push_back(Path::PARDIR);
      }

      // Adjust directories count.
      else
      {
        size_t diff = (dirs + backup - shift);
        stack.resize(diff);
      }
    }
    size_t size = stack.size();
    names_iter = stack.begin();
    names_tail = stack.end();
    if (abspath)
      path = Path::SEP;
    if (size == 0)
      return path;
    if (abspath && (*names_iter == Path::PARDIR))
      return path;
    for (; names_iter < names_tail; ++names_iter)
      path /= *names_iter;
    return path;
  }
};


} // namespace filesystem
} // namespace quirinus
#include "autotype/FilePath.hpp"
#endif // QUIRINUS_FILESYSTEM_FILEPATH_HPP
