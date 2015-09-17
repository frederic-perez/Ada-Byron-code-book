// -- 

#include <iostream>
#include <sstream>

#include "aux-raw-compiler-warnings-off++begin.h"

	#include <boost/algorithm/string.hpp>

#include "aux-raw-compiler-warnings-off++end.h"

#include "aux-raw.h"
#include "under-construction.h"

namespace ABcb = Ada_Byron_code_book;

// TODO: Add point cloud binary file I/O
// TODO: Add example point cloud file in data folder
// TODO: Move point cloud-related code to new source files
// TODO: Point cloud file: endianness control

#undef ADA_BYRON_PARSING_WITH_ISTRINGSTREAM_IS_EASY_20150626
#ifdef ADA_BYRON_PARSING_WITH_ISTRINGSTREAM_IS_EASY_20150626
// TODO
// NOTE: Parsing using std::istringstream is easy
#include <sstream>

std::string line;
while (getline(fileI, line))
	if (!line.empty()) {
		std::istringstream parse(line);
		double x, y;
		parse >> x >> y;
		// do stuff with x and y
	}
#endif

namespace Ada_Byron_code_book {

namespace Guru {
	const uint8_t first = 1;
	const uint8_t last = static_cast<uint8_t>(enumText.size() - 1);
} // namespace Guru

} // namespace Ada_Byron_code_book

auto
ABcb::Guru::GetEnum(const std::string& a_text)
-> Enum
{
	uint8_t i = first;
	for (; i <= last && a_text != enumText[i]; ++i);
	if (i <= last)
		return static_cast<Enum>(i);
	return Enum::undefined;
}

std::string
ABcb::Guru::GetString(Enum a_enum)
{
	return enumText[static_cast<uint8_t>(a_enum)];
}

std::vector<std::string>
ABcb::Guru::GetDefinedStrings()
{
	std::vector<std::string> result;
	uint8_t i = first;
	for (; i <= last; ++i)
		result.push_back(enumText[i]);
	return result;
}

namespace {

void
GuruTest(const std::string& a_text)
{
	using namespace ABcb;
	Guru::Enum guru = Guru::GetEnum(a_text);
	using raw::pad;
	if (guru == Guru::Enum::undefined) {
		const std::string message =
			"Unknown guru parameter '" + a_text + "'";

		std::ostringstream oss;
		std::vector<std::string> definedStrings = Guru::GetDefinedStrings();
		oss << '{' << boost::algorithm::join(definedStrings, ", ") << '}';
		const std::string setOfDefinedStrings = oss.str();

		std::cerr << pad << __func__ << ": " << message << '\n'
			<< pad << pad << "--guru arg " << setOfDefinedStrings << '\n';

	} else
		std::cout << pad << __func__ << ": guru = " << a_text << std::endl;
}

} // namespace

void
ABcb::GurusTest(std::initializer_list<std::string> a_args)
{
	std::cout << __func__ << " called" << std::endl;
	for (auto text : a_args)
		GuruTest(text);
}

// -- eof
