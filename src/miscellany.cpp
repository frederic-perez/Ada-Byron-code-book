// -- 

#include <stdexcept>
#include <iostream>
#include <sstream>

#include <boost/numeric/conversion/bounds.hpp>

#include "aux-raw.h"
#include "miscellany.h"

namespace ABcb = Ada_Byron_code_book;

void
ABcb::miscellany::Function(const int a_value) // <-- notice the "const" here
{	std::cout << __func__ << ": a_value=" << a_value << std::endl; }

size_t
ABcb::miscellany::FactorialRecursive(const size_t a_n)
{
	if (a_n <= 1)
		return 1;

	const size_t factorialRecursiveNMinus1 = FactorialRecursive(a_n - 1);
	const size_t result = a_n * factorialRecursiveNMinus1;
	static const size_t max = boost::numeric::bounds<size_t>::highest();
	//
	// Interesting information on std::overflow_error available at
	// http://en.cppreference.com/w/cpp/error/overflow_error
	//
	// TODO: Study en.cppreference.com/w/cpp/error/overflow_error and apply it!
	//
	const bool overflow =
		// overflow of a * b \equiv a * b > max \equiv a > max/b
		a_n > max/factorialRecursiveNMinus1;
	if (overflow) {
		std::ostringstream oss;
		oss << "Overflow trying to compute " << __func__ << '(' << a_n << ')';
		throw std::overflow_error(oss.str());
	}

	return result;
}

size_t
ABcb::miscellany::FactorialIterative(const size_t a_n)
{
	size_t result = 1;
	for (size_t i = 1; i <= a_n; ++i)
		result *= i;
	return result;
}

void
ABcb::miscellany::ExamplesOfFactorial()
{
	std::clog << __func__ << " started..." << std::endl;

	using ABcb::raw::pad;

	// Using FactorialCompileTime
	//
	//const size_t N = 21; // < integral constant overflow in vs14
	const size_t N = 20; // < integral constant overflow in vs14
	const size_t factorialCompileTime =
		ABcb::miscellany::FactorialCompileTime<N>::d_value; // == 24
	std::ostringstream oss;
	oss.imbue(std::locale("")); // To add commas when outputting result
	oss << factorialCompileTime;
	std::cout << pad << "FactorialCompileTime<" << N << ">::d_value = "
		<< oss.str() << std::endl;

	// Using FactorialRecursive
	//
	size_t n = 0;
	size_t factorialN = 0;
	bool overflow = false;
	while (!overflow) {
		++n;
		try {
			factorialN = FactorialRecursive(n);
		} catch (const std::overflow_error& e) {
			std::cerr << pad << __func__ << ": Exception caught: " << e.what()
				<< '\n';
			overflow = true;
		}
	}

	--n;
	factorialN = FactorialRecursive(n);
	oss.str("");
	oss << factorialN;
	std::cout << pad << "FactorialRecursive(" << n << ")            = "
		<< oss.str() << std::endl;

	// Using FactorialIterative
	//
	const size_t factorialIterative = FactorialIterative(n);
	oss.str("");
	oss << factorialIterative;
	std::cout << pad << "FactorialIterative(" << n << ")            = "
		<< oss.str() << std::endl;

	std::clog << __func__ << " finished." << std::endl;
}


// -- eof
