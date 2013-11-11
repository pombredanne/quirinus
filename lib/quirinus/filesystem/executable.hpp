/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_FILESYSTEM_EXECUTABLE_HPP
#define QUIRINUS_FILESYSTEM_EXECUTABLE_HPP
#include "FilePath.hpp"
namespace quirinus {
namespace filesystem {


inline FilePath
executable()
{
#if defined(QUIRINUS_SYSTEM_LINUX) \
|| defined(QUIRINUS_SYSTEM_NETBSD) \
|| defined(QUIRINUS_SYSTEM_DRAGONFLY)
  int32_t size = 32;
  int32_t nsize = 0;
  char* buffer = NULL;

  while (true)
  {
    buffer = new char[size];
    ::memset(buffer, 0, size);
    #if defined(QUIRINUS_SYSTEM_LINUX)
    nsize = ::readlink("/proc/self/exe", buffer, size);
    #elif defined(QUIRINUS_SYSTEM_NETBSD) \
    || defined(QUIRINUS_SYSTEM_DRAGONFLY)
    nsize = ::readlink("/proc/curproc/file", buffer, size);
    #endif
    if ((nsize < 0) && (errno != ERANGE))
    {
      delete[] buffer;
      throw SystemError(errno);
    }
    if (nsize < size)
      break;
    delete[] buffer;
    size *= 1.5;
  }


#elif defined(QUIRINUS_SYSTEM_FREEBSD)
  int state;
  size_t size = 16;
  char* buffer = NULL;
  int names = new int[4];
  for (size_t i = 0; i < size; ++i)
    buffer[i] = 0;
  names[0] = CTL_KERN;
  names[1] = KERN_PROC;
  names[2] = KERN_PROC_PATHNAME;
  names[3] = -1;
  while (true)
  {
    buffer = new char[size];
    ::memset(buffer, 0, size);
    state = ::sysctl(names, 4, buffer, &size, NULL, 0);
    if ((nsize < 0) && (errno != ERANGE))
    {
      delete[] buffer;
      throw SystemError(errno);
    }
    delete[] buffer;
    size *= 1.5;
  }


#elif defined(QUIRINUS_SYSTEM_WINDOWS)
  size_t size = 16;
  size_t nsize = 0;
  wchar_t* buffer = NULL;
  while (true)
  {
    buffer = new wchar_t[size];
    for (size_t i = 0; i < size; ++i)
      buffer[i] = 0;
    nsize = ::GetModuleFileNameW(NULL, buffer, size);
    if (nsize < size)
      break;
    delete[] buffer;
    size *= 1.5;
  }
#endif


#if defined(QUIRINUS_SYSTEM_WINDOWS)
  Unicode result(buffer);
#else
  struct quirinus::sysinfo sys;
  quirinus::sysinfo(&sys);
  Bytes encoding = sys.encoding.filesystem;
  Unicode result = codecs::decode(buffer, encoding);
#endif

  // Free memory.
  delete[] buffer;
  return result;
}


} // namespace filesystem
} // namespace quirinus
#endif // QUIRINUS_FILESYSTEM_EXECUTABLE_HPP
