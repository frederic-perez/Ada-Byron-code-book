// -- 

#pragma once

#include <string>

namespace Ada_Byron_code_book {

// The PlatonicSolidType definition and helpers
//
enum PlatonicSolidType {
	ePlatonicSolidUndefined,
	eTetrahedron, eOctahedron, eIcosahedron, eHexahedron, eDodecahedron
};
const size_t ePlatonicSolidType_First = eTetrahedron;
const size_t ePlatonicSolidType_Last = eDodecahedron;
const char* const platonicSolidText[] = {
	"undefined",
	"tetrahedron", "octahedron", "icosahedron", "hexahedron", "dodecahedron" };

namespace cli {

std::string
ProgramName();

bool
ParseCommandLine(int argc, char** argv);

void
OutputRunInfoAndParsedCommandLine();

} // namespace cli

} // namespace Ada_Byron_code_book

// -- eof
