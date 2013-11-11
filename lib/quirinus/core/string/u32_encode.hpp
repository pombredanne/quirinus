/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_STRING_U32_ENCODE_HPP
#define QUIRINUS_CORE_STRING_U32_ENCODE_HPP
#include "u32_ucslen.hpp"
namespace quirinus {


inline int
u32_encode(const unicode* decptr,
           const size_t& declen,
           bytechar*& encptr,
           size_t& enclen,
           size_t& offset)
{
  int state = UNICODE_STATE_SUCCESS;
  bytechar* tempptr;
  union codeconv {
    uint32_t code;
    uint8_t bytes[4];
  } codeconv = {0x0000};
  const unicode* iter = decptr;
  const unicode* tail = (iter + declen);

  // Reserve memory.
  state = u32_ucslen(decptr, declen, enclen, offset);
  if (state != UNICODE_STATE_SUCCESS)
    return state;
  encptr = tempptr = new bytechar[enclen];

  // Encode sequence.
  while (iter < tail)
  {
    codeconv.code = *iter;
    tempptr[0] = codeconv.bytes[0];
    tempptr[1] = codeconv.bytes[1];
    tempptr[2] = codeconv.bytes[2];
    tempptr[3] = codeconv.bytes[3];
    tempptr += 4;
    ++iter;
  }
  return UNICODE_STATE_SUCCESS;
}


inline int
u32_encode(const unicodestack& dec,
           bytecharstack& enc,
           size_t& offset)
{
  int state;
  size_t enclen = 0;
  bytechar* encptr = NULL;
  size_t declen = dec.size();
  const unicode* decptr = &dec[0];
  state = u32_encode(decptr, declen, encptr, enclen, offset);
  if (state != UNICODE_STATE_SUCCESS)
    return state;
  enc.reserve(enclen);
  for (size_t i = 0; i < enclen; ++i)
    enc.push_back(decptr[i]);
  return UNICODE_STATE_SUCCESS;
}


} // namespace quirinus
#endif // QUIRINUS_CORE_STRING_U32_ENCODE_HPP
