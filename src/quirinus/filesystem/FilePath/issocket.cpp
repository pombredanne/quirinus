/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

namespace quirinus {
namespace filesystem {


Bool
FilePath::issocket() const
{
#if !defined(QUIRINUS_PLATFORM_WINDOWS)
  int state;
  struct stat buffer;
  state = ::stat64(*this, &buffer);
  return ((state == 0) && ((buffer.st_mode & S_IFMT) == S_IFSOCK));
#else
  return false;
#endif
}


} // namespace filesystem
} // namespace quirinus
