// Based on the example by Andrzej Krzemienski
// in https://akrzemi1.wordpress.com/examples/parsing-xml/

// Copyright 2014 Andrzej Krzemienski.
//
// This demonstrates how to use Boost.PropertyTree
// to read and write XML files.

#define XML_DATE_TRANSLATOR_20150325

#ifdef XML_DATE_TRANSLATOR_20150325
#  include <locale>
#endif
#include <vector>

#ifdef XML_DATE_TRANSLATOR_20150325
#  include <boost/date_time/gregorian/gregorian.hpp>
#endif
#include <boost/filesystem.hpp>
//#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/version.hpp>

#include "aux-raw.hpp" // for pad
#include "log.hpp"
#include "xml-parser.hpp"

#ifdef XML_DATE_TRANSLATOR_20150325

using Date = boost::gregorian::date;

class DateTranslator {
  using tOFacet = boost::date_time::date_facet<Date, char>;
  using tIFacet = boost::date_time::date_input_facet<Date, char>;
  std::locale d_locale;

  static std::locale isoDateLocale()
  {
    std::locale loc; // default ctor first
    loc = std::locale(loc, new tIFacet("%Y-%m-%d"));
    loc = std::locale(loc, new tOFacet("%Y-%m-%d"));
    return loc;
  }

public:
  using internal_type = std::string;
  using external_type = Date;

  DateTranslator() : d_locale(isoDateLocale()) {}

  boost::optional<external_type> get_value(internal_type const& v)
  {
    std::istringstream stream(v);
    stream.imbue(d_locale);
    external_type vAns;
    if (stream >> vAns)
      return vAns;
    else
      return boost::none;
  }

  boost::optional<internal_type> put_value(external_type const& v)
  {
    std::ostringstream ans;
    ans.imbue(d_locale);
    ans << v;
    return ans.str();
  }
};

#endif

#ifdef XML_DATE_TRANSLATOR_20150325
using Date = boost::gregorian::date;
#else
using Date = std::string;
#endif

class Flight {
public:
  Flight(const std::string& a_carrier, unsigned a_number, const Date& a_date, bool a_cancelled)
  : d_carrier(a_carrier), d_number(a_number), d_date(a_date), d_cancelled(a_cancelled)
  {}

  const std::string& GetCarrier() const { return d_carrier; }
  unsigned GetNumber() const { return d_number; }
  const Date& GetDate() const { return d_date; }
  bool IsCancelled() const { return d_cancelled; }

private:
  std::string d_carrier;
  unsigned d_number;
  Date d_date;
  bool d_cancelled;
};

using Flights = std::vector<Flight>;

#ifdef XML_DATE_TRANSLATOR_20150325

namespace boost::property_tree {

template <>
struct translator_between<std::string, Date> {
  using type = DateTranslator;
};

} // namespace boost::property_tree

#endif

namespace {

void
Read(std::istream& a_istream, Flights& a_flights)
{
  using Ada_Byron_code_book::raw::pad;

  // populate tree structure pt
  using boost::property_tree::ptree;
  ptree pt;
  read_xml(a_istream, pt);
  // '- TODO: Study: read_xml(a_istream, pt, 0, std::locale());

  // traverse pt
  for (const ptree::value_type& pairStringPtree : pt.get_child("flights")) {
    if (pairStringPtree.first == "flight") {
      const ptree& subtree = pairStringPtree.second;
      const std::string carrier = subtree.get<std::string>("carrier");
      unsigned number = 0;
      try {
        number = subtree.get<unsigned>("number");
      } catch (const std::exception& e) {
        B_LOG_ERROR << pad << __func__ << ": std::exception caught: " << e.what();
        throw; // rethrow the original exception, no slicing or anything
      }
      const Date date = subtree.get<Date>("date");
      const bool cancelled = subtree.get("<xmlattr>.cancelled", false);
      const Flight flight(carrier, number, date, cancelled);
      a_flights.push_back(flight);
    }
  }
}

void
Write(const Flights& a_flights, std::ostream& a_ostream)
{
  using boost::property_tree::ptree;
  ptree pt;

  pt.add("flights.version", 3);

  for (const auto& flight : a_flights) {
    ptree& node = pt.add("flights.flight", "");
    node.put("carrier", flight.GetCarrier());
    node.put("number", flight.GetNumber());
    node.put("date", flight.GetDate());
    if (flight.IsCancelled())
      node.put("<xmlattr>.cancelled", true);
  }

#if BOOST_VERSION >= 105700
  boost::property_tree::xml_writer_settings<std::string> settings('\t', 1);
#else
  boost::property_tree::xml_writer_settings<char> settings('\t', 1);
#endif
  write_xml(a_ostream, pt, settings); // write_xml(a_ostream, pt);
}

} // namespace

bool
Ada_Byron_code_book::ParseXML(const std::string& a_inputFilename, const std::string& a_outputFilename)
{
  B_LOG_TRACE_STARTED

  using raw::pad;
  namespace bf = boost::filesystem;
  if (bf::exists(a_inputFilename))
    B_LOG_INFO << pad << __func__ << ": Reading " << a_inputFilename;
  else {
    B_LOG_ERROR << pad << __func__ << ": " << a_inputFilename << " does not exist";
    return false;
  }
  try {
    std::ifstream input(a_inputFilename);
    Flights flights;
    try {
      Read(input, flights);
    } catch (const std::exception& e) {
      B_LOG_ERROR << pad << __func__ << ": Exception by 'Read' caught: " << e.what();
      return false;
    }
    B_LOG_INFO << pad << __func__ << ": Read(\"" << a_inputFilename << "\") finished";
    std::ofstream output(a_outputFilename);
    Write(flights, output);
    B_LOG_INFO << pad << __func__ << ": Writing of \"" << a_outputFilename << "\" finished";
  } catch (...) {
    B_LOG_ERROR << pad << __func__ << ": Exception ... caught";
    return false;
  }

  B_LOG_TRACE_FINISHED
  return true;
}
