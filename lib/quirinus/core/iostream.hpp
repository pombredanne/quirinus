/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_IOSTREAM_HPP
#define QUIRINUS_CORE_IOSTREAM_HPP
#include "pointers.hpp"
#include "types.hpp"
namespace quirinus {


ocharstream&
operator<<(ocharstream& sstream,
           const NullPointer&);

template<typename TYPE>
ocharstream&
operator<<(ocharstream& sstream,
           const SmartPointer<TYPE>& object);

ocharstream&
operator<<(ocharstream& sstream,
           const Error& object);

ocharstream&
operator<<(ocharstream& sstream,
           const Object& object);


} // namespace quirinus
#endif // QUIRINUS_CORE_IOSTREAM_HPP
