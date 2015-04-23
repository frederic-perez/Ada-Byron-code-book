// -- 

#include <iostream>
#include <string>
#include <vector>

#include "aux-raw.h"

namespace ABcb = Ada_Byron_code_book;

namespace {

template <typename T>
void
Output(const T& a_t, const std::string& a_name)
{
	std::cout << a_name << " = ";
	if (a_t.empty())
		std::cout << "[empty]" << std::endl;
	else {
		std::cout << "{ ";
		for (auto value : a_t)
			std::cout << value << ' ';
		std::cout << '}' << std::endl;
	}
}

} // namespace

void
ABcb::raw::ExamplesOfRaw()
{
	std::clog << __func__ << " started..." << std::endl;

	const std::string pad = "  ";

	std::vector<int> myVector{ 4, 3, 2, 1 };
	Output(myVector, pad + "myVector (after construction)");
	ABcb::raw::WipeOut(myVector);
	Output(myVector, pad + "myVector (after WipeOut call)");

	std::clog << __func__ << " finished." << std::endl;
}

// -- eof
