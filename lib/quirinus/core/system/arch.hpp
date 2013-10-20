/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_SYSTEM_ARCH_HPP
#define QUIRINUS_SYSTEM_ARCH_HPP
namespace quirinus {


inline Bytes
arch()
{ return Bytes(QUIRINUS_ARCH); }


} // namespace quirinus
#endif // QUIRINUS_SYSTEM_ARCH_HPP
