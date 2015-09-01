// --

// IMPORTANT: See notes in the companion header file ...-off.h
//            (They are not replicated here for maintenance reasons.)

// Stuff to forbid a bad usage of these headers
//
#if !defined(AuxRawCompilerWarningsOff)
	#error AuxRawCompilerWarningsOff.h has to be included BEFORE the ...on.h file
#else
	#undef AuxRawCompilerWarningsOff
#endif

// TODO: In order to make the use of the coupled headers less error prone, rename them to ..--begin.h and end.h. This simple policy allows quick inspection of their correctly sorted usage by searching for the string " aux-raw-warnings-control--."

#if defined(__GNUC__)
	// See http://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
	// Further reading:
	// - https://svn.boost.org/trac/boost/wiki/Guidelines/WarningsGuidelines
	#pragma GCC diagnostic warning "-Wcast-qual"
	#pragma GCC diagnostic warning "-Wconversion"
	#pragma GCC diagnostic warning "-Wfloat-equal"
	#pragma GCC diagnostic warning "-Wignored-qualifiers"
	#pragma GCC diagnostic warning "-Wredundant-decls"
	#pragma GCC diagnostic warning "-Wshadow"
#if !defined(__clang__)
	#pragma GCC diagnostic warning "-Wunused-local-typedefs"
#endif
	#pragma GCC diagnostic warning "-Wunused-variable"
#endif

#if defined(_MSC_VER)
	#pragma warning(pop)
#endif

// -- eof
