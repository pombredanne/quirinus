/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

namespace quirinus {


Bool::Bool(const Object& object)
{
  Bool stack(object.cast_bool());
  swap(*this, stack);
}


Bytes
Bool::repr() const
{ return ((!!self) ? "true" : "false"); }


Bool
Bool::cast_bool() const
{ return (!!self); }


Int
Bool::cast_int() const
{ return ((!!self) ? 1 : 0); }


Float
Bool::cast_float() const
{ return ((!!self) ? 1.0 : 0.0); }


Bytes
Bool::cast_bytes() const
{ return this->repr(); }


Unicode
Bool::cast_unicode() const
{ return this->repr(); }


} // namespace quirinus
