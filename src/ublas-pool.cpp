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

typedef bnu::vector<double, std::array<double, 3>> VectorD3;
typedef bnu::matrix<double, bnu::row_major, std::array<double, 4>> MatrixD3;

VectorD3
CrossProduct(const VectorD3& a_v1, const VectorD3& a_v2)
{
	return
		VectorD3({
			a_v1[1] * a_v2[2] - a_v2[1] * a_v1[2],
			a_v1[2] * a_v2[0] - a_v2[2] * a_v1[0],
			a_v1[0] * a_v2[1] - a_v2[0] * a_v1[1]
		});
}

const std::string pad = "  ";

double
GetSliceLocation()
{
	const VectorD3 vector_x({ 1., 2., 3. });
	const VectorD3 vector_y({ 4., 5., 6. });

	std::cout << pad << __func__ << ": vector_x = " << vector_x << '\n';
	std::cout << pad << __func__ << ": vector_y = " << vector_y << '\n';
	const VectorD3 vector_z = CrossProduct(vector_x, vector_y);
	std::cout << pad << __func__ << ": vector_z = " << vector_z << '\n';

	bnu::matrix<double> orientation(4, 4);

	orientation.at_element(0, 0) = vector_x[0];
	orientation.at_element(1, 0) = vector_x[1];
	orientation.at_element(2, 0) = vector_x[2];
	orientation.at_element(3, 0) = 0.;

	orientation.at_element(0, 1) = vector_y[0];
	orientation.at_element(1, 1) = vector_y[1];
	orientation.at_element(2, 1) = vector_y[2];
	orientation.at_element(3, 1) = 0.;

	orientation.at_element(0, 2) = vector_z[0];
	orientation.at_element(1, 2) = vector_z[1];
	orientation.at_element(2, 2) = vector_z[2];
	orientation.at_element(3, 2) = 0.;

	orientation.at_element(0, 3) = 0.;
	orientation.at_element(1, 3) = 0.;
	orientation.at_element(2, 3) = 0.;
	orientation.at_element(3, 3) = 1.;

	std::cout << pad << __func__ << ": orientation = " << orientation << '\n';
	
	const VectorD3 imagePos({ 1., 1., 1. });
	const bnu::vector<double> result = prod(orientation, imagePos);
	std::cout << pad << __func__ << ": result = " << result << '\n';

	return result[2];
}

} // namespace

void
Ada_Byron_code_book::ExamplesOfUblas()
{
	std::clog << __func__ << " started..." << std::endl;

	const double location = GetSliceLocation();
	std::cout << pad << __func__ << ": location = " << location << std::endl;

	std::clog << __func__ << " finished." << std::endl;
}

// -- eof
