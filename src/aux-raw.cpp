#include <set>
#include <string>
#include <vector>

#include "aux-raw.h"
#include "aux-spy+.h" // for ToString
#include "log.h"

namespace ABcb = Ada_Byron_code_book;

void
ABcb::raw::ExamplesOfRaw()
{
  B_LOG_TRACE_STARTED

  const double myCArray[] = {1., 2., 3.};
  B_LOG_INFO << ToString(myCArray, ABcb::raw::ArraySize(myCArray), pad + "myCArray (after construction)");

  std::vector myVector{4, 3, 2, 1};
  B_LOG_INFO << ToString(myVector, pad + "myVector (after construction)");
  ABcb::raw::WipeOut(myVector);
  B_LOG_INFO << ToString(myVector, pad + "myVector (after WipeOut call)");

  std::set<char> mySetOfChars{ 'A', 'B', 'C'};
  B_LOG_INFO << ToString(mySetOfChars, pad + "mySetOfChars (after construction)");
  ABcb::raw::WipeOut(mySetOfChars);
  B_LOG_INFO << ToString(mySetOfChars, pad + "mySetOfChars (after WipeOut call)");

  B_LOG_TRACE_FINISHED
}
