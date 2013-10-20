/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_SYSTEM_ENCODING_FILESYSTEM_HPP
#define QUIRINUS_SYSTEM_ENCODING_FILESYSTEM_HPP
#include "encoding_locale.hpp"
namespace quirinus {


inline Bytes
encoding_filesystem()
{
#if defined(QUIRINUS_PLATFORM_WINDOWS)
  return Bytes("UTF-16");
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
#endif // QUIRINUS_SYSTEM_ENCODING_FILESYSTEM_HPP
