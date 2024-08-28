#include <chrono>
#include <iomanip>
#include <string>

#include <boost/preprocessor.hpp>

#include "algorithm-string-pool.hpp"
#include "aux-raw.hpp" // for ExamplesOfRaw
#include "aux-spy+.hpp" // for RunInfo, Timer
#include "cli-parser.hpp"
#include "concurrency.hpp"
#include "conversions+casts++.hpp"
#include "cpp11-pool.hpp"
#include "enum-class-iteration+.hpp"
#include "euclidean.hpp"
#include "filesystem-pool.hpp"
#include "literal-operators.hpp"
#include "log.hpp"
#include "miscellany.hpp"
#include "preprocessor-pool.hpp"
#include "promotions-pool.hpp"
#include "ublas-pool.hpp"
#include "under-construction.hpp"
#include "xml-parser.hpp"

#define B_LOG_END_OF_BLOCK B_LOG_TRACE << "----";

int
main(const int argc, char* argv[])
{
  namespace ABcb = Ada_Byron_code_book;

  ABcb::cli::Parser parser;
  if (const auto pair = parser.ParseCommandLine(argc, argv); pair.has_value()) {
    const auto& [argv0, programName] = pair.value();
    ABcb::spy::RunInfo(argv0, programName).Log();
    parser.LogParsedCommandLine();
  } else {
    return EXIT_FAILURE;
  }

  ABcb::spy::Timer<std::chrono::high_resolution_clock> timerHQ;

  ABcb::cpp11::TryBadCode();
  ABcb::cpp11::TestIfAConstParameterCanBeModified(42);
  ABcb::cpp11::UsingTuple();
  ABcb::cpp11::AlgorithmExamples();
  ABcb::cpp11::MiscellanyExamples();
  B_LOG_END_OF_BLOCK

  ABcb::Euclidean::ExamplesOfVector();
  B_LOG_END_OF_BLOCK

  ABcb::raw::ExamplesOfRaw();
  B_LOG_END_OF_BLOCK

  const std::string exeFile = argv[0];
  ABcb::ExamplesOfBoostFileSystem(exeFile);
  ABcb::ExamplesOfStdFileSystem(std::filesystem::path(exeFile));
  B_LOG_END_OF_BLOCK

  ABcb::ExamplesOfIstringstreamFailingConversions();
  B_LOG_END_OF_BLOCK
  ABcb::ExamplesOfCpp11Conversions();
  B_LOG_END_OF_BLOCK
  const std::string inputValue = "1234567890";
  ABcb::ExamplesOfBoostLexicalCast(inputValue);
  B_LOG_END_OF_BLOCK
  ABcb::ExamplesOfBoostNumericCast();
  B_LOG_END_OF_BLOCK

  ABcb::ExamplesOfAlgorithmsString();
  B_LOG_END_OF_BLOCK

  ABcb::ExamplesOfPromotions();
  B_LOG_END_OF_BLOCK

  ABcb::ExamplesOfUblas();
  B_LOG_END_OF_BLOCK

  const std::string filenameIn = "input.xml";
  const std::string filenameOut = "output.xml";
  bool succeeded = ABcb::ParseXML(filenameIn, filenameOut);
  B_LOG_INFO
    << "Ada_Byron_code_book::ParseXML " << (succeeded ? "succeeded" : "failed") << ".";
  B_LOG_END_OF_BLOCK

  ABcb::ExamplesOfConcurrencyUsingCpp11();
  B_LOG_END_OF_BLOCK
#if !defined(_MSC_VER)
  ABcb::ExamplesOfConcurrencyUsingPOSIXThreads();
  B_LOG_END_OF_BLOCK
#endif

  ABcb::GurusTest({"Bjarne_Stroustrup", "John_Doe", "Andrew_Koenig"});
  ABcb::GurusTest({BOOST_PP_SEQ_FOR_EACH(ABcb_TO_STR, ~, (Annie_Lennox)(Mike_Oldfield))});

  ABcb::miscellany::ExampleOfRawStringLiteral();
  ABcb::miscellany::ExamplesOfFactorial();
  ABcb::miscellany::ExamplesOfMultiprecision();
  B_LOG_END_OF_BLOCK

  ABcb::literal_operators::Examples();
  B_LOG_END_OF_BLOCK

  try {
    ABcb::enums::ExamplesOfEnumClassAsIntegral();
    B_LOG_END_OF_BLOCK
    ABcb::enums::ExamplesOfEnumClassIteration();
  } catch (const std::string& message) {
    B_LOG_ERROR << "Exception caught: " << message;
  }
  B_LOG_END_OF_BLOCK

  B_LOG_INFO << __func__ << " finishes. Time elapsed: " << timerHQ.Seconds(2);

  return EXIT_SUCCESS;
}
