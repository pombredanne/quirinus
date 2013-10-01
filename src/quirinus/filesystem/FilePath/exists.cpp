/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

namespace quirinus {
namespace filesystem {


Bool
FilePath::exists() const
{
#if (QUIRINUS_FEATURE_POSIX)
  int32_t state;
  struct stat64 buffer;
  state = ::stat64(*this, &buffer);
  return (state == 0);
#else
  uint32_t attributes;
  if (self.mode == API::WINANSI)
    attributes = ::GetFileAttributesA(*this);
  else if (self.mode == API::WINWIDE)
    attributes = ::GetFileAttributesW(*this);
  return (attributes != INVALID_FILE_ATTRIBUTES);
#endif
}


} // namespace filesystem
} // namespace quirinus
