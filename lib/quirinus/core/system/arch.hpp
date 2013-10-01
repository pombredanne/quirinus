/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_SYSTEM_ARCH_HPP
#define QUIRINUS_SYSTEM_ARCH_HPP
namespace quirinus {
namespace system {


Bytes arch()
{
  return Bytes(QUIRINUS_ARCH);
}


} // namespace system
} // namespace quirinus
#endif // QUIRINUS_SYSTEM_ARCH_HPP
