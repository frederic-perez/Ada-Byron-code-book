// -- Examples on how to use boost::filesystem

#include <iostream>

#define BOOST_LIB_DIAGNOSTIC

#include <boost/filesystem.hpp>
#include <boost/system/config.hpp>

#include "aux-raw.h"
#include "filesystem-pool.h"

void
Ada_Byron_code_book::ExamplesOfFileSystem(const std::string& a_filename)
{
	std::clog << __func__ << " started..." << std::endl;

	using namespace boost::filesystem;

	const std::string pad = "  ";

	// "Testing" an invented filename
	const std::string inventedFilename =
		"invented-filename-to-check-if-it-exists.yuk";
	std::cout << pad << '\"' << inventedFilename << '\"';
	if (boost::filesystem::exists(inventedFilename))
		std::cout << " exists" << std::endl;
	else 
		std::cout << " does not exist" << std::endl;

	// "Testing" a_filename

	if (!boost::filesystem::exists(a_filename)) { // Bail out ASAP
		std::cout << " does not exist" << std::endl;
		std::clog << __func__ << " aborted." << std::endl;
		return;
	}

	std::cout << pad << '\"' << a_filename << '\"' << " has a file_size of "
		<< file_size(a_filename) << " bytes" << std::endl;

	std::cout << pad << '\"' << a_filename << '\"';
	const path myPath1(a_filename);
	if (myPath1.has_extension())
		std::cout << " has the extension " << myPath1.extension();
	else
		std::cout << " does not have any extension";
	std::cout << std::endl;

	// "Testing" the current directory

	const std::string dot = ".";
	const path currentDir(dot);
	const bool isDirectory = is_directory(currentDir);
	std::cout << pad << "is_directory(" << currentDir << ") = " << std::boolalpha
		<< isDirectory << std::endl;

	if (isDirectory) {
		std::cout << pad << "Directory contents:" << std::endl;
		const std::string eol = "\n";
		std::copy(
			directory_iterator(currentDir), directory_iterator(),
			std::ostream_iterator<directory_entry>(std::cout, eol.c_str()));
			// directory_iterator::value_type is directory_entry, which is converted
			// to a path by the path stream inserter
		std::cout << std::flush;
	}

	std::clog << __func__ << " finished." << std::endl;
}

// -- eof
