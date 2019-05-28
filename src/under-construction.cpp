// --

#include "under-construction.h"

// namespace ABcb = Ada_Byron_code_book;

// TODO: Add point cloud binary file I/O
// TODO: Add example point cloud file in data folder
// TODO: Move point cloud-related code to new source files
// TODO: Point cloud file: endianness control

#undef ADA_BYRON_PARSING_WITH_ISTRINGSTREAM_IS_EASY_20150626
#ifdef ADA_BYRON_PARSING_WITH_ISTRINGSTREAM_IS_EASY_20150626
// TODO
// NOTE: Parsing using std::istringstream is easy
#  include <sstream>

std::string line;
while (getline(fileI, line))
  if (!line.empty()) {
    std::istringstream parse(line);
    double x, y;
    parse >> x >> y;
    // do stuff with x and y
  }
#endif

// -- eof
