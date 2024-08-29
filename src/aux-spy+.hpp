#ifndef ADA_BYRON_CODE_BOOK__AUX_SPY_PLUS_HPP
#define ADA_BYRON_CODE_BOOK__AUX_SPY_PLUS_HPP

#if !defined(_MSC_VER)
#  include <cxxabi.h>
#endif
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>

#include <boost/noncopyable.hpp>

namespace Ada_Byron_code_book::spy {

std::string GetBoostVersion();
std::string GetClangVersion();
std::string GetGNUGppVersion();
std::string GetVisualStudioCppCompilerVersion();

std::string GetUserName();
std::string GetLocalDate();
std::string GetLocalTime();

void LogInfoOfSomeTypes();

class RunInfo : private boost::noncopyable {
public:
  explicit RunInfo(std::string a_argv0, std::string a_progname)
  : d_argv0{ std::move(a_argv0) },
    d_progname{ std::move(a_progname) }
  {}

  void Log() const;

private:
  const std::string d_argv0;
  const std::string d_progname;
};

template <typename TClock>
class Timer : private boost::noncopyable {
  //
  // Based on the example under
  // http://www.boost.org/doc/libs/1_47_0/doc/html/chrono/users_guide.html
  // #chrono.users_guide.examples.time_point.a_tiny_program_that_times_how_
  // long_until_a_key_is_struck
  //
  // Notice that `chrono` is part of the standard since C++11.
  //
  // Some possible instantiations
  // ----------------------------
  // - std::chrono::system_clock
  // - std::chrono::steady_clock // GCC duplicate?
  // - std::chrono::high_resolution_clock
  //
public:
  Timer() = default;
  auto Elapsed() const -> typename TClock::duration;
  auto Seconds() const -> double;
  auto Seconds(size_t precision) const -> std::string;

  void Reset();

private:
  typename TClock::time_point d_start = TClock::now();
};

// Consider this function instead of using typeid(-).name,
// with T being a type, or `decltype(variable)`, for example
//
template <class T>
auto
TypeNameENH11() // Using C++11
-> std::string
{
  // Credits to
  // https://stackoverflow.com/questions/81870/print-variable-type-in-c
  //
  typedef typename std::remove_reference<T>::type TR;
  std::unique_ptr<char, void (*)(void*)> own(
#if !defined(_MSC_VER)
    abi::__cxa_demangle(typeid(TR).name(), nullptr, nullptr, nullptr),
#else
    nullptr,
#endif
    std::free);
  std::string r = own != nullptr ? own.get() : typeid(TR).name();
//#include "aux-raw-compiler-warnings-off++begin.h"
  if (std::is_const<TR>::value)
    r += " const";
  if (std::is_volatile<TR>::value)
    r += " volatile";
  if (std::is_lvalue_reference<T>::value)
    r += "&";
  else if (std::is_rvalue_reference<T>::value)
    r += "&&";
//#include "aux-raw-compiler-warnings-off++end.h"
  return r;
}

// Consider this function instead of using typeid(-).name,
// with T being a type, or `decltype(variable)`, for example
//
template <typename T>
constexpr auto
TypeNameENH() // Using C++17
{
  // Credits to
  // https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c/56766138#56766138
  //
#ifdef __clang__
  std::string_view name = __PRETTY_FUNCTION__;
  std::string_view prefix = "auto Ada_Byron_code_book::spy::TypeNameENH() [T = ";
  std::string_view suffix = "]";
#elif defined(__GNUC__)
  std::string_view name = __PRETTY_FUNCTION__;
  std::string_view prefix = "constexpr auto Ada_Byron_code_book::spy::TypeNameENH() [with T = ";
  std::string_view suffix = "]";
#elif defined(_MSC_VER)
  std::string_view name = __FUNCSIG__;
  std::string_view prefix = "auto __cdecl Ada_Byron_code_book::spy::TypeNameENH<";
  std::string_view suffix = ">(void)";
#endif
  name.remove_prefix(prefix.size());
  name.remove_suffix(suffix.size());
  return name;
}

} // namespace Ada_Byron_code_book::spy

// ToString: helper function to get a string from the values of a tuple of any size
// Based on http://en.cppreference.com/w/cpp/utility/tuple/tuple
// Notice that we define this function in the global namespace

template <class Tuple, std::size_t N>
struct TupleToString {
  static std::string toString(const Tuple& t)
  {
    std::ostringstream oss;
    oss << TupleToString<Tuple, N - 1>::toString(t) << ", " << std::get<N - 1>(t);
    return oss.str();
  }
};

template <class Tuple>
struct TupleToString<Tuple, 1> {
  static std::string toString(const Tuple& t)
  {
    std::ostringstream oss;
    oss << std::get<0>(t);
    return oss.str();
  }
};

template <class... Args>
std::string
ToString(const std::tuple<Args...>& t)
{
  std::ostringstream oss;
  const size_t N = sizeof...(Args);
  oss << '{' << TupleToString<decltype(t), N>::toString(t) << '}';
  return oss.str();
}

// end helper function

// Function that allows output of containers with basic, enum class values, glm::fvec3, etc.
// Notice that we define this in the global namespace—this is on purpose to try to avoid
// name lookup problems (see 
// https://stackoverflow.com/questions/5195512/namespaces-and-operator-resolution).
// - For basic/common types, it can be used directly, since operator<< is defined by C++ for
//   those types.
// - For enum class values, it requires the existence of
//     std::ostream& operator<<(std::ostream&, MyEnumClass)
//   which could be defined, for examples, as
//     std::ostream& operator<<(std::ostream& a_os, MyEnumClass a_value) {
//       a_os << as_string(a_value); // NOSONAR
//       return a_os; // NOSONAR
//     }
// - For non-basic classes like, for example, glm::fvec3 (an instantiation of a template
//   struct), we need to define:
//     namespace glm { // required by clang++
//     std::ostream& operator<<(std::ostream& a_os, const fvec3& value) {
//       a_os << to_string(value); // NOSONAR
//       return a_os; // NOSONAR
//     }
//     } // namespace glm
//   Another example: for a tuple, we could do something like this:
//     using MyTuple = std::tuple<int, std::string, bool>; // NOSONAR
//     std::ostream& operator<<(std::ostream& a_os, const MyTuple& value) {
//       a_os << '{' << std::get<0>(value) << ", " << std::get<1>(value) << ", "
//            << std::get<2>(value) << '}'; // NOSONAR
//       return a_os; // NOSONAR
//     }
//     or this very compact definition by using ToString for tuples:
//     std::ostream& operator<<(std::ostream& a_os, const MyTuple& value) {
//       return a_os << ToString(value); // NOSONAR
//     }
// Usage example:
//   std::clog << ... << ToString(myContainer, "myContainer") << ...; // NOSONAR
//
template <typename TContainer>
std::string
ToString(const TContainer& a_container, const std::string& a_containerName)
{
  std::ostringstream oss;
  oss << (a_containerName.empty() ? "[unnamed]" : a_containerName) << " = ";
  if (a_container.empty()) {
    oss << "[0]{}";
  } else {
    const size_t N = a_container.size();
    oss << "[" << N << "]{";
    size_t i = 0;
    for (const auto element : a_container) { // this allows using set<T> as a parameter
      oss << element;
      if (i < N - 1) {
        oss << ", ";
      }
      ++i;
    }
    oss << '}';
  }
  return oss.str();
}

// Function that allows output of old C arrays with basic, enum class values, etc.
// (see comments for usage at the function above)
//
template <typename T>
std::string
ToString(const T* a_oldCArray, size_t a_size, const std::string& a_name)
{
  std::ostringstream oss;
  oss << (a_name.empty() ? "[unnamed]" : a_name) << " = ";
  if (a_size == 0) {
    oss << "[0]{}";
  } else {
    oss << "[" << a_size << "]{";
    for (size_t i = 0; i < a_size; ++i) {
      oss << a_oldCArray[i];
      if (i < a_size - 1) {
        oss << ", ";
      }
    }
    oss << '}';
  }
  return oss.str();
}

#endif // ADA_BYRON_CODE_BOOK__AUX_SPY_PLUS_HPP
