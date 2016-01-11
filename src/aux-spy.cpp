// -- 

#include <chrono>
#include <sstream>
#include <type_traits>

#include <boost/date_time/c_local_time_adjustor.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/preprocessor.hpp>
#include <boost/version.hpp>

#include "aux-spy.h"
#include "preprocessor-pool.h"

namespace ABcb = Ada_Byron_code_book;

std::ostream&
ABcb::spy::BoostVersion(std::ostream& a_os)
{
	return 
		a_os
			<< BOOST_VERSION / 100000 << '.'	// major version
			<< BOOST_VERSION / 100 % 1000 << '.'	// minor version
			<< BOOST_VERSION % 100	// patch level
			<< std::flush;
}

std::ostream&
ABcb::spy::ClangVersion(std::ostream& a_os)
{
	return
		a_os
#ifdef __clang__
		<< __clang_version__
		//<< __clang_major__ << '.'
		//<< __clang_minor__ << '.'
		//<< __clang_patchlevel__
#else
		<< "[not applicable]"
#endif
		<< std::flush;
}

std::ostream&
ABcb::spy::GNUGppVersion(std::ostream& a_os)
{
	return 
		a_os
#ifdef ADA_BYRON__GNUGPP_VERSION
			<< ADA_BYRON__GNUGPP_VERSION / 10000 << '.'	// major version
			<< ADA_BYRON__GNUGPP_VERSION / 100 % 100 << '.'	// minor version
			<< ADA_BYRON__GNUGPP_VERSION % 100	// patch level
#else
			<< "[not applicable]"
#endif
			<< std::flush;
}

std::ostream&
ABcb::spy::VisualStudioCppCompilerVersion(std::ostream& a_os)
{
	return
		a_os
#ifdef _MSC_VER
		// See https://en.wikipedia.org/wiki/Visual_C%2B%2B for the "conversion"
		<< _MSC_VER << " (Visual Studio "
	#if _MSC_VER == 1900
		<< 2015
	#elif _MSC_VER == 1800
		<< 2013
	#elif _MSC_VER == 1700
		<< 2012
	#elif _MSC_VER == 1600
		<< 2010
	#elif _MSC_VER == 1500
		<< 2008
	#else
		<< "older than 2008"
	#endif
		<< ")"
#else
		<< "[not applicable]"
#endif
		<< std::flush;
}

namespace {

std::string
GetHostName()
{
#ifdef _MSC_VER
	#pragma warning(disable : 4996) // This function or variable may be unsafe
#endif

#if defined(WIN32)
	//
	// This block is meant for vs10 or MinGW's g++
	//
	const char* hostname = getenv("HOSTNAME");
	if (hostname)
		return hostname;

	hostname = getenv("COMPUTERNAME");
	if (hostname)
		return hostname;

#ifdef _WINDOWS
#pragma warning(default : 4996) // This function or variable may be unsafe
#endif

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

std::ostream&
ABcb::spy::HostName(std::ostream& a_os)
{
	return a_os << GetHostName() << std::flush;
}

namespace {

std::string
GetUserName()
{
	const char* username = getenv("USER");
	if (username)
		return username;

	if (!username)
		username = getenv("USERNAME");
	return username ? username : "unknown-username";
}

} // namespace

std::ostream&
ABcb::spy::UserName(std::ostream& a_os)
{
	return a_os << GetUserName() << std::flush;
}

std::ostream&
ABcb::spy::LocalDate(std::ostream& a_os)
{
	namespace pt = boost::posix_time;
	const pt::ptime now = pt::second_clock::local_time();

	std::ostringstream oss;
	const pt::ptime::date_type date = now.date();
	oss << date.day_of_week() << ", "
		<< date.month() << ' ' << date.day() << ", " << date.year();
	a_os << oss.str() << std::flush;
	return a_os;
}

std::ostream&
ABcb::spy::LocalTime(std::ostream& a_os)
{
	namespace pt = boost::posix_time;
	const pt::ptime now = pt::second_clock::local_time();

	std::ostringstream oss;
	pt::time_facet* const f = new pt::time_facet("%H:%M:%S");
	oss.imbue(std::locale(oss.getloc(), f));
	oss << now;

	a_os << oss.str() << std::flush;
	return a_os;
}

namespace {

const std::string pad = "  ";

template <class T>
std::ostream&
Range(std::ostream& a_os)
{
	static_assert(
		std::is_scalar<T>::value || // TODO: How to avoid instantiating with char?
		false == std::numeric_limits<T>::is_integer,
		"static_assert failed: "
		"Template parameter T is neither arithmetic nor floating point");
	a_os << "Range = [" << boost::numeric::bounds<T>::lowest() << ", "
		<< boost::numeric::bounds<T>::highest() << ']' << std::flush;
	return a_os;
}

template <class T>
std::ostream&
RangeAsInt(std::ostream& a_os)
{
	static_assert(
		std::is_scalar<T>::value ||
		true == std::numeric_limits<T>::is_integer,
		"static_assert failed: Template parameter T is not suitable");
	a_os << "Range (as int) = [" 
		<< boost::numeric_cast<int>(boost::numeric::bounds<T>::lowest())
		<< ", "
		<< boost::numeric_cast<int>(boost::numeric::bounds<T>::highest())
		<< ']' << std::flush;
	return a_os;
}

} // namespace

std::ostream&
ABcb::spy::InfoOfSomeTypes(std::ostream& a_os) // TODO: Refactor contents
{
	using boost::multiprecision::cpp_dec_float_50;
	a_os
		<< pad << "sizeof(char) = " << sizeof(char)
			<< " | " << RangeAsInt<char> << '\n'
		<< pad << "sizeof(wchar_t) = " << sizeof(wchar_t)
			<< " | " << Range<wchar_t> << '\n'
		<< pad << "sizeof(int) = " << sizeof(int)
			<< " | " << Range<int> << '\n'
		<< pad << "sizeof(int64_t) = " << sizeof(int64_t)
			<< " | " << Range<int64_t> << '\n'
		<< pad << "sizeof(float) = " << sizeof(float)
			<< " | " << Range<float> << '\n'
		<< pad << "sizeof(double) = " << sizeof(double)
			<< " | " << Range<double> << '\n'
		<< pad << "sizeof(long double) = " << sizeof(long double)
			<< " | " << Range<long double> << '\n'
		<< pad << "sizeof(size_t) = " << sizeof(size_t)
			<< " | " << Range<size_t> << '\n'
		<< pad << "sizeof(unsigned int) = " << sizeof(unsigned int)
			<< " | " << Range<unsigned int> << '\n'
		<< pad << "sizeof(unsigned long) = " << sizeof(unsigned long)
			<< " | " << Range<unsigned long> << '\n'
		<< pad << "sizeof(uint64_t) = " << sizeof(uint64_t)
			<< " | " << Range<uint64_t> << '\n'
		<< pad <<	"sizeof(boost::multiprecision::cpp_dec_float_50) = "
			<< sizeof(cpp_dec_float_50)
			<< " | " << Range<cpp_dec_float_50> << '\n';
	return a_os;
}

namespace {

namespace bf = boost::filesystem;

std::string
GetArgv0Info(const std::string& a_argv0)
{
	const bf::path fullArgv0 =
		bf::system_complete(bf::canonical(bf::path(a_argv0)));

	std::ostringstream oss;
	oss << "The full argv[0]:\n"
		<< pad << "is " << fullArgv0 << ",\n";
	if (bf::exists(fullArgv0)) {
		oss << pad << "which is" << (bf::is_regular(fullArgv0) ? "" : " not")
			<< " a regular file, created by ";
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
			//	how-to-get-a-local-date-time-from-a-time-t-with-boostdate-time
			boost::date_time::c_local_adjustor<pt::ptime>::utc_to_local(
				pt::from_time_t(theTime_t));
		const pt::ptime::date_type date = thePtime.date();
		oss << " on " << date.day_of_week() << ", " << date.month() << ' '
			<< date.day() << ", " << date.year();

		// Hours, minutes and seconds
		//
		pt::time_facet* const f = new pt::time_facet("%H:%M:%S");
		oss.imbue(std::locale(oss.getloc(), f));
		oss << ", at " << thePtime;
	} else
		oss << "(which does not seem to exist)";
	return oss.str();
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

std::ostream&
ABcb::spy::operator<<(std::ostream& a_os, const ABcb::spy::RunInfo& a_runInfo)
{
	const std::string argv0Info = GetArgv0Info(a_runInfo.GetArgv0());
	const std::string currentDirInfo = GetCurrentDirInfo();

	using namespace ABcb::spy;
	a_os << '\n' << a_runInfo.GetProgName()
		<< " was launched by " << UserName << " at " << HostName
		<< " on " << LocalDate << ", at " << LocalTime << '\n'
		<< argv0Info << '\n'
		<< currentDirInfo << '\n'
		<< "Using Boost version " << BoostVersion << '\n'
		<< "Using Clang version " << ClangVersion << '\n'
		<< "Using GNU g++ version " << GNUGppVersion << '\n'
		<< "Using Visual Studio C/C++ compiler version "
			<< VisualStudioCppCompilerVersion << '\n'
		<< "List of preprocessor defines:\n" << ListOfPreprocessorDefines
		<< "Info of some types:\n" << InfoOfSomeTypes;
	return a_os;
}

template <typename TClock>
ABcb::spy::Timer<TClock>::Timer()
: d_start(TClock::now())
{}

template <typename TClock>
typename TClock::duration
ABcb::spy::Timer<TClock>::Elapsed() const
{
	return TClock::now() - d_start;
}

template <typename TClock>
double
ABcb::spy::Timer<TClock>::Seconds() const
{
	return
		Elapsed().count() * ((double)TClock::period::num / TClock::period::den);
}

template <typename TClock>
void
ABcb::spy::Timer<TClock>::Reset()
{
	d_start = TClock::now();
}

//template class ABcb::spy::Timer<std::chrono::system_clock>;
//template class ABcb::spy::Timer<std::chrono::steady_clock>; // GCC duplicate?
template class ABcb::spy::Timer<std::chrono::high_resolution_clock>;

// -- eof
