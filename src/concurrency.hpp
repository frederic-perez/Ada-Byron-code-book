#pragma once

namespace Ada_Byron_code_book {

void ExamplesOfConcurrencyUsingCpp11();

#if !defined(_MSC_VER)

// From https://en.wikipedia.org/wiki/POSIX_Threads (on March 17, 2016)
// "Windows does not support the pthreads standard natively, therefore the
// Pthreads - w32 project seeks to provide a portable and open - source wrapper
// implementation. It can also be used to port Unix software(which use
// pthreads) with little or no modification to the Windows platform."

void ExamplesOfConcurrencyUsingPOSIXThreads();

#endif

} // namespace Ada_Byron_code_book
