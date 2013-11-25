/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#include <quirinus/core.hpp>
namespace quirinus {


int
u16_mbslen(const bytechar* iter,
           const size_t& enclen,
           size_t& declen,
           size_t& offset)
{
  int state = 0;
  const bytechar* tail;
  tail = (iter + enclen);
  union codeconv {
    uint16_t code;
    uint8_t bytes[2];
  } codeconv = {0x0000};

  // Reset variables.
  offset = 0;
  declen = 0;

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
  byte count = 0;
  widechar code = 0;
  while (iter < tail)
  {
    codeconv.bytes[0] = iter[table[0]];
    codeconv.bytes[1] = iter[table[1]];
    code = codeconv.code;
    count = 2;

    // Surrogate pair.
    if ((code >= 0xD800) && (code <= 0xDBFF))
    {
      codeconv.bytes[0] = iter[(table[0] + 2)];
      codeconv.bytes[1] = iter[(table[1] + 2)];
      code = codeconv.code;
      if (!((code >= 0xDC00) && (code <= 0xDFFF)))
        state = UNICODE_STATE_SURROGATE;
      count = 4;
    }

    // Isolated surrogate.
    else if ((code >= 0xDC00) && (code <= 0xDFFF))
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
