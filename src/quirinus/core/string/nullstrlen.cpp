/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#include <quirinus/core.hpp>
namespace quirinus {


namespace {
static const uint64_t
STRLEN_BITMASK_LE[] = \
{
#if (UINT64_MAX == ULONG_MAX)
  // 8-bit character
  0x00000000000000FFUL,
  0x000000000000FF00UL,
  0x0000000000FF0000UL,
  0x00000000FF000000UL,
  0x000000FF00000000UL,
  0x0000FF0000000000UL,
  0x00FF000000000000UL,
  0xFF00000000000000UL,
  // 16-bit character
  0x000000000000FFFFUL,
  0x00000000FFFF0000UL,
  0x0000FFFF00000000UL,
  0xFFFF000000000000UL,
  // 32-bit character
  0x00000000FFFFFFFFUL,
  0xFFFFFFFF00000000UL
#else
  // 8-bit character
  0x00000000000000FFULL,
  0x000000000000FF00ULL,
  0x0000000000FF0000ULL,
  0x00000000FF000000ULL,
  0x000000FF00000000ULL,
  0x0000FF0000000000ULL,
  0x00FF000000000000ULL,
  0xFF00000000000000ULL,
  // 16-bit character
  0x000000000000FFFFULL,
  0x00000000FFFF0000ULL,
  0x0000FFFF00000000ULL,
  0xFFFF000000000000ULL,
  // 32-bit character
  0x00000000FFFFFFFFULL,
  0xFFFFFFFF00000000ULL
#endif
};


static const uint64_t
STRLEN_BITMASK_BE[] = \
{
#if (UINT64_MAX == ULONG_MAX)
  // 8-bit character
  // 8-bit character
  0xFF00000000000000UL,
  0x00FF000000000000UL,
  0x0000FF0000000000UL,
  0x000000FF00000000UL,
  0x00000000FF000000UL,
  0x0000000000FF0000UL,
  0x000000000000FF00UL,
  0x00000000000000FFUL,
  // 16-bit character
  0xFFFF000000000000UL,
  0x0000FFFF00000000UL,
  0x00000000FFFF0000UL,
  0x000000000000FFFFUL,
  // 32-bit character
  0xFFFFFFFF00000000UL,
  0x00000000FFFFFFFFUL
#else
  // 8-bit character
  0xFF00000000000000UL,
  0x00FF000000000000UL,
  0x0000FF0000000000UL,
  0x000000FF00000000UL,
  0x00000000FF000000UL,
  0x0000000000FF0000UL,
  0x000000000000FF00UL,
  0x00000000000000FFUL,
  // 16-bit character
  0xFFFF000000000000UL,
  0x0000FFFF00000000UL,
  0x00000000FFFF0000UL,
  0x000000000000FFFFUL,
  // 32-bit character
  0xFFFFFFFF00000000UL,
  0x00000000FFFFFFFFUL
#endif
};


const uint64_t*
nullstrlen_bitmask()
{
  union {
    uint32_t code;
    uint8_t bytes[4];
  } endian = {0x01020304};
  if (endian.bytes[0] == 0x01)
    return STRLEN_BITMASK_BE;
  return STRLEN_BITMASK_LE;
}
} // namespace


size_t
nullstrlen(const bytechar* str)
{
  size_t i = 0;
  size_t len = 0;
  size_t shift = 8;
  uint64_t code = 0;
  const uint64_t* pointer = NULL;
  const uint64_t* mask = nullstrlen_bitmask();
  pointer = reinterpret_cast<const uint64_t*>(str);
  while (true)
  {
    for (i = 0; i < shift; ++i)
    {
      code = *pointer;
      if (!(code & mask[i]))
        return (len + i);
    }
    len += shift;
    ++pointer;
  }
  return len;
}


size_t
nullstrlen(const widechar* str)
{
  size_t i = 0;
  size_t len = 0;
  size_t shift = 4;
  uint64_t code = 0;
  const uint64_t* pointer = NULL;
  const uint64_t* mask = (nullstrlen_bitmask() + 8);
  pointer = reinterpret_cast<const uint64_t*>(str);
  while (true)
  {
    for (i = 0; i < shift; ++i)
    {
      code = *pointer;
      if (!(code & mask[i]))
        return (len + i);
    }
    len += shift;
    ++pointer;
  }
  return len;
}


size_t
nullstrlen(const unicode* str)
{
  size_t i = 0;
  size_t len = 0;
  size_t shift = 2;
  uint64_t code = 0;
  const uint64_t* pointer = NULL;
  const uint64_t* mask = (nullstrlen_bitmask() + 8 + 4);
  pointer = reinterpret_cast<const uint64_t*>(str);
  while (true)
  {
    for (i = 0; i < shift; ++i)
    {
      code = *pointer;
      if (!(code & mask[i]))
        return (len + i);
    }
    len += shift;
    ++pointer;
  }
  return len;
}


size_t
nullstrlen(const char* str)
{ return nullstrlen(reinterpret_cast<const bytechar*>(str)); }


size_t
nullstrlen(const wchar_t* str)
{
#if (QUIRINUS_UNICODE_WCHAR_SIZE == 4)
  return nullstrlen(reinterpret_cast<const unicode*>(str));
#else // (QUIRINUS_UNICODE_WCHAR_SIZE != 4)
  return nullstrlen(reinterpret_cast<const widechar*>(str));
#endif
}


} // namespace quirinus
