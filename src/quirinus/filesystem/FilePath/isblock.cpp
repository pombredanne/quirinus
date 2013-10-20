/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

namespace quirinus {
namespace filesystem {


Bool
FilePath::isblock() const
{
#if !defined(QUIRINUS_PLATFORM_WINDOWS)
  int state = 0;
  struct stat64 buffer;
  state = ::stat64(*this, &buffer);
  return ((state == 0) && ((buffer.st_mode & S_IFMT) == S_IFBLK));
#else
  return false;
#endif
}


} // namespace filesystem
} // namespace quirinus
