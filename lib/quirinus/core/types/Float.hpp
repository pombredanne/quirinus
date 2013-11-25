/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_TYPES_FLOAT_HPP
#define QUIRINUS_CORE_TYPES_FLOAT_HPP
namespace quirinus {


class Float: public Object
{
private:
  mpfr_t self;
public:
  friend class Bool;
  friend class Int;
  friend class Bytes;
  friend class Unicode;
  Float(const Object&);
template <typename TYPE>
  struct typeinfo
  {
    typedef uint8_t type;
    static const bool sign = false;
    static const bool integer = false;
    static const uint8_t min = SCHAR_MIN;
    static const uint8_t max = SCHAR_MAX;
    static const size_t typeno = SIZE_MAX;
  };
public:
  Bytes repr() const;
  Bool cast_bool() const;
  Int cast_int() const;
  Float cast_float() const;
  Bytes cast_bytes() const;
  Unicode cast_unicode() const;
  Bytes repr(const Int&) const;
public:
  ~Float()
  { ::mpfr_clear(self); }

  Float()
  {
    ::mpfr_init(self);
    ::mpfr_set_zero(self, 1);
  }

  Float(const Float& object)
  {
    ::mpfr_init2(self, mpfr_get_prec(object.self));
    ::mpfr_set(self, object.self, MPFR_RNDA);
  }

#if (QUIRINUS_FEATURE_CXX11)
  Float(Float&& object)
  { swap(*this, object); }
#endif

  Float(const float& object)
  {
    ::mpfr_init(self);
    ::mpfr_set_flt(self, object, MPFR_RNDA);
  }

  Float(const double& object)
  {
    ::mpfr_init(self);
    ::mpfr_set_d(self, object, MPFR_RNDA);
  }

  Float(const mpz_t& object)
  {
    ::mpfr_init(self);
    ::mpfr_set_z(self, object, MPFR_RNDA);
  }

  Float(const mpfr_t& object)
  {
    ::mpfr_init2(self, mpfr_get_prec(object));
    ::mpfr_set(self, object, MPFR_RNDA);
  }


  // Swap function
  friend void
  swap(Float& lhs, Float& rhs)
  { ::mpfr_swap(lhs.self, rhs.self); }


  // Assignment function
  Float&
  operator=(Float object)
  {
    swap(*this, object);
    return *this;
  }


  // Virtual functions
  Float*
  clone() const
  { return new Float(*this); }


  // Comparison functions
  friend Bool
  operator<(const Float& lhs, const Float& rhs)
  { return (::mpfr_cmp(lhs.self, rhs.self) < 0); }

    friend Bool
    operator<(const Float& lhs, const Int& rhs)
    { return (lhs < static_cast<Float>(rhs)); }

    friend Bool
    operator<(const Int& lhs, const Float& rhs)
    { return (static_cast<Float>(lhs) < rhs); }

    template <typename TYPE>
    friend Bool
    operator<(const Float& lhs, const TYPE& rhs)
    { return (lhs < static_cast<typename supertype<TYPE>::type>(rhs)); }

    template <typename TYPE>
    friend Bool
    operator<(const TYPE& lhs, const Float& rhs)
    { return (static_cast<typename supertype<TYPE>::type>(lhs) < rhs); }

  friend Bool
  operator<=(const Float& lhs, const Float& rhs)
  { return (::mpfr_cmp(lhs.self, rhs.self) <= 0); }

    friend Bool
    operator<=(const Float& lhs, const Int& rhs)
    { return (lhs <= static_cast<Float>(rhs)); }

    friend Bool
    operator<=(const Int& lhs, const Float& rhs)
    { return (static_cast<Float>(lhs) <= rhs); }

    template <typename TYPE>
    friend Bool
    operator<=(const Float& lhs, const TYPE& rhs)
    { return (lhs <= static_cast<typename supertype<TYPE>::type>(rhs)); }

    template <typename TYPE>
    friend Bool
    operator<=(const TYPE& lhs, const Float& rhs)
    { return (static_cast<typename supertype<TYPE>::type>(lhs) <= rhs); }

  friend Bool
  operator==(const Float& lhs, const Float& rhs)
  { return (::mpfr_cmp(lhs.self, rhs.self) == 0); }

    friend Bool
    operator==(const Float& lhs, const Int& rhs)
    { return (lhs == static_cast<Float>(rhs)); }

    friend Bool
    operator==(const Int& lhs, const Float& rhs)
    { return (static_cast<Float>(lhs) == rhs); }

    template <typename TYPE>
    friend Bool
    operator==(const Float& lhs, const TYPE& rhs)
    { return (lhs == static_cast<typename supertype<TYPE>::type>(rhs)); }

    template <typename TYPE>
    friend Bool
    operator==(const TYPE& lhs, const Float& rhs)
    { return (static_cast<typename supertype<TYPE>::type>(lhs) == rhs); }

  friend Bool
  operator!=(const Float& lhs, const Float& rhs)
  { return (::mpfr_cmp(lhs.self, rhs.self) != 0); }

    friend Bool
    operator!=(const Float& lhs, const Int& rhs)
    { return (lhs != static_cast<Float>(rhs)); }

    friend Bool
    operator!=(const Int& lhs, const Float& rhs)
    { return (static_cast<Float>(lhs) != rhs); }

    template <typename TYPE>
    friend Bool
    operator!=(const Float& lhs, const TYPE& rhs)
    { return (lhs != static_cast<typename supertype<TYPE>::type>(rhs)); }

    template <typename TYPE>
    friend Bool
    operator!=(const TYPE& lhs, const Float& rhs)
    { return (static_cast<typename supertype<TYPE>::type>(lhs) != rhs); }

  friend Bool
  operator>=(const Float& lhs, const Float& rhs)
  { return (::mpfr_cmp(lhs.self, rhs.self) >= 0); }

    friend Bool
    operator>=(const Float& lhs, const Int& rhs)
    { return (lhs >= static_cast<Float>(rhs)); }

    friend Bool
    operator>=(const Int& lhs, const Float& rhs)
    { return (static_cast<Float>(lhs) >= rhs); }

    template <typename TYPE>
    friend Bool
    operator>=(const Float& lhs, const TYPE& rhs)
    { return (lhs >= static_cast<typename supertype<TYPE>::type>(rhs)); }

    template <typename TYPE>
    friend Bool
    operator>=(const TYPE& lhs, const Float& rhs)
    { return (static_cast<typename supertype<TYPE>::type>(lhs) >= rhs); }

  friend Bool
  operator>(const Float& lhs, const Float& rhs)
  { return (::mpfr_cmp(lhs.self, rhs.self) > 0); }

    friend Bool
    operator>(const Float& lhs, const Int& rhs)
    { return (lhs > static_cast<Float>(rhs)); }

    friend Bool
    operator>(const Int& lhs, const Float& rhs)
    { return (static_cast<Float>(lhs) > rhs); }

    template <typename TYPE>
    friend Bool
    operator>(const Float& lhs, const TYPE& rhs)
    { return (lhs > static_cast<typename supertype<TYPE>::type>(rhs)); }

    template <typename TYPE>
    friend Bool
    operator>(const TYPE& lhs, const Float& rhs)
    { return (static_cast<typename supertype<TYPE>::type>(lhs) > rhs); }


  // Mathematical functions
  friend Float
  operator+(const Float& lhs, const Float& rhs)
  {
    Float result;
    ::mpfr_add(result.self, lhs.self, rhs.self, MPFR_RNDA);
    return result;
  }

    friend Float
    operator+(const Float& lhs, const Int& rhs)
    { return (lhs + static_cast<Float>(rhs)); }

    friend Float
    operator+(const Int& lhs, const Float& rhs)
    { return (static_cast<Float>(lhs) + rhs); }

    template <typename TYPE>
    friend Float
    operator+(const Float& lhs, const TYPE& rhs)
    { return (lhs + static_cast<typename supertype<TYPE>::type>(rhs)); }

    template <typename TYPE>
    friend Float
    operator+(const TYPE& lhs, const Float& rhs)
    { return (static_cast<typename supertype<TYPE>::type>(lhs) + rhs); }

  friend Float
  operator-(const Float& lhs, const Float& rhs)
  {
    Float result;
    ::mpfr_sub(result.self, lhs.self, rhs.self, MPFR_RNDA);
    return result;
  }

    friend Float
    operator-(const Float& lhs, const Int& rhs)
    { return (lhs - static_cast<Float>(rhs)); }

    friend Float
    operator-(const Int& lhs, const Float& rhs)
    { return (static_cast<Float>(lhs) - rhs); }

    template <typename TYPE>
    friend Float
    operator-(const Float& lhs, const TYPE& rhs)
    { return (lhs - static_cast<typename supertype<TYPE>::type>(rhs)); }

    template <typename TYPE>
    friend Float
    operator-(const TYPE& lhs, const Float& rhs)
    { return (static_cast<typename supertype<TYPE>::type>(lhs) - rhs); }

  friend Float
  operator*(const Float& lhs, const Float& rhs)
  {
    Float result;
    ::mpfr_mul(result.self, lhs.self, rhs.self, MPFR_RNDA);
    return result;
  }

    friend Float
    operator*(const Float& lhs, const Int& rhs)
    { return (lhs * static_cast<Float>(rhs)); }

    friend Float
    operator*(const Int& lhs, const Float& rhs)
    { return (static_cast<Float>(lhs) * rhs); }

    template <typename TYPE>
    friend Float
    operator*(const Float& lhs, const TYPE& rhs)
    { return (lhs * static_cast<typename supertype<TYPE>::type>(rhs)); }

    template <typename TYPE>
    friend Float
    operator*(const TYPE& lhs, const Float& rhs)
    { return (static_cast<typename supertype<TYPE>::type>(lhs) * rhs); }

  friend Float
  operator/(const Float& lhs, const Float& rhs)
  {
    Float result;
    ::mpfr_div(result.self, lhs.self, rhs.self, MPFR_RNDA);
    return result;
  }

    friend Float
    operator/(const Float& lhs, const Int& rhs)
    { return (lhs / static_cast<Float>(rhs)); }

    friend Float
    operator/(const Int& lhs, const Float& rhs)
    { return (static_cast<Float>(lhs) / rhs); }

    template <typename TYPE>
    friend Float
    operator/(const Float& lhs, const TYPE& rhs)
    { return (lhs / static_cast<typename supertype<TYPE>::type>(rhs)); }

    template <typename TYPE>
    friend Float
    operator/(const TYPE& lhs, const Float& rhs)
    { return (static_cast<typename supertype<TYPE>::type>(lhs) / rhs); }

    template <typename TYPE>
    friend Float
    operator/(const Int& lhs, const TYPE& rhs)
    { return (static_cast<Float>(lhs) / static_cast<Float>(rhs)); }

    template <typename TYPE>
    friend Float
    operator/(const TYPE& lhs, const Int& rhs)
    { return (static_cast<Float>(lhs) / static_cast<Float>(rhs)); }

  friend Float
  operator%(const Float& lhs, const Float& rhs)
  {
    Float result;
    ::mpfr_div(result.self, lhs.self, rhs.self, MPFR_RNDA);
    ::mpfr_trunc(result.self, result.self);
    ::mpfr_mul(result.self, result.self, rhs.self, MPFR_RNDA);
    ::mpfr_sub(result.self, lhs.self, result.self, MPFR_RNDA);
    return result;
  }

    friend Float
    operator%(const Float& lhs, const Int& rhs)
    { return (lhs % static_cast<Int>(rhs)); }

    friend Float
    operator%(const Int& lhs, const Float& rhs)
    { return (static_cast<Float>(lhs) % rhs); }

    template <typename TYPE>
    friend Float
    operator%(const Float& lhs, const TYPE& rhs)
    { return (lhs % static_cast<typename supertype<TYPE>::type>(rhs)); }

    template <typename TYPE>
    friend Float
    operator%(const TYPE& lhs, const Float& rhs)
    { return (static_cast<typename supertype<TYPE>::type>(lhs) % rhs); }
};


template <>
struct supertype<float>
{ typedef Float type; };


template <>
struct supertype<double>
{ typedef Float type; };


#if (QUIRINUS_FEATURE_LONGDOUBLE)
template <>
struct supertype<long double>
{ typedef Float type; };
#endif


} // namespace quirinus
#endif // QUIRINUS_CORE_TYPES_FLOAT_HPP
