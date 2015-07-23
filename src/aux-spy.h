// -- 

#pragma once

#include <ostream>
#include <string>

#include <boost/noncopyable.hpp>

// TODO: Possibly extend SpyLine with Boost's PP for extra information

#define SpyLine \
	std::cerr << "@@@@ " << __FILE__ << ':' << __func__ << ":L" << __LINE__ \
		<< '\n';

namespace Ada_Byron_code_book {

namespace spy {

std::ostream& BoostVersion(std::ostream&);
std::ostream& ClangVersion(std::ostream&);
std::ostream& GNUGppVersion(std::ostream&);
std::ostream& VisualStudioCppCompilerVersion(std::ostream&);

std::ostream& HostName(std::ostream&);
std::ostream& UserName(std::ostream&);
std::ostream& LocalDate(std::ostream&);
std::ostream& LocalTime(std::ostream&);
std::ostream& SizeOfs(std::ostream&);

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
	a_os << (a_containerName.empty() ? "[unnamed]" : a_containerName) << " = ";
	if (a_container.empty())
		a_os << "[empty]" << std::endl;
	else {
		const size_t N = a_container.size();
		a_os << "[" << N << "]{";
		for (size_t i = 0; i < N; ++i) {
			a_os << a_container[i];
			if (i < N - 1)
				a_os << ", ";
		}
		a_os << '}' << std::endl;
	}
	return a_os;
}

template<typename TClock>
class Timer : boost::noncopyable {
	//
	// Based on the example under
	// http://www.boost.org/doc/libs/1_47_0/doc/html/chrono/users_guide.html
	// #chrono.users_guide.examples.time_point.a_tiny_program_that_times_how_
	// long_until_a_key_is_struck
	//
	// Examples
	// --------
	//	Timer<boost::chrono::system_clock> t1;
	//	Timer<boost::chrono::steady_clock> t2; // GCC duplicate?
	//	Timer<boost::chrono::high_resolution_clock> t3;
	//
public:
	Timer();
	double Seconds() const;

	void Reset();

protected:
	typename TClock::duration Elapsed() const;
	typename TClock::time_point d_start;
};

} // spy

} // Ada_Byron_code_book

// -- eof
