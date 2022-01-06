// -- Examples on how to use boost::lexical_cast

#include <limits>
#include <sstream>
#include <string>

#include "aux-raw-compiler-warnings-off++begin.h"
// clang-format off
  #include <boost/lexical_cast.hpp>
// clang-format on
#include "aux-raw-compiler-warnings-off++end.h"

#include "aux-raw.h"
#include "aux-spy+.h" // for TypeNameENH
#include "conversions+casts++.h"
#include "log.h"

namespace ABcb = Ada_Byron_code_book;
using ABcb::raw::pad;

void
ABcb::ExamplesOfIstringstreamFailingConversions()
{
  B_LOG_TRACE_STARTED

  // Old way, which so far does not work properly -- TODO: Fix this

  const std::string string = "14 -1 3";
  B_LOG_INFO << pad << "Parsing string \"" << string << "\" to unsigned ints i, j, k using std::istringstream >> ";
  std::istringstream iss(string); // or parse(string)
  unsigned int i;
  iss >> i;
  if (!iss.good()) // Note: `if (iss.fail)` does not work fine for our purposes
    B_LOG_ERROR << "Error parsing first index";
  else {
    unsigned int j;
    iss >> j;
    if (!iss.good())
      B_LOG_ERROR << pad << "Error parsing second index (expected behavior)";
    else {
      unsigned int k;
      iss >> k;
      if (!iss.good())
        B_LOG_ERROR
          << pad << "Error parsing third index (i=" << i << ", j=" << j
          << "), but it should have failed for the second index";
      else
        B_LOG_INFO << pad << "indices: " << i << ", " << j << ", " << k;
    }
  }

  B_LOG_TRACE_FINISHED
}

void
ABcb::ExamplesOfCpp11Conversions()
{
  B_LOG_TRACE_STARTED

  std::string string = "14 -1 67.89 3.1416 5e-7";
  B_LOG_INFO << pad << "Parsing string \"" << string << "\"";
  std::string::size_type idx;
  const unsigned long ul = std::stoul(string, &idx);
  string = string.substr(idx);
  const int i = std::stoi(string, &idx);
  string = string.substr(idx);
  const float f = std::stof(string, &idx);
  string = string.substr(idx);
  const double d1 = std::stod(string, &idx);
  string = string.substr(idx);
  const double d2 = std::stod(string); // Caution: idx is not updated here
  B_LOG_INFO
    << pad << pad << ">> std::stoul: " << ul << "; std::stoi: " << i << "; std::stof: " << f << "; std::stod: " << d1
    << "; std::stod: " << d2;

  const std::string backToString = std::to_string(ul) + ' ' + std::to_string(i) + ' ' + std::to_string(f) + ' '
    + std::to_string(d1) + ' ' + std::to_string(d2);
  B_LOG_INFO << pad << "Back to string (using std::to_string): \"" << backToString << "\"";
  std::ostringstream oss;
  oss << ul << ' ' << i << ' ' << f << ' ' << d1 << ' ' << d2;
  B_LOG_INFO << pad << "Back to string (using std::ostringstream): \"" << oss.str() << "\" <-- Preferred way!";

#if 0
  // From http://www.cplusplus.com/forum/general/125880/
  //
  // vs14 linker error
  const std::u16string utf16 = u"Πυθαγόρας ὁ Σάμιος (Pythagoras of Samos)";
  // http://en.cppreference.com/w/cpp/locale/wstring_convert
  std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> codecvt;
  B_LOG_INFO << pad << codecvt.to_bytes(utf16);

  // vs14 linker error
  const std::u16string utf16 = u"Πυθαγόρας ὁ Σάμιος";
  const std::u16string another_utf16 = u"(Pythagoras of Samos)";

  // http://en.cppreference.com/w/cpp/locale/wstring_convert
  std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> codecvt;

  std::ostringstream ograph;
  ograph << "the two UTF-16 strings contain: '" << codecvt.to_bytes(utf16)
          << "' and '" << codecvt.to_bytes(another_utf16) << "'";

  B_LOG_INFO << ograph.str();
#endif

  // TODO: Study and go ahead with stuff from
  // http://en.cppreference.com/w/cpp/locale/codecvt_utf8_utf16

  // TODO: Add more examples from www.cplusplus.com/reference/string/

  B_LOG_TRACE_FINISHED
}

void
ABcb::ExamplesOfBoostLexicalCast(const std::string& a_numberToConvert)
{
  B_LOG_TRACE_STARTED

  using boost::bad_lexical_cast;
  using boost::lexical_cast;

  const int valueIntS = stoi(a_numberToConvert);
  B_LOG_INFO << pad << "stoi(\"" << a_numberToConvert << "\") is " << valueIntS;
  const auto valueIntL = lexical_cast<int>(a_numberToConvert);
  B_LOG_INFO << pad << "lexical_cast<int>(\"" << a_numberToConvert << "\") is " << valueIntL;

  const auto valueShortS = static_cast<short>(stoi(a_numberToConvert));
  B_LOG_INFO << pad << "stoi(\"" << a_numberToConvert << "\") is " << valueShortS;
  try {
    const auto valueShortL = lexical_cast<short>(a_numberToConvert);
    B_LOG_INFO << pad << "lexical_cast<short>(\"" << a_numberToConvert << "\") is " << valueShortL;
  } catch (const boost::bad_lexical_cast& e) {
    B_LOG_ERROR << pad << "Exception caught: " << e.what();
  }

  B_LOG_TRACE_FINISHED
}

namespace {

template <class SourceT, class TargetT>
void
UseStdNumericLimitsPlusStaticCast_FAILS_SOMETIMES(const SourceT a_source)
{
  B_LOG_INFO << pad << __func__ << ": a_source (" << ABcb::spy::TypeNameENH<SourceT>() << ") = " << a_source;
#include "aux-raw-compiler-warnings-off++begin.h"
  bool succeeded = true;
  const auto typeNameENHOfTargetT = ABcb::spy::TypeNameENH<TargetT>();
  if (a_source < std::numeric_limits<TargetT>::lowest()) { // Now in C++ (we used to use boost before)
    B_LOG_ERROR << pad << __func__ << ": Error: a_source too small to convert to " << typeNameENHOfTargetT;
    succeeded = false;
  } else if (a_source > std::numeric_limits<TargetT>::max()) { // Use just C++
    B_LOG_ERROR << pad << __func__ << ": Error: a_source too large to convert to " << typeNameENHOfTargetT;
    succeeded = false;
  }
#include "aux-raw-compiler-warnings-off++end.h"

  if (!succeeded)
    return;
  const auto target = static_cast<TargetT>(a_source);

  // Keep on using sourceObjectSelf from this point onwards

  B_LOG_INFO << pad << pad << ">> target (" << typeNameENHOfTargetT << ") = " << static_cast<double>(target);
}

template <class SourceT, class TargetT>
void
ApplyBoostNumericCast(const SourceT a_source)
{
  /*

  The code below--using boost::numeric_cast<T>--beats the previous options, so
  this is the best code so far.
  Explanations on boost::numeric_cast<T>::... can be found, for example, in
  From Beyond the C++ Standard Library - An Introduction to Boost, by
  Björn Karlsson: Part I : General Libraries, Library 2 : Conversion,
  numeric_cast

  Note: Another possibility would be using std::stod (from <string>)

  */

#include <boost/numeric/conversion/bounds.hpp>

  B_LOG_INFO << pad << __func__ << ": a_source (" << ABcb::spy::TypeNameENH<SourceT>() << ") = " << a_source;
  TargetT target = 66;
  const auto typeNameOfTargetT = ABcb::spy::TypeNameENH<TargetT>();
  try {
    target = boost::numeric_cast<TargetT>(a_source);
    B_LOG_INFO << pad << pad << ">> target (" << typeNameOfTargetT << ") = " << static_cast<long double>(target);
  } catch (const boost::numeric::bad_numeric_cast& e) {
    B_LOG_ERROR
      << pad << __func__ << ": Error: Bad target (" << static_cast<long double>(target)
      << ", which is the preset value) tried conversion (to " << typeNameOfTargetT << "): " << e.what();
  }
}

} // namespace

void
ABcb::ExamplesOfBoostNumericCast()
{
  B_LOG_TRACE_STARTED

  int source = 123456;
  using SourceT = decltype(source);
  ApplyBoostNumericCast<SourceT, signed long>(source);
  ApplyBoostNumericCast<SourceT, unsigned long>(source);
  source = -123456;
  using Target1 = signed long;
  UseStdNumericLimitsPlusStaticCast_FAILS_SOMETIMES<SourceT, Target1>(source);
  ApplyBoostNumericCast<SourceT, Target1>(source);
  using Target2 = unsigned long;
  UseStdNumericLimitsPlusStaticCast_FAILS_SOMETIMES<SourceT, Target2>(source);
  ApplyBoostNumericCast<SourceT, Target2>(source);
  source = 4200;
  using Target3 = char;
  UseStdNumericLimitsPlusStaticCast_FAILS_SOMETIMES<SourceT, Target3>(source);
  ApplyBoostNumericCast<SourceT, Target3>(source);
  source = 42;
  ApplyBoostNumericCast<SourceT, unsigned char>(source);
  source = 1234567890;
  ApplyBoostNumericCast<SourceT, double>(source);

  B_LOG_TRACE_FINISHED
}
