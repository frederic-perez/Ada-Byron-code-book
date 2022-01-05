#include <chrono>
#include <iomanip>
#include <string>

#include <boost/log/trivial.hpp>
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

#define BOOST_LOG_END_OF_BLOCK BOOST_LOG_TRIVIAL(trace) << "----"

int
main(const int argc, char* argv[])
{
  namespace ABcb = Ada_Byron_code_book;

  bool succeeded = ABcb::cli::ParseCommandLine(argc, argv);
  if (!succeeded)
    return EXIT_FAILURE;

  ABcb::spy::RunInfo(ABcb::cli::Argv0(), ABcb::cli::ProgramName()).Log();
  ABcb::cli::LogParsedCommandLine();

  ABcb::spy::Timer<std::chrono::high_resolution_clock> timerHQ;

  ABcb::cpp11::TryBadCode();
  ABcb::cpp11::TestIfAConstParameterCanBeModified(42);
  ABcb::cpp11::UsingTuple();
  ABcb::cpp11::AlgorithmExamples();
  ABcb::cpp11::MiscellanyExamples();
  BOOST_LOG_END_OF_BLOCK;

  ABcb::Euclidean::ExamplesOfVector();
  BOOST_LOG_END_OF_BLOCK;

  ABcb::raw::ExamplesOfRaw();
  BOOST_LOG_END_OF_BLOCK;

  const std::string exeFile = argv[0];
  ABcb::ExamplesOfFileSystem(exeFile);
  BOOST_LOG_END_OF_BLOCK;

  ABcb::ExamplesOfIstringstreamFailingConversions();
  BOOST_LOG_END_OF_BLOCK;
  ABcb::ExamplesOfCpp11Conversions();
  BOOST_LOG_END_OF_BLOCK;
  const std::string inputValue = "1234567890";
  ABcb::ExamplesOfBoostLexicalCast(inputValue);
  BOOST_LOG_END_OF_BLOCK;
  ABcb::ExamplesOfBoostNumericCast();
  BOOST_LOG_END_OF_BLOCK;

  ABcb::ExamplesOfAlgorithmsString();
  BOOST_LOG_END_OF_BLOCK;

  ABcb::ExamplesOfPromotions();
  BOOST_LOG_END_OF_BLOCK;

  ABcb::ExamplesOfUblas();
  BOOST_LOG_END_OF_BLOCK;

  const std::string filenameIn = "input.xml";
  const std::string filenameOut = "output.xml";
  succeeded = ABcb::ParseXML(filenameIn, filenameOut);
  BOOST_LOG_TRIVIAL(info)
    << "Ada_Byron_code_book::ParseXML " << (succeeded ? "succeeded" : "failed") << ".";
  BOOST_LOG_END_OF_BLOCK;

  ABcb::ExamplesOfConcurrencyUsingCpp11();
  BOOST_LOG_END_OF_BLOCK;
#if !defined(_MSC_VER)
  ABcb::ExamplesOfConcurrencyUsingPOSIXThreads();
  BOOST_LOG_END_OF_BLOCK;
#endif

  ABcb::GurusTest({"Bjarne_Stroustrup", "John_Doe", "Andrew_Koenig"});
  ABcb::GurusTest({BOOST_PP_SEQ_FOR_EACH(ABcb_TO_STR, ~, (Annie_Lennox)(Mike_Oldfield))});

  ABcb::miscellany::ExampleOfRawStringLiteral();
  ABcb::miscellany::ExamplesOfFactorial();
  ABcb::miscellany::ExamplesOfMultiprecision();
  BOOST_LOG_END_OF_BLOCK;

  ABcb::literal_operators::Examples();
  BOOST_LOG_END_OF_BLOCK;

  try {
    ABcb::enums::ExamplesOfEnumClassAsIntegral();
    BOOST_LOG_END_OF_BLOCK;
    ABcb::enums::ExamplesOfEnumClassIteration();
  } catch (const std::string& message) {
    BOOST_LOG_TRIVIAL(error) << "Exception caught: " << message;
  }
  BOOST_LOG_END_OF_BLOCK;

  BOOST_LOG_TRIVIAL(info) << __func__ << " finishes. Time elapsed: " << timerHQ.Seconds(2);

  return EXIT_SUCCESS;
}
