/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_STREAM_INPUT_HPP
#define QUIRINUS_STREAM_INPUT_HPP
namespace quirinus {
namespace stream {


Unicode
input(const char& delimiter = '\n',
      const bool& password = false);


} // namespace stream
} // namespace quirinus
#endif // QUIRINUS_STREAM_INPUT_HPP
