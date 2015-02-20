
#include "f.hpp"
#include <iostream>

X::X() { std::cout << "X::X() an der Adresse " 
                   << (void*)this 
                   << std::endl;
}


X::~X() { std::cout << "X::~X() an der Adresse " 
                   << (void*)this 
                   << std::endl;
}

X obj;

void f1()
{}

