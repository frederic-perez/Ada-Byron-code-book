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
std::ostream& UserName(std::ostream&);
std::ostream& LocalTime(std::ostream&);

class RunInfo; // To be used like std::cout << RunInfo("my-progname") << ...
std::ostream& operator<<(std::ostream&, const RunInfo&);

class RunInfo : boost::noncopyable {
public:
	explicit RunInfo(const std::string& a_progname) : d_progname(a_progname) {}
	const std::string& GetProgName() const { return d_progname; }
private:
	const std::string d_progname;
};

template<typename T>
std::ostream&
Output(
	std::ostream& a_os,
	const T& a_container,
	const std::string& a_containerName)
{
	a_os << a_containerName << " = ";
	if (a_container.empty())
		a_os << "[empty]" << std::endl;
	else {
		a_os << "[" << a_container.size() << "]{ ";
		for (auto value : a_container)
			a_os << value << ' ';
		a_os << '}' << std::endl;
	}
	return a_os;
}

} // spy

} // Ada_Byron_code_book

// -- eof
