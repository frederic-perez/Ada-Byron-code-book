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
  std::cout << spy::ToString(myCArray, ABcb::raw::ArraySize(myCArray), pad + "myCArray (after construction)") << std::endl;

  std::vector myVector{4, 3, 2, 1};
  std::cout << spy::ToString(myVector, pad + "myVector (after construction)") << std::endl;
  ABcb::raw::WipeOut(myVector);
  std::cout << spy::ToString(myVector, pad + "myVector (after WipeOut call)") << std::endl;

  std::clog << __func__ << " finished." << std::endl;
}
