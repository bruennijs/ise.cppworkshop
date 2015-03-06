
#include <iostream>
//#include <initializer_list>

template<typename E>
class MyVector
{
public:
	MyVector() : p_buffer(nullptr), c(10), s(0) {
		std::cout << "MyVector()" << std::endl;
	}
	MyVector( const MyVector& v ) : p_buffer(nullptr), c(v.c), s(v.s)
	{
		std::cout << "MyVector( const MyVector& v )" << std::endl;
		if( v.p_buffer != nullptr )
		{
			p_buffer = new E[c];
			for( size_t i = 0; i < s; ++i )
				p_buffer[i] = v.p_buffer[i];
		}
	}
	MyVector( MyVector &&v ) // Move Constructor
	: p_buffer(v.p_buffer), c(v.c), s(v.s)
	{
		std::cout << "MyVector( MyVector &&v )" << std::endl;
		v.p_buffer = nullptr;
	}
	
	
	~MyVector() {
		std::cout << "~MyVector()" << std::endl;
		if( p_buffer )
			delete [] p_buffer;
	}
	void push_back( const E& e ) {
		if( p_buffer == nullptr )
			p_buffer = new E[ c ];
			
		if( s == c )
		{
			c *= 2;
			E *p_newbuffer = new E[c];
			for( size_t i = 0; i < s; ++i )
				p_newbuffer[i] = p_buffer[i];
			delete [] p_buffer;
			p_buffer = p_newbuffer;
		}
		
		p_buffer[s++] = e;
	}
	
	size_t size() const { return s; }
	E& operator[]( size_t i ) { return p_buffer[i]; }
	const E& operator[]( size_t i ) const { return p_buffer[i]; }
	
	MyVector operator+( const MyVector& v ) const
	{
		MyVector tmp;
		for( size_t i = 0; i < size(); ++i )
			tmp.push_back( p_buffer[i] );
		for( size_t i = 0; i < v.size(); ++i )
			tmp.push_back( v[i] );
		return tmp;
	}
private:
	E *p_buffer;
	size_t c;
	size_t s;
};

void f( MyVector<int> v )
{
	std::cout << v.size() << std::endl;
}

int main()
{
	MyVector<int> v1;
	MyVector<int> v2;
	
	v1.push_back( 99 );
	v1.push_back( 33 );
	v2.push_back( 555 );
	v2.push_back( 77 );
	
	MyVector<int> v3 = v1 + v2;
	
	f( v1 );
	f( v1 + v2 + v3 );

}

