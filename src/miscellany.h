// -- 

#pragma once

namespace Ada_Byron_code_book {

namespace miscellany {

	// See Herb Sutter, Andrei Alexandrescu, C++ Coding Standards: 101 Rules, 
	// Guidelines, and Best Practices, Addison Wesley Professional, 2004,
	// Chapter 15, Use const proactively (particularly, the Examples section)
	//
	void Function(int);
	// void Function(const int); // redeclares the same: top-level const ignored

} // namespace miscellany

} // namespace Ada_Byron_code_book

// -- eof
