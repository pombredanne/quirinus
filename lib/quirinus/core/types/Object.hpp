/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_TYPES_OBJECT_HPP
#define QUIRINUS_CORE_TYPES_OBJECT_HPP
namespace quirinus {


class Object
{
public:
  virtual Bytes repr() const;
  virtual Bool cast_bool() const;
  virtual Int cast_int() const;
  virtual Float cast_float() const;
  virtual Bytes cast_bytes() const;
  virtual Unicode cast_unicode() const;
public:
  virtual operator bool() const;
  virtual operator signed char() const;
  virtual operator unsigned char() const;
  virtual operator signed short() const;
  virtual operator unsigned short() const;
  virtual operator signed int() const;
  virtual operator unsigned int() const;
  virtual operator signed long() const;
  virtual operator unsigned long() const;
#if (QUIRINUS_FEATURE_LONGLONG)
  virtual operator signed long long() const;
  virtual operator unsigned long long() const;
#endif
  virtual operator float() const;
  virtual operator double() const;
  virtual operator const char*() const;
  virtual operator const unicode*() const;
public:
  virtual ~Object()
  {}

  Object()
  {}
};


} // namespace quirinus
#endif // QUIRINUS_CORE_TYPES_OBJECT_HPP
