#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <boost/log/trivial.hpp>

#include "aux-raw.h"
#include "aux-spy+.h" // for ToString

namespace ABcb = Ada_Byron_code_book;

void
ABcb::raw::ExamplesOfRaw()
{
  BOOST_LOG_TRIVIAL(trace) << __func__ << " started...";

  const double myCArray[] = {1., 2., 3.};
  BOOST_LOG_TRIVIAL(info) << ToString(myCArray, ABcb::raw::ArraySize(myCArray), pad + "myCArray (after construction)");

  std::vector myVector{4, 3, 2, 1};
  BOOST_LOG_TRIVIAL(info) << ToString(myVector, pad + "myVector (after construction)");
  ABcb::raw::WipeOut(myVector);
  BOOST_LOG_TRIVIAL(info) << ToString(myVector, pad + "myVector (after WipeOut call)");

  std::set<char> mySetOfChars{ 'A', 'B', 'C'};
  BOOST_LOG_TRIVIAL(info) << ToString(mySetOfChars, pad + "mySetOfChars (after construction)");
  ABcb::raw::WipeOut(mySetOfChars);
  BOOST_LOG_TRIVIAL(info) << ToString(mySetOfChars, pad + "mySetOfChars (after WipeOut call)");

  BOOST_LOG_TRIVIAL(trace) << __func__ << " finished.";
}
