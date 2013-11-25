/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#include <quirinus/core.hpp>
#include <quirinus/codecs.hpp>
#include <quirinus/stream.hpp>
namespace quirinus {
namespace stream {


ConsoleInputStream stdin_default;
ConsoleOutputStream stdout_default;
ConsoleErrorStream stderr_default;
IOStream stdin = stdin_default;
IOStream stdout = stdout_default;
IOStream stderr = stderr_default;


} // namespace stream
} // namespace quirinus
