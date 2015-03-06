
#include <iostream>
#include <initializer_list>
#include <typeinfo>

class X
{
public:
	X( int i, std::initializer_list<int> l ) {}
};

class Y
{
public:
	Y( std::initializer_list<int> l ) {}
};

int main()
{
	X o1( 1, {2,3} );
	X o2( 1, {} );
	Y o3{1};
}




