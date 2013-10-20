/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CODECS_CODEC_HPP
#define QUIRINUS_CODECS_CODEC_HPP
namespace quirinus {
namespace codecs {


class Codec: public Object
{
public:
  virtual Codec* clone() const = 0;
  virtual Bytes encoding() const = 0;
  virtual Unicode decode(const Bytes& string) const = 0;
  virtual Bytes encode(const Unicode& string) const = 0;
public:
  ~Codec()
  {}

  Codec()
  {}
};


} // namespace codecs
} // namespace quirinus
#endif // QUIRINUS_CODECS_CODEC_HPP
