/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#include <quirinus/core.hpp>
namespace quirinus {


bytechar*
nullstrdup(const bytechar* str)
{
  size_t len = nullstrlen(str);
  bytechar* pointer = new bytechar[(len + 1)];
  for (size_t i = 0; i < len; ++i)
    pointer[i] = str[i];
  pointer[len] = 0;
  return pointer;
}


widechar*
nullstrdup(const widechar* str)
{
  size_t len = nullstrlen(str);
  widechar* pointer = new widechar[(len + 1)];
  for (size_t i = 0; i < len; ++i)
    pointer[i] = str[i];
  pointer[len] = 0;
  return pointer;
}


unicode*
nullstrdup(const unicode* str)
{
  size_t len = nullstrlen(str);
  unicode* pointer = new unicode[(len + 1)];
  for (size_t i = 0; i < len; ++i)
    pointer[i] = str[i];
  pointer[len] = 0;
  return pointer;
}


char*
nullstrdup(const char* str)
{
  const bytechar* pointer = reinterpret_cast<const bytechar*>(str);
  return reinterpret_cast<char*>(nullstrdup(pointer));
}


wchar_t*
nullstrdup(const wchar_t* str)
{
#if (QUIRINUS_UNICODE_WCHAR_SIZE == 4)
  const unicode* pointer = reinterpret_cast<const unicode*>(str);
#else
  const widechar* pointer = reinterpret_cast<const widechar*>(str);
#endif
  return reinterpret_cast<wchar_t*>(nullstrdup(pointer));
}


} // namespace quirinus
