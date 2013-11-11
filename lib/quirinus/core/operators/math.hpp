/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_OPERATORS_MATH_HPP
#define QUIRINUS_CORE_OPERATORS_MATH_HPP
namespace quirinus {


template <typename LTYPE, typename RTYPE>
inline typename quirinus::autotype<LTYPE, RTYPE>::type
operator+(const LTYPE& lhs, const RTYPE& rhs)
{
  typename quirinus::autotype<LTYPE, RTYPE>::type lop(lhs);
  typename quirinus::autotype<LTYPE, RTYPE>::type rop(rhs);
  return (lop + rop);
}


template <typename LTYPE, typename RTYPE>
inline typename quirinus::autotype<LTYPE, RTYPE>::type
operator-(const LTYPE& lhs, const RTYPE& rhs)
{
  typename quirinus::autotype<LTYPE, RTYPE>::type lop(lhs);
  typename quirinus::autotype<LTYPE, RTYPE>::type rop(rhs);
  return (lop - rop);
}


template <typename LTYPE, typename RTYPE>
inline typename quirinus::autotype<LTYPE, RTYPE>::type
operator*(const LTYPE& lhs, const RTYPE& rhs)
{
  typename quirinus::autotype<LTYPE, RTYPE>::type lop(lhs);
  typename quirinus::autotype<LTYPE, RTYPE>::type rop(rhs);
  return (lop * rop);
}


template <typename LTYPE, typename RTYPE>
inline typename quirinus::autotype<LTYPE, RTYPE>::type
operator/(const LTYPE& lhs, const RTYPE& rhs)
{
  typename quirinus::autotype<LTYPE, RTYPE>::type lop(lhs);
  typename quirinus::autotype<LTYPE, RTYPE>::type rop(rhs);
  return (lop / rop);
}


template <typename LTYPE, typename RTYPE>
inline typename quirinus::autotype<LTYPE, RTYPE>::type
operator%(const LTYPE& lhs, const RTYPE& rhs)
{
  typename quirinus::autotype<LTYPE, RTYPE>::type lop(lhs);
  typename quirinus::autotype<LTYPE, RTYPE>::type rop(rhs);
  return (lop % rop);
}


} // namespace quirinus
#endif // QUIRINUS_CORE_OPERATORS_MATH_HPP
