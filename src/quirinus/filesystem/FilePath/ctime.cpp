/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

namespace quirinus {
namespace filesystem {


Int
FilePath::ctime() const
{
#if (QUIRINUS_FEATURE_POSIX)
  int32_t state;
  struct stat64 buffer;
  state = ::stat64(*this, &buffer);
  state = (!state) ? 0 : errno;
  if (!!state)
    throw SystemError(state);
  return static_cast<time_t>(buffer.st_ctime);
#else
  HANDLE handle;
  uint32_t state;
  FILETIME wintime;
  uint32_t access = GENERIC_READ;
  uint32_t disposition = OPEN_EXISTING;
  handle = ::CreateFile(*this, access, 0, NULL, disposition, 0, NULL);
  state = (!handle) ? ::GetLastError() : 0;
  if (!!state)
    throw SystemError(state);
  ::GetFileTime(handle, &wintime, NULL, NULL);
  ::CloseHandle(handle);
  uint64_t ms2ns = 10000000ULL;
  uint64_t diff = 116444736000000000ULL;
  uint32_t hpart = wintime.dwHighDateTime;
  uint32_t lpart = wintime.dwLowDateTime;
  uint64_t time = ((hpart << 32) | lpart);
  return static_cast<time_t>((time - diff) / ms2ns);
#endif
}


} // namespace filesystem
} // namespace quirinus
