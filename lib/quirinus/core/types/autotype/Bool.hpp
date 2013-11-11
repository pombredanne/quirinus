/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_AUTOTYPE_BOOL_HPP
#define QUIRINUS_AUTOTYPE_BOOL_HPP
namespace quirinus {


// bool type
template <>
struct autotype<Bool, bool>
{ typedef Bool type; };

template <>
struct autotype<bool, Bool>
{ typedef Bool type; };


} 

#endif
