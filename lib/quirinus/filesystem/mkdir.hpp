/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_FILESYSTEM_MKDIR_HPP
#define QUIRINUS_FILESYSTEM_MKDIR_HPP
#include "FilePath.hpp"
namespace quirinus {
namespace filesystem {


inline void
mkdir(const FilePath& path, const Int& mode = 0)
{
#if (QUIRINUS_FEATURE_POSIX)
  int state = 0;
  state = ::mkdir(path, mode);
  state = ((!state) ? 0 : errno);
#else
  (void)(mode);
  DWORD state = 0;
  state = ::CreateDirectoryW(path, NULL);
  state = ((!state) ? ::GetLastError() : 0);
#endif
  if (state)
    throw SystemError(state);
}


} // namespace filesystem
} // namespace quirinus
#endif // QUIRINUS_FILESYSTEM_MKDIR_HPP
