// -- 

// TODO: Add definitions to .cpp as Roberto did elsewhere. Try one first!

#pragma once

// TODO: Move #includes to .cpp

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <numeric>
#include <sstream>
#include <type_traits>
#include <vector>

#include "aux-raw-compiler-warnings-off++begin.h"

	#include <boost/algorithm/string.hpp>
	#include <boost/math/constants/constants.hpp>
	#include <boost/multiprecision/cpp_dec_float.hpp>

#include "aux-raw-compiler-warnings-off++end.h"

namespace Ada_Byron_code_book {

namespace Euclidean {

void ExamplesOfVector();

template<class T, size_t N>
class Vector {

	static_assert(
		N > 0,
		"static_assert failed: Vector template parameter N (size) is 0. "
		"It should be strictly positive.");
	static_assert(
		// std::is_floating_point<T>::value,
		//	'- Oops! Alas, this assert does not work with
		//		 boost::multiprecision::cpp_dec_float_50
		//		 so we use the expression below, found in the Internet
		//		 (it catches attempts of instantiating T as a char, for example)
		false == std::numeric_limits<T>::is_integer,
		"static_assert failed: Vector template parameter T is not floating point");

public:
	explicit Vector(T); // All elements will be set the input argument
	Vector() : Vector(0.) {} // Delegating constructor
	explicit Vector(std::initializer_list<T>);

	// Note: 
	// Copy constructor and assignment operator are automatically (silently)
	// created.

	T operator[](size_t a_idx) const { return d_array[a_idx]; }
	T& operator[](size_t a_idx) { return d_array[a_idx]; }
	T at(size_t a_idx) const { return d_array.at(a_idx); }
	T& at(size_t a_idx) { return d_array.at(a_idx); }

	T Norm() const; // Synonyms: length, magnitude, norm
	T ElementsSum() const;
	T ElementsAvg() const;

	const Vector& Normalize();

	// Note: Here we follow the advice of Scott Meyers, More Effective C++
	// (mec++), Item 22, Consider using op= instead of stand-alone op
	//
	Vector& operator+=(const Vector&);
	Vector& operator-=(const Vector&);
	Vector& operator*=(T);
	Vector& operator/=(T);

	T operator*(const Vector&) const; // Scalar product
	const Vector operator^(const Vector&) const; // Only for N==3

	T ComputeAzimuthAngle() const; // Only for N==3
	T ComputePolarAngle() const; // Only for N==3; Precondition: Normalized

	template<class t, size_t n>
	friend std::ostream& operator<<(std::ostream&, const Vector<t, n>&);

private:
	std::array<T, N> d_array;
};

template<class T, size_t N>
T
Vector<T, N>::operator*(const Vector<T, N>& a_rhs) const
{
	T result = 0.;
#undef ADA_BYRON__USE_INNER_PRODUCT_20151215
#if defined(ADA_BYRON__USE_INNER_PRODUCT_20151215)
	std::inner_product(
		d_array.begin(), d_array.end(), a_rhs.d_array.begin(), result);
	// '- TODO: Debug this (it does not work!)
#else
	for (size_t i = 0; i < N; ++i)
		result += d_array[i] * a_rhs.d_array[i];
#endif
	return result;
}

template<class T, size_t N>
const Vector<T, N>
Vector<T, N>::operator^(const Vector<T, N>& a_rhs) const
{
	static_assert(
		N == 3,
		"static_assert failed: Vector template parameter N (size) is not 3.");
	return
		Vector<T, N>{
			d_array[1] * a_rhs[2] - d_array[2] * a_rhs[1],
			d_array[2] * a_rhs[0] - d_array[0] * a_rhs[2],
			d_array[0] * a_rhs[1] - d_array[1] * a_rhs[0]};
}

template<class T, size_t N>
const Vector<T, N>
operator+(const Vector<T, N>& a_lhs, const Vector<T, N>& a_rhs)
{
	return Vector<T, N>(a_lhs) += a_rhs;
}

template<class T, size_t N>
const Vector<T, N>
operator-(const Vector<T, N>& a_lhs, const Vector<T, N>& a_rhs)
{
	return Vector<T, N>(a_lhs) -= a_rhs;
}

template<class T, size_t N, class T2>
const Vector<T, N>
operator*(const Vector<T, N>& a_lhs, T2 a_rhs)
{
	return Vector<T, N>(a_lhs) *= a_rhs;
}

template<class T, size_t N, class T2>
const Vector<T, N>
operator*(T2 a_lhs, const Vector<T, N>& a_rhs)
{
	return Vector<T, N>(a_rhs) *= a_lhs;
}

template<class T, size_t N, class T2>
const Vector<T, N>
operator/(const Vector<T, N>& a_lhs, T2 a_rhs)
{
	return Vector<T, N>(a_lhs) /= a_rhs;
}

template<class T, size_t N, class T2>
const Vector<T2, N>
operator/(T a_lhs, const Vector<T, N>& a_rhs)
{
	return Vector<T, N>(a_rhs) /= a_lhs;
}
	
template<class T, size_t N>
std::ostream&
operator<<(std::ostream& a_os, const Vector<T, N>& a_vector)
{
	// 1st, the size of the Vector
	//
	a_os << '[' << a_vector.d_array.size() << ']';

	// 2nd, its actual contents
	//
	std::ostringstream oss;
	std::vector<std::string> valuesAsStrings;
	for (auto value : a_vector.d_array) {
		oss << value;
		valuesAsStrings.push_back(oss.str());
		// '- Note: We do not use
		//			valuesAsStrings.push_back(std::to_string(value));
		//		because std::to_string(double) outputs six decimal digits
		//		and we want no decimal digits whenever possible.
		oss.str("");
	}
	oss << '(' << boost::algorithm::join(valuesAsStrings, ", ") << ')';
	a_os << oss.str();

	return a_os;
}

using Vector2 = Vector<double, 2>;
using Vector3 = Vector<double, 3>;
using Vector3Q = Vector<long double, 3>;
using Vector3HQ = Vector<boost::multiprecision::cpp_dec_float_50, 3>;

} // namespace Euclidean

} // namespace Ada_Byron_code_book

// -- eof
