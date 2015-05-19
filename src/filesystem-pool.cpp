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
	std::cout << std::endl;

	namespace bf = boost::filesystem;

	const std::string pad = "  ";

	// Preferred separator and directories

	const bf::path::value_type slash = bf::path::preferred_separator;
	std::cout << pad << "path::preferred_separator (system slash) is \'"
		<< static_cast<char>(slash) << '\'' << std::endl;

	bf::path path1 = "C:\\Windows\\System32";
	std::cout << pad << "path1: " << path1 << " becomes (after make_preferred) ";
	path1.make_preferred();
	std::cout << path1 << " which "
		<< (bf::exists(path1) ? "exists" : "does not exist") << std::endl;

	bf::path path2 = "/usr/include/./clang";
	std::cout << pad << "path2: " << path2 << " becomes (after make_preferred) ";
	path2.make_preferred();
	std::cout << path2 << " which "
		<< (bf::exists(path2) ? "exists" : "does not exist") << std::endl;

	// "Testing" an invented filename

	const std::string inventedFilename =
		"invented-filename-to-check-if-it-exists.yuk";
	std::cout << pad << '\"' << inventedFilename << '\"';
	if (bf::exists(inventedFilename))
		std::cout << " exists" << std::endl;
	else 
		std::cout << " does not exist" << std::endl;

	// "Testing" a_filename

	if (!bf::exists(a_filename)) { // Bail out ASAP
		std::cout << " does not exist" << std::endl;
		std::clog << __func__ << " aborted." << std::endl;
		return;
	}

	std::cout << pad << '\"' << a_filename << '\"' << " has a file_size of "
		<< bf::file_size(a_filename) << " bytes" << std::endl;

	std::cout << pad << '\"' << a_filename << '\"';
	const bf::path myPath1(a_filename);
	if (myPath1.has_extension())
		std::cout << " has the extension " << myPath1.extension();
	else
		std::cout << " does not have any extension";
	std::cout << std::endl;

	// "Testing" the current directory

	const std::string dot = ".";
	const bf::path currentDir(dot);
	const bool isDirectory = is_directory(currentDir);
	std::cout << pad << "is_directory(" << currentDir << ") = " << std::boolalpha
		<< isDirectory << std::endl;
	const bf::path fullPathCD = bf::system_complete(dot);
	std::cout << pad << "full path of " << currentDir << " = " << fullPathCD
		<< std::endl;

	if (isDirectory) {
		std::cout << pad
			<< "Directory " << currentDir << " contents:\n" + pad + pad
			<< std::flush;
		const std::string eol = "\n" + pad + pad;
		std::copy(
			bf::directory_iterator(currentDir), bf::directory_iterator(),
			std::ostream_iterator<bf::directory_entry>(std::cout, eol.c_str()));
			// directory_iterator::value_type is directory_entry, which is converted
			// to a path by the path stream inserter
		std::cout << std::flush;
	}
	std::cout << std::endl;
	std::clog << __func__ << " finished." << std::endl;
}

// -- eof
