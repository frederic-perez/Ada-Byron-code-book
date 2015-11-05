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
	std::cout << pad << a_message << " = " << a_t << " is of type \'"
		<< typeid(a_t).name() << '\'' << std::endl;
}

}

void
ABcb::ExamplesOfPromotions()
{
	std::clog << __func__ << " started..." << std::endl;

	Output("1.f + 2u", 1.f + 2u);
	Output("1. + 2u", 1. + 2u);
	Output("1.f - 2.", 1.f - 2.);
	Output("0u - 2u", 0u - 2u);
	Output("0u - 2", 0u - 2);
	Output("0 - 2u", 0 - 2u);
	Output("0 - 2ul", 0 - 2ul);
	Output("0 - 2l", 0 - 2l);
	Output("0 - 2", 0 - 2);
	Output("0 - static_cast<int>(2u)", 0 - static_cast<int>(2u));
	Output("0 - size_t(2)", 0 - size_t(2));

#undef ADA_BYRON_TRYING_STATIC_ASSERT_20150525
#ifdef ADA_BYRON_TRYING_STATIC_ASSERT_20150525
	const auto idx = static_cast<int>(0) - static_cast<int>(2);
	Output(
		"static_cast<int>(0) - static_cast<int>(2)",
		static_cast<int>(0) - static_cast<int>(2));
	static_assert(idx >= 0, "Compiler error message--trying static_assert");
#endif

	std::clog << __func__ << " finished." << std::endl;
}

// -- eof
