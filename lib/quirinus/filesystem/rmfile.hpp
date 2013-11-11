/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_FILESYSTEM_RMFILE_HPP
#define QUIRINUS_FILESYSTEM_RMFILE_HPP
#include "FilePath.hpp"
namespace quirinus {
namespace filesystem {


inline void
rmfile(const FilePath& path)
{
#if (QUIRINUS_FEATURE_POSIX)
  int state = 0;
  state = ::unlink(path);
  state = ((!state) ? 0 : errno);
#else
  DWORD state = 0;
  state = ::DeleteFileW(path);
  state = ((!state) ? ::GetLastError() : 0);
#endif
  if (state)
    throw SystemError(state);
}


} // namespace filesystem
} // namespace quirinus
#endif // QUIRINUS_FILESYSTEM_RMFILE_HPP
