/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_STRING_CHARACTER_WIDECHAR_HPP
#define QUIRINUS_CORE_STRING_CHARACTER_WIDECHAR_HPP
namespace quirinus {


class widechar
{
private:
  uint16_t self;
public:
  inline ~widechar()
  {}

  inline widechar()
  : self(0) {}

  inline widechar(const uint16_t& object)
  : self(object) {}

  inline widechar(const widechar& object)
  : self(object.self) {}

  inline void
  swap(widechar& lhs, widechar& rhs)
  {
    using std::swap;
    swap(lhs.self, rhs.self);
  }

  inline widechar&
  operator=(widechar object)
  {
    swap(*this, object);
    return *this;
  }

  inline operator uint16_t() const
  { return self; }

  friend inline std::ostream&
  operator<<(std::ostream& sstream,
             const widechar& object)
  {
    const size_t size = 5;
    char* buffer = new char[size];
    ::memset(buffer, 0, size);
    uint16_t code = object.self;
    ::sprintf(buffer, "%0X", code);
    sstream << '\\' << 'u' << buffer;
    delete[] buffer;
    return sstream;
  }
};


} // namespace quirinus
#endif // QUIRINUS_CORE_STRING_CHARACTER_WIDECHAR_HPP
