/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

namespace quirinus {
namespace filesystem {


Bool
FilePath::is_link() const
{
#if (QUIRINUS_FEATURE_POSIX)
  int state = 0;
  struct stat64 buffer;
  state = ::stat64(*this, &buffer);
  return ((state == 0) && ((buffer.st_mode & Path::FMT) == Path::LNK));
#else
  return false;
#endif
}


} // namespace filesystem
} // namespace quirinus
