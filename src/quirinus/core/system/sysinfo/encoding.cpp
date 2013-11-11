/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#include <quirinus/core.hpp>
namespace quirinus {
namespace {


inline void
sysinfo_encoding(struct sysinfo* sys)
{
#if (QUIRINUS_FEATURE_POSIX)
  Bytes language;
  char* encoding = NULL;
  char* tmplocale = NULL;
  char* oldlocale = NULL;
  char* newlocale = NULL;
  const char* pointer = NULL;
  language = quirinus::env("LANG");
  if (!language)
    language = quirinus::env("LC_ALL");

  // Backup default and emerge system locale.
  pointer = ::setlocale(LC_ALL, NULL);
  oldlocale = nullstrdup(pointer);
  tmplocale = language.nullstr();
  pointer = ::setlocale(LC_ALL, tmplocale);
  if (!pointer)
    throw SupportError("locale charset detection failed");
  newlocale = nullstrdup(pointer);
  pointer = ::nl_langinfo(CODESET);
  encoding = nullstrdup(pointer);

  // Change sysinfo variables.
  sys->encoding.locale = encoding;
  sys->encoding.stdinstream = encoding;
  sys->encoding.stdoutstream = encoding;
  sys->encoding.stderrstream = encoding;
  sys->encoding.filesystem = encoding;

  // Restore locale and free memory.
  pointer = ::setlocale(LC_ALL, oldlocale);
  delete[] encoding;
  delete[] tmplocale;
  delete[] oldlocale;
  delete[] newlocale;
#else
  UINT codepage = 0;
  const size_t size = 16;
  char* encoding = new char[size];

  // ANSI encoding
  ::memset(encoding, 0, size);
  codepage = ::GetACP();
  ::snprintf(encoding, size, "CP%u", codepage);
  sys->encoding.locale = encoding;

  // stdin encoding
  ::memset(encoding, 0, size);
  codepage = ::GetConsoleCP();
  ::snprintf(encoding, size, "CP%u", codepage);
  sys->encoding.stdinstream = encoding;

  // stdout/stderr encoding
  ::memset(encoding, 0, size);
  codepage = ::GetConsoleOutputCP();
  ::snprintf(encoding, size, "CP%u", codepage);
  sys->encoding.stdoutstream = encoding;
  sys->encoding.stderrstream = encoding;

  // file system encoding
  sys->encoding.filesystem = "UTF-16";
#endif
}


} // namespace
} // namespace quirinus
