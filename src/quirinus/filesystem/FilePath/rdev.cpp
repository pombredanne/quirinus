/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

namespace quirinus {
namespace filesystem {


Int
FilePath::rdev() const
{
#if (QUIRINUS_FEATURE_POSIX)
  int32_t state;
  struct stat64 buffer;
  state = ::stat64(*this, &buffer);
  state = (!state) ? 0 : errno;
  if (!!state)
    throw SystemError(state);
  return buffer.st_rdev;
#else
  return this->dev();
#endif
}


} // namespace filesystem
} // namespace quirinus
