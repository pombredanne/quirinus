/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_STREAM_STDSTREAM_HPP
#define QUIRINUS_STREAM_STDSTREAM_HPP
namespace quirinus {
namespace stream {


extern ConsoleInputStream stdin_default;
extern ConsoleOutputStream stdout_default;
extern ConsoleErrorStream stderr_default;

extern IOStream stdin;
extern IOStream stdout;
extern IOStream stderr;


} // namespace stream
} // namespace quirinus
#endif // QUIRINUS_STREAM_STDSTREAM_HPP
