// -- Examples on how to use boost::numeric::ublas

#include <iostream>

#include "aux-raw-compiler-warnings-off.h"

	#include <boost/numeric/ublas/io.hpp>
	#include <boost/numeric/ublas/matrix.hpp>
	#include <boost/numeric/ublas/vector.hpp>

#include "aux-raw-compiler-warnings-on.h"

#include "aux-raw.h"
#include "ublas-pool.h"

namespace bnu = boost::numeric::ublas;

namespace {

typedef bnu::fixed_vector<double, 3> VectorD3;
typedef bnu::fixed_matrix<double, 3, 3> MatrixD33;

VectorD3
CrossProduct(const VectorD3& a_v1, const VectorD3& a_v2)
{
	return
		VectorD3(
			VectorD3::array_type{{
				a_v1[1] * a_v2[2] - a_v2[1] * a_v1[2],
				a_v1[2] * a_v2[0] - a_v2[2] * a_v1[0],
				a_v1[0] * a_v2[1] - a_v2[0] * a_v1[1]
			}});
}

const std::string pad = "  ";

double
GetSliceLocation(
	const VectorD3& a_vecX,
	const VectorD3& a_vecY,
	const VectorD3& a_point)
{
	std::cout << pad << __func__ << ": a_vecX = " << a_vecX << '\n';
	std::cout << pad << __func__ << ": a_vecY = " << a_vecY << '\n';
	const VectorD3 vecZ = CrossProduct(a_vecX, a_vecY);
	std::cout << pad << __func__ << ": vecZ = " << vecZ << '\n';

	const MatrixD33 orientation(
		MatrixD33::array_type{ {
			a_vecX[0], a_vecY[0], vecZ[0],
			a_vecX[1], a_vecY[1], vecZ[1],
			a_vecX[2], a_vecY[2], vecZ[2] } });

	std::cout << pad << __func__ << ": orientation = " << orientation << '\n';
	
	const VectorD3 result = prod(a_point, orientation);
	std::cout << pad << __func__ << ": result = " << result << '\n';

	return result[2];
}

} // namespace

void
Ada_Byron_code_book::ExamplesOfUblas()
{
	std::clog << __func__ << " started..." << std::endl;
	
	// Simple example
	GetSliceLocation(
		VectorD3::array_type{ { 1., 0., 0. } },
		VectorD3::array_type{ { 0., 0., -1. } },
		VectorD3::array_type{ { -105.80165, -201.29752, 227.30165 } });
	
	// A more difficult example
	GetSliceLocation(
		VectorD3::array_type{ { 1., 0., 0. } },
		VectorD3::array_type{ { 0., -0.033155151, -0.99945021 } },
		VectorD3::array_type{ { -95.202782, -71.037422, 206.67741 } });

	std::clog << __func__ << " finished." << std::endl;
}

// -- eof
