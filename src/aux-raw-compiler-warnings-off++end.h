//! IMPORTANT: See notes in the companion header file ...-off++begin.h
//!            (They are not replicated here for maintenance reasons.)

// Stuff to forbid a bad usage of these headers
//
#if !defined(AuxRawCompilerWarningsOffBegin)
#  error File ...++begin.h has to be included BEFORE the ...++end.h file
#else
#  undef AuxRawCompilerWarningsOffBegin
#endif

#if defined(__GNUC__)
// See http://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
// Further reading:
// - https://svn.boost.org/trac/boost/wiki/Guidelines/WarningsGuidelines
#  pragma GCC diagnostic warning "-Wcast-qual"
#  pragma GCC diagnostic warning "-Wconversion"
#  pragma GCC diagnostic warning "-Wfloat-equal"
#  pragma GCC diagnostic warning "-Wignored-qualifiers"
#  pragma GCC diagnostic warning "-Wredundant-decls"
#  pragma GCC diagnostic warning "-Wshadow"
#  if !defined(__clang__)
#    pragma GCC diagnostic warning "-Wunused-local-typedefs"
#  endif
#  pragma GCC diagnostic warning "-Wunused-variable"
#endif

#if defined(_MSC_VER)
#  pragma warning(pop)
#endif
