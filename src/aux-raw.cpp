#include <algorithm> // for std::generate_n
#include <set>
#include <string>
#include <vector>

#include "aux-raw.h"
#include "aux-spy+.h" // for ToString
#include "log.h"

namespace ABcb = Ada_Byron_code_book;

// From
// https://stackoverflow.com/questions/440133/
//   how-do-i-create-a-random-alpha-numeric-string-in-c/12468109#12468109
//
std::string
ABcb::raw::RandomString(size_t length)
{
  auto randchar = []() -> char
  {
    const char charset[] =
      "0123456789"
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz";
    const size_t max_index = sizeof(charset) - 1;
    return charset[rand() % max_index];
  };
  std::string str(length, 0);
  std::generate_n(str.begin(), length, randchar);
  return str;
}

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

  B_LOG_INFO << "RandomString(8) returned \"" << RandomString(8) << "\"";

  B_LOG_TRACE_FINISHED
}
