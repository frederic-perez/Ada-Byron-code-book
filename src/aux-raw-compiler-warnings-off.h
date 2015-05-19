// -- 

// Note: Do not even think about doing
// #pragma once
// since we want these preprocessor command to be included in <<every>> client
// file that does include this file.

// Companion file to ...-off.h is ...-on.h
//
// Right usage of these headers
// ============================
// #include <aux-raw-compiler-warnings-off.h>
//   #include ...
// #include <aux-raw-compiler-warnings-on.h>
//
// Wrong usage of these headers
// ============================
// #include <aux-raw-compiler-warnings-on.h>
//   #include ...
// #include <aux-raw-compiler-warnings-off.h>

// Stuff to forbid a bad usage of these headers
//
#define AuxRawCompilerWarningsOff

#if defined(__GNUC__)
	// See http://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
	// Further reading:
	// - https://svn.boost.org/trac/boost/wiki/Guidelines/WarningsGuidelines
	#pragma GCC diagnostic ignored "-Wcast-qual"
	#pragma GCC diagnostic ignored "-Wconversion"
	#pragma GCC diagnostic ignored "-Wfloat-equal"
	#pragma GCC diagnostic ignored "-Wignored-qualifiers"
	#pragma GCC diagnostic ignored "-Wredundant-decls"
	#pragma GCC diagnostic ignored "-Wshadow"
	#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
	#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

#if defined(_MSC_VER)
	#pragma warning(push)
	#pragma warning(disable : 4127)
	#pragma warning(disable : 4244)
	#pragma warning(disable : 4251)
	#pragma warning(disable : 4275)
	#pragma warning(disable : 4310)
	#pragma warning(disable : 4503)
	#pragma warning(disable : 4512)
	#pragma warning(disable : 4616)
	#pragma warning(disable : 4701)
	#pragma warning(disable : 4800)
	#pragma warning(disable : 4913)
	#pragma warning(disable : 4996)
#endif

// -- eof
