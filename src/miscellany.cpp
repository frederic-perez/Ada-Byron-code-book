#include <iomanip>
#include <sstream>
#include <stdexcept>

#include <boost/log/trivial.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/numeric/conversion/bounds.hpp>

#include "aux-raw.h"
#include "miscellany.h"

namespace ABcb = Ada_Byron_code_book;

void
ABcb::miscellany::ExampleOfRawStringLiteral()
{
  BOOST_LOG_TRIVIAL(info) << __func__ << ": " << R"(C:\life\brian\foo.pdf)";
}

void
ABcb::miscellany::Function(const int value)
// notice the "const" above (see header file with the function declaration)
{
  BOOST_LOG_TRIVIAL(info) << __func__ << ": value=" << value;
}

size_t
ABcb::miscellany::FactorialRecursive(const size_t n)
{
  if (n <= 1)
    return 1;

  const size_t factorialRecursiveNMinus1 = FactorialRecursive(n - 1);
  const size_t result = n * factorialRecursiveNMinus1;
  static const size_t max = boost::numeric::bounds<size_t>::highest();
  //
  // Interesting information on std::overflow_error available at
  // http://en.cppreference.com/w/cpp/error/overflow_error
  //
  // TODO: Study en.cppreference.com/w/cpp/error/overflow_error and apply it!
  //
  if (const bool overflow = n > max / factorialRecursiveNMinus1; overflow) {
    // '- overflow of a * b \equiv a * b > max \equiv a > max/b
    std::ostringstream oss;
    oss << "Overflow trying to compute " << __func__ << '(' << n << ')';
    throw std::overflow_error(oss.str());
  }

  return result;
}

constexpr size_t
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
  BOOST_LOG_TRIVIAL(trace) << __func__ << " started...";

  using ABcb::raw::pad;

  // Using FactorialCompileTime
  //
  // const size_t N = 21; // < integral constant overflow in vs14
  const size_t N = 20; // < integral constant overflow in vs14
  const size_t factorialCompileTime = FactorialCompileTime<N>::d_value; // == 24
  std::ostringstream oss;
  oss.imbue(std::locale("")); // To add commas when outputting result
  oss << factorialCompileTime;
  BOOST_LOG_TRIVIAL(info)
    << pad << "FactorialCompileTime<" << N << ">::d_value = " << oss.str();

  static_assert(FactorialCompileTime<1>::d_value == 1);
  static_assert(FactorialCompileTime<4>::d_value == 24);

  // Using FactorialRecursive
  //
  size_t n = 0;
  for (bool overflow = false; !overflow;) {
    ++n;
    try {
      FactorialRecursive(n);
    } catch (const std::overflow_error& e) {
      BOOST_LOG_TRIVIAL(error) << pad << __func__ << ": Exception caught: " << e.what();
      overflow = true;
    }
  }

  --n;
  const size_t factorialN = FactorialRecursive(n);
  oss.str("");
  oss << factorialN;
  BOOST_LOG_TRIVIAL(info)
    << pad << "FactorialRecursive(" << n << ")            = " << oss.str();

  // Using FactorialIterative
  //
  const size_t factorialIterative = FactorialIterative(n);
  oss.str("");
  oss << factorialIterative;
  BOOST_LOG_TRIVIAL(info)
    << pad << "FactorialIterative(" << n << ")            = " << oss.str();

  static_assert(FactorialIterative(1) == 1);
  static_assert(FactorialIterative(4) == 24);

  BOOST_LOG_TRIVIAL(trace) << __func__ << " finished.";
}

namespace {

template <typename T>
T
AreaOfACircle(const T r)
{
  return boost::math::constants::pi<T>() * r * r; // Notice the nice pi used
}

} // namespace

void
ABcb::miscellany::ExamplesOfMultiprecision()
{
  BOOST_LOG_TRIVIAL(trace) << __func__ << " started...";

  using ABcb::raw::pad;

  // Code based on
  //   http://www.boost.org/doc/libs/1_59_0/libs/multiprecision/
  //   doc/html/boost_multiprecision/tut/floats/fp_eg/aos.html

  const float r_f = 123.f / 100.f;
  const float a_f = AreaOfACircle(r_f);
  BOOST_LOG_TRIVIAL(info) << pad << std::setprecision(std::numeric_limits<float>::digits10) << a_f;

  const double r_d = 123. / 100.;
  const double a_d = AreaOfACircle(r_d);
  BOOST_LOG_TRIVIAL(info) << pad << std::setprecision(std::numeric_limits<double>::digits10) << a_d;

  using boost::multiprecision::cpp_dec_float_50;
  const cpp_dec_float_50 r_mp(cpp_dec_float_50(123) / 100);
  const cpp_dec_float_50 a_mp = AreaOfACircle(r_mp);
  BOOST_LOG_TRIVIAL(info) << pad << std::setprecision(std::numeric_limits<cpp_dec_float_50>::digits10) << a_mp;

  BOOST_LOG_TRIVIAL(trace) << __func__ << " finished.";
}
