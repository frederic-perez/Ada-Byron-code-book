#ifndef ADA_BYRON_CODE_BOOK__LITERAL_OPERATORS_HPP
#define ADA_BYRON_CODE_BOOK__LITERAL_OPERATORS_HPP

namespace Ada_Byron_code_book::literal_operators {

void Examples();

// Specifying unsigned char values as literals in the code:
// From https://stackoverflow.com/questions/2304732/how-do-i-specify-an-integer-literal-of-type-unsigned-char-in-c
// C++11 introduced user defined literals. It can be used like this:
constexpr unsigned char operator"" _uchar(unsigned long long arg) noexcept
{
  return static_cast<unsigned char>(arg);
}

} // namespace Ada_Byron_code_book::literal_operators

#endif // ADA_BYRON_CODE_BOOK__LITERAL_OPERATORS_HPP
