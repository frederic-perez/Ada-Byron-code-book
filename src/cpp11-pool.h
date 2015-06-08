// -- Examples on how to use some C++11 functionalities

#pragma once

#include <string>

namespace Ada_Byron_code_book {

namespace cpp11 {

void TryBadCode();
void TestIfAConstParameterCanBeModified(const int);
void UsingTuple();
void AlgorithmExamples();
void MiscellanyExamples();

// Variadic template and related basic template

template<typename T>
void
PrintList(T a_last)
{	std::cout << a_last << std::endl; }

template<typename Arg1, typename... Args>
void
PrintList(Arg1 a_first, Args... a_rest)
{
	std::cout << a_first << ", ";
	PrintList(a_rest...);
}

} // namespace cpp11

} // namespace Ada_Byron_code_book

// -- eof
