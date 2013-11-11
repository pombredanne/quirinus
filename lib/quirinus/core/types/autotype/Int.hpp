/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_AUTOTYPE_INT_HPP
#define QUIRINUS_AUTOTYPE_INT_HPP
namespace quirinus {


template <>
struct Int::autotype<bool>
{ typedef Int type; };


template <>
struct Int::autotype<signed char>
{ typedef Int type; };

template <>
struct Int::autotype<unsigned char>
{ typedef Int type; };


template <>
struct Int::autotype<signed short>
{ typedef Int type; };

template <>
struct Int::autotype<unsigned short>
{ typedef Int type; };


template <>
struct Int::autotype<signed int>
{ typedef Int type; };

template <>
struct Int::autotype<unsigned int>
{ typedef Int type; };


template <>
struct Int::autotype<signed long>
{ typedef Int type; };

template <>
struct Int::autotype<unsigned long>
{ typedef Int type; };



#if (QUIRINUS_FEATURE_LONGLONG)
template <>
struct Int::autotype<signed long long>
{ typedef Int type; };

template <>
struct Int::autotype<unsigned long long>
{ typedef Int type; };
#endif


template <>
struct Int::autotype<float>
{ typedef Float type; };


template <>
struct Int::autotype<double>
{ typedef Float type; };


} // namespace quirinus
#endif // QUIRINUS_AUTOTYPE_INT_HPP
