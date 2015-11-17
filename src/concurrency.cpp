// -- 

#include <future>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>

#include "aux-raw.h"
#include "concurrency.h"

namespace ABcb = Ada_Byron_code_book; // Stroustrup C++ PL, p. 179

using ABcb::raw::pad;

namespace {

std::mutex m;

void
run(const size_t a_n) {
	m.lock();
	for (size_t i = 0; i < 4; ++i)
		std::cout << pad << pad << a_n << ": " << i << std::endl;
	m.unlock();
}

void
ExampleOf3ThreadsAndMutex() // From C++11 slides - Alex Sinkayov.pdf
{
	std::clog << pad << __func__ << " started..." << std::endl;
	std::thread t1(run, 1);
	std::thread t2(run, 2);
	std::thread t3(run, 3);

	t1.join();
	t2.join();
	t3.join();
	std::clog << pad << __func__ << " finished." << std::endl;
}

// From C++1 slides by Alex Sinkayov
//
size_t
Fibonacci(size_t a_n)
{	return a_n <= 2 ? 1 : Fibonacci(a_n - 1) + Fibonacci(a_n - 2); }

size_t GetFibonacci30() { return Fibonacci(30); }
size_t GetFibonacci40() { return Fibonacci(40); }

void
ExampleOfFutureAndAsync()
{
	// Start GetFib30() asynchronously 
	std::future<size_t> result30 = std::async(GetFibonacci30);
	// Call GetFib40() synchronously 
	const size_t result40 = GetFibonacci40();
	// Wait for GetFib30() and add its result to result2
	const size_t result = result30.get() + result40;
	std::ostringstream oss;
	oss.imbue(std::locale("")); // To add commas when outputting result
	oss << result;
	std::cout << pad << "std::future and std::async example: "
		<< "GetFib30() + GetFib40() = " << oss.str() << std::endl;
}

} // namespace

void
ABcb::ExamplesOfConcurrency()
{
	std::clog << __func__ << " started..." << std::endl;

	ExampleOf3ThreadsAndMutex();
	ExampleOfFutureAndAsync();

	std::clog << __func__ << " finished." << std::endl;
}

// -- eof
