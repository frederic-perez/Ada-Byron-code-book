// -- Examples on how to use C++11 features, and some other stuff

#include <algorithm>
#include <ratio>
#include <tuple>
#include <vector>

#include "aux-raw.h" // for pad
#include "aux-spy+.h" // for ToString, TypeNameENH
#include "cpp11-pool.h"
#include "log.h"

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
  B_LOG_INFO << __func__ << ": array[1] is " << array[1]; // BOOM
#else
  B_LOG_INFO << __func__ << ": Note: ASAN_TEST was not defined";
#endif
}

void
ABcb::cpp11::TestIfAConstParameterCanBeModified(const int value)
{
#if defined(__GNUG__) || defined(WIN32)
  int i = value;
  ++i; // Silly operations to avoid compiler warnings
#else
  value = 0; // Error in VS 2022, VS 2012, g++ 4.8.2, clang++ 3.4-1
#endif
}

namespace {

using MyTuple = std::tuple<int, std::string, bool>;

std::ostream&
operator<<(std::ostream& a_os, const MyTuple& value)
{
  return a_os << ToString(value);
}

} // namespace

void
ABcb::cpp11::UsingTuple()
{
  B_LOG_TRACE_STARTED

  const size_t N = std::tuple_size<MyTuple>::value;
  B_LOG_INFO << pad << "The size of MyTuple is " << N;

  const MyTuple myTuple{16, "Test", true};
  B_LOG_INFO
    << pad << "spy::TypeNameENH of decltype(get<0>(myTuple)) = " << spy::TypeNameENH<decltype(std::get<0>(myTuple))>();
  B_LOG_INFO
    << pad << "spy::TypeNameENH of decltype(get<1>(myTuple)) = " << spy::TypeNameENH<decltype(std::get<1>(myTuple))>();
  B_LOG_INFO
    << pad << "spy::TypeNameENH of decltype(get<2>(myTuple)) = " << spy::TypeNameENH<decltype(std::get<2>(myTuple))>();
  {
    std::ostringstream oss;
    oss << myTuple;
    B_LOG_INFO << pad << "myTuple = " << oss.str() << " should be equal to " << ToString(myTuple);
  }

  const std::vector myTuples = {myTuple, {42, "foo", false}};
  B_LOG_INFO << pad << ToString(myTuples, "myTuples");

  B_LOG_TRACE_FINISHED
}

void
ABcb::cpp11::AlgorithmExamples()
{
  B_LOG_TRACE_STARTED

  const std::vector v{3, 9, 1, 4, 2, 5, 9};
  B_LOG_INFO << ToString(v, pad + "v");
  const auto [minIt, maxIt] = // C++17 structured binding
    std::minmax_element(v.cbegin(), v.cend());
  B_LOG_INFO << pad << pad << "v's min element is " << *minIt << ", at index " << minIt - v.cbegin();
  B_LOG_INFO << pad << pad << "v's max element is " << *maxIt << ", at index " << maxIt - v.cbegin();

  const auto [f1, f2] = std::tuple(12.f, 7.f); // C++17 structured binding
  // '- Using the "Exception" of the
  // https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#Res-name-one
  //    ES.10: Declare one name (only) per declaration
  const auto [min, max] = // C++17 structured binding
    std::minmax(f1, f2);
  B_LOG_INFO << pad << "f1 = " << f1 << ", f2 = " << f2;
  B_LOG_INFO << pad << pad << "min of {f1, f2} = " << min;
  B_LOG_INFO << pad << pad << "max of {f1, f2} = " << max;

  B_LOG_TRACE_FINISHED
}

void
ABcb::cpp11::MiscellanyExamples()
{
  B_LOG_TRACE_STARTED

  B_LOG_INFO
    << pad << "ListToString (variadic template function): "
    << ListToString(1, 2, 'c', "Hello, world!", 666.);

  {
    std::ostringstream oss;
    for (const auto prime : { 2, 3, 5, 7 }) // initializer_list-based range-for example
      oss << prime << ' ';
    B_LOG_INFO
      << pad << "initializer_list-based range-for example: "
      << "for (const auto prime : { 2, 3, 5, 7 }) > " << oss.str();
  }

  // std::ratio stuff
  //
  using ratioOneThree = std::ratio<1, 3>;
  using ratioTwoFour = std::ratio<2, 4>;
  using sum = std::ratio_add<ratioOneThree, ratioTwoFour>;
  B_LOG_INFO
    << pad << "std::ratio and std::ratio_add example: " << ratioOneThree::num << "/" << ratioOneThree::den << " + "
    << ratioTwoFour::num << "/" << ratioTwoFour::den << " = " << sum::num << "/" << sum::den << " = "
    << static_cast<double>(sum::num) / sum::den;

  B_LOG_TRACE_FINISHED
}
