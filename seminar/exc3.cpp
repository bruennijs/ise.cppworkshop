
#include <iostream>


struct X
{
	X() { std::cout << "X::X()" << std::endl; }
	~X() { std::cout << "X::~X()" << std::endl; }
};

void f()
{
	X x;

	throw std::exception();
}

int main()
{
	try {
		f();
	}
	catch( ... ) {
		throw;
	}

	return 0;
}

