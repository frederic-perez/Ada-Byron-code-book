// -- 

#include <iostream>
#include <sstream>

#include "aux-raw-compiler-warnings-off.h"

	#include <boost/algorithm/string.hpp>

#include "aux-raw-compiler-warnings-on.h"

#include "aux-raw.h"
#include "under-construction.h"

namespace ABcb = Ada_Byron_code_book;

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

void
ABcb::GuruTest(const std::string& a_text)
{
	Guru::Enum guru = Guru::GetEnum(a_text);
	if (guru == Guru::Enum::undefined) {
		const std::string message =
			"Unknown guru parameter '" + a_text + "'";

		std::ostringstream oss;
		std::vector<std::string> definedStrings = Guru::GetDefinedStrings();
		oss << '{' << boost::algorithm::join(definedStrings, ", ") << '}';
		const std::string setOfDefinedStrings = oss.str();
		
		std::cerr << __FUNCTION__ << ": " << message << '\n'
			<< raw::pad << "--guru arg\t" << setOfDefinedStrings << '\n';

	} else
		std::cout << __FUNCTION__ << ": guru = " << a_text << std::endl;
}

// -- eof
