#ifndef ADA_BYRON_CODE_BOOK__AUX_RAW_HPP
#define ADA_BYRON_CODE_BOOK__AUX_RAW_HPP

#include <string>

//! Unfortulately __func__ is not known by vs12, vs14.
//! This is a workaround:
#ifndef __func__
#  define __func__ __FUNCTION__
#endif

namespace Ada_Byron_code_book::raw {

// Note: Recall that for std::array objects you must use the size() inspector
//
template <typename T, size_t N>
constexpr
auto
ArraySize(const T (&)[N])
-> size_t
{
  return N;
}

template <typename T>
void
WipeOut(T& a_t)
{
  a_t.clear();
  T().swap(a_t);
}

constexpr
auto
SystemSlash()
-> char
{
#if defined(__CYGWIN__) || defined(__GNUC__)
  return '/';
#else
  return '\\';
#endif
}

std::string RandomString(size_t length);

void ExamplesOfRaw();

const std::string pad = "  ";
const auto pad2x = pad + pad;

} // namespace Ada_Byron_code_book::raw

#endif // ADA_BYRON_CODE_BOOK__AUX_RAW_HPP
