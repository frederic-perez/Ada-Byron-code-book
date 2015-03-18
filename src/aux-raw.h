// -- 

#pragma once
// '- This pragma works for
// - Windows 8.1:
// - Visual Studio 2013 (vs12)
// - Ubuntu (virtual machine):
// - g++ 4.8.2
// - clang++ 3.4-1ubuntu3 (based on LLVM 3.4)
// - Apple OS X Yosemite
// - Xcode 6.1 with Apple LLVM 6.0 (clang-600.0.54) (based on LLVM 3.5svn)

// Unfortulately __func__ is not understood by vs12. This is a workaround:
#ifndef __func__
#define __func__ __FUNCTION__
#endif

// -- eof
