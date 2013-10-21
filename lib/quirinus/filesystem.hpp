/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_FILESYSTEM_HPP
#define QUIRINUS_FILESYSTEM_HPP
#include "core.hpp"
#include "codecs.hpp"

#if !defined(S_IFLNK)
  #define S_IFLNK 0120000
#endif

#if !defined(S_IFSOCK)
  #define S_IFSOCK 0140000
#endif

#include "filesystem/Path.hpp"
#include "filesystem/FilePath.hpp"
#include "filesystem/VirtualPath.hpp"
// #include "filesystem/Walker.hpp"
#include "filesystem/cwd.hpp"
#include "filesystem/executable.hpp"
#include "filesystem/link.hpp"
#include "filesystem/mkdir.hpp"
#include "filesystem/rmdir.hpp"
#include "filesystem/rmfile.hpp"
#include "filesystem/symlink.hpp"
#endif // QUIRINUS_FILESYSTEM_HPP
