/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_STATIC_AUTOTYPE_HPP
#define QUIRINUS_CORE_STATIC_AUTOTYPE_HPP
namespace quirinus {


template <typename LTYPE, typename RTYPE>
struct autotype { /* type deduction */ };


} // namespace quirinus
#include "autotype/Int.hpp"
#include "autotype/Float.hpp"
#include "autotype/Bytes.hpp"
#include "autotype/Unicode.hpp"
#endif // QUIRINUS_CORE_AUTOTYPE_HPP
