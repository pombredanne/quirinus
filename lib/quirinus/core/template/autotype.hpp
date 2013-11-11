/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_AUTOTYPE_HPP
#define QUIRINUS_CORE_AUTOTYPE_HPP
namespace quirinus {


template <typename LTYPE, typename RTYPE>
struct autotype;


template <typename TYPE>
struct autotype<TYPE, TYPE>
{ typedef TYPE type; };


} // namespace quirinus
#endif // QUIRINUS_CORE_AUTOTYPE_HPP
