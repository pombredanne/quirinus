/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#ifndef QUIRINUS_CORE_CONFIG_INCLUDE_HPP
#define QUIRINUS_CORE_CONFIG_INCLUDE_HPP


// Large file support
#if !defined(_FILE_OFFSET_BITS)
  #define _FILE_OFFSET_BITS 64
#endif

// C standart library
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <limits.h>
#include <math.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// C++ standart library
#include <algorithm>
#include <exception>
#include <iostream>
#include <iomanip>
#include <limits>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <vector>

// Perl Compatible Regular Expressions
#if !defined(PCRE_STATIC)
  #define PCRE_STATIC
#endif
#include <pcre.h>

// GNU Multiprecision Library
#include <gmp.h>

// Multiple Precision Floating-Point Reliable Library
#include <mpfr.h>


#endif // QUIRINUS_CORE_CONFIG_INCLUDE_HPP
