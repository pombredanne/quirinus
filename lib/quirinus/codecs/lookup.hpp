/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CODECS_LOOKUP_HPP
#define QUIRINUS_CODECS_LOOKUP_HPP
#include "Codec.hpp"
#include "UTF8Codec.hpp"
#include "UTF16Codec.hpp"
#include "UTF32Codec.hpp"
#include "LookupError.hpp"
namespace quirinus {
namespace codecs {

inline Codec*
lookup(const Bytes& encoding)
{
  // ASCII
  if ((encoding == "ASCII")
  ||  (encoding == "ascii")
  ||  (encoding == "US-ASCII")
  ||  (encoding == "us-ascii"))
    throw ValueError("ASCII");

  // UTF-8
  else if ((encoding == "UTF-8")
  ||       (encoding == "utf-8")
  ||       (encoding == "UTF8")
  ||       (encoding == "utf8")
  ||       (encoding == "cp65001"))
    return new UTF8Codec;

  // UTF-16
  else if ((encoding == "UTF-16")
  ||       (encoding == "UTF-16BE")
  ||       (encoding == "UTF-16LE")
  ||       (encoding == "utf-16")
  ||       (encoding == "utf-16be")
  ||       (encoding == "utf-16le")
  ||       (encoding == "UTF16")
  ||       (encoding == "UTF16BE")
  ||       (encoding == "UTF16LE")
  ||       (encoding == "utf16")
  ||       (encoding == "utf16be")
  ||       (encoding == "utf16le"))
    return new UTF16Codec;

  // UTF-32
  else if ((encoding == "UTF-32")
  ||       (encoding == "UTF-32BE")
  ||       (encoding == "UTF-32LE")
  ||       (encoding == "utf-32")
  ||       (encoding == "utf-32be")
  ||       (encoding == "utf-32le")
  ||       (encoding == "UTF32")
  ||       (encoding == "UTF32BE")
  ||       (encoding == "UTF32LE")
  ||       (encoding == "utf32")
  ||       (encoding == "utf32be")
  ||       (encoding == "utf32le"))
    return new UTF32Codec;

  // Other
  else
  {
    char* encbuffer = encoding.nullstr();
    LookupError error(encbuffer);
    delete[] encbuffer;
    throw error;
  }
}


} // namespace codecs
} // namespace quirinus
#endif // QUIRINUS_CODECS_LOOKUP_HPP
