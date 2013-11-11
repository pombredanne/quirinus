/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

namespace quirinus {
namespace filesystem {


Bool
FilePath::is_device() const
{
#if !defined(QUIRINUS_PLATFORM_WINDOWS)
  int state = 0;
  struct stat64 buffer;
  state = ::stat64(*this, &buffer);
  return ((state == 0) && ((buffer.st_mode & S_IFMT) == S_IFCHR));
#else
  DWORD attributes = 0;
  attributes = ::GetFileAttributesW(*this);
  if (attributes != INVALID_FILE_ATTRIBUTES)
    return (attributes & FILE_ATTRIBUTE_DEVICE);
  return false;
#endif
}


} // namespace filesystem
} // namespace quirinus
