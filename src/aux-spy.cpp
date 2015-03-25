// -- 

#include <boost/version.hpp>

#include "aux-spy.h"

namespace ABcb = Ada_Byron_code_book;

void
ABcb::spy::BoostVersion(std::ostream& a_os)
{
	a_os
		<< BOOST_VERSION / 100000 << "."  // major version
		<< BOOST_VERSION / 100 % 1000 << "."  // minior version
		<< BOOST_VERSION % 100                // patch level
		<< std::flush;
}

// -- eof
