// -- 

#include <fstream>
#include <iostream>

#include "aux-raw-compiler-warnings-off.h"

	#include <boost/algorithm/string.hpp>
	#include <boost/program_options.hpp>
	#include <boost/tokenizer.hpp>

#include "aux-raw-compiler-warnings-on.h"

#include "aux-raw.h"
#include "cli-parser.h"

namespace ABcb = Ada_Byron_code_book;

namespace {

char* progname = 0;

}

std::string
ABcb::cli::ProgramName()
{	return progname; }

namespace Ada_Byron_code_book {

namespace cli {

// 1) File selection
//
std::string filenameIn;

// 2) Operation flags/parameters
//
double cutOff = .8;
PlatonicSolidType platonicSolid = ePlatonicSolidUndefined;

// 3) Informative output
//
std::string consoleOutputFilename;
bool verbose = false;
std::string verboseCLI;
const std::string usageParameterExamples =
	"  --input-file C:\\\\tmp\\\\input.txt --cut-off 0.8"
		" --platonic-solid octahedron"
	"\n\n" // ie. a new example starts here
	"  --input-file C:\\\\tmp\\\\input2.txt --cut-off 2.5"
		" --platonic-solid hexahedron"
	"\n\n" // ie. a new example starts here
	"  --input-file C:\\\\tmp\\\\input3.txt --cut-off 2.5";

// Helping function
//
bool CheckArguments(const boost::program_options::variables_map&);

} // namespace cli

} // namespace Ada_Byron_code_book

bool
ABcb::cli::ParseCommandLine(int argc, char** argv)
{
	if ((progname = (char *)strrchr(argv[0], ABcb::raw::SystemSlash())) == NULL)
		progname = argv[0];
	else
		++progname;

	namespace po = boost::program_options;
	const std::string usageTitle =
		std::string("Usage: ") + progname + " [OPTIONS]...";
	po::options_description odFull(usageTitle);

	using namespace ABcb::cli;

	{	// 1) File selection
		//
		po::options_description od("File selection");
		po::options_description odReq("  Mandatory", 160, 80);
		po::options_description odOpt("  Optional", 160, 80);
		odReq.add_options()
			("input-file",
			po::value<std::string>(&filenameIn)->required(),
			"<filename>");
		od.add(odReq);
		od.add(odOpt);
		odFull.add(od);
	}

	{	// 2) Operation flags/parameters
		//
		po::options_description od("Operation flags/parameters", 160, 80);
		od.add_options()
			("cut-off",
			po::value<double>(&cutOff),
			"{ on | off }")
			("platonic-solid",
			po::value<std::string>(), //po::value<PlatonicSolidType>(&platonicSolid),
			"{ tetrahedron | octahedron | icosahedron | hexahedron | dodecahedron }")
			;
		odFull.add(od);
	}

	{	// 3) Informative output
		//
		po::options_description od("Informative output", 160, 80);
		od.add_options()
			("help", "# \tOutput help on the usage, then exit")
			("verbose",
			po::value<std::string>(&verboseCLI),
			"{ on | off }")
			("usage-examples",
			"# \tOutput example parameters, help on the usage, then exit");
		odFull.add(od);
	}

	{	// 4) Response file
		//
		po::options_description od("Response file", 160, 80);
		od.add_options()
			("response-file",
			po::value<std::string>(),
			"# \tConfiguration file which uses the same syntax as the command line");
		odFull.add(od);
	}

	po::variables_map vm;
	try {
		po::store(
			po::command_line_parser(argc, argv).
			options(odFull).
			style(
			po::command_line_style::allow_long |
			po::command_line_style::long_allow_next).
			run(),
			//po::parse_command_line(argc, argv, odFull),
			vm);
		if (vm.count("help")) {
			std::cout << odFull << '\n';
			return false;
		} else if (vm.count("usage-examples")) {
			std::cout << "Usage parameter example(s):\n\n"
				<< cli::usageParameterExamples << "\n\n" << odFull << '\n';
			return false;
		}
	} catch (const std::exception& e) {
		std::cerr << progname << ": Error: " << e.what() << "\n\n" << odFull
			<< '\n';
		return false;
	}

	// 4) Response file
	//
	if (vm.count("response-file")) {
		// Load the file and tokenize it
		const std::string filename = vm["response-file"].as<std::string>();
		std::ifstream ifs(filename.c_str());
		if (!ifs) {
			std::cerr << progname << ": Error: Could not open the response file "
				<< filename << "\n\n" << odFull << '\n';
			return false;
		}
		// Read the whole file into a string
		std::ostringstream oss;
		oss << ifs.rdbuf();
		// Split the file content
		boost::char_separator<char> sep(" \n\r");
		std::string ResponsefileContents(oss.str());
		boost::tokenizer<boost::char_separator<char> >
			tokenizerObject(ResponsefileContents, sep);
		std::vector<std::string> args;
		copy(tokenizerObject.begin(), tokenizerObject.end(), back_inserter(args));
		// Parse the file and store the options
		namespace po = boost::program_options;
		try {
			po::store(
				po::command_line_parser(args).
				options(odFull).
				style(
				po::command_line_style::allow_long |
				po::command_line_style::long_allow_next).
				run(),
				vm);
		} catch (const std::exception& e) {
			std::cerr << progname << ": Error: " << e.what() << "\n\n" << odFull
				<< '\n';
			return false;
		}
	}

	try {
		po::notify(vm);
	} catch (const std::exception& e) {
		std::cerr << progname << ": Error: " << e.what() << "\n\n" << odFull
			<< '\n';
		return false;
	}

	const bool succeeded = CheckArguments(vm);
	if (!succeeded) {
		std::cerr << odFull;
		return false;
	}

	return true;
}

namespace {

bool
OutputErrorAndReturnFalse(const std::string& a_message)
{
	std::cerr << progname << ": Error: " << a_message << "\n\n";
	return false;
}

bool
ParseBoolean(
	const char* a_optarg, bool& a_field,
	const std::string& a_on, const std::string& a_off)
{
	if (strcmp(a_optarg, a_on.c_str()) == 0)
		a_field = true;
	else if (strcmp(a_optarg, a_off.c_str()) == 0)
		a_field = false;
	else
		return false;
	return true;
}

ABcb::PlatonicSolidType
GetPlatonicSolid(const std::string& a_text)
{
	using namespace ABcb;
	size_t i = ePlatonicSolidType_First;
	for (; i <= ePlatonicSolidType_Last && a_text != platonicSolidText[i]; ++i);
	if (i <= ePlatonicSolidType_Last)
		return static_cast<PlatonicSolidType>(i);
	return ePlatonicSolidUndefined;
}

std::ostream&
operator<<(std::ostream& a_os, ABcb::PlatonicSolidType a_rhs)
{
	using namespace ABcb;
	if (a_rhs > ePlatonicSolidType_Last)
		a_os << platonicSolidText[ePlatonicSolidType_First];
	else
		a_os << platonicSolidText[a_rhs];
	return a_os;
}

} // namespace

bool
ABcb::cli::CheckArguments(const boost::program_options::variables_map& a_vm)
{
	if (a_vm.count("help"))
		return false; // force a error so the usage is shown automatically

	if (a_vm.count("cut-off")) {
		if (cutOff <= 0.)
			return
				OutputErrorAndReturnFalse("The cut-off parameter must be positive");
	}

	if (a_vm.count("platonic-solid")) {
		const std::string& text = a_vm["platonic-solid"].as<std::string>();
		platonicSolid = GetPlatonicSolid(text);
		if (platonicSolid == ePlatonicSolidUndefined) {
			const std::string message =
				"Unknown platonic-solid parameter '" + text + "'";
			return OutputErrorAndReturnFalse(message);
		}
	}

	if (a_vm.count("verbose")) {
		if (!ParseBoolean(verboseCLI.c_str(), verbose, "on", "off"))
			return OutputErrorAndReturnFalse("Unknown verbose parameter");
	}

	return true;
}

#define OutputWithCare(a_string) (a_string.empty() ? "[empty]" : a_string)

void
ABcb::cli::OutputRunInfoAndParsedCommandLine()
{
	//AuxRaw::OutputRunInfo(std::cout, progname);

	std::cout << '\n' << progname
		<< " was called with the following options:\n\n";

	// 1) File selection
	//
	std::cout << "File selection:\n"
		<< "  --input-file " << OutputWithCare(filenameIn) << '\n';
	std::cout << '\n';

	// 2) Operation flags/parameters
	//
	std::cout << "Operation flags/parameters:\n";
	std::cout
		<< "  --cut-off " << cutOff << '\n'
		<< "  --platonic-solid " << platonicSolid << '\n';
	std::cout << '\n';

	// 3) Informative output
	//
	std::cout << "Informative output:\n"
		<< "  --verbose " << (verbose ? "on" : "off") << "\n\n";

	std::cout << std::flush;
}

// -- eof
