/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#include <quirinus/core.hpp>
namespace quirinus {


int
u16_decode(const bytechar* encptr,
           const size_t& enclen,
           unicode*& decptr,
           size_t& declen,
           size_t& offset)
{
  int state = 0;
  unicode* tempptr;
  union codeconv {
    uint16_t code;
    uint8_t bytes[2];
  } codeconv = {0x0000};
  const bytechar* iter = encptr;
  const bytechar* tail = (iter + enclen);

  // Allocate memory.
  state = u16_mbslen(encptr, enclen, declen, offset);
  if (state != UNICODE_STATE_SUCCESS)
    return state;
  decptr = tempptr = new unicode[declen];

  // Byte order check.
  union endian {
    uint32_t code;
    uint8_t bytes[4];
  } endian = {0x01020304};
  byte byteorder_data;
  byte byteorder_system;
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
  table = ((byteorder_data == byteorder_system) ? btable : ltable);

  // Decode sequence.
  byte count;
  uint32_t code;
  uint16_t hsurr;
  uint16_t lsurr;
  while (iter < tail)
  {
    codeconv.bytes[0] = iter[table[0]];
    codeconv.bytes[1] = iter[table[1]];
    if ((codeconv.code & 0xF800) != 0xD800)
    {
      code = codeconv.code;
      count = 2;
    }
    else
    {
      hsurr = codeconv.code;
      codeconv.bytes[0] = iter[(table[0] + 2)];
      codeconv.bytes[1] = iter[(table[1] + 2)];
      lsurr = codeconv.code;
      code  = (0xFFFF + 1);
      code += (lsurr - 0xDC00);
      code += ((hsurr - 0xD800) << 10);
      count = 4;
    }
    *tempptr = code;
    iter += count;
    ++tempptr;
  }
  return UNICODE_STATE_SUCCESS;
}


int
u16_decode(const std::vector<bytechar>& enc,
           std::vector<unicode>& dec,
           size_t& offset)
{
  int state;
  size_t declen = 0;
  unicode* decptr = NULL;
  size_t enclen = enc.size();
  const bytechar* encptr = &enc[0];
  state = u16_decode(encptr, enclen, decptr, declen, offset);
  if (state != UNICODE_STATE_SUCCESS)
    return state;
  dec.reserve(declen);
  for (size_t i = 0; i < declen; ++i)
    dec.push_back(decptr[i]);
  return UNICODE_STATE_SUCCESS;
}


} // namespace quirinus
