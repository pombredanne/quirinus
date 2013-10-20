/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_POINTERS_NULLPOINTER_HPP
#define QUIRINUS_CORE_POINTERS_NULLPOINTER_HPP
namespace quirinus {


class NullPointer
{
private:
  void operator->() const;
  void operator&() const;
public:
  ~NullPointer()
  {}

  NullPointer()
  {}


  // Cast functions
  inline
  operator bool() const
  { return 0; }

  template < typename TYPE >
  inline operator TYPE*() const
  { return 0; }

  template < typename TYPE, typename SUBTYPE >
  inline operator SUBTYPE TYPE::*() const
  { return 0; }


  // Special functions
  template <typename TYPE>
  static inline int
  cmp(const NullPointer&, const TYPE* pointer)
  { return ((!!pointer) ? +1 : 0); }

  template <typename TYPE>
  static inline int
  cmp(const TYPE* pointer, const NullPointer&)
  { return ((!!pointer) ? -1 : 0); }
};


} // namespace quirinus
#endif // QUIRINUS_CORE_POINTERS_NULLPOINTER_HPP
