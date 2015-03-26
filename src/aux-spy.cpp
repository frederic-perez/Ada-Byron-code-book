// -- 

#include <boost/version.hpp>

#include "aux-spy.h"

namespace ABcb = Ada_Byron_code_book;

std::ostream&
ABcb::spy::BoostVersion(std::ostream& a_os)
{
	return 
		a_os
			<< BOOST_VERSION / 100000 << "."	// major version
			<< BOOST_VERSION / 100 % 1000 << "."	// minor version
			<< BOOST_VERSION % 100	// patch level
			<< std::flush;
}

std::ostream&
ABcb::spy::GNUGppVersion(std::ostream& a_os)
{
	return 
		a_os
#ifdef MY_GNUGPP_VERSION
			<< MY_GNUGPP_VERSION / 10000 << "."	// major version
			<< MY_GNUGPP_VERSION / 100 % 100 << "."	// minor version
			<< MY_GNUGPP_VERSION % 100	// patch level
#else
			<< "[not applicable]"
#endif
			<< std::flush;
}

// -- eof
