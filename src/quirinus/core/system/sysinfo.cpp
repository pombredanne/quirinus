/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#include <quirinus/core.hpp>
#include "sysinfo/arch.cpp"
#include "sysinfo/byteorder.cpp"
#include "sysinfo/datamodel.cpp"
#include "sysinfo/encoding.cpp"
#include "sysinfo/library.cpp"
#include "sysinfo/uname.cpp"
namespace quirinus {


void
sysinfo(struct sysinfo* sys)
{
  if (!sys)
    throw ValueError("null pointer access");
  sysinfo_arch(sys);
  sysinfo_byteorder(sys);
  sysinfo_datamodel(sys);
  sysinfo_encoding(sys);
  sysinfo_library(sys);
  sysinfo_uname(sys);
}


} // namespace quirinus
