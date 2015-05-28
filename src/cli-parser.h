// -- 

#pragma once

#include <array>
#include <cstdint>
#include <iostream>
#include <string>

namespace Ada_Byron_code_book {

// The PlatonicSolidType definition and helpers
//
enum class PlatonicSolidType : uint8_t {
	eUndefined,
	eTetrahedron, eOctahedron, eIcosahedron, eHexahedron, eDodecahedron
};
const std::array<const char*, 6> platonicSolidText{ {
	"undefined",
	"tetrahedron", "octahedron", "icosahedron", "hexahedron", "dodecahedron" } };
const uint8_t ePlatonicSolidType_First = 1;
const uint8_t ePlatonicSolidType_Last =
	static_cast<uint8_t>(platonicSolidText.size() - 1);

// The Color definition and helpers
//
namespace Color {

enum class Enum : uint8_t {
	undefined,
	red, green, blue
};
const std::array<const char*, 4> enumText{ {
	"undefined",
	"red", "green", "blue" } };
Enum GetEnum(const std::string&);
std::string GetString(Enum);

}

namespace cli {

std::string
ProgramName();

bool
ParseCommandLine(int argc, char** argv);

std::ostream&
ParsedCommandLine(std::ostream&);

} // namespace cli

} // namespace Ada_Byron_code_book

std::ostream& operator<<(std::ostream&, Ada_Byron_code_book::Color::Enum);

// -- eof
