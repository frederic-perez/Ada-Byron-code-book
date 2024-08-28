#include <future>
#include <mutex>
#include <sstream>
#include <thread>

#if !defined(_MSC_VER)
#  include <array>
#  include <chrono>
#  include <string>

#  include <pthread.h> // From 3rd party library POSIX threads
#endif

#include "aux-raw.hpp"
#include "concurrency.hpp"
#include "log.hpp"

namespace ABcb = Ada_Byron_code_book; // Stroustrup C++ PL, p. 179

using ABcb::raw::pad;
using ABcb::raw::pad2x;

namespace {

std::mutex m;

void
run(const size_t a_n)
{
  m.lock();
  for (size_t i = 0; i < 4; ++i)
    B_LOG_INFO << pad2x << a_n << ": " << i;
  m.unlock();
}

// From C++11 slides - Alex Sinkayov.pdf
void
ExampleOf3ThreadsAndMutex()
{
  B_LOG_TRACE << pad << __func__ << " started...";
  std::thread t1(run, 1);
  std::thread t2(run, 2);
  std::thread t3(run, 3);

  t1.join();
  t2.join();
  t3.join();
  B_LOG_TRACE << pad << __func__ << " finished.";
}

// From C++1 slides by Alex Sinkayov
size_t
Fibonacci(size_t a_n)
{
  return a_n <= 2 ? 1 : Fibonacci(a_n - 1) + Fibonacci(a_n - 2);
}

size_t
GetFibonacci30()
{
  return Fibonacci(30);
}
size_t
GetFibonacci40()
{
  return Fibonacci(40);
}

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
  B_LOG_INFO
    << pad << "std::future and std::async example: "
    << "GetFibonacci30() + GetFibonacci40() = " << oss.str();
}

} // namespace

void
ABcb::ExamplesOfConcurrencyUsingCpp11()
{
  B_LOG_TRACE_STARTED

  ExampleOf3ThreadsAndMutex();
  ExampleOfFutureAndAsync();

  B_LOG_TRACE_FINISHED
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
  B_LOG_TRACE
    << pad2x << __func__ << " starts to wait for 5 seconds [thread #" << a_threadNumber
    << ", thread_self()=" << pthread_self() << "]...";
  std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  B_LOG_TRACE
    << pad2x << __func__ << " is about to end (sleeping time finished)";
}

pthread_barrier_t barrier;

void*
Function(void* a_param)
{
  const size_t threadNumber = reinterpret_cast<size_t>(a_param);

  std::ostringstream oss;
  oss << " [thread #" << threadNumber << ", thread_self()=" << pthread_self() << ']';
  const std::string threadInfo = oss.str();

  if (threadNumber == 3) {
    B_LOG_INFO << pad2x << __func__ << " is about to call Waiter" << threadInfo;
    Waiter(threadNumber);
  }

  B_LOG_INFO << pad2x << __func__ << " is about to stop for barrier" << threadInfo;
  const int rc = pthread_barrier_wait(&barrier); // Synchronization point
  if (rc != 0 and rc != PTHREAD_BARRIER_SERIAL_THREAD) {
    B_LOG_ERROR << pad2x << __func__ << ": Error: Could not wait on barrier. Exiting.";
    exit(-1);
  }
  B_LOG_INFO << pad2x << __func__ << " exited from barrier" << threadInfo;
  return nullptr;
}

void*
LogThreadSelf(void*)
{
  B_LOG_TRACE << __func__ << pad2x << __func__ << " called [thread_self()=" << pthread_self() << ']';
  return nullptr;
}

void
ExampleOfPthreadsBarrierCreateAndJoin()
{
  B_LOG_TRACE_STARTED

  const size_t NumberOfThreads = 6;

  if (pthread_barrier_init(&barrier, nullptr, NumberOfThreads)) {
    B_LOG_ERROR << pad << __func__ << ": Failed to initialize the barrier. Exiting.";
    return;
  }

  std::array<pthread_t, NumberOfThreads> threads;
  for (size_t i = 0; i < NumberOfThreads; ++i)
    pthread_create(&threads[i], nullptr, Function, reinterpret_cast<void*>(i));
  for (auto thread : threads)
    pthread_join(thread, nullptr);

  B_LOG_INFO << pad << __func__ << " starts to wait for 1 second...";
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  B_LOG_INFO << " (finished)";

  for (auto thread : threads)
    pthread_create(&thread, nullptr, LogThreadSelf, nullptr);
  for (auto thread : threads)
    pthread_join(thread, nullptr);

  B_LOG_TRACE_FINISHED
}

} // namespace POSIX

void
ABcb::ExamplesOfConcurrencyUsingPOSIXThreads()
{
  B_LOG_TRACE_STARTED

  POSIX::ExampleOfPthreadsBarrierCreateAndJoin();

  B_LOG_TRACE_FINISHED
}

#endif // !defined(_MSC_VER)
