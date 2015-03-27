// -- 

#include <string>

#include "preprocessor-pool.h"

namespace ABcb = Ada_Byron_code_book;

std::ostream&
ABcb::spy::ListOfPreprocessorDefines(std::ostream& a_os)
{
	const std::string pad = "  ";
	return
		a_os
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
