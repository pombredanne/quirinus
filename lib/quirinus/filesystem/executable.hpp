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
  Unicode result;

// GNU/Linux
#if defined(QUIRINUS_OS_LINUX)
  int32_t size = 16;
  int32_t nsize = 0;
  char* buffer = NULL;
  while (true)
  {
    buffer = new char[size];
    for (int32_t i = 0; i < size; ++i)
      buffer[i] = 0;
    nsize = ::readlink("/proc/self/exe", buffer, size);
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


// FreeBSD
#elif defined(QUIRINUS_OS_FREEBSD)
  int32_t state;
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
    state = ::sysctl(names, 4, buffer, &size, NULL, 0);
    if ((nsize < 0) && (errno != ERANGE))
    {
      delete[] buffer;
      throw SystemError(errno);
    }
    delete[] buffer;
    size *= 1.5;
  }


// NetBSD / DragonFly
#elif defined(QUIRINUS_OS_NETBSD) \
|| defined(QUIRINUS_OS_DRAGONFLY)
  int32_t size = 16;
  int32_t nsize = 0;
  char* buffer = NULL;
  while (true)
  {
    buffer = new char[size];
    for (int32_t i = 0; i < size; ++i)
      buffer[i] = 0;
    nsize = ::readlink("/proc/curproc/file", buffer, size);
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


// Windows
#elif defined(QUIRINUS_OS_WINDOWS)
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
  result = Unicode(buffer);
#endif

#if !defined(QUIRINUS_OS_WINDOWS)
  Bytes temp(buffer);
  Bytes encoding = encoding_filesystem();
  result = codecs::decode(temp, encoding);
#endif

  // Free memory.
  if (buffer != NULL)
    delete[] buffer;
  return result;
}


} // namespace filesystem
} // namespace quirinus
#endif // QUIRINUS_FILESYSTEM_EXECUTABLE_HPP
