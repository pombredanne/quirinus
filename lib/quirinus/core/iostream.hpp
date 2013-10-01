/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_IOSTREAM_HPP
#define QUIRINUS_CORE_IOSTREAM_HPP
#include "pointers.hpp"
#include "types.hpp"
namespace quirinus {


std::ostream&
operator<<(std::ostream& sstream,
           const NullPointer& object);


template <typename TYPE>
std::ostream&
operator<<(std::ostream& sstream,
           const SmartPointer<TYPE>& object);


std::ostream&
operator<<(std::ostream& sstream,
           const Error& object);


std::ostream&
operator<<(std::ostream& sstream,
           const Object& object);


} // namespace quirinus
#endif // QUIRINUS_CORE_IOSTREAM_HPP
