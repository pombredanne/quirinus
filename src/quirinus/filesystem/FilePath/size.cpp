/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

namespace quirinus {
namespace filesystem {


Int
FilePath::size() const
{
#if (QUIRINUS_FEATURE_POSIX)
  int state = 0;
  struct stat64 buffer;
  state = ::stat64(*this, &buffer);
  if (state)
    throw SystemError(errno);
  return buffer.st_size;
#else
  DWORD state = 0;
  DWORD attributes = 0;
  struct __stat64 buffer;
  attributes = ::GetFileAttributesW(*this);
  state = ::_wstat64(*this, &buffer);
  if (attributes == INVALID_FILE_ATTRIBUTES)
    throw SystemError(state);
  return buffer.st_size;
#endif
}


} // namespace filesystem
} // namespace quirinus
