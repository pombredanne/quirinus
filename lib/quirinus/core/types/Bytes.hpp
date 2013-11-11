/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_TYPES_BYTES_HPP
#define QUIRINUS_CORE_TYPES_BYTES_HPP
namespace quirinus {


class Bytes: public Object
{
private:
  bytecharstack self;
public:
  friend class Bool;
  friend class Int;
  friend class Float;
  friend class Unicode;
  friend class Iter;
  Bytes(const Object&);
public:
  Iter iter() const;
  Bytes repr() const;
  Bool cast_bool() const;
  Int cast_int() const;
  Float cast_float() const;
  Bytes cast_bytes() const;
  Unicode cast_unicode() const;
public:
  ~Bytes()
  {}

  Bytes()
  { self.push_back(0); }

  Bytes(const Bytes& object)
  : self(object.self)
  {}

#if (QUIRINUS_FEATURE_CXX11)
  Bytes(const Bytes&& object)
  { swap(*this, object); }
#endif

  Bytes(const char* object)
  {
    const bytechar* pointer = reinterpret_cast<const bytechar*>(object);
    Bytes stack(pointer, quirinus::nullstrlen(pointer));
    swap(*this, stack);
  }

  Bytes(const wchar_t* object)
  {
#if (UNICODE_WCHAR_SIZE == 4)
    const unicode* pointer = reinterpret_cast<const unicode*>(object);
#else
    const widechar* pointer = reinterpret_cast<const widechar*>(object);
#endif
    Bytes stack(pointer, quirinus::nullstrlen(pointer));
    swap(*this, stack);
  }

  Bytes(const bytechar* object)
  {
    Bytes stack(object, quirinus::nullstrlen(object));
    swap(*this, stack);
  }

  Bytes(const widechar* object)
  {
    Bytes stack(object, quirinus::nullstrlen(object));
    swap(*this, stack);
  }

  Bytes(const unicode* object)
  {
    Bytes stack(object, quirinus::nullstrlen(object));
    swap(*this, stack);
  }

  Bytes(const char* object, const size_t& len)
  {
    const bytechar* pointer = reinterpret_cast<const bytechar*>(object);
    Bytes stack(pointer, len);
    swap(*this, stack);
  }

  Bytes(const wchar_t* object, const size_t& len)
  {
#if (UNICODE_WCHAR_SIZE == 4)
    const unicode* pointer = reinterpret_cast<const unicode*>(object);
#else
    const widechar* pointer = reinterpret_cast<const widechar*>(object);
#endif
    Bytes stack(pointer, len);
    swap(*this, stack);
  }


  Bytes(const bytechar* object, const size_t& len)
  {
    if (!object)
      throw ValueError("null pointer access");
    self.reserve(len);
    for (size_t i = 0; i < len; ++i)
      self.push_back(object[i]);
  }

  Bytes(const widechar* object, const size_t& len)
  {
    if (!object)
      throw ValueError("null pointer access");
    int state = 0;
    size_t offset = 0;
    size_t declen = 0;
    size_t enclen = 0;
    unicode* decptr = NULL;
    bytechar* encptr = NULL;
    const size_t xlen = (len * 2);
    const bytechar* xptr = reinterpret_cast<const bytechar*>(object);
    state = u16_decode(xptr, xlen, decptr, declen, offset);
    if (state != UNICODE_STATE_SUCCESS)
      throw DecodeError(state, offset, "UTF-16");
    state = u8_encode(decptr, declen, encptr, enclen, offset);
    if (state != UNICODE_STATE_SUCCESS)
      throw EncodeError(state, offset, "UTF-8");
    self.reserve(enclen);
    for (size_t i = 0; i < enclen; ++i)
      self.push_back(encptr[i]);
    delete[] decptr;
    delete[] encptr;
  }

  Bytes(const unicode* object, const size_t& len)
  {
    if (!object)
      throw ValueError("null pointer access");
    int state = 0;
    size_t offset = 0;
    size_t enclen = 0;
    bytechar* encptr = NULL;
    state = u8_encode(object, len, encptr, enclen, offset);
    if (state != UNICODE_STATE_SUCCESS)
      throw EncodeError(state, offset, "UTF-8");
    self.reserve(enclen);
    for (size_t i = 0; i < enclen; ++i)
      self.push_back(encptr[i]);
    delete[] encptr;
  }

  Bytes(const char* head,
        const char* tail)
  {
    if (tail <= head)
      throw ValueError("incorrect range");
    size_t len = (tail - head);
    Bytes stack(head, len);
    swap(*this, stack);
  }

  Bytes(const wchar_t* head,
        const wchar_t* tail)
  {
    if (tail <= head)
      throw ValueError("incorrect range");
    size_t len = (tail - head);
    Bytes stack(head, len);
    swap(*this, stack);
  }

  Bytes(const bytechar* head,
        const bytechar* tail)
  {
    if (tail <= head)
      throw ValueError("incorrect range");
    size_t len = (tail - head);
    Bytes stack(head, len);
    swap(*this, stack);
  }

  Bytes(const widechar* head,
        const widechar* tail)
  {
    if (tail <= head)
      throw ValueError("incorrect range");
    size_t len = (tail - head);
    Bytes stack(head, len);
    swap(*this, stack);
  }

  Bytes(const unicode* head,
        const unicode* tail)
  {
    if (tail <= head)
      throw ValueError("incorrect range");
    size_t len = (tail - head);
    Bytes stack(head, len);
    swap(*this, stack);
  }


  // Swap function
  friend void
  swap(Bytes& lhs, Bytes& rhs)
  {
    using std::swap;
    swap(lhs.self, rhs.self);
  }


  // Assignment function
  Bytes&
  operator=(Bytes object)
  {
    swap(*this, object);
    return *this;
  }


  // Cast functions
  operator const char*() const
  { return reinterpret_cast<const char*>(&self[0]); }

  operator const bytechar*() const
  { return &self[0]; }


  // Virtual functions
  Bytes*
  clone() const
  { return new Bytes(*this); }


  // Comparison functions
  static int
  cmp(const Bytes& lhs, const Bytes& rhs)
  {
    size_t lsize = lhs.self.size();
    size_t rsize = rhs.self.size();
    size_t size = ((lsize > rsize) ? rsize : lsize);
    const bytechar* lptr = &lhs.self[0];
    const bytechar* rptr = &rhs.self[0];
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
  friend Bytes
  operator+(const Bytes& lhs, const Bytes& rhs)
  {
    Bytes result;
    bytecharstack::const_iterator lbegin = lhs.self.begin();
    bytecharstack::const_iterator lend = lhs.self.end();
    bytecharstack::const_iterator rbegin = rhs.self.begin();
    bytecharstack::const_iterator rend = rhs.self.end();
    result.self.insert(result.self.end(), lbegin, lend);
    result.self.insert(result.self.end(), rbegin, rend);
    return result;
  }

  friend Bytes
  operator*(const Bytes& object, Int count)
  {
    if (mpz_sgn(count.self) <= 0)
      return Bytes();
    Bytes result;
    bytecharstack::const_iterator begin = object.self.begin();
    bytecharstack::const_iterator end = object.self.end();
    for (; count; --count)
      result.self.insert(result.self.end(), begin, end);
    return result;
  }

  friend Bytes
  operator*(Int count, const Bytes& object)
  {
    if (mpz_sgn(count.self) <= 0)
      return Bytes();
    Bytes result;
    bytecharstack::const_iterator begin = object.self.begin();
    bytecharstack::const_iterator end = object.self.end();
    for (; count; --count)
      result.self.insert(result.self.end(), begin, end);
    return result;
  }


  // Modifying functions
  /**
   * @brief Concatenate current string with the other string.
   */
  Bytes&
  operator+=(const Bytes& object)
  {
    bytecharstack::const_iterator begin = object.self.begin();
    bytecharstack::const_iterator end = object.self.end();
    self.insert(self.end(), begin, end);
    return *this;
  }

  Bytes&
  operator*=(Int count)
  {
    if (mpz_sgn(count.self) <= 0)
      return *this;
    Bytes stack;
    stack.self.insert(stack.self.end(), self.begin(), self.end());
    bytecharstack::const_iterator begin = stack.self.begin();
    bytecharstack::const_iterator end = stack.self.end();
    for (; count; --count)
      self.insert(self.end(), begin, end);
    return *this;
  }


  // Iterable functions
  const bytechar*
  head() const
  { return &self[0]; }

  const bytechar*
  tail() const
  { return (&self[0] + self.size()); }


  /// @brief Return string length.
  Int
  length() const
  { return self.size(); }


  /// @brief Check if string starts with substring.
  Bool
  startswith(const Bytes& substring) const
  {
    size_t size = self.size();
    size_t subsize = substring.self.size();
    if (size < subsize)
      return false;
    const bytechar* head = substring.head();
    const bytechar* tail = substring.tail();
    Bytes operand(head, tail);
    return (Bytes::cmp(*this, operand) == 0);
  }


  /// @brief Check if string ends with substring.
  Bool
  endswith(const Bytes& substring) const
  {
    size_t size = self.size();
    size_t subsize = substring.self.size();
    if (size < subsize)
      return false;
    const bytechar* head = substring.head();
    const bytechar* tail = substring.tail();
    Bytes operand(head, tail);
    return (Bytes::cmp(*this, operand) == 0);
  }


  /// @brief Return pointer to string.
  const char*
  pointer() const
  { return reinterpret_cast<const char*>(&self[0]); }


  /**
   * @brief Return null terminated string.
   * @WARNING Allocated memory must be freed using delete[] statement.
   */
  char*
  nullstr() const
  {
    bytecharstack::const_iterator iter = self.begin();
    bytecharstack::const_iterator tail = self.end();
    size_t size = self.size();
    char* buffer = new char[size + 1];
    for (size_t i = 0; iter < tail; ++iter, ++i)
      buffer[i] = *iter;
    buffer[size] = 0;
    return buffer;
  }


  /// @brief Check if null character occurs.
  Bool
  nullcheck() const
  {
    bytecharstack::const_iterator iter = self.begin();
    bytecharstack::const_iterator tail = self.end();
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
struct supertype<const char*>
{ typedef Bytes type; };


template <>
struct supertype<const bytechar*>
{ typedef Bytes type; };


} // namespace quirinus
#include "autotype/Bytes.hpp"
#endif // QUIRINUS_CORE_TYPES_BYTES_HPP
