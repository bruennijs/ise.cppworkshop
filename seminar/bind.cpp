// C++11
#include <iostream>
#include <functional>

void f( int a, int b, int c, int d )
{
	std::cout << a << "  " << b << "  " << c << "  " << d << std::endl;
}

class X
{
public:
	X( int vx ) : x(vx) {}
	void m() const;
private:
	int x;
};

void X::m() const
{
	std::cout << "X::m() " << x << std::endl;
}

int main()
{
	using namespace std::placeholders;
	auto f1 = std::bind( f, 99, _1, 88, _2 );
	auto f2 = std::bind( f, _3, _2, _1, 99 );

	X obj(42);
	auto f3 = std::bind( &X::m, &obj );

	f1( 3, 4 );
	f2( 1, 2, 3 );
	f3();

	return 0;
}
