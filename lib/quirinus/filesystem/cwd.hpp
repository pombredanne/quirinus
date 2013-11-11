/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_FILESYSTEM_CWD_HPP
#define QUIRINUS_FILESYSTEM_CWD_HPP
#include "FilePath.hpp"
namespace quirinus {
namespace filesystem {


/**
 * @brief Get current working directory.
 */
inline FilePath
cwd()
{
#if (QUIRINUS_FEATURE_POSIX)
  int state = 0;
  size_t size = 32;
  char* buffer = NULL;
  char* xbuffer = NULL;
  while (true)
  {
    buffer = new char[size];
    ::memset(buffer, 0, size);
    xbuffer = ::getcwd(buffer, size);
    if (!xbuffer && (errno != ERANGE))
    {
      delete[] buffer;
      state = static_cast<int>(errno);
      throw SystemError(state);
    }
    if (xbuffer == buffer)
      break;
    delete[] buffer;
    size *= 1.5;
  }
  Bytes stack(buffer);
  delete[] buffer;
  return stack;
#else
  DWORD state = 0;
  size_t size = 32;
  size_t xsize = 0;
  wchar_t* buffer = NULL;
  while (true)
  {
    buffer = new wchar_t[size];
    ::wmemset(buffer, 0, size);
    xsize = ::GetCurrentDirectoryW(size, buffer);
    if (xsize == 0)
    {
      delete[] buffer;
      state = ::GetLastError();
      throw SystemError(state);
    }
    if (xsize < size)
      break;
    delete[] buffer;
    size *= 1.5;
  }
  Unicode stack(buffer);
  delete[] buffer;
  return stack;
#endif
}


/**
 * @brief Set current working directory.
 */
inline void
cwd(const FilePath& dir)
{
#if (QUIRINUS_FEATURE_POSIX)
  int state = 0;
  state = ::chdir(dir);
  state = ((!state) ? 0 : errno);
#else
  DWORD state = 0;
  state = ::SetCurrentDirectoryW(dir);
  state = ((!state) ? ::GetLastError() : 0);
#endif
  if (state)
    throw SystemError(state);
#if (QUIRINUS_FEATURE_POSIX)
  quirinus::env("PWD", dir);
#else
  quirinus::env("CD", dir);
#endif
}



} // namespace filesystem
} // namespace quirinus
#endif // QUIRINUS_FILESYSTEM_CWD_HPP
