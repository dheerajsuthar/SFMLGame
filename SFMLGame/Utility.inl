#include "stdafx.h"
#include <iostream>

template <typename T>
std::string toString(const T& value) {
	std::stringstream stream;
	stream << value;
	return stream.str();
}