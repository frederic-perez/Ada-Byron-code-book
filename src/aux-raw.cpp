#include <iostream>
#include <string>
#include <vector>

#include "aux-raw.h"
#include "aux-spy.h"

namespace ABcb = Ada_Byron_code_book;

void
ABcb::raw::ExamplesOfRaw()
{
  std::clog << __func__ << " started..." << std::endl;

  const double myCArray[] = {1., 2., 3.};
  spy::Output(std::cout, myCArray, ABcb::raw::ArraySize(myCArray), pad + "myCArray (after construction)");

  std::vector myVector{4, 3, 2, 1};
  spy::Output(std::cout, myVector, pad + "myVector (after construction)");
  ABcb::raw::WipeOut(myVector);
  spy::Output(std::cout, myVector, pad + "myVector (after WipeOut call)");

  std::clog << __func__ << " finished." << std::endl;
}
