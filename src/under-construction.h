// -- 

#pragma once

#include <array>
#include <cstdint>
#include <initializer_list>
#include <string>
#include <vector>

#include <boost/preprocessor.hpp>

#define ABcb_TO_STR(unused,data,elem) BOOST_PP_STRINGIZE(elem),
#define ABcb_DECLARE_ENUM_AND_ENUMTEXT(sequence) \
enum class Enum : uint8_t { BOOST_PP_SEQ_ENUM(sequence) }; \
const std::array<const char*, BOOST_PP_SEQ_SIZE(sequence)> enumText{{ \
	BOOST_PP_SEQ_FOR_EACH(ABcb_TO_STR, ~, sequence) }};

namespace Ada_Byron_code_book {

namespace Guru { // An enum class and related stuff

// Code originarily based on
// http://www.gamedev.net/topic/437852-c-enum-names-as-strings/

#define SEQUENCE (undefined)(Alexandrescu)(Koenig)(Meyers)(Stroustrup)(Sutter)
ABcb_DECLARE_ENUM_AND_ENUMTEXT(SEQUENCE)
Enum GetEnum(const std::string&);
std::string GetString(Enum);
std::vector<std::string> GetDefinedStrings();

#undef SEQUENCE

} // namespace Fruit

void GurusTest(std::initializer_list<std::string>);

} // namespace Ada_Byron_code_book

// -- eof
