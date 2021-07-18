#include <fstream>
#include <iostream>
#include <sstream> // std::ostringstream oss
#include <vector>

#include "aux-raw-compiler-warnings-off++begin.h"
// clang-format off
  #include <boost/algorithm/string.hpp>
  #include <boost/numeric/conversion/bounds.hpp>
  #include <boost/numeric/conversion/cast.hpp>
  #include <boost/program_options.hpp>
  #include <boost/tokenizer.hpp>
// clang-format on
#include "aux-raw-compiler-warnings-off++end.h"

#include "aux-raw.h"
#include "cli-parser.h"

namespace ABcb = Ada_Byron_code_book;

namespace {

ABcb_DEFINE_NAMESPACE_WITH_ENUM_TOOLS(
  Guru, (Andrei_Alexandrescu)(Andrew_Koenig)(Bruce_Eckel)(Bjarne_Stroustrup)(Herb_Sutter)(Ira_Pohl)(Scott_Meyers));

void
GuruTest(const std::string& a_text)
{
  using ABcb::raw::pad;

  const Guru::Enum guru = Guru::GetEnum(a_text);
  if (guru == Guru::Enum::undefined) {
    const std::string message = "Unknown guru parameter '" + a_text + "'";

    std::ostringstream oss;
    std::vector<std::string> definedStrings = Guru::GetDefinedStrings();
    oss << '{' << boost::algorithm::join(definedStrings, ", ") << '}';
    const std::string setOfDefinedStrings = oss.str();

    std::cerr << pad << __func__ << ": " << message << '\n'
              << pad << pad << "--guru arg " << setOfDefinedStrings << '\n';
  } else {
    std::cout << pad << __func__ << ": Guru::Enum guru exists for text `" << a_text << "`" << std::endl;
  }
}

} // namespace

void
ABcb::GurusTest(const std::initializer_list<std::string> a_args)
{
  std::cout << __func__ << " called" << std::endl;
  for (auto text : a_args) {
    GuruTest(text);
  }
}

namespace {

char* argv0 = nullptr;
char* progname = nullptr;

ABcb_DEFINE_NAMESPACE_WITH_ENUM_TOOLS(PlatonicSolid, (tetrahedron)(octahedron)(icosahedron)(hexahedron)(dodecahedron));
ABcb_DEFINE_NAMESPACE_WITH_ENUM_TOOLS(Color, (red)(green)(blue));
ABcb_DEFINE_NAMESPACE_WITH_ENUM_TOOLS(Fruit, (apple)(orange)(pear));

} // namespace

auto
ABcb::cli::Argv0()
-> std::string
{
  return argv0;
}

auto
ABcb::cli::ProgramName()
-> std::string
{
  return progname;
}

namespace Ada_Byron_code_book::cli {

// 1) File selection
//
std::string filenameIn;

// 2) Operation flags/parameters
//
double inputDouble = 42.666;
double inputPositiveDouble = .8;
size_t inputUnsignedCharCLI;
unsigned char inputUnsignedChar;
PlatonicSolid::Enum platonicSolid = PlatonicSolid::Enum::undefined;
Color::Enum color = Color::Enum::undefined;
Fruit::Enum fruit = Fruit::Enum::undefined;
std::vector<size_t> suggestedWindowPosition;

// 3) Informative output
//
std::string consoleOutputFilename;
bool verbose = false;
std::string verboseCLI;
const std::string usageParameterExamples =
  "  --input-file C:\\\\tmp\\\\input.txt --input-positive-double 0.8"
  " --platonic-solid octahedron"
  "\n\n" // ie. a new example starts here
  "  --input-file C:\\\\tmp\\\\input2.txt --input-positive-double 2.5"
  " --platonic-solid hexahedron"
  "\n\n" // ie. a new example starts here
  "  --input-file C:\\\\tmp\\\\input3.txt --input-positive-double 2.5";

// Helping function
//
auto CheckArguments(const boost::program_options::variables_map&) -> bool;

// Miscellany

auto
GetSetOfDefinedString(const std::vector<std::string>& a_definedStrings)
-> std::string
{
  const std::string result = '{' + boost::algorithm::join(a_definedStrings, ", ") + '}';
  return result;
}

} // namespace Ada_Byron_code_book::cli

auto
ABcb::cli::ParseCommandLine(const int argc, char** argv)
-> bool
{
  argv0 = argv[0];
  if ((progname = (char*)strrchr(argv[0], ABcb::raw::SystemSlash())) == NULL) {
    progname = argv[0];
  } else {
    ++progname;
  }

  namespace po = boost::program_options;
  const std::string usageTitle = std::string("Usage: ") + progname + " [OPTIONS]...";
  po::options_description odFull(usageTitle);

  { // 1) File selection
    //
    po::options_description od("File selection");
    po::options_description odReq("  Mandatory", 160, 80);
    po::options_description odOpt("  Optional", 160, 80);
    odReq.add_options()("input-file", po::value<std::string>(&filenameIn)->required(), "<filename>");
    od.add(odReq);
    od.add(odOpt);
    odFull.add(od);
  }

  { // 2) Operation flags/parameters
    //
    po::options_description od("Operation flags/parameters", 160, 80);
    od.add_options()("input-double", po::value<double>(&inputDouble), "<double> # \texample to get any double value")(
      "input-positive-double",
      po::value<double>(&inputPositiveDouble),
      "<positive double> # \texample to check the input is positive")(
      "input-ID",
      po::value<size_t>(&inputUnsignedCharCLI),
      "<unsigned char> # \texample to get an ID--number--as an unsigned char")(
      "platonic-solid",
      po::value<std::string>(), // po::value<PlatonicSolid>(&platonicSolid),
      GetSetOfDefinedString(PlatonicSolid::GetDefinedStrings()).c_str())(
      "color", po::value<std::string>(), GetSetOfDefinedString(Color::GetDefinedStrings()).c_str())(
      "fruit",
      po::value<std::string>(),
      GetSetOfDefinedString(Fruit::GetDefinedStrings()).c_str())(
      "suggested-window-position", // multitoken example
      po::value<decltype(suggestedWindowPosition)>(&suggestedWindowPosition)->multitoken(),
      "<x> <y>  # \tIn pixels, with (1, 1) being the top-left corner");
    odFull.add(od);
  }

  { // 3) Informative output
    //
    po::options_description od("Informative output", 160, 80);
    od.add_options()("help", "# \tOutput help on the usage, then exit")(
      "verbose", po::value<std::string>(&verboseCLI), "{on, off}")(
      "usage-examples", "# \tOutput example parameters, help on the usage, then exit");
    odFull.add(od);
  }

  { // 4) Response file
    //
    po::options_description od("Response file", 160, 80);
    od.add_options()(
      "response-file",
      po::value<std::string>(),
      "# \tConfiguration file which uses the same syntax as the command line");
    odFull.add(od);
  }

  po::variables_map vm;
  try {
    po::store(
      po::command_line_parser(argc, argv)
        .options(odFull)
        .style(po::command_line_style::allow_long | po::command_line_style::long_allow_next)
        .run(),
      // po::parse_command_line(argc, argv, odFull),
      vm);
    if (vm.count("help") != 0) {
      std::cout << odFull << '\n';
      return false;
    }
    if (vm.count("usage-examples") != 0) {
      std::cout << "Usage parameter example(s):\n\n" << cli::usageParameterExamples << "\n\n" << odFull << '\n';
      return false;
    }
  } catch (const std::exception& e) {
    std::cerr << progname << ": Error: " << e.what() << "\n\n" << odFull << '\n';
    return false;
  }

  // 4) Response file
  //
  if (vm.count("response-file") != 0) {
    // Load the file and tokenize it
    const std::string filename = vm["response-file"].as<std::string>();
    std::ifstream ifs(filename.c_str());
    if (!ifs) {
      std::cerr << progname << ": Error: Could not open the response file " << filename << "\n\n" << odFull << '\n';
      return false;
    }
    // Read the whole file into a string
    std::ostringstream oss;
    oss << ifs.rdbuf();
    // Split the file content
    boost::char_separator<char> sep(" \n\r");
    std::string ResponsefileContents(oss.str());
    boost::tokenizer<boost::char_separator<char>> tokenizerObject(ResponsefileContents, sep);
    std::vector<std::string> args;
    copy(tokenizerObject.begin(), tokenizerObject.end(), back_inserter(args));
    // Parse the file and store the options
    namespace po = boost::program_options;
    try {
      po::store(
        po::command_line_parser(args)
          .options(odFull)
          .style(po::command_line_style::allow_long | po::command_line_style::long_allow_next)
          .run(),
        vm);
    } catch (const std::exception& e) {
      std::cerr << progname << ": Error: " << e.what() << "\n\n" << odFull << '\n';
      return false;
    }
  }

  try {
    po::notify(vm);
  } catch (const std::exception& e) {
    std::cerr << progname << ": Error: " << e.what() << "\n\n" << odFull << '\n';
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

auto
OutputErrorAndReturnFalse(const std::string& a_message)
-> bool
{
  std::cerr << progname << ": Error: " << a_message << "\n\n";
  return false;
}

auto
ParseBoolean(const char* a_optarg, bool& a_field, const std::string& a_on, const std::string& a_off)
-> bool
{
  if (strcmp(a_optarg, a_on.c_str()) == 0) {
    a_field = true;
  } else if (strcmp(a_optarg, a_off.c_str()) == 0) {
    a_field = false;
  } else {
    return false;
  }
  return true;
}

} // namespace

auto
ABcb::cli::CheckArguments(const boost::program_options::variables_map& a_vm)
-> bool
{
  if (a_vm.count("help") != 0) {
    return false; // force a error so the usage is shown automatically
  }

  if (a_vm.count("input-positive-double") != 0) {
    if (inputPositiveDouble <= 0.) {
      return OutputErrorAndReturnFalse("The input-positive-double parameter must be positive");
    }
  }

  if (a_vm.count("input-ID") != 0) {
    try {
      inputUnsignedChar = boost::numeric_cast<unsigned char>(inputUnsignedCharCLI);
    } catch (const boost::numeric::bad_numeric_cast&) {
      std::ostringstream oss;
      oss << "Wrong input-ID parameter '" << inputUnsignedCharCLI << '\''
          << " (maximum allowed: " << static_cast<size_t>(boost::numeric::bounds<unsigned char>::highest()) << ')';
      const std::string message = oss.str();
      return OutputErrorAndReturnFalse(message);
    }
  }

  if (a_vm.count("platonic-solid") != 0) {
    const auto& text = a_vm["platonic-solid"].as<std::string>();
    platonicSolid = PlatonicSolid::GetEnum(text);
    if (platonicSolid == PlatonicSolid::Enum::undefined) {
      const std::string message = "Unknown platonic-solid parameter '" + text + "'";
      return OutputErrorAndReturnFalse(message);
    }
  }

  if (a_vm.count("color") != 0) {
    const auto& text = a_vm["color"].as<std::string>();
    color = Color::GetEnum(text);
    if (color == Color::Enum::undefined) {
      const std::string message = "Unknown color parameter '" + text + "'";
      return OutputErrorAndReturnFalse(message);
    }
  }

  if (a_vm.count("fruit") != 0) {
    const auto& text = a_vm["fruit"].as<std::string>();
    fruit = Fruit::GetEnum(text);
    if (fruit == Fruit::Enum::undefined) {
      const std::string message = "Unknown fruit parameter '" + text + "'";
      return OutputErrorAndReturnFalse(message);
    }
  }

  if (!suggestedWindowPosition.empty()) {
    if (suggestedWindowPosition.size() != 2) {
      std::ostringstream oss;
      oss << "Wrong suggested-window-position parameter ";
      for (auto position : suggestedWindowPosition) {
        oss << position << ' ';
      }
      oss << "-- please, specify 2 (x, y) components";
      const std::string message = oss.str();
      return OutputErrorAndReturnFalse(message);
    }
  }

  if (a_vm.count("verbose") != 0) {
    if (!ParseBoolean(verboseCLI.c_str(), verbose, "on", "off")) {
      return OutputErrorAndReturnFalse("Unknown verbose parameter");
    }
  }

  return true;
}

#define OutputWithCare(a_string) (a_string.empty() ? "[empty]" : a_string)

auto
ABcb::cli::ParsedCommandLine(std::ostream& a_os)
-> std::ostream&
{
  a_os << progname << " was called with the following options:\n\n";

  // 1) File selection
  //
  a_os << "File selection:\n"
       << "  --input-file " << OutputWithCare(filenameIn) << '\n';
  a_os << '\n';

  // 2) Operation flags/parameters
  //
  a_os << "Operation flags/parameters:\n";
  a_os << "  --input-double " << inputDouble << '\n'
       << "  --input-positive-double " << inputPositiveDouble << '\n'
       << "  --input-ID " << inputUnsignedCharCLI << '\n'
       << "  --platonic-solid " << GetString(platonicSolid) << '\n'
       << "  --color " << Color::GetString(color) << '\n'
       << "  --fruit " << Fruit::GetString(fruit) << '\n';
  if (!suggestedWindowPosition.empty()) {
    a_os << "  --suggested-window-position ";
    for (auto position : suggestedWindowPosition) {
      a_os << position << ' ';
    }
    a_os << '\n';
  }
  a_os << '\n';

  // 3) Informative output
  //
  a_os << "Informative output:\n"
       << "  --verbose " << (verbose ? "on" : "off") << '\n';

  a_os << std::flush;
  return a_os;
}
