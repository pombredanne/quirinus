/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#include <quirinus/core.hpp>
#include <quirinus/codecs.hpp>
namespace quirinus {
namespace codecs {


Bytes
encode(const Unicode& ustring,
       const Bytes& encoding)
{
  Codec* codec = lookup(encoding);
  Bytes bstring = codec->encode(bstring);
  delete codec;
  return bstring;
}


} // namespace codecs
} // namespace quirinus
