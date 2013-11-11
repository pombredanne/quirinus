/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_SYSTEM_SYSINFO_HPP
#define QUIRINUS_CORE_SYSTEM_SYSINFO_HPP
namespace quirinus {


/**
 * @struct sysinfo
 * @brief System information structure.
 * 
 * Quirinus entirely uses sysinfo structure to store system information.
 */
struct sysinfo
{
  /**
   * @var sysinfo::arch
   * System architecture (Intel x86, AMD64, etc.).
   */
  Bytes arch;


  /** 
   * @var sysinfo::byteorder
   * Byte order (+1 if big endian, -1 if little endian).
   */
  Int byteorder;


  /**
   * @var sysinfo::datamodel
   * Data model used entirely (LP32, ILP32, LP64, ILP64, LLP64).
   */
  Bytes datamodel;


  /**
   * @struct sysinfo::encoding
   * 
   * @var sysinfo::encoding::locale
   * Locale character set.
   * 
   * @var sysinfo::encoding::filesystem
   * File system character set.
   * 
   * @var sysinfo::encoding::stdin
   * Standart input stream character set.
   * 
   * @var sysinfo::encoding::stdout
   * Standart output stream character set.
   */
  struct encoding {
    Bytes locale;
    Bytes stdinstream;
    Bytes stdoutstream;
    Bytes stderrstream;
    Bytes filesystem;
  } encoding;


  /**
   * @struct sysinfo::library
   * 
   * @var sysinfo::library::author
   * Quirinus library author.
   * 
   * @var sysinfo::library::license
   * Quirinus library Open Source license.
   * 
   * @var sysinfo::library::version_major
   * Quirinus library major version number.
   * 
   * @var sysinfo::library::version_minor
   * Quirinus library minor version number.
   * 
   * @var sysinfo::library::version_micro
   * Quirinus library micro version number.
   */
  struct library {
    Bytes author;
    Bytes license;
    Int version_major;
    Int version_minor;
    Int version_micro;
  } library;


  /**
   * @struct sysinfo::uname
   * 
   * @var sysinfo::uname::platform
   * Currently used platform (Unix, BSD, Windows).
   * 
   * @var sysinfo::uname::system
   * Operating system name (GNU/Linux, Windows, FreeBSD, etc.).
   * 
   * @var sysinfo::uname::edition
   * Operating system edition (Linux distribution or Windows edition).
   * 
   * @var sysinfo::uname::version_major
   * Kernel major version number (default is 1).
   * 
   * @var sysinfo::uname::version_minor
   * Kernel minor version number (default is 0).
   * 
   * @var sysinfo::uname::version_micro
   * Kernel micro version number (default is 0).
   */
  struct uname {
    Bytes platform;
    Bytes system;
    Bytes edition;
    Int version_major;
    Int version_minor;
    Int version_micro;
  } uname;
};


void
sysinfo(struct sysinfo*);


} // namespace quirinus
#endif // QUIRINUS_CORE_SYSTEM_SYSINFO_HPP
