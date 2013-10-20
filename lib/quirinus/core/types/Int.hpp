/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_TYPES_INT_HPP
#define QUIRINUS_CORE_TYPES_INT_HPP
namespace quirinus {


class Int: public Object
{
private:
  mpz_t self;
public:
  friend class Bool;
  friend class Float;
  friend class Bytes;
  friend class Unicode;
  Int(const Object&);
public:
  Bytes repr() const;
  Bool cast_bool() const;
  Int cast_int() const;
  Float cast_float() const;
  Bytes cast_bytes() const;
  Unicode cast_unicode() const;
  Bytes repr(const Int&) const;
public:
  friend Bytes operator*(const Bytes& object, Int count);
  friend Bytes operator*(Int count, const Bytes& object);
  friend Unicode operator*(const Unicode& object, Int count);
  friend Unicode operator*(Int count, const Unicode& object);
public:
  ~Int()
  { ::mpz_clear(self); }

  Int()
  { ::mpz_init(self); }

  Int(const Int& object)
  {
    ::mpz_init(self);
    ::mpz_set(self, object.self);
  }

#if (QUIRINUS_FEATURE_CXX11)
  Int(const Int&& object)
  { swap(*this, object); }
#endif

  Int(const bool& object)
  {
    ::mpz_init2(self, 1);
    ::mpz_import(self, 1, 1, 1, 0, 0, &object);
  }

  Int(const signed char& object)
  {
    ::mpz_init2(self, (sizeof(signed char) * 8));
    ::mpz_import(self, 1, 1, sizeof(signed char), 0, 0, &object);
  }

  Int(const unsigned char& object)
  {
    ::mpz_init2(self, (sizeof(signed char) * 8));
    unsigned char abs_object = (object < 0) ? -object : object;
    ::mpz_import(self, 1, 1, sizeof(signed char), 0, 0, &abs_object);
    if (object < 0)
      ::mpz_neg(self, self);
  }

  Int(const signed short& object)
  {
    ::mpz_init2(self, (sizeof(signed short) * 8));
    unsigned short abs_object = (object < 0) ? -object : object;
    ::mpz_import(self, 1, 1, sizeof(signed short), 0, 0, &abs_object);
    if (object < 0)
      ::mpz_neg(self, self);
  }

  Int(const unsigned short& object)
  {
    ::mpz_init2(self, (sizeof(unsigned short) * 8));
    ::mpz_import(self, 1, 1, sizeof(unsigned short), 0, 0, &object);
  }

  Int(const signed int& object)
  {
    ::mpz_init2(self, (sizeof(signed int) * 8));
    unsigned int abs_object = (object < 0) ? -object : object;
    ::mpz_import(self, 1, 1, sizeof(signed int), 0, 0, &abs_object);
    if (object < 0)
      ::mpz_neg(self, self);
  }

  Int(const unsigned int& object)
  {
    ::mpz_init2(self, (sizeof(unsigned int) * 8));
    ::mpz_import(self, 1, 1, sizeof(unsigned int), 0, 0, &object);
  }

  Int(const signed long& object)
  {
    ::mpz_init2(self, (sizeof(signed long) * 8));
    unsigned long abs_object = (object < 0) ? -object : object;
    ::mpz_import(self, 1, 1, sizeof(signed long), 0, 0, &abs_object);
    if (object < 0)
      ::mpz_neg(self, self);
  }

  Int(const unsigned long& object)
  {
    ::mpz_init2(self, (sizeof(unsigned long) * 8));
    ::mpz_import(self, 1, 1, sizeof(unsigned long), 0, 0, &object);
  }

#if (QUIRINUS_FEATURE_LONGLONG)
  Int(const signed long long& object)
  {
    ::mpz_init2(self, (sizeof(signed long long) * 8));
    unsigned long long abs_object = (object < 0) ? -object : object;
    ::mpz_import(self, 1, 1, sizeof(signed long long), 0, 0, &abs_object);
    if (object < 0)
      ::mpz_neg(self, self);
  }

  Int(const unsigned long long& object)
  {
    ::mpz_init2(self, (sizeof(unsigned long long) * 8));
    ::mpz_import(self, 1, 1, sizeof(unsigned long long), 0, 0, &object);
  }
#endif

  Int(const float& object)
  {
    ::mpz_init(self);
    ::mpz_set_d(self, (double)(object));
  }

  Int(const double& object)
  {
    ::mpz_init(self);
    ::mpz_set_d(self, (double)(object));
  }

  Int(const mpz_t& object)
  {
    ::mpz_init(self);
    ::mpz_set(self, object);
  }

  Int(const mpfr_t& object)
  {
    ::mpz_init(self);
    ::mpfr_get_z(self, object, MPFR_RNDA);
  }

  Int(const char* object)
  {
    int state;
    ::mpz_init(self);
    state = ::mpz_set_str(self, object, 10);
    if (state != 0)
    {
      ::mpz_clear(self);
      throw CastError("int casting failed");
    }
  }

  Int(const char* object, const int& base)
  {
    int state;
    ::mpz_init(self);
    state = ::mpz_set_str(self, object, base);
    if (state != 0)
    {
      ::mpz_clear(self);
      throw CastError("int casting failed");
    }
  }


  // Swap function
  inline friend void
  swap(Int& lhs, Int& rhs)
  { ::mpz_swap(lhs.self, rhs.self); }


  // Assignment function
  inline Int&
  operator=(Int object)
  {
    swap(*this, object);
    return *this;
  }


  // Cast functions
  operator signed char() const
  {
    size_t count;
    signed char stack;
    Int min = std::numeric_limits<signed char>::min();
    Int max = std::numeric_limits<signed char>::max();
    if ((::mpz_cmp(self, min.self) >= 0)
    ||  (::mpz_cmp(self, max.self) <= 0))
    {
      ::mpz_export(&stack, &count, 0, sizeof(signed char), 0, 0, self);
      return (stack * mpz_sgn(self));
    }
    throw CastError("C++ signed char casting failed");
  }

  operator unsigned char() const
  {
    size_t count;
    unsigned char stack;
    Int min = std::numeric_limits<unsigned char>::min();
    Int max = std::numeric_limits<unsigned char>::max();
    if ((::mpz_cmp(self, min.self) >= 0)
    ||  (::mpz_cmp(self, max.self) <= 0))
    {
      ::mpz_export(&stack, &count, 0, sizeof(unsigned char), 0, 0, self);
      return (stack * mpz_sgn(self));
    }
    throw CastError("C++ unsigned char casting failed");
  }

  operator signed short() const
  {
    size_t count;
    signed short stack;
    Int min = std::numeric_limits<signed short>::min();
    Int max = std::numeric_limits<signed short>::max();
    if ((::mpz_cmp(self, min.self) >= 0)
    ||  (::mpz_cmp(self, max.self) <= 0))
    {
      ::mpz_export(&stack, &count, 0, sizeof(signed short), 0, 0, self);
      return (stack * mpz_sgn(self));
    }
    throw CastError("C++ signed short casting failed");
  }

  operator unsigned short() const
  {
    size_t count;
    unsigned short stack;
    Int min = std::numeric_limits<unsigned short>::min();
    Int max = std::numeric_limits<unsigned short>::max();
    if ((::mpz_cmp(self, min.self) >= 0)
    ||  (::mpz_cmp(self, max.self) <= 0))
    {
      ::mpz_export(&stack, &count, 0, sizeof(unsigned short), 0, 0, self);
      return (stack * mpz_sgn(self));
    }
    throw CastError("C++ unsigned short casting failed");
  }

  operator signed int() const
  {
    size_t count;
    signed int stack;
    Int min = std::numeric_limits<signed int>::min();
    Int max = std::numeric_limits<signed int>::max();
    if ((::mpz_cmp(self, min.self) >= 0)
    ||  (::mpz_cmp(self, max.self) <= 0))
    {
      ::mpz_export(&stack, &count, 0, sizeof(signed int), 0, 0, self);
      return (stack * mpz_sgn(self));
    }
    throw CastError("C++ signed int casting failed");
  }

  operator unsigned int() const
  {
    size_t count;
    unsigned int stack;
    Int min = std::numeric_limits<unsigned int>::min();
    Int max = std::numeric_limits<unsigned int>::max();
    if ((::mpz_cmp(self, min.self) >= 0)
    ||  (::mpz_cmp(self, max.self) <= 0))
    {
      ::mpz_export(&stack, &count, 0, sizeof(unsigned int), 0, 0, self);
      return (stack * mpz_sgn(self));
    }
    throw CastError("C++ unsigned int casting failed");
  }

  operator signed long() const
  {
    size_t count;
    signed long stack;
    Int min = std::numeric_limits<signed long>::min();
    Int max = std::numeric_limits<signed long>::max();
    if ((::mpz_cmp(self, min.self) >= 0)
    ||  (::mpz_cmp(self, max.self) <= 0))
    {
      ::mpz_export(&stack, &count, 0, sizeof(signed long), 0, 0, self);
      return (stack * mpz_sgn(self));
    }
    throw CastError("C++ signed long casting failed");
  }

  operator unsigned long() const
  {
    size_t count;
    unsigned long stack;
    Int min = std::numeric_limits<unsigned long>::min();
    Int max = std::numeric_limits<unsigned long>::max();
    if ((::mpz_cmp(self, min.self) >= 0)
    ||  (::mpz_cmp(self, max.self) <= 0))
    {
      ::mpz_export(&stack, &count, 0, sizeof(unsigned long), 0, 0, self);
      return (stack * mpz_sgn(self));
    }
    throw CastError("C++ unsigned long casting failed");
  }

#if (QUIRINUS_FEATURE_LONGLONG)
  operator signed long long() const
  {
    size_t count;
    signed long long stack;
    Int min = std::numeric_limits<signed long long>::min();
    Int max = std::numeric_limits<signed long long>::max();
    if ((::mpz_cmp(self, min.self) >= 0)
    ||  (::mpz_cmp(self, max.self) <= 0))
    {
      ::mpz_export(&stack, &count, 0, sizeof(signed long long), 0, 0, self);
      return (stack * mpz_sgn(self));
    }
    throw CastError("C++ signed long long casting failed");
  }

  operator unsigned long long() const
  {
    size_t count;
    unsigned long long stack;
    Int min = std::numeric_limits<unsigned long long>::min();
    Int max = std::numeric_limits<unsigned long long>::max();
    if ((::mpz_cmp(self, min.self) >= 0)
    ||  (::mpz_cmp(self, max.self) <= 0))
    {
      ::mpz_export(&stack, &count, 0, sizeof(unsigned long long), 0, 0, self);
      return (stack * mpz_sgn(self));
    }
    throw CastError("C++ unsigned long long casting failed");
  }
#endif // QUIRINUS_FEATURE_LONGLONG


  // Comparison functions
  static inline int
  cmp(const Int& lhs, const Int& rhs)
  {
    return ::mpz_cmp(lhs.self, rhs.self);
  }


  // Mathematical functions
  friend inline Int
  operator+(const Int& lhs, const Int& rhs)
  {
    Int result;
    ::mpz_add(result.self, lhs.self, rhs.self);
    return result;
  }

  friend inline Int
  operator-(const Int& lhs, const Int& rhs)
  {
    Int result;
    ::mpz_sub(result.self, lhs.self, rhs.self);
    return result;
  }

  friend inline Int
  operator*(const Int& lhs, const Int& rhs)
  {
    Int result;
    ::mpz_mul(result.self, lhs.self, rhs.self);
    return result;
  }

  friend inline Int
  operator/(const Int& lhs, const Int& rhs)
  {
    if (!mpz_sgn(rhs.self))
      throw ZeroDivError("division by zero");
    Int result;
    ::mpz_div(result.self, lhs.self, rhs.self);
    return result;
  }

  friend inline Int
  operator%(const Int& lhs, const Int& rhs)
  {
    if (!mpz_sgn(rhs.self))
      throw ZeroDivError("division by zero");
    Int result;
    ::mpz_mod(result.self, lhs.self, rhs.self);
    return result;
  }


  // Logical functions
  friend inline Int
  operator&(const Int& lhs, const Int& rhs)
  {
    Int result;
    ::mpz_and(result.self, lhs.self, rhs.self);
    return result;
  }

  friend inline Int
  operator|(const Int& lhs, const Int& rhs)
  {
    Int result;
    ::mpz_ior(result.self, lhs.self, rhs.self);
    return result;
  }

  friend inline Int
  operator^(const Int& lhs, const Int& rhs)
  {
    Int result;
    ::mpz_xor(result.self, lhs.self, rhs.self);
    return result;
  }

  friend inline Int
  operator<<(const Int& lhs, const Int& rhs)
  {
    Int result;
    ::mpz_mul_2exp(result.self, lhs.self, rhs);
    return result;
  }

  friend inline Int
  operator>>(const Int& lhs, const Int& rhs)
  {
    Int result;
    ::mpz_fdiv_q_2exp(result.self, lhs.self, rhs);
    return result;
  }


  // Modifying functions
  inline Int&
  operator+=(const Int& object)
  {
    ::mpz_and(self, self, object.self);
    return *this;
  }

  inline Int&
  operator-=(const Int& object)
  {
    ::mpz_sub(self, self, object.self);
    return *this;
  }

  inline Int&
  operator*=(const Int& object)
  {
    ::mpz_mul(self, self, object.self);
    return *this;
  }

  inline Int&
  operator/=(const Int& object)
  {
    if (!mpz_sgn(object.self))
      throw ZeroDivError("division by zero");
    ::mpz_div(self, self, object.self);
    return *this;
  }

  inline Int&
  operator%=(const Int& object)
  {
    if (!mpz_sgn(object.self))
      throw ZeroDivError("division by zero");
    ::mpz_mod(self, self, object.self);
    return *this;
  }

  inline Int&
  operator<<=(const Int& object)
  {
    ::mpz_mul_2exp(self, self, object);
    return *this;
  }

  inline Int&
  operator>>=(const Int& object)
  {
    ::mpz_fdiv_q_2exp(self, self, object);
    return *this;
  }

  inline Int&
  operator&=(const Int& object)
  {
    ::mpz_and(self, self, object.self);
    return *this;
  }

  inline Int&
  operator|=(const Int& object)
  {
    ::mpz_ior(self, self, object.self);
    return *this;
  }

  inline Int&
  operator^=(const Int& object)
  {
    ::mpz_xor(self, self, object.self);
    return *this;
  }

  inline const Int&
  operator++()
  {
    ::mpz_add_ui(self, self, 1);
    return *this;
  }

  inline const Int&
  operator--()
  {
    ::mpz_sub_ui(self, self, 1);
    return *this;
  }

  inline Int
  operator++(int)
  {
    Int result(*this);
    this->operator++();
    return result;
  }

  inline Int
  operator--(int)
  {
    Int result(*this);
    this->operator--();
    return result;
  }


  // Unary functions
  inline Int
  operator+() const
  {
    Int result;
    ::mpz_abs(result.self, self);
    return result;
  }

  inline Int
  operator-() const
  {
    Int result;
    ::mpz_neg(result.self, self);
    return result;
  }


  // Other functions
  inline void
  memory_import(const void* array,
                const size_t& count,
                const size_t& size,
                const size_t& nails,
                const int& endian,
                const int& order)
  {
    if (!array)
      throw MemoryError("null pointer access");
    ::mpz_import(self, count, order, size, endian, nails, array);
  }

  inline void
  memory_export(void* array,
                size_t& count,
                const size_t& size,
                const size_t& nails,
                const int& endian,
                const int& order)
  {
    if (!array)
      throw MemoryError("null pointer access");
    ::mpz_export(array, &count, order, size, endian, nails, self);
  }
};


} // namespace quirinus
#endif // QUIRINUS_CORE_TYPES_INT_HPP
