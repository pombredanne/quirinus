/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#include <quirinus/core.hpp>
namespace quirinus {


bytechar::bytechar(const widechar& object)
: self(object.self) {}

bytechar::bytechar(const unicode& object)
: self(object.self) {}


widechar::widechar(const bytechar& object)
: self(object.self) {}

widechar::widechar(const unicode& object)
: self(object.self) {}


unicode::unicode(const bytechar& object)
: self(object.self) {}

unicode::unicode(const widechar& object)
: self(object.self) {}


} // namespace quirinus
