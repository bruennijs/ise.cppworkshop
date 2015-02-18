#include <iostream>
#include <vector>

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

	/* data */
	E* m_val;
};

int main() {
	MyVector<int> v1;

	MyVector<int> v2 = v1;

	MyVector<int> v3  = v1 + v2;
}