/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#include <quirinus/core.hpp>
namespace quirinus {
namespace {


void
sysinfo_uname(struct sysinfo* sys)
{
  sys->uname.platform = QUIRINUS_PLATFORM;
  sys->uname.system = QUIRINUS_SYSTEM;
#if defined(QUIRINUS_SYSTEM_WINDOWS)
  DWORD state = 0;
  OSVERSIONINFO winver = {sizeof(OSVERSIONINFO)};
  state = ::GetVersionEx(&winver);
  state = ((!state) ? ::GetLastError() : 0);
  if (state)
    throw SystemError(state);
  sys->uname.version_major = winver.dwMajorVersion;
  sys->uname.version_minor = winver.dwMinorVersion;
#endif
}


} // namespace
} // namespace quirinus
