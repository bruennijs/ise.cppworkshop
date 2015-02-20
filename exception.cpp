#include <iostream>
#include <vector>
#include <memory>

class Exception
{
public:
	Exception() {}
	~Exception() {}

	/* data */
};

class X
{
public:
	X() {}
	~X() { std::cout << "~X" << std::endl; }

	/* data */
};

class ClassThrowing
{
public:
	ClassThrowing(std::initializer_list<std::string> il)
	{
		for (auto& v : il)
			m_l.push_back(v);
	}
	~ClassThrowing() 
	{
		std::cout << "~ClassThrowing" << std::endl;
	}

	void DoIt() throw(Exception){
		// try
		// {
			X x;
			for (auto& v : m_l)
				std::cout << v << std::endl;
			throw Exception();
		// }
		// catch (...)
		// {
		// 	std::cout << "exception in DoIt" << std::endl;
		// 	throw;
		// }
	}

	/* data */
private:
	std::vector<std::string> m_l;
};

template<typename MyType>
class exception<MyType> {
private:
	/* data */
public:
	exception(/* args */) = default;
};

int main() {
	ClassThrowing ct({"text1", "text2"});
	try
	{
		std::unique_ptr<char> myBuffer(new char[1000]);
		ct.DoIt();
	}
	catch ( Exception e)
	{
		std::cout << "exception" << std::endl;
	}

	throw exception("for debugging porpouses");
}