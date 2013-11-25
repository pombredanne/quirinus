/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_TYPES_INT_HPP
#define QUIRINUS_CORE_TYPES_INT_HPP
#include "Bool.hpp"
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
private:
  template <typename TYPE>
  Int(const TYPE& object,
      const int& state)
  {
    const int state_unsigned = 0;
    const int state_negative = -1;
    const int state_positive = +1;
    if ((state != state_unsigned)
    &&  (state != state_negative)
    &&  (state != state_positive))
      throw ValueError("integer type must be 0, +1 or -1");
    ::mpz_init2(self, (sizeof(TYPE) * CHAR_BIT));
    if (state != state_unsigned)
    {
      ::mpz_import(self, 1, 1, sizeof(TYPE), 0, 0, &object);
      if (state == state_negative)
        ::mpz_neg(self, self);
    }
    else
      ::mpz_import(self, 1, 1, sizeof(TYPE), 0, 0, &object);
  }

  template <typename TYPE>
  TYPE cast(const char* type = NULL) const
  {
    size_t size = 0;
    Int min = std::numeric_limits<TYPE>::min();
    Int max = std::numeric_limits<TYPE>::max();
    const bool check_min = (::mpz_cmp(self, min.self) >= 0);
    const bool check_max = (::mpz_cmp(self, max.self) <= 0);
    if (check_min && check_max)
    {
      TYPE buffer = 0;
      ::mpz_export(&buffer, &size, 0, sizeof(TYPE), 0, 0, self);
      return (buffer * mpz_sgn(self));
    }
    char* repr_min = NULL;
    char* repr_max = NULL;
    size_t repr_size = 0;
    std::ostringstream sstream;
    void (*mp_free_str)(void *, size_t);
    ::mp_get_memory_functions(NULL, NULL, &mp_free_str);
    repr_min = ::mpz_get_str(NULL, 10, min.self);
    repr_max = ::mpz_get_str(NULL, 10, max.self);
    if (!repr_min || !repr_max)
      throw MemoryError();
    size = (sizeof(TYPE) * CHAR_BIT);
    if (!type)
      sstream << "C++ casting failed: ";
    else
    {
      sstream << "C++ " << type << " (" << size << "-bit)";
      sstream << " casting failed: ";
    }
    if (!check_min)
      sstream << "value < " << repr_min;
    else
      sstream << "value > " << repr_max;
    repr_size = nullstrlen(repr_min);
    mp_free_str(repr_min, ++repr_size);
    repr_size = nullstrlen(repr_max);
    mp_free_str(repr_max, ++repr_size);
    throw CastError(sstream.str().c_str());
  }
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
  Int(Int&& object)
  { swap(*this, object); }
#endif

  Int(const bool& object)
  {
    ::mpz_init2(self, 1);
    ::mpz_set_ui(self, object);
  }

  Int(const signed char& object)
  {
    int state = ((object < 0) ? -1 : +1);
    Int stack(&object, state);
    swap(*this, stack);
  }

  Int(const unsigned char& object)
  {
    Int stack(&object, 0);
    swap(*this, stack);
  }

  Int(const signed short& object)
  {
    int state = ((object < 0) ? -1 : +1);
    Int stack(&object, state);
    swap(*this, stack);
  }

  Int(const unsigned short& object)
  {
    Int stack(&object, 0);
    swap(*this, stack);
  }

  Int(const signed int& object)
  {
    int state = ((object < 0) ? -1 : +1);
    Int stack(&object, state);
    swap(*this, stack);
  }

  Int(const unsigned int& object)
  {
    Int stack(&object, 0);
    swap(*this, stack);
  }

  Int(const signed long& object)
  {
    int state = ((object < 0) ? -1 : +1);
    Int stack(&object, state);
    swap(*this, stack);
  }

  Int(const unsigned long& object)
  {
    Int stack(&object, 0);
    swap(*this, stack);
  }

#if (QUIRINUS_FEATURE_LONGLONG)
  Int(const signed long long& object)
  {
    int state = ((object < 0) ? -1 : +1);
    Int stack(&object, state);
    swap(*this, stack);
  }

  Int(const unsigned long long& object)
  {
    Int stack(&object, 0);
    swap(*this, stack);
  }
#endif

#if (QUIRINUS_FEATURE_INT128)
  Int(const int128_t& object)
  {
    int state = ((object < 0) ? -1 : +1);
    Int stack(&object, state);
    swap(*this, stack);
  }

  Int(const uint128_t& object)
  {
    Int stack(&object, 0);
    swap(*this, stack);
  }
#endif

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
  { return cast<signed char>("signed char"); }

  operator unsigned char() const
  { return cast<unsigned char>("unsigned char"); }

  operator signed short() const
  { return cast<signed short>("signed short"); }

  operator unsigned short() const
  { return cast<unsigned short>("unsigned short"); }

  operator signed int() const
  { return cast<signed int>("signed int"); }

  operator unsigned int() const
  { return cast<unsigned int>("unsigned int"); }

  operator signed long() const
  { return cast<signed long>("signed long"); }

  operator unsigned long() const
  { return cast<unsigned long>("unsigned long"); }

#if (QUIRINUS_FEATURE_LONGLONG)
  operator signed long long() const
  { return cast<signed long long>("signed long long"); }

  operator unsigned long long() const
  { return cast<unsigned long long>("unsigned long long"); }
#endif

#if (QUIRINUS_FEATURE_INT128)
  operator int128_t() const
  { return cast<int128_t>("int128_t"); }

  operator uint128_t() const
  { return cast<uint128_t>("uint128_t"); }
#endif


  // Virtual functions
  Int*
  clone() const
  { return new Int(*this); }


  // Comparison functions
  friend Bool
  operator<(const Int& lhs, const Int& rhs)
  { return (::mpz_cmp(lhs.self, rhs.self) < 0); }

    template <typename TYPE>
    friend Bool
    operator<(const Int& lhs, const TYPE& rhs)
    { return (lhs < static_cast<typename supertype<TYPE>::type>(rhs)); }

    template <typename TYPE>
    friend Bool
    operator<(const TYPE& lhs, const Int& rhs)
    { return (static_cast<typename supertype<TYPE>::type>(lhs) < rhs); }

  friend Bool
  operator<=(const Int& lhs, const Int& rhs)
  { return (::mpz_cmp(lhs.self, rhs.self) <= 0); }

    template <typename TYPE>
    friend Bool
    operator<=(const Int& lhs, const TYPE& rhs)
    { return (lhs <= static_cast<typename supertype<TYPE>::type>(rhs)); }

    template <typename TYPE>
    friend Bool
    operator<=(const TYPE& lhs, const Int& rhs)
    { return (static_cast<typename supertype<TYPE>::type>(lhs) <= rhs); }

  friend Bool
  operator==(const Int& lhs, const Int& rhs)
  { return (::mpz_cmp(lhs.self, rhs.self) == 0); }

    template <typename TYPE>
    friend Bool
    operator==(const Int& lhs, const TYPE& rhs)
    { return (lhs == static_cast<typename supertype<TYPE>::type>(rhs)); }

    template <typename TYPE>
    friend Bool
    operator==(const TYPE& lhs, const Int& rhs)
    { return (static_cast<typename supertype<TYPE>::type>(lhs) == rhs); }

  friend Bool
  operator!=(const Int& lhs, const Int& rhs)
  { return (::mpz_cmp(lhs.self, rhs.self) != 0); }

    template <typename TYPE>
    friend Bool
    operator!=(const Int& lhs, const TYPE& rhs)
    { return (lhs != static_cast<typename supertype<TYPE>::type>(rhs)); }

    template <typename TYPE>
    friend Bool
    operator!=(const TYPE& lhs, const Int& rhs)
    { return (static_cast<typename supertype<TYPE>::type>(lhs) != rhs); }

  friend Bool
  operator>=(const Int& lhs, const Int& rhs)
  { return (::mpz_cmp(lhs.self, rhs.self) >= 0); }

    template <typename TYPE>
    friend Bool
    operator>=(const Int& lhs, const TYPE& rhs)
    { return (lhs >= static_cast<typename supertype<TYPE>::type>(rhs)); }

    template <typename TYPE>
    friend Bool
    operator>=(const TYPE& lhs, const Int& rhs)
    { return (static_cast<typename supertype<TYPE>::type>(lhs) >= rhs); }

  friend Bool
  operator>(const Int& lhs, const Int& rhs)
  { return (::mpz_cmp(lhs.self, rhs.self) > 0); }

    template <typename TYPE>
    friend Bool
    operator>(const Int& lhs, const TYPE& rhs)
    { return (lhs > static_cast<typename supertype<TYPE>::type>(rhs)); }

    template <typename TYPE>
    friend Bool
    operator>(const TYPE& lhs, const Int& rhs)
    { return (static_cast<typename supertype<TYPE>::type>(lhs) > rhs); }


  // Mathematical functions
  friend Int
  operator+(const Int& lhs, const Int& rhs)
  {
    Int result;
    ::mpz_add(result.self, lhs.self, rhs.self);
    return result;
  }

    template <typename TYPE>
    friend Int
    operator+(const Int& lhs, const TYPE& rhs)
    { return (lhs + static_cast<typename supertype<TYPE>::type>(rhs)); }

    template <typename TYPE>
    friend Int
    operator+(const TYPE& lhs, const Int& rhs)
    { return (static_cast<typename supertype<TYPE>::type>(lhs) + rhs); }

  friend Int
  operator-(const Int& lhs, const Int& rhs)
  {
    Int result;
    ::mpz_sub(result.self, lhs.self, rhs.self);
    return result;
  }

    template <typename TYPE>
    friend Int
    operator-(const Int& lhs, const TYPE& rhs)
    { return (lhs - static_cast<typename supertype<TYPE>::type>(rhs)); }

    template <typename TYPE>
    friend Int
    operator-(const TYPE& lhs, const Int& rhs)
    { return (static_cast<typename supertype<TYPE>::type>(lhs) - rhs); }

  friend Int
  operator*(const Int& lhs, const Int& rhs)
  {
    Int result;
    ::mpz_mul(result.self, lhs.self, rhs.self);
    return result;
  }

    template <typename TYPE>
    friend Int
    operator*(const Int& lhs, const TYPE& rhs)
    { return (lhs * static_cast<typename supertype<TYPE>::type>(rhs)); }

    template <typename TYPE>
    friend Int
    operator*(const TYPE& lhs, const Int& rhs)
    { return (static_cast<typename supertype<TYPE>::type>(lhs) * rhs); }

  friend Int
  operator%(const Int& lhs, const Int& rhs)
  {
    if (!mpz_sgn(rhs.self))
      throw ZeroDivError();
    Int result;
    ::mpz_mod(result.self, lhs.self, rhs.self);
    return result;
  }

    template <typename TYPE>
    friend Int
    operator%(const Int& lhs, const TYPE& rhs)
    { return (lhs % static_cast<typename supertype<TYPE>::type>(rhs)); }

    template <typename TYPE>
    friend Int
    operator%(const TYPE& lhs, const Int& rhs)
    { return (static_cast<typename supertype<TYPE>::type>(lhs) % rhs); }


  // Logical functions
  friend Int
  operator&(const Int& lhs, const Int& rhs)
  {
    Int result;
    ::mpz_and(result.self, lhs.self, rhs.self);
    return result;
  }

    template <typename TYPE>
    friend Int
    operator&(const Int& lhs, const TYPE& rhs)
    { return (lhs & static_cast<typename supertype<TYPE>::type>(rhs)); }

    template <typename TYPE>
    friend Int
    operator&(const TYPE& lhs, const Int& rhs)
    { return (static_cast<typename supertype<TYPE>::type>(lhs) & rhs); }

  friend Int
  operator|(const Int& lhs, const Int& rhs)
  {
    Int result;
    ::mpz_ior(result.self, lhs.self, rhs.self);
    return result;
  }

    template <typename TYPE>
    friend Int
    operator|(const Int& lhs, const TYPE& rhs)
    { return (lhs | static_cast<typename supertype<TYPE>::type>(rhs)); }

    template <typename TYPE>
    friend Int
    operator|(const TYPE& lhs, const Int& rhs)
    { return (static_cast<typename supertype<TYPE>::type>(lhs) | rhs); }

  friend Int
  operator^(const Int& lhs, const Int& rhs)
  {
    Int result;
    ::mpz_xor(result.self, lhs.self, rhs.self);
    return result;
  }

    template <typename TYPE>
    friend Int
    operator^(const Int& lhs, const TYPE& rhs)
    { return (lhs ^ static_cast<typename supertype<TYPE>::type>(rhs)); }

    template <typename TYPE>
    friend Int
    operator^(const TYPE& lhs, const Int& rhs)
    { return (static_cast<typename supertype<TYPE>::type>(lhs) ^ rhs); }

  friend Int
  operator<<(const Int& lhs, const Int& rhs)
  {
    Int result;
    ::mpz_mul_2exp(result.self, lhs.self, rhs);
    return result;
  }

    template <typename TYPE>
    friend Int
    operator<<(const Int& lhs, const TYPE& rhs)
    { return (lhs << static_cast<typename supertype<TYPE>::type>(rhs)); }

    template <typename TYPE>
    friend Int
    operator<<(const TYPE& lhs, const Int& rhs)
    { return (static_cast<typename supertype<TYPE>::type>(lhs) << rhs); }

  friend Int
  operator>>(const Int& lhs, const Int& rhs)
  {
    Int result;
    ::mpz_fdiv_q_2exp(result.self, lhs.self, rhs);
    return result;
  }

    template <typename TYPE>
    friend Int
    operator>>(const Int& lhs, const TYPE& rhs)
    { return (lhs >> static_cast<typename supertype<TYPE>::type>(rhs)); }

    template <typename TYPE>
    friend Int
    operator>>(const TYPE& lhs, const Int& rhs)
    { return (static_cast<typename supertype<TYPE>::type>(lhs) >> rhs); }


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


} // namespace quirinus
#endif // QUIRINUS_CORE_TYPES_INT_HPP
