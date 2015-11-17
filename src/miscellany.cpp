// -- 

#include <iostream>
#include <sstream>

#include "aux-raw.h"
#include "miscellany.h"

namespace ABcb = Ada_Byron_code_book;

void
ABcb::miscellany::Function(const int a_value) // <-- notice the "const" here
{	std::cout << __func__ << ": a_value=" << a_value << std::endl; }

size_t
ABcb::miscellany::FactorialRecursive(const size_t a_n)
{	return a_n <= 1 ? 1 : a_n * FactorialRecursive(a_n - 1); }

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
	size_t n = 3;
	size_t factorialN = FactorialRecursive(n);
	size_t nMinus1 = n - 1;
	size_t factorialNMinus1 = FactorialRecursive(nMinus1);
	bool failed = factorialN <= factorialNMinus1;
	for (; !failed;) {
		++n;
		++nMinus1;
		factorialNMinus1 = factorialN;
		factorialN = FactorialRecursive(n);
		failed = factorialN <= factorialNMinus1; // TODO: Does this really work?
	}

	oss.str("");
	oss << factorialNMinus1;
	std::cout << pad << "FactorialRecursive(" << nMinus1 << ")            = "
		<< oss.str() << std::endl;

	// Using FactorialIterative
	//
	const size_t factorialIterative = FactorialIterative(nMinus1-1);
	oss.str("");
	oss << factorialIterative;
	std::cout << pad << "FactorialIterative(" << nMinus1-1 << ")            = "
		<< oss.str() << std::endl;

	std::clog << __func__ << " finished." << std::endl;
}


// -- eof
