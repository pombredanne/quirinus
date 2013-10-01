/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_STATIC_AUTOTYPE_INT_HPP
#define QUIRINUS_CORE_STATIC_AUTOTYPE_INT_HPP
namespace quirinus {


template <>
struct autotype<Int, Int>
{ typedef Int type; };


template <>
struct autotype<Int, bool>
{ typedef Int type; };

template <>
struct autotype<bool, Int>
{ typedef Int type; };


template <>
struct autotype<Int, signed char>
{ typedef Int type; };

template <>
struct autotype<signed char, Int>
{ typedef Int type; };


template <>
struct autotype<Int, unsigned char>
{ typedef Int type; };

template <>
struct autotype<unsigned char, Int>
{ typedef Int type; };


template <>
struct autotype<Int, signed short>
{ typedef Int type; };

template <>
struct autotype<signed short, Int>
{ typedef Int type; };


template <>
struct autotype<Int, unsigned short>
{ typedef Int type; };

template <>
struct autotype<unsigned short, Int>
{ typedef Int type; };


template <>
struct autotype<Int, signed int>
{ typedef Int type; };

template <>
struct autotype<signed int, Int>
{ typedef Int type; };


template <>
struct autotype<Int, unsigned int>
{ typedef Int type; };

template <>
struct autotype<unsigned int, Int>
{ typedef Int type; };


template <>
struct autotype<Int, signed long>
{ typedef Int type; };

template <>
struct autotype<signed long, Int>
{ typedef Int type; };


template <>
struct autotype<Int, unsigned long>
{ typedef Int type; };

template <>
struct autotype<unsigned long, Int>
{ typedef Int type; };


#if (QUIRINUS_FEATURE_LONGLONG)
template <>
struct autotype<Int, signed long long>
{ typedef Int type; };

template <>
struct autotype<signed long long, Int>
{ typedef Int type; };


template <>
struct autotype<Int, unsigned long long>
{ typedef Int type; };

template <>
struct autotype<unsigned long long, Int>
{ typedef Int type; };
#endif // QUIRINUS_FEATURE_LONGLONG


template <>
struct autotype<Int, float>
{ typedef Float type; };

template <>
struct autotype<float, Int>
{ typedef Float type; };


template <>
struct autotype<Int, double>
{ typedef Float type; };

template <>
struct autotype<double, Int>
{ typedef Float type; };


template <>
struct autotype<Int, mpz_t>
{ typedef Float type; };

template <>
struct autotype<mpz_t, Int>
{ typedef Float type; };


template <>
struct autotype<Int, mpfr_t>
{ typedef Float type; };

template <>
struct autotype<mpfr_t, Int>
{ typedef Float type; };


} // namespace quirinus
#endif // QUIRINUS_CORE_STATIC_AUTOTYPE_INT_HPP
