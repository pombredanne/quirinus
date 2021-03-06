/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_SUPERTYPE_HPP
#define QUIRINUS_CORE_SUPERTYPE_HPP
namespace quirinus {


template <typename TYPE>
struct supertype
{
  static const bool value = false;
  typedef TYPE type;
};


} // namespace quirinus
#endif // QUIRINUS_CORE_SUPERTYPE_HPP
