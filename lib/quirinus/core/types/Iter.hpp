/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_TYPES_ITER_HPP
#define QUIRINUS_CORE_TYPES_ITER_HPP
#include "Bool.hpp"
#include "Int.hpp"
#include "Float.hpp"
#include "Bytes.hpp"
#include "Unicode.hpp"
namespace quirinus {


class Iter: public Object
{
public:
  typedef size_t index_type;
  typedef SmartPointer<Object> element_type;
  typedef std::vector<element_type> array_type;
private:
  array_type self_array;
  mutable index_type self_index;
public:
  ~Iter()
  {}

  Iter()
  : self_array()
  , self_index(0)
  {}

  Iter(const Iter& object)
  : self_array(object.self_array)
  , self_index(object.self_index)
  {}

#if (QUIRINUS_FEATURE_CXX11)
  Iter(Iter&& object)
  { swap(*this, object); }
#endif

  Iter(const Bytes& object)
  : self_array()
  , self_index(0)
  {
    const bytechar* head = object.head();
    const bytechar* tail = object.tail();
    for (; head < tail; ++head)
    {
      Bytes stack(head, 1);
      self_array.push_back(stack.clone());
    }
  }

  Iter(const Unicode& object)
  : self_array()
  , self_index(0)
  {
    const unicode* head = object.head();
    const unicode* tail = object.tail();
    for (; head < tail; ++head)
    {
      Unicode stack(head, 1);
      self_array.push_back(stack.clone());
    }
  }

  template <typename TYPE>
  Iter(TYPE object)
  : self_array()
  , self_index(0)
  {
    typedef typename supertype<TYPE>::type SUPER;
    if ((!sametype<Bytes, SUPER>::value)
    &&  (!sametype<Unicode, SUPER>::value))
      throw TypeError("iterable cast failed");
    SUPER temp(object);
    Iter stack(temp);
    swap(*this, stack);
  }

  Iter(const Object* iter,
       const size_t& size)
  : self_array()
  , self_index(0)
  {
    if (size <= 0)
      throw ValueError("size must be >= 0");
    const Object* tail = (iter + size);
    Iter stack(iter, tail);
    swap(*this, stack);
  }

  template <typename TYPE>
  Iter(const TYPE* iter,
       const size_t& size)
  {
    if (size <= 0)
      throw ValueError("size must be >= 0");
    const TYPE* tail = (iter + size);
    Iter stack(iter, tail);
    swap(*this, stack);
  }

  Iter(const char* head,
       const char* tail)
  {
    if (head > tail)
      throw ValueError("incorrect range");
    Iter stack(Bytes(head, tail));
    swap(*this, stack);
  }

  Iter(const wchar_t* head,
       const wchar_t* tail)
  {
    if (head > tail)
      throw ValueError("incorrect range");
    Iter stack(Unicode(head, tail));
    swap(*this, stack);
  }

  Iter(const bytechar* head,
       const bytechar* tail)
  {
    if (head > tail)
      throw ValueError("incorrect range");
    Iter stack(Bytes(head, tail));
    swap(*this, stack);
  }

  Iter(const widechar* head,
       const widechar* tail)
  {
    if (head > tail)
      throw ValueError("incorrect range");
    Iter stack(Unicode(head, tail));
    swap(*this, stack);
  }

  Iter(const unicode* head,
       const unicode* tail)
  {
    if (head > tail)
      throw ValueError("incorrect range");
    Iter stack(Unicode(head, tail));
    swap(*this, stack);
  }

  Iter(const Object* head,
       const Object* tail)
  : self_array()
  , self_index(0)
  {
    if (head > tail)
      throw ValueError("incorrect range");
    self_array.reserve(tail - head);
    for (; head < tail; ++head)
      self_array.push_back(head->clone());
  }

  template <typename TYPE>
  Iter(const TYPE* head,
       const TYPE* tail)
  : self_array()
  , self_index(0)
  {
    if (head > tail)
      throw ValueError("incorrect range");
    self_array.reserve(tail - head);
    for (; head < tail; ++head)
    {
      typename supertype<TYPE>::type object(*head);
      self_array.push_back(object.clone());
    }
  }


  // Swap function
  friend void
  swap(Iter& lhs, Iter& rhs)
  {
    using std::swap;
    swap(lhs.self_index, rhs.self_index);
    swap(lhs.self_array, rhs.self_array);
  }


  // Assignment function
  Iter&
  operator=(Iter object)
  {
    swap(*this, object);
    return *this;
  }


  // Virtual functions
  Bool
  cast_bool() const
  { return (self_index < self_array.size()); }


  // Iterable functions
  const Object&
  acquire() const
  {
    index_type size = self_array.size();
    if (self_index >= size)
      throw IndexError();
    return *self_array[self_index++];
  }


  const Object*
  head() const
  { return (self_array.begin()->pointer()); }


  const Object*
  iter() const
  { return ((self_array.begin() + self_index)->pointer()); }


  const Object*
  tail() const
  { return ((self_array.end() - 1)->pointer() + 1); }
};


} // namespace quirinus
#endif // QUIRINUS_CORE_TYPES_ITER_HPP
