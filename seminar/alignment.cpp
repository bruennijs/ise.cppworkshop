
#include <iostream>

int main()
{
	char a;
	char b;
	alignas(4) char c;
	alignas(16) char d;
	alignas(32) char e;
	alignas(64) char f;
	alignas(128) char g;
	alignas( alignof(e) ) h;
	alignas(1) char s1;
	alignas(4) int s2;
	
	alignas(16) float array[4];
	
	
	std::cout << (void*)&a << std::endl;
	std::cout << (void*)&b << std::endl;
	std::cout << (void*)&c << std::endl;
	std::cout << (void*)&d << std::endl;
	std::cout << (void*)&e << std::endl;
	std::cout << (void*)&f << std::endl;

	return 0;
}
