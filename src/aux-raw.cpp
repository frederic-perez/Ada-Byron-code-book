// -- 

#include <iostream>
#include <string>
#include <vector>

#include "aux-raw.h"
#include "aux-spy.h"

namespace ABcb = Ada_Byron_code_book;

char
ABcb::raw::SystemSlash()
{
#if defined(__CYGWIN__) || defined(__GNUC__)
	return '/';
#else
	return '\\';
#endif
}

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
	spy::Output(std::cout, myVector, pad + "myVector (after construction)");
	ABcb::raw::WipeOut(myVector);
	spy::Output(std::cout, myVector, pad + "myVector (after WipeOut call)");

	std::clog << __func__ << " finished." << std::endl;
}

// -- eof
