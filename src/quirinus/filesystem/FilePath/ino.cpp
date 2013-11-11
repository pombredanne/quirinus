/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

namespace quirinus {
namespace filesystem {


Int
FilePath::ino() const
{
#if (QUIRINUS_FEATURE_POSIX)
  int state = 0;
  struct stat64 buffer;
  state = ::stat64(*this, &buffer);
  if (state)
    throw SystemError(errno);
  return buffer.st_ino;
#else
  return 0;
#endif
}


} // namespace filesystem
} // namespace quirinus
