#include <cassert> // TODO: Use Boost instead of the good old <cassert>

#include <boost/assert.hpp>

#include "aux-raw.h"
#include "enum-class-iteration+.h"
#include "log.h"

namespace Ada_Byron_code_book::enums {

//
// Planet
//

static constexpr std::array text_planet{
  "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"};
static_assert(text_planet.size() == count_defined<Planet>(), "Bad array: wrong size");

auto
as_string(Planet input)
-> std::string
{
  return input == decltype(input)::undefined ? "undefined" : text_planet.at(static_cast<size_t>(input));
}

constexpr auto
as_planet(const std::string& enum_value_str)
-> Planet
{
  using result_type = Planet;
  for (size_t i = 0; i < text_planet.size(); ++i) {
    if (text_planet[i] == enum_value_str) {
      return static_cast<result_type>(i);
    }
  }
  return result_type::undefined;
}

//
// Opposite
//

static constexpr std::array text_opposite{"yin", "yang"};
static_assert(text_opposite.size() == count_defined<Opposite>(), "Bad array: wrong size");

auto
as_string(Opposite input)
-> std::string
{
  return input == decltype(input)::undefined ? "undefined" : text_opposite.at(static_cast<size_t>(input));
}

constexpr auto
as_opposite(const std::string& enum_value_str)
-> Opposite
{
  using result_type = Opposite;
  for (size_t i = 0; i < text_opposite.size(); ++i) {
    if (text_opposite[i] == enum_value_str) {
      return static_cast<result_type>(i);
    }
  }
  return result_type::undefined;
}

} // namespace Ada_Byron_code_book::enums

#if defined(_WIN64)
using uint = unsigned int;
#endif

namespace ABcb = Ada_Byron_code_book;

using ABcb::raw::pad;

void
ABcb::enums::ExamplesOfEnumClassAsIntegral()
{
  B_LOG_TRACE_STARTED

  auto planet = Planet::Earth;
  B_LOG_INFO
    << pad << "planet = Planet::Earth as string: " << as_string(planet)
    << "; static_cast<uint>(as_integral(planet)): " << static_cast<uint>(as_integral(planet));
  planet = Planet::undefined;
  B_LOG_INFO
    << pad << "planet = Planet::undefined as string: " << as_string(planet)
    << "; static_cast<uint>(as_integral(planet)): " << static_cast<uint>(as_integral(planet));

  B_LOG_TRACE_FINISHED
}

void
ABcb::enums::ExamplesOfEnumClassIteration()
{
  B_LOG_TRACE_STARTED

  using namespace std::string_literals;

  B_LOG_INFO << pad << "all_defined_planets.size() = " << all_defined_planets.size();
  B_LOG_INFO << pad << "count_defined<Planet>() = " << count_defined<Planet>();
  for (const auto planet : all_defined_planets) {
    const std::string planet_str = as_string(planet);
    if (planet != as_planet(planet_str))
      throw "Problem using planet"s;
    B_LOG_INFO << pad << "planet as string: " << planet_str;
  }

  B_LOG_INFO << pad << "all_defined_opposites.size() = " << all_defined_opposites.size();
  B_LOG_INFO << pad << "count_defined<Opposite>() = " << count_defined<Opposite>();
  for (const auto opposite : all_defined_opposites) {
    const std::string opposite_str = as_string(opposite);
    if (opposite != as_opposite(opposite_str))
      throw "Problem using opposite"s;
    B_LOG_INFO << pad << "opposite as string: " << opposite_str;
  }

  B_LOG_TRACE_FINISHED
}
