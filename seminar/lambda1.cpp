
#include <iostream>
#include <list>
#include <algorithm>
#include <functional>

void printOut( int n )
{
	std::cout << n << std::endl;
}

struct Printer
{
	void operator()( int n )
	{
		std::cout << n << std::endl;
	}
};

const int C = []{ return 42; }();

int main()
{
	std::list<int> c1{ 41, 42, 43 };
	
	std::string str("\n");
	
	std::function<void(int)> l1 = [=]( int n )->void  { std::cout << n << str; };
	auto l2 = [&]( int n )->void  { std::cout << n << str; };
	auto l3 = [str]( int n )->void  { std::cout << n << str; };
	auto l4 = [&str]( int n )->void  { std::cout << n << str; };

	std::for_each( c1.begin(), c1.end(), printOut );
	std::for_each( c1.begin(), c1.end(), Printer() );
	std::for_each( c1.begin(), c1.end(), [&](int n){l1(n);l2(n);l3(n);} );

	[](){}();

	return 0;
}

