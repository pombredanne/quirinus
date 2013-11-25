/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_TYPES_SUPERTYPE_HPP
#define QUIRINUS_CORE_TYPES_SUPERTYPE_HPP
namespace quirinus {


template <>
struct supertype<bool>
{ typedef Bool type; };


template <>
struct supertype<signed char>
{ typedef Int type; };

template <>
struct supertype<unsigned char>
{ typedef Int type; };


template <>
struct supertype<signed short>
{ typedef Int type; };

template <>
struct supertype<unsigned short>
{ typedef Int type; };


template <>
struct supertype<signed int>
{ typedef Int type; };

template <>
struct supertype<unsigned int>
{ typedef Int type; };


template <>
struct supertype<signed long>
{ typedef Int type; };

template <>
struct supertype<unsigned long>
{ typedef Int type; };


#if (QUIRINUS_FEATURE_LONGLONG)
template <>
struct supertype<signed long long>
{ typedef Int type; };

template <>
struct supertype<unsigned long long>
{ typedef Int type; };
#endif


} // namespace quirinus
#endif // QUIRINUS_CORE_TYPES_SUPERTYPE_HPP
