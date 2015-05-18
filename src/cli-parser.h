// -- 

#pragma once

#include <cstdint>
#include <string>

namespace Ada_Byron_code_book {

// The PlatonicSolidType definition and helpers
//
enum class PlatonicSolidType : uint8_t {
	eUndefined,
	eTetrahedron, eOctahedron, eIcosahedron, eHexahedron, eDodecahedron
};
const uint8_t ePlatonicSolidType_First =
	static_cast<uint8_t>(PlatonicSolidType::eTetrahedron);
const uint8_t ePlatonicSolidType_Last =
	static_cast<uint8_t>(PlatonicSolidType::eDodecahedron);
const char* const platonicSolidText[] = {
	"undefined",
	"tetrahedron", "octahedron", "icosahedron", "hexahedron", "dodecahedron" };

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
