#include <cassert> // TODO: Use Boost instead of the good old <cassert>

#include <boost/assert.hpp>
#include <boost/log/trivial.hpp>

#include "aux-raw.h"
#include "enum-class-iteration+.h"

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
  BOOST_LOG_TRIVIAL(trace) << __func__ << " started...";

  auto planet = Planet::Earth;
  BOOST_LOG_TRIVIAL(info)
    << pad << "planet = Planet::Earth as string: " << as_string(planet)
    << "; static_cast<uint>(as_integral(planet)): " << static_cast<uint>(as_integral(planet));
  planet = Planet::undefined;
  BOOST_LOG_TRIVIAL(info)
    << pad << "planet = Planet::undefined as string: " << as_string(planet)
    << "; static_cast<uint>(as_integral(planet)): " << static_cast<uint>(as_integral(planet));

  BOOST_LOG_TRIVIAL(trace) << __func__ << " finished.";
}

void
ABcb::enums::ExamplesOfEnumClassIteration()
{
  BOOST_LOG_TRIVIAL(trace) << __func__ << " started...";

  using namespace std::string_literals;

  BOOST_LOG_TRIVIAL(info) << pad << "all_defined_planets.size() = " << all_defined_planets.size();
  BOOST_LOG_TRIVIAL(info) << pad << "count_defined<Planet>() = " << count_defined<Planet>();
  for (const auto planet : all_defined_planets) {
    const std::string planet_str = as_string(planet);
    if (planet != as_planet(planet_str))
      throw "Problem using planet"s;
    BOOST_LOG_TRIVIAL(info) << pad << "planet as string: " << planet_str;
  }

  BOOST_LOG_TRIVIAL(info) << pad << "all_defined_opposites.size() = " << all_defined_opposites.size();
  BOOST_LOG_TRIVIAL(info) << pad << "count_defined<Opposite>() = " << count_defined<Opposite>();
  for (const auto opposite : all_defined_opposites) {
    const std::string opposite_str = as_string(opposite);
    if (opposite != as_opposite(opposite_str))
      throw "Problem using opposite"s;
    BOOST_LOG_TRIVIAL(info) << pad << "opposite as string: " << opposite_str;
  }

  BOOST_LOG_TRIVIAL(trace) << __func__ << " finished.";
}
