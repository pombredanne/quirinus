/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

namespace quirinus {
namespace filesystem {


Bool
FilePath::isdir() const
{
#if (QUIRINUS_FEATURE_POSIX)
  int state = 0;
  struct stat64 buffer;
  state = ::stat64(*this, &buffer);
  return ((state == 0) && ((buffer.st_mode & S_IFMT) == S_IFDIR));
#else
  DWORD attributes = 0;
  if (self_api == filesystem::API::WINWIDE)
    attributes = ::GetFileAttributesW(*this);
  else
    attributes = ::GetFileAttributesA(*this);
  if (attributes != INVALID_FILE_ATTRIBUTES)
    return (attributes & FILE_ATTRIBUTE_DIRECTORY);
  return false;
#endif
}


} // namespace filesystem
} // namespace quirinus
