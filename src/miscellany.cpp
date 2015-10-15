// -- 

#include <iostream>

#include "miscellany.h"

namespace ABcb = Ada_Byron_code_book;

void
ABcb::miscellany::Function(const int a_value) // <-- notice the "const" here
{	std::cout << __func__ << ": a_value=" << a_value << std::endl; }

// -- eof
