#include <iostream>
#include <typeinfo>
#include <list>
#include <string>
#include <algorithm>
#include <stdlib.h>

void print(int n) {
	std::cout << n << std::endl;
}

struct Printer
{
	void operator()(int n) {
		print(n);
	}
};

int main() {
	std::list<int> l = {1, 3, 5};
	std::list<std::string> ls = {"Hello", "world"};
	std::string str = "hello world";
	int a = 1;

	for(auto it = l.begin(); it != l.end(); ++it)
	{
		print(*it);
	}

	std::for_each(l.begin(), l.end(), Printer());

	auto l1 =  [&]( int n ) 
	{
		str = "Hello";
		std::cout << str << std::endl;
	};

	auto l3 = [](int n) { std::cout << n << std::endl; };

	std::function<void(int)> l2 = [=]( int n ) { 
		std::cout << str << std::endl;
	};

	std::for_each(l.begin(), l.end(), l1);

	std::for_each(ls.begin(), ls.end(), [](std::string& val) { std::cout << val << std::endl; });

	l3(4711);
}