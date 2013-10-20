/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_SYSTEM_DATAMODEL_HPP
#define QUIRINUS_SYSTEM_DATAMODEL_HPP
namespace quirinus {


inline Bytes
datamodel()
{
  if ((sizeof(int) == 2)
  ||  (sizeof(long) == 4)
  ||  (sizeof(void*) == 4))
    return "LP32";

  if ((sizeof(int) == 4)
  ||  (sizeof(long) == 4)
  ||  (sizeof(void*) == 4))
    return "ILP32";

  if ((sizeof(int) == 4)
  ||  (sizeof(long) == 8)
  ||  (sizeof(void*) == 8))
    return "LP64";

  if ((sizeof(int) == 8)
  ||  (sizeof(long) == 8)
  ||  (sizeof(void*) == 8))
    return "ILP64";

  if ((sizeof(int) == 4)
  ||  (sizeof(long) == 4)
  ||  (sizeof(void*) == 8))
    return "LLP64";
}


} // namespace quirinus
#endif // QUIRINUS_SYSTEM_DATAMODEL_HPP
