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
		<< pad << a_vectorName << " spy::TypeName of its decltype = "
			<< ABcb::spy::TypeName<decltype(a_vector)>() << '\n'
		<< pad << a_vectorName << " = " << a_vector
		<< " | " << a_vectorName << "[0] = " << a_vector[0]
		<< " | Norm() = " << a_vector.Norm()
		<< " | /2. = " << a_vector / 2.
		<< " | *2. = " << a_vector * 2.
		<< std::endl;
}

} // namespace

void
ABcb::Euclidean::ExamplesOfVector()
{
	std::clog << __func__ << " started..." << std::endl;

	const Vector2 vector2default;
	DoAndOutputStuff(vector2default, "vector2default");

	const Vector2 vector2ones(1.);
	DoAndOutputStuff(vector2ones, "vector2ones");

	const Vector2 vector2{ 2., 3. };
	DoAndOutputStuff(vector2, "vector2");

	const Vector3 vector3a{ 5., 7., 11. };
	DoAndOutputStuff(vector3a, "vector3a");

	const Vector3 vector3b{ -4., -6., -10. };
	DoAndOutputStuff(vector3b, "vector3b");

	const Vector3 vector3plus = vector3a + vector3b;
	DoAndOutputStuff(vector3plus, "vector3plus");

	const Vector3 vector3minus = vector3a - vector3b;
	DoAndOutputStuff(vector3minus, "vector3minus");

	std::clog << __func__ << " finished." << std::endl;
}

// -- eof
