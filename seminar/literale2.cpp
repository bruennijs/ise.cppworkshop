
#include <iostream>

constexpr long double operator "" _volt( long double n )
{
	return n;
}

int main()
{
	long double i = 30.5_volt;
	
	std::cout << i << std::endl;

	return 0;
}



