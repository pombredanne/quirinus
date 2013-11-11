/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CODECS_CONVERT_HPP
#define QUIRINUS_CODECS_CONVERT_HPP
namespace quirinus {
namespace codecs {


/**
 * @brief Convert text from one charset to other.
 * @param buffer input binary buffer
 * @param srcencoding source charset
 * @param destencoding destination charset
 */
inline Bytes
convert(const Bytes& buffer,
        const Bytes& srcencoding,
        const Bytes& destencoding)
{
  Codec* srccodec = codecs::lookup(srcencoding);
  Codec* destcodec = codecs::lookup(destencoding);
  Unicode ustring = srccodec->decode(buffer);
  Bytes bstring = destcodec->encode(ustring);
  delete srccodec;
  delete destcodec;
  return bstring;
}


} // namespace codecs
} // namespace quirinus
#endif // QUIRINUS_CODECS_CONVERT_HPP
