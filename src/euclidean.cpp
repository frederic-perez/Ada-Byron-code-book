// -- 

#include "aux-raw.h"
#include "aux-spy.h"
#include "euclidean.h"

namespace ABcb = Ada_Byron_code_book; // Stroustrup C++ PL, p. 179

using ABcb::raw::pad;

void
ABcb::Euclidean::ExamplesOfVector()
{
	std::clog << __func__ << " started..." << std::endl;

	const Vector2 vector2{ 2., 3. };
	std::cout
		<< pad << "vector2 typeid name = " << typeid(vector2).name() << '\n'
		<< pad << "vector2 spy::TypeName of its decltype = "
			<< spy::TypeName<decltype(vector2)>() << '\n'
		<< pad << "vector2 = " << vector2 
		<< " | vector2[0] = " << vector2[0]
		<< " | Norm() = " << vector2.Norm()
		<< " | *2. = " << vector2 * 2.
		<< std::endl;

	const Vector3 vector3a{ 5., 7., 11. };
	std::cout
		<< pad << "vector3a typeid name = " << typeid(vector3a).name() << '\n'
		<< pad << "vector3a spy::TypeName of its decltype = "
			<< spy::TypeName<decltype(vector3a)>() << '\n'
		<< pad << "vector3a = " << vector3a
		<< " | vector3a[0] = " << vector3a[0]
		<< " | Norm() = " << vector3a.Norm()
		<< " | *2. = " << vector3a * 2.
		<< std::endl;
	const Vector3 vector3b{ -4., -6., -10. };
	std::cout
		<< pad << "vector3b typeid name = " << typeid(vector3b).name() << '\n'
		<< pad << "vector3b spy::TypeName of its decltype = "
		<< spy::TypeName<decltype(vector3b)>() << '\n'
		<< pad << "vector3b = " << vector3b
		<< " | vector3b[0] = " << vector3b[0]
		<< " | Norm() = " << vector3b.Norm()
		<< " | *2. = " << vector3b * 2.
		<< std::endl;
	const Vector3 vector3plus = vector3a + vector3b;
	std::cout
		<< pad << "vector3plus typeid name = "
			<< typeid(vector3plus).name() << '\n'
		<< pad << "vector3plus spy::TypeName of its decltype = "
		<< spy::TypeName<decltype(vector3plus)>() << '\n'
		<< pad << "vector3plus = " << vector3plus
		<< " | vector3plus[0] = " << vector3plus[0]
		<< " | Norm() = " << vector3plus.Norm()
		<< " | *2. = " << vector3plus * 2.
		<< std::endl;
	const Vector3 vector3minus = vector3a - vector3b;
	std::cout
		<< pad << "vector3minus typeid name = "
			<< typeid(vector3minus).name() << '\n'
		<< pad << "vector3minus spy::TypeName of its decltype = "
		<< spy::TypeName<decltype(vector3minus)>() << '\n'
		<< pad << "vector3minus = " << vector3minus
		<< " | vector3minus[0] = " << vector3minus[0]
		<< " | Norm() = " << vector3minus.Norm()
		<< " | *2. = " << vector3minus * 2.
		<< std::endl;

	std::clog << __func__ << " finished." << std::endl;
}

// -- eof
