// -- 

#pragma once

#include <string>

namespace Ada_Byron_code_book {

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
