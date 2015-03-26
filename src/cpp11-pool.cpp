// -- Examples on how to use C++11 features, and some other stuff

#include <iostream>
#include <tuple>
#include <typeinfo>

#include "aux-raw.h"
#include "cpp11-pool.h"

namespace ABcb = Ada_Byron_code_book; // Stroustrup C++ PL, p. 179

void
ABcb::cpp11::TryBadCode()
{
	int foo;
#if defined(__GNUG__) || defined(WIN32)
	foo = 42; // Silly operation to avoid a vs12 warning
#endif
	int bar = foo;
#if defined(__GNUG__) || defined(WIN32)
	++bar; // Silly operation to avoid compiler warnings
#endif
	char* const pointer = new char;
	*pointer = 'a';

	double* const baz = new double[3];
	baz[0] = 42.;
}

void
ABcb::cpp11::TestIfAConstParameterCanBeModified(const int a_int)
{
#if defined(__GNUG__) || defined(WIN32)
	int i = a_int; ++i; // Silly operations to avoid compiler warnings
#else
	a_int = 0; // Error in vs12, g++ 4.8.2, clang++ 3.4-1
#endif
}

namespace {

// helper function to print a tuple of any size
// from http://en.cppreference.com/w/cpp/utility/tuple/tuple

template<class Tuple, std::size_t N>
struct TuplePrinter {
	static void print(const Tuple& t)
	{
		TuplePrinter<Tuple, N - 1>::print(t);
		std::cout << ", " << std::get<N - 1>(t);
	}
};

template<class Tuple>
struct TuplePrinter<Tuple, 1>{
	static void print(const Tuple& t)
	{
		std::cout << std::get<0>(t);
	}
};

template<class... Args>
void print(const std::tuple<Args...>& t)
{
	std::cout << "{ ";
	TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
	std::cout << " }";
}
// end helper function

} // namespace

void
ABcb::cpp11::UsingTuple()
{
	std::clog << __func__ << ':' << std::endl;
	typedef std::tuple<int, std::string, bool> MyTuple;
	const size_t N = std::tuple_size<MyTuple>::value;
	std::clog << "The size of MyTuple is " << N << std::endl;

	const MyTuple t1{ 16, "Test", true };
	std::cout << "  Type of get<1>(t1) = " << typeid(std::get<1>(t1)).name()
		<< std::endl;
	std::cout << "  t1 = ";
	print(t1);
	std::cout << '\n' << std::endl;
}

// -- eof
