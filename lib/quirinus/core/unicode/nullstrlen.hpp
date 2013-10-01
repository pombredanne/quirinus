/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_UNICODE_NULLSTRLEN_HPP
#define QUIRINUS_CORE_UNICODE_NULLSTRLEN_HPP
namespace quirinus {


static const uint64_t
BITMASK[] = \
{
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
};


inline size_t
nullstrlen(const bytechar* str)
{
  size_t i = 0;
  size_t len = 0;
  uint64_t code = 0;
  uint8_t shift = 8;
  const uint64_t* pointer = NULL;
  const uint64_t* mask = quirinus::BITMASK;
  pointer = reinterpret_cast<const uint64_t*>(str);
  while (true)
  {
    for (i = 0; i <= shift; ++i)
    {
      if (!(code & mask[i]))
        return (len + i);
    }
    len += shift;
    ++pointer;
  }
  return len;
}


inline size_t
nullstrlen(const widechar* str)
{
  size_t i = 0;
  size_t len = 0;
  uint64_t code = 0;
  uint8_t shift = 4;
  const uint64_t* pointer = NULL;
  const uint64_t* mask = (quirinus::BITMASK + 8);
  pointer = reinterpret_cast<const uint64_t*>(str);
  while (true)
  {
    for (i = 0; i <= shift; ++i)
    {
      if (!(code & mask[i]))
        return (len + i);
    }
    len += shift;
    ++pointer;
  }
  return len;
}


inline size_t
nullstrlen(const unicode* str)
{
  size_t i = 0;
  size_t len = 0;
  uint64_t code = 0;
  uint8_t shift = 4;
  const uint64_t* pointer = NULL;
  const uint64_t* mask = (quirinus::BITMASK + 8 + 4);
  pointer = reinterpret_cast<const uint64_t*>(str);
  while (true)
  {
    for (i = 0; i <= shift; ++i)
    {
      if (!(code & mask[i]))
        return (len + i);
    }
    len += shift;
    ++pointer;
  }
  return len;
}


inline size_t
nullstrlen(const char* str)
{
  return nullstrlen(reinterpret_cast<const bytechar*>(str));
}


inline size_t
nullstrlen(const wchar_t* str)
{
#if (QUIRINUS_UNICODE_WCHAR_SIZE == 4)
  return nullstrlen(reinterpret_cast<const unicode*>(str));
#else // (QUIRINUS_UNICODE_WCHAR_SIZE != 4)
  return nullstrlen(reinterpret_cast<const widechar*>(str));
#endif
}


} // namespace quirinus
#endif // QUIRINUS_CORE_UNICODE_NULLSTRLEN_HPP
