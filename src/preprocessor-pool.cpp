// -- 

#include <string>

#include "preprocessor-pool.h"

namespace ABcb = Ada_Byron_code_book;

std::ostream&
ABcb::spy::ListOfPreprocessorDefines(std::ostream& a_os)
{
	const std::string pad = "  ";
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

	return
		a_os
			<< std::boolalpha
			<< pad << "defined(__clang__): " << definedClang << '\n'
			<< pad << "defined(WIN32): " << definedWIN32 << '\n'
#ifdef __GNUG__
			<< pad << "__GNUG__ = " << __GNUG__ << '\n'
#endif
#ifdef _MSC_VER
			<< pad << "_MSC_VER = " << _MSC_VER << '\n'
#endif
#ifdef MY_GNUGPP_VERSION
			<< pad << "MY_GNUGPP_VERSION = " << MY_GNUGPP_VERSION << '\n'
#endif
			<< std::flush;
}

// -- eof
