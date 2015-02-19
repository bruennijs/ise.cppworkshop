#include <iostream>
#include <vector>
#include <list>

class MoveableString
{
public:
	MoveableString()
	{
	}

	~MoveableString()
	{
	}

	std::string m_data;
};

class Moveable
{
public:
	Moveable()
	{
		std::cout << "Moveable" << std::endl;
		this->m_data = new char[1024];
	}

	~Moveable()
	{
		std::cout << "~Moveable" << std::endl;
		if (this->m_data != nullptr)
		{
			delete this->m_data;
		}
	}

	Moveable& operator=(const Moveable& assign)
	{
		std::cout << "Moveable lvalue assigmnent" << std::endl;
	}

/*
	Moveable& operator=(Moveable&& assign)
	{
		std::cout << "Moveable rvalue assigmnent" << std::endl;
	}
	*/

	char* m_data;
};

/*
template<typename E>
class MyVector
{
public:
	MyVector()
	{}

	~MyVector() 
	{
		std::cout << "~MyVector" << std::endl;
	}

	MyVector(const MyVector<E>& v) : m_val(v.m_val)
		std::cout << "MyVector(copy)" << std::endl;
	}

	MyVector<E>& operator=(const MyVector<E> && v)
	{
		std::cout << "MyVector(copy)" << std::endl;	
	}

	MyVector<E>& operator+(const MyVector<E>& obj) {
		std::cout << "operator+" << std::endl;
		this->m_val += obj.m_val;
	}

	std::list<Moveable> m_dl;
};
*/

template<typename E>
class MyContainer
{
public:
	MyContainer()
	{
		std::cout << "MyContainer" << std::endl;
	}

	~MyContainer() 
	{
		std::cout << "~MyContainer" << std::endl;
	}

	MyContainer(const MyContainer<E>& v) : m_data(v.m_data)
	{
		std::cout << "MyContainer(copy)" << std::endl;
	}


	MyContainer<E>& operator=(const MyContainer<E> & v)
	{
		std::cout << "MyContainer assignment" << std::endl;	
		this->m_data = v.m_data;
	}


	/* data */
	E m_data;
};

int main() {
	MyContainer<Moveable> v1;
	MyContainer<Moveable> v3;

	MyContainer<Moveable> v2 = v1;

	//MyVector<Moveable> v3  = v1 + v2;
}