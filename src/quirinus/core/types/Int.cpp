/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

namespace quirinus {


Int::Int(const Object& object)
{
  Int stack(object.cast_int());
  swap(*this, stack);
}


Bytes
Int::repr(const Int& base) const
{
  char* pointer = NULL;
  void (*mp_free_str)(void *, size_t);
  ::mp_get_memory_functions(NULL, NULL, &mp_free_str);
  pointer = ::mpz_get_str(NULL, base, self);
  Bytes result(pointer);
  size_t len = strlen(pointer);
  mp_free_str(pointer, ++len);
  return result;
}


Bytes
Int::repr() const
{ return this->repr(10); }


Bool
Int::cast_bool() const
{ return (mpz_sgn(self) != 0); }


Int
Int::cast_int() const
{ return *this; }


Float
Int::cast_float() const
{
  Float result;
  ::mpfr_set_z(result.self, self, MPFR_RNDA);
  return result;
}


Bytes
Int::cast_bytes() const
{ return this->repr(10); }


Unicode
Int::cast_unicode() const
{ return this->repr(10); }


} // namespace quirinus
