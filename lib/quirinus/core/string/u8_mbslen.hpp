/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_STRING_U8_MBSLEN_HPP
#define QUIRINUS_CORE_STRING_U8_MBSLEN_HPP
namespace quirinus {


inline int
u8_mbslen(const bytechar* iter,
          const size_t& enclen,
          size_t& declen,
          size_t& offset)
{
  int state = UNICODE_STATE_SUCCESS;
  const bytechar* tail;
  tail = (iter + enclen);

  // Reset variables.
  offset = 0;
  declen = 0;

  // Check null pointer.
  if (iter == NULL)
    return UNICODE_STATE_NULLPTR;

  // Skip byte order mark.
  if ((iter[0] == 0xEF)
  &&  (iter[1] == 0xBB)
  &&  (iter[2] == 0xBF))
    iter += 3;

  // Calculate length.
  byte count = 0;
  while (iter < tail)
  {
    // ASCII codeset code point.
    if (*iter < 0x80)
      count = 1;

    // Isolated code point.
    else if (*iter < 0xC0)
      state = UNICODE_STATE_ISOLATED;

    // 2-byte sequence.
    else if (*iter < 0xE0)
    {
      if ((iter[1] & 0xC0) != 0x80)
        state = UNICODE_STATE_HEADER;
      if (!(*iter & 0x3E))
        state = UNICODE_STATE_OVERLONG;
      count = 2;
    }

    // 3-byte sequence.
    else if (*iter < 0xF0)
    {
      if ((iter[1] & 0xC0) != 0x80)
        state = UNICODE_STATE_HEADER;
      if ((iter[2] & 0xC0) != 0x80)
      {
        ++offset;
        state = UNICODE_STATE_HEADER;
      }
      if ((iter[0] == 0xE0) && !(iter[1] & 0x20))
        state = UNICODE_STATE_OVERLONG;
      if ((iter[0] == 0xED) && (iter[1] >= 0xA0))
        state = UNICODE_STATE_ILLEGAL;
      count = 3;
    }

    // 4-byte sequence.
    else if (*iter < 0xF8)
    {
      if ((iter[1] & 0xC0) != 0x80)
        state = UNICODE_STATE_HEADER;
      if ((iter[2] & 0xC0) != 0x80)
      {
        ++offset;
        state = UNICODE_STATE_HEADER;
      }
      if ((iter[3] & 0xC0) != 0x80)
      {
        offset += 2;
        state = UNICODE_STATE_HEADER;
      }
      if ((iter[0] == 0xF0) && !(iter[1] & 0x30))
        state = UNICODE_STATE_OVERLONG;
      if ((iter[0] > 0xF4) || ((iter[0] == 0xF4) && (iter[1] > 0x8F)))
        state = UNICODE_STATE_ILLEGAL;
      count = 4;
    }

    // Illegal code point.
    else
      state = UNICODE_STATE_ILLEGAL;

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
#endif // QUIRINUS_CORE_STRING_U8_MBSLEN_HPP
