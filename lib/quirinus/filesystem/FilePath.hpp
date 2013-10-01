/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_FILESYSTEM_FILEPATH_HPP
#define QUIRINUS_FILESYSTEM_FILEPATH_HPP
#include "Path.hpp"
namespace quirinus {
namespace filesystem {


class FilePath: public Path
{
public:
  class API: public Object
  {
  public:
    enum api_type
    {
      POSIX,
      WINANSI,
      WINWIDE
    };
    api_type self;
  public:
    ~API()
    {}

    API()
#if (QUIRINUS_FEATURE_POSIX)
    : self(API::POSIX)
#else
    : self(API::WINANSI)
#endif
    {}

    API(const API& api)
    : self(api.self)
    {}

    API(const api_type& api)
    : self(api)
    {}


    // Swap function
    friend inline void
    swap(API& lhs, API& rhs)
    {
      using std::swap;
      swap(lhs.self, rhs.self);
    }


    // Assignement function
    inline API&
    operator=(API path)
    {
      swap(*this, path);
      return *this;
    }


    // Virtual functions
    Bytes repr() const
    {
      if (self == WINANSI)
        return "WinANSI";
      else if (self == WINWIDE)
        return "WinWIDE";
      return "POSIX";
    }


    // Comparison functions
    friend inline Bool
    operator==(const API& lhs, const API& rhs)
    {
      return (lhs.self == rhs.self);
    }

    friend inline Bool
    operator!=(const API& lhs, const API& rhs)
    {
      return (lhs.self != rhs.self);
    }
  };
private:
  API self_api;
  void* self_path;
public:
  ~FilePath()
  {
    if (self_api == API::WINWIDE)
      delete[] static_cast<char*>(self_path);
    delete[] static_cast<wchar_t*>(self_path);
  }

  FilePath(const FilePath& object)
  : self_api(object.self_api)
  , self_path(NULL)
  {
    if (object.self_api == API::WINWIDE)
    {
      const wchar_t* path = \
        reinterpret_cast<const wchar_t*>(object.self_path);
      self_path = quirinus::nullstrdup(path);
    }
    else
    {
      const char* path = \
        reinterpret_cast<const char*>(object.self_path);
      self_path = quirinus::nullstrdup(path);
    }
  }

#if (QUIRINUS_FEATURE_CXX11)
  FilePath(const FilePath&& object)
  : self_api(object.self_api)
  , self_path(NULL)
  {
    swap(*this, object);
  }
#endif

  FilePath(const char* object)
#if (QUIRINUS_FEATURE_POSIX)
  : self_api(API::POSIX)
#else
  : self_api(API::WINANSI)
#endif
  , self_path(NULL)
  {
    Bytes path(object);
    FilePath stack(path);
    swap(*this, stack);
  }

  FilePath(const wchar_t* object)
#if (!QUIRINUS_FEATURE_POSIX)
  : self_api(API::POSIX)
#else
  : self_api(API::WINWIDE)
#endif
  , self_path(NULL)
  {
    Unicode path(object);
    FilePath stack(path);
    swap(*this, stack);
  }

  FilePath(const bytechar* object)
#if (QUIRINUS_FEATURE_POSIX)
  : self_api(API::POSIX)
#else
  : self_api(API::WINANSI)
#endif
  , self_path(NULL)
  {
    Bytes path(object);
    FilePath stack(path);
    swap(*this, stack);
  }

  FilePath(const widechar* object)
#if (QUIRINUS_FEATURE_POSIX)
  : self_api(API::POSIX)
#else
  : self_api(API::WINWIDE)
#endif
  , self_path(NULL)
  {
    Unicode path(object);
    FilePath stack(path);
    swap(*this, stack);
  }

  FilePath(const unicode* object)
#if (QUIRINUS_FEATURE_POSIX)
  : self_api(API::POSIX)
#else
  : self_api(API::WINWIDE)
#endif
  , self_path(NULL)
  {
    Bytes path(object);
    FilePath stack(path);
    swap(*this, stack);
  }

  FilePath(const Bytes& path)
  : self_path(NULL)
  {
    if (path.nullcheck())
#if (QUIRINUS_FEATURE_POSIX)
    const char* str = path;
    self_api = API::POSIX;
    self_path = nullstrdup(str);
#else
    Unicode upath;
    bool convert = true;
    try { upath = codecs::decode(path, "UTF-8"); }
    catch (const DecodeError&)
    {
      try { upath = codecs::decode(path, "UTF-16"); }
      catch (const DecodeError&) { convert = false; }
    }
    if (convert)
    {
      FilePath stack(upath);
      swap(*this, stack);
    }
    else
    {
      const char* str = path;
      self_api = API::WINANSI;
      self_path = nullstrdup(path);
    }
#endif
  }

  FilePath(const Unicode& path)
  : self_path(NULL)
  {
#if (QUIRINUS_FEATURE_POSIX)
    self_api = API::POSIX;
    Bytes encoding = system::encoding_filesystem();
    self_path = nullstrdup(codecs::encode(path, encoding));
#else
    self_api = API::WINWIDE;
    const unicode* str = path;
    Bytes bpath = codecs::encode(path, "UTF-16");
    self_path = nullstrdup(path);
#endif
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
  operator const char*() const
  {
    return static_cast<const char*>(self_path);
  }

  operator const wchar_t*() const
  {
    if (self_api == API::WINWIDE)
      return static_cast<const char*>(self_path);
    throw CastError("C++ const wchar_t* casting failed");
  }


  // Other functions
  inline API
  api() const
  {
    return self_api;
  }

  inline Int
  mode() const;

  inline Int
  ino() const;

  inline Int
  dev() const;

  inline Int
  rdev() const;

  inline Int
  nlink() const;

  inline Int
  uid() const;

  inline Int
  gid() const;

  inline Int
  size() const;

  inline Int
  atime() const;

  inline Int
  ctime() const;

  inline Int
  mtime() const;

  inline Bool
  exists() const;

  inline Bool
  lexists() const;

  inline Bool
  isblock() const;

  inline Bool
  isdevice() const;

  inline Bool
  isdir() const;

  inline Bool
  isfifo() const;

  inline Bool
  isfile() const;

  inline Bool
  islink() const;

  inline Bool
  issocket() const;
};

} // namespace filesystem
} // namespace quirinus
#endif // QUIRINUS_FILESYSTEM_FILEPATH_HPP
