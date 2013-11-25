/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

namespace quirinus {


Float::Float(const Object& object)
{
  Float stack(object.cast_float());
  swap(*this, stack);
}


Bytes
Float::repr(const Int& base) const
{
  return "0.0";
  /*
  // Special values.
  if (mpfr_inf_p(self))
  {
    if (mpfr_sgn(self) > 0)
      return Bytes("+Inf");
    else
      return Bytes("-Inf");
  }
  if (mpfr_zero_p(self))
    return Bytes("0.0");
  if (mpfr_nan_p(self))
    return Bytes("NaN");
  
  // Initialize variables.
  mpfr_t epsilon;
  mpfr_t ioperand;
  mpfr_t foperand;
  mpfr_exp_t exp;
  size_t len = 0;
  char* str = NULL;
  Float::prec_type prec;
  Float machine_epsilon;
  prec = ::mpfr_get_prec(self);
  ::mpfr_init2(epsilon, prec);
  ::mpfr_init2(ioperand, prec);
  ::mpfr_init2(foperand, prec);
  ::mpfr_set(foperand, self, MPFR_RNDA);
  machine_epsilon = this->machine_epsilon();
  machine_epsilon.copy(epsilon);
  std::vector<char> stack;

  // Extract integral part.
  ::mpfr_modf(ioperand, foperand, foperand, MPFR_RNDA);
  str = ::mpfr_get_str(NULL, &exp, base, 0, ioperand, MPFR_RNDA);
  len = ((exp < 0) ? static_cast<size_t>(-exp) : static_cast<size_t>(exp));
  for (size_t i = 0; i < len; ++i)
    stack.push_back(str[i]);
  if (exp == 0)
    stack.push_back('0');
  stack.push_back('.');
  ::mpfr_free_str(str);

  // Extract fractional part.
  bool state = true;
  while (true)
  {
    ::mpfr_mul_ui(foperand, foperand, base, MPFR_RNDA);
    ::mpfr_trunc(ioperand, foperand);
    str = ::mpfr_get_str(NULL, &exp, base, 0, ioperand, MPFR_RNDA);
    len = ((exp < 0) ? static_cast<size_t>(-exp) : static_cast<size_t>(exp));
    if (len != 0)
    {
      if (*str == '-')
        stack.push_back(str[1]);
      else
        stack.push_back(*str);
    }
    else
      stack.push_back('0');
    ::mpfr_free_str(str);
    ::mpfr_sub(foperand, foperand, ioperand, MPFR_RNDA);
    
    // Check if zero-equal using machine epsilon.
    // Also check for negative exponent.
    ::mpfr_set_d(ioperand, 0.0, MPFR_RNDA);
    ::mpfr_sub(ioperand, ioperand, epsilon, MPFR_RNDA);
    state &= ::mpfr_cmp(foperand, ioperand);
    ::mpfr_set_d(ioperand, 0.0, MPFR_RNDA);
    ::mpfr_add(ioperand, ioperand, epsilon, MPFR_RNDA);
    state &= ::mpfr_cmp(foperand, ioperand);
    state &= ::mpfr_cmp_d(foperand, 0.0);
    if (!(state))
      break;
  }
  
  // Free memory and return value.
  ::mpfr_clear(epsilon);
  ::mpfr_clear(ioperand);
  ::mpfr_clear(foperand);
  return Bytes(stack.begin(), stack.end());
  */
}


Bytes
Float::repr() const
{ return this->repr(10); }


Bool
Float::cast_bool() const
{ return (mpfr_sgn(self) != 0); }


Int
Float::cast_int() const
{
  Int result;
  ::mpfr_get_z(result.self, self, MPFR_RNDA);
  return result;
}


Float
Float::cast_float() const
{ return *this; }


Bytes
Float::cast_bytes() const
{ return this->repr(10); }


Unicode
Float::cast_unicode() const
{ return this->repr(10); }


} // namespace quirinus
