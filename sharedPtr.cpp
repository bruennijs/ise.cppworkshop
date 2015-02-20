#include <memory>
#include <iostream>

class X {
public:
	X(std::string data) : m_s(data)
	{}

	~X() 
	{ 
		std::cout << "~X " << m_s << std::endl;
	}

	X(const X& x)
	{ 
		std::cout << "copy x" << std::endl;
	}

	X(X&& x)
	{ 
		std::cout << "move x" << std::endl;
	}

	void print() {
		std::cout << m_s << std::endl;
	}
private:
	std::string m_s;
};

void f_up(std::unique_ptr<X> sp) {
	sp.get()->print();
	std::cout << "END f" << std::endl;
}

void f_sp(std::shared_ptr<X> sp) {
	sp.get()->print();
}

int main() {
	std::shared_ptr<X> sp1(new X("o1"));
	std::unique_ptr<X> up(new X("o2"));

	f_sp(sp1);
	f_up(std::move(up));
	std::cout << "END main" << std::endl;
}
