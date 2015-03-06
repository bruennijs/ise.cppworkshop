
#include <iostream>
#include <string>
#include <typeinfo>

int main()
{
	auto str1 = " Ein String";          // ANSCII/ANSI char
    auto str2 = L" Ein anderer String"; // wchar_t
	auto str3 = u8" noch ein String";   // UTF-8 char        C++11
	auto str4 = u" noch ein String";    // UTF-16 char16_t   C++11
	auto str5 = U" noch ein String";    // UTF-32 char32_t   C++11
	
	const char *str6 = R"XXXX(++s)"++""""(((!!\\)XXXX";
	const char *str7 = R"blubb(++s++""""(((!!\\)blubb";
	const char *str8 = u8R"blubb(++s++""""(((!!\\)blubb";

	std::cout << typeid(str1).name() << str1 << std::endl;
	std::cout << typeid(str2).name() << std::endl;
	std::cout << typeid(str3).name() << str3 << std::endl;
	std::cout << typeid(str4).name() << std::endl;
	std::cout << typeid(str5).name() << std::endl;
	std::cout << str6 << std::endl;
	std::cout << str7 << std::endl;
	std::cout << str8 << std::endl;

	return 0;
}



