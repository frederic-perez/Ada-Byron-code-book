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

namespace WIP {

template<class T, size_t N>
class V {

	static_assert(
		N > 0,
		"static_assert failed: V template parameter N (size) is 0. "
		"It should be strictly positive.");

public:
	explicit V(T a_value)
	: d_array()
	{ // All elements will be set the input argument
		for (auto& value : d_array)
			value = a_value;
	}

	V() : V(0.) {} // Delegating constructor

	explicit V(std::initializer_list<T> a_args)
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

	T operator[](size_t a_idx) const { return d_array[a_idx]; }
	T& operator[](size_t a_idx) { return d_array[a_idx]; }

	// Note: Here we follow the advice of Scott Meyers, More Effective C++
	// (mec++), Item 22, Consider using op= instead of stand-alone op
	//
	V& operator*=(T a_rhs)
	{
		for (size_t i = 0; i < N; ++i)
			d_array[i] *= a_rhs;
		return *this;
	}

	template<class t, size_t n>
	friend std::ostream& operator<<(std::ostream&, const V<t, n>&);

private:
	std::array<T, N> d_array;
};

template<class T, size_t N, class T2>
const V<T, N>
operator*(const V<T, N>& a_lhs, T2 a_rhs)
{
	return V<T, N>(a_lhs) *= a_rhs;
}

template<class T, size_t N>
std::ostream&
operator<<(std::ostream& a_os, const V<T, N>& a_vector)
{
	// 1st, the size of the Vector
	//
	a_os << '[' << a_vector.d_array.size() << ']';

	// 2nd, its actual contents
	//
	std::ostringstream oss;
	std::vector<std::string> valuesAsStrings;
	for (auto value : a_vector.d_array) {
		oss << value;
		valuesAsStrings.push_back(oss.str());
		// '- Note: We do not use
		//			valuesAsStrings.push_back(std::to_string(value));
		//		because std::to_string(double) outputs six decimal digits
		//		and we want no decimal digits whenever possible.
		oss.str("");
	}
	oss << '(' << boost::algorithm::join(valuesAsStrings, ", ") << ')';
	a_os << oss.str();

	return a_os;
}

template<class V>
void
DoAndOutputStuff(const V& a_vector, const std::string& a_vectorName)
{
	std::cout
		<< pad << a_vectorName << " typeid name = " << typeid(a_vector).name()
		<< '\n'
		<< pad << a_vectorName << " spy::TypeNameENH of its decltype = "
		<< ABcb::spy::TypeNameENH<decltype(a_vector)>() << '\n'
		<< pad << a_vectorName << " = " << a_vector
		<< " | " << a_vectorName << "[0] = " << a_vector[0]
		//		<< " | x2 = " << a_vector * 2.
		<< std::endl;
}

} // namespace WIP

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

	// WIP::V

	using V2 = WIP::V<double, 2>;
	V2 v2a{ 1., 2. };
	WIP::DoAndOutputStuff(v2a, "v2a");
	v2a *= .5f;
	v2a = v2a * 2.f;
	WIP::DoAndOutputStuff(v2a, "v2a after *2");

	std::clog << __func__ << " finished." << std::endl;
}

// -- eof
