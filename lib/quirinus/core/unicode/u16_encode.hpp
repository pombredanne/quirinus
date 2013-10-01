/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_UNICODE_U16_ENCODE_HPP
#define QUIRINUS_CORE_UNICODE_U16_ENCODE_HPP
#include "u16_ucslen.hpp"
namespace quirinus {


inline int
u16_encode(const unicode* decptr,
           const size_t& declen,
           bytechar*& encptr,
           size_t& enclen,
           size_t& offset)
{
  int state;
  bytechar* tempptr;
  union codeconv {
    widechar code;
    bytechar bytes[2];
  } codeconv = {0x0000};
  const unicode* iter = decptr;
  const unicode* tail = (iter + declen);

  // Reserve memory.
  state = quirinus::u16_ucslen(decptr, declen, enclen, offset);
  if (!!state)
    return state;
  encptr = tempptr = new bytechar[enclen];

  // Append byteorder mark.
  union endian {
    uint32_t code;
    uint8_t bytes[4];
  } endian = {0x01020304};
  int8_t byteorder = ((endian.bytes[0] != 0x01) ? -1 : +1);
  if (byteorder == -1)
  {
    tempptr[0] = 0xFF;
    tempptr[1] = 0xFE;
  }
  else
  {
    tempptr[0] = 0xFE;
    tempptr[1] = 0xFF;
  }
  tempptr += 2;

  // Encode sequence.
  byte count;
  byte hindex;
  byte lindex;
  unicode code;
  while (iter < tail)
  {
    code = *iter;
    if (code < 0xD800)
      count = 2;
    else if ((code <= 0xFFFF) && (code >= 0xE000))
      count = 2;
    else
      count = 4;
    for (size_t i = 0; i < count; ++iter, tempptr += 2, i += 2)
    {
      codeconv.code = *iter;
      hindex = ((byteorder < 0) ? 1 : 0);
      lindex = ((byteorder < 0) ? 0 : 1);
      tempptr[hindex] = codeconv.bytes[1];
      tempptr[lindex] = codeconv.bytes[0];
    }
  }
  return UNICODE_STATE_SUCCESS;
}


inline int
u16_encode(const unicodestack& dec,
           bytecharstack& enc,
           size_t& offset)
{
  int state;
  size_t enclen = 0;
  bytechar* encptr = NULL;
  size_t declen = dec.size();
  const unicode* decptr = &dec[0];
  state = u16_encode(decptr, declen, encptr, enclen, offset);
  if (state != UNICODE_STATE_SUCCESS)
    return state;
  enc.reserve(enclen);
  for (size_t i = 0; i < enclen; ++i)
    enc.push_back(decptr[i]);
  return UNICODE_STATE_SUCCESS;
}


} // namespace quirinus
#endif // QUIRINUS_CORE_UNICODE_U16_ENCODE_HPP
