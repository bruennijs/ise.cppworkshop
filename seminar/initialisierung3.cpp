
#include <iostream>
#include <list>
#include <typeinfo>

int main()
{
	auto l = {1,2,3,4,5};
	std::list<int> c1 = l;
	std::cout << typeid(l).name() << std::endl;
	for( auto i = l.begin(); i != l.end(); ++i )
		std::cout << *i << std::endl;
}




