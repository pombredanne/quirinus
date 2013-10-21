/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_FILESYSTEM_API_HPP
#define QUIRINUS_FILESYSTEM_API_HPP
namespace quirinus {
namespace filesystem {


class API: public Object
{
private:
  enum enum_type
  {
    ENUM_POSIX,
    ENUM_WINANSI,
    ENUM_WINWIDE
  };
  enum_type self;
public:
  static const API POSIX;
  static const API WINANSI;
  static const API WINWIDE;
public:
  ~API()
  {}

  API()
#if (QUIRINUS_FEATURE_POSIX)
  : self(ENUM_POSIX)
#else
  : self(ENUM_WINANSI)
#endif
  {}

  API(const API& object)
  : self(object.self)
  {}

#if (QUIRINUS_FEATURE_CXX11)
  API(const API&& object)
  { swap(*this, object); }
#endif

  API(const enum_type& object)
  : self(object)
  {}


  // Swap function
  friend inline void
  swap(API& lhs, API& rhs)
  {
    using std::swap;
    swap(lhs.self, rhs.self);
  }


  // Assignment function
  inline API&
  operator=(API object)
  {
    swap(*this, object);
    return *this;
  }


  // Cast functions
  inline operator enum_type() const
  { return self; }


  // Virtual functions
  inline API*
  clone() const
  { return new API(*this); }

  inline Bytes
  repr() const
  {
#if (QUIRINUS_FEATURE_POSIX)
    return "filesystem::API::POSIX";
#else
    if (self == ENUM_WINANSI)
      return "filesystem::API::WINANSI";
    return "filesystem::API::WINWIDE";
#endif
  }

  inline Bytes
  cast_bytes() const
  { return this->repr(); }

  inline Unicode
  cast_unicode() const
  { return this->repr(); }


  // Comparison functions
  friend inline Bool
  operator==(const API& lhs, const API& rhs)
  { return (lhs.self == rhs.self); }

  friend inline Bool
  operator!=(const API& lhs, const API& rhs)
  { return (lhs.self != rhs.self); }
private:
  template<typename TYPE> operator TYPE() const;
};


} // namespace filesystem
} // namespace quirinus
#endif // QUIRINUS_FILESYSTEM_API_HPP
