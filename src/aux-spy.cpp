// -- 

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

// -- eof
