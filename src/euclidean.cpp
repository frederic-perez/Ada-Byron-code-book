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

	std::clog << __func__ << " finished." << std::endl;
}

// -- eof
