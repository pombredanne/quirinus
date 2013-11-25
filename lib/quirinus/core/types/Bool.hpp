/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_TYPES_BOOL_HPP
#define QUIRINUS_CORE_TYPES_BOOL_HPP
namespace quirinus {


class Bool: public Object
{
private:
  bool self;
public:
  friend class Int;
  friend class Float;
  friend class Bytes;
  friend class Unicode;
  Bool(const Object&);
public:
  Bytes repr() const;
  Bool cast_bool() const;
  Int cast_int() const;
  Float cast_float() const;
  Bytes cast_bytes() const;
  Unicode cast_unicode() const;
public:
  ~Bool()
  {}

  Bool(const bool& object)
  : self(object)
  {}

  Bool(const Bool& object)
  : self(object.self)
  {}

#if (QUIRINUS_FEATURE_CXX11)
  Bool(Bool&& object)
  { swap(*this, object); }
#endif

  // Swap function
  friend void
  swap(Bool& lhs, Bool& rhs)
  {
    using std::swap;
    swap(lhs.self, rhs.self);
  }


  // Assignment function
  Bool&
  operator=(Bool object)
  {
    swap(*this, object);
    return *this;
  }


  // Cast functions
  operator bool() const
  { return self; }


  // Virtual functions
  Bool*
  clone() const
  { return new Bool(*this); }


  // Logical functions
  friend Bool
  operator&(const Bool& lhs, const Bool& rhs)
  { return (lhs.self & rhs.self); }

  friend Bool
  operator|(const Bool& lhs, const Bool& rhs)
  { return (lhs.self | rhs.self); }

  friend Bool
  operator^(const Bool& lhs, const Bool& rhs)
  { return (lhs.self ^ rhs.self); }


  // Modifying functions
  friend Bool
  operator&=(Bool& lhs, const bool& rhs)
  { return (lhs.self &= rhs); }

  friend Bool
  operator&=(bool& lhs, const Bool& rhs)
  { return (lhs &= rhs.self); }

  friend Bool
  operator|=(Bool& lhs, const bool& rhs)
  { return (lhs.self |= rhs); }

  friend Bool
  operator|=(bool& lhs, const Bool& rhs)
  { return (lhs |= rhs.self); }

  friend Bool
  operator^=(Bool& lhs, const bool& rhs)
  { return (lhs.self ^= rhs); }

  friend Bool
  operator^=(bool& lhs, const Bool& rhs)
  { return (lhs ^= rhs.self); }
};


} // namespace quirinus
#endif // QUIRINUS_CORE_TYPES_BOOL_HPP
