#include <string>

#include <boost/log/trivial.hpp>

#include "aux-raw.h"
#include "preprocessor-pool.h"

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

  BOOST_LOG_TRIVIAL(info) << "List of preprocessor defines:";
  BOOST_LOG_TRIVIAL(info) << std::boolalpha << pad << "defined(__clang__): " << definedClang;
  BOOST_LOG_TRIVIAL(info) << pad << "defined(WIN32): " << definedWIN32;
  BOOST_LOG_TRIVIAL(info) << pad << "defined(_WIN32): " << defined_WIN32;
  BOOST_LOG_TRIVIAL(info) << pad << "defined(_WIN64): " << defined_WIN64;
  BOOST_LOG_TRIVIAL(info) << pad << "defined(macintosh): " << defined_macintosh;
  BOOST_LOG_TRIVIAL(info) << pad << "defined(__APPLE__): " << defined_APPLE;
  BOOST_LOG_TRIVIAL(info) << pad << "defined(__APPLE_CC__): " << defined_APPLE_CC;
  BOOST_LOG_TRIVIAL(info) << pad << "defined(NDEBUG): " << definedNDEBUG;
#ifdef __GNUG__
  BOOST_LOG_TRIVIAL(info) << pad << "__GNUG__ = " << __GNUG__;
#endif
#ifdef _MSC_VER
  BOOST_LOG_TRIVIAL(info) << pad << "_MSC_VER = " << _MSC_VER;
#endif
#ifdef ADA_BYRON__GNUGPP_VERSION
  BOOST_LOG_TRIVIAL(info) << pad << "ADA_BYRON__GNUGPP_VERSION = " << ADA_BYRON__GNUGPP_VERSION;
#endif
}
