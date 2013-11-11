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
  template <typename TYPE> struct autotype;
  template <typename TYPE> struct typeinfo;
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

  template <typename TYPE>
  Int(TYPE object)
  {
    if (Int::typeinfo<TYPE>::sign)
    {
      ::mpz_init2(self, (sizeof(TYPE) * CHAR_BIT));
      typename Int::typeinfo<TYPE>::stype svalue(object);
      typename Int::typeinfo<TYPE>::utype uvalue(object);
      uvalue = ((svalue < 0) ? -svalue : svalue);
      ::mpz_import(self, 1, 1, sizeof(TYPE), 0, 0, &uvalue);
      if (svalue < 0)
        ::mpz_neg(self, self);
    }
    else
    {
      ::mpz_init2(self, (sizeof(TYPE) * CHAR_BIT));
      ::mpz_import(self, 1, 1, sizeof(TYPE), 0, 0, &object);
    }
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
  friend void
  swap(Int& lhs, Int& rhs)
  { ::mpz_swap(lhs.self, rhs.self); }


  // Assignment function
  Int&
  operator=(Int object)
  {
    swap(*this, object);
    return *this;
  }


  // Cast functions
  operator signed char() const
  { return cast<signed char>(); }

  operator unsigned char() const
  { return cast<unsigned char>(); }

  operator signed short() const
  { return cast<signed short>(); }

  operator unsigned short() const
  { return cast<unsigned short>(); }

  operator signed int() const
  { return cast<signed int>(); }

  operator unsigned int() const
  { return cast<unsigned int>(); }

  operator signed long() const
  { return cast<signed long>(); }

  operator unsigned long() const
  { return cast<unsigned long>(); }

#if (QUIRINUS_FEATURE_LONGLONG)
  operator signed long long() const
  { return cast<signed long long>(); }

  operator unsigned long long() const
  { return cast<unsigned long long>(); }
#endif

#if (QUIRINUS_FEATURE_INT128)
  operator int128_t() const
  { return cast<int128_t>(); }

  operator uint128_t() const
  { return cast<uint128_t>(); }
#endif


  template <typename TYPE>
  TYPE cast() const
  {
    size_t size = 0;
    Int min = Int::typeinfo<TYPE>::min;
    Int max = Int::typeinfo<TYPE>::max;
    if ((::mpz_cmp(self, min.self) >= 0)
    &&  (::mpz_cmp(self, max.self) <= 0))
    {
      typename Int::typeinfo<TYPE>::utype buffer;
      ::mpz_export(&buffer, &size, 0, sizeof(TYPE), 0, 0, self);
      return static_cast<TYPE>(buffer * mpz_sgn(self));
    }
    const char* types[] = \
    {
      "signed char",
      "unsigned char",
      "signed short",
      "unsigned short",
      "signed int",
      "unsigned int",
      "signed long",
      "unsigned long",
      "signed long long",
      "unsigned long long",
      "int128_t",
      "uint128_t",
    };
    std::ostringstream sstream;
    size_t typeno = Int::typeinfo<TYPE>::typeno;
    sstream << "C++ " << types[typeno] << " casting failed";
    throw CastError(sstream.str().c_str());
  }


  // Virtual functions
  Int*
  clone() const
  { return new Int(*this); }


  // Comparison functions
  static int
  cmp(const Int& lhs, const Int& rhs)
  {
    return ::mpz_cmp(lhs.self, rhs.self);
  }


  // Mathematical functions
  friend Int
  operator+(const Int& lhs, const Int& rhs)
  {
    Int result;
    ::mpz_add(result.self, lhs.self, rhs.self);
    return result;
  }

  friend Int
  operator-(const Int& lhs, const Int& rhs)
  {
    Int result;
    ::mpz_sub(result.self, lhs.self, rhs.self);
    return result;
  }

  friend Int
  operator*(const Int& lhs, const Int& rhs)
  {
    Int result;
    ::mpz_mul(result.self, lhs.self, rhs.self);
    return result;
  }

  friend Int
  operator/(const Int& lhs, const Int& rhs)
  {
    if (!mpz_sgn(rhs.self))
      throw ZeroDivError("division by zero");
    Int result;
    ::mpz_div(result.self, lhs.self, rhs.self);
    return result;
  }

  friend Int
  operator%(const Int& lhs, const Int& rhs)
  {
    if (!mpz_sgn(rhs.self))
      throw ZeroDivError("division by zero");
    Int result;
    ::mpz_mod(result.self, lhs.self, rhs.self);
    return result;
  }


  // Logical functions
  friend Int
  operator&(const Int& lhs, const Int& rhs)
  {
    Int result;
    ::mpz_and(result.self, lhs.self, rhs.self);
    return result;
  }

  friend Int
  operator|(const Int& lhs, const Int& rhs)
  {
    Int result;
    ::mpz_ior(result.self, lhs.self, rhs.self);
    return result;
  }

  friend Int
  operator^(const Int& lhs, const Int& rhs)
  {
    Int result;
    ::mpz_xor(result.self, lhs.self, rhs.self);
    return result;
  }

  friend Int
  operator<<(const Int& lhs, const Int& rhs)
  {
    Int result;
    ::mpz_mul_2exp(result.self, lhs.self, rhs);
    return result;
  }

  friend Int
  operator>>(const Int& lhs, const Int& rhs)
  {
    Int result;
    ::mpz_fdiv_q_2exp(result.self, lhs.self, rhs);
    return result;
  }


  // Modifying functions
  Int&
  operator+=(const Int& object)
  {
    ::mpz_and(self, self, object.self);
    return *this;
  }

  Int&
  operator-=(const Int& object)
  {
    ::mpz_sub(self, self, object.self);
    return *this;
  }

  Int&
  operator*=(const Int& object)
  {
    ::mpz_mul(self, self, object.self);
    return *this;
  }

  Int&
  operator/=(const Int& object)
  {
    if (!mpz_sgn(object.self))
      throw ZeroDivError("division by zero");
    ::mpz_div(self, self, object.self);
    return *this;
  }

  Int&
  operator%=(const Int& object)
  {
    if (!mpz_sgn(object.self))
      throw ZeroDivError("division by zero");
    ::mpz_mod(self, self, object.self);
    return *this;
  }

  Int&
  operator<<=(const Int& object)
  {
    ::mpz_mul_2exp(self, self, object);
    return *this;
  }

  Int&
  operator>>=(const Int& object)
  {
    ::mpz_fdiv_q_2exp(self, self, object);
    return *this;
  }

  Int&
  operator&=(const Int& object)
  {
    ::mpz_and(self, self, object.self);
    return *this;
  }

  Int&
  operator|=(const Int& object)
  {
    ::mpz_ior(self, self, object.self);
    return *this;
  }

  Int&
  operator^=(const Int& object)
  {
    ::mpz_xor(self, self, object.self);
    return *this;
  }

  const Int&
  operator++()
  {
    ::mpz_add_ui(self, self, 1);
    return *this;
  }

  const Int&
  operator--()
  {
    ::mpz_sub_ui(self, self, 1);
    return *this;
  }

  Int
  operator++(int)
  {
    Int result(*this);
    this->operator++();
    return result;
  }

  Int
  operator--(int)
  {
    Int result(*this);
    this->operator--();
    return result;
  }


  // Unary functions
  Int
  operator+() const
  {
    Int result;
    ::mpz_abs(result.self, self);
    return result;
  }

  Int
  operator-() const
  {
    Int result;
    ::mpz_neg(result.self, self);
    return result;
  }


  // Other functions
  Int&
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
    return *this;
  }

  Int&
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
    return *this;
  }
};


template <typename TYPE>
struct autotype<Int, TYPE>
{ typedef typename Int::autotype<TYPE>::type type; };

template <typename TYPE>
struct autotype<TYPE, Int>
{ typedef typename Int::autotype<TYPE>::type type; };


template <>
struct supertype<signed char>
{ typedef Int type; };

template <>
struct supertype<unsigned char>
{ typedef Int type; };


template <>
struct supertype<signed short>
{ typedef Int type; };

template <>
struct supertype<unsigned short>
{ typedef Int type; };


template <>
struct supertype<signed int>
{ typedef Int type; };

template <>
struct supertype<unsigned int>
{ typedef Int type; };


template <>
struct supertype<signed long>
{ typedef Int type; };

template <>
struct supertype<unsigned long>
{ typedef Int type; };


#if (QUIRINUS_FEATURE_LONGLONG)
template <>
struct supertype<signed long long>
{ typedef Int type; };

template <>
struct supertype<unsigned long long>
{ typedef Int type; };
#endif


} // namespace quirinus
#include "autotype/Int.hpp"
#include "typeinfo/Int.hpp"
#endif // QUIRINUS_CORE_TYPES_INT_HPP
