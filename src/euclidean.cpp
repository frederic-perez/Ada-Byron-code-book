#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <numeric>

#include "aux-raw-compiler-warnings-off++begin.h"
// clang-format off
  #include <boost/math/constants/constants.hpp>
// clang-format on
#include "aux-raw-compiler-warnings-off++end.h"

#include "aux-raw.h"
#include "aux-spy.h"
#include "euclidean.h"

namespace ABcb = Ada_Byron_code_book; // Stroustrup C++ PL, p. 179

using ABcb::raw::pad;

template <class T, size_t N>
ABcb::Euclidean::Vector<T, N>::Vector(const T a_value) : d_array()
{
  std::fill(d_array.begin(), d_array.end(), a_value);
}

template <class T, size_t N>
ABcb::Euclidean::Vector<T, N>::Vector(std::initializer_list<T> a_args) : d_array()
{
  // Note: There is a nice discussion in
  // stackoverflow.com/questions/5438671/static-assert-on-initializer-listsize
  // to try to add a static_assert in the ctor, but alas, we did not succeed.
  //
  if (d_array.size() != a_args.size()) { // Verify right size
    std::ostringstream oss;
    oss << __func__ << ": a_args.size()=" << a_args.size() << " does not match N=" << N;
    const std::string what = oss.str();
    throw std::length_error(what);
  }

  size_t i = 0;
  for (auto it = begin(a_args); it != end(a_args); ++it, ++i)
    d_array[i] = *it;
}

// Synonyms: length, magnitude, norm
template <class T, size_t N>
T
ABcb::Euclidean::Vector<T, N>::Norm() const
{
  T accSquared = 0.;
  for (auto value : d_array)
    accSquared += value * value;
  using std::sqrt;
  // '- To avoid "Implicit conversion loses floating-point precision..."
  return sqrt(accSquared);
}

template <class T, size_t N>
T
ABcb::Euclidean::Vector<T, N>::ElementsSum() const
{
  const auto zero = static_cast<T>(0.);
  T acc = std::accumulate(d_array.begin(), d_array.end(), zero);
  return acc;
}

template <class T, size_t N>
T
ABcb::Euclidean::Vector<T, N>::ElementsAvg() const
{
  return ElementsSum() / N;
}

template <class T, size_t N>
auto
ABcb::Euclidean::Vector<T, N>::Normalize() -> const Vector<T, N>&
{
  const T norm = Norm();
  for (T& value : d_array)
    value /= norm;
  return *this;
}

template <class T, size_t N>
auto
ABcb::Euclidean::Vector<T, N>::operator+=(const Vector<T, N>& a_rhs) -> Vector<T, N>&
{
  for (size_t i = 0; i < N; ++i)
    d_array[i] += a_rhs.d_array[i];
  return *this;
}

template <class T, size_t N>
auto
ABcb::Euclidean::Vector<T, N>::operator-=(const Vector<T, N>& a_rhs) -> Vector<T, N>&
{
  for (size_t i = 0; i < N; ++i)
    d_array[i] -= a_rhs.d_array[i];
  return *this;
}

template <class T, size_t N>
auto
ABcb::Euclidean::Vector<T, N>::operator*=(const T a_rhs) -> Vector<T, N>&
{
  for (size_t i = 0; i < N; ++i)
    d_array[i] *= a_rhs;
  return *this;
}

template <class T, size_t N>
auto
ABcb::Euclidean::Vector<T, N>::operator/=(T a_rhs) -> Vector<T, N>&
{
  for (size_t i = 0; i < N; ++i)
    d_array[i] /= a_rhs;
  return *this;
}

template <class T, size_t N>
T ABcb::Euclidean::Vector<T, N>::operator*(const Vector<T, N>& a_rhs) const
{
  T result = 0.;
#undef ADA_BYRON__USE_INNER_PRODUCT_20151215
#if defined(ADA_BYRON__USE_INNER_PRODUCT_20151215)
  std::inner_product(d_array.begin(), d_array.end(), a_rhs.d_array.begin(), result);
  // '- TODO: Debug this (it does not work!)
#else
  for (size_t i = 0; i < N; ++i)
    result += d_array[i] * a_rhs.d_array[i];
#endif
  return result;
}

template <class T, size_t N>
auto
ABcb::Euclidean::Vector<T, N>::operator^(const Vector<T, N>& a_rhs) const -> const Vector<T, N>
{
  static_assert(N == 3, "static_assert failed: Vector template parameter N (size) is not 3.");
  return Vector<T, N>{d_array[1] * a_rhs[2] - d_array[2] * a_rhs[1],
                      d_array[2] * a_rhs[0] - d_array[0] * a_rhs[2],
                      d_array[0] * a_rhs[1] - d_array[1] * a_rhs[0]};
}

template <class T, size_t N>
T
ABcb::Euclidean::Vector<T, N>::ComputeAzimuthAngle() const
{
  static_assert(N == 3, "static_assert failed: Vector template parameter N (size) is not 3.");
#define ADA_BYRON__USEATAN2_20151022
#ifdef ADA_BYRON__USEATAN2_20151022
  using std::atan2;
  // '- To avoid "Implicit conversion loses floating-point precision..."
  T phi = atan2(d_array[1], d_array[0]);
  if (phi < 0.)
    phi += 2. * boost::math::constants::pi<T>();
  return phi;
#else
  // Precondition: v must be a normalized Vector3
  const T sinTheta = sin(acos(d_array[2]));
  if (fabs(sinTheta) < THRESHOLD_SIN_THETA)
    return 0.; // x = y = 0.
  else {
    T phi;
    const T aux = d_array[0] / sinTheta; // to avoid precision problems
    if (aux > 1.)
      phi = 0.;
    else if (aux < -1.)
      phi = boost::math::constants::pi<T>();
    else
      phi = acos(aux);
    return (d_array[1] < 0.) ? -phi : phi;
  }
#endif
}

template <class T, size_t N>
T
ABcb::Euclidean::Vector<T, N>::ComputePolarAngle() const
{
  static_assert(N == 3, "static_assert failed: Vector template parameter N (size) is not 3.");

  //! Precondition: *this must be a normalized Vector<T, N>
  using std::acos;
  // '- To avoid "Implicit conversion loses floating-point precision..."
  return acos(d_array[2]);
  // Equivalent code for this routine:
  // return atan2(sqrt(v.x*v.x+v.y*v.y), v.z);
}

template <class T, size_t N>
auto
ABcb::Euclidean::operator+(const Vector<T, N>& a_lhs, const Vector<T, N>& a_rhs) -> const Vector<T, N>
{
  return Vector<T, N>(a_lhs) += a_rhs;
}

template <class T, size_t N>
auto
ABcb::Euclidean::operator-(const Vector<T, N>& a_lhs, const Vector<T, N>& a_rhs) -> const Vector<T, N>
{
  return Vector<T, N>(a_lhs) -= a_rhs;
}

template <class T, size_t N, class T2>
auto ABcb::Euclidean::operator*(const Vector<T, N>& a_lhs, T2 a_rhs) -> const Vector<T, N>
{
  return Vector<T, N>(a_lhs) *= a_rhs;
}

template <class T, size_t N, class T2>
auto ABcb::Euclidean::operator*(T2 a_lhs, const Vector<T, N>& a_rhs) -> const Vector<T, N>
{
  return Vector<T, N>(a_rhs) *= a_lhs;
}

template <class T, size_t N, class T2>
auto
ABcb::Euclidean::operator/(const Vector<T, N>& a_lhs, T2 a_rhs) -> const Vector<T, N>
{
  return Vector<T, N>(a_lhs) /= a_rhs;
}

template <class T, size_t N, class T2>
auto
ABcb::Euclidean::operator/(T a_lhs, const Vector<T, N>& a_rhs) -> const Vector<T2, N>
{
  return Vector<T, N>(a_rhs) /= a_lhs;
}

namespace {

template <class Vector>
void
DoAndOutputStuff(const Vector& a_vector, const std::string& a_vectorName)
{
  std::cout << pad << a_vectorName << " typeid name = " << typeid(a_vector).name() << '\n'
            << pad << a_vectorName
            << " spy::TypeNameENH of its decltype = " << ABcb::spy::TypeNameENH<decltype(a_vector)>() << '\n'
            << pad << a_vectorName << " = " << a_vector << " | " << a_vectorName << "[0] = " << a_vector[0]
            << " | Norm() = " << a_vector.Norm() << " | ElementsSum() = " << a_vector.ElementsSum()
            << " | ElementsAvg() = " << a_vector.ElementsAvg() << " | /2 = " << a_vector / 2.
            << " | x2 = " << a_vector * 2. << std::endl;
}

} // namespace

void
ABcb::Euclidean::ExamplesOfVector()
{
  std::clog << __func__ << " started..." << std::endl;

#undef ADA_BYRON_CHECK_STATIC_ASSERT_COMPILER_ERROR_20151009
#if defined(ADA_BYRON_CHECK_STATIC_ASSERT_COMPILER_ERROR_20151009)
  using Vector0 = Vector<0>;
  const Vector0 vector0default;
  const Vector0 vector0initializerList{};
#endif

#undef ADA_BYRON_CHECK_STATIC_ASSERT_COMPILER_ERROR_20151210
#if defined(ADA_BYRON_CHECK_STATIC_ASSERT_COMPILER_ERROR_20151210)
  using VectorImpossible = Vector<char, 2>;
  const VectorImpossible vectorImpossible;
#endif

  const Vector2 vector2default;
  DoAndOutputStuff(vector2default, "vector2default");

  const Vector2 vector2ones(1.);
  DoAndOutputStuff(vector2ones, "vector2ones");

  try {
    const Vector2 vector2faulty{1., 2., 3};
    std::cerr << pad << "Error: vector2faulty successfully created (?!)\n";
  } catch (const std::length_error& e) {
    std::cerr << pad << __func__ << ": Error caught (creating vector2faulty): " << e.what() << "\n";
  }

  try {
    const Vector2 vector2{1., 2.};
    std::cout << pad << "vector2 = " << vector2
              << "; "
              // << "vector2[66] = " << vector2[66] << "; " // undefined behavior
              << "vector2.at(66) = " << std::flush;
    std::cout << vector2.at(66) << std::endl;
  } catch (const std::out_of_range& e) {
    std::cerr << pad << __func__ << ": Error caught (access out of range): " << e.what() << '\n';
  }

  const Vector2 vector2{2., 3.};
  DoAndOutputStuff(vector2, "vector2");
  Vector2 vector2Self = vector2; // Copy constructor
  DoAndOutputStuff(vector2Self, "vector2_copy_ctor");
  vector2Self = vector2; // Assignment operator
  DoAndOutputStuff(vector2Self, "vector2_assignment_operator");

  const double dotProduct = vector2 * vector2Self;
  std::cout << pad << "Dot product: " << vector2 << " * " << vector2Self << " = " << dotProduct << std::endl;

  Vector3 vector3a{5., 7., 11.};
  DoAndOutputStuff(vector3a, "vector3a");
  vector3a.Normalize();
  DoAndOutputStuff(vector3a, "vector3a (normalized)");
  std::cout << pad << "vector3a's azimuth angle = " << vector3a.ComputeAzimuthAngle()
            << "; polar angle = " << vector3a.ComputePolarAngle() << std::endl;

  const Vector3 vector3b{-4., -6., -10.};
  DoAndOutputStuff(vector3b, "vector3b");

  const Vector3 vector3plus = vector3a + vector3b;
  DoAndOutputStuff(vector3plus, "vector3plus");

  const Vector3 vector3minus = vector3a - vector3b;
  DoAndOutputStuff(vector3minus, "vector3minus");

  const Vector3 vector3cross = vector3a ^ vector3b;
  DoAndOutputStuff(vector3cross, "vector3cross");

  // Vector3Q

  Vector3Q vector3Qa{5., 7., 11.};
  DoAndOutputStuff(vector3Qa, "vector3Qa");
  vector3Qa *= .5;
  vector3Qa = vector3Qa * 2.; // No need for ... * static_cast<long double>(2.);
  vector3Qa.Normalize();
  DoAndOutputStuff(vector3Qa, "vector3Qa (normalized)");
  std::cout << pad << "vector3Qa's azimuth angle = " << vector3Qa.ComputeAzimuthAngle()
            << "; polar angle = " << vector3Qa.ComputePolarAngle() << std::endl;

  const Vector3Q vector3Qb{-4., -6., -10.};
  DoAndOutputStuff(vector3Qb, "vector3Qb");

  const Vector3Q vector3Qcross = vector3Qa ^ vector3Qb;
  DoAndOutputStuff(vector3Qcross, "vector3Qcross");

  // Vector3HQ

  Vector3HQ vector3HQa{5., 7., 11.};
  DoAndOutputStuff(vector3HQa, "vector3HQa");
  vector3HQa *= .5;
  vector3HQa = vector3HQa * 2.;
  vector3HQa.Normalize();
  DoAndOutputStuff(vector3HQa, "vector3HQa (normalized)");
  std::cout << pad << "vector3HQa's azimuth angle = " << vector3HQa.ComputeAzimuthAngle()
            << "; polar angle = " << vector3HQa.ComputePolarAngle() << std::endl;

  const Vector3HQ vector3HQb{-4., -6., -10.};
  DoAndOutputStuff(vector3HQb, "vector3HQb");

  const Vector3HQ vector3HQcross = vector3HQa ^ vector3HQb;
  DoAndOutputStuff(vector3HQcross, "vector3HQcross");

  std::clog << __func__ << " finished." << std::endl;
}
