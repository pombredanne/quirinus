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
  Float(const Float&& object)
  { swap(*this, object); }
#endif

  /*
  Float(const Object& object)
  {
    Float operand = object.cast_float();
    ::mpz_init2(self, ::mpfr_get_prec(operand.self));
    ::mpz_set(self, operand.self);
  }
  */

  Float(const bool& object)
  {
    ::mpfr_init(self);
    if (!!object)
    {
      Int operand(object);
      ::mpfr_set_z(self, operand.self, MPFR_RNDA);
    }
    else
      ::mpfr_set_zero(self, 1);
  }

  Float(const signed char& object)
  {
    ::mpfr_init(self);
    Int operand(object);
    ::mpfr_set_z(self, operand.self, MPFR_RNDA);
  }

  Float(const unsigned char& object)
  {
    ::mpfr_init(self);
    Int operand(object);
    ::mpfr_set_z(self, operand.self, MPFR_RNDA);
  }

  Float(const signed short& object)
  {
    ::mpfr_init(self);
    Int operand(object);
    ::mpfr_set_z(self, operand.self, MPFR_RNDA);
  }

  Float(const unsigned short& object)
  {
    ::mpfr_init(self);
    Int operand(object);
    ::mpfr_set_z(self, operand.self, MPFR_RNDA);
  }

  Float(const signed int& object)
  {
    ::mpfr_init(self);
    Int operand(object);
    ::mpfr_set_z(self, operand.self, MPFR_RNDA);
  }

  Float(const unsigned int& object)
  {
    ::mpfr_init(self);
    Int operand(object);
    ::mpfr_set_z(self, operand.self, MPFR_RNDA);
  }

  Float(const signed long& object)
  {
    ::mpfr_init(self);
    Int operand(object);
    ::mpfr_set_z(self, operand.self, MPFR_RNDA);
  }

  Float(const unsigned long& object)
  {
    ::mpfr_init(self);
    Int operand(object);
    ::mpfr_set_z(self, operand.self, MPFR_RNDA);
  }

#if (QUIRINUS_FEATURE_LONGLONG)
  Float(const signed long long& object)
  {
    ::mpfr_init(self);
    Int operand(object);
    ::mpfr_set_z(self, operand.self, MPFR_RNDA);
  }

  Float(const unsigned long long& object)
  {
    ::mpfr_init(self);
    Int operand(object);
    ::mpfr_set_z(self, operand.self, MPFR_RNDA);
  }
#endif // !QUIRINUS_FEATURE_LONGLONG

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
  inline friend void
  swap(Float& lhs, Float& rhs)
  { ::mpfr_swap(lhs.self, rhs.self); }


  // Assignment function
  inline Float&
  operator=(Float object)
  {
    swap(*this, object);
    return *this;
  }


  // Virtual functions
  inline Float*
  clone() const
  { return new Float(*this); }


  // Comparison functions
  static inline int
  cmp(const Float& lhs, const Float& rhs)
  { return ::mpfr_cmp(lhs.self, rhs.self); }


  // Mathematical functions
  friend inline Float
  operator+(const Float& lhs, const Float& rhs)
  {
    Float result;
    ::mpfr_add(result.self, lhs.self, rhs.self, MPFR_RNDA);
    return result;
  }

  friend inline Float
  operator-(const Float& lhs, const Float& rhs)
  {
    Float result;
    ::mpfr_sub(result.self, lhs.self, rhs.self, MPFR_RNDA);
    return result;
  }

  friend inline Float
  operator*(const Float& lhs, const Float& rhs)
  {
    Float result;
    ::mpfr_mul(result.self, lhs.self, rhs.self, MPFR_RNDA);
    return result;
  }

  friend inline Float
  operator/(const Float& lhs, const Float& rhs)
  {
    Float result;
    ::mpfr_div(result.self, lhs.self, rhs.self, MPFR_RNDA);
    return result;
  }

  friend inline Float
  operator%(const Float& lhs, const Float& rhs)
  {
    Float result;
    ::mpfr_div(result.self, lhs.self, rhs.self, MPFR_RNDA);
    ::mpfr_trunc(result.self, result.self);
    ::mpfr_mul(result.self, result.self, rhs.self, MPFR_RNDA);
    ::mpfr_sub(result.self, lhs.self, result.self, MPFR_RNDA);
    return result;
  }
};


} // namespace quirinus
#endif // QUIRINUS_CORE_TYPES_FLOAT_HPP
