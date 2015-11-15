// -- 

#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <sstream>
#include <type_traits>
#include <vector>

#include "aux-raw-compiler-warnings-off++begin.h"

	#include <boost/algorithm/string.hpp>
	#include <boost/math/constants/constants.hpp>

#include "aux-raw-compiler-warnings-off++end.h"

namespace Ada_Byron_code_book {

namespace Euclidean {

void ExamplesOfVector();

template<size_t N>
class Vector {

	static_assert(
		N > 0,
		"static_assert failed: Vector template parameter N (size) is 0. "
		"It should be strictly positive.");
	static_assert(
		std::is_floating_point<double>::value,
		"static_assert failed: Vector template parameter T is not floating point");

public:
	explicit Vector(double); // All elements will be set the input argument
	Vector() : Vector(0.) {} // Delegating constructor
	explicit Vector(std::initializer_list<double>);

	// Note: 
	// Copy constructor and assignment operator are automatically (silently)
	// created.

	double operator[](size_t a_idx) const { return d_array[a_idx]; }
	double& operator[](size_t a_idx) { return d_array[a_idx]; }

	double Norm() const; // Synonyms: length, magnitude, norm
	double ElementsSum() const;
	double ElementsAvg() const;

	const Vector& Normalize();

	// Note: Here we follow the advice of Scott Meyers, More Effective C++
	// (mec++), Item 22, Consider using op= instead of stand-alone op
	//
	Vector& operator+=(const Vector&);
	Vector& operator-=(const Vector&);
	Vector& operator*=(double);
	Vector& operator/=(double);

	double ComputeAzimuthAngle() const; // Only for N==3
	double ComputePolarAngle() const; // Only for N==3; Precondition: Normalized
	const Vector operator^(const Vector&) const; // Only for N==3

	template<size_t n>
	friend std::ostream& operator<<(std::ostream&, const Vector<n>&);

private:
	std::array<double, N> d_array;
};

template<size_t N>
Vector<N>::Vector(double a_value)
: d_array()
{
	for (auto& value : d_array)
		value = a_value;
}

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
double
Vector<N>::Norm() const // Synonyms: length, magnitude, norm
{
	double accSquared = 0.;
	for (auto value : d_array)
		accSquared += value*value;
	return sqrt(accSquared);
}

template<size_t N>
double
Vector<N>::ElementsSum() const
{
	double acc = 0.;
	for (auto value : d_array)
		acc += value;
	return acc;
}

template<size_t N>
double
Vector<N>::ElementsAvg() const
{	return ElementsSum()/N; }

template<size_t N>
const Vector<N>&
Vector<N>::Normalize()
{
	const double norm = Norm();
	for (double& value : d_array)
		value /= norm;
	return *this;
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
Vector<N>&
Vector<N>::operator/=(double a_rhs)
{
	for (size_t i = 0; i < N; ++i)
		d_array[i] /= a_rhs;
	return *this;
}

template<size_t N>
double
Vector<N>::ComputeAzimuthAngle() const
{
	static_assert(
		N == 3,
		"static_assert failed: Vector template parameter N (size) is not 3.");
#define ADA_BYRON__USEATAN2_20151022
#ifdef ADA_BYRON__USEATAN2_20151022
	double phi = atan2(d_array[1], d_array[0]);
	if (phi < 0.)
		phi += 2. * boost::math::constants::pi<double>();
	return phi;
#else
	// Precondition: v must be a normalized Vector3
	const double sinTheta = sin(acos(d_array[2]));
	if (fabs(sinTheta)<THRESHOLD_SIN_THETA)
		return 0.; // x = y = 0.
	else {
		double phi;
		const double aux = d_array[0] / sinTheta; // to avoid precision problems
		if (aux>1.) phi = 0.;
		else if (aux<-1.) phi = boost::math::constants::pi<double>();
		else phi = acos(aux);
		return (d_array[1]<0.) ? -phi : phi;
	}
#endif
}

template<size_t N>
double
Vector<N>::ComputePolarAngle() const
{
	static_assert(
		N == 3,
		"static_assert failed: Vector template parameter N (size) is not 3.");

	//! Precondition: *this must be a normalized Vector<N>
	return acos(d_array[2]);
	// Equivalent code for this routine:
	// return atan2(sqrt(v.x*v.x+v.y*v.y), v.z);
}

template<size_t N>
const Vector<N>
Vector<N>::operator^(const Vector<N>& a_rhs) const
{
	static_assert(
		N == 3,
		"static_assert failed: Vector template parameter N (size) is not 3.");
	return
		Vector<N>{
			d_array[1] * a_rhs[2] - d_array[2] * a_rhs[1],
			d_array[2] * a_rhs[0] - d_array[0] * a_rhs[2],
			d_array[0] * a_rhs[1] - d_array[1] * a_rhs[0]};
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
const Vector<N>
operator/(const Vector<N>& a_lhs, double a_rhs)
{
	return Vector<N>(a_lhs) /= a_rhs;
}

template<size_t N>
const Vector<N>
operator/(double a_lhs, const Vector<N>& a_rhs)
{
	return Vector<N>(a_rhs) /= a_lhs;
}
	
template<size_t N>
std::ostream&
operator<<(std::ostream& a_os, const Vector<N>& a_vector)
{
	// 1st, the size of the Vector
	//
	a_os << '[' << a_vector.d_array.size() << ']';

	// 2nd, its actual contents
	//
	std::ostringstream oss; // TODO: Simplify, ditching oss
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
