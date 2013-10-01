/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_FILESYSTEM_FILEPATH_HPP
#define QUIRINUS_FILESYSTEM_FILEPATH_HPP
namespace quirinus {


struct VirtualPath: public Object
{
public:
  byte* self_path;
  PathAPI self_api;
public:
  typedef uint64_t dev_type;   // ID of device containing the file
  typedef uint64_t ino_type;   // Serial number for the file
  typedef uint32_t mode_type;  // Access mode and file type for the file
  typedef uint64_t nlink_type; // Number of links to the file
  typedef uint32_t uid_t;      // User ID of file owner
  typedef uint32_t gid_t;      // Group ID of file owner
  typedef uint64_t rdev_type;  // Device ID (if the file is device)
  typedef int64_t blkcnt_type; // 
  typedef uint64_t off_t;
  typedef int32_t pid_t;
  typedef signed long int __clock_t;
  typedef unsigned long int __rlim_t;
  typedef unsigned long int __rlim64_t;
  typedef unsigned int __id_t;
  typedef signed long int __time_t;
  typedef unsigned int __useconds_t;
  typedef uint64_t suseconds_t;
  typedef struct { int __val[2]; } __fsid_t;
}
