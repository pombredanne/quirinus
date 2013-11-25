/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_STRING_CHARACTER_UNICODE_HPP
#define QUIRINUS_CORE_STRING_CHARACTER_UNICODE_HPP
namespace quirinus {


class unicode
{
private:
  uint32_t self;
public:
  inline ~unicode()
  {}

  inline unicode()
  : self(0) {}

  inline unicode(const uint32_t& object)
  : self(object) {}

  inline unicode(const unicode& object)
  : self(object.self) {}

  inline void
  swap(unicode& lhs, unicode& rhs)
  {
    using std::swap;
    swap(lhs.self, rhs.self);
  }

  inline unicode&
  operator=(unicode object)
  {
    swap(*this, object);
    return *this;
  }

  inline operator uint32_t() const
  { return self; }

  friend inline std::ostream&
  operator<<(std::ostream& sstream,
             const unicode& object)
  {
    uint32_t code = object.self;
    const size_t size = ((code > 0xFFFF) ? 8 : 4);
    const char prefix = ((code > 0xFFFF) ? 'U' : 'u');
    char* buffer = new char[size];
    ::memset(buffer, 0, size);
    ::sprintf(buffer, "%0X", code);
    sstream << '\\' << prefix << buffer;
    delete[] buffer;
    return sstream;
  }
};


} // namespace quirinus
#endif // QUIRINUS_CORE_STRING_CHARACTER_UNICODE_HPP
