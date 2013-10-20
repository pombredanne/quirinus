/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_SYSTEM_BYTEORDER_HPP
#define QUIRINUS_SYSTEM_BYTEORDER_HPP
namespace quirinus {


inline Int
byteorder()
{
  union {
    uint32_t code;
    uint8_t bytes[4];
  } endian = {0x01020304};
  return ((endian.bytes[0] == 0x01) ? +1 : -1);
}


} // namespace quirinus
#endif // QUIRINUS_SYSTEM_BYTEORDER_HPP
