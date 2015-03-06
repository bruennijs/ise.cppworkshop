
#include <iostream>
#include <list>
#include <initializer_list>

struct point
{
	point( int vx, int vy ) : x(vx), y(vy)
	{ std::cout << "point( int vx, int vy )" << std::endl; }
	point( std::initializer_list<int> l )
	{
		auto i = l.begin();
		if( i != l.end() )
		{
			x = *i;
			i++;
		}
		if( i != l.end() ) y = *i;
		std::cout << "point( std::initializer_list<int> l )" << std::endl; 
	}
	int x;
	int y;
};

int main()
{
	point p1(0, 0);
	point p2 = {0, 0};
	point p3{0,0};
	point p4({0,0});
	
	std::list<int> c1( {41,42,43,44} );

}




