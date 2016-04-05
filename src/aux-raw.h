// -- 

#pragma once
// '- This pragma works for
// - Windows 8.1:
//   - Visual Studio 2013 (vs12)
// - Ubuntu (virtual machine):
//   - g++ 4.8.2
//   - clang++ 3.4-1ubuntu3 (based on LLVM 3.4)
// - Apple OS X Yosemite
//   - Xcode 6.1 with Apple LLVM 6.0 (clang-600.0.54) (based on LLVM 3.5svn)

#include <string>

//! Unfortulately __func__ is not known by vs12, vs14.
//! This is a workaround:
#ifndef __func__
#define __func__ __FUNCTION__
#endif

namespace Ada_Byron_code_book {

namespace raw {

// Note: Recall that for std::array<> objects you must use the size() inspector
//
template<typename T, size_t N>
size_t
ArraySize(const T(&)[N])
{	return N; }

template<typename T>
void
WipeOut(T& a_t)
{
	a_t.clear();
	T().swap(a_t);
}

char
SystemSlash();

void ExamplesOfRaw();

const std::string pad = "  ";

} // namespace raw

} // namespace Ada_Byron_code_book

// -- eof
