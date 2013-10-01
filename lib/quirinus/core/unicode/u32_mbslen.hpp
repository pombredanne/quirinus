/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_UNICODE_U32_MBSLEN_HPP
#define QUIRINUS_CORE_UNICODE_U32_MBSLEN_HPP
namespace quirinus {


inline int
u32_mbslen(const bytechar* iter,
           const size_t& enclen,
           size_t& declen,
           size_t& offset)
{
  int state;
  const bytechar* tail;
  tail = (iter + enclen);
  union codeconv {
    unicode code;
    bytechar bytes[4];
  } codeconv = {0x0000};

  // Reset variables.
  offset = 0;
  declen = 0;
  state = UNICODE_STATE_SUCCESS;

  // Check null pointer.
  if (iter == NULL)
    return UNICODE_STATE_NULLPTR;

  // Check length quickly.
  if (declen % 4)
    return UNICODE_STATE_TRUNCATED;

  // Byte order check.
  union {
    uint32_t code;
    uint8_t bytes[4];
  } endian = {0x01020304};
  int8_t byteorder_data;
  int8_t byteorder_system;
  byteorder_system = ((endian.bytes[0] != 0x01) ? -1 : +1);
  if (((iter[0] == 0x00)&& (iter[1] == 0x00)
      && (iter[2] == 0xFE) && (iter[3] == 0xFF))
  || ((iter[0] == 0xFF)&& (iter[1] == 0xFE)
      && (iter[2] == 0x00) && (iter[3] == 0x00)))
  {
    byteorder_data = ((*iter == 0xFF) ? -1 : +1);
    iter += 4;
  }
  else
    byteorder_data = byteorder_system;
  const byte* table;
  const byte btable[4] = {0, 1, 2, 3};
  const byte ltable[4] = {3, 2, 1, 0};
  table = ((byteorder_data == byteorder_system) ? btable : ltable);

  // Calculate length.
  unicode code;
  while (iter < tail)
  {
    codeconv.bytes[0] = iter[table[0]];
    codeconv.bytes[1] = iter[table[1]];
    codeconv.bytes[2] = iter[table[2]];
    codeconv.bytes[3] = iter[table[3]];
    code = codeconv.code;

    // Illegal code point.
    if (!((code < 0xD800) || ((code >= 0xE000) && (code < 0x110000))))
    // if (!(((code & 0xFFFF800) != 0xD800) && (code <= 0x10FFFF)))
      state = UNICODE_STATE_ILLEGAL;

    // Truncated sequence.
    if ((iter + 4) > tail)
      state = UNICODE_STATE_TRUNCATED;

    // Check current state.
    if (state != UNICODE_STATE_SUCCESS)
    {
      declen = 0;
      return state;
    }

    // Adjust variables.
    offset += 4;
    iter += 4;
    ++declen;
  }
  return UNICODE_STATE_SUCCESS;
}


} // namespace quirinus
#endif // QUIRINUS_CORE_UNICODE_U32_MBSLEN_HPP
