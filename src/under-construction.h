// -- 

#pragma once

#include <array>
#include <cstdint>
#include <initializer_list>
#include <string>
#include <vector>

#include <boost/preprocessor.hpp>

// TODO: (iss) Parse point cloud (ASCII) file as a 1st example (3DI)

#define ABcb_TO_STR(unused, data, elem) BOOST_PP_STRINGIZE(elem),

// Code originarily based on
// http://www.gamedev.net/topic/437852-c-enum-names-as-strings/
//
#define ABcb_DEFINE_NAMESPACE_WITH_ENUM_TOOLS(namespaceName, sequence) \
namespace namespaceName { \
\
enum class Enum : uint8_t { BOOST_PP_SEQ_ENUM(sequence) }; \
const std::array<const char*, BOOST_PP_SEQ_SIZE(sequence)> enumText{{ \
	BOOST_PP_SEQ_FOR_EACH(ABcb_TO_STR, ~, sequence) }}; \
\
const uint8_t first = 1; \
const uint8_t beyond = static_cast<uint8_t>(enumText.size()); \
\
inline \
Enum \
GetEnum(const std::string& a_text) \
{ \
	uint8_t i = first; \
	for (; i < beyond && a_text != enumText[i]; ++i); \
	if (i < beyond) \
		return static_cast<Enum>(i); \
	return Enum::undefined; \
} \
\
inline \
std::string \
GetString(Enum a_enum) \
{	return enumText[static_cast<uint8_t>(a_enum)]; } \
\
inline \
std::vector<std::string> \
GetDefinedStrings() \
{ \
	std::vector<std::string> result; \
	for (uint8_t i = first; i < beyond; ++i) \
		result.push_back(enumText[i]); \
	return result; \
} \
\
} // namespace namespaceName 

namespace Ada_Byron_code_book {

ABcb_DEFINE_NAMESPACE_WITH_ENUM_TOOLS(\
	Guru,
	(undefined)\
	(Andrei_Alexandrescu)(Andrew_Koenig)(Bruce_Eckel)(Bjarne_Stroustrup)\
	(Herb_Sutter)(Ira_Pohl)(Scott_Meyers)
)

void GurusTest(std::initializer_list<std::string>);

// First attempt at creating a template class for enhanced enum classes
#ifdef ADA_BYRON_WORK_IN_PROGRESS_20150616
template<typename Enum, size_t N, std::string>
	//, const std::array<const char*, N>& e>
class EnumENH
{
	int d_i;
	Enum GetEnum(const std::string&) {
		return Enum::undefined;
	}
};

template<typename Enum>
auto
GetEnum(const std::string& a_text)
-> Enum
{
	//uint8_t i = first;
	//for (; i <= last && a_text != enumText[i]; ++i);
	//if (i <= last)
	//	return static_cast<Enum>(i);
	return Enum::undefined;
}

enum class FooBar : uint8_t { undefined, foo, bar };
const std::string fooAndBarText = "foo and bar";
namespace { const std::string s = "abc"; }
const std::array<const char*, 3> fooBarText{{ "undefined", "foo", "bar" }};

//using ConcreteType = EnumENH<FooBar, 3, s>; //, fooBarText>;
using ConcreteType = EnumENH<FooBar, 3, "string">; //, fooBarText>;
#endif

} // namespace Ada_Byron_code_book

// -- eof
