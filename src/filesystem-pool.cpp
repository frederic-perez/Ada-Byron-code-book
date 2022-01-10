// -- Examples on how to use boost::filesystem

#include <sstream> // for std::ostringstream

#define BOOST_LIB_DIAGNOSTIC

#include <boost/filesystem.hpp>
#include <boost/system/config.hpp>

#include "aux-raw.h"
#include "filesystem-pool.h"
#include "log.h"

namespace ABcb = Ada_Byron_code_book;
using ABcb::raw::pad;

namespace bf = boost::filesystem;

namespace {

void
DoSomeStuff(bf::path& a_path, const std::string& a_label)
{
  B_LOG_INFO << pad << a_label << ": " << a_path;
  a_path.make_preferred();
  B_LOG_INFO
    << pad << "becomes (after make_preferred) " << a_path
    << " which " << (bf::exists(a_path) ? "exists" : "does not exist");
}

} // namespace

void
ABcb::ExamplesOfFileSystem(const std::string& a_filename)
{
  B_LOG_TRACE_STARTED

  // Preferred separator and directories

  const bf::path::value_type slash = bf::path::preferred_separator;
  B_LOG_INFO << pad << "path::preferred_separator (system slash) is \'" << static_cast<char>(slash) << '\'';

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
    B_LOG_INFO << pad << "temp_directory_path() returned " << tempDirectoryPath;
  } catch (...) {
    B_LOG_ERROR << __func__ << ": Error: Could not get temporary folder";
  }

  // "Testing" and invented file (random file)

  const bf::path randomPath =
    bf::unique_path(bf::path("invented-filename-to-check-if-it-exists-%%%%-%%%%-%%%%-%%%%.yuk"));
  B_LOG_INFO
    << pad << '\"' << randomPath.string() << '\"'
    << (bf::exists(randomPath) ? " exists" : " does not exist");

  // "Testing" a_filename

  if (not bf::exists(a_filename)) { // Bail out ASAP
    B_LOG_ERROR << a_filename << " does not exist. Aborted.";
    return;
  }

  B_LOG_INFO << pad << '\"' << a_filename << '\"' << " has a file_size of " << bf::file_size(a_filename) << " bytes";

  // "Split" a_filename

  const auto directory = bf::path(a_filename, nullptr).remove_filename().string();
  const auto raw_filename = bf::path(a_filename, nullptr).filename().string();
  B_LOG_INFO << pad << '\"' << a_filename << '\"' << " » directory = \"" << directory << "\"";
  B_LOG_INFO << pad << '\"' << a_filename << '\"' << " » raw_filename = \"" << raw_filename << "\"";

  bf::path myPath1("/usr/include/assert.h");
  B_LOG_INFO << pad << "Path " << myPath1;
  if (myPath1.has_extension()) {
    B_LOG_INFO << pad << pad << "has the extension " << myPath1.extension();
    myPath1.replace_extension(".new_extension");
    B_LOG_INFO
      << pad << pad << "Path " << myPath1 << " now (after replace_extension) has the extension "
      << myPath1.extension();
  } else
    B_LOG_INFO << pad << pad << "does not have any extension";

  // "Testing" the current directory

  const std::string dot = ".";
  const bf::path currentDir(dot);
  const bool isDirectory = is_directory(currentDir);
  B_LOG_INFO << pad << "is_directory(" << currentDir << ") = " << std::boolalpha << isDirectory;
  const bf::path fullPathCD = bf::system_complete(dot);
  B_LOG_INFO << pad << "full path of " << currentDir << " = " << fullPathCD;

  if (isDirectory) {
    const std::string space = " ";
    std::ostringstream oss;
    std::copy(
      bf::directory_iterator(currentDir),
      bf::directory_iterator(),
      std::ostream_iterator<bf::directory_entry>(oss, space.c_str()));
    // directory_iterator::value_type is directory_entry, which is converted
    // to a path by the path stream inserter
    B_LOG_INFO
      << pad << "Directory " << currentDir << " contents: " << oss.str();
  }
  B_LOG_TRACE_FINISHED
}
