
#include <iostream>


struct X
{
	X() { std::cout << "X::X()" << std::endl; }
	~X() { std::cout << "X::~X()" << std::endl; }
};

int main()
{
	try
	{
		X x;
	
		throw std::exception();
	}
	catch( ... )
	{
		throw;
	}
	
	return 0;
}

