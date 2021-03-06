#include <typeinfo>
#include <iostream>
#include <list>
#include <string>
//#include <gtest/gtest.h>

#include "Playground.hpp"
#include "Keywords.hpp"

auto f() -> int
{
	return 42;
}

auto fref() -> int&
{
	static int si = 42;
	return si;
}

constexpr int constInt(int n)
{
	return n * n;
}

enum class PotenzEnum : int {
	I1 = constInt(1),
  I2 = constInt(2),
};

enum ConstExprEnum {
	E1 = constInt(5)
};

int main() {
  int n1;
  auto a1 = 0x1122334455667788;
  auto a2 = f();
  auto &a3 = fref();
  
  std::list<int> nList;
  nList.push_back(5);

  for (auto it = nList.begin(); it != nList.end(); ++it)
  {
  	std::cout << *it << std::endl;
  }

  std::cout << typeid(a1).name() << std::endl;
  std::cout << typeid(a2).name() << std::endl;
  std::cout << typeid(a3).name() << std::endl;

  /// keywords exercises
  PotenzEnum pe = PotenzEnum::I2;
  std::cout << (int)pe << std::endl;  
  std::cout << (int)pe << std::endl;  

}