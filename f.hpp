#ifndef _f_hpp
#define _f_hpp

class X
{
public:
	X();
	~X();
	X( const X& ) = delete;
	/* data */
};

void f1();
void f2();

#endif