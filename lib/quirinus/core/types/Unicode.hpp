/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_TYPES_UNICODE_HPP
#define QUIRINUS_CORE_TYPES_UNICODE_HPP
namespace quirinus {


class Unicode: public Object
{
private:
  unicodestack self;
public:
  friend class Bool;
  friend class Int;
  friend class Float;
  friend class Bytes;
  friend class Iter;
  Unicode(const Object&);
public:
  Iter iter() const;
  Bytes repr() const;
  Bool cast_bool() const;
  Int cast_int() const;
  Float cast_float() const;
  Bytes cast_bytes() const;
  Unicode cast_unicode() const;
public:
  ~Unicode()
  {}

  Unicode()
  {}

  Unicode(const Unicode& object)
  : self(object.self)
  {}

#if (QUIRINUS_FEATURE_CXX11)
  Unicode(const Unicode&& object)
  { swap(*this, object); }
#endif

  Unicode(const char* object)
  {
    const bytechar* pointer = reinterpret_cast<const bytechar*>(object);
    Unicode stack(pointer, nullstrlen(pointer));
    swap(*this, stack);
  }

  Unicode(const wchar_t* object)
  {
#if (UNICODE_WCHAR_SIZE == 4)
    const unicode* pointer = reinterpret_cast<const unicode*>(object);
#else
    const widechar* pointer = reinterpret_cast<const widechar*>(object);
#endif
    Unicode stack(pointer, nullstrlen(pointer));
    swap(*this, stack);
  }

  Unicode(const bytechar* object)
  {
    Unicode stack(object, nullstrlen(object));
    swap(*this, stack);
  }

  Unicode(const widechar* object)
  {
    Unicode stack(object, nullstrlen(object));
    swap(*this, stack);
  }

  Unicode(const unicode* object)
  {
    Unicode stack(object, nullstrlen(object));
    swap(*this, stack);
  }

  Unicode(const char* object, const size_t& len)
  {
    const bytechar* pointer = reinterpret_cast<const bytechar*>(object);
    Unicode stack(pointer, len);
    swap(*this, stack);
  }

  Unicode(const wchar_t* object, const size_t& len)
  {
#if (UNICODE_WCHAR_SIZE == 4)
    const unicode* pointer = reinterpret_cast<const unicode*>(object);
#else
    const widechar* pointer = reinterpret_cast<const widechar*>(object);
#endif
    Unicode stack(pointer, len);
    swap(*this, stack);
  }

  Unicode(const bytechar* object, const size_t& len)
  {
    if (!object)
      throw ValueError("null pointer access");
    int state = 0;
    size_t offset = 0;
    size_t declen = 0;
    unicode* decptr = NULL;
    state = u8_decode(object, len, decptr, declen, offset);
    if (state != UNICODE_STATE_SUCCESS)
      throw DecodeError(state, offset, "UTF-8");
    self.reserve(declen);
    for (size_t i = 0; i < declen; ++i)
      self.push_back(decptr[i]);
    delete[] decptr;
  }

  Unicode(const widechar* object, const size_t& len)
  {
    if (!object)
      throw ValueError("null pointer access");
    int state = 0;
    size_t offset = 0;
    size_t declen = 0;
    unicode* decptr = NULL;
    const size_t enclen = (len * 2);
    const bytechar* encptr = reinterpret_cast<const bytechar*>(object);
    state = u16_decode(encptr, enclen, decptr, declen, offset);
    if (state != UNICODE_STATE_SUCCESS)
      throw DecodeError(state, offset, "UTF-16");
    self.reserve(declen);
    for (size_t i = 0; i < declen; ++i)
      self.push_back(decptr[i]);
  }

  Unicode(const unicode* object, const size_t& len)
  {
    if (!object)
      throw ValueError("null pointer access");
    self.reserve(len);
    for (size_t i = 0; i < len; ++i)
      self.push_back(object[i]);
  }

  Unicode(const char* head,
          const char* tail)
  {
    if (tail <= head)
      throw ValueError("incorrect range");
    size_t len = (tail - head);
    Unicode stack(head, len);
    swap(*this, stack);
  }

  Unicode(const wchar_t* head,
          const wchar_t* tail)
  {
    if (tail <= head)
      throw ValueError("incorrect range");
    size_t len = (tail - head);
    Unicode stack(head, len);
    swap(*this, stack);
  }

  Unicode(const bytechar* head,
          const bytechar* tail)
  {
    if (tail <= head)
      throw ValueError("incorrect range");
    size_t len = (tail - head);
    Unicode stack(head, len);
    swap(*this, stack);
  }

  Unicode(const widechar* head,
          const widechar* tail)
  {
    if (tail <= head)
      throw ValueError("incorrect range");
    size_t len = (tail - head);
    Unicode stack(head, len);
    swap(*this, stack);
  }

  Unicode(const unicode* head,
          const unicode* tail)
  {
    if (tail <= head)
      throw ValueError("incorrect range");
    size_t len = (tail - head);
    Unicode stack(head, len);
    swap(*this, stack);
  }


  // Swap function
  friend void
  swap(Unicode& lhs, Unicode& rhs)
  {
    using std::swap;
    swap(lhs.self, rhs.self);
  }


  // Assignment function
  Unicode&
  operator=(Unicode object)
  {
    swap(*this, object);
    return *this;
  }


  // Cast functions
  operator const unicode*() const
  { return reinterpret_cast<const unicode*>(&self[0]); }


  // Virtual functions
  Unicode*
  clone() const
  { return new Unicode(*this); }


  // Comparison functions
  static int
  cmp(const Unicode& lhs, const Unicode& rhs)
  {
    size_t lsize = lhs.self.size();
    size_t rsize = rhs.self.size();
    size_t size = ((lsize > rsize) ? rsize : lsize);
    const unicode* lptr = &lhs.self[0];
    const unicode* rptr = &rhs.self[0];
    for (size_t i = 0; i < size; ++i)
    {
      if (lptr[i] < rptr[i])
        return -1;
      else if (lptr[i] > rptr[i])
        return +1;
    }
    if (lsize < rsize)
      return -1;
    else if (lsize > rsize)
      return +1;
    return 0;
  }


  // Mathematical functions
  friend Unicode
  operator+(const Unicode& lhs, const Unicode& rhs)
  {
    Unicode result;
    unicodestack::const_iterator lbegin = lhs.self.begin();
    unicodestack::const_iterator lend = lhs.self.end();
    unicodestack::const_iterator rbegin = rhs.self.begin();
    unicodestack::const_iterator rend = rhs.self.end();
    result.self.insert(result.self.end(), lbegin, lend);
    result.self.insert(result.self.end(), rbegin, rend);
    return result;
  }

  friend Unicode
  operator*(const Unicode& object, Int count)
  {
    if (mpz_sgn(count.self) <= 0)
      return Unicode();
    Unicode result;
    unicodestack::const_iterator begin = object.self.begin();
    unicodestack::const_iterator end = object.self.end();
    for (; count; --count)
      result.self.insert(result.self.end(), begin, end);
    return result;
  }

  friend Unicode
  operator*(Int count, const Unicode& object)
  {
    if (mpz_sgn(count.self) <= 0)
      return Unicode();
    Unicode result;
    unicodestack::const_iterator begin = object.self.begin();
    unicodestack::const_iterator end = object.self.end();
    for (; count; --count)
      result.self.insert(result.self.end(), begin, end);
    return result;
  }


  // Modifying functions
  Unicode&
  operator+=(const Unicode& object)
  {
    unicodestack::const_iterator begin = object.self.begin();
    unicodestack::const_iterator end = object.self.end();
    self.insert(self.end(), begin, end);
    return *this;
  }

  Unicode&
  operator*=(Int count)
  {
    if (mpz_sgn(count.self) <= 0)
      return *this;
    Unicode stack;
    stack.self.insert(stack.self.end(), self.begin(), self.end());
    unicodestack::const_iterator begin = stack.self.begin();
    unicodestack::const_iterator end = stack.self.end();
    for (; count; --count)
      self.insert(self.end(), begin, end);
    return *this;
  }


  // Iterable functions
  const unicode*
  head() const
  { return &self[0]; }

  const unicode*
  tail() const
  { return (&self[0] + self.size()); }


  /// @brief Return string length.
  Int
  length() const
  { return self.size(); }


  /// @brief Check if string starts with substring.
  Bool
  startswith(const Unicode& substring) const
  {
    size_t size = self.size();
    size_t subsize = substring.self.size();
    if (size < subsize)
      return false;
    const unicode* head = substring.head();
    const unicode* tail = substring.tail();
    Unicode operand(head, tail);
    return (Unicode::cmp(*this, operand) == 0);
  }


  /// @brief Check if string ends with substring.
  Bool
  endswith(const Unicode& substring) const
  {
    size_t size = self.size();
    size_t subsize = substring.self.size();
    if (size < subsize)
      return false;
    const unicode* head = substring.head();
    const unicode* tail = substring.tail();
    Unicode operand(head, tail);
    return (Unicode::cmp(*this, operand) == 0);
  }

  /**
   * @brief Return null terminated string.
   * @WARNING Allocated memory must be freed using delete[] statement.
   */
  unicode*
  nullstr() const
  {
    unicodestack::const_iterator iter = self.begin();
    unicodestack::const_iterator tail = self.end();
    size_t size = self.size();
    unicode* buffer = new unicode[size + 1];
    for (size_t i = 0; iter < tail; ++iter, ++i)
      buffer[i] = *iter;
    buffer[size] = 0;
    return buffer;
  }


  /// @brief Check if null character occurs.
  Bool
  nullcheck() const
  {
    unicodestack::const_iterator iter = self.begin();
    unicodestack::const_iterator tail = self.end();
    while (iter < tail)
    {
      if (*iter == 0)
        return true;
      ++iter;
    }
    return false;
  }
};


template <>
struct supertype<const wchar_t*>
{ typedef Unicode type; };


template <>
struct supertype<const widechar*>
{ typedef Unicode type; };


template <>
struct supertype<const unicode*>
{ typedef Unicode type; };


} // namespace quirinus
#include "autotype/Unicode.hpp"
#endif // QUIRINUS_CORE_TYPES_UNICODE_HPP
