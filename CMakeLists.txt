cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME "Ada-Byron-code-book")
set(PROJECT_TYPE "CXX")
project(${PROJECT_NAME} ${PROJECT_TYPE})

set(CMAKE_VERBOSE_MAKEFILE TRUE)

message(STATUS "CMAKE_C_PLATFORM_ID is ${CMAKE_C_PLATFORM_ID}")
message(STATUS "CMAKE_SYSTEM_NAME is ${CMAKE_SYSTEM_NAME}")

# set(BUILD_TESTING OFF CACHE BOOL OFF FORCE)
# message(STATUS "BUILD_TESTING is ${BUILD_TESTING}")

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
set(MyUserActualFullName "N.N.")
if(${MyUsername} MATCHES "frede" OR "frederic" OR "frederic.perez")
  set(MyUserActualFullName "Frederic-Perez")
endif()
message(STATUS "MyUserActualFullName is ${MyUserActualFullName}")

cmake_host_system_information(RESULT MyHostname QUERY HOSTNAME)
message(STATUS "Your host name (MyHostname variable) is ${MyHostname}")
set(def_CMAKE_MYHOSTNAME CMAKE_MYHOSTNAME=${MyHostname})
message(STATUS "> def_CMAKE_MYHOSTNAME is ${def_CMAKE_MYHOSTNAME}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if("${CMAKE_SYSTEM_NAME}" MATCHES "Windows")
  if(MSVC)
    message(STATUS "Entering Windows/MSVC branch.")
    string(APPEND CMAKE_CXX_FLAGS " "
      "-D_SCL_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS "
      "/W4 /WX /EHa /wd4127 /wd4351 "
      "/diagnostics:caret "
      "/permissive- "
      "/D${def_CMAKE_MYUSERNAME} /D${def_CMAKE_MYHOSTNAME}")
    # '- http://msdn.microsoft.com/en-US/library/thxezb7y.aspx:
    #    /wd n  Disables the compiler warning that is specified in n.
    #    For example, /wd4351 disables compiler warning C4351.
    string(APPEND CMAKE_EXE_LINKER_FLAGS " "
      "/FORCE:MULTIPLE /LARGEADDRESSAWARE")
    message(STATUS "CMAKE_EXE_LINKER_FLAGS are: " ${CMAKE_EXE_LINKER_FLAGS})
  else()
    message(ERROR "Uncontemplated case.")
  endif()
elseif("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
  if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "Entering Linux/CMAKE_COMPILER_IS_GNUCXX branch.")
    string(APPEND CMAKE_CXX_FLAGS " "
      "-Wall -D${def_CMAKE_MYUSERNAME} -D${def_CMAKE_MYHOSTNAME}")
    string(APPEND CMAKE_EXE_LINKER_FLAGS " -pthread")
  else()
    message(STATUS "Entering Linux/else branch. We assume clang++.")
    string(APPEND CMAKE_CXX_FLAGS " "
      "-Wall -D ${def_CMAKE_MYUSERNAME} -D ${def_CMAKE_MYHOSTNAME}")
    string(APPEND CMAKE_EXE_LINKER_FLAGS " -pthread")
  endif()
elseif("${CMAKE_SYSTEM_NAME}" MATCHES "Darwin")
  message(STATUS "Entering Darwin branch. We assume clang++.")
  string(CONCAT CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -Wall "
    "-D${def_CMAKE_MYUSERNAME} -D${def_CMAKE_MYHOSTNAME}")
else()
  message(FATAL_ERROR "Unknown system")
endif()

message(STATUS "CMAKE_CXX_FLAGS are: " ${CMAKE_CXX_FLAGS})

option(BUILD_TESTING "Build the testing tree" ON)
if(BUILD_TESTING)
  set(SITE ${MyUserActualFullName}-at-${MyHostname})
  message(STATUS "SITE is ${SITE}")

  message(STATUS "CMAKE_CXX_COMPILER is ${CMAKE_CXX_COMPILER}")
  message(STATUS "CMAKE_CXX_COMPILER_ID is ${CMAKE_CXX_COMPILER_ID}")
  message(STATUS "CMAKE_CXX_COMPILER_VERSION is ${CMAKE_CXX_COMPILER_VERSION}")
  if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    # See https://cmake.org/cmake/help/v3.19/variable/MSVC_TOOLSET_VERSION.html
    if(MSVC_TOOLSET_VERSION MATCHES 100)
      set(MyCxx "VS-2010")
    elseif (MSVC_TOOLSET_VERSION MATCHES 110)
      set(MyCxx "VS-2012")
    elseif (MSVC_TOOLSET_VERSION MATCHES 120)
      set(MyCxx "VS-2013")
    elseif (MSVC_TOOLSET_VERSION MATCHES 140)
      set(MyCxx "VS-2015")
    elseif (MSVC_TOOLSET_VERSION MATCHES 141)
      set(MyCxx "VS-2017")
    elseif (MSVC_TOOLSET_VERSION MATCHES 142)
      set(MyCxx "VS-2019")
    else()
      set(MyCxx "VS-NNNN")
    endif()
    string(APPEND MyCxx "-${MSVC_TOOLSET_VERSION}")
  else()
    set(MyCxx "${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}")
  endif()
  set(MyBuildType ${CMAKE_CONFIGURATION_TYPES})
  set(BUILDNAME
    ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME}-${MyCxx}-${MyBuildType})
  message(STATUS "BUILDNAME is ${BUILDNAME}")

  include(CTest)
  # '- To build Continuous, Experimental, etc., and enables submission to
  #    dashboards.
  #    From http://www.cmake.org/Wiki/CMake/Testing_With_CTest:
  #    "This module will automatically call enable_testing() ... so you no
  #    longer have to do so ..."
endif(BUILD_TESTING)

add_subdirectory(src)
add_subdirectory(data)
