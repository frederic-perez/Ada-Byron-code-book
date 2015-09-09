# -- CMake build rules

cmake_minimum_required(VERSION 2.8)

project(Ada-Byron-code-book)

message(STATUS "CMAKE_C_PLATFORM_ID is ${CMAKE_C_PLATFORM_ID}")
message(STATUS "CMAKE_SYSTEM_NAME is ${CMAKE_SYSTEM_NAME}")

if("${CMAKE_SYSTEM_NAME}" MATCHES "Windows")
	set(MyUsername $ENV{username})
elseif("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
	set(MyUsername $ENV{USER})
elseif("${CMAKE_SYSTEM_NAME}" MATCHES "Darwin")
	set(MyUsername $ENV{USER})
else()
	set(MyUsername "Unknown")
endif()
message(STATUS "Your username (MyUsername variable) is ${MyUsername}")
set(def_CMAKE_MYUSERNAME CMAKE_MYUSERNAME=${MyUsername})
message(STATUS "> def_CMAKE_MYUSERNAME is ${def_CMAKE_MYUSERNAME}")

if(CMAKE_MAJOR_VERSION LESS 3)
	SITE_NAME(MyHostname)
else()
	cmake_host_system_information(RESULT MyHostname QUERY HOSTNAME)
endif()
message(STATUS "Your host name (MyHostname variable) is ${MyHostname}")
set(def_CMAKE_MYHOSTNAME CMAKE_MYHOSTNAME=${MyHostname}) 
message(STATUS "> def_CMAKE_MYHOSTNAME is ${def_CMAKE_MYHOSTNAME}")
# SET(CTEST_SITE ${MyHostname})
# SET(SITE ${CTEST_SITE}) # For Visual Studio to use the right value

if("${CMAKE_SYSTEM_NAME}" MATCHES "Windows")
	if(MSVC)
		message(STATUS "Entering Windows/MSVC branch.")
		string(CONCAT CMAKE_CXX_FLAGS
			"${CMAKE_CXX_FLAGS} -D_SCL_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS "
			"/W4 /WX /EHa /wd4127 /wd4351 "
			"/D${def_CMAKE_MYUSERNAME} /D${def_CMAKE_MYHOSTNAME}")
		# '- http://msdn.microsoft.com/en-US/library/thxezb7y.aspx:
		#		  /wd n  Disables the compiler warning that is specified in n.
		#			For example, /wd4326 disables compiler warning C4351.
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /FORCE:MULTIPLE")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LARGEADDRESSAWARE")
		message(STATUS "CMAKE_EXE_LINKER_FLAGS are: " ${CMAKE_EXE_LINKER_FLAGS})
	else()
		message(ERROR "Uncontemplated case.")
	endif()
elseif("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
	if(CMAKE_COMPILER_IS_GNUCXX)
		message(STATUS "Entering Linux/CMAKE_COMPILER_IS_GNUCXX branch.")
# TODO: Use string(CONCAT CMAKE_CXX_FLAGS after updating cmake-gui!
		set(CMAKE_CXX_FLAGS
			"${CMAKE_CXX_FLAGS} -Wall -std=c++11 -D${def_CMAKE_MYUSERNAME} -D${def_CMAKE_MYHOSTNAME}")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
	else()
		message(STATUS "Entering Linux/else branch. We assume clang++.")
# TODO: Use string(CONCAT CMAKE_CXX_FLAGS after updating cmake-gui!
		set(CMAKE_CXX_FLAGS
			"${CMAKE_CXX_FLAGS} -Wall -std=c++11 -D ${def_CMAKE_MYUSERNAME} -D ${def_CMAKE_MYHOSTNAME}")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
	endif()
elseif("${CMAKE_SYSTEM_NAME}" MATCHES "Darwin")
	message(STATUS "Entering Darwin branch. We assume clang++.")
	string(CONCAT CMAKE_CXX_FLAGS
		"${CMAKE_CXX_FLAGS} -Wall -std=c++11 "
		"-D${def_CMAKE_MYUSERNAME} -D${def_CMAKE_MYHOSTNAME}")
else()
	message(FATAL_ERROR "Unknown system")
endif()

message(STATUS "CMAKE_CXX_FLAGS are:" ${CMAKE_CXX_FLAGS})

option(BUILD_TESTING "Build the testing tree" ON)
if(BUILD_TESTING)
	enable_testing()
	include(CTest)
	# '- to build Continuous, Experimental, etc., and enables dashboard scripting
endif(BUILD_TESTING)

add_subdirectory(src)
add_subdirectory(data)

# -- eof
