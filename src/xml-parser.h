// --

// Based on the example by Andrzej Krzemienski
// in https://akrzemi1.wordpress.com/examples/parsing-xml/

// Copyright 2014 Andrzej Krzemienski.
//
// This demonstrates how to use Boost.PropertyTree
// to read and write XML files.

#include <locale>
#include <string>

#undef DATETRANSLATOR
#ifdef DATETRANSLATOR
#include <boost/date_time/gregorian/gregorian.hpp>
#endif

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#ifdef DATETRANSLATOR
typedef boost::gregorian::date Date;
#else
typedef std::string Date;
#endif

struct Flight
{
	std::string carrier;
	unsigned number;
	Date date;
	bool cancelled;
};
 
typedef std::vector<Flight> Sked;

#ifdef DATETRANSLATOR

class DateTranslator
{
	typedef boost::date_time::date_facet<Date, char> tOFacet;
	typedef boost::date_time::date_input_facet<Date, char> tIFacet;
	std::locale locale_;
	 
	static std::locale isoDateLocale() {
		std::locale loc = std::locale(loc, new tIFacet("%Y-%m-%d"));
		loc = std::locale(loc, new tOFacet("%Y-%m-%d"));
		return loc;
	}
	 
public:
	typedef std::string internal_type;
	typedef Date external_type;
	 
	DateTranslator() : locale_(isoDateLocale()) {}
	 
	boost::optional<external_type>
	get_value(internal_type const& v)
	{
		std::istringstream stream(v);
		stream.imbue(locale_);
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
		ans.imbue(locale_);
		ans << v;
		return ans.str();
	}
};

#endif

namespace Ada_Byron_code_book {

bool
ParseXML(
	const std::string& a_inputFilename,
	const std::string& a_outputFilename);

} // namespace Ada_Byron_code_book

// -- eof
