/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#include <quirinus/core.hpp>
namespace quirinus {
namespace {


inline void
sysinfo_datamodel(struct sysinfo* sys)
{
  if ((sizeof(int) == 2)
  ||  (sizeof(long) == 4)
  ||  (sizeof(void*) == 4))
    sys->datamodel = "LP32";

  if ((sizeof(int) == 4)
  ||  (sizeof(long) == 4)
  ||  (sizeof(void*) == 4))
    sys->datamodel = "ILP32";

  if ((sizeof(int) == 4)
  ||  (sizeof(long) == 8)
  ||  (sizeof(void*) == 8))
    sys->datamodel = "LP64";

  if ((sizeof(int) == 8)
  ||  (sizeof(long) == 8)
  ||  (sizeof(void*) == 8))
    sys->datamodel = "ILP64";

  if ((sizeof(int) == 4)
  ||  (sizeof(long) == 4)
  ||  (sizeof(void*) == 8))
    sys->datamodel = "LLP64";
}


} // namespace
} // namespace quirinus
