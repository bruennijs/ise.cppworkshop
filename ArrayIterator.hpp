#include <array.hpp>

template<typename E, unsigned S>
class ArrayIterator
{
public:
	ArrayIterator(Array* a = nullptr, unsigned i) : m_it(it), m_i(0)
	{}

	ArrayIterator(Array* a = nullptr) : ArrayIterator(a, 0)
	{}

	~ArrayIterator()
	{}

	E& operator*() const { return m_a[m_i]; }
	
	ArrayIterator& operator++() const 
	{ 
		m_i++;
		return *this;
	}

	// pre operator
	ArrayIterator& operator++(int) const 
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