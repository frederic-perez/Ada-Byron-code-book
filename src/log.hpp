#ifndef ADA_BYRON_CODE_BOOK__LOG_HPP
#define ADA_BYRON_CODE_BOOK__LOG_HPP

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

#endif // ADA_BYRON_CODE_BOOK__LOG_HPP
