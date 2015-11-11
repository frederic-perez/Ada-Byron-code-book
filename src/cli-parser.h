// -- 

#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <vector>

#include <boost/preprocessor.hpp>

#include "under-construction.h"

namespace Ada_Byron_code_book {

ABcb_DEFINE_NAMESPACE_WITH_ENUM_TOOLS(\
	PlatonicSolid,
	(undefined)\
	(tetrahedron)(octahedron)(icosahedron)(hexahedron)(dodecahedron)
)

ABcb_DEFINE_NAMESPACE_WITH_ENUM_TOOLS(\
	Color,
	(undefined)\
	(red)(green)(blue)
)

ABcb_DEFINE_NAMESPACE_WITH_ENUM_TOOLS(\
	Fruit,
	(undefined)\
	(apple)(orange)(pear)
)

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
