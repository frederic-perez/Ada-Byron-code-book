// -- 

#pragma once

#include <ostream>
#include <string>

#include <boost/noncopyable.hpp>

namespace Ada_Byron_code_book {

namespace spy {

std::ostream& BoostVersion(std::ostream&);
std::ostream& ClangVersion(std::ostream&);
std::ostream& GNUGppVersion(std::ostream&);
std::ostream& VisualStudioCppCompilerVersion(std::ostream&);

std::ostream& HostName(std::ostream&);
std::ostream& LocalTime(std::ostream&);

class RunInfo; // To be used like std::cout << RunInfo("my-progname") << ...
std::ostream& operator<<(std::ostream&, const RunInfo&);

class RunInfo : boost::noncopyable {
public:
	RunInfo(const std::string& a_progname) : d_progname(a_progname) {}
	const std::string& GetProgName() const { return d_progname; }
private:
	const std::string d_progname;
};

} // spy

} // Ada_Byron_code_book

// -- eof
