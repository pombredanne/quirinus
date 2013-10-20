/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_SYSTEM_ENCODING_STDERR_HPP
#define QUIRINUS_CORE_SYSTEM_ENCODING_STDERR_HPP
#include "encoding_stdout.hpp"
namespace quirinus {


inline Bytes
encoding_stderr()
{
  return encoding_stdout();
}


} // namespace quirinus
#endif // QUIRINUS_CORE_SYSTEM_ENCODING_STDERR_HPP
