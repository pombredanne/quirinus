/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_STRING_U16_UCSLEN_HPP
#define QUIRINUS_CORE_STRING_U16_UCSLEN_HPP
namespace quirinus {


inline int
u16_ucslen(const unicode* iter,
           const size_t& declen,
           size_t& enclen,
           size_t& offset)
{
  int state = UNICODE_STATE_SUCCESS;
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
    if (code < 0xD800)
      count = 2;
    else if (code <= 0xFFFF)
    {
      if (code >= 0xE000)
        count = 2;
      else
        state = UNICODE_STATE_ILLEGAL;
    }
    else
    {
      if (code < 0x110000)
        count = 4;
      else
        state = UNICODE_STATE_ILLEGAL;
    }

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
#endif // QUIRINUS_CORE_STRING_U16_UCSLEN_HPP
