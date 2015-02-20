#ifndef _f_hpp_
#define _f_hpp_

class X
{
public:
	X();
	~X();
	X( const X& ) = delete;
};

void f1();
void f2();

#endif 
