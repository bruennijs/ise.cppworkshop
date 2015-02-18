#include <iostream>
#include <list>
#include <map>
#include <initializer_list>

struct ints {
	ints(std::initializer_list<int> il)
	{
		auto it = il.begin();
		a = *it;
		++it;
		b = *it;
	}

	int a;
	int b;
};

void print(ints& l)
{
	std::cout << (int)l.a << "," << (int)l.b << std::endl;	
}

int main() {
	ints p1 = {0, 1};
	ints p2({7, 9});
	ints p3({7});

	print(p1);
	print(p2);
	print(p3);

	// map 
	//std::initializer_list<std::string> il = {{"k1", "v1"}, {"k2", "v2"}};
	std::map<std::string, std::string> dic(il);

	std::initializer_list<int> initList;
}