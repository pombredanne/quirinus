/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#include <quirinus/core.hpp>
namespace quirinus {


int
u8_decode(const bytechar* encptr,
          const size_t& enclen,
          unicode*& decptr,
          size_t& declen,
          size_t& offset)
{
  int state = 0;
  unicode* tempptr;
  const bytechar* iter = encptr;
  const bytechar* tail = (iter + enclen);

  // Allocate memory.
  state = u8_mbslen(encptr, enclen, declen, offset);
  if (state != UNICODE_STATE_SUCCESS)
    return state;
  decptr = tempptr = new unicode[declen];

  // Byte order check.
  if ((iter[0] == 0xEF)
  &&  (iter[1] == 0xBB)
  &&  (iter[2] == 0xBF))
    iter += 3;

  // Decode sequence.
  byte count;
  uint32_t code;
  while (iter < tail)
  {
    if (*iter < 0x80)
    {
      code = *iter;
      count = 1;
    }
    else if (*iter < 0xE0)
    {
      code  = ((iter[0] & 0x1F) << 6);
      code |= ((iter[1] ^ 0x80));
      count = 2;
    }
    else if (*iter < 0xF0)
    {
      code  = ((iter[0] & 0x0F) << 12);
      code |= ((iter[1] ^ 0x80) << 6);
      code |= ((iter[2] ^ 0x80));
      count = 3;
    }
    else
    {
      code  = ((iter[0] & 0x07) << 18);
      code |= ((iter[1] ^ 0x80) << 12);
      code |= ((iter[2] ^ 0x80) << 6);
      code |= ((iter[3] ^ 0x80));
      count = 4;
    }
    *tempptr = code;
    iter += count;
    ++tempptr;
  }
  return UNICODE_STATE_SUCCESS;
}


int
u8_decode(const std::vector<bytechar>& enc,
          std::vector<unicode>& dec,
          size_t& offset)
{
  int state;
  size_t declen = 0;
  unicode* decptr = NULL;
  size_t enclen = enc.size();
  const bytechar* encptr = &enc[0];
  state = u8_decode(encptr, enclen, decptr, declen, offset);
  if (state != UNICODE_STATE_SUCCESS)
    return state;
  dec.reserve(declen);
  for (size_t i = 0; i < declen; ++i)
    dec.push_back(decptr[i]);
  return UNICODE_STATE_SUCCESS;
}


} // namespace quirinus
