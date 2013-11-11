/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#include <quirinus/core.hpp>
namespace quirinus {
namespace {


inline void
sysinfo_library(struct sysinfo* sys)
{
  sys->library.author = QUIRINUS_AUTHOR;
  sys->library.license = QUIRINUS_LICENSE;
  sys->library.version_major = QUIRINUS_VERSION_MAJOR;
  sys->library.version_minor = QUIRINUS_VERSION_MINOR;
  sys->library.version_micro = QUIRINUS_VERSION_MICRO;
}


} // namespace
} // namespace quirinus
