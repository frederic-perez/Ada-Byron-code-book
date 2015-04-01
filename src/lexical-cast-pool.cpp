// -- Examples on how to use boost::lexical_cast

#include <iostream>

#include <boost/lexical_cast.hpp>

#include "aux-raw.h"
#include "lexical-cast-pool.h"

void
Ada_Byron_code_book::ExamplesOfLexicalCast(const std::string& a_string)
{
	std::clog << __func__ << " started..." << std::endl;

	using boost::lexical_cast;
	using boost::bad_lexical_cast;

	const std::string pad = "  ";

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

// -- eof
