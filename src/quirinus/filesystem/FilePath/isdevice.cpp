/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

namespace quirinus {
namespace filesystem {


Bool
FilePath::isdevice() const
{
#if !defined(QUIRINUS_PLATFORM_WINDOWS)
  int state;
  struct stat buffer;
  state = ::stat64(*this, &buffer);
  return ((state == 0) && ((buffer.st_mode & S_IFMT) == S_IFCHR));
#else
  uint32_t attributes;
  if (self.mode == Path::API::WINWIDE)
    attributes = ::GetFileAttributesW(*this);
  else
    attributes = ::GetFileAttributesA(*this);
  if (attributes != INVALID_FILE_ATTRIBUTES)
    return (attributes & FILE_ATTRIBUTE_DEVICE);
  return false;
#endif
}


} // namespace filesystem
} // namespace quirinus
