## Ada Byron's code book

This "book" gathers a collection of C++ code snippets ready to be used as examples or reused in your own projects. The name Ada Byron in the repository title is a homage to the first software programmer ([Wikipedia entry](http://en.wikipedia.org/wiki/Ada_Lovelace)).

I use to build binaries for these settings:
- Microsoft Windows 8.1: Visual Studio 12 2013 Win64
- Linux Ubuntu: g++ 4.8.2, clang++ 3.4.1
- Apple OS X: Xcode 6.2 (LLVM, clang++) 64-bit

The "book" uses C++11 features, and includes:
- Boost examples, using both just headers and installed components:
  - <code>&lt;boost/filesystem.hpp&gt;, &lt;boost/system/config.hpp&gt;</code> 
  - <code>boost::lexical_cast</code>
  - <code>&lt;boost/algorithm/string.hpp&gt;</code> nice tools
  - XML parsing
- (In the future it will contain code ported from my Evernote's notes)

Some interesting C++11-related URLs:
- http://en.wikipedia.org/wiki/C%2B%2B11
- http://herbsutter.com/elements-of-modern-c-style/
- http://www.cprogramming.com/c++11/c++11-auto-decltype-return-value-after-function.html
- http://scottmeyers.blogspot.co.at/2013/01/effective-c11-content-and-status.html
- http://blog.feabhas.com/2014/03/demystifying-c-lambdas/
