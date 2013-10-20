/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#include <quirinus/core.hpp>
namespace quirinus {


ocharstream&
operator<<(ocharstream& sstream,
           const NullPointer&)
{
  sstream << "null";
  return sstream;
}


// SmartPointer
template<typename TYPE>
ocharstream&
operator<<(ocharstream& sstream,
           const SmartPointer<TYPE>& object)
{
  const void* pointer;
  pointer = object.pointer();
  if (!pointer)
    sstream << pointer;
  else
    sstream << "null";
  return sstream;
}


ocharstream&
operator<<(ocharstream& sstream,
           const Error& object)
{
  sstream << object.what();
  return sstream;
}


ocharstream&
operator<<(ocharstream& sstream,
           const Object& object)
{
  Bytes repr = object.repr();
  char* buffer = repr.nullstr();
  sstream << buffer;
  delete[] buffer;
  return sstream;
}


} // namespace quirinus
