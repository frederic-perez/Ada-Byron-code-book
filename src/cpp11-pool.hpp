// -- Examples on how to use some C++11 functionalities

#ifndef ADA_BYRON_CODE_BOOK__CPP11_POOL_HPP
#define ADA_BYRON_CODE_BOOK__CPP11_POOL_HPP

#include <sstream>
#include <string>

namespace Ada_Byron_code_book::cpp11 {

void TryBadCode();
void TestIfAConstParameterCanBeModified(int);
void UsingTuple();
void AlgorithmExamples();
void MiscellanyExamples();

// Variadic template and related basic template

template <typename T>
std::string
ListToString(T a_last)
{
  std::ostringstream oss;
  oss << a_last;
  return oss.str();
}

template <typename Arg1, typename... Args>
std::string
ListToString(Arg1 a_first, Args... a_rest)
{
  std::ostringstream oss;
  oss << a_first << ", " << ListToString(a_rest...);
  return oss.str();
}

// Example of usage of the "override" keyword

class Base {
  virtual void Function(int) const {}
#define ABcb_needed_to_avoid_compiler_error_20150917
#if defined(ABcb_needed_to_avoid_compiler_error_20150917)
  virtual void Function(size_t) const {}
#endif
};

class Derived : public Base {
  void Function(size_t) const override {}
  // '- Note: It is better typing "override" than "virtual" (when overriding)
};

} // namespace Ada_Byron_code_book::cpp11

#endif // ADA_BYRON_CODE_BOOK__CPP11_POOL_HPP
