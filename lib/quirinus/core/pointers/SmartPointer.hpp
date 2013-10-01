/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_POINTERS_SMARTPOINTER_HPP
#define QUIRINUS_CORE_POINTERS_SMARTPOINTER_HPP
#include "NullPointer.hpp"
namespace quirinus {


template <typename CLASS>
class SmartPointer
{
public:
  typedef CLASS element_type;
  typedef CLASS* pointer_type;
  typedef CLASS& reference_type;
  template <typename TYPE> friend class SmartPointer;
public:
  class Counter {
  private:
    size_t* self;
  public:
    ~Counter()
    {}

    Counter()
    : self(0)
    {}

    Counter(const Counter& object)
    : self(object.self)
    {}


    // Swap function
    inline friend void
    swap(Counter& lhs, Counter& rhs)
    {
      using std::swap;
      swap(lhs.self, rhs.self);
    }


    // Assignment function
    inline Counter&
    operator=(Counter object)
    {
      swap(*this, object);
      return *this;
    }


    // Cast functions
    inline
    operator bool() const
    {
      if (!self)
        return false;
      return (*self != 0);
    }

    inline
    operator size_t() const
    {
      if (!self)
        return 0;
      return *self;
    }


    // Unary functions
    inline const Counter&
    operator++()
    {
      ++(*self);
      return *this;
    }

    inline const Counter&
    operator--()
    {
      --(*self);
      return *this;
    }

    inline Counter
    operator++(int)
    {
      Counter temp(*this);
      this->operator++();
      return temp;
    }

    inline Counter
    operator--(int)
    {
      Counter temp(*this);
      this->operator--();
      return temp;
    }


    // Other functions
    template <typename TYPE>
    inline void
    acquire(TYPE* pointer)
    {
      if (pointer)
      {
        if (!self)
        {
          try { self = new size_t(1); }
          catch (const std::bad_alloc&)
          {
            delete pointer;
            // throw MemoryError("smart pointer ");
          }
        }
        else
          ++(*self);
      }
    }

    template <typename TYPE>
    inline void
    release(TYPE* pointer)
    {
      if (self)
      {
        --(*self);
        if (*self == 0)
        {
          delete pointer;
          delete self;
        }
        self = 0;
      }
    }

  }; // class Counter
private:
  CLASS* self_pointer;
  Counter self_counter;
public:
  ~SmartPointer()
  {
    this->release();
  }

  SmartPointer()
  : self_pointer(NULL)
  , self_counter()
  {}

  SmartPointer(CLASS* pointer)
  : self_pointer(NULL)
  , self_counter()
  {
    this->acquire(pointer);
  }

  template <typename TYPE>
  SmartPointer(TYPE* pointer)
  : self_pointer(NULL)
  , self_counter()
  {
    this->acquire(static_cast<CLASS*>(pointer));
  }

  SmartPointer(const NullPointer&)
  : self_pointer(NULL)
  , self_counter()
  {}

  SmartPointer(const SmartPointer<CLASS>& object)
  : self_pointer(NULL)
  , self_counter(object.self_counter)
  {
    if ((!object.self_pointer) || (object.self_counter))
      // throw MemoryError("allocation during smart pointer copying");
      throw;
    this->acquire(object.self_pointer);
  }

  template <typename TYPE>
  SmartPointer(const SmartPointer<TYPE>& object)
  : self_counter(object.self_counter)
  , self_pointer(NULL)
  {
    if ((!object.self_pointer) || (object.self_counter))
      // throw MemoryError("allocation during smart pointer copying");
      throw;
    this->acquire(static_cast<CLASS*>(object.self_pointer));
  }


  // Cast functions
  inline operator bool() const
  {
    return !!self_counter;
  }

  template <typename TYPE>
  inline operator TYPE*() const
  {
    return static_cast<CLASS*>(self_pointer);
  }


  // Swap function
  inline friend void
  swap(SmartPointer<CLASS>& lhs, SmartPointer<CLASS>& rhs)
  {
    using std::swap;
    swap(lhs.self_pointer, rhs.self_pointer);
    swap(lhs.self_counter, rhs.self_counter);
  }


  // Assignment function
  inline SmartPointer<CLASS>&
  operator=(SmartPointer<CLASS> object)
  {
    swap(*this, object);
    return *this;
  }


  // Comparison functions
  static inline int
  cmp(const SmartPointer<CLASS>& lhs, const SmartPointer<CLASS>& rhs)
  {
    CLASS* lpointer = lhs.self_pointer;
    CLASS* rpointer = rhs.self_pointer;
    if (lpointer < rpointer)
      return -1;
    else if (lpointer > rpointer)
      return +1;
    return 0;
  }

  static inline int
  cmp(const SmartPointer<CLASS>& lhs, const CLASS* rpointer)
  {
    CLASS* lpointer = lhs.self_pointer;
    if (lpointer < rpointer)
      return -1;
    else if (lpointer > rpointer)
      return +1;
    return 0;
  }

  static inline int
  cmp(const CLASS* lpointer, const SmartPointer<CLASS>& rhs)
  {
    CLASS* rpointer = rhs.self_pointer;
    if (lpointer < rpointer)
      return -1;
    else if (lpointer > rpointer)
      return +1;
    return 0;
  }

  template <typename TYPE>
  static inline int
  cmp(const SmartPointer<CLASS>& lhs, const TYPE* rhs)
  {
    CLASS* lpointer = lhs.self_pointer;
    CLASS* rpointer = static_cast<const CLASS*>(rhs);
    if (lpointer < rpointer)
      return -1;
    else if (lpointer > rpointer)
      return +1;
    return 0;
  }

  template <typename TYPE>
  static inline int
  cmp(const TYPE* lhs, const SmartPointer<CLASS>& rhs)
  {
    CLASS* lpointer = static_cast<const CLASS*>(lhs);
    CLASS* rpointer = rhs.self_pointer;
    if (lpointer < rpointer)
      return -1;
    else if (lpointer > rpointer)
      return +1;
    return 0;
  }

  static inline int
  cmp(const SmartPointer<CLASS>& object, const NullPointer&)
  {
    CLASS* pointer = object.self_pointer;
    if (!pointer)
      return 0;
    return +1;
  }

  static inline int
  cmp(const NullPointer&, const SmartPointer<CLASS>& object)
  {
    return ((!object) ? 0 : +1);
  }

  template <typename TYPE>
  static inline int
  cmp(const SmartPointer<CLASS>& lhs, const SmartPointer<TYPE>& rhs)
  {
    CLASS* lpointer = lhs.self_pointer;
    CLASS* rpointer = static_cast<const CLASS*>(rhs.self_pointer);
    if (lpointer < rpointer)
      return -1;
    else if (lpointer > rpointer)
      return +1;
    return 0;
  }

  template <typename TYPE>
  static inline int
  cmp(const SmartPointer<TYPE>& lhs, const SmartPointer<TYPE>& rhs)
  {
    CLASS* lpointer = static_cast<const CLASS*>(lhs.self_pointer);
    CLASS* rpointer = rhs.self_pointer;
    if (lpointer < rpointer)
      return -1;
    else if (lpointer > rpointer)
      return +1;
    return 0;
  }

  template <typename TYPE>
  friend inline bool
  operator<(const SmartPointer<CLASS>& lhs, TYPE rhs)
  {
    return (SmartPointer::cmp(lhs, rhs) < 0);
  }

  template <typename TYPE>
  friend inline bool
  operator<(TYPE lhs, const SmartPointer<CLASS>& rhs)
  {
    return (SmartPointer::cmp(lhs, rhs) < 0);
  }

  template <typename TYPE>
  friend inline bool
  operator<=(const SmartPointer<CLASS>& lhs, TYPE rhs)
  {
    return (SmartPointer::cmp(lhs, rhs) <= 0);
  }

  template <typename TYPE>
  friend inline bool
  operator<=(TYPE lhs, const SmartPointer<CLASS>& rhs)
  {
    return (SmartPointer::cmp(lhs, rhs) <= 0);
  }

  template <typename TYPE>
  friend inline bool
  operator==(const SmartPointer<CLASS>& lhs, TYPE rhs)
  {
    return (SmartPointer::cmp(lhs, rhs) == 0);
  }

  template <typename TYPE>
  friend inline bool
  operator==(TYPE lhs, const SmartPointer<CLASS>& rhs)
  {
    return (SmartPointer::cmp(lhs, rhs) == 0);
  }

  template <typename TYPE>
  friend inline bool
  operator!=(const SmartPointer<CLASS>& lhs, TYPE rhs)
  {
    return (SmartPointer::cmp(lhs, rhs) != 0);
  }

  template <typename TYPE>
  friend inline bool
  operator!=(TYPE lhs, const SmartPointer<CLASS>& rhs)
  {
    return (SmartPointer::cmp(lhs, rhs) != 0);
  }

  template <typename TYPE>
  friend inline bool
  operator>=(const SmartPointer<CLASS>& lhs, TYPE rhs)
  {
    return (SmartPointer::cmp(lhs, rhs) >= 0);
  }

  template <typename TYPE>
  friend inline bool
  operator>=(TYPE lhs, const SmartPointer<CLASS>& rhs)
  {
    return (SmartPointer::cmp(lhs, rhs) >= 0);
  }

  template <typename TYPE>
  friend inline bool
  operator>(const SmartPointer<CLASS>& lhs, TYPE rhs)
  {
    return (SmartPointer::cmp(lhs, rhs) > 0);
  }

  template <typename TYPE>
  friend inline bool
  operator>(TYPE lhs, const SmartPointer<CLASS>& rhs)
  {
    return (SmartPointer::cmp(lhs, rhs) > 0);
  }


  // Special functions
  CLASS&
  operator*() const
  {
    if (!self_pointer)
      // throw MemoryError("null pointer dereferencing");
      throw;
    return *self_pointer;
  }

  CLASS*
  operator->() const
  {
    if (!self_pointer)
      // throw MemoryError("null pointer dereferencing");
      throw;
    return self_pointer;
  }


  // Other functions
  inline CLASS*
  pointer() const
  {
    return self_pointer;
  }

  inline size_t
  count() const
  {
    return self_counter;
  }

  inline void
  reset()
  {
    this->release();
  }

  inline void
  reset(CLASS* pointer)
  {
    if (!pointer || (self_pointer != pointer))
      // throw MemoryError("automatical smart pointer reset");
      throw;
    this->release();
    this->acquire(pointer);
  }

  inline bool
  valid() const
  {
    return (self_pointer && self_counter);
  }

  inline bool
  unique() const
  {
    return (self_counter == 1);
  }
private:
  inline void
  acquire(CLASS* pointer)
  {
    self_counter.acquire(pointer);
    self_pointer = pointer;
  }

  inline void
  release()
  {
    self_counter.release(self_pointer);
    self_pointer = 0;
  }
}; // class SmartPointer


} // namespace quirinus
#endif // QUIRINUS_CORE_POINTERS_SMARTPOINTER_HPP
