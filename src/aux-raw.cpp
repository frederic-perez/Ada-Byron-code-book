// -- 

#include <iostream>
#include <string>
#include <vector>

#include "aux-raw.h"

namespace ABcb = Ada_Byron_code_book;

namespace {

template<typename T>
void
Output(const T* a_t, size_t a_size, const std::string& a_name)
{
	std::cout << a_name << " = ";
	if (a_size == 0)
		std::cout << "[empty]" << std::endl;
	else {
		std::cout << "{ ";
		for (size_t i=0; i < a_size; ++i)
			std::cout << a_t[i] << ' ';
		std::cout << '}' << std::endl;
	}
}

template<typename T>
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
	const double myCArray[3] = { 1., 2., 3. };
	Output(
		myCArray, ABcb::raw::ArraySize(myCArray),
		pad + "myCArray (after construction)");

	std::vector<int> myVector{ 4, 3, 2, 1 };
	Output(myVector, pad + "myVector (after construction)");
	ABcb::raw::WipeOut(myVector);
	Output(myVector, pad + "myVector (after WipeOut call)");

	std::clog << __func__ << " finished." << std::endl;
}

// -- eof
