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
  uint8_t code;
  charstack stack;
  size_t size = self.size();
  char* buffer = new char[4];
  for (size_t i = 0; i < size; ++i)
  {
    code = self[i];
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
      sprintf(buffer, "\\x%02x", code);
      stack.push_back(buffer[0]);
      stack.push_back(buffer[1]);
      stack.push_back(buffer[2]);
      stack.push_back(buffer[3]);
    }
  }
  delete[] buffer;
  return Bytes(stack.begin(), stack.end());
}


Bool
Unicode::cast_bool() const
{
  return (!!self.size());
}


Int
Unicode::cast_int() const
{
  // pass
}


Float
Unicode::cast_float() const
{
  // pass
}


Bytes
Unicode::cast_bytes() const
{
  return Bytes(self.begin(), self.end());
}


Unicode
Unicode::cast_unicode() const
{
  return Unicode(self.begin(), self.end());
}

} // namespace quirinus
