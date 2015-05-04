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
#include "xml-parser.h"

int
main(int argc, char* argv[])
{
	std::cout << __func__ << " started...\n" << std::endl;

	namespace ABcb = Ada_Byron_code_book;

	std::cout
		<< "Using Boost version " << ABcb::spy::BoostVersion << '\n'
		<< "Using Clang version " << ABcb::spy::ClangVersion << '\n'
		<< "Using GNU g++ version " << ABcb::spy::GNUGppVersion << '\n'
		<< "Using Visual Studio C/C++ compiler version "
			<< ABcb::spy::VisualStudioCppCompilerVersion << '\n'
		<< "List of preprocessor defines:\n"
			<< ABcb::spy::ListOfPreprocessorDefines
		<< std::endl;

	 bool succeeded = ABcb::cli::ParseCommandLine(argc, argv);
	 if (!succeeded)
		 return EXIT_FAILURE;

	ABcb::cli::OutputRunInfoAndParsedCommandLine();

	ABcb::cpp11::TryBadCode();
	ABcb::cpp11::TestIfAConstParameterCanBeModified(42);
	ABcb::cpp11::UsingTuple();

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

	const std::string filenameIn = "input.xml";
	const std::string filenameOut = "output.xml";
	succeeded = ABcb::ParseXML(filenameIn, filenameOut);
	std::clog << "ABcb::ParseXML " << (succeeded ? "succeeded" : "failed")
		<< std::endl;

	std::cout << '\n' << __func__ << " finished!\n" << std::endl;
	
	return EXIT_SUCCESS;
}

// -- eof
