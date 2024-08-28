// -- Examples on how to use boost::filesystem

#include <sstream> // for std::ostringstream

#define BOOST_LIB_DIAGNOSTIC

#include <boost/system/config.hpp>

#include "aux-raw.hpp"
#include "filesystem-pool.hpp"
#include "log.hpp"

namespace ABcb = Ada_Byron_code_book;
using ABcb::raw::pad;
using ABcb::raw::pad2x;

namespace bf = boost::filesystem;
namespace sf = std::filesystem;

namespace {

void
DoSomeBoostStuff(const std::string& a_label, bf::path& a_path)
{
  B_LOG_INFO << pad << a_label << ": " << a_path.string();

  B_LOG_INFO << pad2x << "» empty: " << a_path.empty();
  B_LOG_INFO << pad2x << "» is_absolute: " << a_path.is_absolute();
  B_LOG_INFO << pad2x << "» is_relative: " << a_path.is_relative();

  B_LOG_INFO << pad2x << "» has_filename: " << a_path.has_filename();
  B_LOG_INFO << pad2x << "» filename: " << a_path.filename();

  B_LOG_INFO << pad2x << "» has_extension: " << a_path.has_extension();
  B_LOG_INFO << pad2x << "» extension: " << a_path.extension();

  B_LOG_INFO << pad2x << "» has_parent_path: " << a_path.has_parent_path();
  B_LOG_INFO << pad2x << "» parent_path: " << a_path.parent_path().string();

  B_LOG_INFO << pad2x << "» has_root_path: " << a_path.has_root_path();
  B_LOG_INFO << pad2x << "» root_path: " << a_path.root_path().string();

  B_LOG_INFO << pad2x << "» lexically_normal: " << a_path.lexically_normal().string();

  a_path.make_preferred();
  B_LOG_INFO
    << pad2x << "becomes (after make_preferred) " << a_path.string()
    << " which " << (bf::exists(a_path) ? "exists" : "does not exist");
}

void
DoSomeStdStuff(const std::string& a_label, sf::path& a_path)
{
  B_LOG_INFO << pad << a_label << ": " << a_path.string();

  B_LOG_INFO << pad2x << "» empty: " << a_path.empty();
  B_LOG_INFO << pad2x << "» is_absolute: " << a_path.is_absolute();
  B_LOG_INFO << pad2x << "» is_relative: " << a_path.is_relative();

  B_LOG_INFO << pad2x << "» has_filename: " << a_path.has_filename();
  B_LOG_INFO << pad2x << "» filename: " << a_path.filename();

  B_LOG_INFO << pad2x << "» has_extension: " << a_path.has_extension();
  B_LOG_INFO << pad2x << "» extension: " << a_path.extension();

  B_LOG_INFO << pad2x << "» has_parent_path: " << a_path.has_parent_path();
  B_LOG_INFO << pad2x << "» parent_path: " << a_path.parent_path().string();

  B_LOG_INFO << pad2x << "» has_root_path: " << a_path.has_root_path();
  B_LOG_INFO << pad2x << "» root_path: " << a_path.root_path().string();

  B_LOG_INFO << pad2x << "» lexically_normal: " << a_path.lexically_normal().string();

  a_path.make_preferred();
  B_LOG_INFO
    << pad2x << "becomes (after make_preferred) " << a_path.string()
    << " which " << (sf::exists(a_path) ? "exists" : "does not exist");
}

} // namespace

void
ABcb::ExamplesOfBoostFileSystem(const bf::path& a_filename)
{
  B_LOG_TRACE_STARTED

  // Preferred separator and directories

  const auto slash = bf::path::preferred_separator;
  B_LOG_INFO << pad << "path::preferred_separator (system slash) is \'" << slash << '\'';

  bf::path path1 = bf::path("C:\\Windows") / "System32"; // operator/
  DoSomeBoostStuff("path1", path1);

  bf::path path2 = bf::path("/usr") / "include" / "." / "clang"; // operator/
  DoSomeBoostStuff("path2", path2);

  // Geting temporary directory path (temporary folder)

  bf::path tempDirectoryPath;
  try {
    tempDirectoryPath = bf::temp_directory_path();
    // '- Returns: A directory path suitable for temporary files under the
    // conventions of the operating system. The specifics of how this path is
    // determined are implementation defined.
    B_LOG_INFO << pad << "temp_directory_path() returned " << tempDirectoryPath.string();
  } catch (const bf::filesystem_error& e) {
    B_LOG_ERROR << __func__ << ": boost::filesystem::filesystem_error caught: " << e.what();
  }

  // "Testing" an invented file (random file)

  const bf::path randomPath =
    bf::unique_path(bf::path("invented-filename-to-check-if-it-exists-%%%%-%%%%-%%%%-%%%%.yuk"));
  B_LOG_INFO
    << pad << '\"' << randomPath.string() << '\"'
    << (bf::exists(randomPath) ? " exists" : " does not exist");

  // "Testing" a_filename

  if (not bf::exists(a_filename)) { // Bail out ASAP
    B_LOG_ERROR << a_filename.string() << " does not exist. Aborted.";
    return;
  }

  B_LOG_INFO << pad << '\"' << a_filename.string() << '\"' << " has a file_size of " << bf::file_size(a_filename) << " bytes";

  // "Split" a_filename

  const auto directory = bf::path(a_filename).remove_filename().string();
  const auto raw_filename = a_filename.filename().string();
  B_LOG_INFO << pad << '\"' << a_filename.string() << '\"' << " » directory = \"" << directory << "\"";
  B_LOG_INFO << pad << '\"' << a_filename.string() << '\"' << " » raw_filename = \"" << raw_filename << "\"";

  bf::path myPath1("/usr/include/assert.h");
  B_LOG_INFO << pad << "Path " << myPath1.string();
  if (myPath1.has_extension()) {
    B_LOG_INFO << pad2x << "has the extension " << myPath1.extension().string();
    myPath1.replace_extension(".new_extension");
    B_LOG_INFO
      << pad2x << "Path " << myPath1.string()
      << " now (after replace_extension) has the extension " << myPath1.extension().string();
  } else
    B_LOG_INFO << pad2x << "does not have any extension";

  // "Testing" the current directory

  const auto currentPath = bf::current_path();
  const bool isDirectory = bf::is_directory(currentPath);
  B_LOG_INFO << pad << "is_directory(" << currentPath.string() << ") = " << std::boolalpha << isDirectory;
  const bf::path fullPathCD = bf::system_complete(currentPath);
  B_LOG_INFO << pad << "full path of " << currentPath.string() << " = " << fullPathCD.string();

  if (isDirectory) {
    const std::string space = " ";
    std::ostringstream oss;
    std::copy(
      bf::directory_iterator(currentPath),
      bf::directory_iterator(),
      std::ostream_iterator<bf::directory_entry>(oss, space.c_str()));
    // directory_iterator::value_type is directory_entry, which is converted
    // to a path by the path stream inserter
    B_LOG_INFO << pad << "Directory " << currentPath.string() << " contents: " << oss.str();
  }

  B_LOG_INFO << pad << "currentPath is currently " << bf::current_path().string();
  bf::current_path(bf::temp_directory_path());
  B_LOG_INFO << pad << "currentPath has been changed to " << bf::current_path().string();
  bf::current_path(currentPath);
  B_LOG_INFO << pad << "currentPath has been changed again to " << bf::current_path().string();

  B_LOG_TRACE_FINISHED
}

// Interesting information is available at https://www.cppstories.com/2019/05/boost-to-stdfs/
// ("Converting from Boost to std::filesystem," by Scott Furry)
//
void
ABcb::ExamplesOfStdFileSystem(const std::filesystem::path& a_filename)
{
  B_LOG_TRACE_STARTED

  // Preferred separator and directories

  const auto slash = sf::path::preferred_separator;
  B_LOG_INFO << pad << "path::preferred_separator (system slash) is \'" << slash << '\'';

  sf::path path1 = sf::path("C:\\Windows") / "System32"; // operator/
  DoSomeStdStuff("path1", path1);

  sf::path path2 = sf::path("/usr") / "include" / "." / "clang"; // operator/
  DoSomeStdStuff("path2", path2);

  // Geting temporary directory path (temporary folder)

  sf::path tempDirectoryPath;
  try {
    tempDirectoryPath = sf::temp_directory_path();
    // '- Returns: A directory path suitable for temporary files under the
    // conventions of the operating system. The specifics of how this path is
    // determined are implementation defined.
    B_LOG_INFO << pad << "temp_directory_path() returned " << tempDirectoryPath.string();
  } catch (const sf::filesystem_error& e) {
    B_LOG_ERROR << __func__ << ": std::filesystem::filesystem_error caught: " << e.what();
  } catch (const std::exception& e) {
    B_LOG_ERROR << __func__ << ": std::exception caught: " << e.what();
  } catch (...) {
    B_LOG_ERROR << __func__ << ": '...' exception caught";
  }

  // "Testing" an invented file (random file)
  //
  // See https://stackoverflow.com/questions/43316527/what-is-the-c17-equivalent-to-boostfilesystemunique-path
  //
  using namespace std::string_literals; // enables s-suffix for std::string literals
  using ABcb::raw::RandomString;
  const auto inventedFilenameRaw =
    "invented-filename-to-check-if-it-exists-"s
    + RandomString(4) + "-" + RandomString(4) + "-" + RandomString(4) + "-" + RandomString(4)
    + ".yuk";
  const auto randomPath = sf::temp_directory_path() / inventedFilenameRaw;
  B_LOG_INFO << pad << "\"" << randomPath.string() << '\"'
    << (sf::exists(randomPath) ? " exists" : " does not exist");

  // "Testing" a_filename

  if (not sf::exists(a_filename)) { // Bail out ASAP
    B_LOG_ERROR << a_filename.string() << " does not exist. Aborted.";
    return;
  }

  B_LOG_INFO << pad << '\"' << a_filename.string() << '\"' << " has a file_size of " << sf::file_size(a_filename) << " bytes";

  // "Split" a_filename

  const auto directory = sf::path(a_filename).remove_filename().string();
  const auto raw_filename = a_filename.filename().string();
  B_LOG_INFO << pad << '\"' << a_filename.string() << '\"' << " » directory = \"" << directory << "\"";
  B_LOG_INFO << pad << '\"' << a_filename.string() << '\"' << " » raw_filename = \"" << raw_filename << "\"";

  sf::path myPath1("/usr/include/assert.h");
  B_LOG_INFO << pad << "Path " << myPath1.string();
  if (myPath1.has_extension()) {
    B_LOG_INFO << pad2x << "has the extension " << myPath1.extension().string();
    myPath1.replace_extension(".new_extension");
    B_LOG_INFO
      << pad2x << "Path " << myPath1.string()
      << " now (after replace_extension) has the extension " << myPath1.extension().string();
  } else
    B_LOG_INFO << pad2x << "does not have any extension";

  // "Testing" the current directory

  const auto currentPath = sf::current_path();
  const bool isDirectory = sf::is_directory(currentPath);
  B_LOG_INFO << pad << "is_directory(" << currentPath.string() << ") = " << std::boolalpha << isDirectory;
  const sf::path fullPathCD = sf::absolute(currentPath); // ported from old bf::system_complete(dot);
  B_LOG_INFO << pad << "full path of " << currentPath.string() << " = " << fullPathCD.string();

  if (isDirectory) {
    const std::string space = " ";
    std::ostringstream oss;
    std::copy(
      sf::directory_iterator(currentPath),
      sf::directory_iterator(),
      std::ostream_iterator<sf::directory_entry>(oss, space.c_str()));
    // directory_iterator::value_type is directory_entry, which is converted
    // to a path by the path stream inserter
    B_LOG_INFO << pad << "Directory " << currentPath.string()  << " contents: " << oss.str();
  }

  B_LOG_INFO << pad << "currentPath is currently " << sf::current_path().string();
  sf::current_path(sf::temp_directory_path());
  B_LOG_INFO << pad << "currentPath has been changed to " << sf::current_path().string();
  sf::current_path(currentPath);
  B_LOG_INFO << pad << "currentPath has been changed again to " << sf::current_path().string();

  B_LOG_TRACE_FINISHED
}
