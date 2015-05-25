// -- 

#pragma once

#include <array>
#include <cstdint>
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
