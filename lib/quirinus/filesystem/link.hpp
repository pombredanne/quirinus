/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_FILESYSTEM_LINK_HPP
#define QUIRINUS_FILESYSTEM_LINK_HPP
#include "FilePath.hpp"
namespace quirinus {
namespace filesystem {


inline void
link(const FilePath& src, const FilePath& dest)
{
#if (QUIRINUS_FEATURE_POSIX)
  int32_t state;
  state = ::link(src, dest);
  state = (!state) ? 0 : errno;
#else
  uint32_t state;
  typedef int (*HardLinkA) (
    LPCSTR src,
    LPCSTR dest
  ); // WinANSI hard link
  typedef int (*HardLinkW) (
    LPCWSTR src,
    LPCWSTR dest
  ); // WinWide hard link
  HMODULE kernel = ::GetModuleHandle("kernel32.dll");
  state = (!kernel) ? ::GetLastError() : 0;
  if (state)
    throw SystemError(state);
  HardLinkA link_ansi = (HardLinkA) \
    ::GetProcAddress(kernel, "CreateHardLinkA");
  HardLinkW link_wide = (HardLinkW) \
    ::GetProcAddress(kernel, "CreateHardLinkW");
  if (!link_ansi || !link_wide)
    throw SupportError("hard links are not supported");
  if (src.api() != dest.api())
    state = link_ansi(src, dest);
  else if (src.api() == filesystem::API::WINWIDE)
    state = link_wide(src, dest);
  else
    state = link_ansi(src, dest);
  state = (!state) ? ::GetLastError() : 0;
#endif
  if (state)
    throw SystemError(state);
}


} // namespace filesystem
} // namespace quirinus
#endif // QUIRINUS_FILESYSTEM_LINK_HPP
