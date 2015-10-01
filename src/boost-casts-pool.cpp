// -- Examples on how to use boost::lexical_cast

#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>

#include "aux-raw.h"
#include "boost-casts-pool.h"

namespace ABcb = Ada_Byron_code_book;
using ABcb::raw::pad;

void
ABcb::ExamplesOfBoostLexicalCast(const std::string& a_string)
{
	std::clog << __func__ << " started..." << std::endl;

	// First, old way, which so far does not work properly -- TODO: Fix this

	const std::string line = "14 -1 3";
	if (!line.empty()) {
		std::cout << pad << "Parsing line \"" << line << "\" => " << std::flush;
		std::istringstream iss(line); // or parse(line)
		unsigned int i;
		iss >> i;
		if (!iss.good()) // Note: if (iss.fail) does not work fine for our purposes
			std::cerr << "Error parsing first index\n";
		else {
			unsigned int j;
			iss >> j;
			if (!iss.good())
				std::cerr << pad << "Error parsing second index\n";
			else {
				unsigned int k;
				iss >> k;
				if (!iss.good())
					std::cerr << "Error parsing third index (i=" << i << ", j=" << j
						<< ")\n";
				else
					std::cout << pad << "indices: " << i << ", " << j << ", " << k
					<< std::endl;
			}
		}
	}

	// Now, lexical_cast

	using boost::lexical_cast;
	using boost::bad_lexical_cast;

	const int valueIntS = stoi(a_string);
	std::cout << pad << "stoi(\"" << a_string << "\") is "
		<< valueIntS << std::endl;
	const int valueIntL = lexical_cast<int>(a_string);
	std::cout << pad << "lexical_cast<int>(\"" << a_string << "\") is "
		<< valueIntL << std::endl;

	const short valueShortS = static_cast<short>(stoi(a_string));
	std::cout << pad << "stoi(\"" << a_string << "\") is "
		<< valueShortS << std::endl;
	try {
		const short valueShortL = lexical_cast<short>(a_string);
		std::cout << pad << "lexical_cast<short>(\"" << a_string << "\") is "
			<< valueShortL << std::endl;
	} catch (const boost::bad_lexical_cast& e) {
		std::cerr << pad << "Exception caught: " << e.what() << '\n';
	}

	std::clog << __func__ << " finished." << std::endl;
}

void
ABcb::ExamplesOfBoostNumericCast()
{
	std::clog << __func__ << " started..." << std::endl;

	std::cerr << "TODO\n"; // TODO

	std::clog << __func__ << " finished." << std::endl;
}

// -- eof
