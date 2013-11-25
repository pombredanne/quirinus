/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_STRING_CHARACTER_BYTECHAR_HPP
#define QUIRINUS_CORE_STRING_CHARACTER_BYTECHAR_HPP
namespace quirinus {


class bytechar
{
private:
  uint8_t self;
public:
  inline ~bytechar()
  {}

  inline bytechar()
  : self(0) {}

  inline bytechar(const uint8_t& object)
  : self(object) {}

  inline bytechar(const bytechar& object)
  : self(object.self) {}

  inline void
  swap(bytechar& lhs, bytechar& rhs)
  {
    using std::swap;
    swap(lhs.self, rhs.self);
  }

  inline bytechar&
  operator=(bytechar object)
  {
    swap(*this, object);
    return *this;
  }

  inline operator uint8_t() const
  { return self; }

  friend inline std::ostream&
  operator<<(std::ostream& sstream,
             const bytechar& object)
  {
    uint8_t code = object.self;
    if (code <= 0x80)
      sstream << '\\' << code;
    else
    {
      const size_t size = 3;
      char* buffer = new char[size];
      ::memset(buffer, 0, size);
      ::sprintf(buffer, "%0X", code);
      sstream << '\\' << 'x' << buffer;
      delete[] buffer;
    }
    return sstream;
  }
};


} // namespace quirinus
#endif // QUIRINUS_CORE_STRING_CHARACTER_BYTECHAR_HPP
