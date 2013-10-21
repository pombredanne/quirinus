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
  Bool(const Bool&& object)
  : self()
  { swap(*this, object); }
#endif

  // Swap function
  friend inline void
  swap(Bool& lhs, Bool& rhs)
  {
    using std::swap;
    swap(lhs.self, rhs.self);
  }


  // Assignment function
  inline Bool&
  operator=(Bool object)
  {
    swap(*this, object);
    return *this;
  }


  // Cast functions
  inline
  operator bool() const
  { return self; }


  // Virtual functions
  inline Bool*
  clone() const
  { return new Bool(*this); }


  // Logical functions
  friend inline Bool
  operator&(const Bool& lhs, const Bool& rhs)
  { return (lhs.self & rhs.self); }

  friend inline Bool
  operator|(const Bool& lhs, const Bool& rhs)
  { return (lhs.self | rhs.self); }

  friend inline Bool
  operator^(const Bool& lhs, const Bool& rhs)
  { return (lhs.self ^ rhs.self); }


  // Modifying functions
  inline Bool&
  operator&=(const Bool& object)
  {
    self &= object.self;
    return *this;
  }

  inline Bool&
  operator|=(const Bool& object)
  {
    self |= object.self;
    return *this;
  }

  inline Bool&
  operator^=(const Bool& object)
  {
    self ^= object.self;
    return *this;
  }
};


} // namespace quirinus
#endif // QUIRINUS_CORE_TYPES_BOOL_HPP
