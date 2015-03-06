
#include <typeinfo>
#include <iostream>
#include <list>

auto f() -> int
{
	return 42;
}


int main()
{
	int n1 = 42;
	auto n2 = f();
	auto n3 = 21;
	const auto &n4 = n1;
	decltype(n4) n5 = n1;
	auto *p1 = &n1;
	auto p2 = &n1;

	std::cout << typeid(n1).name() << std::endl;
	std::cout << typeid(n2).name() << std::endl;
	std::cout << typeid(n3).name() << std::endl;
	std::cout << typeid(n4).name() << std::endl;
	std::cout << typeid(n5).name() << std::endl;
	std::cout << typeid(p1).name() << std::endl;
	std::cout << typeid(p2).name() << std::endl;
	
	std::list<int> c1;
	c1.push_back( 44 );
	
	for( std::list<int>::iterator i = c1.begin(); i != c1.end(); ++i )
		std::cout << *i << std::endl;

	for( auto i = c1.begin(); i != c1.end(); ++i )
		std::cout << *i << std::endl;

	return 0;
}


