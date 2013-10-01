/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

namespace quirinus {
namespace filesystem {


Bool
FilePath::isfile() const
{
#if (QUIRINUS_FEATURE_POSIX)
  int state;
  struct stat64 buffer;
  state = ::stat64(*this, &buffer);
  return ((state == 0) && ((buffer.st_mode & S_IFMT) == S_IFREG));
#else
  uint32_t attributes;
  if (self.mode == Path::API::WINANSI)
    attributes = ::GetFileAttributesA(*this);
  else if (self.mode == Path::API::WINWIDE)
    attributes = ::GetFileAttributesW(*this);
  if (attributes != INVALID_FILE_ATTRIBUTES)
    return (!(attributes & FILE_ATTRIBUTE_DIRECTORY));
  return false;
#endif
}


} // namespace quirinus
} // namespace filesystem
