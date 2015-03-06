

template <typename T>
struct isPointer
{
	enum : bool { value = false };
};

template <typename T>
struct isPointer<T*>
{
	enum : bool { value = true };
};

template <bool C, typename A, typename B>
struct IF
{
	typedef A RESULT_TYPE;
};
template <typename A, typename B>
struct IF<false,A,B>
{
	typedef B RESULT_TYPE;
};

#include <iostream>

typedef int*   T1;
typedef int    T2;

class Verhalten1
{
public:
	void execute() { std::cout << "blubb" << std::endl; }
};

class Verhalten2
{
public:
	void execute() { std::cout << "bla" << std::endl; }
};

int main()
{
	using V = IF<isPointer<T1>::value,Verhalten1,Verhalten2>::RESULT_TYPE;
	V obj;
	obj.execute();
}

