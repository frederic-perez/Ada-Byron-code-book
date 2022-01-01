// -- Examples on how to use boost::algorithm::string

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#ifdef _MSC_VER
#  include <atlstr.h>
#endif

#include "aux-raw-compiler-warnings-off++begin.h"
// clang-format off
  #include <boost/algorithm/string.hpp>
  #include <boost/locale.hpp>
  #include <boost/log/trivial.hpp>
  #include <boost/range/algorithm/remove_if.hpp>
// clang format on
#include "aux-raw-compiler-warnings-off++end.h"

#include "algorithm-string-pool.h"
#include "aux-raw.h"

namespace {

void
DoLog(const std::string& a_description, const std::string& a_value)
{
  using Ada_Byron_code_book::raw::pad;
  BOOST_LOG_TRIVIAL(info) << pad << a_description << ": \"" << a_value << "\"";
}

void
DoLog(const std::string& a_description, const std::wstring& a_value)
{
  using Ada_Byron_code_book::raw::pad;
  BOOST_LOG_TRIVIAL(info) << pad << a_description << ": \"" << a_value << "\"";
}

void
ourToLower(std::string& a_text)
{
#ifdef _MSC_VER
  CStringA text = a_text.c_str();
  text.MakeLower();
  a_text = text.GetBuffer();
#else
  std::transform(a_text.begin(), a_text.end(), a_text.begin(), ::tolower);
  for (auto& c : a_text) {
    switch (c) {
    case '�': c = '�'; break;
    case '�': c = '�'; break;
    case '�': c = '�'; break;
    case '�': c = '�'; break;
    case '�': c = '�'; break;
    case '�': c = '�'; break;
    case '�': c = '�'; break;
    case '�': c = '�'; break;
    case '�': c = '�'; break;
    case '�': c = '�'; break;
    case '�': c = '�'; break;
    case '�': c = '�'; break;
    case '�': c = '�'; break;
    case '�': c = '�'; break;
    case '�': c = '�'; break;
    case '�': c = '�'; break;
    case '�': c = '�'; break;
    default:;
    }
  }
#endif
}

} // namespace

void
Ada_Byron_code_book::ExamplesOfAlgorithmsString()
{
  BOOST_LOG_TRIVIAL(trace) << __func__ << " started...";

  using Ada_Byron_code_book::raw::pad;
  BOOST_LOG_TRIVIAL(info) << pad << "sizeof(char) = " << sizeof(char);
  BOOST_LOG_TRIVIAL(info) << pad << "sizeof(wchar_t) = " << sizeof(wchar_t);

  namespace bl = boost::locale;
  std::locale loc("");
  std::locale::global(loc);
  std::locale conv_loc = boost::locale::util::create_info(loc, loc.name());
  // See
  // www.boost.org/doc/libs/1_57_0/libs/locale/doc/html/locale_information.html
  BOOST_LOG_TRIVIAL(info) << pad << "locale: The name code is `" << std::use_facet<bl::info>(conv_loc).name() << "`";

  std::string name = "  Alan Turing 42  ";
  DoLog("%% name (original)", name);
  name.erase(boost::remove_if(name, ::isdigit), name.end());
  // '- Notice that all "remove_if" call has an "erase" companion to do the actual cleanup.
  //    This happens for both std:: and boost::, by the way
  DoLog("   name (after isdigit removal)", name);

  namespace ba = boost::algorithm;
  ba::to_lower(name);
  DoLog("   name (after to_lower)", name);
  ba::to_upper(name);
  DoLog("   name (after to_upper)", name);
  ba::trim_right(name);
  DoLog("   name (after trim_right)", name);
  ba::trim(name);
  DoLog("   name (after trim)", name);
  if (ba::iequals(name, "AlAn TuRiNg"))
    DoLog("   iequals(name, \"AlAn TuRiNg\") returns true, with name", name);
  else
    DoLog("   iequals(name, \"AlAn TuRiNg\") returns false, with name", name);
  name.erase(remove_if(name.begin(), name.end(), ::isspace), name.end());
  DoLog("   name (after isspace removal)", name);
  name.erase(remove_if(name.begin(), name.end(), ba::is_any_of("LN")), name.end());
  DoLog("   name (after is_any_of(\"LN\") removal)", name);

  std::string special = "CAF� BJ�RK ����� ����� ����� �� L�L";
  DoLog(">> special (original)", special);
  ourToLower(special);
  DoLog("   special (after ourToLower)", special);
  const std::string specialK = "caf� bj�rk ����� ����� ����� �� l�l";
  const bool equal = special == specialK;
  // '- NOTE on comparing std::string objects:
  //    Use operator== (or operator!=) instead of writing obfuscated code like
  //      strcmp(a_date.c_str(), date2.c_str()) == 0
  //    See
  //      http://en.cppreference.com/w/cpp/string/basic_string/operator_cmp
  //    std::string::operator==:
  //    Simpler, shorter, faster, easier to maintain. Period.

  BOOST_LOG_TRIVIAL(info) << pad << "   special == \"" << specialK << "\" is " << std::boolalpha << equal;

  // Unicode character table: http://unicode-table.com/en/#basic-latin

  const char* raw = "CAF\u00C9 BJ\u00D6RK";
  std::string narrow = raw;
  DoLog("-- narrow (original)", narrow);
  ba::to_lower(narrow);
  DoLog("   narrow (after ba::to_lower)", narrow);

  // std::transform(narrow.begin(), narrow.end(), narrow.begin(), ::tolower);
  //  '- warning C4244: '=': conversion from 'int' to 'char', possible loss of data
  //
  // Thus, we resort to the solution proposed in 
  // https://developercommunity.visualstudio.com/content/problem/23811
  //
  std::transform(
    narrow.begin(), narrow.end(), narrow.begin(),
    [](char c) { return static_cast<char>(::tolower(c)); });
  DoLog("   narrow (after lambda-wrapped ::tolower within transform)", narrow);

  ba::to_upper_copy(narrow);
  DoLog("   narrow (after ba::to_upper_copy)", narrow);
  try {
    bl::to_lower(narrow);
    DoLog("   narrow (after bl::to_lower)", narrow);
  } catch (const std::bad_cast& e) {
    BOOST_LOG_TRIVIAL(error) << pad << "   Error (bl::to_lower): " << e.what();
  }

  const wchar_t* raw_utf16{L"CAF\u00C9 BJ\u00D6RK"};
  std::wstring wide = raw_utf16;
  DoLog("-- wide (original)", wide);
  ba::to_lower(wide);
  DoLog("   wide (after ba::to_lower)", wide);
  std::transform(wide.begin(), wide.end(), wide.begin(), ::towlower);
  DoLog("   wide (after ::towlower)", wide);

  const std::string line = "aa bb , cc dd , ee , gg,hh, ii ,kk";
  DoLog("$$ line (original)", line);
  // Split the string a into sections using "," as the delimiter,
  // store result into a vector of strings
  // Code adapted from http://www.panix.com/~jrr/boost/string.htm on 05.26.2015
  std::vector<std::string> tokens;
  ba::split(tokens, line, ba::is_any_of(","));
  struct Trim {
    void operator()(std::string& a_s) const { ba::trim(a_s); }
  };
  for_each(tokens.begin(), tokens.end(), Trim());
  const std::string instanceCleaned = ba::join(tokens, ",");
  DoLog("   line (after blanks around commas removal)", instanceCleaned);

  BOOST_LOG_TRIVIAL(trace) << __func__ << " finished.";
}
