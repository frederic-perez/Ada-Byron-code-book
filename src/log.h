#pragma once
// '- This pragma works for
// - Windows 8.1:
//   - Visual Studio 2013 (vs12)
// - Ubuntu (virtual machine):
//   - g++ 4.8.2
//   - clang++ 3.4-1ubuntu3 (based on LLVM 3.4)
// - Apple OS X Yosemite
//   - Xcode 6.1 with Apple LLVM 6.0 (clang-600.0.54) (based on LLVM 3.5svn)

#include <boost/log/trivial.hpp>

#define B_LOG_TRACE   BOOST_LOG_TRIVIAL(trace)
#define B_LOG_DEBUG   BOOST_LOG_TRIVIAL(debug)
#define B_LOG_INFO    BOOST_LOG_TRIVIAL(info)
#define B_LOG_WARNING BOOST_LOG_TRIVIAL(warning)
#define B_LOG_ERROR   BOOST_LOG_TRIVIAL(error)
#define B_LOG_FATAL   BOOST_LOG_TRIVIAL(fatal)

#define B_LOG_TRACE_STARTED B_LOG_TRACE << __func__ << " started...";
#define B_LOG_TRACE_FINISHED B_LOG_TRACE << __func__ << " finished.";

//!? TODO: Possibly extend LogLine with Boost's PP for extra information

#define LogLine B_LOG_TRACE << "@@@@ " << __FILE__ << ':' << __func__ << ":L" << __LINE__;
