
#include <iostream>

enum Alt { OFF=0, ON=1 };
enum class Neu { Off=0, On=1 };
enum class Neu2 : int { Off=0, On=1 };

int main()
{
	std::cout << ON << std::endl;
	std::cout << (int)Neu::On << std::endl;
	std::cout << (int)Neu2::On << std::endl;
	
	Neu2 n = Neu2::Off;
	
	using Neu2::Off;
	using Neu2::On;
	
	n = On;

}

