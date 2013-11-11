/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_STRING_U32_DECODE_HPP
#define QUIRINUS_CORE_STRING_U32_DECODE_HPP
#include "u32_mbslen.hpp"
namespace quirinus {


inline int
u32_decode(const bytechar* encptr,
           const size_t& enclen,
           unicode*& decptr,
           size_t& declen,
           size_t& offset)
{
  int state = UNICODE_STATE_SUCCESS;
  unicode* tempptr;
  union codeconv {
    uint32_t code;
    uint8_t bytes[4];
  } codeconv = {0x0000};
  const bytechar* iter = encptr;
  const bytechar* tail = (iter + enclen);

  // Allocate memory.
  state = u32_mbslen(encptr, enclen, declen, offset);
  if (state != UNICODE_STATE_SUCCESS)
    return state;
  decptr = tempptr = new unicode[declen];

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

  // Decode sequence.
  while (iter < tail)
  {
    codeconv.bytes[0] = iter[table[0]];
    codeconv.bytes[1] = iter[table[1]];
    codeconv.bytes[2] = iter[table[2]];
    codeconv.bytes[3] = iter[table[3]];
    *tempptr = codeconv.code;
    iter += 4;
    ++tempptr;
  }
  return UNICODE_STATE_SUCCESS;
}


inline int
u32_decode(const bytecharstack& enc,
           unicodestack& dec,
           size_t& offset)
{
  int state;
  size_t declen = 0;
  unicode* decptr = NULL;
  size_t enclen = enc.size();
  const bytechar* encptr = &enc[0];
  state = u32_decode(encptr, enclen, decptr, declen, offset);
  if (state != UNICODE_STATE_SUCCESS)
    return state;
  dec.reserve(declen);
  for (size_t i = 0; i < declen; ++i)
    dec.push_back(decptr[i]);
  return UNICODE_STATE_SUCCESS;
}


} // namespace quirinus
#endif // QUIRINUS_CORE_STRING_U32_DECODE_HPP
