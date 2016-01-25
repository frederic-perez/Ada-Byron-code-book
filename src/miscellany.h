// -- 

#pragma once

namespace Ada_Byron_code_book {

namespace miscellany {

void ExampleOfRawStringLiteral();

// See Herb Sutter, Andrei Alexandrescu, C++ Coding Standards: 101 Rules, 
// Guidelines, and Best Practices, Addison Wesley Professional, 2004,
// Chapter 15, Use const proactively (particularly, the Examples section)
//
void Function(int);
// void Function(const int); // redeclares the same: top-level const ignored

// Factorial stuff based on 
// http://stackoverflow.com/questions/5721796/
// how-do-you-implement-the-factorial-function-in-c
//

template<size_t N>
class FactorialCompileTime
{
public:
	enum : size_t { d_value = N * FactorialCompileTime<N - 1>::d_value };
};

template<>
class FactorialCompileTime<0>
{
public:
	enum : size_t { d_value = 1 };
};

size_t FactorialRecursive(size_t); 
size_t FactorialIterative(size_t);

void ExamplesOfFactorial();

void ExamplesOfMultiprecision();

} // namespace miscellany

} // namespace Ada_Byron_code_book

// -- eof
