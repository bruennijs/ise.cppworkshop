
#include <iostream>
#include <list>

void f( const std::list<int> &c1 )
{
	for( auto i = c1.cbegin(); i != c1.cend(); ++i )
	{
		std::cout << *i << std::endl;
	}
}

int main()
{
	std::list<int> c1{1,6,9};
	for( auto i = std::begin(c1); i != std::end(c1); ++i )
	{
		std::cout << *i << std::endl;
	}
	
	for( auto e : c1 )
	{
		std::cout << e << std::endl;
	}
	
	int array[3] = {111,444,777};
	for( const auto& e : array )
	{
		std::cout << e << std::endl;
	}
	for( auto i = std::begin(array); i != std::end(array); ++i )
	{
		std::cout << *i << std::endl;
	}
}

