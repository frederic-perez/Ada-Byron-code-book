// -- 

#pragma once

#include <ostream>

namespace Ada_Byron_code_book {

namespace spy {

std::ostream& BoostVersion(std::ostream&);

#ifdef __GNUG__
#define MY_GNUGPP_VERSION (__GNUC__ * 10000 \
	+ __GNUC_MINOR__ * 100 \
	+ __GNUC_PATCHLEVEL__)
// #if MY_GNUGPP_VERSION > 30200 // Test for GCC > 3.2.0
#endif

std::ostream& GNUGppVersion(std::ostream&);

} // namespace spy

} // namespace Ada_Byron_code_book

// -- eof
