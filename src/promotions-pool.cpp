// -- Examples on promotions ("implicit conversions that preserve values")

#include <iostream>
#include <typeinfo>

#include "aux-raw.h"
#include "promotions-pool.h"

namespace ABcb = Ada_Byron_code_book;
using ABcb::raw::pad;

namespace {

template <typename T>
void
Output(const std::string& a_message, const T a_t)
{
  std::cout << pad << a_message << " = " << a_t << " is of type \'" << typeid(a_t).name() << '\'' << std::endl;
}

} // namespace

void
ABcb::ExamplesOfPromotions()
{
  std::clog << __func__ << " started..." << std::endl;

  Output("1.F + 2U", 1.F + 2U);
  Output("1. + 2U", 1. + 2U);
  Output("1.F - 2.", 1.F - 2.);
  Output("0U - 2U", 0U - 2U);
  Output("0U - 2", 0U - 2);
  Output("0 - 2U", 0 - 2U);
  Output("0 - 2UL", 0 - 2UL);
  Output("0 - 2L", 0 - 2L);
  Output("0 - 2", 0 - 2);
  Output("0 - static_cast<int>(2U)", 0 - static_cast<int>(2U));
  Output("0 - size_t(2)", 0 - size_t(2));

  std::clog << __func__ << " finished." << std::endl;
}
