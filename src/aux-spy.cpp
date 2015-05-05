// -- 

#include <ctime>
#if defined(__GNUG__)
#include <unistd.h>
#endif

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

std::ostream&
ABcb::spy::LocalTime(std::ostream& a_os)
{
	const time_t theTime_t = time(NULL);
	//strcat(GLBox::d_comments, asctime(localtime(&theTime_t)));
	// \__ realloc() of already freed area, or addresss outside of heap

#if defined(_MSC_VER)
#pragma warning(disable : 4996) // function or variable may be unsafe
#endif

	struct tm* const theLocalTime =
		localtime(&theTime_t); // <-- Caution: This inserts \n at end!
	a_os << asctime(theLocalTime) << std::flush;

#if defined(_MSC_VER)
#pragma warning(default : 4996) // function or variable may be unsafe
#endif

	return a_os;
}

std::ostream&
operator<<(std::ostream& a_os, const ABcb::spy::RunInfo& a_runInfo)
{
	using namespace ABcb::spy;
	a_os << '\n' << a_runInfo.d_progname
		<< " started at " << HostName << " on " << LocalTime //< LocalTime adds \n
		<< "Using Boost version " << BoostVersion << '\n'
		<< "Using Clang version " << ClangVersion << '\n'
		<< "Using GNU g++ version " << GNUGppVersion << '\n'
		<< "Using Visual Studio C/C++ compiler version "
			<< VisualStudioCppCompilerVersion << '\n'
		<< "List of preprocessor defines:\n" << ListOfPreprocessorDefines;
	return a_os;
}

// -- eof
