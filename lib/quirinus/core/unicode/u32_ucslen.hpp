/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_UNICODE_U32_UCSLEN_HPP
#define QUIRINUS_CORE_UNICODE_U32_UCSLEN_HPP
namespace quirinus {


inline int
u32_ucslen(const unicode* iter,
           const size_t& declen,
           size_t& enclen,
           size_t& offset)
{
  int state;
  const unicode* tail;
  tail = (iter + declen);

  // Reset variables.
  offset = 0;
  enclen = 0;
  state = UNICODE_STATE_SUCCESS;

  // Check null pointer.
  if (iter == NULL)
    return UNICODE_STATE_NULLPTR;

  // Calculate length.
  unicode code;
  while (iter < tail)
  {
    code = *iter;
    if (!((code < 0xD800) || ((code >= 0xE000) && (code < 0x110000))))
      state = UNICODE_STATE_ILLEGAL;

    // Check current state.
    if (state != UNICODE_STATE_SUCCESS)
    {
      enclen = 0;
      return state;
    }

    // Adjust variables.
    enclen += 4;
    ++offset;
    ++iter;
  }
  offset = (tail - iter);
  enclen += 4; // Byte order mark
  return UNICODE_STATE_SUCCESS;
}


} // namespace quirinus
#endif // QUIRINUS_CORE_UNICODE_U32_UCSLEN_HPP
