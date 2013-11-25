/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_ASSERTION_HPP
#define QUIRINUS_CORE_ASSERTION_HPP
namespace quirinus {


#define \
  dynamic_assertion(condition) \
  assert(condition)


template <bool> struct STATIC_ASSERTION;
template <> struct STATIC_ASSERTION<true>{};
#define \
  static_assertion(condition) \
  STATIC_ASSERTION<condition>()


} // namespace quirinus
#endif // QUIRINUS_CORE_ASSERTION_HPP
