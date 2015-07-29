// -- Examples on how to use C++11 features, and some other stuff

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <sstream>
#include <tuple>
#include <typeinfo>
#include <vector>

#include "aux-raw-compiler-warnings-off.h"

	#include <boost/algorithm/string.hpp>

#include "aux-raw-compiler-warnings-on.h"

#include "aux-raw.h"
#include "aux-spy.h"
#include "cpp11-pool.h"

namespace ABcb = Ada_Byron_code_book; // Stroustrup C++ PL, p. 179

using ABcb::raw::pad;

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

#ifdef ASAN_TEST
// TODO: Output (in execution) offending source code symbols
	/*
	
	Within CMake we can do set particular flags (working for Ubuntu):

		CMAKE_CXX_FLAGS: -DASAN_TEST -fsanitize=address -fno-omit-frame-pointer

	and we get at running time error messages like:

		=================================================================
		==5162== ERROR: AddressSanitizer: heap-use-after-free on address ...
		READ of size 4 at 0x602e0001fc64 thread T0
		...

	*/

	int* const array = new int[100];
	delete[] array;
	std::cout << __func__ << ": array[1] is " << array[1] << std::endl; // BOOM
#else
	std::clog << __func__ << ": Note: ASAN_TEST was not defined" << std::endl;
#endif
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
struct TuplePrinter<Tuple, 1> {
	static void print(const Tuple& t) {	std::cout << std::get<0>(t); }
};

template<class... Args>
void print(const std::tuple<Args...>& t)
{
	const size_t N = sizeof...(Args);
	std::cout << '[' << N << "]{";
	TuplePrinter<decltype(t), N>::print(t);
	std::cout << '}';
}
// end helper function

} // namespace

void
ABcb::cpp11::UsingTuple()
{
	std::clog << __func__ << " started..." << std::endl;

	using MyTuple = std::tuple<int, std::string, bool>;
	const size_t N = std::tuple_size<MyTuple>::value;
	std::clog << pad << "The size of MyTuple is " << N << std::endl;

	const MyTuple myTuple{ 16, "Test", true };
	std::cout << pad << "typeid of get<0>(myTuple) = "
		<< typeid(std::get<0>(myTuple)).name() << std::endl;
	std::cout << pad << "typeid of get<1>(myTuple) = "
		<< typeid(std::get<1>(myTuple)).name() << std::endl;
	std::cout << pad << "typeid of get<2>(myTuple) = "
		<< typeid(std::get<2>(myTuple)).name() << std::endl;
	std::cout << pad << "myTuple = ";
	print(myTuple);
	std::cout << std::endl;

	std::clog << __func__ << " finished." << std::endl;
}

void
ABcb::cpp11::AlgorithmExamples()
{
	std::clog << __func__ << " started..." << std::endl;

	const std::vector<int> v{ 3, 9, 1, 4, 2, 5, 9 };
	spy::Output(std::cout, v, pad + "v");
	auto result = std::minmax_element(v.begin(), v.end());
	std::cout
		<< pad << pad << "v's min element (" << *result.first << ") at index "
		<< (result.first - v.begin()) << '\n'
		<< pad << pad << "v's max element (" << *result.second << ") at index "
		<< (result.second - v.begin()) << std::endl;
	
	float f1 = 12., f2 = 7.;
	auto fs = std::minmax(f1, f2);
	std::cout
		<< pad << "f1 = " << f1 << ", f2 = " << f2 << '\n'
		<< pad << pad << "min of {f1, f2} = " << fs.first << '\n'
		<< pad << pad << "max of {f1, f2} = " << fs.second << std::endl;

	std::clog << __func__ << " finished." << std::endl;
}

namespace Euclidean {

template<size_t N>
class Vector {
public:

	// Note: There is a nice discussion in
	// stackoverflow.com/questions/5438671/static-assert-on-initializer-listsize
	// to try to add a static_assert in the ctor, but alas, we did not succeed.
	//
	Vector(std::initializer_list<double> a_args)
	: d_array()
	{
		if (d_array.size() != a_args.size()) { // Verify right size
			std::cerr << __func__ << ": a_args.size()=" << a_args.size()
				<< " does not match N=" << N << std::endl;
			throw 666; // TODO: Use a better std exception
		}

		size_t i = 0;
		for (auto it = begin(a_args); it != end(a_args); ++it, ++i)
			d_array[i] = *it;
	}

	double
	Length() const
	{
		double accSquared = 0.;
		for (auto value : d_array)
			accSquared += value*value;
		return sqrt(accSquared);
	}

	template<size_t n>
	friend std::ostream& operator<<(std::ostream&, const Vector<n>&);

private:
	std::array<double, N> d_array;
};

template<size_t N>
std::ostream&
operator<<(std::ostream& a_os, const Vector<N>& a_vector)
{
	// 1st, the size of the Point
	//
	a_os << '[' << a_vector.d_array.size() << ']';

	// 2nd, the actual contents
	//
	std::ostringstream oss;
	std::vector<std::string> valuesAsStrings;
	for (auto value : a_vector.d_array) {
		oss << value;
		valuesAsStrings.push_back(oss.str());
		oss.str("");
	}
	oss << '(' << boost::algorithm::join(valuesAsStrings, ", ") << ')';
	a_os << oss.str();

	return a_os;
}

using Vector2 = Vector<2>;
using Vector3 = Vector<3>;

} // namespace Euclidean

void
ABcb::cpp11::MiscellanyExamples()
{
	std::clog << __func__ << " started..." << std::endl;

	std::cout << pad << "PrintList (variadic template function): ";
	PrintList(1, 2, 'c', "Hello, world!", 666.);

	const Euclidean::Vector2 vector2{ 2., 3. };
	std::cout
		<< pad << "vector2 typeid name = " << typeid(vector2).name() << '\n'
		<< pad << "vector2 spy::TypeName of its decltype = "
			<< spy::TypeName<decltype(vector2)>() << '\n'
		<< pad << "vector2 = " << vector2 << "    Length() = "
		<< vector2.Length() << std::endl;

	const Euclidean::Vector3 vector3{ 5., 7., 11. };
	std::cout
		<< pad << "vector3 typeid name = " << typeid(vector3).name() << '\n'
		<< pad << "vector3 spy::TypeName of its decltype = "
			<< spy::TypeName<decltype(vector3)>() << '\n'
		<< pad << "vector3 = " << vector3 << "    Length() = "
		<< vector3.Length() << std::endl;

	std::clog << __func__ << " finished." << std::endl;
}

// -- eof
