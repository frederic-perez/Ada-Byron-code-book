#pragma once

#if !defined(_MSC_VER)
#  include <cxxabi.h>
#endif
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>

#include <boost/noncopyable.hpp>

//!? TODO: Possibly extend SpyLine with Boost's PP for extra information

#define SpyLine std::cerr << "@@@@ " << __FILE__ << ':' << __func__ << ":L" << __LINE__ << '\n';

namespace Ada_Byron_code_book::spy {

auto BoostVersion(std::ostream&) -> std::ostream&;
auto ClangVersion(std::ostream&) -> std::ostream&;
auto GNUGppVersion(std::ostream&) -> std::ostream&;
auto VisualStudioCppCompilerVersion(std::ostream&) -> std::ostream&;

auto HostName(std::ostream&) -> std::ostream&;
auto UserName(std::ostream&) -> std::ostream&;
auto LocalDate(std::ostream&) -> std::ostream&;
auto LocalTime(std::ostream&) -> std::ostream&;
auto InfoOfSomeTypes(std::ostream&) -> std::ostream&;

class RunInfo; // To be used like std::cout << RunInfo("my-progname") << ...
auto operator<<(std::ostream&, const RunInfo&) -> std::ostream&;

class RunInfo : boost::noncopyable {
public:
  explicit RunInfo(std::string a_argv0, std::string a_progname)
  : d_argv0{ std::move(a_argv0) },
    d_progname{ std::move(a_progname) }
  {}

  auto GetArgv0() const -> const std::string& { return d_argv0; }
  auto GetProgName() const -> const std::string& { return d_progname; }

private:
  const std::string d_argv0;
  const std::string d_progname;
};

// Function that allows output of containers with basic, enum class values, glm::fvec3, etc.
// - For basic/common types, it can be used directly, since operator<< is defined by C++ for
//   those types.
// - For enum class values, it requires the existence of
//     std::ostream& operator<<(std::ostream&, MyEnumClass)
//   which could be defined, for examples, as
//     std::ostream& operator<<(std::ostream& a_os, MyEnumClass a_value) {
//       a_os << as_string(a_value);
//       return a_os;
//     }
// - For non-basic classes like, for example, glm::fvec3 (an instantiation of a template 
//   struct), we need to define:
//     namespace glm { // required by clang++
//     std::ostream& operator<<(std::ostream& a_os, const fvec3& value) {
//       a_os << to_string(value);
//       return a_os;
//     }
//     } // namespace glm
// Usage example: std::clog << ... << ToString(myContainer, "myContainer") << ...;
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
    for (size_t i = 0; i < N; ++i) {
      oss << a_container[i];
      if (i < N - 1) {
        oss << ", ";
      }
    }
    oss << '}';
  }
  return oss.str();
}

// Function that allows output of old C arrays with basic, enum class values, etc.
// (see comments for the function above)
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

template <typename TClock>
class Timer : boost::noncopyable {
  //
  // Based on the example under
  // http://www.boost.org/doc/libs/1_47_0/doc/html/chrono/users_guide.html
  // #chrono.users_guide.examples.time_point.a_tiny_program_that_times_how_
  // long_until_a_key_is_struck
  //
  // Notice that `chrono` is part of the standard since C++11.
  //
  // Examples
  // --------
  // Timer<std::chrono::system_clock> t1;
  // Timer<std::chrono::steady_clock> t2; // GCC duplicate?
  // Timer<std::chrono::high_resolution_clock> t3;
  //
public:
  Timer();
  auto Elapsed() const -> typename TClock::duration;
  auto Seconds() const -> double;
  auto Seconds(size_t precision) const -> std::string;

  void Reset();

protected:
  typename TClock::time_point d_start;
};

// Consider this function instead of using typeid(-).name
//
template <class T>
auto
TypeNameENH()
-> std::string
{
  // Credits to
  // http://stackoverflow.com/questions/81870/print-variable-type-in-c
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
#include "aux-raw-compiler-warnings-off++begin.h"
  if (std::is_const<TR>::value)
    r += " const";
  if (std::is_volatile<TR>::value)
    r += " volatile";
  if (std::is_lvalue_reference<T>::value)
    r += "&";
  else if (std::is_rvalue_reference<T>::value)
    r += "&&";
#include "aux-raw-compiler-warnings-off++end.h"
  return r;
}

} // namespace Ada_Byron_code_book::spy
