/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#include <quirinus/core.hpp>
#include <quirinus/filesystem.hpp>
namespace quirinus {
namespace filesystem {


#if (QUIRINUS_FEATURE_POSIX)
const Bytes Path::SEP = "/";
const Bytes Path::ALTSEP = "";
const Bytes Path::PATHSEP = ":";
const Bytes Path::DEVNULL = "/dev/null";
#else
const Bytes Path::SEP = "\\";
const Bytes Path::ALTSEP = "/";
const Bytes Path::PATHSEP = ";";
const Bytes Path::DEVNULL = "NUL";
#endif
const Bytes Path::CURDIR = ".";
const Bytes Path::PARDIR = "..";
const Bytes Path::EXTSEP = ".";


} // namespace filesystem
} // namespace quirinus
