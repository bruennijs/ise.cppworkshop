
#include <iostream>

template <typename E, unsigned S>
class Array
{
	static_assert(S>0,"size must be greater 0");
public:
	Array() { p_buf = new E[S]; }
	Array( const Array &a )
	{
		p_buf = new E[S];
		for( unsigned i = 0; i < S; ++i )
			p_buf[i] = a.p_buf[i];
	}
	Array( Array &&a )
	{
		p_buf = a.p_buf;
		a.p_buf = nullptr;
	}
	~Array() { if(p_buf) delete [] p_buf; }
	Array& operator=( const Array& a )
	{
		if( this != &a )
		{
			for( unsigned i = 0; i < S; ++i )
				p_buf[i] = a.p_buf[i];
		}
		return *this;
	}
	Array& operator=( Array&& a )
	{
		if( this != &a )
		{
			delete [] p_buf;
			p_buf = a.p_buf;
			a.p_buf = nullptr;
		}
		return *this;
	}
	bool valid() const { return p_buf != nullptr; }
	enum { SIZE = S };
	unsigned size() { return (p_buf) ? S : 0; }
	
	E& operator[]( unsigned i ) { return p_buf[i]; }
	const E& operator[]( unsigned i ) const { return p_buf[i]; }
	
	typedef E* iterator;
	typedef const E* const_iterator;
	
	iterator begin() { return &p_buf[0]; }
	iterator end() { return &p_buf[S]; }
	const_iterator begin() const { return &p_buf[0]; }
	const_iterator end() const { return &p_buf[S]; }
	const_iterator cbegin() const { return &p_buf[0]; }
	const_iterator cend() const { return &p_buf[S]; }

private:
	E *p_buf;
};


int main()
{
	Array<int,3> a1;
	
	a1[0] = 44;
	a1[1] = 55;
	a1[2] = 88;
	
	for( auto e : a1 )
		std::cout << e << std::endl;
		
	// Array<int,0> a2;

	return 0;
}




