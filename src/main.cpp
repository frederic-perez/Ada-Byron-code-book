// --

#include <iostream>
#include <string>

#include "algorithm-string-pool.h"
#include "aux-raw.h"
#include "aux-spy.h"
#include "cli-parser.h"
#include "cpp11-pool.h"
#include "filesystem-pool.h"
#include "lexical-cast-pool.h"
#include "preprocessor-pool.h"
#include "promotions-pool.h"
#include "ublas-pool.h"
#include "xml-parser.h"

int
main(int argc, char* argv[])
{
	namespace ABcb = Ada_Byron_code_book;

	bool succeeded = ABcb::cli::ParseCommandLine(argc, argv);
	if (!succeeded)
		return EXIT_FAILURE;

	std::cout << ABcb::spy::RunInfo(ABcb::cli::ProgramName()) << '\n'
		<< ABcb::cli::ParsedCommandLine << std::endl;

	ABcb::cpp11::TryBadCode();
	ABcb::cpp11::TestIfAConstParameterCanBeModified(42);
	ABcb::cpp11::UsingTuple();
	ABcb::cpp11::AlgorithmExamples();
	ABcb::cpp11::MiscellanyExamples();

	ABcb::raw::ExamplesOfRaw();
	std::cout << std::endl;

	const std::string exeFile = argv[0];
	ABcb::ExamplesOfFileSystem(exeFile);
	std::cout << std::endl;

	const std::string inputValue = "1234567890";
	ABcb::ExamplesOfLexicalCast(inputValue);
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
	std::clog << "ABcb::ParseXML " << (succeeded ? "succeeded" : "failed")
		<< std::endl;

	return EXIT_SUCCESS;
}

// -- eof
