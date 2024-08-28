// -- Examples on how to use boost::numeric::ublas

#include "aux-raw-compiler-warnings-off++begin.hpp"
// clang-format off
  #include <boost/numeric/ublas/io.hpp>
  #include <boost/numeric/ublas/matrix.hpp>
  #include <boost/numeric/ublas/vector.hpp>
// clang-format on
#include "aux-raw-compiler-warnings-off++end.hpp"

#include "aux-raw.hpp"
#include "log.hpp"
#include "ublas-pool.hpp"

namespace ABcb = Ada_Byron_code_book;
using ABcb::raw::pad;

namespace bnu = boost::numeric::ublas;

namespace {

using VectorD3 = bnu::fixed_vector<double, 3>;
using MatrixD33 = bnu::fixed_matrix<double, 3, 3>;

#if defined(_MSC_VER) && (_MSC_VER >= 1930)
VectorD3
operator^(const VectorD3& a_lhs, const VectorD3& a_rhs)
{
  return VectorD3{
    a_lhs[1] * a_rhs[2] - a_rhs[1] * a_lhs[2],
    a_lhs[2] * a_rhs[0] - a_rhs[2] * a_lhs[0],
    a_lhs[0] * a_rhs[1] - a_rhs[0] * a_lhs[1]};
}
#else
VectorD3
operator^(const VectorD3& a_lhs, const VectorD3& a_rhs)
{
  return VectorD3::array_type{
    a_lhs[1] * a_rhs[2] - a_rhs[1] * a_lhs[2],
    a_lhs[2] * a_rhs[0] - a_rhs[2] * a_lhs[0],
    a_lhs[0] * a_rhs[1] - a_rhs[0] * a_lhs[1]};
}
#endif

double
GetSliceLocation(const VectorD3& a_vecX, const VectorD3& a_vecY, const VectorD3& a_point)
{
  B_LOG_INFO << pad << __func__ << ": a_vecX = " << a_vecX;
  B_LOG_INFO << pad << __func__ << ": a_vecY = " << a_vecY;
#if defined(_MSC_VER) && (_MSC_VER >= 1900)
  B_LOG_INFO << pad << __func__ << ": a_point = " << a_point;
  return 666.; // TODO
#else
  const VectorD3 vecZ = a_vecX ^ a_vecY;
  B_LOG_INFO << pad << __func__ << ": vecZ = " << vecZ;

  const MatrixD33 orientation(MatrixD33::array_type{
    a_vecX[0], a_vecY[0], vecZ[0], a_vecX[1], a_vecY[1], vecZ[1], a_vecX[2], a_vecY[2], vecZ[2]});

  B_LOG_INFO << pad << __func__ << ": orientation = " << orientation;

#  if defined(_MSC_VER)
  const auto resultTmp2 = prod(a_point, orientation);
  const VectorD3::array_type resultAT{resultTmp2(0), resultTmp2(1), resultTmp2(2)};
  const VectorD3 result{resultAT}
#  else
  const VectorD3 result = prod(a_point, orientation);
#  endif
  B_LOG_INFO << pad << __func__ << ": result = " << result;

  return result[2];
#endif
}

} // namespace

void
ABcb::ExamplesOfUblas()
{
  B_LOG_TRACE_STARTED

  // Simple example
#if defined(_MSC_VER)
  const VectorD3::array_type p1{1., 0., 0.};
  const VectorD3::array_type p2{0., 0., -1.};
  const VectorD3::array_type p3{-105.80165, -201.29752, 227.30165};
  GetSliceLocation(p1, p2, p3);
#else
  GetSliceLocation(
    VectorD3::array_type{1., 0., 0.},
    VectorD3::array_type{0., 0., -1.},
    VectorD3::array_type{-105.80165, -201.29752, 227.30165});
#endif

  // A more difficult example
#if defined(_MSC_VER)
  const VectorD3::array_type p4{1., 0., 0.};
  const VectorD3::array_type p5{0., -0.033155151, -0.99945021};
  const VectorD3::array_type p6{-95.202782, -71.037422, 206.67741};
  GetSliceLocation(p4, p5, p6);
#else
  GetSliceLocation(
    VectorD3::array_type{1., 0., 0.},
    VectorD3::array_type{0., -0.033155151, -0.99945021},
    VectorD3::array_type{-95.202782, -71.037422, 206.67741});
#endif

  B_LOG_TRACE_FINISHED
}
