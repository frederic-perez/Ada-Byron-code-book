// --

#include <string>

#include "aux-raw.h"
#include "preprocessor-pool.h"

namespace ABcb = Ada_Byron_code_book;
using ABcb::raw::pad;

std::ostream&
ABcb::spy::ListOfPreprocessorDefines(std::ostream& a_os)
{
  const bool definedClang =
#ifdef __clang__
    true;
#else
    false;
#endif
  const bool definedWIN32 =
#if defined(WIN32)
    true;
#else
    false;
#endif
  const bool defined_WIN32 =
#if defined(_WIN32)
    true;
#else
    false;
#endif
  const bool defined_WIN64 =
#if defined(_WIN64)
    true;
#else
    false;
#endif
  const bool defined_macintosh =
#if defined(macintosh)
    true;
#else
    false;
#endif
  const bool defined_APPLE =
#if defined(__APPLE__)
    true;
#else
    false;
#endif
  const bool defined_APPLE_CC =
#if defined(__APPLE_CC__)
    true;
#else
    false;
#endif
  const bool definedNDEBUG =
#if defined(NDEBUG)
    true;
#else
    false;
#endif

  return a_os << std::boolalpha << pad << "defined(__clang__): " << definedClang << '\n'
              << pad << "defined(WIN32): " << definedWIN32 << '\n'
              << pad << "defined(_WIN32): " << defined_WIN32 << '\n'
              << pad << "defined(_WIN64): " << defined_WIN64 << '\n'
              << pad << "defined(macintosh): " << defined_macintosh << '\n'
              << pad << "defined(__APPLE__): " << defined_APPLE << '\n'
              << pad << "defined(__APPLE_CC__): " << defined_APPLE_CC << '\n'
              << pad << "defined(NDEBUG): " << definedNDEBUG << '\n'
#ifdef __GNUG__
              << pad << "__GNUG__ = " << __GNUG__ << '\n'
#endif
#ifdef _MSC_VER
              << pad << "_MSC_VER = " << _MSC_VER << '\n'
#endif
#ifdef ADA_BYRON__GNUGPP_VERSION
              << pad << "ADA_BYRON__GNUGPP_VERSION = " << ADA_BYRON__GNUGPP_VERSION << '\n'
#endif
              << std::flush;
}

// -- eof
