/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_FILESYSTEM_SYMLINK_HPP
#define QUIRINUS_FILESYSTEM_SYMLINK_HPP
#include "FilePath.hpp"
namespace quirinus {
namespace filesystem {


inline void
symlink(const FilePath& src, const FilePath& dest)
{
#if !defined(QUIRINUS_PLATFORM_WINDOWS)
  int state = 0;
  state = ::symlink(src, dest);
  state = (!state) ? 0 : errno;
#else
  DWORD state = 0;
  typedef int (*SymbolicLinkA) (
    const char* src,
    const char* dest,
    uint32_t flags
  ); // WinANSI symbolic link
  typedef int (*SymbolicLinkW) (
    const wchar_t* src,
    const wchar_t* dest,
    uint32_t flags
  ); // WinWide symbolic link

  // Access required privileges.
  HANDLE token;
  TOKEN_PRIVILEGES tp;
  state = ::OpenProcessToken(
    ::GetCurrentProcess(),
    TOKEN_ADJUST_PRIVILEGES,
    &token
  ); // Open access token
  state = (!state) ? ::GetLastError() : 0;
  if (state)
    throw SystemError(state);
  state = ::LookupPrivilegeValueA(
    NULL,
    "SeCreateSymbolicLinkPrivilege",
    &tp.Privileges[0].Luid
  ); // Retrieve LUID
  state = (!state) ? ::GetLastError() : 0;
  if (state)
    throw SystemError(state);
  tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
  tp.PrivilegeCount = 1;
  state = ::AdjustTokenPrivileges(
    token,        // token handle
    false,        // disable all privileges
    &tp,          // pointer to new privileges
    0,            // previous old privileges size
    NULL,         // pointer to old privileges
    NULL);        // returned length
  state = (!state) ? ::GetLastError() : 0;
  if (state)
    throw SystemError(state);
  state = ::CloseHandle(token);
  state = (!state) ? ::GetLastError() : 0;
  if (state)
    throw SystemError(state);

  // Dynamic function import.
  HMODULE kernel = ::GetModuleHandle("kernel32.dll");
  state = (!kernel) ? ::GetLastError() : 0;
  if (state)
    throw SystemError(state);
  SymbolicLinkA link_ansi = \
    (SymbolicLinkA)::GetProcAddress(kernel, "CreateSymbolicLinkA");
  SymbolicLinkW link_wide = \
    (SymbolicLinkW)::GetProcAddress(kernel, "CreateSymbolicLinkW");
  if (!link_ansi || !link_wide)
    throw SupportError("symbolic links are not supported");
  if (src.api() != dest.api())
    state = link_ansi(src, dest, dest.isdir());
  else if (src.api() == filesystem::API::WINWIDE)
    state = link_wide(src, dest, dest.isdir());
  else
    state = link_ansi(src, dest, dest.isdir());
  state = (!state) ? ::GetLastError() : 0;
#endif
  if (state)
    throw SystemError(state);
}


} // namespace filesystem
} // namespace quirinus
#endif // QUIRINUS_FILESYSTEM_SYMLINK_HPP
