#include <string>
#include <iostream>
#include <typeinfo>


// =============================================0

template<typename E>
class ArrayIterator;


template <typename E, unsigned S>
class Array
{
public:
	typedef ArrayIterator<E> *iterator;
	typedef const ArrayIterator<E>* const_iterator;

	Array()
	{
		std::cout << "array ctor" << std::endl;
		Init();		
	}
	
	~Array()
	{
		std::cout << "~array" << std::endl;
		if (p_buf != nullptr)
		{
			delete[] p_buf;
			p_buf = nullptr;
		}
	}

	Array(const Array& a)
	{
		std::cout << "array copy" << std::endl;
		Init();
		for (unsigned i = 0;i < S; ++i)	
			p_buf[i] = a.p_buf[i];
	}

	Array(Array&& a)
	{
		std::cout << "array rvalue assigmnent" << std::endl;
		if (this != &a)
		{
			p_buf = a.p_buf;
			a.p_buf = nullptr;
		}
	}

	Array& operator=(Array& a) 
	{
		std::cout << "array assign" << std::endl;
		for (unsigned i = 0;i < S; ++i)	
			p_buf[i] = a.p_buf[i];
		return *this;
	}

	E& operator[](unsigned idx)
	{
		return p_buf[idx];
	}

	unsigned size() const { return S; }

	bool valid() const { p_buf != nullptr; }

	iterator begin() { return &p_buf[0]; }
	iterator end() { return &p_buf[S]; }

	//const_iterator cbegin() const { return static_cast<const_iterator>(&p_buf[0]); }
	//const_iterator cend() const { return  static_cast<const_iterator>(&p_buf[S]); }

	const_iterator cbegin() const { return new ArrayIterator(this, 0); }
	const_iterator cend() const { return new ArrayIterator(this, S); }
private:
	E* p_buf;

	void Init() 
	{ 
		p_buf = new E[S]; 
		std::cout << typeid(p_buf).name() << std::endl;
	}
};

// =========================================
template<typename E>
class ArrayIterator
{
public:
	ArrayIterator(Array* a = nullptr, unsigned i = 0) : m_a(a), m_i(0)
	{}

	~ArrayIterator()
	{}

	E& operator*() const { return m_a[m_i]; }
	
	ArrayIterator& operator++()
	{ 
		m_i++;
		return *this;
	}

	// pre operator
	ArrayIterator& operator++(int)
	{ 
		return *this;
	}

	ArrayIterator& operator!=(const ArrayIterator& a) const
	{
		return m_i != a.m_i;
	}


private:
	Array* m_a;
	int m_i;
};
// ====================================



template<typename E, unsigned S>
void doWithArray(Array<E, S> a)
{
	std::cout << "doWithArray" << std::endl;
	for (auto i = a.cbegin(); i != a.cend(); ++i)
	{
		std::cout << (E)(*i) << std::endl;
	}
}

template<typename E, unsigned S>
void doWithArrayRef(Array<E, S>& a)
{
	std::cout << "doWithArrayRef" << std::endl;
	for (auto i = a.cbegin(); i != a.cend(); ++i)
	{
		std::cout << (E)(*i) << std::endl;
	}
}


Array<std::string, 2> GetArray()
{
	Array<std::string, 2> a1;
	a1[0] = "test1";
	a1[1] = "test2";
	return a1;
}

int main() {
	//Array<int, 2> a1;
	//a1[0] = 4711;
	//a1[1] = 815;

	//doWithArray<int, 2>(a1);
	//doWithArray<int, 2>(std::move(a1));
	
	//doWithArray<std::string, 2>(GetArray());
	//doWithArray<std::string, 2>(std::move(GetArray()));

	Array<std::string, 2> a1 = GetArray();
	doWithArray<std::string, 2>(std::move(a1));

	//doWithArray<std::string, 2>(GetArray());
	//doWithArray<std::string, 2>(std::move(GetArray()));


}