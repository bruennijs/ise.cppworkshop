#include <cstdio>
#include <cassert>
#include <list>
#include <utility>
#include <iostream>

class TextdateiException 
{};

class X 
{};

class Textdatei
{
public:
	Textdatei( const char *name ) throw(TextdateiException);
	~Textdatei();
	Textdatei( const Textdatei& ) = delete;
	Textdatei& operator=( const Textdatei& ) = delete;
	
	void schreiben( const char* txt );
private:
	FILE *f;
};

Textdatei::Textdatei( const char *name ) throw(TextdateiException)
: p1( new char[10] ), p2(new char [10])
{
	f = fopen( name, "wt" );
	if( f == nullptr )
	{
		throw TextdateiException();
	}
}
Textdatei::~Textdatei()
{
	fclose( f );
}
	
void Textdatei::schreiben( const char* txt )
{
	fputs( txt, f );
}



int main()
{
	try
	{
		Textdatei d1( "test1.txt" );
		Textdatei d2( "test2.txt" );

		d1.schreiben( "Eine lange Zeile Text.\n" );
		d2.schreiben( "Eine lange Zeile Text.\n" );
	}
	catch( TextdateiException &e )
	{
		std::cerr << "Es hat nicht funktioniert!" << std::endl;
	}

}


