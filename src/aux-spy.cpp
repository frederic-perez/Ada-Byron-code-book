// -- 

#include <chrono>
#include <sstream>

#include <boost/date_time/posix_time/posix_time.hpp>
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
		<< _MSC_VER / 100 << '.'	// major version
		<< _MSC_VER / 10000 % 100	// minor version
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

std::ostream&
ABcb::spy::operator<<(std::ostream& a_os, const ABcb::spy::RunInfo& a_runInfo)
{
// TODO: Follow this structure for time output: "The final decision is scheduled
// to come at 12:45 ET Dec. 7."
	using namespace ABcb::spy;
	a_os << '\n' << a_runInfo.GetProgName()
		<< " was launched by " << UserName << " at " << HostName
		<< " on " << LocalDate << ", at " << LocalTime << '\n'
		<< "Using Boost version " << BoostVersion << '\n'
		<< "Using Clang version " << ClangVersion << '\n'
		<< "Using GNU g++ version " << GNUGppVersion << '\n'
		<< "Using Visual Studio C/C++ compiler version "
			<< VisualStudioCppCompilerVersion << '\n'
		<< "List of preprocessor defines:\n" << ListOfPreprocessorDefines;
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
