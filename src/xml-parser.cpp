// --

// Based on the example by Andrzej Krzemienski
// in https://akrzemi1.wordpress.com/examples/parsing-xml/

// Copyright 2014 Andrzej Krzemienski.
//
// This demonstrates how to use Boost.PropertyTree
// to read and write XML files.

#undef XML_DATE_TRANSLATOR_20150325

#include <iostream>
#ifdef XML_DATE_TRANSLATOR_20150325
#include <locale>
#endif
#include <vector>

#ifdef XML_DATE_TRANSLATOR_20150325
#include <boost/date_time/gregorian/gregorian.hpp>
#endif
//#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/version.hpp>

#include "aux-raw.h"
#include "xml-parser.h"

#ifdef XML_DATE_TRANSLATOR_20150325

class DateTranslator
{
	using tOFacet = boost::date_time::date_facet<Date, char>;
	using tIFacet = boost::date_time::date_input_facet<Date, char>;
	std::locale d_locale;

	static std::locale isoDateLocale() {
		std::locale loc = std::locale(loc, new tIFacet("%Y-%m-%d"));
		loc = std::locale(loc, new tOFacet("%Y-%m-%d"));
		return loc;
	}

public:
	using internal_type = std::string;
	using external_type = Date;

	DateTranslator() : d_locale(isoDateLocale()) {}

	boost::optional<external_type>
	get_value(internal_type const& v)
	{
		std::istringstream stream(v);
		stream.imbue(d_locale);
		external_type vAns;
		if (stream >> vAns)
			return vAns;
		else
			return boost::none;
	}

	boost::optional<internal_type>
	put_value(external_type const& v)
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

class Flight
{
public:
	Flight(
		const std::string& a_carrier,
		unsigned a_number,
		const Date& a_date,
		bool a_cancelled)
	: d_carrier(a_carrier),
		d_number(a_number),
		d_date(a_date),
		d_cancelled(a_cancelled)
	{}

	std::string d_carrier;
	unsigned d_number;
	Date d_date;
	bool d_cancelled;
};

using Flights = std::vector<Flight>;

#ifdef XML_DATE_TRANSLATOR_20150325

namespace boost {
namespace property_tree {

template<> struct translator_between<std::string, Date> {
	using type = XML_DATE_TRANSLATOR_20150325 type;
};

} // namespace property_tree
} // namespace boost

#endif

namespace {

void
read(std::istream& a_is, Flights& a_flights)
{
	// populate tree structure pt
	using boost::property_tree::ptree;
	ptree pt;
	read_xml(a_is, pt);

	// traverse pt
	for (const ptree::value_type& v : pt.get_child("flights")) {
		if (v.first == "flight") {
			const std::string carrier = v.second.get<std::string>("carrier");
			const unsigned number = v.second.get<unsigned>("number");
			const Date date = v.second.get<Date>("date");
			const bool cancelled = v.second.get("<xmlattr>.cancelled", false);
			const Flight flight(carrier, number, date, cancelled);
			a_flights.push_back(flight);
		}
	}
}

void
write(const Flights& a_flights, std::ostream& a_os)
{
	using boost::property_tree::ptree;
	ptree pt;

	pt.add("flights.version", 3);

	for (const auto& flight : a_flights) {
		ptree& node = pt.add("flights.flight", "");
		node.put("carrier", flight.d_carrier); // TODO: Add and use inspectors!
		node.put("number", flight.d_number);
		node.put("date", flight.d_date);
		if (flight.d_cancelled)
			node.put("<xmlattr>.cancelled", true);
	}

#if BOOST_VERSION >= 105700
	boost::property_tree::xml_writer_settings<std::string> settings('\t', 1);
#else
	boost::property_tree::xml_writer_settings<char> settings('\t', 1);
#endif
	write_xml(a_os, pt, settings); //write_xml(a_os, pt);
}

} // namespace

bool
Ada_Byron_code_book::ParseXML(
	const std::string& a_inputFilename,
	const std::string& a_outputFilename)
{
	std::clog << __func__ << " started..." << std::endl;
	try {
		std::ifstream input(a_inputFilename);
		Flights flights;
		read(input, flights);
		using raw::pad;
		std::clog << pad << __func__ << ": Read(\"" << a_inputFilename
			<< "\") finished" << std::endl;
		std::ofstream output(a_outputFilename);
		write(flights, output);
		std::clog << pad << __func__ << ": Writing of \"" << a_outputFilename
			<< "\" finished" << std::endl;
	} catch (...) {
		return false;
	}
	std::clog << __func__ << " finished." << std::endl;
	return true;
}

// -- eof
