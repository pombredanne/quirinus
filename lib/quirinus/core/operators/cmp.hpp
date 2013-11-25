/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_OPERATORS_CMP_HPP
#define QUIRINUS_CORE_OPERATORS_CMP_HPP
namespace quirinus {


template <typename LTYPE, typename RTYPE>
inline int
cmp(const LTYPE& lhs, const RTYPE& rhs)
{
  if (lhs < rhs)
    return -1;
  else if (lhs > rhs)
    return +1;
  return 0;
}


template <typename LTYPE, typename RTYPE>
inline Bool
operator<(const LTYPE& lhs, const RTYPE& rhs)
{ return (quirinus::cmp<LTYPE, RTYPE>(lhs, rhs) < 0); }


template <typename LTYPE, typename RTYPE>
inline Bool
operator<=(const LTYPE& lhs, const RTYPE& rhs)
{ return (quirinus::cmp<LTYPE, RTYPE>(lhs, rhs) <= 0); }


template <typename LTYPE, typename RTYPE>
inline Bool
operator==(const LTYPE& lhs, const RTYPE& rhs)
{ return (quirinus::cmp<LTYPE, RTYPE>(lhs, rhs) == 0); }


template <typename LTYPE, typename RTYPE>
inline Bool
operator!=(const LTYPE& lhs, const RTYPE& rhs)
{ return (quirinus::cmp<LTYPE, RTYPE>(lhs, rhs) != 0); }


template <typename LTYPE, typename RTYPE>
inline Bool
operator>=(const LTYPE& lhs, const RTYPE& rhs)
{ return (quirinus::cmp<LTYPE, RTYPE>(lhs, rhs) >= 0); }


template <typename LTYPE, typename RTYPE>
inline Bool
operator>(const LTYPE& lhs, const RTYPE& rhs)
{ return (quirinus::cmp<LTYPE, RTYPE>(lhs, rhs) > 0); }


} // namespace quirinus
#endif // QUIRINUS_CORE_OPERATORS_CMP_HPP
