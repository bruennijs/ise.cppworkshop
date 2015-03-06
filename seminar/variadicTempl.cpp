// C++11
#include <iostream>
#include <stdexcept>

void newprintf(const char *s)
{
    while (*s) {
        if (*s == '%') {
            if (*(s + 1) == '%') {
                ++s;
            }
            else {
                throw std::runtime_error("invalid format string: missing arguments");
            }
        }
        std::cout << *s++;
    }
}
 
template<typename T, typename... Args>
void newprintf(const char *s, T value, Args... args)
{
    while (*s) {
        if (*s == '%') {
            if (*(s + 1) == '%') {
                ++s;
            }
            else {
                std::cout << value;
                newprintf(s + 1, args...); // call even when *s == 0 to detect extra arguments
                return;
            }
        }
        std::cout << *s++;
    }
    throw std::logic_error("extra arguments provided to printf");
}


template <typename T>
int print1( T &v )
{
	std::cout << v;
	return 0;
}

template <typename T>
void print2( T &v )
{
	std::cout << v;
}


template<typename... Args> inline void pass1(Args&&...) {}

template<typename... Args> inline void expand1(Args&&... args) {
    pass1( print1(args)... );
}

struct pass2 {
    template<typename ...T> pass2(T...) {}
};

template<typename... Args> inline void expand2(Args&&... args) {
    pass2{(print2(args),1)...};
}

struct NullType {};
template <bool C, typename A, typename B> struct IF{ typedef A RESULT; };
template <typename A, typename B> struct IF<false,A,B> { typedef B RESULT; };
template <typename A, typename B> struct EQUALS { enum : bool { result = false }; };
template <typename A > struct EQUALS<A,A> { enum : bool { result = true }; };

template<typename T, typename... TP>
struct TypeList
{
	typedef T type;
	typedef TypeList<TP...> next;
};

template<typename T>
struct TypeList<T>
{
	typedef T type;
	typedef TypeList<NullType> next;
};

template <typename T, typename TL>
struct IsIn
{
	enum : bool { result = EQUALS< T, typename TL::type >::result == false
					?
					IsIn< T, typename TL::next >::result
					:
					true
			    };
};
template <typename T>
struct IsIn<T,TypeList<NullType>>
{
	enum : bool { result = false };
};

template <typename T1, typename T2, typename... TP>
struct IsInTP
{
	enum : bool { result = 
		IsInTP<T1,T2>::result == false ?
		IsInTP<T1,TP...>::result
		: true };
};
template <typename T1, typename T2>
struct IsInTP<T1,T2>
{
	enum : bool { result = false };
};
template <typename T1>
struct IsInTP<T1,T1>
{
	enum : bool { result = true };
};


int main()
{
	newprintf( "Integer: % String: %\n", 42, "blubb" );
	
	expand1( "bla", "blubb", 42 );
	
	std::cout << std::endl;
	
	expand2( "bla", "blubb", 42 );
	
	std::cout << std::endl;
	
	typedef TypeList<short, int, long > Integers;
	
	std::cout << IsInTP<int, char, double, int, long >::result << std::endl;
	std::cout << IsInTP<float, char, double, int, long >::result << std::endl;
	
	std::cout << IsIn<int, Integers>::result << std::endl;
	std::cout << IsIn<float, Integers>::result << std::endl;

	return 0;
}
