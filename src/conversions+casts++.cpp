// -- Examples on how to use boost::lexical_cast

//#include <codecvt>
#include <iostream>
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

namespace ABcb = Ada_Byron_code_book;
using ABcb::raw::pad;

void
ABcb::ExamplesOfIstringstreamFailingConversions()
{
  std::clog << __func__ << " started..." << std::endl;

  // Old way, which so far does not work properly -- TODO: Fix this

  const std::string string = "14 -1 3";
  std::cout << pad << "Parsing string \"" << string << "\" to unsigned ints i, j, k using std::istringstream >> "
            << std::flush;
  std::istringstream iss(string); // or parse(string)
  unsigned int i;
  iss >> i;
  if (not iss.good()) // Note: if (iss.fail) does not work fine for our purposes
    std::cerr << "Error parsing first index\n";
  else {
    unsigned int j;
    iss >> j;
    if (not iss.good())
      std::cerr << pad << "Error parsing second index (expected behavior)\n";
    else {
      unsigned int k;
      iss >> k;
      if (not iss.good())
        std::cerr << "Error parsing third index (i=" << i << ", j=" << j
                  << "), but it should have failed for the second index\n";
      else
        std::cout << pad << "indices: " << i << ", " << j << ", " << k << std::endl;
    }
  }

  std::clog << __func__ << " finished." << std::endl;
}

void
ABcb::ExamplesOfCpp11Conversions()
{
  std::clog << __func__ << " started..." << std::endl;

  std::string string = "14 -1 67.89 3.1416 5e-7";
  std::cout << pad << "Parsing string \"" << string << "\" >> " << std::flush;
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
  std::cout << "std::stoul: " << ul << "; std::stoi: " << i << "; std::stof: " << f << "; std::stod: " << d1
            << "; std::stod: " << d2 << std::endl;

  const std::string backToString = std::to_string(ul) + ' ' + std::to_string(i) + ' ' + std::to_string(f) + ' '
    + std::to_string(d1) + ' ' + std::to_string(d2);
  std::cout << pad << "Back to string (using std::to_string): \"" << backToString << "\"" << std::endl;
  std::ostringstream oss;
  oss << ul << ' ' << i << ' ' << f << ' ' << d1 << ' ' << d2;
  std::cout << pad << "Back to string (using std::ostringstream): \"" << oss.str() << "\" <-- Preferred way!"
            << std::endl;

  // From http://www.cplusplus.com/forum/general/125880/
  //
  /* vs14 linker error
  const std::u16string utf16 = u"Πυθαγόρας ὁ Σάμιος (Pythagoras of Samos)";
  // http://en.cppreference.com/w/cpp/locale/wstring_convert
  std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> codecvt;
  std::cout << pad << codecvt.to_bytes(utf16) << std::endl;
  */
  /* vs14 linker error
  const std::u16string utf16 = u"Πυθαγόρας ὁ Σάμιος";
  const std::u16string another_utf16 = u"(Pythagoras of Samos)";

  // http://en.cppreference.com/w/cpp/locale/wstring_convert
  std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> codecvt;

  std::ostringstream ograph;
  ograph << "the two UTF-16 strings contain: '" << codecvt.to_bytes(utf16)
          << "' and '" << codecvt.to_bytes(another_utf16) << "'";

  std::cout << ograph.str() << '\n';
  */

  // TODO: Study and go ahead with stuff from
  // http://en.cppreference.com/w/cpp/locale/codecvt_utf8_utf16

  // TODO: Add more examples from www.cplusplus.com/reference/string/

  std::clog << __func__ << " finished." << std::endl;
}

void
ABcb::ExamplesOfBoostLexicalCast(const std::string& a_numberToConvert)
{
  std::clog << __func__ << " started..." << std::endl;

  using boost::bad_lexical_cast;
  using boost::lexical_cast;

  const int valueIntS = stoi(a_numberToConvert);
  std::cout << pad << "stoi(\"" << a_numberToConvert << "\") is " << valueIntS << std::endl;
  const int valueIntL = lexical_cast<int>(a_numberToConvert);
  std::cout << pad << "lexical_cast<int>(\"" << a_numberToConvert << "\") is " << valueIntL << std::endl;

  const short valueShortS = static_cast<short>(stoi(a_numberToConvert));
  std::cout << pad << "stoi(\"" << a_numberToConvert << "\") is " << valueShortS << std::endl;
  try {
    const short valueShortL = lexical_cast<short>(a_numberToConvert);
    std::cout << pad << "lexical_cast<short>(\"" << a_numberToConvert << "\") is " << valueShortL << std::endl;
  } catch (const boost::bad_lexical_cast& e) {
    std::cerr << pad << "Exception caught: " << e.what() << '\n';
  }

  std::clog << __func__ << " finished." << std::endl;
}

namespace {

template <class SourceT, class TargetT>
void
UseStdNumericLimitsPlusStaticCast_FAILS_SOMETIMES(const SourceT a_source)
{
  std::cout << pad << __func__ << ": a_source (" << ABcb::spy::TypeNameENH<SourceT>() << ") = " << a_source
            << std::flush;
#include "aux-raw-compiler-warnings-off++begin.h"
  bool succeeded = true;
  const auto typeNameENHOfTargetT = ABcb::spy::TypeNameENH<TargetT>();
  // if (a_source < boost::numeric::bounds<TargetT>::lowest()) { vs min()
  if (a_source < std::numeric_limits<TargetT>::lowest()) { // Now in C++
    std::cout << std::endl;
    std::cerr << pad << __func__ << ": Error: a_source too small to convert to " << typeNameENHOfTargetT << '\n';
    succeeded = false;
    //} else if (a_source > boost::numeric::bounds<TargetT>::highest()) {
  } else if (a_source > std::numeric_limits<TargetT>::max()) { // Use just C++
    std::cout << std::endl;
    std::cerr << pad << __func__ << ": Error: a_source too large to convert to " << typeNameENHOfTargetT << '\n';
    succeeded = false;
  }
#include "aux-raw-compiler-warnings-off++end.h"

  if (not succeeded)
    return;
  const TargetT target = static_cast<TargetT>(a_source);

  // Keep on using sourceObjectSelf from this point onwards

  std::cout << "; target (" << typeNameENHOfTargetT << ") = " << static_cast<double>(target) << std::endl;
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

  std::cout << pad << __func__ << ": a_source (" << ABcb::spy::TypeNameENH<SourceT>() << ") = " << a_source
            << std::flush;
  TargetT target = 66;
  const auto typeNameOfTargetT = ABcb::spy::TypeNameENH<TargetT>();
  try {
    target = boost::numeric_cast<TargetT>(a_source);
    std::cout << "; target (" << typeNameOfTargetT << ") = " << static_cast<long double>(target) << std::endl;
  } catch (const boost::numeric::bad_numeric_cast& e) {
    std::cout << std::endl;
    std::cerr << pad << __func__ << ": Error: Bad target (" << static_cast<long double>(target)
              << ", which is the preset value) tried conversion (to " << typeNameOfTargetT << "): " << e.what() << '\n';
  }
}

} // namespace

void
ABcb::ExamplesOfBoostNumericCast()
{
  std::clog << __func__ << " started..." << std::endl;

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

  std::clog << __func__ << " finished." << std::endl;
}
