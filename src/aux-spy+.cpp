#include <chrono>
#include <iomanip>
#include <sstream>
#include <type_traits>

#include <boost/date_time/c_local_time_adjustor.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/preprocessor.hpp>
#include <boost/version.hpp>

#include "aux-raw.h" // for pad
#include "aux-spy+.h"
#include "preprocessor-pool.h"

namespace ABcb = Ada_Byron_code_book;

std::string
ABcb::spy::GetBoostVersion()
{
  std::ostringstream oss;
  oss << BOOST_VERSION / 100000 << '.' // major version
    << BOOST_VERSION / 100 % 1000 << '.' // minor version
    << BOOST_VERSION % 100; // patch level
  return oss.str();
}

std::string
ABcb::spy::GetClangVersion()
{
  std::ostringstream oss;
  oss
#ifdef __clang__
    << __clang_version__;
  //<< __clang_major__ << '.'
  //<< __clang_minor__ << '.'
  //<< __clang_patchlevel__
#else
    << "[not applicable]";
#endif
  return oss.str();
}

std::string
ABcb::spy::GetGNUGppVersion()
{
  std::ostringstream oss;
  oss
#ifdef ADA_BYRON__GNUGPP_VERSION
    << ADA_BYRON__GNUGPP_VERSION / 10000 << '.' // major version
    << ADA_BYRON__GNUGPP_VERSION / 100 % 100 << '.' // minor version
    << ADA_BYRON__GNUGPP_VERSION % 100; // patch level
#else
    << "[not applicable]";
#endif
  return oss.str();
}

std::string
ABcb::spy::GetVisualStudioCppCompilerVersion()
{
  std::ostringstream oss;
  oss
#ifdef _MSC_VER
    // See https://en.wikipedia.org/wiki/Visual_C%2B%2B for the "conversion"
    << _MSC_VER << " (Visual Studio "
#  if _MSC_VER >= 1930
    << 2022
#  elif _MSC_VER >= 1920
    << 2019
#  elif _MSC_VER >= 1910
    << 2017
#  elif _MSC_VER == 1900
    << 2015
#  elif _MSC_VER == 1800
    << 2013
#  elif _MSC_VER == 1700
    << 2012
#  elif _MSC_VER == 1600
    << 2010
#  elif _MSC_VER == 1500
    << 2008
#  else
    << "older than 2008"
#  endif
    << ")";
#else
    << "[not applicable]";
#endif
  return oss.str();
}

namespace {

auto
GetHostName()
-> std::string
{
#ifdef _MSC_VER
#  pragma warning(disable : 4996) // This function or variable may be unsafe
#endif

#if defined(WIN32)
  //
  // This block is meant for vs10 or MinGW's g++
  //
  const char* hostname = getenv("HOSTNAME");
  if (hostname != nullptr) {
    return hostname; // iff hostname != nullptr, it can be converted to string
  }

  hostname = getenv("COMPUTERNAME");
  if (hostname != nullptr) {
    return hostname; // iff like above
  }

  return "UNKNOWN";
#else
  //
  // This block is meant only for Linux and g++
  //
  char hostname[1024];
  hostname[1023] = '\0';
  gethostname(hostname, 1023);
  return hostname;
#endif
}

} // namespace

std::string
ABcb::spy::GetUserName()
{
  const char* username = getenv("USER");
  if (username != nullptr) {
    return username; // iff username != nullptr, it can be converted to string
  }

  username = getenv("USERNAME");
  return username != nullptr ? username : "unknown-username"; // iff like above
}

std::string
ABcb::spy::GetLocalDate()
{
  namespace pt = boost::posix_time;
  const pt::ptime now = pt::second_clock::local_time();

  std::ostringstream oss;
  const pt::ptime::date_type date = now.date();
  oss << date.day_of_week() << ", " << date.month() << ' ' << date.day() << ", " << date.year();
  return oss.str();
}

std::string
ABcb::spy::GetLocalTime()
{
  namespace pt = boost::posix_time;

  // From
  // https://thispointer.com/get-current-date-time-in-c-example-using-boost-date-time-library/
  const auto now = pt::second_clock::local_time();
  std::ostringstream oss;
  oss << now.time_of_day();

  return oss.str();
}

namespace {

using ABcb::raw::pad;

template <class T>
auto
Range(std::ostream& a_os)
-> std::ostream&
{
  static_assert(
    not std::is_same<T, char>::value,
    "Cannot instantiate with char (use Range_CastingToInt<T> instead)");
  static_assert(
    std::is_scalar<T>::value
    or false == std::numeric_limits<T>::is_integer,
    "Template parameter T is neither arithmetic nor floating point");
  a_os << "Range of `" << typeid(T).name()
       << "` = [" << boost::numeric::bounds<T>::lowest() << ", " << boost::numeric::bounds<T>::highest() << ']'
       << std::flush;
  return a_os;
}

template <class T>
auto
Range_CastingToInt(std::ostream& a_os)
-> std::ostream&
{
  static_assert(
    std::is_scalar<T>::value or true == std::numeric_limits<T>::is_integer,
    "Template parameter T is not suitable");
  a_os << "Range of `" << typeid(T).name()
       << "` (casting to int) = [" << boost::numeric_cast<int>(boost::numeric::bounds<T>::lowest()) << ", "
       << boost::numeric_cast<int>(boost::numeric::bounds<T>::highest()) << ']' << std::flush;
  return a_os;
}

} // namespace

void
ABcb::spy::LogInfoOfSomeTypes()
{
  BOOST_LOG_TRIVIAL(info) << "Info of some types:";
  BOOST_LOG_TRIVIAL(info) << pad << "sizeof(char) = " << sizeof(char) << " | " << Range_CastingToInt<char>;
  BOOST_LOG_TRIVIAL(info) << pad << "sizeof(wchar_t) = " << sizeof(wchar_t) << " | " << Range<wchar_t>;
  BOOST_LOG_TRIVIAL(info) << pad << "sizeof(char16_t) = " << sizeof(char16_t) << " | " << Range<char16_t>;
  BOOST_LOG_TRIVIAL(info) << pad << "sizeof(char32_t) = " << sizeof(char32_t) << " | " << Range<char32_t>;
  BOOST_LOG_TRIVIAL(info) << pad << "sizeof(int) = " << sizeof(int) << " | " << Range<int>;
  BOOST_LOG_TRIVIAL(info) << pad << "sizeof(short int) = " << sizeof(short int) << " | " << Range<short int>;
  BOOST_LOG_TRIVIAL(info) << pad << "sizeof(int64_t) = " << sizeof(int64_t) << " | " << Range<int64_t>;
  BOOST_LOG_TRIVIAL(info) << pad << "sizeof(float) = " << sizeof(float) << " | " << Range<float>;
  BOOST_LOG_TRIVIAL(info) << pad << "sizeof(double) = " << sizeof(double) << " | " << Range<double>;
  BOOST_LOG_TRIVIAL(info) << pad << "sizeof(long double) = " << sizeof(long double) << " | " << Range<long double>;
  BOOST_LOG_TRIVIAL(info) << pad << "sizeof(size_t) = " << sizeof(size_t) << " | " << Range<size_t>;
  BOOST_LOG_TRIVIAL(info) << pad << "sizeof(unsigned int) = " << sizeof(unsigned int) << " | " << Range<unsigned int>;
  BOOST_LOG_TRIVIAL(info) << pad << "sizeof(unsigned short) = " << sizeof(unsigned short) << " | " << Range<unsigned short>;
  BOOST_LOG_TRIVIAL(info) << pad << "sizeof(unsigned long) = " << sizeof(unsigned long) << " | " << Range<unsigned long>;
  BOOST_LOG_TRIVIAL(info) << pad << "sizeof(uint64_t) = " << sizeof(uint64_t) << " | " << Range<uint64_t>;
  using boost::multiprecision::cpp_dec_float_50;
  BOOST_LOG_TRIVIAL(info) << pad << "sizeof(boost::multiprecision::cpp_dec_float_50) = " << sizeof(cpp_dec_float_50) << " | " << Range<cpp_dec_float_50>;
}

namespace {

namespace bf = boost::filesystem;

void
LogArgv0Info(const std::string& a_argv0)
{
  const bf::path fullArgv0 = bf::system_complete(bf::canonical(bf::path(a_argv0, nullptr)));

  BOOST_LOG_TRIVIAL(info) << "The full argv[0]:";
  BOOST_LOG_TRIVIAL(info) << pad << "is " << fullArgv0 << ",";
  std::ostringstream oss;
  if (bf::exists(fullArgv0)) {
    oss << "which is" << (bf::is_regular(fullArgv0) ? "" : " not") << " a regular file, created by ";
#if defined(CMAKE_MYUSERNAME)
    oss << BOOST_PP_STRINGIZE(CMAKE_MYUSERNAME);
#else
    oss << '?';
#endif
    oss << ", at ";
#if defined(CMAKE_MYHOSTNAME)
    oss << BOOST_PP_STRINGIZE(CMAKE_MYHOSTNAME);
#else
    oss << '?';
#endif
    oss << ',';

    // Day of the week, month, day, year
    //
    const std::time_t theTime_t = bf::last_write_time(fullArgv0);
    namespace pt = boost::posix_time;
    const pt::ptime thePtime =
      // pt::from_time_t(theTime_t); <-- Does not work properly for Darwin
      // Solution from http://stackoverflow.com/questions/6143569/
      //   how-to-get-a-local-date-time-from-a-time-t-with-boostdate-time
      boost::date_time::c_local_adjustor<pt::ptime>::utc_to_local(pt::from_time_t(theTime_t));
    const pt::ptime::date_type date = thePtime.date();
    oss << " on " << date.day_of_week() << ", " << date.month() << ' ' << date.day() << ", " << date.year();

    // Hours, minutes and seconds
    //
    oss << ", at " << thePtime.time_of_day();
  } else {
    oss << "(which does not seem to exist)";
  }
  BOOST_LOG_TRIVIAL(info) << pad << oss.str();
}

std::string
GetCurrentDirInfo()
{
  const std::string dot = ".";
  const bf::path currentDir(dot);
  const bf::path fullPathCD = bf::system_complete(bf::canonical(dot));
  std::ostringstream oss;
  oss << "The full path of the current directory is " << fullPathCD;
  return oss.str();
}

} // namespace

void
ABcb::spy::RunInfo::Log() const
{
  BOOST_LOG_TRIVIAL(info)
    << d_progname << " was launched by " << GetUserName() << " at " << GetHostName()
    << " on " << GetLocalDate() << ", at " << GetLocalTime();
  LogArgv0Info(d_argv0);
  BOOST_LOG_TRIVIAL(info) << GetCurrentDirInfo();
  BOOST_LOG_TRIVIAL(info) << "Using Boost version " << GetBoostVersion();
  BOOST_LOG_TRIVIAL(info) << "Using Clang version " << GetClangVersion();
  BOOST_LOG_TRIVIAL(info) << "Using GNU g++ version " << GetGNUGppVersion();
  BOOST_LOG_TRIVIAL(info) << "Using Visual Studio C/C++ compiler version " << GetVisualStudioCppCompilerVersion();
  LogListOfPreprocessorDefines();
  LogInfoOfSomeTypes();
  BOOST_LOG_TRIVIAL(info) << "";
}

template <typename TClock>
auto
ABcb::spy::Timer<TClock>::Elapsed() const
-> typename TClock::duration
{
  return TClock::now() - d_start;
}

template <typename TClock>
auto
ABcb::spy::Timer<TClock>::Seconds() const
-> double
{
  return static_cast<double>(Elapsed().count()) * ((double)TClock::period::num / TClock::period::den);
}

template <typename TClock>
auto
ABcb::spy::Timer<TClock>::Seconds(size_t precision) const
-> std::string
{
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(precision) << Seconds() << " seconds";
  return oss.str();
}

template <typename TClock>
void
ABcb::spy::Timer<TClock>::Reset()
{
  d_start = TClock::now();
}

// Other possible instantiations:
// - std::chrono::system_clock
// - std::chrono::steady_clock << GCC duplicate?
template class ABcb::spy::Timer<std::chrono::high_resolution_clock>;
