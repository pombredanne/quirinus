/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

namespace quirinus {
namespace filesystem {


Int
FilePath::mode() const
{
#if (QUIRINUS_FEATURE_POSIX)
  int32_t state;
  struct stat64 buffer;
  state = ::stat64(*this, &buffer);
  state = (!state) ? 0 : errno;
  if (!!state)
    throw SystemError(state);
  return buffer.st_mode;
#else
  uint32_t state;
  uint32_t attributes;
  struct __stat64 buffer;
  if (self_api == API::WINWIDE)
  {
    attributes = ::GetFileAttributesW(*this);
    state = ::_wstat64(path, &buffer);
  }
  else
  {
    attributes = ::GetFileAttributesA(*this);
    state = ::_stat64(*this, &buffer);
  }
  state |= (attributes == INVALID_FILE_ATTRIBUTES);
  state = (!state) ? ::GetLastError() : 0;
  if (!!state)
    throw SystemError(state);
  buffer.st_mode = 0;
  if ((attributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
    buffer.st_mode += S_IFDIR;
  else
    buffer.st_mode += S_IFREG;
  return buffer.st_mode;
#endif
}


} // namespace filesystem
} // namespace quirinus
