// -- Examples on how to use boost::algorithm::string

#include <iostream>
#include <string>

#include <boost/algorithm/string.hpp>

#include "aux-raw.h"
#include "algorithm-string-pool.h"

namespace {

void
Output(const std::string& a_description, const std::string& a_value) {
	const std::string pad = "  ";
	std::cout << pad << a_description << ": \"" << a_value << "\"" << std::endl;
}
	
} // namespace

void
Ada_Byron_code_book::ExamplesOfAlgorithmsString()
{
	std::clog << __func__ << " started..." << std::endl;
	
	std::string name = "  Alan Turing  ";
	Output("Name (original)", name);
	
	using namespace boost::algorithm;
	to_lower(name);
	Output("Name (after to_lower)", name);
	to_upper(name);
	Output("Name (after to_upper)", name);
	trim_right(name);
	Output("Name (after trim_right)", name);
	trim(name);
	Output("Name (after trim)", name);
	name.erase(remove_if(name.begin(), name.end(), isspace), name.end());
	Output("Name (after isspace removal)", name);
	
	std::clog << __func__ << " finished." << std::endl;
}

// -- eof
