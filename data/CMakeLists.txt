# -- CMake build rules

set(SRC_LIST
	input.xml
	rf_00.txt
)

install(FILES ${SRC_LIST}
	DESTINATION bin
)

# -- eof
