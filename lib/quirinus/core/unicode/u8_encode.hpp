/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_UNICODE_U8_ENCODE_HPP
#define QUIRINUS_CORE_UNICODE_U8_ENCODE_HPP
#include "u8_ucslen.hpp"
namespace quirinus {


inline int
u8_encode(const unicode* decptr,
          const size_t& declen,
          bytechar*& encptr,
          size_t& enclen,
          size_t& offset)
{
  int state;
  unicode code;
  bytechar* tempptr;
  const unicode* iter;
  const unicode* tail;

  // Reserve memory.
  state = quirinus::u8_ucslen(decptr, declen, enclen, offset);
  if (!!state)
    return state;
  encptr = tempptr = new bytechar[enclen];

  // Decode sequence.
  byte count;
  iter = decptr;
  tail = (decptr + declen);
  while (iter < tail)
  {
    code = *iter;
    if (code < 0x00000080)
      count = 1;
    else if (code < 0x00000800)
      count = 2;
    else if (code < 0x00010000)
      count = 3;
    else
      count = 4;
    switch (count)
    {
      case 4:
        tempptr[3] = 0x80 | (code & 0x3F);
        code = code >> 6;
        code |= 0x10000;
      case 3:
        tempptr[2] = 0x80 | (code & 0x3F);
        code = code >> 6;
        code |= 0x800;
      case 2:
        tempptr[1] = 0x80 | (code & 0x3F);
        code = code >> 6;
        code |= 0xC0;
      case 1:
        *tempptr = code;
    }
    tempptr += count;
    ++iter;
  }
  return UNICODE_STATE_SUCCESS;
}


inline int
u8_encode(const unicodestack& dec,
          bytecharstack& enc,
          size_t& offset)
{
  int state;
  size_t enclen = 0;
  bytechar* encptr = NULL;
  size_t declen = dec.size();
  const unicode* decptr = &dec[0];
  state = u8_encode(decptr, declen, encptr, enclen, offset);
  if (state != UNICODE_STATE_SUCCESS)
    return state;
  enc.reserve(enclen);
  for (size_t i = 0; i < enclen; ++i)
    enc.push_back(decptr[i]);
  return UNICODE_STATE_SUCCESS;
}


} // namespace quirinus
#endif // QUIRINUS_CORE_UNICODE_U8_ENCODE_HPP
