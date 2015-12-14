// -- 

#include "aux-raw.h"
#include "aux-spy.h"
#include "euclidean.h"

namespace ABcb = Ada_Byron_code_book; // Stroustrup C++ PL, p. 179

using ABcb::raw::pad;

namespace {

template<class Vector>
void
DoAndOutputStuff(const Vector& a_vector, const std::string& a_vectorName)
{
	std::cout
		<< pad << a_vectorName << " typeid name = " << typeid(a_vector).name()
		<< '\n'
		<< pad << a_vectorName << " spy::TypeNameENH of its decltype = "
		<< ABcb::spy::TypeNameENH<decltype(a_vector)>() << '\n'
		<< pad << a_vectorName << " = " << a_vector
		<< " | " << a_vectorName << "[0] = " << a_vector[0]
		<< " | Norm() = " << a_vector.Norm()
		<< " | ElementsSum() = " << a_vector.ElementsSum()
		<< " | ElementsAvg() = " << a_vector.ElementsAvg()
		<< " | /2 = " << a_vector / 2.
		<< " | x2 = " << a_vector * 2.
		<< std::endl;
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
		const Vector2 vector2faulty{ 1., 2., 3 };
		std::cerr << pad << "Error: vector2faulty successfully created (?!)\n";
	} catch (const std::length_error& e) {
		std::cerr << pad << __func__ << ": Error caught (creating vector2faulty): "
			<< e.what() << "\n";
	}

	const Vector2 vector2{ 2., 3. };
	DoAndOutputStuff(vector2, "vector2");
	Vector2 vector2Self = vector2; // Copy constructor
	DoAndOutputStuff(vector2Self,	"vector2_copy_ctor");
	vector2Self = vector2; // Assignment operator
	DoAndOutputStuff(vector2Self, "vector2_assignment_operator");

	const double dotProduct = vector2 * vector2Self;
	std::cout << pad << "Dot product: " << vector2 << " * " << vector2Self
		<< " = " << dotProduct << std::endl;

	Vector3 vector3a{ 5., 7., 11. };
	DoAndOutputStuff(vector3a, "vector3a");
	vector3a.Normalize();
	DoAndOutputStuff(vector3a, "vector3a (normalized)");
	std::cout << pad
		<< "vector3a's azimuth angle = " << vector3a.ComputeAzimuthAngle()
		<< "; polar angle = " << vector3a.ComputePolarAngle()
		<< std::endl;

	const Vector3 vector3b{ -4., -6., -10. };
	DoAndOutputStuff(vector3b, "vector3b");

	const Vector3 vector3plus = vector3a + vector3b;
	DoAndOutputStuff(vector3plus, "vector3plus");

	const Vector3 vector3minus = vector3a - vector3b;
	DoAndOutputStuff(vector3minus, "vector3minus");

	const Vector3 vector3cross = vector3a ^ vector3b;
	DoAndOutputStuff(vector3cross, "vector3cross");

	// Vector3Q

	Vector3Q vector3Qa{ 5., 7., 11. };
	DoAndOutputStuff(vector3Qa, "vector3Qa");
	vector3Qa *= .5;
	vector3Qa = vector3Qa * 2.; // No need for ... * static_cast<long double>(2.);
	vector3Qa.Normalize();
	DoAndOutputStuff(vector3Qa, "vector3Qa (normalized)");
	std::cout << pad
		<< "vector3Qa's azimuth angle = " << vector3Qa.ComputeAzimuthAngle()
		<< "; polar angle = " << vector3Qa.ComputePolarAngle()
		<< std::endl;

	const Vector3Q vector3Qb{ -4., -6., -10. };
	DoAndOutputStuff(vector3Qb, "vector3Qb");

	const Vector3Q vector3Qcross = vector3Qa ^ vector3Qb;
	DoAndOutputStuff(vector3Qcross, "vector3Qcross");

	// Vector3HQ

	Vector3HQ vector3HQa{ 5., 7., 11. };
	DoAndOutputStuff(vector3HQa, "vector3HQa");
	vector3HQa *= .5;
	vector3HQa = vector3HQa * 2.;
	vector3HQa.Normalize();
	DoAndOutputStuff(vector3HQa, "vector3HQa (normalized)");
	std::cout << pad
		<< "vector3HQa's azimuth angle = " << vector3HQa.ComputeAzimuthAngle()
		<< "; polar angle = " << vector3HQa.ComputePolarAngle()
		<< std::endl;

	const Vector3HQ vector3HQb{ -4., -6., -10. };
	DoAndOutputStuff(vector3HQb, "vector3HQb");

	const Vector3HQ vector3HQcross = vector3HQa ^ vector3HQb;
	DoAndOutputStuff(vector3HQcross, "vector3HQcross");

	std::clog << __func__ << " finished." << std::endl;
}

// -- eof
