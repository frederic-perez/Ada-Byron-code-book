# -- CMake build rules

# Boost stuff
if(WIN32)
	set(Boost_USE_STATIC_LIBS ON)
else()
	set(Boost_USE_STATIC_LIBS OFF)
endif()
set(Boost_USE_MULTITHREADED ON)
# find_package(Boost) # <-- Use this simple line for using only headers
find_package(Boost 
	COMPONENTS
		# lexicographically sorted
		date_time
		filesystem
		locale
		program_options
		system
)
if (Boost_FOUND)
	message(STATUS "Boost found:")
	include_directories(${Boost_INCLUDE_DIRS})
	message(STATUS "  Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
	message(STATUS "  Boost_LIBRARIES: ${Boost_LIBRARIES}
	Note: Boost_LIBRARIES can be empty if no COMPONENTS are used.") # Used below
else ()
	message(FATAL_ERROR "Boost not found - Hint(?): ENV{BOOST_ROOT} is $ENV{BOOST_ROOT}")
endif ()

set(SRC_LIST
	aux-raw.cpp aux-raw.h
	aux-raw-compiler-warnings-off++begin.h aux-raw-compiler-warnings-off++end.h
	aux-spy.cpp aux-spy.h
	algorithm-string-pool.cpp algorithm-string-pool.h
	cli-parser.cpp cli-parser.h
	concurrency.cpp concurrency.h
	cpp11-pool.cpp cpp11-pool.h
	euclidean.cpp euclidean.h
	main.cpp
	filesystem-pool.cpp filesystem-pool.h
	lexical-cast-pool.cpp lexical-cast-pool.h
	preprocessor-pool.cpp preprocessor-pool.h
	promotions-pool.cpp promotions-pool.h
	ublas-pool.cpp ublas-pool.h
	under-construction.cpp under-construction.h
	xml-parser.cpp xml-parser.h
)

add_executable(${PROJECT_NAME} ${SRC_LIST})

# Link the executable to the required libraries

target_link_libraries(${PROJECT_NAME}
	${Boost_LIBRARIES}
#	Other required 3rd party libraries would appear below
)

set(TARGET_NAME ${PROJECT_NAME}Targets)
install(TARGETS ${PROJECT_NAME} # EXPORT ${TARGET_NAME}
#	LIBRARY DESTINATION lib
#	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
#	INCLUDES DESTINATION include
)

# -- eof
