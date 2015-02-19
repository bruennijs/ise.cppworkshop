#include "f.hpp"
#include <iostream>

X::X() {
	std::cout << "X:X()" << (void*)this << std::endl;
}

X::~X() {
	std::cout << "X:~X()" << (void*)this << std::endl;
}

void f1() {
}

X x;