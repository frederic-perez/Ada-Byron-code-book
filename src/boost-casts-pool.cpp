// -- Examples on how to use boost::lexical_cast

#include <iostream>
#include <limits>
#include <sstream>
#include <string>

#include <boost/lexical_cast.hpp>

#include "aux-raw.h"
#include "aux-spy.h"
#include "boost-casts-pool.h"

namespace ABcb = Ada_Byron_code_book;
using ABcb::raw::pad;

void
ABcb::ExamplesOfOldConversions()
{
	std::clog << __func__ << " started..." << std::endl;

	// Old way, which so far does not work properly -- TODO: Fix this

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

	std::clog << __func__ << " finished." << std::endl;
}

void
ABcb::ExamplesOfBoostLexicalCast(const std::string& a_numberToConvert)
{
	std::clog << __func__ << " started..." << std::endl;

	using boost::lexical_cast;
	using boost::bad_lexical_cast;

	const int valueIntS = stoi(a_numberToConvert);
	std::cout << pad << "stoi(\"" << a_numberToConvert << "\") is "
		<< valueIntS << std::endl;
	const int valueIntL = lexical_cast<int>(a_numberToConvert);
	std::cout << pad << "lexical_cast<int>(\"" << a_numberToConvert << "\") is "
		<< valueIntL << std::endl;

	const short valueShortS = static_cast<short>(stoi(a_numberToConvert));
	std::cout << pad << "stoi(\"" << a_numberToConvert << "\") is "
		<< valueShortS << std::endl;
	try {
		const short valueShortL = lexical_cast<short>(a_numberToConvert);
		std::cout << pad << "lexical_cast<short>(\"" << a_numberToConvert 
			<< "\") is " << valueShortL << std::endl;
	} catch (const boost::bad_lexical_cast& e) {
		std::cerr << pad << "Exception caught: " << e.what() << '\n';
	}

	std::clog << __func__ << " finished." << std::endl;
}

namespace {

template <class SourceT, class TargetT>
void
UseStdNumericLimitsPlusStaticCast_FAILS_SOMETIMES(const SourceT a_source)
{
	std::cout << pad << __func__ << ": a_source ("
		<< ABcb::spy::TypeName<SourceT>() << ") = " << a_source << std::flush;
#include "aux-raw-compiler-warnings-off++begin.h"
	bool succeeded = true;
	const std::string typeNameOfTargetT = ABcb::spy::TypeName<TargetT>();
	//if (a_source < boost::numeric::bounds<TargetT>::lowest()) { vs min()
	if (a_source < std::numeric_limits<TargetT>::lowest()) { // Now in C++
		std::cout << std::endl;
		std::cerr << pad << __func__ << ": Error: a_source too small to convert to "
			<< typeNameOfTargetT << '\n';
		succeeded = false;
	//} else if (a_source > boost::numeric::bounds<TargetT>::highest()) {
	} else if (a_source > std::numeric_limits<TargetT>::max()) { // Use just C++
		std::cout << std::endl;
		std::cerr << pad << __func__ << ": Error: a_source too large to convert to "
			<< typeNameOfTargetT << '\n';
		succeeded = false;
	}
#include "aux-raw-compiler-warnings-off++end.h"

	if (!succeeded)
		return;
	const TargetT target = static_cast<TargetT>(a_source);

	// Keep on using sourceObjectSelf from this point onwards

	std::cout << "; target (" << ABcb::spy::TypeName<TargetT>() << ") = "
		<< static_cast<double>(target) << std::endl;
}

template <class SourceT, class TargetT>
void
ApplyBoostNumericCast(const SourceT a_source)
{
	/*
	
	The code below--using boost::numeric_cast<T>--beats the previous options, so
	this is the best code so far.
	Explanations on boost::numeric_cast<T>::... can be found, for example, in
	From Beyond the C++ Standard Library - An Introduction to Boost, by 
	Björn Karlsson: Part I : General Libraries, Library 2 : Conversion, 
	numeric_cast

	*/

	#include <boost/lexical_cast.hpp>

	std::cout << pad << __func__ << ": a_source ("
		<< ABcb::spy::TypeName<SourceT>() << ") = " << a_source << std::flush;
	TargetT target = 66;
	const std::string typeNameOfTargetT = ABcb::spy::TypeName<TargetT>();
	try {
		target = boost::numeric_cast<TargetT>(a_source);
		std::cout << "; target (" << typeNameOfTargetT << ") = "
			<< static_cast<long double>(target) << std::endl;
	}	catch (const boost::numeric::bad_numeric_cast& e) {
		std::cout << std::endl;
		std::cerr << pad << __func__ << ": Error: Bad target ("
			<< static_cast<long double>(target)
			<< ", which is the preset value) tried conversion (to "
			<< typeNameOfTargetT << "): " << e.what() << '\n';
	}
}

} // namespace

void
ABcb::ExamplesOfBoostNumericCast()
{
	std::clog << __func__ << " started..." << std::endl;

	int source = 123456;
	using SourceT = decltype(source);
	ApplyBoostNumericCast<SourceT, signed long>(source);
	ApplyBoostNumericCast<SourceT, unsigned long>(source);
	source = -123456;
	using Target1 = signed long;
	UseStdNumericLimitsPlusStaticCast_FAILS_SOMETIMES<SourceT, Target1>(source);
	ApplyBoostNumericCast<SourceT, Target1>(source);
	using Target2 = unsigned long;
	UseStdNumericLimitsPlusStaticCast_FAILS_SOMETIMES<SourceT, Target2>(source);
	ApplyBoostNumericCast<SourceT, Target2>(source);
	source = 4200;
	using Target3 = char;
	UseStdNumericLimitsPlusStaticCast_FAILS_SOMETIMES<SourceT, Target3>(source);
	ApplyBoostNumericCast<SourceT, Target3>(source);
	source = 42;
	ApplyBoostNumericCast<SourceT, unsigned char>(source);
	source = 1234567890;
	ApplyBoostNumericCast<SourceT, double>(source);

	std::clog << __func__ << " finished." << std::endl;
}

// -- eof
