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
  Bytes(const Object&);
public:
  Bytes repr() const;
  Bool cast_bool() const;
  Int cast_int() const;
  Float cast_float() const;
  Bytes cast_bytes() const;
  Unicode cast_unicode() const;
public:
  typedef bytecharstack::iterator iterator;
  typedef bytecharstack::const_iterator const_iterator;
public:
  ~Bytes()
  {}

  Bytes()
  {}

  Bytes(const Bytes& object)
  : self(object.self)
  {}

#if (QUIRINUS_FEATURE_CXX11)
  Bytes(const Bytes&& object)
  {
    swap(*this, object);
  }
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
      throw MemoryError("null pointer access");
    self.reserve(len);
    for (size_t i = 0; i < len; ++i)
      self.push_back(object[i]);
  }

  Bytes(const widechar* object, const size_t& len)
  {
    if (!object)
      throw MemoryError("null pointer access");
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
      throw MemoryError("null pointer access");
    int state = 0;
    size_t offset = 0;
    size_t enclen = 0;
    bytechar* encptr = NULL;
    state = u8_encode(object, len, encptr, enclen, offset);
    std::cout << "unicode " << state << std::endl;
    if (state != UNICODE_STATE_SUCCESS)
      throw EncodeError(state, offset, "UTF-8");
    self.reserve(enclen);
    for (size_t i = 0; i < enclen; ++i)
      self.push_back(encptr[i]);
    delete[] encptr;
  }

  Bytes(charstack::const_iterator begin,
        charstack::const_iterator end)
  {
    size_t len = (end - begin);
    const char* object = &(*begin);
    Bytes stack(object, len);
    swap(*this, stack);
  }

  Bytes(wcharstack::const_iterator begin,
        wcharstack::const_iterator end)
  {
    size_t len = (end - begin);
    const wchar_t* object = &(*begin);
    Bytes stack(object, len);
    swap(*this, stack);
  }

  Bytes(bytecharstack::const_iterator begin,
        bytecharstack::const_iterator end)
  {
    size_t len = (end - begin);
    const bytechar* object = &(*begin);
    Bytes stack(object, len);
    swap(*this, stack);
  }

  Bytes(widecharstack::const_iterator begin,
        widecharstack::const_iterator end)
  {
    size_t len = (end - begin);
    const widechar* object = &(*begin);
    Bytes stack(object, len);
    swap(*this, stack);
  }

  Bytes(unicodestack::const_iterator begin,
        unicodestack::const_iterator end)
  {
    size_t len = (end - begin);
    const unicode* object = &(*begin);
    Bytes stack(object, len);
    swap(*this, stack);
  }


  // Swap function
  inline friend void
  swap(Bytes& lhs, Bytes& rhs)
  {
    using std::swap;
    swap(lhs.self, rhs.self);
  }


  // Assignment function
  inline Bytes&
  operator=(Bytes object)
  {
    swap(*this, object);
    return *this;
  }


  // Cast functions
  operator const char*() const
  { return reinterpret_cast<const char*>(&self[0]); }

  operator const bytechar*() const
  { return reinterpret_cast<const bytechar*>(&self[0]); }


  // Virtual functions
  inline Bytes*
  clone() const
  { return new Bytes(*this); }


  // Comparison functions
  static inline int
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
  friend inline Bytes
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

  friend inline Bytes
  operator*(const Bytes& object, Int count)
  {
    if (mpz_sgn(count.self) <= 0)
      return Bytes();
    Bytes result;
    bytecharstack::const_iterator begin = object.self.begin();
    bytecharstack::const_iterator end = object.self.end();
    while (count)
    {
      result.self.insert(result.self.end(), begin, end);
      --count;
    }
    return result;
  }

  friend inline Bytes
  operator*(Int count, const Bytes& object)
  {
    if (mpz_sgn(count.self) <= 0)
      return Bytes();
    Bytes result;
    bytecharstack::const_iterator begin = object.self.begin();
    bytecharstack::const_iterator end = object.self.end();
    while (count)
    {
      result.self.insert(result.self.end(), begin, end);
      --count;
    }
    return result;
  }


  // Modifying functions
  /**
   * @brief Concatenate current string with the other string.
   */
  inline Bytes&
  operator+(const Bytes& object)
  {
    bytecharstack::const_iterator begin = object.self.begin();
    bytecharstack::const_iterator end = object.self.end();
    self.insert(self.end(), begin, end);
    return *this;
  }

  /**
   * @brief 
   */
  inline Bytes&
  operator*(Int count)
  {
    if (mpz_sgn(count.self) <= 0)
      return *this;
    Bytes stack;
    stack.self.insert(stack.self.end(), self.begin(), self.end());
    bytecharstack::const_iterator begin = stack.self.begin();
    bytecharstack::const_iterator end = stack.self.end();
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
  inline char*
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


  /**
   * @brief Check if null character occurs.
   */
  inline Bool
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


} // namespace quirinus
#endif // QUIRINUS_CORE_TYPES_BYTES_HPP
