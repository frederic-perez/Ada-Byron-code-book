// -- 

#include <iostream>
#include <mutex>
#include <thread>

#include "aux-raw.h"
#include "concurrency.h"

namespace ABcb = Ada_Byron_code_book; // Stroustrup C++ PL, p. 179

using ABcb::raw::pad;

namespace {

std::mutex m;

void
run(size_t a_n) {
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

} // namespace

void
ABcb::ExamplesOfConcurrency()
{
	std::clog << __func__ << " started..." << std::endl;

	ExampleOf3ThreadsAndMutex();

	std::clog << __func__ << " finished." << std::endl;
}

// -- eof
