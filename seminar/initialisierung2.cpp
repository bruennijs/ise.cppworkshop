
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <typeinfo>

int main()
{
	std::map< std::string, std::string > dic = { {"house", "Haus"}, {"mouse", "Maus"} };
	for( auto i = dic.begin(); i != dic.end(); ++i )
		std::cout << i->first << "  " << i->second << std::endl;


	auto l = {1,2,3,4,5};
	std::cout << typeid(l).name() << std::endl;
	
	for( auto e : l )
		std::cout << e << std::endl;
		
	for( auto i = l.begin(); i != l.end(); ++i  )
		std::cout << *i << std::endl;
}




