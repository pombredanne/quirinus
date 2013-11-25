/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#include <quirinus/core.hpp>
#include <quirinus/filesystem.hpp>
namespace quirinus {
namespace filesystem {


const Int Path::BLK = 0060000;
const Int Path::CHR = 0020000;
const Int Path::DIR = 0040000;
const Int Path::FIFO = 0010000;
const Int Path::LNK = 0120000;
const Int Path::FMT = 0170000;
const Int Path::REG = 0100000;
const Int Path::SOCK = 0140000;

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
