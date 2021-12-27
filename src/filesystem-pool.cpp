// -- Examples on how to use boost::filesystem

#include <iostream>

#define BOOST_LIB_DIAGNOSTIC

#include <boost/filesystem.hpp>
#include <boost/system/config.hpp>

#include "aux-raw.h"
#include "filesystem-pool.h"

namespace ABcb = Ada_Byron_code_book;
using ABcb::raw::pad;

namespace bf = boost::filesystem;

namespace {

void
DoSomeStuff(bf::path& a_path, const std::string& a_label)
{
  std::cout << pad << a_label << ": " << a_path << " becomes (after make_preferred) ";
  a_path.make_preferred();
  std::cout << a_path << " which " << (bf::exists(a_path) ? "exists" : "does not exist") << std::endl;
}

} // namespace

void
ABcb::ExamplesOfFileSystem(const std::string& a_filename)
{
  std::clog << __func__ << " started..." << std::endl;
  std::cout << std::endl;

  // Preferred separator and directories

  const bf::path::value_type slash = bf::path::preferred_separator;
  std::cout << pad << "path::preferred_separator (system slash) is \'" << static_cast<char>(slash) << '\'' << std::endl;

  bf::path path1 = bf::path("C:\\Windows") / "System32"; // operator/
  DoSomeStuff(path1, "path1");

  bf::path path2 = bf::path("/usr") / "include" / "." / "clang"; // operator/
  DoSomeStuff(path2, "path2");

  // Geting temporary directory path (temporary folder)

  bf::path tempDirectoryPath;
  try {
    tempDirectoryPath = bf::temp_directory_path();
    // '- Returns: A directory path suitable for temporary files under the
    // conventions of the operating system. The specifics of how this path is
    // determined are implementation defined.
    std::cout << pad << "temp_directory_path() returned " << tempDirectoryPath << std::endl;
  } catch (...) {
    std::cerr << __func__ << ": Error: Could not get temporary folder\n";
  }

  // "Testing" and invented file (random file)

  const bf::path randomPath =
    bf::unique_path(bf::path("invented-filename-to-check-if-it-exists-%%%%-%%%%-%%%%-%%%%.yuk"));
  std::cout << pad << '\"' << randomPath.string() << '\"';
  if (bf::exists(randomPath))
    std::cout << " exists" << std::endl;
  else
    std::cout << " does not exist" << std::endl;

  // "Testing" a_filename

  if (not bf::exists(a_filename)) { // Bail out ASAP
    std::cout << " does not exist" << std::endl;
    std::clog << __func__ << " aborted." << std::endl;
    return;
  }

  std::cout << pad << '\"' << a_filename << '\"' << " has a file_size of " << bf::file_size(a_filename) << " bytes"
            << std::endl;

  bf::path myPath1("/usr/include/assert.h");
  std::cout << pad << "Path " << myPath1;
  if (myPath1.has_extension()) {
    std::cout << " has the extension " << myPath1.extension() << std::endl;
    myPath1.replace_extension(".new_extension");
    std::cout << pad << "Path " << myPath1 << " now (after replace_extension) has the extension "
              << myPath1.extension();
  } else
    std::cout << " does not have any extension";
  std::cout << std::endl;

  // "Testing" the current directory

  const std::string dot = ".";
  const bf::path currentDir(dot);
  const bool isDirectory = is_directory(currentDir);
  std::cout << pad << "is_directory(" << currentDir << ") = " << std::boolalpha << isDirectory << std::endl;
  const bf::path fullPathCD = bf::system_complete(dot);
  std::cout << pad << "full path of " << currentDir << " = " << fullPathCD << std::endl;

  if (isDirectory) {
    std::cout << pad << "Directory " << currentDir << " contents:\n" + pad + pad << std::flush;
    const std::string eol = "\n" + pad + pad;
    std::copy(
      bf::directory_iterator(currentDir),
      bf::directory_iterator(),
      std::ostream_iterator<bf::directory_entry>(std::cout, eol.c_str()));
    // directory_iterator::value_type is directory_entry, which is converted
    // to a path by the path stream inserter
    std::cout << std::flush;
  }
  std::cout << std::endl;
  std::clog << __func__ << " finished." << std::endl;
}
