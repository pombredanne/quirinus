/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_SYSTEM_WORDSIZE_HPP
#define QUIRINUS_CORE_SYSTEM_WORDSIZE_HPP
namespace quirinus {
namespace system {


Bytes wordsize()
{
  size_t wordsize = sizeof(void*);
  if ((wordsize != 8) && (wordsize != 4))
    throw SystemError("wordsize must be 4 or 8");
}


} // namespace system
} // namespace quirinus
#endif QUIRINUS_CORE_SYSTEM_WORDSIZE_HPP
