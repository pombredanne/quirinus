/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_SYSTEM_ENCODING_STDERR_HPP
#define QUIRINUS_CORE_SYSTEM_ENCODING_STDERR_HPP
namespace quirinus {
namespace system {


Bytes encoding_stderr()
{
  return system::encoding_stdout();
}


} // namespace system
} // namespace quirinus
#endif // QUIRINUS_CORE_SYSTEM_ENCODING_STDERR_HPP
