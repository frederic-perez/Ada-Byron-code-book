#include <string>

#include "aux-raw.hpp"
#include "log.hpp"
#include "preprocessor-pool.hpp"

namespace ABcb = Ada_Byron_code_book;
using ABcb::raw::pad;

void
ABcb::spy::LogListOfPreprocessorDefines()
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

  B_LOG_INFO << "List of preprocessor defines:";
  B_LOG_INFO << std::boolalpha << pad << "defined(__clang__): " << definedClang;
  B_LOG_INFO << pad << "defined(WIN32): " << definedWIN32;
  B_LOG_INFO << pad << "defined(_WIN32): " << defined_WIN32;
  B_LOG_INFO << pad << "defined(_WIN64): " << defined_WIN64;
  B_LOG_INFO << pad << "defined(macintosh): " << defined_macintosh;
  B_LOG_INFO << pad << "defined(__APPLE__): " << defined_APPLE;
  B_LOG_INFO << pad << "defined(__APPLE_CC__): " << defined_APPLE_CC;
  B_LOG_INFO << pad << "defined(NDEBUG): " << definedNDEBUG;
#ifdef __GNUG__
  B_LOG_INFO << pad << "__GNUG__ = " << __GNUG__;
#endif
#ifdef _MSC_VER
  B_LOG_INFO << pad << "_MSC_VER = " << _MSC_VER;
#endif
#ifdef ADA_BYRON__GNUGPP_VERSION
  B_LOG_INFO << pad << "ADA_BYRON__GNUGPP_VERSION = " << ADA_BYRON__GNUGPP_VERSION;
#endif
}
