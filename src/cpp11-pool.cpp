// -- Examples on how to use C++11 features, and some other stuff

#include <algorithm>
#include <iostream>
#include <ratio>
#include <tuple>
#include <vector>

#include "aux-raw.h"
#include "aux-spy+.h"
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
  int i = a_int;
  ++i; // Silly operations to avoid compiler warnings
#else
  a_int = 0; // Error in vs12, g++ 4.8.2, clang++ 3.4-1
#endif
}

namespace {

// helper function to print a tuple of any size
// from http://en.cppreference.com/w/cpp/utility/tuple/tuple

template <class Tuple, std::size_t N>
struct TuplePrinter {
  static void print(const Tuple& t)
  {
    TuplePrinter<Tuple, N - 1>::print(t);
    std::cout << ", " << std::get<N - 1>(t);
  }
};

template <class Tuple>
struct TuplePrinter<Tuple, 1> {
  static void print(const Tuple& t) { std::cout << std::get<0>(t); }
};

template <class... Args>
void
print(const std::tuple<Args...>& t)
{
  const size_t N = sizeof...(Args);
  std::cout << '{';
  TuplePrinter<decltype(t), N>::print(t);
  std::cout << '}';
}
// end helper function

using MyTuple = std::tuple<int, std::string, bool>;

std::ostream&
operator<<(std::ostream& a_os, const MyTuple& value)
{
  a_os << '{' << std::get<0>(value) << ", " << std::get<1>(value) << ", " << std::get<2>(value) << '}';
  return a_os;
}

} // namespace

void
ABcb::cpp11::UsingTuple()
{
  std::clog << __func__ << " started..." << std::endl;

  const size_t N = std::tuple_size<MyTuple>::value;
  std::clog << pad << "The size of MyTuple is " << N << std::endl;

  const MyTuple myTuple{16, "Test", true};
  std::cout << pad << "typeid of get<0>(myTuple) = " << typeid(std::get<0>(myTuple)).name() << std::endl;
  std::cout << pad << "typeid of get<1>(myTuple) = " << typeid(std::get<1>(myTuple)).name() << std::endl;
  std::cout << pad << "typeid of get<2>(myTuple) = " << typeid(std::get<2>(myTuple)).name() << std::endl;
  std::cout << pad << "myTuple = " << myTuple << " should be equal to ";
  print(myTuple);
  std::cout << std::endl;

  const std::vector myTuples = {myTuple, {42, "foo", false}};
  std::cout << pad << ToString(myTuples, "myTuples") << std::endl;

  std::clog << __func__ << " finished." << std::endl;
}

void
ABcb::cpp11::AlgorithmExamples()
{
  std::clog << __func__ << " started..." << std::endl;

  const std::vector v{3, 9, 1, 4, 2, 5, 9};
  std::cout << ToString(v, pad + "v") << std::endl;
  const auto [minIt, maxIt] = // C++17 structured binding
    std::minmax_element(v.cbegin(), v.cend());
  std::cout << pad << pad << "v's min element is " << *minIt << ", at index " << (minIt - v.cbegin()) << '\n'
            << pad << pad << "v's max element is " << *maxIt << ", at index " << (maxIt - v.cbegin()) << std::endl;

  const auto [f1, f2] = std::tuple(12.f, 7.f); // C++17 structured binding
  // '- Using the "Exception" of the
  // https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#Res-name-one
  //    ES.10: Declare one name (only) per declaration
  const auto [min, max] = // C++17 structured binding
    std::minmax(f1, f2);
  std::cout << pad << "f1 = " << f1 << ", f2 = " << f2 << '\n'
            << pad << pad << "min of {f1, f2} = " << min << '\n'
            << pad << pad << "max of {f1, f2} = " << max << std::endl;

  std::clog << __func__ << " finished." << std::endl;
}

void
ABcb::cpp11::MiscellanyExamples()
{
  std::clog << __func__ << " started..." << std::endl;

  std::cout << pad << "PrintList (variadic template function): ";
  PrintList(1, 2, 'c', "Hello, world!", 666.);

  std::cout << pad << "initializer_list-based range-for example: "
            << "for (int prime : { 2, 3, 5, 7 }) > ";
  for (int prime : {2, 3, 5, 7}) // initializer_list-based range-for example
    std::cout << prime << ' ';
  std::cout << std::endl;

  // std::ratio stuff
  //
  using ratioA = std::ratio<1, 3>;
  using ratioB = std::ratio<2, 4>;
  using sum = std::ratio_add<ratioA, ratioB>;
  std::cout << pad << "std::ratio and std::ratio_add example: " << ratioA::num << "/" << ratioA::den << " + "
            << ratioB::num << "/" << ratioB::den << " = " << sum::num << "/" << sum::den << " = "
            << static_cast<double>(sum::num) / sum::den << std::endl;

  std::clog << __func__ << " finished." << std::endl;
}
