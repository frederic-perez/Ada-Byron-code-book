// -- Examples on how to use boost::lexical_cast

#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>

#include "aux-raw.h"
#include "aux-spy.h"
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


namespace {

template <class TargetT>
// TODO: Add <class SourceT, class TargetT> void Do...(SourceT a_source)
void
DoNumericCast(int a_source)
{
	/*

	The code below (using boost::numeric_cast<T>) beats the following options:

	1) Using C++'s std::numeric_limits<T>::...

		 a) Particular example

				#include <limits>

				const int foo = ComputeAnInt();
				if (foo > std::numeric_limits<char>::max()) { // Bad situation!
					std::cerr << __func __ << ": Error: foo too large\n";
					return false; // this depends on the particular context
				}

				// Here we are on the safe side (we can perform the cast safely)
				//
				const char fooSelf = static_cast<char>(foo);

				// Keep on using fooSelf from this point onwards

		 b) Now, using invented/generic names of classes for cut & paste.
				After pasting the code, substitute the text in italics with actual code.

				#include <limits>

				const SourceClass sourceObject = ComputeSomething();
				if (sourceObject > std::numeric_limits<TargetClass>::max()) { // Bad!
					std::cerr << __func__ << ": Error: sourceObject too large\n";
					return ThisDependsOnTheParticularContext;
				}
				const TargetClass sourceObjectSelf =
					static_cast<TargetClass>(sourceObject);

				// Keep on using sourceObjectSelf from this point onwards

	2) Using boost::numeric::bounds<T>::... Example:

			#include <boost/numeric/conversion/bounds.hpp>

			if (a_milliseconds > boost::numeric::bounds<DWORD>::highest()) { // Bad!
				std::cerr << __func__ << ": Error: Too large milliseconds value\n";
				return false;
			}
			const DWORD milliseconds = static_cast<DWORD>(a_milliseconds);

	*/

	/*
	
	And now, the best code (so far).
	Explanations on boost::numeric_cast<T>::... can be found, for example, in
	From Beyond the C++ Standard Library - An Introduction to Boost, by 
	Björn Karlsson: Part I : General Libraries, Library 2 : Conversion, 
	numeric_cast

	*/

	std::cout << pad << __func__ << ": a_source = " << a_source << std::flush;
	TargetT target = 66;
	const std::string typeNameOfTargetT = ABcb::spy::TypeName<TargetT>();
	try {
		target = boost::numeric_cast<TargetT>(a_source);
		std::cout << "; target (" << typeNameOfTargetT << ") = "
			<< static_cast<double>(target) << std::endl;
	}	catch (const boost::numeric::bad_numeric_cast& e) {
		std::cout << std::endl;
		std::cerr << pad << __func__ << ": Error: Bad target ("
			<< static_cast<double>(target)
			<< ", which is the preset value) tried conversion (to "
			<< typeNameOfTargetT << "): " << e.what() << '\n';
	}
}

} // namespace

void
ABcb::ExamplesOfBoostNumericCast()
{
	std::clog << __func__ << " started..." << std::endl;

	DoNumericCast<signed long>(123456);
	DoNumericCast<unsigned long>(-123456);
	DoNumericCast<char>(4200);
	DoNumericCast<unsigned char>(42);
	DoNumericCast<double>(1234567890);

	std::clog << __func__ << " finished." << std::endl;
}

// -- eof
