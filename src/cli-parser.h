// -- 

#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <vector>

#include <boost/preprocessor.hpp>

namespace Ada_Byron_code_book {

namespace PlatonicSolid { // An enum class and related stuff

enum class Enum : uint8_t {
	undefined,
	tetrahedron, octahedron, icosahedron, hexahedron, dodecahedron
};
const std::array<const char*, 6> enumText{ {
	"undefined",
	"tetrahedron", "octahedron", "icosahedron", "hexahedron", "dodecahedron" } };
Enum GetEnum(const std::string&);
std::string GetString(Enum);
std::vector<std::string> GetDefinedStrings();

} // namespace PlatonicSolid

namespace Color { // An enum class and related stuff

enum class Enum : uint8_t {
	undefined,
	red, green, blue
};
const std::array<const char*, 4> enumText{ {
	"undefined",
	"red", "green", "blue" } };
Enum GetEnum(const std::string&);
std::string GetString(Enum);
std::vector<std::string> GetDefinedStrings();

} // namespace Color

namespace Fruit { // An enum class and related stuff

// Code originarily based on
// http://www.gamedev.net/topic/437852-c-enum-names-as-strings/

#define SEQUENCE (undefined)(apple)(orange)(pear)
#define TO_STR(unused, data, elem) BOOST_PP_STRINGIZE(elem),
enum class Enum : uint8_t { BOOST_PP_SEQ_ENUM(SEQUENCE) };
const std::array<const char*, BOOST_PP_SEQ_SIZE(SEQUENCE)> enumText{ { 
	BOOST_PP_SEQ_FOR_EACH(TO_STR, ~, SEQUENCE) } };
Enum GetEnum(const std::string&);
std::string GetString(Enum);
std::vector<std::string> GetDefinedStrings();

#undef TO_STR
#undef SEQUENCE

} // namespace Fruit

/*
#define PROJECT_PREFIX_DO_EVIL_TO_STR(unused, data, elem) \
	BOOST_PP_STRINGIZE(elem),
#define PROJECT_PREFIX_DO_EVIL(enum_, strings, elements) \ 
enum enum_ { BOOST_PP_SEQ_ENUM(elements) };                 \
	const char * strings[] = \
		{ BOOST_PP_SEQ_FOR_EACH(PROJECT_PREFIX_DO_EVIL_TO_STR, ~, SEQ) };
*/

namespace cli {

std::string Argv0();
std::string ProgramName();

bool
ParseCommandLine(int argc, char** argv);

std::ostream&
ParsedCommandLine(std::ostream&);

} // namespace cli

} // namespace Ada_Byron_code_book

// -- eof
