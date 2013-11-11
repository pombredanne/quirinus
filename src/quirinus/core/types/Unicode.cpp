/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

namespace quirinus {


Unicode::Unicode(const Object& object)
{
  Unicode stack(object.cast_unicode());
  swap(*this, stack);
}


Bytes
Unicode::repr() const
{
  uint32_t code;
  unicodestack stack;
  char* buffer = new char[10];
  const unicode* head = NULL;
  const unicode* tail = NULL;
  head = &*self.begin();
  tail = &*self.end();
  for (; head < tail; ++head)
  {
    code = *head;
    if (code < 0x80)
    {
      if ((code == 0x00)  // \0
      ||  (code == 0x07)  // \a
      ||  (code == 0x08)  // \b
      ||  (code == 0x09)  // \t
      ||  (code == 0x0A)  // \n
      ||  (code == 0x0C)  // \f
      ||  (code == 0x0D)  // \r
      ||  (code == 0x22)  // \"
      ||  (code == 0x5C)) // \\;
      {
        stack.push_back('\\');
        if (code == 0x00)
          stack.push_back('0');
        else if (code == 0x07)
          stack.push_back('a');
        else if (code == 0x08)
          stack.push_back('b');
        else if (code == 0x09)
          stack.push_back('t');
        else if (code == 0x0A)
          stack.push_back('n');
        else if (code == 0x0C)
          stack.push_back('f');
        else if (code == 0x0D)
          stack.push_back('r');
        else if (code == 0x22)
          stack.push_back('"');
        else if (code == 0x5C)
          stack.push_back('\\');
      }
      else
        stack.push_back(code);
    }
    else
    {
      ::memset(buffer, 0, 10);
      size_t count = ((code < 0xFFFF) ? 6 : 10);
      if (code < 0xFFFF)
        ::sprintf(buffer, "\\u%04x", code);
      else
        ::sprintf(buffer, "\\u%08x", code);
      for (size_t j = 0; j < count; ++j)
        stack.push_back(buffer[j]);
    }
  }
  if (!stack.size())
  {
    stack.reserve(1);
    stack.push_back(0);
  }
  delete[] buffer;
  head = &*stack.begin();
  tail = &*stack.end();
  return Bytes(head, tail);
}


Bool
Unicode::cast_bool() const
{ return (self.size()); }


Int
Unicode::cast_int() const
{
  Bytes stack(this->cast_bytes());
  return stack.cast_int();
}


Float
Unicode::cast_float() const
{
  Bytes stack(this->cast_bytes());
  return stack.cast_float();
}


Bytes
Unicode::cast_bytes() const
{ return Bytes(this->head(), this->tail()); }


Unicode
Unicode::cast_unicode() const
{ return Unicode(this->head(), this->tail()); }


} // namespace quirinus
