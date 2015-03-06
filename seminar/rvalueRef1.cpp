
#include <iostream>

struct X
{
	X() noexcept { std::cout << "X()" << std::endl; }
	X(const X&) noexcept { std::cout << "X(const X&)" << std::endl; }
	X(X &&) noexcept { std::cout << "X(X &&)" << std::endl; }
	X& operator=(const X&) noexcept { std::cout << "operator=(const X&)" << std::endl; return *this;}
	X& operator=(X&&) noexcept { std::cout << "operator=(X&&)" << std::endl; return *this;}
	~X() { std::cout << "~X()" << std::endl; }

	void m() & { std::cout << "m() &" << std::endl; }
	void m() && { std::cout << "m() &&" << std::endl; }
};

X f()
{
	X tmp;
	return tmp;
}

int main()
{
	X obj1;
	X &r = obj1;
	X &&rr = f();
	
	obj1.m();
	r.m();
	rr.m();
	f().m();

	return 0;
}
