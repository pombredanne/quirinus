/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_AUTOTYPE_FLOAT_HPP
#define QUIRINUS_AUTOTYPE_FLOAT_HPP
namespace quirinus {


// bool type
template <>
struct autotype<Float, bool>
{ typedef Float type; };

template <>
struct autotype<bool, Float>
{ typedef Float type; };


// signed char type
template <>
struct autotype<Float, signed char>
{ typedef Float type; };

template <>
struct autotype<signed char, Float>
{ typedef Float type; };


// unsigned char type
template <>
struct autotype<Float, unsigned char>
{ typedef Float type; };

template <>
struct autotype<unsigned char, Float>
{ typedef Float type; };


// signed short type
template <>
struct autotype<Float, signed short>
{ typedef Float type; };

template <>
struct autotype<signed short, Float>
{ typedef Float type; };


// unsigned short type
template <>
struct autotype<Float, unsigned short>
{ typedef Float type; };

template <>
struct autotype<unsigned short, Float>
{ typedef Float type; };


// signed int type
template <>
struct autotype<Float, signed int>
{ typedef Float type; };

template <>
struct autotype<signed int, Float>
{ typedef Float type; };


// unsigned int type
template <>
struct autotype<Float, unsigned int>
{ typedef Float type; };

template <>
struct autotype<unsigned int, Float>
{ typedef Float type; };


// signed long type
template <>
struct autotype<Float, signed long>
{ typedef Float type; };

template <>
struct autotype<signed long, Float>
{ typedef Float type; };


// unsigned long type
template <>
struct autotype<Float, unsigned long>
{ typedef Float type; };

template <>
struct autotype<unsigned long, Float>
{ typedef Float type; };


#if (QUIRINUS_FEATURE_LONGLONG)
// signed long long type
template <>
struct autotype<Float, signed long long>
{ typedef Float type; };

template <>
struct autotype<signed long long, Float>
{ typedef Float type; };


// unsigned long long type
template <>
struct autotype<Float, unsigned long long>
{ typedef Float type; };

template <>
struct autotype<unsigned long long, Float>
{ typedef Float type; };
#endif // QUIRINUS_FEATURE_LONGLONG


// float type
template <>
struct autotype<Float, float>
{ typedef Float type; };

template <>
struct autotype<float, Float>
{ typedef Float type; };


// double type
template <>
struct autotype<Float, double>
{ typedef Float type; };

template <>
struct autotype<double, Float>
{ typedef Float type; };


// mpz_t type
template <>
struct autotype<Float, mpz_t>
{ typedef Float type; };

template <>
struct autotype<mpz_t, Float>
{ typedef Float type; };


// mpfr_t type
template <>
struct autotype<Float, mpfr_t>
{ typedef Float type; };

template <>
struct autotype<mpfr_t, Float>
{ typedef Float type; };


// Int type
template <>
struct autotype<Float, Int>
{ typedef Float type; };

template <>
struct autotype<Int, Float>
{ typedef Float type; };


} // namespace quirinus
#endif // QUIRINUS_AUTOTYPE_FLOAT_HPP
