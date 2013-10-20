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
  int state = 0;
  struct stat64 buffer;
  state = ::stat64(*this, &buffer);
  return (state == 0);
#else
  DWORD attributes = 0;
  if (self_api == API::WINANSI)
    attributes = ::GetFileAttributesA(*this);
  else if (self_api == API::WINWIDE)
    attributes = ::GetFileAttributesW(*this);
  return (attributes != INVALID_FILE_ATTRIBUTES);
#endif
}


} // namespace filesystem
} // namespace quirinus
