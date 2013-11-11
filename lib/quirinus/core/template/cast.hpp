/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_CAST_HPP
#define QUIRINUS_CORE_CAST_HPP
namespace quirinus {


template <typename SRC, typename DEST>
DEST cast(SRC);


template <typename TYPE>
TYPE cast(TYPE object) { return static_cast<TYPE>(object); }


} // namespace quirinus
#endif // QUIRINUS_CORE_CAST_HPP
