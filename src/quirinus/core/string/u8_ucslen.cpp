/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#include <quirinus/core.hpp>
namespace quirinus {


int
u8_ucslen(const unicode* iter,
          const size_t& declen,
          size_t& enclen,
          size_t& offset)
{
  int state = 0;
  const unicode* tail;
  tail = (iter + declen);

  // Reset variables.
  offset = 0;
  enclen = 0;

  // Check null pointer.
  if (iter == NULL)
    return UNICODE_STATE_NULLPTR;

  // Calculate length.
  byte count;
  unicode code;
  while (iter < tail)
  {
    code = *iter;
    if (code < 0x00000080)
      count = 1;
    else if (code < 0x00000800)
      count = 2;
    else if (code < 0x00010000)
    {
      if (!((code < 0x0000D800) || (code >= 0x0000E000)))
        state = UNICODE_STATE_ILLEGAL;
      count = 3;
    }
    else if (code < 0x001FFFFF)
      count = 4;
    else
      state = UNICODE_STATE_ILLEGAL;

    // Check current state.
    if (state != UNICODE_STATE_SUCCESS)
    {
      enclen = 0;
      return state;
    }

    // Adjust variables.
    enclen += count;
    ++offset;
    ++iter;
  }
  return UNICODE_STATE_SUCCESS;
}


} // namespace quirinus
