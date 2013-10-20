/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

namespace quirinus {

Bytes::Bytes(const Object& object)
{
  Bytes stack(object.cast_bytes());
  swap(*this, stack);
}


Bytes
Bytes::repr() const
{
  bytechar code = 0;
  bytecharstack stack;
  char* buffer = new char[4];
  bytecharstack::const_iterator iter = self.begin();
  bytecharstack::const_iterator tail = self.end();
  while (iter < tail)
  {
    code = *iter;
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
      ::sprintf(buffer, "\\x%02x", code);
      for (size_t j = 0; j < 4; ++j)
        stack.push_back(buffer[j]);
    }
    ++iter;
  }
  delete[] buffer;
  return Bytes(stack.begin(), stack.end());
}


Bool
Bytes::cast_bool() const
{
  return (!!self.size());
}


Int
Bytes::cast_int() const
{
  mpz_t operand;
  int state = 0;
  ::mpz_init(operand);
  char* buffer = this->nullstr();
  state = ::mpz_set_str(operand, buffer, 10);
  if (state != 0)
  {
    delete[] buffer;
    ::mpz_clear(operand);
    throw CastError("int casting failed");
  }
  Int stack(operand);
  ::mpz_clear(operand);
  delete[] buffer;
  return stack;
}


Float
Bytes::cast_float() const
{
  return 1.0;
}


Bytes
Bytes::cast_bytes() const
{
  return Bytes(self.begin(), self.end());
}


Unicode
Bytes::cast_unicode() const
{
  return Unicode(self.begin(), self.end());
}

} // namespace quirinus
