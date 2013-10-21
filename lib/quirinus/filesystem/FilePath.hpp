/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_FILESYSTEM_FILEPATH_HPP
#define QUIRINUS_FILESYSTEM_FILEPATH_HPP
#include "API.hpp"
#include "VirtualPath.hpp"
namespace quirinus {
namespace filesystem {


class FilePath: public Path
{
private:
  API self_api;
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
  Bool isblock() const;
  Bool isdevice() const;
  Bool isdir() const;
  Bool isfifo() const;
  Bool isfile() const;
  Bool islink() const;
  Bool issocket() const;
public:
  ~FilePath()
  {
    delete[] static_cast<byte*>(self_path);
  }

  FilePath(const FilePath& object)
  {
    size_t size = 0;
    byte* buffer = NULL;
    self_api = object.self_api;
    const void* pointer = object.self_path;
    if (self_api == filesystem::API::WINWIDE)
      size = (nullstrlen(static_cast<const wchar_t*>(pointer)) * 2);
    else
      size = nullstrlen(static_cast<const char*>(pointer));
    size_t append = ((self_api == filesystem::API::WINWIDE) ? 2 : 1);
    buffer = new byte[size + append];
    ::memcpy(buffer, pointer, size);
    for (size_t i = 0; i < append; ++i)
      buffer[size + i] = 0;
    self_path = buffer;
  }

  FilePath(const char* str)
  : self_api()
  , self_path(NULL)
  {
    Bytes path(str);
    FilePath stack(path);
    swap(*this, stack);
  }

  FilePath(const wchar_t* str)
  : self_api()
  , self_path(NULL)
  {
    Unicode path(str);
    FilePath stack(path);
    swap(*this, stack);
  }

  FilePath(const bytechar* str)
  : self_api()
  , self_path(NULL)
  {
    Bytes path(str);
    FilePath stack(path);
    swap(*this, stack);
  }

  FilePath(const widechar* str)
  : self_api()
  , self_path(NULL)
  {
    Unicode path(str);
    FilePath stack(path);
    swap(*this, stack);
  }

  FilePath(const unicode* str)
  : self_api()
  , self_path(NULL)
  {
    Unicode path(str);
    FilePath stack(path);
    swap(*this, stack);
  }

  FilePath(const Bytes& str)
  : self_api()
  , self_path(NULL)
  {
    if (str.nullcheck())
      throw ValueError("null character occured");
#if (QUIRINUS_FEATURE_POSIX)
    size_t size = str.length();
    self_api = filesystem::API::POSIX;
    Bytes::const_iterator iter = str.begin();
#else
    Bytes stack = str;
    self_api = filesystem::API::WINANSI;

    // Check for UTF-8 encoding.
    try
    {
      stack = codecs::convert(stack, "UTF-8", "UTF-16");
      self_api = filesystem::API::WINWIDE;
    }
    catch (...) { /* pass */ }

    // Check for UTF-16 encoding.
    try
    {
      codecs::decode(stack, "UTF-16");
      self_api = filesystem::API::WINWIDE;
    }
    catch (...) { /* pass */ }

    // Initialize members.
    size_t size = stack.length();
    Bytes::const_iterator iter = stack.begin();
#endif
    byte* buffer = NULL;
    const bytechar* pointer = &(*iter);
    size_t append = ((self_api == filesystem::API::WINWIDE) ? 2 : 1);
    buffer = new byte[size + append];
    ::memcpy(buffer, pointer, size);
    for (size_t i = 0; i < append; ++i)
      buffer[size + i] = 0;
    self_path = buffer;
  }

  FilePath(const Unicode& str)
  : self_api()
  , self_path(NULL)
  {
    if (str.nullcheck())
      throw ValueError("null character occured");
#if (QUIRINUS_FEATURE_POSIX)
    self_api = filesystem::API::POSIX;
#else
    self_api = filesystem::API::WINWIDE;
#endif
    byte* buffer = NULL;
    Bytes encoding = encoding_filesystem();
    Bytes stack = codecs::encode(str, encoding);
    size_t size = stack.length();
    Bytes::const_iterator iter = stack.begin();
    const bytechar* pointer = &(*iter);
    size_t append = ((self_api == filesystem::API::WINWIDE) ? 2 : 1);
    buffer = new byte[size + append];
    ::memcpy(buffer, pointer, size);
    for (size_t i = 0; i < append; ++i)
      buffer[size + i] = 0;
    self_path = buffer;
  }


  // Swap function
  friend inline void
  swap(FilePath& lhs, FilePath& rhs)
  {
    using std::swap;
    swap(lhs.self_api, rhs.self_api);
    swap(lhs.self_path, rhs.self_path);
  }


  // Assignement function
  inline FilePath&
  operator=(FilePath path)
  {
    swap(*this, path);
    return *this;
  }


  // Cast functions
  inline operator const char*() const
  {
    if (self_api == filesystem::API::WINWIDE)
      return (static_cast<const char*>(self_path) + 2);
    return static_cast<const char*>(self_path);
  }

  inline operator const wchar_t*() const
  {
    if (self_api == filesystem::API::WINWIDE)
      return (static_cast<const wchar_t*>(self_path) + 1);
    throw CastError("C++ const wchar_t* casting failed");
  }


  // Virtual functions
  inline FilePath*
  clone() const
  { return new FilePath(*this); }

  inline Bytes
  repr() const
  {
    try { return cast_unicode().repr(); }
    catch (const DecodeError& error) { return cast_bytes().repr(); }
  }

  inline Bytes
  cast_bytes() const
  {
    size_t size = 0;
    const bytechar* path = NULL;
    if (self_api == filesystem::API::WINWIDE)
    {
      size = (nullstrlen(static_cast<const wchar_t*>(self_path)) * 2);
      path = (static_cast<const bytechar*>(self_path) + 2);
      size -= 2;
    }
    else
    {
      size = nullstrlen(static_cast<const char*>(self_path));
      path = static_cast<const bytechar*>(self_path);
    }
    return Bytes(path, size);
  }

  Unicode
  cast_unicode() const
  {
    Bytes stack = this->cast_bytes();
    Bytes encoding = encoding_filesystem();
    return codecs::decode(stack, encoding);
  }


  // Filesystem functions
  inline API
  api() const
  { return self_api; }
};


} // namespace filesystem
} // namespace quirinus
#endif // QUIRINUS_FILESYSTEM_FILEPATH_HPP
