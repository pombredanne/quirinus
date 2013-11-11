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
  int state = 0;
  state = ::link(src, dest);
  state = ((!state) ? 0 : errno);
#else
  DWORD state = 0;
  typedef int (*HardLink) (
    LPCWSTR src,
    LPCWSTR dest
  ); // CreateHardLinkW pointer

  HMODULE kernel = ::GetModuleHandle("kernel32.dll");
  state = ((!kernel) ? ::GetLastError() : 0);
  if (state)
    throw SystemError(state);
  HardLink link = (HardLink) \
    ::GetProcAddress(kernel, "CreateHardLinkW");
  if (!link)
    throw SupportError("hard links are not supported");
  state = link(src, dest);
  state = ((!state) ? ::GetLastError() : 0);
#endif
  if (state)
    throw SystemError(state);
}


} // namespace filesystem
} // namespace quirinus
#endif // QUIRINUS_FILESYSTEM_LINK_HPP
