// --

// Based on the example by Andrzej Krzemienski
// in https://akrzemi1.wordpress.com/examples/parsing-xml/

// Copyright 2014 Andrzej Krzemienski.
//
// This demonstrates how to use Boost.PropertyTree
// to read and write XML files.

#include <iostream>

#include "aux-raw.h"
#include "XML-parser.h"

//#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#ifdef XML_DATE_TRANSLATOR_20150325

namespace boost {
namespace property_tree {
 
template<> struct translator_between<std::string, Date> {
		typedef XML_DATE_TRANSLATOR_20150325 type;
};

} // namespace property_tree
} // namespace boost

#endif

namespace {

Flights
read(std::istream& is)
{
	// populate tree structure pt
	using boost::property_tree::ptree;
	ptree pt;
	read_xml(is, pt);
	 
	// traverse pt
	Flights ans;
	for (const ptree::value_type& v : pt.get_child("sked")) {
		if (v.first == "flight") {
			Flight f;
			f.carrier = v.second.get<std::string>("carrier");
			f.number = v.second.get<unsigned>("number");
			f.date = v.second.get<Date>("date");
			f.cancelled = v.second.get("<xmlattr>.cancelled", false);
			ans.push_back(f);
		}
	}
	return ans;
}
 
void
write(Flights sked, std::ostream & os)
{
	using boost::property_tree::ptree;
	ptree pt;
	 
	pt.add("sked.version", 3);
	 
	for (Flight f : sked) {
		ptree& node = pt.add("sked.flight", "");
		node.put("carrier", f.carrier);
		node.put("number", f.number);
		node.put("date", f.date);
		if (f.cancelled)
			node.put("<xmlattr>.cancelled", true);
	}
	write_xml(os, pt);
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
		Flights sked = read(input);
		std::clog << "  ParseXML: Read(\"" << a_inputFilename << "\") finished"
			<< std::endl;
		std::ofstream output(a_outputFilename);
		write(sked, output);
		std::clog << "  ParseXML: Writing of \"" << a_outputFilename
			<< "\" finished" << std::endl;
	} catch (...) {
		return false;
	}
	std::clog << __func__ << " finished." << std::endl;
	return true;
}

// -- eof
