#ifndef CPP_PLAYGROUND_ENUM_CLASS_ITERATION_PLUS_H
#define CPP_PLAYGROUND_ENUM_CLASS_ITERATION_PLUS_H

#include <array>
#include <string>
#include <type_traits> // for std::underlying_type

namespace Ada_Byron_code_book::enums {

//
// tools, helpers
//

// From https://stackoverflow.com/questions/14589417/can-an-enum-class-be-converted-to-the-underlying-type
//
// as_integral -- begin
//
template <typename E>
constexpr auto
as_integral(E e) -> typename std::underlying_type<E>::type
{
  return static_cast<typename std::underlying_type<E>::type>(e);
}
//
// as integral -- end

// From https://stackoverflow.com/questions/26936640/how-to-implement-is-enum-class-type-trait
//
// is_enum_class -- begin
//
template <typename T, typename V = void>
struct test : std::false_type {};

template <typename T>
struct test<T, decltype((void)+T{})> : std::true_type {};

template <typename T>
using is_enum_class = std::integral_constant<bool, not test<T>::value and std::is_enum<T>::value>;
//
// is_enum_class -- end

template <class T>
constexpr auto
count_defined()
-> size_t
{
  // Note: This works for
  // 1. consecutive enum values, starting with "zero"; if not > Specialize, and
  // 2. `undefined` must be the last value of the enum class
  static_assert(is_enum_class<T>::value, "Bad type--T should be an enum class");
  return static_cast<size_t>(T::undefined);
}

//
// Planet
//

enum class Planet : uint8_t { Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune, undefined };
auto as_string(Planet) -> std::string;
constexpr auto as_planet(const std::string&) -> Planet;

constexpr std::array all_defined_planets{
  Planet::Mercury,
  Planet::Venus,
  Planet::Earth,
  Planet::Mars,
  Planet::Jupiter,
  Planet::Saturn,
  Planet::Uranus,
  Planet::Neptune};
static_assert(all_defined_planets.size() == count_defined<Planet>(), "Bad array: wrong size");

//
// Opposite
//

enum class Opposite : uint8_t { yin, yang, undefined };
auto as_string(Opposite) -> std::string;
constexpr auto as_opposite(const std::string&) -> Opposite;

constexpr std::array all_defined_opposites{Opposite::yin, Opposite::yang};
static_assert(all_defined_opposites.size() == count_defined<Opposite>(), "Bad array: wrong size");

void ExamplesOfEnumClassAsIntegral();
void ExamplesOfEnumClassIteration();

} // namespace Ada_Byron_code_book::enums

#endif // CPP_PLAYGROUND_ENUM_CLASS_ITERATION_PLUS_H
