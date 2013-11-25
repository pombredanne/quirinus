/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CODECS_LOOKUP_HPP
#define QUIRINUS_CODECS_LOOKUP_HPP
#include "Codec.hpp"
#include "Codec_ASCII.hpp"
#include "Codec_UTF8.hpp"
#include "Codec_UTF16.hpp"
#include "Codec_UTF32.hpp"
#include "LookupError.hpp"
namespace quirinus {
namespace codecs {


Codec*
lookup(const Bytes& encoding);


} // namespace codecs
} // namespace quirinus
#endif // QUIRINUS_CODECS_LOOKUP_HPP
