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
  Unicode(const Object&);
public:
  Bytes repr() const;
  Bool cast_bool() const;
  Int cast_int() const;
  Float cast_float() const;
  Bytes cast_bytes() const;
  Unicode cast_unicode() const;
public:
  typedef unicodestack::iterator iterator;
  typedef unicodestack::const_iterator const_iterator;
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
  {
    swap(*this, object);
  }
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
      throw MemoryError("null pointer access");
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
      throw MemoryError("null pointer access");
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
      throw MemoryError("null pointer access");
    self.reserve(len);
    for (size_t i = 0; i < len; ++i)
      self.push_back(object[i]);
  }

  Unicode(charstack::const_iterator begin,
          charstack::const_iterator end)
  {
    size_t len = (end - begin);
    const char* object = &(*begin);
    Unicode stack(object, len);
    swap(*this, stack);
  }

  Unicode(wcharstack::const_iterator begin,
          wcharstack::const_iterator end)
  {
    size_t len = (end - begin);
    const wchar_t* object = &(*begin);
    Unicode stack(object, len);
    swap(*this, stack);
  }

  Unicode(bytecharstack::const_iterator begin,
          bytecharstack::const_iterator end)
  {
    size_t len = (end - begin);
    const bytechar* object = &(*begin);
    Unicode stack(object, len);
    swap(*this, stack);
  }

  Unicode(widecharstack::const_iterator begin,
          widecharstack::const_iterator end)
  {
    size_t len = (end - begin);
    const widechar* object = &(*begin);
    Unicode stack(object, len);
    swap(*this, stack);
  }

  Unicode(unicodestack::const_iterator begin,
          unicodestack::const_iterator end)
  {
    size_t len = (end - begin);
    const unicode* object = &(*begin);
    Unicode stack(object, len);
    swap(*this, stack);
  }


  // Swap function
  inline friend void
  swap(Unicode& lhs, Unicode& rhs)
  {
    using std::swap;
    swap(lhs.self, rhs.self);
  }


  // Assignment function
  inline Unicode&
  operator=(Unicode object)
  {
    swap(*this, object);
    return *this;
  }


  // Cast functions
  operator const unicode*() const
  { return reinterpret_cast<const unicode*>(&self[0]); }


  // Comparison functions
  static inline int
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
  friend inline Unicode
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

  friend inline Unicode
  operator*(const Unicode& object, Int count)
  {
    if (mpz_sgn(count.self) <= 0)
      return Unicode();
    Unicode result;
    unicodestack::const_iterator begin = object.self.begin();
    unicodestack::const_iterator end = object.self.end();
    while (count)
    {
      result.self.insert(result.self.end(), begin, end);
      --count;
    }
    return result;
  }

  friend inline Unicode
  operator*(Int count, const Unicode& object)
  {
    if (mpz_sgn(count.self) <= 0)
      return Unicode();
    Unicode result;
    unicodestack::const_iterator begin = object.self.begin();
    unicodestack::const_iterator end = object.self.end();
    while (count)
    {
      result.self.insert(result.self.end(), begin, end);
      --count;
    }
    return result;
  }


  // Modifying functions
  inline Unicode&
  operator+(const Unicode& object)
  {
    unicodestack::const_iterator begin = object.self.begin();
    unicodestack::const_iterator end = object.self.end();
    self.insert(self.end(), begin, end);
    return *this;
  }

  inline Unicode&
  operator*(Int count)
  {
    if (mpz_sgn(count.self) <= 0)
      return *this;
    Unicode stack;
    stack.self.insert(stack.self.end(), self.begin(), self.end());
    unicodestack::const_iterator begin = stack.self.begin();
    unicodestack::const_iterator end = stack.self.end();
    while (count)
    {
      self.insert(self.end(), begin, end);
      --count;
    }
    return *this;
  }


  // Other functions
  /**
   * @brief 
   */
  inline iterator
  begin()
  { return self.begin(); }


  /**
   * @brief 
   */
  inline const_iterator
  begin() const
  { return self.begin(); }


  /**
   * @brief 
   */
  inline iterator
  end()
  { return self.end(); }


  /**
   * @brief 
   */
  inline const_iterator
  end() const
  { return self.end(); }


  /**
   * @brief Return string length.
   */
  inline Int
  length() const
  { return self.size(); }


  /**
   * @brief Return null terminated string.
   * @WARNING Allocated memory must be freed using delete[] statement.
   */
  inline unicode*
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


  /**
   * @brief Check if null character occurs.
   */
  inline Bool
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


} // namespace quirinus
#endif // QUIRINUS_CORE_TYPES_UNICODE_HPP
