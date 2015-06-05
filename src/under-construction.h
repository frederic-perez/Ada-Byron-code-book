// -- 

#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <vector>

#include <boost/preprocessor.hpp>

namespace Ada_Byron_code_book {

namespace Guru { // An enum class and related stuff

// Code originarily based on
// http://www.gamedev.net/topic/437852-c-enum-names-as-strings/

#define SEQUENCE (undefined)(Alexandrescu)(Koenig)(Meyers)(Stroustrup)(Sutter)
#define TO_STR(unused,data,elem) BOOST_PP_STRINGIZE(elem),
enum class Enum : uint8_t { BOOST_PP_SEQ_ENUM(SEQUENCE) };
const std::array<const char*, BOOST_PP_SEQ_SIZE(SEQUENCE)> enumText{ { 
	BOOST_PP_SEQ_FOR_EACH(TO_STR, ~, SEQUENCE) } };
Enum GetEnum(const std::string&);
std::string GetString(Enum);
std::vector<std::string> GetDefinedStrings();

#undef TO_STR
#undef SEQUENCE

} // namespace Fruit

void GuruTest(const std::string&);

/*
#define PROJECT_PREFIX_DO_EVIL_TO_STR(unused,data,elem) BOOST_PP_STRINGIZE(elem),
#define PROJECT_PREFIX_DO_EVIL(enum_,strings,elements) \ 
enum enum_ { BOOST_PP_SEQ_ENUM(elements) };                 \
	const char * strings[] = { BOOST_PP_SEQ_FOR_EACH(PROJECT_PREFIX_DO_EVIL_TO_STR, ~, SEQ) };
*/

} // namespace Ada_Byron_code_book

// -- eof
