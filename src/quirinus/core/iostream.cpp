/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#include <quirinus/core.hpp>
namespace quirinus {


std::ostream&
operator<<(std::ostream& sstream,
           const NullPointer&)
{
  sstream << "null";
  return sstream;
}


// SmartPointer
template<typename TYPE>
std::ostream&
operator<<(std::ostream& sstream,
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


std::ostream&
operator<<(std::ostream& sstream,
           const Error& object)
{
  sstream << object.what();
  return sstream;
}


std::ostream&
operator<<(std::ostream& sstream,
           const Object& object)
{
  Bytes repr = object.repr();
  char* buffer = repr.nullstr();
  sstream << buffer;
  delete[] buffer;
  return sstream;
}


std::ostream&
operator<<(std::ostream& sstream,
           const Int& object)
{
  sstream << object.repr();
  return sstream;
}


} // namespace quirinus
