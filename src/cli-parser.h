// -- 

#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <vector>

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

namespace cli {

std::string
ProgramName();

bool
ParseCommandLine(int argc, char** argv);

std::ostream&
ParsedCommandLine(std::ostream&);

} // namespace cli

} // namespace Ada_Byron_code_book

// -- eof
