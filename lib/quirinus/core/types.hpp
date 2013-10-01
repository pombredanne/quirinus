/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_TYPES_HPP
#define QUIRINUS_CORE_TYPES_HPP
#include "config.hpp"
#include "errors.hpp"
#include "static.hpp"
#include "unicode.hpp"
#include "types/Object.hpp"
#include "types/Bool.hpp"
#include "types/Int.hpp"
#include "types/Float.hpp"
#include "types/Bytes.hpp"
#include "types/Unicode.hpp"
namespace quirinus {


template <typename TYPE>
std::ostream&
operator<<(std::ostream& sstream,
           const Object& object)
{
  sstream << (const char*)(object.repr());
  return sstream;
}


} // namespace quirinus
#endif // QUIRINUS_CORE_TYPES_HPP
