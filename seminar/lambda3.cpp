
#include <iostream>
#include <list>
#include <algorithm>
#include <functional>
;

int main()
{
	auto l1 = [](bool b)->long{ if(b) return 42; else return 23L; };

	return 0;
}

