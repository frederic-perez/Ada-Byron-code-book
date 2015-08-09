// -- 

#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

#include "aux-raw-compiler-warnings-off.h"

	#include <boost/algorithm/string.hpp>

#include "aux-raw-compiler-warnings-on.h"

namespace Ada_Byron_code_book {

namespace Euclidean {

void ExamplesOfVector();

template<size_t N>
class Vector {
public:
	explicit Vector(std::initializer_list<double>);

	double operator[](size_t a_idx) const { return d_array[a_idx]; }
	double& operator[](size_t a_idx) { return d_array[a_idx]; }

	// Note: Here we follow the advice of Scott Meyers, More Effective C++ (mec++), Item 22, Consider using op= instead of stand-alone op
	Vector& operator+=(const Vector&);
	Vector& operator-=(const Vector&);
	Vector& operator*=(double);

	double Norm() const; // Synonyms: length, magnitude, norm

	template<size_t n>
	friend std::ostream& operator<<(std::ostream&, const Vector<n>&);

private:
	std::array<double, N> d_array;
};

template<size_t N>
Vector<N>::Vector(std::initializer_list<double> a_args)
	: d_array()
{
	// Note: There is a nice discussion in
	// stackoverflow.com/questions/5438671/static-assert-on-initializer-listsize
	// to try to add a static_assert in the ctor, but alas, we did not succeed.
	//
	if (d_array.size() != a_args.size()) { // Verify right size
		std::ostringstream oss;
		oss << __func__ << ": a_args.size()=" << a_args.size()
			<< " does not match N=" << N;
		const std::string what = oss.str();
		throw std::length_error(what);
	}

	size_t i = 0;
	for (auto it = begin(a_args); it != end(a_args); ++it, ++i)
		d_array[i] = *it;
}

template<size_t N>
Vector<N>&
Vector<N>::operator+=(const Vector<N>& a_rhs)
{
	for (size_t i = 0; i < N; ++i)
		d_array[i] += a_rhs.d_array[i];
	return *this;
}

template<size_t N>
Vector<N>&
Vector<N>::operator-=(const Vector<N>& a_rhs)
{
	for (size_t i = 0; i < N; ++i)
		d_array[i] -= a_rhs.d_array[i];
	return *this;
}

template<size_t N>
Vector<N>&
Vector<N>::operator*=(double a_rhs)
{
	for (size_t i = 0; i < N; ++i)
		d_array[i] *= a_rhs;
	return *this;
}

template<size_t N>
double
Vector<N>::Norm() const // Synonyms: length, magnitude, norm
{
	double accSquared = 0.;
	for (auto value : d_array)
		accSquared += value*value;
	return sqrt(accSquared);
}

template<size_t N>
const Vector<N>
operator+(const Vector<N>& a_lhs, const Vector<N>& a_rhs)
{
	return Vector<N>(a_lhs) += a_rhs;
}

template<size_t N>
const Vector<N>
operator-(const Vector<N>& a_lhs, const Vector<N>& a_rhs)
{
	return Vector<N>(a_lhs) -= a_rhs;
}

template<size_t N>
const Vector<N>
operator*(const Vector<N>& a_lhs, double a_rhs)
{
	return Vector<N>(a_lhs) *= a_rhs;
}

template<size_t N>
const Vector<N>
operator*(double a_lhs, const Vector<N>& a_rhs)
{
	return Vector<N>(a_rhs) *= a_lhs;
}

template<size_t N>
std::ostream&
operator<<(std::ostream& a_os, const Vector<N>& a_vector)
{
	// 1st, the size of the Point
	//
	a_os << '[' << a_vector.d_array.size() << ']';

	// 2nd, the actual contents
	//
	std::ostringstream oss;
	std::vector<std::string> valuesAsStrings;
	for (auto value : a_vector.d_array) {
		oss << value;
		valuesAsStrings.push_back(oss.str());
		oss.str("");
	}
	oss << '(' << boost::algorithm::join(valuesAsStrings, ", ") << ')';
	a_os << oss.str();

	return a_os;
}

using Vector2 = Vector<2>;
using Vector3 = Vector<3>;

} // namespace Euclidean

} // namespace Ada_Byron_code_book

// -- eof
