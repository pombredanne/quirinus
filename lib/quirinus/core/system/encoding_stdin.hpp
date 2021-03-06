/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_SYSTEM_ENCODING_STDIN_HPP
#define QUIRINUS_CORE_SYSTEM_ENCODING_STDIN_HPP
#include "encoding_locale.hpp"
namespace quirinus {


inline Bytes
encoding_stdin()
{
#if defined(QUIRINUS_PLATFORM_WINDOWS)
  size_t len = 13;
  char* buffer = new char[len];
  ::snprintf(buffer, len, "CP%u", ::GetConsoleCP());
  return Bytes(buffer);
#elif defined(QUIRINUS_PLATFORM_UNIX) \
&& (defined(QUIRINUS_OS_MACOS) ||  defined(QUIRINUS_OS_MACOSX))
  return Bytes("UTF-8");
#elif defined(QUIRINUS_PLATFORM_UNIX) \
|| defined(QUIRINUS_PLATFORM_BSD)
  return encoding_locale();
#else
  return Bytes("US-ASCII");
#endif
}


} // namespace quirinus
#endif // QUIRINUS_CORE_SYSTEM_ENCODING_STDIN_HPP
