// -- 

#pragma once

#include <ostream>
#include <string>

namespace Ada_Byron_code_book {

namespace spy {

std::ostream& BoostVersion(std::ostream&);
std::ostream& ClangVersion(std::ostream&);
std::ostream& GNUGppVersion(std::ostream&);
std::ostream& VisualStudioCppCompilerVersion(std::ostream&);

std::ostream& HostName(std::ostream&);
std::ostream& LocalTime(std::ostream&);

class RunInfo; // To be used like std::cout << RunInfo("my-progname") << ...

} // namespace spy

} // namespace Ada_Byron_code_book

std::ostream&
operator<<(std::ostream&, const Ada_Byron_code_book::spy::RunInfo&);

namespace Ada_Byron_code_book {

namespace spy {

class RunInfo { 
public:
	RunInfo(const std::string& a_progname) : d_progname(a_progname) {}
	friend std::ostream& ::operator<<(std::ostream&, const RunInfo&);
private:
	std::string d_progname;
};

} // spy

} // Ada_Byron_code_book

// -- eof
