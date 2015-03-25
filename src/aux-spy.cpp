// -- 

#include <boost/version.hpp>

#include "aux-spy.h"

namespace ABcb = Ada_Byron_code_book;

std::ostream&
ABcb::spy::BoostVersion(std::ostream& a_os)
{
	return 
		a_os
			<< BOOST_VERSION / 100000 << "."  // major version
			<< BOOST_VERSION / 100 % 1000 << "."  // minior version
			<< BOOST_VERSION % 100                // patch level
			<< std::flush;
}

// -- eof
