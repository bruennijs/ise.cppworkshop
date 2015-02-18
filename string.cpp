#include <iostream>
#include <typeinfo>

int main() {
	auto str1 = u8"text bla";
	auto str2 = "text blaä";
	auto str3 = u"text bla";
	auto str4 = U"text bla";
	const char* cstr;
	std::string str;

	//std::cout << typeid(typeid(str)).name() << std::endl;
	std::cout << typeid(str).name() << std::endl;
	std::cout << typeid(cstr).name() << std::endl;
	std::cout << typeid(str1).name() << std::endl;
	std::cout << typeid(str2).name() << std::endl;
	std::cout << typeid(str3).name() << std::endl;
	std::cout << typeid(str4).name() << std::endl;
}