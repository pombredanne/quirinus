/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_SYSTEM_PLATFORM_HPP
#define QUIRINUS_CORE_SYSTEM_PLATFORM_HPP
namespace quirinus {


inline Bytes
platform()
{ return Bytes(QUIRINUS_PLATFORM); }


} // namespace quirinus
#endif // QUIRINUS_CORE_SYSTEM_PLATFORM_HPP
