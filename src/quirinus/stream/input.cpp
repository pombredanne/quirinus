/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#include <quirinus/core.hpp>
#include <quirinus/codecs.hpp>
#include <quirinus/stream.hpp>
namespace quirinus {
namespace stream {


Unicode
input(const char& delimiter,
      const bool& password)
{
  byte character = 0;
  struct sysinfo sys;
  sysinfo(&sys);
  Bytes encoding = sys.encoding.stdout;
  codecs::Codec* codec = codecs::lookup(encoding);
  std::vector<bytechar> stack;

  // Modify console settings.
#if (QUIRINUS_FEATURE_POSIX)
  int state = 0;
  struct termios console;
  int fileno = STDIN_FILENO;
  state = ::tcgetattr(fileno, &console);
  state = ((state) ? errno : 0);
  if (state)
    throw SystemError(state);
  console.c_lflag &= ~ICANON;
  if (password)
    console.c_lflag &= ~ECHO;
  console.c_cc[VTIME] = 0;
  console.c_cc[VMIN] = 1;
  state = ::tcsetattr(fileno, TCSANOW, &console);
  state = ((state) ? errno : 0);
  if (state)
    throw SystemError(state);
#else
  DWORD mode = 0;
  DWORD state = 0;
  HANDLE console = ::GetStdHandle(STD_INPUT_HANDLE);
  state = ::GetConsoleMode(console, &mode);
  state = ((!state) ? ::GetLastError() : 0);
  if (state)
    throw SystemError(state);
  if (password)
    mode &= ~ENABLE_ECHO_INPUT;
#endif

  // Read characters until delimiter.
  while (true)
  {
    character = ::getchar();
    if (character == delimiter)
      break;
    stack.push_back(character);
  }

  // Restore console settings.
#if (QUIRINUS_FEATURE_POSIX)
  console.c_lflag |= ICANON;
  if (password)
    console.c_lflag |= ECHO;
  state = ::tcsetattr(fileno, TCSADRAIN, &console);
  state = ((state) ? errno : 0);
  if (state)
    throw SystemError(state);
#else
  if (password)
    mode |= ENABLE_ECHO_INPUT;
  state = ::SetConsoleMode(console, mode);
  state = ((!state) ? ::GetLastError() : 0);
  if (state)
    throw SystemError(state);
#endif

  // Return result.
  const bytechar* head = &*stack.begin();
  const bytechar* tail = &*stack.end();
  Bytes bstring(head, tail);
  Unicode ustring = codec->decode(bstring);
  delete codec;
  return ustring;
}


} // namespace stream
} // namespace quirinus
