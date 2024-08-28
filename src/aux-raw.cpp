#include <algorithm> // for std::generate_n
#include <random>
#include <set>
#include <string>
#include <vector>

#include "aux-raw.hpp"
#include "aux-spy+.hpp" // for ToString
#include "log.hpp"

namespace ABcb = Ada_Byron_code_book;

// Originarily (but later modified) from
// https://stackoverflow.com/questions/440133/
//   how-do-i-create-a-random-alpha-numeric-string-in-c/12468109#12468109
//
std::string
ABcb::raw::RandomString(size_t length)
{
  auto randchar = []()
  {
    const char charset[] =
      "0123456789"
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz";

    // From https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
    std::random_device rd; // Will be used to obtain a seed for the random number engine
    std::mt19937 generator(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<size_t> distribution(0, sizeof(charset) - 2);
    return charset[distribution(generator)];
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

  B_LOG_INFO << "RandomString(32) returned \"" << RandomString(32) << "\"";

  B_LOG_TRACE_FINISHED
}
