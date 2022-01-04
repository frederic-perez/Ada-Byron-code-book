// -- Examples on promotions ("implicit conversions that preserve values")

#include <typeinfo>

#include <boost/log/trivial.hpp>

#include "aux-raw.h"
#include "promotions-pool.h"

namespace ABcb = Ada_Byron_code_book;
using ABcb::raw::pad;

namespace {

template <typename T>
void
Log(const std::string& a_message, const T a_t)
{
  BOOST_LOG_TRIVIAL(info)
    << pad << a_message << " = " << a_t << " is of type \'" << typeid(a_t).name() << '\'';
}

} // namespace

void
ABcb::ExamplesOfPromotions()
{
  BOOST_LOG_TRIVIAL(trace) << __func__ << " started...";

  Log("1.F + 2U", 1.F + 2U);
  Log("1. + 2U", 1. + 2U);
  Log("1.F - 2.", 1.F - 2.);
  Log("0U - 2U", 0U - 2U);
  Log("0U - 2", 0U - 2);
  Log("0 - 2U", 0 - 2U);
  Log("0 - 2UL", 0 - 2UL);
  Log("0 - 2L", 0 - 2L);
  Log("0 - 2", 0 - 2);
  Log("0 - static_cast<int>(2U)", 0 - static_cast<int>(2U));
  Log("0 - size_t(2)", 0 - size_t(2));

  BOOST_LOG_TRIVIAL(trace) << __func__ << " finished.";
}
