#pragma once

// TODO: Move #includes to .cpp
// TODO: Study #include <type_traits> possibilities

#include <sstream>
#include <type_traits>
#include <vector>

#include "aux-raw-compiler-warnings-off++begin.hpp"
// clang-format off
  #include <boost/algorithm/string.hpp>
  #include <boost/multiprecision/cpp_dec_float.hpp>
// clang-format on
#include "aux-raw-compiler-warnings-off++end.hpp"

namespace Ada_Byron_code_book::Euclidean {

void ExamplesOfVector();

template <class T, size_t N>
class Vector {
  static_assert(
    N > 0,
    "Vector template parameter N (size) is 0. It should be strictly positive.");
  static_assert(
    // std::is_floating_point<T>::value,
    // '- Oops! Alas, this assert does not work when instantiating
    //    T with boost::multiprecision::cpp_dec_float_50
    //    so we use the expression below, found on the Internet
    //    (it catches attempts of instantiating T as a char, for example)
    false == std::numeric_limits<T>::is_integer,
    "Vector template parameter T is not floating point");

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

  template <class t, size_t n>
  friend std::ostream& operator<<(std::ostream&, const Vector<t, n>&);

private:
  std::array<T, N> d_array;
};

template <class T, size_t N>
const Vector<T, N> operator+(const Vector<T, N>& a_lhs, const Vector<T, N>& a_rhs);

template <class T, size_t N>
const Vector<T, N> operator-(const Vector<T, N>& a_lhs, const Vector<T, N>& a_rhs);

template <class T, size_t N, class T2>
const Vector<T, N> operator*(const Vector<T, N>& a_lhs, T2 a_rhs);

template <class T, size_t N, class T2>
const Vector<T, N> operator*(T2 a_lhs, const Vector<T, N>& a_rhs);

template <class T, size_t N, class T2>
const Vector<T, N> operator/(const Vector<T, N>& a_lhs, T2 a_rhs);

template <class T, size_t N, class T2>
const Vector<T2, N> operator/(T a_lhs, const Vector<T, N>& a_rhs);

// TODO: Move the definition below to .cpp

template <class T, size_t N>
std::ostream&
operator<<(std::ostream& a_os, const Vector<T, N>& a_vector)
{
  // 1st, the size of the Vector
  //
  a_os << '[' << a_vector.d_array.size() << ']';

  // 2nd, its actual contents
  //
  std::ostringstream oss;
  oss << std::setprecision(std::numeric_limits<T>::digits10);
  std::vector<std::string> valuesAsStrings;
  for (auto value : a_vector.d_array) {
    oss << value;
    valuesAsStrings.push_back(oss.str());
    // '- Note: We do not use valuesAsStrings.push_back(std::to_string(value));
    //    because std::to_string(double) outputs six decimal digits
    //    and we want no decimal digits whenever possible.
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

} // namespace Ada_Byron_code_book::Euclidean
