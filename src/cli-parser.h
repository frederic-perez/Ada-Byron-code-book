#pragma once

#include <array>
#include <cstdint>
#include <initializer_list>
#include <optional>
#include <string>
#include <utility> // for pair
#include <vector>

#include <boost/preprocessor.hpp>
#include <boost/program_options.hpp>

#define ABcb_TO_STR(unused, data, elem) BOOST_PP_STRINGIZE(elem),

// Code originarily based on
// http://www.gamedev.net/topic/437852-c-enum-names-as-strings/
//
#define ABcb_DEFINE_NAMESPACE_WITH_ENUM_TOOLS(namespaceName, sequence) \
  namespace namespaceName { \
\
  enum class Enum : uint8_t { undefined, BOOST_PP_SEQ_ENUM(sequence) }; \
  const std::array enumText{"undefined", BOOST_PP_SEQ_FOR_EACH(ABcb_TO_STR, ~, sequence)}; \
\
  constexpr size_t beyond = enumText.size(); \
\
  inline auto GetEnum(const std::string& a_text) -> Enum \
  { \
    size_t i = 1; \
    for (; i < beyond and a_text != enumText[i]; ++i) \
      ; \
    return i < beyond ? static_cast<Enum>(i) : Enum::undefined; \
  } \
\
  inline auto GetString(const Enum a_enum) -> std::string { return enumText[static_cast<size_t>(a_enum)]; } \
\
  inline auto GetDefinedStrings() -> std::vector<std::string> \
  { \
    std::vector<std::string> result; \
    for (size_t i = 1; i < beyond; ++i) { \
      result.emplace_back(enumText[i]); \
    } \
    return result; \
  } \
\
  } // namespace namespaceName

ABcb_DEFINE_NAMESPACE_WITH_ENUM_TOOLS(PlatonicSolid, (tetrahedron)(octahedron)(icosahedron)(hexahedron)(dodecahedron));
ABcb_DEFINE_NAMESPACE_WITH_ENUM_TOOLS(Color, (red)(green)(blue));
ABcb_DEFINE_NAMESPACE_WITH_ENUM_TOOLS(Fruit, (apple)(orange)(pear));

namespace Ada_Byron_code_book {

void GurusTest(std::initializer_list<std::string>);

// First attempt at creating a template class for enhanced enum classes
#ifdef ADA_BYRON_WORK_IN_PROGRESS_20150616
template <typename Enum, size_t N, std::string>
//, const std::array<const char*, N>& e>
class EnumENH {
  int d_i;
  Enum GetEnum(const std::string&) { return Enum::undefined; }
};

template <typename Enum>
auto
GetEnum(const std::string& a_text)
-> Enum
{
  // uint8_t i = first;
  // for (; i <= last and a_text != enumText[i]; ++i);
  // if (i <= last)
  //   return static_cast<Enum>(i);
  return Enum::undefined;
}

enum class FooBar : uint8_t { undefined, foo, bar };
const std::string fooAndBarText = "foo and bar";
namespace {
const std::string s = "abc";
}
const std::array fooBarText{"undefined", "foo", "bar"};

// using ConcreteType = EnumENH<FooBar, 3, s>; //, fooBarText>;
using ConcreteType = EnumENH<FooBar, 3, "string">; //, fooBarText>;
#endif

namespace cli {

class Parser {
public:
  Parser() = default;

  auto ParseCommandLine(int argc, char** argv) -> std::optional<std::pair<std::string, std::string>>;
  // '- when succeeding, it returns argv0 and programName

  void LogParsedCommandLine() const;

private:
  bool CheckArguments(const boost::program_options::variables_map&);

  char* d_argv0 = nullptr;
  char* d_program_name = nullptr;

  // 1) File selection
  //
  std::string d_filenameIn;

  // 2) Operation flags/parameters
  //
  double d_inputDouble = 42.666;
  double d_inputPositiveDouble = .8;
  size_t d_inputUnsignedCharCLI;
  unsigned char d_inputUnsignedChar;
  PlatonicSolid::Enum d_platonicSolid = PlatonicSolid::Enum::undefined;
  Color::Enum d_color = Color::Enum::undefined;
  Fruit::Enum d_fruit = Fruit::Enum::undefined;
  std::vector<size_t> d_suggestedWindowPosition;

  // 3) Informative output
  //
  bool d_verbose = false;
  std::string d_verboseCLI;
  static const std::string d_usageParameterExamples;
};

} // namespace cli

} // namespace Ada_Byron_code_book
