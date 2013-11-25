/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#include <quirinus/core.hpp>
#include <quirinus/codecs.hpp>
namespace quirinus {
namespace codecs {


Unicode
decode(const Bytes& bstring,
       const Bytes& encoding)
{
  Codec* codec = lookup(encoding);
  Unicode ustring = codec->decode(bstring);
  delete codec;
  return ustring;
}


} // namespace codecs
} // namespace quirinus
