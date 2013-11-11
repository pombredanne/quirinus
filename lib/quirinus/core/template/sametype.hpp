/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_SAMETYPE_HPP
#define QUIRINUS_CORE_SAMETYPE_HPP
namespace quirinus {


template <typename LTYPE, typename RTYPE>
struct sametype
{ static const bool value = false; };


template <typename TYPE>
struct sametype<TYPE, TYPE>
{ static const bool value = true; };


} // namespace quirinus
#endif // QUIRINUS_CORE_SAMETYPE_HPP
