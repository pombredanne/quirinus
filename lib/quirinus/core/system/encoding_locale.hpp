/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_SYSTEM_ENCODING_LOCALE_HPP
#define QUIRINUS_CORE_SYSTEM_ENCODING_LOCALE_HPP
namespace quirinus {


inline Bytes
encoding_locale()
{
#if (QUIRINUS_FEATURE_LANGINFO)
  char* buffer = NULL;
  char* oldlocale = NULL;
  char* newlocale = NULL;
  oldlocale = ::strdup(::setlocale(LC_ALL, NULL));
  newlocale = ::strdup(setlocale(LC_ALL, ""));
  buffer = ::strdup(::nl_langinfo(CODESET));
  if (!buffer)
    throw MemoryError("no memory available");
  ::setlocale(LC_ALL, oldlocale);
  Bytes encoding(buffer);
  ::free(oldlocale);
  ::free(newlocale);
  ::free(buffer);
  return encoding;
#elif defined(QUIRINUS_PLATFORM_WINDOWS)
  char buffer[13];
  ::sprintf(buffer, "CP%u", ::GetACP());
  Bytes encoding(buffer);
  return encoding;
#endif
}


} // namespace quirinus
#endif // QUIRINUS_CORE_SYSTEM_ENCODING_LOCALE_HPP
