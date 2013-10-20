/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

namespace quirinus {

Bytes
Object::repr() const
{
  throw AttributeError("representation not implemented");
}


Bool
Object::cast_bool() const
{
  throw AttributeError("Bool casting not implemented");
}


Int
Object::cast_int() const
{
  throw AttributeError("Int casting not implemented");
}


Float
Object::cast_float() const
{
  throw AttributeError("Float casting not implemented");
}


Bytes
Object::cast_bytes() const
{
  throw AttributeError("Bytes casting not implemented");
}


Unicode
Object::cast_unicode() const
{
  throw AttributeError("Unicode casting not implemented");
}


Object::operator bool() const
{
  return this->cast_bool();
}


Object::operator signed char() const
{
  return this->cast_int();
}


Object::operator unsigned char() const
{
  return this->cast_int();
}


Object::operator signed short() const
{
  return this->cast_int();
}


Object::operator unsigned short() const
{
  return this->cast_int();
}


Object::operator signed int() const
{
  return this->cast_int();
}


Object::operator unsigned int() const
{
  return this->cast_int();
}


Object::operator signed long() const
{
  return this->cast_int();
}


Object::operator unsigned long() const
{
  return this->cast_int();
}


#if (QUIRINUS_FEATURE_LONGLONG)
Object::operator signed long long() const
{
  return this->cast_int();
}


Object::operator unsigned long long() const
{
  return this->cast_int();
}
#endif


Object::operator float() const
{
  return this->cast_float();
}


Object::operator double() const
{
  return this->cast_float();
}


Object::operator const char*() const
{
  return this->cast_bytes();
}


Object::operator const unicode*() const
{
  return this->cast_unicode();
}

} // namespace quirinus
