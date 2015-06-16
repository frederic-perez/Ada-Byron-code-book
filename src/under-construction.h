// -- 

#pragma once

#include <array>
#include <cstdint>
#include <initializer_list>
#include <string>
#include <vector>

#include <boost/preprocessor.hpp>

#define ABcb_TO_STR(unused,data,elem) BOOST_PP_STRINGIZE(elem),
#define ABcb_DECLARE_ENUM_AND_ENUMTEXT(sequence) \
enum class Enum : uint8_t { BOOST_PP_SEQ_ENUM(sequence) }; \
const std::array<const char*, BOOST_PP_SEQ_SIZE(sequence)> enumText{{ \
	BOOST_PP_SEQ_FOR_EACH(ABcb_TO_STR, ~, sequence) }};

namespace Ada_Byron_code_book {

namespace Guru { // An enum class and related stuff

// Code originarily based on
// http://www.gamedev.net/topic/437852-c-enum-names-as-strings/

ABcb_DECLARE_ENUM_AND_ENUMTEXT(\
	(undefined)\
	(Andrei_Alexandrescu)(Andrew_Koenig)(Bruce_Eckel)(Bjarne_Stroustrup)\
	(Herb_Sutter)(Ira_Pohl)(Scott_Meyers)
)
Enum GetEnum(const std::string&);
std::string GetString(Enum);
std::vector<std::string> GetDefinedStrings();

} // namespace Guru

void GurusTest(std::initializer_list<std::string>);

// First attempt at creating a template class for enhanced enum classes
#ifdef FPCX_WORK_IN_PROGESS_20150616
template<typename Enum, size_t N, std::string> //, const std::array<const char*, N>& e>
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

//using ConcreteType = EnumENH<FooBar, 3, s>; //, fooBarText > ;
using ConcreteType = EnumENH<FooBar, 3, "string">; //, fooBarText > ;
#endif

} // namespace Ada_Byron_code_book

// -- eof
