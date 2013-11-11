/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#include <quirinus/core.hpp>
namespace quirinus {
namespace {


inline void
sysinfo_arch(struct sysinfo* sys)
{ sys->arch = QUIRINUS_ARCH; }


} // namespace
} // namespace quirinus
