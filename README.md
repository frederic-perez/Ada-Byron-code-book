## Ada Byron's code book

<p align="center">
  <img src="https://dl.dropboxusercontent.com/u/1068081/Shared-images/Ada_Byron_aged_seventeen_1832--Cr-Ed-200x200.png?raw=true" alt="Ada Byron from the Wikipedia"/>
</p>

This "book" gathers a collection of C++ code snippets ready to be used as examples or reused in your own projects. The name Ada Byron in the repository title is a homage to the first software programmer ([Wikipedia entry](http://en.wikipedia.org/wiki/Ada_Lovelace)).

I use to build binaries for these settings:
- Microsoft Windows 8.1:
  - Visual Studio 14 2015 Win64 (starting in July, 2015)
  - ~~Visual Studio 12 2013 Win64~~
- Linux Ubuntu: g++ 4.8.2, clang++ 3.4.1
- Apple OS X: Xcode 6.2 (LLVM, clang++) 64-bit

and for all of them we use
- [Boost](http://www.boost.org/) Version 1.57.0 (November 3rd, 2014 21:55 GMT)

The "book" uses C++11 features, and includes:
- Boost examples, using both just headers and installed components:
  - <code>&lt;boost/filesystem.hpp&gt;, &lt;boost/system/config.hpp&gt;</code> 
  - <code>boost::lexical_cast</code>
  - <code>&lt;boost/algorithm/string.hpp&gt;</code> nice tools
  - XML parsing
- (In the future it will contain code ported from my Evernote's notes)

### Reference material

Some interesting C++11-related URLs:
- Wikipedia's [C++11](http://en.wikipedia.org/wiki/C%2B%2B11) entry
- Herb Sutter's post on [Elements of modern style](http://herbsutter.com/elements-of-modern-c-style/)
- http://www.cprogramming.com/c++11/c++11-auto-decltype-return-value-after-function.html
- Scott Meyers's post on the [Effective C++11 book](http://scottmeyers.blogspot.co.at/2013/01/effective-c11-content-and-status.html)
- Post on [lambdas](http://blog.feabhas.com/2014/03/demystifying-c-lambdas/)
- Alex Sinyakov's [C++11 cheat sheet](https://isocpp.org/blog/2012/12/c11-a-cheat-sheet-alex-sinyakov)

A never complete list of great C++ references (selected books, etc.):
- Scott Meyers, More Efficient C++ -- 35 New Ways to Improve Your Programs and Designs (mec++, for short), Addison-Wesley Professional Computing Series, 1996.
- Andrew Koenig, Barbara Moo, Ruminations on C++ -- A Decade of Programming Insight and Experience, Addison-Wesley, 1997. (I particulalarly love Chapter 4, Checklist for class authors.)
- Bjarne Stroustrup, The C++ Programming Language - Third Edition, Addison-Wesley, 1997.

### Code analysis
We strive to maintain a certain quality on the code by taking advantage of some tools:
- Cppcheck - A tool for static C/C++ code analysis. Being myself a fan of portable apps, I particularly use the version from [PortableApps.com](http://portableapps.com/apps/development/cppcheck-portable).
- "Analyze > Run Code Analysis on Only Ada-Byron-code-book" when using Microsoft Windows 8.1: Microsoft Visual Studio Community 2015 (Version 14, with solution platform for x64)
- "Product > Analyze" when using Apple OS X: Xcode 6.2 (LLVM, clang++) 64-bit
- (Just starting...) In g++ and clang++, address/thread/memory sanitizer (AKA [ASan](https://code.google.com/p/address-sanitizer/), TSan, MSan)--for example, for Asan, with the flags <code>-fsanitize=address -fno-omit-frame-pointer</code>
- TODO (try this): Cloud-based [Coverity Scan](http://www.coverity.com/products/coverity-scan/) for the Open Source Community

Other tools related to code analysis:
- TODO (try this): [C-Reduce](http://embed.cs.utah.edu/creduce/) _"takes a large C or C++ program that has a property of interest (such as triggering a compiler bug) and automatically produces a much smaller C/C++ program that has the same property."_

### Commits

When committing changes, we use common prefixes--see for example a [list of ITK changes](http://kitware.com/blog/home/post/881). From an [Slicer entry](https://www.slicer.org/slicerWiki/index.php/Documentation/4.1/Developers/Style_Guide#Commit_message_prefix):

| Prefix | What          |
| ------ |:--------------|
| BUG    | a change made to fix a runtime issue (crash, segmentation fault, exception, or incorrect result) |
| COMP   | a fix for a compilation issue (including minor C++ or C++11 improvements), error or warning  |
| ENH    | new functionality added to the project |
| PERF   | a performance improvement |
| STYLE  | a change that does not impact the logic or execution of the code (coding style, comments, doc.) |

Example commit messages:
- Bad: BUG: Check pointer validity before dereferencing -> implementation detail, self-explanatory (by looking at the code)
- Good: BUG: Fix crash in Module X when clicking Apply button
- Bad: ENH: More work in qSlicerXModuleWidget -> more work is too vague, qSlicerXModuleWidget is too low level
- Good: ENH: Add float image outputs in module X
- Bad: COMP: Typo in cmake variable -> implementation detail, self-explanatory
- Good: COMP: Fix compilation error with Numpy on Visual Studio 

### Miscellaneous notes

Advice on **unnecessary comments**:
- Avoid (or remove) unnecessary comments! For example, from C++ Gotchas: Avoiding Common Problems in Coding and Design, by Stephen C. Dewhurst: Gotcha #1: Excessive Commenting: _"If a maintainer has to be reminded of the meaning of the <code>public:</code> label [for example with the comment <code>// Public Interface</code>], you don't want that person maintaining your code."_

Why C++ does not have a **<code>super</code> keyword**, and we do not promote creating any proxy for that:
- See the most voted answer of this [StackOverflow's thread](http://stackoverflow.com/questions/180601/using-super-in-c).

Do not write **<code>using namespace [std]</code>** in header files or before an <code>#include</code>:
- From Programming, Principles and Practice Using C++, by Stroustrup: _"Be restrained in the use or <code>using</code> directives. The notational convenience offered by a <code>using</code> directive is achieved at the cost or potential name clashes. In particular, avoid <code>using</code> directives in header files."_
- From Thinking in C++, 2nd ed. Vol. 1, by Eckel: _"Thus, if you start putting <code>using</code> directives in header files, it’s very easy to end up “turning off” namespaces practically everywhere, and thereby neutralizing the beneficial effects of namespaces.In short: don’t put <code>using</code> directives in header files."_
- From Industrial Strength C++, by Henricson and Nyquist: _"A <code>using</code> declaration or a <code>using</code> directive in the global scope is not recommended inside header files, since it will make names globally accessible to all files that include that header."_
- From C++ Coding Standards: 101 Rules, Guidelines, and Best Practices, by Sutter and Alexandrescu: _"Rule 59: Don't write namespace usings in a header file or before an <code>#include</code>."_

Advices on **Hungarian notation**, from well-known C++ gurus:
- _"Notations that incorporate type information in variable names have mixed utility in type-unsafe languages (notably C), are possible but have no benefits (only drawbacks) in object-oriented languages, and are impossible in generic programming. Therefore, no C++ coding standard should require Hungarian notation, though a C++ coding standard might legitimately choose to ban it."_ (from C++ Coding Standards: 101 Rules, Guidelines, and Best Practices, by Herb Sutter and Andrei Alexandrescu)
- _"Additionally, never attempt to encode a variable's type in its name. For instance, calling an integer index iIndex is actively damaging to understanding and maintaining the code. First, a name should describe a program entity's abstract meaning, not how it's implemented (data abstraction can apply even to predefined types). Second, in the common case that the variable's type changes, just as common is that its name doesn't change in sync. The variable's name then becomes an effective source of misinformation about its type."_ (from C++ Gotchas: Avoiding Common Problems in Coding and Design, by Stephen C. Dewhurst; Gotcha #8: Failure to Distinguish Access and Visibility) 
- Examples: Ditch <code>std::string sName; int iIndex;</code> and write instead <code>std::string name; int index;</code>


- - -

*Note: To render a GitHub webpage containing code with a tab size of 2 spaces, append to its URL "?ts=2"*
