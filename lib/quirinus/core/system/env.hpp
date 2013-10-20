/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_SYSTEM_ENV_HPP
#define QUIRINUS_CORE_SYSTEM_ENV_HPP
namespace quirinus {


inline Bytes
env(const Bytes& variable)
{
  Bytes stack;
  char* varbuffer = variable.nullstr();
#if (QUIRINUS_FEATURE_POSIX)
  char* buffer = NULL;
  buffer = ::getenv(varbuffer);
  if (buffer)
    stack = buffer;
#else
  size_t size = 32;
  size_t xsize = 0;
  char* buffer = NULL;
  while (true)
  {
    buffer = new char[size];
    ::memset(buffer, 0, size);
    xsize = ::GetEnvironmentVariableA(varbuffer, buffer, size);
    if (xsize == 0)
    {
      delete[] buffer;
      DWORD state = ::GetLastError();
      if (state == ERROR_ENVVAR_NOT_FOUND)
        return stack;
      throw SystemError(state);
    }
    if (xsize < size)
      break;
    delete[] buffer;
    size *= 1.5;
  }
  stack = buffer;
  delete[] buffer;
#endif
  delete[] varbuffer;
  return stack;
}


inline void
env(const Bytes& variable, const Bytes& value)
{
  Bytes xvalue = env(variable);
  char* varbuffer = variable.nullstr();
  char* valbuffer = value.nullstr();
  char* xvalbuffer = xvalue.nullstr();
#if (QUIRINUS_FEATURE_POSIX)
  int state = 0;
  state = ::setenv(varbuffer, valbuffer, true);
  if (state)
  {
    state = static_cast<int>(errno);
    ::setenv(varbuffer, xvalbuffer, true);
    throw SystemError(state);
  }
#else
  DWORD state = 0;
  state = ::SetEnvironmentVariableA(varbuffer, valbuffer);
  state = (!state) ? ::GetLastError() : 0;
  if (state)
  {
    state = ::GetLastError();
    ::SetEnvironmentVariableA(varbuffer, xvalbuffer);
    throw SystemError(state);
  }
#endif
  delete[] varbuffer;
  delete[] valbuffer;
  delete[] xvalbuffer;
}


} // namespace quirinus
#endif // QUIRINUS_CORE_SYSTEM_ENV_HPP
