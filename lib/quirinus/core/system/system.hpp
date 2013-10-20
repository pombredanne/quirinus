/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_SYSTEM_SYSTEM_HPP
#define QUIRINUS_CORE_SYSTEM_SYSTEM_HPP
namespace quirinus {


inline Bytes
system()
{ return Bytes(QUIRINUS_OS); }


} // namespace quirinus
#endif // QUIRINUS_CORE_SYSTEM_SYSTEM_HPP
