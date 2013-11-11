/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#include <quirinus/core.hpp>
namespace quirinus {
namespace {


inline void
sysinfo_byteorder(struct sysinfo* sys)
{
#if defined(__BYTE_ORDER__) \
&& defined(__ORDER_BIG_ENDIAN__) \
&& defined(__ORDER_LITTLE_ENDIAN__)
  #if (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
    sys->byteorder = +1;
  #else
    sys->byteorder = -1;
  #endif
#else
  union {
    uint32_t code;
    uint8_t bytes[4];
  } endian = {0x00010203};
  sys->byteorder = ((endian.bytes[0]) ? -1 : +1);
#endif
}


} // namespace
} // namespace quirinus
