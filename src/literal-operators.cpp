#include "literal-operators.h"

#include "aux-raw.h"
#include "aux-spy.h"

#include <algorithm>
#include <iostream>

namespace ABcb = Ada_Byron_code_book;

namespace {

using Ada_Byron_code_book::raw::pad;

void
ExampleOfSSuffixStringLiteral()
{
  using namespace std::string_literals; // enables s-suffix for std::string literals

  const auto foo = "Hello, world!"s; // auto deduces std::string
  // '- See https://en.wikipedia.org/wiki/C%2B%2B14#Standard_user-defined_literals
  std::clog << pad << "foo = `" << foo
            << "`; spy::TypeNameENH of foo's decltype = " << ABcb::spy::TypeNameENH<decltype(foo)>() << std::endl;
}

void
ExampleOfUnsignedCharLiteral()
{
  using ABcb::literal_operators::operator"" _uchar;
#undef FPCX_MIXING_UNSIGNED_CHAR_WITH_INTEGER_20210130
#if defined(FPCX_MIXING_UNSIGNED_CHAR_WITH_INTEGER_20210130)
  const auto result = std::min(42_uchar, 66);
  // '- Compiler error: No instance of overloaded function "std::min" matches the argument list
#else
  const auto result = std::min(42_uchar, static_cast<unsigned char>(66)); // OK, same type
#endif
  std::clog << pad << "std::min(42_uchar, static_cast<unsigned char>(66)) returned (as size_t) "
            << static_cast<size_t>(result) << std::endl;
}

} // namespace

void
ABcb::literal_operators::Examples()
{
  std::clog << __func__ << " started..." << std::endl;

  ExampleOfSSuffixStringLiteral();
  ExampleOfUnsignedCharLiteral();

  std::clog << __func__ << " finished." << std::endl;
}
