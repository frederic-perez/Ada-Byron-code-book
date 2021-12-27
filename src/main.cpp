#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

#include <boost/preprocessor.hpp>

#include "algorithm-string-pool.h"
#include "aux-raw.h" // for ExamplesOfRaw
#include "aux-spy+.h" // for RunInfo, Timer
#include "cli-parser.h"
#include "concurrency.h"
#include "conversions+casts++.h"
#include "cpp11-pool.h"
#include "enum-class-iteration+.h"
#include "euclidean.h"
#include "filesystem-pool.h"
#include "literal-operators.h"
#include "miscellany.h"
#include "preprocessor-pool.h"
#include "promotions-pool.h"
#include "ublas-pool.h"
#include "under-construction.h"
#include "xml-parser.h"

int
main(const int argc, char* argv[])
{
  namespace ABcb = Ada_Byron_code_book;

  bool succeeded = ABcb::cli::ParseCommandLine(argc, argv);
  if (not succeeded)
    return EXIT_FAILURE;

  std::cout << ABcb::spy::RunInfo(ABcb::cli::Argv0(), ABcb::cli::ProgramName()) << '\n'
            << ABcb::cli::ParsedCommandLine << std::endl;

  ABcb::spy::Timer<std::chrono::high_resolution_clock> timerHQ;

  ABcb::cpp11::TryBadCode();
  ABcb::cpp11::TestIfAConstParameterCanBeModified(42);
  ABcb::cpp11::UsingTuple();
  ABcb::cpp11::AlgorithmExamples();
  ABcb::cpp11::MiscellanyExamples();
  std::cout << std::endl;

  ABcb::Euclidean::ExamplesOfVector();
  std::cout << std::endl;

  ABcb::raw::ExamplesOfRaw();
  std::cout << std::endl;

  const std::string exeFile = argv[0];
  ABcb::ExamplesOfFileSystem(exeFile);
  std::cout << std::endl;

  ABcb::ExamplesOfIstringstreamFailingConversions();
  std::cout << std::endl;
  ABcb::ExamplesOfCpp11Conversions();
  std::cout << std::endl;
  const std::string inputValue = "1234567890";
  ABcb::ExamplesOfBoostLexicalCast(inputValue);
  std::cout << std::endl;
  ABcb::ExamplesOfBoostNumericCast();
  std::cout << std::endl;

  ABcb::ExamplesOfAlgorithmsString();
  std::cout << std::endl;

  ABcb::ExamplesOfPromotions();
  std::cout << std::endl;

  ABcb::ExamplesOfUblas();
  std::cout << std::endl;

  const std::string filenameIn = "input.xml";
  const std::string filenameOut = "output.xml";
  succeeded = ABcb::ParseXML(filenameIn, filenameOut);
  std::clog << "Ada_Byron_code_book::ParseXML " << (succeeded ? "succeeded" : "failed") << ".\n" << std::endl;

  ABcb::ExamplesOfConcurrencyUsingCpp11();
  std::cout << std::endl;
#if !defined(_MSC_VER)
  ABcb::ExamplesOfConcurrencyUsingPOSIXThreads();
  std::cout << std::endl;
#endif

  ABcb::GurusTest({"Bjarne_Stroustrup", "John_Doe", "Andrew_Koenig"});
  ABcb::GurusTest({BOOST_PP_SEQ_FOR_EACH(ABcb_TO_STR, ~, (Annie_Lennox)(Mike_Oldfield))});

  ABcb::miscellany::ExampleOfRawStringLiteral();
  ABcb::miscellany::ExamplesOfFactorial();
  ABcb::miscellany::ExamplesOfMultiprecision();
  std::cout << std::endl;

  ABcb::literal_operators::Examples();
  std::cout << std::endl;

  try {
    ABcb::enums::ExamplesOfEnumClassAsIntegral();
    std::cout << std::endl;
    ABcb::enums::ExamplesOfEnumClassIteration();
  } catch (const std::string& message) {
    std::cerr << "Exception caught: " << message << "\n\n";
  }

  // Output final message and exit
  //
  const double timeElapsed = timerHQ.Seconds();
  const auto previousPrecision = std::clog.precision(2);
  // '- Note: "auto" is recommended here to avoid potential problems with
  //    different compilers (eg. requiring "static_cast" to set the previous
  //    precision in vs12), since the standard states that the return type of
  //    setprecision is "unspecified"
  std::clog << '\n'
            << __func__ << " finishes. Time elapsed: " << timeElapsed << " seconds"
            << std::setprecision(previousPrecision) << std::endl;

  return EXIT_SUCCESS;
}
