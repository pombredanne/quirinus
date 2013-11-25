/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_FILESYSTEM_HPP
#define QUIRINUS_FILESYSTEM_HPP
#include "core.hpp"
#include "codecs.hpp"

#if !defined(S_IFBLK)
  #define S_IFBLK 0060000
#endif

#if !defined(S_IFLNK)
  #define S_IFLNK 0120000
#endif

#if !defined(S_IFSOCK)
  #define S_IFSOCK 0140000
#endif

// The uniform system limit (if any) for the length of a file name component.
#if !defined(QUIRINUS_FILESYSTEM_NAME_MAX)
  #if defined(NAME_MAX)
    #define QUIRINUS_FILESYSTEM_NAME_MAX NAME_MAX
  #elif defined(MAXNAMLEN)
    #define QUIRINUS_FILESYSTEM_NAME_MAX MAXNAMLEN
  #else
    #define QUIRINUS_FILESYSTEM_NAME_MAX 255
  #endif
#endif

// The uniform system limit (if any) for the length of an entire file name.
#if !defined(QUIRINUS_FILESYSTEM_PATH_MAX)
  #if !defined(QUIRINUS_PLATFORM_WINDOWS)
    #if defined(QUIRINUS_SYSTEM_HPUX)
      #define QUIRINUS_FILESYSTEM_PATH_MAX 1024
    #elif defined(PATH_MAX)
      #define QUIRINUS_FILESYSTEM_PATH_MAX PATH_MAX
    #else
      #define QUIRINUS_FILESYSTEM_PATH_MAX 255
    #endif
  #else
    #define QUIRINUS_FILESYSTEM_PATH_MAX 260
  #endif
#endif

// The uniform system limit (if any) for the number of names for a given file.
#if !defined(QUIRINUS_FILESYSTEM_LINK_MAX)
  #if defined(LINK_MAX)
    #define QUIRINUS_FILESYSTEM_LINK_MAX LINK_MAX
  #else
    #define QUIRINUS_FILESYSTEM_LINK_MAX 8
  #endif
#endif

// The uniform system limit for how many symlinks functions may follow.
#if !defined(QUIRINUS_FILESYSTEM_SYMLINK_MAX)
  #if defined(MAXSYMLINKS)
    #define QUIRINUS_FILESYSTEM_SYMLINK_MAX MAXSYMLINKS
  #endif
#endif

// Windows SYMBOLIC_LINK_FLAG_DIRECTORY fix.
#if defined(QUIRINUS_PLATFORM_WINDOWS)
  #if !defined(SYMBOLIC_LINK_FLAG_DIRECTORY)
    #define SYMBOLIC_LINK_FLAG_DIRECTORY 0x01
  #endif
#endif

#include "filesystem/Path.hpp"
#include "filesystem/FilePath.hpp"
#include "filesystem/VirtualPath.hpp"
#include "filesystem/Walker.hpp"
#include "filesystem/cwd.hpp"
#include "filesystem/executable.hpp"
#include "filesystem/link.hpp"
#include "filesystem/mkdir.hpp"
#include "filesystem/rmdir.hpp"
#include "filesystem/rmfile.hpp"
#include "filesystem/symlink.hpp"
#endif // QUIRINUS_FILESYSTEM_HPP
