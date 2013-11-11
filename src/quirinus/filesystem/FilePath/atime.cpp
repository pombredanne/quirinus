/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

namespace quirinus {
namespace filesystem {


Int
FilePath::atime() const
{
#if (QUIRINUS_FEATURE_POSIX)
  int state = 0;
  struct stat64 buffer;
  state = ::stat64(*this, &buffer);
  if (state)
    throw SystemError(errno);
  return static_cast<time_t>(buffer.st_atime);
#else
  DWORD state = 0;
  HANDLE handle;
  FILETIME wintime;
  uint32_t access = GENERIC_READ;
  uint32_t disposition = OPEN_EXISTING;
  handle = ::CreateFileW(*this, access, 0, NULL, disposition, 0, NULL);
  state = ((!handle) ? ::GetLastError() : 0);
  if (!state)
    throw SystemError(state);
  ::GetFileTime(handle, NULL, &wintime, NULL);
  ::CloseHandle(handle);
#if (UINT64_MAX == ULONG_MAX)
  uint64_t ms2ns = 10000000UL;
  uint64_t diff = 116444736000000000UL;
#else
  uint64_t ms2ns = 10000000ULL;
  uint64_t diff = 116444736000000000ULL;
#endif
  uint64_t hpart = wintime.dwHighDateTime;
  uint64_t lpart = wintime.dwLowDateTime;
  uint64_t time = ((hpart << 32) | lpart);
  return static_cast<time_t>((time - diff) / ms2ns);
#endif
}


} // namespace filesystem
} // namespace quirinus
