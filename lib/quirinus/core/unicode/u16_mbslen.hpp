/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_UNICODE_U16_MBSLEN_HPP
#define QUIRINUS_CORE_UNICODE_U16_MBSLEN_HPP
namespace quirinus {


inline int
u16_mbslen(const bytechar* iter,
           const size_t& enclen,
           size_t& declen,
           size_t& offset)
{
  int state;
  const bytechar* tail;
  tail = (iter + enclen);
  union codeconv {
    widechar code;
    bytechar bytes[2];
  } codeconv = {0x0000};

  // Reset variables.
  offset = 0;
  declen = 0;
  state = UNICODE_STATE_SUCCESS;

  // Check null pointer.
  if (iter == NULL)
    return UNICODE_STATE_NULLPTR;

  // Check length quickly.
  if (declen % 2)
    return UNICODE_STATE_TRUNCATED;

  // Byte order check.
  union {
    uint32_t code;
    uint8_t bytes[4];
  } endian = {0x01020304};
  int8_t byteorder_data;
  int8_t byteorder_system;
  byteorder_system = ((endian.bytes[0] != 0x01) ? -1 : +1);
  if (((iter[0] == 0xFE) && (iter[1] == 0xFF))
  ||  ((iter[0] == 0xFF) && (iter[1] == 0xFE)))
  {
    byteorder_data = ((*iter == 0xFF) ? -1 : +1);
    iter += 2;
  }
  else
    byteorder_data = byteorder_system;
  const byte* table;
  const byte btable[2] = {0, 1};
  const byte ltable[2] = {1, 0};
  table = ((byteorder_data == byteorder_system) ? ltable : btable);

  // Calculate length.
  byte count;
  while (iter < tail)
  {
    codeconv.bytes[0] = iter[table[0]];
    codeconv.bytes[1] = iter[table[1]];

    // Normal code point.
    if ((codeconv.code & 0xF800) != 0xD800)
      count = 2;

    // Surrogate pair.
    else if ((codeconv.code & 0x0400) == 0)
    {
      codeconv.bytes[0] = iter[(table[0] + 2)];
      codeconv.bytes[1] = iter[(table[1] + 2)];
      if ((codeconv.code & 0xFC00) != 0xDC00)
        state = UNICODE_STATE_SURROGATE;
      count = 4;
    }

    // Isolated surrogate.
    else
      state = UNICODE_STATE_ISOLATED;

    // Truncated sequence.
    if ((iter + count) > tail)
      state = UNICODE_STATE_TRUNCATED;

    // Check current state.
    if (state != UNICODE_STATE_SUCCESS)
    {
      declen = 0;
      return state;
    }

    // Adjust variables.
    offset += count;
    iter += count;
    ++declen;
  }
  return UNICODE_STATE_SUCCESS;
}


} // namespace quirinus
#endif // QUIRINUS_CORE_UNICODE_U16_MBSLEN_HPP
