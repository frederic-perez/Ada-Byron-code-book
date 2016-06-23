// -- 

#include <future>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>

#if !defined(_MSC_VER)
#include <array>
#include <chrono>
#include <string>

#include <pthread.h> // From 3rd party library POSIX threads
#endif

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
	// Start GetFibonacci30() asynchronously 
	std::future<size_t> result30 = std::async(GetFibonacci30);
	// Call GetFibonacci40() synchronously 
	const size_t result40 = GetFibonacci40();
	// Wait for GetFibonacci30() and add its result to result2
	const size_t result = result30.get() + result40;
	std::ostringstream oss;
	oss.imbue(std::locale("")); // To add commas when outputting result
	oss << result;
	std::cout << pad << "std::future and std::async example: "
		<< "GetFibonacci30() + GetFibonacci40() = " << oss.str() << std::endl;
}

} // namespace

void
ABcb::ExamplesOfConcurrencyUsingCpp11()
{
	std::clog << __func__ << " started..." << std::endl;

	ExampleOf3ThreadsAndMutex();
	ExampleOfFutureAndAsync();

	std::clog << __func__ << " finished." << std::endl;
}

#if !defined(_MSC_VER)

// TODO: void ExamplesOfConcurrencyUsingPOSIXThreads();
// TODO: Start by translating into C++ (using Pthreads) the simple example in
// https://en.wikipedia.org/wiki/POSIX_Threads
/*
ADD use examples of:
- creating threads (detached, joinable)
- pthread_join
- mutex, rwlocks, conditions, barriers and semaphores
- thread cancellations
*/

namespace POSIX {

void
Waiter(size_t a_threadNumber)
{
	std::cout << pad << pad << __func__ 
		<< " starts to wait for 5 seconds [thread #"
		<< a_threadNumber << ", thread_self()=" << pthread_self() << "]..."
		<< std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	std::cout << pad << pad << __func__ 
		<< " is about to end (sleeping time finished)" << std::endl;
}

pthread_barrier_t barrier;

void*
Function(void* a_param)
{
	const size_t threadNumber = reinterpret_cast<size_t>(a_param);

	std::ostringstream oss;
	oss << " [thread #" << threadNumber << ", thread_self()=" << pthread_self()
		<< ']';
	const std::string threadInfo = oss.str();

	if (threadNumber == 3) {
		std::cout << pad << pad << __func__ << " is about to call Waiter"
			<< threadInfo << std::endl;
		Waiter(threadNumber);
	}

	std::cout << pad << pad << __func__ << " is about to stop for barrier"
		<< threadInfo << std::endl;
	const int rc = pthread_barrier_wait(&barrier); // Synchronization point
	if (rc != 0 && rc != PTHREAD_BARRIER_SERIAL_THREAD) {
		std::cerr << pad << pad << __func__
			<< ": Error: Could not wait on barrier. Exiting.\n";
		exit(-1);
	}
	std::cout << pad << pad << __func__ << " exited from barrier" << threadInfo
		<< std::endl;
	return nullptr;
}

void*
OutputThreadSelf(void*)
{
	std::cout << pad << pad << __func__ << " called [thread_self()="
		<< pthread_self() << ']' << std::endl;
	return nullptr;
}

void
ExampleOfPthreadsBarrierCreateAndJoin()
{
	std::clog << pad << __func__ << " started..." << std::endl;

	const size_t NumberOfThreads = 6;

	if (pthread_barrier_init(&barrier, nullptr, NumberOfThreads)) {
		std::cerr << pad << __func__
			<< ": Failed to initialize the barrier. Exiting.\n";
		return;
	}

	std::array<pthread_t, NumberOfThreads> threads;
	for (size_t i = 0; i < NumberOfThreads; ++i)
		pthread_create(&threads[i], nullptr, Function, reinterpret_cast<void*>(i));
	for (auto thread : threads)
		pthread_join(thread, nullptr);

	std::cout << pad << __func__ << " starts to wait for 1 second..."
		<< std::flush;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cout << " (finished)" << std::endl;

	for (auto thread : threads)
		pthread_create(&thread, nullptr, OutputThreadSelf, nullptr);
	for (auto thread : threads)
		pthread_join(thread, nullptr);

	std::clog << pad << __func__ << " finished." << std::endl;
}

} // namespace POSIX

void
ABcb::ExamplesOfConcurrencyUsingPOSIXThreads()
{
	std::clog << __func__ << " started..." << std::endl;

	POSIX::ExampleOfPthreadsBarrierCreateAndJoin();

	std::clog << __func__ << " finished." << std::endl;
}

#endif // !defined(_MSC_VER)

// -- eof
