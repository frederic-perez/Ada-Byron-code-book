# Ada Byron’s code book

<p align="center">
  <img src="images/Ada%20Byron--from%20teaser%20of%20Happy%20Ada%20Lovelace%20Day%202015%20by%20Natasha%20Sayce-Zelem-200V.jpg?raw=true" alt="Ada Byron from the Wikipedia"/>
</p>

This “book” gathers a collection of C++ code snippets ready to be used as examples or reused in your own projects. The name Ada Byron in the repository title is a homage to the first software programmer ([Wikipedia entry](https://en.wikipedia.org/wiki/Ada_Lovelace)).

I use to build binaries for these settings (sorted alphabetically)

- Apple Mac OS X:
  - 10.11 El Capitan, Xcode 7.1.1 (LLVM, clang++) 64-bit (discontinued in January 2016)
  - ~~10.10 Yosemite, Xcode 6.2 (LLVM, clang++) 64-bit~~
- Linux Ubuntu: g++ 4.8.2, clang++ 3.4.1 (discontinued in October 2019)
- Microsoft Windows
  - 10 Pro:
    - Microsoft Visual Studio Community 2022 v17 (started in December 2021)
    - ~~Microsoft Visual Studio Community 2019 v16~~
  - 8.1 Pro:
    - Microsoft Visual Studio Community 2015 v14 (started in July 2015; discontinued in October 2019)
    - ~~Microsoft Visual Studio Community 2013 v12~~

and for all of them we use

- [Boost](https://www.boost.org/) Version [1.86.0](https://www.boost.org/users/history/version_1_86_0.html) (August 14th, 2024)
- ~~Boost Version 1.78.0 (December 8th, 2021)~~
- ~~Boost Version 1.76.0 (April 16th, 2021)~~
- ~~Boost Version 1.75.0 (December 11th, 2020)~~
- ~~Boost Version 1.59.0 (August 13th, 2015)~~
- ~~Boost Version 1.58.0 (April 17th, 2015)~~
- ~~Boost Version 1.57.0 (November 3rd, 2014)~~

The “book” uses modern C++ features, and includes:

- Boost examples, using both just headers and installed components:
  - `<boost/filesystem.hpp>`, `<boost/system/config.hpp>`
  - casts (`boost::lexical_cast`, `boost::numeric_cast`)
  - `<boost/algorithm/string.hpp>` nice tools
  - XML parsing
- (TODO: Finish porting code from my Evernote’s notes)

## Reference material

Some interesting URLs on different C++ revisions:

- C++ language revisions: Wikipedia’s [C++23](https://en.wikipedia.org/wiki/C%2B%2B23), [C++20](https://en.wikipedia.org/wiki/C%2B%2B20), [C++17](https://en.wikipedia.org/wiki/C%2B%2B17), [C++14](https://en.wikipedia.org/wiki/C%2B%2B14), [C++11](https://en.wikipedia.org/wiki/C%2B%2B11), [C++03](https://en.wikipedia.org/wiki/C%2B%2B03), and [C++98](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) entries
- [A cheatsheet of modern C++ language and library features](https://github.com/AnthonyCalandra/modern-cpp-features), by Anthony Calandra
- Herb Sutter’s post on [Elements of modern style](https://herbsutter.com/elements-of-modern-c-style/)
- [Improved Type Inference in C++11](https://www.cprogramming.com/c++11/c++11-auto-decltype-return-value-after-function.html)
- Scott Meyers’s post on the [Effective C++11 book](http://scottmeyers.blogspot.co.at/2013/01/effective-c11-content-and-status.html)
- Post on [lambdas](https://blog.feabhas.com/2014/03/demystifying-c-lambdas/)
- Alex Sinyakov’s [C++11 cheat sheet](https://isocpp.org/blog/2012/12/c11-a-cheat-sheet-alex-sinyakov)
- Concurrency:
  - Bartosz Milewski’s post on [Functional Data Structures and Concurrency in C++](https://bartoszmilewski.com/2013/12/10/functional-data-structures-and-concurrency-in-c/)
  - [cppreference.com’s thread](http://en.cppreference.com/w/cpp/thread)
  - [C++11 concurrency cheat sheet](http://cpprocks.com/c-concurrency-cheatsheet/)
  - Solarian Programmer’s [C++11 multithreading tutorial](https://solarianprogrammer.com/2011/12/16/cpp-11-thread-tutorial/) (posted on December 16, 2011), [C++11 multithreading tutorial - part 2](https://solarianprogrammer.com/2012/02/27/cpp-11-thread-tutorial-part-2/), both with [code on GitHub](https://github.com/sol-prog/threads)
  - K Hong’s [Multi-Threaded Programming with C++11 - Part A](https://www.bogotobogo.com/cplusplus/multithreaded4_cplusplus11.php), [Part B
(Sharing Data - mutex, and race conditions, and deadlock)](https://www.bogotobogo.com/cplusplus/multithreaded4_cplusplus11B.php); [Debugging - 2020](https://www.bogotobogo.com/cplusplus/multithreadedDebugging.php)

A never complete list of great C++ references (selected books, etc.):

- Scott Meyers, _More Efficient C++: 35 New Ways to Improve Your Programs and Designs_ (mec++, for short), Addison-Wesley Professional Computing Series, 1996.
- Andrew Koenig, Barbara Moo, _Ruminations on C++: A Decade of Programming Insight and Experience_, Addison-Wesley, 1997. (I particularly love Chapter 4, Checklist for class authors.)
- Bjarne Stroustrup, _The C++ Programming Language - Third Edition_, Addison-Wesley, 1997.
- Anthony Williams, _C++ Concurrency in Action: Practical Multithreading_, Manning Publications, 2012.
- Wikibooks’ C++ programming [subject](https://en.wikibooks.org/wiki/C%2B%2B_Programming), and [category](https://en.wikibooks.org/wiki/Category:Subject:C%2B%2B_programming_language).
- Yurii Cherkasov’s [The comprehensive catalog of C++ books](https://github.com/yuchdev/CppBooks)- [C++ links: Learning and teaching](https://github.com/MattPD/cpplinks): A categorized list of C++ resources (a GitHub repo by MattPD).
- [Modernes C++](https://www.modernescpp.com/)
- MITK’s [Bug Squashing Seminars](https://www.mitk.org/wiki/Bug_Squashing_Seminars)

A list of Boost-related stuff:

- Boris Schäling’s [The Boost C++ Libraries](https://theboostcpplibraries.com/)
- Antony Polukhin’s [Boost Application Development Cookbook Online Examples](http://apolukhin.github.io/Boost-Cookbook-4880OS/)

Guidelines:

- A new open source project, led by Bjarne Stroustrup, on GitHub to build modern authoritative guidelines for writing C++ code: [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines)
- Herb Sutter, Andrei Alexandrescu, _C++ Coding Standards: 101 Rules, Guidelines, and Best Practices_, Addison Wesley Professional, 2004
- [LLVM Coding Standards](http://llvm.org/docs/CodingStandards.html)

C++ compilers:

- [stroustrup.com/compilers.html](https://www.stroustrup.com/compilers.html), by Bjarne Stroustrup

A list of interesting libraries or toolkits:

- OpenGL Mathematics (GLM), a header only C++ mathematics library for graphics software

Some questions, and code:

- StackOverflow’s [questions tagged C++](https://stackoverflow.com/questions/tagged/c%2b%2b)

And finally, a list of good programming practices and other interesting programming books:

- Martin Fowler, Kent Beck, John Brant, William Opdyke, Don Roberts, _Refactoring: Improving the Design of Existing Code_, Addison Wesley, 2000

### Code analysis

We strive to maintain a certain quality on the code by taking advantage of some tools:

- Cppcheck - A tool for static C/C++ code analysis. Being myself a fan of portable apps, I particularly use the version from [PortableApps.com](https://portableapps.com/apps/development/cppcheck-portable).
- “Analyze and Code Cleanup » Run Code Analysis on Only Ada-Byron-code-book” when using Microsoft Windows 10 Pro: Microsoft Visual Studio Community 2019 (Version 16)
- “Product » Analyze” when using Apple OS X: Xcode 7.1.1 (LLVM, clang++) 64-bit
- In g++ and clang++, address/thread/memory sanitizer (ASan, TSan, MSan)—for example, for ASan, with the flags `-fsanitize=address -fno-omit-frame-pointer`. See [google/sanitizers repo](https://github.com/google/sanitizers).
- [SonarLint](https://www.sonarsource.com/products/sonarlint/), a _Free_ and _Open Source_ IDE extension that identifies and helps you fix quality and security issues as you code. Like a spell checker, SonarLint squiggles flaws and provides real-time feedback and clear remediation guidance to deliver clean code from the get-go.

Other tools related to code analysis:

- TODO (try this): [C-Reduce](https://github.com/csmith-project/creduce) _“takes a large C or C++ program that has a property of interest (such as triggering a compiler bug) and automatically produces a much smaller C/C++ program that has the same property.”_

### Commits

When committing changes, we now favor using emojis that convey information (see, for example, [gitmoji](https://gitmoji.dev/)). In the past we used common prefixes—see for example a [list of ITK changes](https://www.kitware.com/itk-4-7-2-has-been-released/). From the [Slicer’s style guide](https://slicer.readthedocs.io/en/latest/developer_guide/style_guide.html):

| Prefix | What          |
| ------ |:--------------|
| BUG   | a change made to fix a runtime issue (crash, segmentation fault, exception, or incorrect result) |
| COMP  | a fix for a compilation issue, error or warning |
| DOC   | a documentation change |
| ENH   | new functionality added to the project |
| PERF  | a performance improvement |
| STYLE | a change that does not impact the logic or execution of the code (improve coding style, comments) |

Example commit messages:

- Bad: BUG: Check pointer validity before dereferencing -> _implementation detail, self-explanatory_ (by looking at the code)
- Good: BUG: Fix crash in Module X when clicking Apply button
- Bad: ENH: More work in qSlicerXModuleWidget -> more work is _too vague_, qSlicerXModuleWidget is too _low level_
- Good: ENH: Add float image outputs in module X
- Bad: COMP: Typo in cmake variable -> _implementation detail, self-explanatory_
- Good: COMP: Fix compilation error with Numpy on Visual Studio

### Online compilers

- [List at Get Started!](https://isocpp.org/get-started)
- [Coliru](https://coliru.stacked-crooked.com/)
- [Compiler Explorer (Godbolt)](https://godbolt.org/)
- [cppinsights.io](https://cppinsights.io/)
- The site [&lt;Coding Ground&gt;](https://www.tutorialspoint.com/codingground.htm) includes a [C++ online compiler](https://www.tutorialspoint.com/online_cpp_compiler.php)
- [Rextester](https://rextester.com/l/cpp_online_compiler_visual)
- [Wandbox](https://wandbox.org/)

### Miscellaneous notes

Advice on **unnecessary comments**:

- Avoid (or remove) unnecessary comments! For example, from C++ Gotchas: Avoiding Common Problems in Coding and Design, by Stephen C. Dewhurst: Gotcha #1: Excessive Commenting: _“If a maintainer has to be reminded of the meaning of the `public:` label [for example with the comment `// Public Interface`], you don’t want that person maintaining your code.”_

Why C++ does not have a **`super` keyword**, and we do not promote creating any proxy for that:

- See the most voted answer of this [StackOverflow’s thread](https://stackoverflow.com/questions/180601/using-super-in-c).

Do not write (for example) **`using namespace std;`** in header files or before an `#include`:

- From Programming, Principles and Practice Using C++, by Stroustrup: _“Be restrained in the use or `using` directives. The notational convenience offered by a `using` directive is achieved at the cost or potential name clashes. In particular, avoid `using` directives in header files.”_
- From Thinking in C++, 2nd ed. Vol. 1, by Eckel: _“Thus, if you start putting `using` directives in header files, it’s very easy to end up “turning off” namespaces practically everywhere, and thereby neutralizing the beneficial effects of namespaces. In short: don’t put `using` directives in header files.”_
- From Industrial Strength C++, by Henricson and Nyquist: _“A `using` declaration or a `using` directive in the global scope is not recommended inside header files, since it will make names globally accessible to all files that include that header.”_
- From C++ Coding Standards: 101 Rules, Guidelines, and Best Practices, by Sutter and Alexandrescu: _“Rule 59: Don’t write namespace `#using`s in a header file or before an `#include`.”_

Advices on **Hungarian notation**, from well-known C++ gurus:

- _“Notations that incorporate type information in variable names have mixed utility in type-unsafe languages (notably C), are possible but have no benefits (only drawbacks) in object-oriented languages, and are impossible in generic programming. Therefore, no C++ coding standard should require Hungarian notation, though a C++ coding standard might legitimately choose to ban it.”_ (from C++ Coding Standards: 101 Rules, Guidelines, and Best Practices, by Herb Sutter and Andrei Alexandrescu)
- _“Additionally, never attempt to encode a variable’s type in its name. For instance, calling an integer index iIndex is actively damaging to understanding and maintaining the code. First, a name should describe a program entity’s abstract meaning, not how it’s implemented (data abstraction can apply even to predefined types). Second, in the common case that the variable’s type changes, just as common is that its name doesn’t change in sync. The variable’s name then becomes an effective source of misinformation about its type.”_ (from C++ Gotchas: Avoiding Common Problems in Coding and Design, by Stephen C. Dewhurst; Gotcha #8: Failure to Distinguish Access and Visibility)
- Examples: Ditch `std::string sName; int iIndex;` and write instead `std::string name; int index;`

---

_Note: To render a GitHub (or Bitbucket) webpage containing code with a tab size of 2 spaces, append to its URL_ `?ts=2`.
