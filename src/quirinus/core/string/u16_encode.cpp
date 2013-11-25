/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#include <quirinus/core.hpp>
namespace quirinus {


int
u16_encode(const unicode* decptr,
           const size_t& declen,
           bytechar*& encptr,
           size_t& enclen,
           size_t& offset)
{
  int state = 0;
  bytechar* tempptr;
  union codeconv {
    uint16_t code;
    uint8_t bytes[2];
  } codeconv = {0x0000};
  const unicode* iter = decptr;
  const unicode* tail = (iter + declen);

  // Reserve memory.
  state = u16_ucslen(decptr, declen, enclen, offset);
  if (state != UNICODE_STATE_SUCCESS)
    return state;
  encptr = tempptr = new bytechar[enclen];

  // Encode sequence.
  uint32_t code;
  while (iter < tail)
  {
    code = *iter;
    if ((code < 0xD800) \
    ||  ((code <= 0xFFFF) && (code >= 0xE000)))
    {
      codeconv.code = code;
      tempptr[0] = codeconv.bytes[0];
      tempptr[1] = codeconv.bytes[1];
      tempptr += 2;
    }
    else
    {
      codeconv.code = (0xD800 + ((code - 0x10000) >> 10));
      tempptr[0] = codeconv.bytes[0];
      tempptr[1] = codeconv.bytes[1];
      codeconv.code = (0xDC00 + ((code - 0x10000) & 0x03FF));
      tempptr[0] = codeconv.bytes[0];
      tempptr[1] = codeconv.bytes[1];
      tempptr += 4;
    }
    ++iter;
  }
  return UNICODE_STATE_SUCCESS;
}


int
u16_encode(const std::vector<unicode>& dec,
           std::vector<bytechar>& enc,
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
  {
    uint8_t code = decptr[i];
    enc.push_back(code);
  }
  return UNICODE_STATE_SUCCESS;
}


} // namespace quirinus
